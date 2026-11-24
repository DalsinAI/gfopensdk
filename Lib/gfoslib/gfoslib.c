/* Copyright (c) 2026 AmiCradle Team. MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * gfoslib (GF-126): what a module links besides its own code. Field-table
 * checks and conversion, the module match check, the GFSG record, and the
 * helpers over the runtime's import table (struct gf_rt).
 * Include/gfos/gfoslib.h says what each does.
 *
 * Built into every native module. A module is linked with -nostdlib: with
 * GFOS_MODULE_LIBC defined this file also gives it memcpy, memmove, memset
 * and memcmp (hidden), the only C library calls a compiler may emit on its
 * own, so the module's only imports stay the runtime's table. Build it with
 * -fno-builtin -fno-tree-loop-distribute-patterns, so the compiler does not
 * turn those loops back into calls to themselves.
 */
#include "gfos/gfoslib.h"

/* ---- field tables ------------------------------------------------------- */

#define GF_MAX_DEPTH 8

/* the bytes one element of a field takes in each layout; 0: unknown kind */
static unsigned elem(const struct gf_field *f, unsigned *nsz)
{
    switch (f->kind) {
    case GF_K_U8: case GF_K_BYTES: *nsz = 1; return 1;
    case GF_K_U16: *nsz = 2; return 2;
    case GF_K_U32: case GF_K_GPTR: *nsz = 4; return 4;
    case GF_K_U64: *nsz = 8; return 8;
    case GF_K_NEST:
        if (!f->nest) return 0;
        *nsz = f->nest->nsize;
        return f->nest->gsize;
    }
    return 0;
}

static int check(const struct gf_table *t, int depth)
{
    unsigned i;
    if (!t || depth > GF_MAX_DEPTH || (t->nfields && !t->f))
        return -1;
    for (i = 0; i < t->nfields; i++) {
        const struct gf_field *f = &t->f[i];
        unsigned nsz = 0, gsz = elem(f, &nsz);
        if (!gsz || !f->count || !(f->flags & GF_F_INOUT) || (f->flags & ~GF_F_INOUT))
            return -1;
        if ((uint32_t)f->goff + (uint32_t)gsz * f->count > t->gsize ||
            (uint32_t)f->noff + (uint32_t)nsz * f->count > t->nsize)
            return -1;
        if (f->kind == GF_K_NEST && check(f->nest, depth + 1))
            return -1;
    }
    return 0;
}

int gf_table_check(const struct gf_table *t)
{
    return check(t, 0);
}

static int conv(const struct gf_table *t, unsigned char *dst, const unsigned char *src,
                int swap, int to_native, int want)
{
    unsigned i, k;
    for (i = 0; i < t->nfields; i++) {
        const struct gf_field *f = &t->f[i];
        unsigned nsz = 0, gsz = elem(f, &nsz);
        if (!gsz)
            return -1;
        if (!(f->flags & want))
            continue;
        for (k = 0; k < f->count; k++) {
            const unsigned go = f->goff + k * gsz, no = f->noff + k * nsz;
            unsigned char *d = dst + (to_native ? no : go);
            const unsigned char *s = src + (to_native ? go : no);
            switch (f->kind) {
            case GF_K_U8: case GF_K_BYTES: *d = *s; break;
            case GF_K_U16: gf_st16(d, GF_SW16(swap, gf_ld16(s))); break;
            case GF_K_U32: case GF_K_GPTR: gf_st32(d, GF_SW32(swap, gf_ld32(s))); break;
            case GF_K_U64: gf_st64(d, GF_SW64(swap, gf_ld64(s))); break;
            case GF_K_NEST:
                /* the field's mark says whether to go in; inside, each of
                 * the nested structure's fields keeps its own mark */
                if (conv(f->nest, d, s, swap, to_native, want))
                    return -1;
                break;
            }
        }
    }
    return 0;
}

int gf_struct_in(const struct gf_table *t, void *native, const void *guest, int swap)
{
    if (check(t, 0))
        return -1;
    return conv(t, (unsigned char *)native, (const unsigned char *)guest, swap, 1, GF_F_IN);
}

int gf_struct_out(const struct gf_table *t, void *guest, const void *native, int swap)
{
    if (check(t, 0))
        return -1;
    return conv(t, (unsigned char *)guest, (const unsigned char *)native, swap, 0, GF_F_OUT);
}

static uint64_t fnv(uint64_t h, uint32_t v)
{
    int i;
    for (i = 0; i < 4; i++) {
        h ^= (v >> (8 * i)) & 0xff;
        h *= 0x100000001b3ULL;
    }
    return h;
}

/* the 68k side's shape only: the native offsets are this build's. gfmodgen.py
 * (layout_sig) does the same from the .fields file. */
static uint64_t table_sig(uint64_t h, const struct gf_table *t, int depth)
{
    unsigned i;
    if (!t || depth > GF_MAX_DEPTH)
        return h ^ 0xffu;
    h = fnv(h, t->gsize);
    h = fnv(h, t->nfields);
    for (i = 0; i < t->nfields; i++) {
        const struct gf_field *f = &t->f[i];
        h = fnv(h, f->goff);
        h = fnv(h, (uint32_t)f->kind << 16 | f->flags);
        h = fnv(h, f->count);
        if (f->kind == GF_K_NEST)
            h = table_sig(h, f->nest, depth + 1);
    }
    return h;
}

uint64_t gf_tables_sig(const struct gf_table *const *t, unsigned n)
{
    uint64_t h = 0xcbf29ce484222325ULL;
    unsigned i;
    for (i = 0; i < n; i++)
        h = table_sig(h, t ? t[i] : 0, 0);
    return h;
}

/* ---- the module match (Native-Modules-ABI.md section 8) ------------------ */

static int str_eq(const char *a, const char *b)
{
    if (!a || !b)
        return 0;                   /* no name is never a match */
    while (*a && *a == *b) {
        a++;
        b++;
    }
    return *a == *b;
}

int gf_mod_match(const struct gf_mod *m, const struct gf_partner *p, uint16_t host_cpu, uint8_t host_order)
{
    unsigned i;
    if (!m || !p || m->magic[0] != 'G' || m->magic[1] != 'F' || m->magic[2] != 'M' || m->magic[3] != 'D' ||
        m->gate_abi != GF_GATE_ABI)
        return GF_MATCH_MAGIC;
    if (m->cpu != host_cpu)
        return GF_MATCH_CPU;
    if (m->order != host_order)
        return GF_MATCH_ORDER;
    if (!str_eq(m->name, p->name))
        return GF_MATCH_NAME;
    if (m->version != p->version || m->revision != p->revision)
        return GF_MATCH_VERSION;
    if (m->nslots != p->nslots || m->nslots < 4)
        return GF_MATCH_SLOTS;
    if (!m->slots)
        return GF_MATCH_SLOT_TABLE;
    for (i = 0; i < m->nslots; i++) {
        const struct gf_slot *s = &m->slots[i];
        if (s->lvo != -6 * (int)(i + 1) || !s->fn || s->mark > GF_MARK_NATIVE_ONLY ||
            (s->flags & ~(GF_SLOT_D1 | GF_SLOT_CCR)))
            return GF_MATCH_SLOT_TABLE;
    }
    if (m->possize != p->possize || m->possize < GF_LIB_SIZE)
        return GF_MATCH_POSSIZE;
    if (m->ntables && !m->tables)
        return GF_MATCH_TABLES;
    for (i = 0; i < m->ntables; i++)
        if (gf_table_check(m->tables[i]))
            return GF_MATCH_TABLES;
    if (!p->lvo_sig)
        return GF_MATCH_LVO_SIG;
    for (i = 0; i < 32; i++)
        if (m->lvo_sig[i] != p->lvo_sig[i])
            return GF_MATCH_LVO_SIG;
    if (gf_tables_sig(m->tables, m->ntables) != p->layout_sig)
        return GF_MATCH_LAYOUT_SIG;
    return GF_MATCH_OK;
}

const char *gf_match_reason(int why)
{
    switch (why) {
    case GF_MATCH_OK: return "serves";
    case GF_MATCH_MAGIC: return "not a module for this gate";
    case GF_MATCH_CPU: return "another CPU's module";
    case GF_MATCH_ORDER: return "not this CPU's byte order";
    case GF_MATCH_NAME: return "another library's module";
    case GF_MATCH_VERSION: return "version or revision differs from the 68k body";
    case GF_MATCH_SLOTS: return "LVO count differs from the 68k body";
    case GF_MATCH_SLOT_TABLE: return "a slot out of place, without an entry or marked wrong";
    case GF_MATCH_POSSIZE: return "the base's positive size differs from the 68k body's";
    case GF_MATCH_TABLES: return "a field table is not well formed";
    case GF_MATCH_LVO_SIG: return "LVO table differs from the 68k body (or the body has no record)";
    case GF_MATCH_LAYOUT_SIG: return "shared structure layouts differ from the 68k body";
    }
    return "?";
}

static uint16_t be16(const uint8_t *p) { return (uint16_t)(p[0] << 8 | p[1]); }

int gf_gfsg_read(const uint8_t rec[GF_GFSG_SIZE], struct gf_partner *p)
{
    unsigned i;
    if (rec[0] != 'G' || rec[1] != 'F' || rec[2] != 'S' || rec[3] != 'G' || be16(rec + GF_GFSG_VERSION) != 1)
        return -1;
    p->nslots = be16(rec + GF_GFSG_NSLOTS);
    p->possize = be16(rec + GF_GFSG_POSSIZE);
    p->lvo_sig = rec + GF_GFSG_LVO_SIG;
    p->layout_sig = 0;
    for (i = 0; i < 8; i++)
        p->layout_sig = p->layout_sig << 8 | rec[GF_GFSG_LAYOUT_SIG + i];
    return 0;
}

unsigned gf_variant(uint8_t caller_in, uint8_t caller_out, uint8_t module_order)
{
    return GF_VINDEX(caller_in != module_order, caller_out != module_order);
}

/* ---- helpers over the runtime -------------------------------------------- */

const void *gf_ptr_r(struct gf_call *c, gf_gaddr at, uint32_t n)
{
    const void *p = c->rt->ptr(c, at, n, 0);
    if (!p)
        gf_fault(c, 1, at);
    return p;
}

void *gf_ptr_w(struct gf_call *c, gf_gaddr at, uint32_t n)
{
    void *p = c->rt->ptr(c, at, n, 1);
    if (!p)
        gf_fault(c, 2, at);
    return p;
}

gf_gaddr gf_gaddr_of(struct gf_call *c, const void *host)
{
    gf_gaddr g;
    if (!host)
        return 0;
    g = c->rt->gaddr(c, host);
    if (!g)
        gf_fault(c, 3, 0);
    return g;
}

uint32_t gf_size(struct gf_call *c, uint32_t n, uint32_t each, uint32_t extra)
{
    uint32_t v;
    if (__builtin_mul_overflow(n, each, &v) || __builtin_add_overflow(v, extra, &v))
        gf_fault(c, 5, n);
    return v;
}

gf_gaddr gf_alloc_vec(struct gf_call *c, uint32_t size, uint32_t flags)
{
    struct gf_regs io;
    __builtin_memset(&io, 0, sizeof io);
    io.d[0] = size;
    io.d[1] = flags;
    c->rt->lib(c, c->sysbase, GF_LVO_ALLOCVEC, &io);
    return io.d[0];
}

void gf_free_vec(struct gf_call *c, gf_gaddr mem)
{
    struct gf_regs io;
    if (!mem)
        return;
    __builtin_memset(&io, 0, sizeof io);
    io.a[1] = mem;
    c->rt->lib(c, c->sysbase, GF_LVO_FREEVEC, &io);
}

/* ---- a module's own C library calls --------------------------------------- */

#ifdef GFOS_MODULE_LIBC
#define GF_HIDDEN __attribute__((visibility("hidden")))
/* Eight bytes at a time where the two ends allow it */
GF_HIDDEN void *memmove(void *d, const void *s, size_t n)
{
    unsigned char *dd = (unsigned char *)d;
    const unsigned char *ss = (const unsigned char *)s;
    if (dd == ss || !n)
        return d;
    if (dd < ss || dd >= ss + n) {
        for (; n >= 8; n -= 8, dd += 8, ss += 8)
            gf_st64(dd, gf_ld64(ss));
        while (n--)
            *dd++ = *ss++;
    } else {
        for (; n >= 8; n -= 8)
            gf_st64(dd + n - 8, gf_ld64(ss + n - 8));
        while (n--)
            dd[n] = ss[n];
    }
    return d;
}
GF_HIDDEN void *memcpy(void *d, const void *s, size_t n)
{
    return memmove(d, s, n);
}
GF_HIDDEN void *memset(void *d, int v, size_t n)
{
    unsigned char *dd = (unsigned char *)d;
    const uint64_t w = 0x0101010101010101ull * (unsigned char)v;
    for (; n >= 8; n -= 8, dd += 8)
        gf_st64(dd, w);
    while (n--)
        *dd++ = (unsigned char)v;
    return d;
}
GF_HIDDEN int memcmp(const void *a, const void *b, size_t n)
{
    const unsigned char *x = (const unsigned char *)a, *y = (const unsigned char *)b;
    for (; n; n--, x++, y++)
        if (*x != *y)
            return *x < *y ? -1 : 1;
    return 0;
}
#endif
