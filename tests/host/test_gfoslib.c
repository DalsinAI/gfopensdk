/* Host test: gfoslib (Include/gfos/gfoslib.h, GF-126) and a module made by
 * tools/gfmodgen.py, through a stand-in gate: a register frame, guest memory
 * at its own addresses (not the host's), exec's AllocVec and FreeVec, and a
 * "68k" function to call back. For each caller order, "in" and "out" each
 * BE or LE, the session's copy is checked, then every call's results in the
 * caller's own order. The module's order is this build's (an LE host runs
 * the LE-module rows; a BE target runs the BE-module rows: test_gfoslib.sh).
 * The 68k side's values come from the GFSG record gfmodgen wrote for it
 * (tstmod_gfsg.c), whose layout signature gfmodgen works out from
 * test_gfoslib.fields on its own, not from the module's C tables. */
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include "tstmod.h"
#include "test_gfoslib_lib.h"

extern const struct gf_mod gfmod_header;
extern const unsigned char gfsg_record[64];

static int checks, fails;
#define CHECK(cond, ...) do { checks++; if (!(cond)) { fails++; printf("FAIL %s:%d ", __FILE__, __LINE__); \
    printf(__VA_ARGS__); printf("\n"); } } while (0)

/* ---- the stand-in runtime ------------------------------------------------- */

#define RAM_BASE 0x00100000u
#define RAM_SIZE (1u << 20)
#define SYSBASE  0x00000400u
#define HOOK_FN  0x00000800u
static uint8_t ram[RAM_SIZE];
static uint32_t brk_at = RAM_BASE + 0x10000;
static int allocs, faults;
static jmp_buf fault_jb;

static void *rt_ptr(struct gf_call *c, gf_gaddr at, uint32_t n, int write)
{
    (void)c; (void)write;
    if (at < RAM_BASE || n > RAM_SIZE || at - RAM_BASE > RAM_SIZE - n)
        return NULL;
    return ram + (at - RAM_BASE);
}
static gf_gaddr rt_gaddr(struct gf_call *c, const void *h)
{
    const uint8_t *p = (const uint8_t *)h;
    (void)c;
    return (p >= ram && p < ram + RAM_SIZE) ? (gf_gaddr)(p - ram) + RAM_BASE : 0;
}
static void rt_call68k(struct gf_call *c, gf_gaddr e, const struct gf_regs *in, struct gf_regs *out)
{
    (void)c; (void)e;
    *out = *in;
}
static uint32_t rt_callc(struct gf_call *c, gf_gaddr fn, uint32_t nargs, const uint32_t *args)
{
    (void)c;
    if (fn == HOOK_FN && nargs == 1)
        return args[0] * 3;          /* the "68k" function: x * 3 */
    return 0;
}
static void rt_lib(struct gf_call *c, gf_gaddr base, int16_t lvo, struct gf_regs *io)
{
    (void)c;
    if (base != SYSBASE)
        return;
    if (lvo == GF_LVO_ALLOCVEC) {
        uint32_t n = (io->d[0] + 15) & ~7u;
        if (brk_at + n > RAM_BASE + RAM_SIZE) { io->d[0] = 0; return; }
        io->d[0] = brk_at + 8;
        brk_at += n;
        allocs++;
    } else if (lvo == GF_LVO_FREEVEC) {
        allocs--;
    }
}
static void *rt_halloc(struct gf_call *c, size_t n) { (void)c; (void)n; return NULL; }
static void rt_hfree(struct gf_call *c, void *p) { (void)c; (void)p; }
static void rt_fault(struct gf_call *c, uint32_t code, gf_gaddr at)
{
    (void)c; (void)code; (void)at;
    faults++;
    longjmp(fault_jb, 1);
}
static const struct gf_rt rt = { GF_GATE_ABI, rt_ptr, rt_gaddr, rt_call68k, rt_callc, rt_lib,
                                 rt_halloc, rt_hfree, rt_fault };

/* the gate, as the runtime's: D0 always, D1 and the CCR as the slot says */
static struct gf_sess sess;
static struct gf_regs after;
static uint32_t gate(int16_t lvo, const struct gf_regs *in)
{
    struct gf_call c;
    const struct gf_slot *s;
    unsigned i = (unsigned)(-lvo / 6 - 1);
    memset(&c, 0, sizeof c);
    c.r = *in;
    c.s = &sess;
    c.m = &gfmod_header;
    c.rt = &rt;
    c.sysbase = SYSBASE;
    if (i >= gfmod_header.nslots || gfmod_header.slots[i].lvo != lvo)
        return 0xdeadbeefu;
    s = &gfmod_header.slots[i];
    s->fn(&c);
    after = *in;
    after.d[0] = c.r.d[0];
    if (s->flags & GF_SLOT_D1)
        after.d[1] = c.r.d[1];
    if (s->flags & GF_SLOT_CCR)
        after.sr = (uint16_t)((in->sr & ~0x1fu) | (c.r.sr & 0x1fu));
    return after.d[0];
}

/* ---- caller-side stores and loads in a stated order --------------------- */

static uint8_t *G(gf_gaddr a) { return ram + (a - RAM_BASE); }
static int sw(uint8_t order) { return order != GFOS_NATIVE_ORDER; }
static void put16(gf_gaddr a, uint16_t v, uint8_t o) { gf_st16(G(a), GF_SW16(sw(o), v)); }
static void put32(gf_gaddr a, uint32_t v, uint8_t o) { gf_st32(G(a), GF_SW32(sw(o), v)); }
static uint16_t get16(gf_gaddr a, uint8_t o) { return GF_SW16(sw(o), gf_ld16(G(a))); }
static uint32_t get32(gf_gaddr a, uint8_t o) { return GF_SW32(sw(o), gf_ld32(G(a))); }
static uint64_t get64(gf_gaddr a, uint8_t o) { return GF_SW64(sw(o), gf_ld64(G(a))); }
static const char *on(uint8_t o) { return o == GFOS_BE ? "BE" : "LE"; }

static void orders(uint8_t in, uint8_t out)
{
    struct gf_regs r;
    const gf_gaddr outer = RAM_BASE + 0x100, buf = RAM_BASE + 0x200, fillb = RAM_BASE + 0x400;
    const uint8_t mo = gfmod_header.order;
    uint32_t i, v;

    sess.in = in;
    sess.out = out;
    sess.variant = (uint8_t)gf_variant(in, out, mo);
    CHECK(sess.variant == GF_VINDEX(in != mo, out != mo), "%s->%s variant %u", on(in), on(out), sess.variant);

    memset(&r, 0, sizeof r);
    r.d[0] = 40; r.d[1] = 2; r.sr = 0x2700 | 0x1f;
    CHECK(gate(-30, &r) == 42 && after.sr == 0x2700, "%s->%s TstAdd, CCR %04x", on(in), on(out), after.sr);

    /* TstSwizzle: the structure in the caller's "in" order */
    memset(G(outer), 0xEE, 64);
    put16(outer + 0, 0x1234, in);
    put32(outer + 4, 5, in);
    put32(outer + 8, 0x01020304u, in);
    put16(outer + 12, 0x0A0B, in);
    G(outer)[14] = 0x55; G(outer)[15] = 0x66;
    put32(outer + 16, buf, in);
    for (i = 0; i < 3; i++) put16(outer + 24 + 2 * i, (uint16_t)(0x100 + i), in);
    for (i = 0; i < 16; i++) G(buf)[i] = (uint8_t)(i * 7 + 1);
    r.a[0] = outer;
    v = gate(-36, &r);
    {
        uint32_t a = 0x01020304u ^ 0xA5A5A5A5u, sum = 0x1234 + a + 0x67;
        for (i = 0; i < 6; i++) sum += (uint32_t)(i * 7 + 1) * (i + 1);
        CHECK(v == 6, "%s->%s TstSwizzle returned %u", on(in), on(out), v);
        CHECK(get32(outer + 4, out) == 6, "%s->%s count", on(in), on(out));
        CHECK(get32(outer + 8, out) == a, "%s->%s inner.a %08x", on(in), on(out), get32(outer + 8, out));
        CHECK(get16(outer + 12, out) == 0x0B0D, "%s->%s inner.b %04x", on(in), on(out), get16(outer + 12, out));
        CHECK(G(outer)[14] == 0xAA, "%s->%s inner.c", on(in), on(out));
        CHECK(G(outer)[15] == 0x66, "%s->%s inner.d, \"in\" only inside a nested table, untouched", on(in), on(out));
        CHECK(get32(outer + 20, out) == sum, "%s->%s sum %08x, want %08x", on(in), on(out),
              get32(outer + 20, out), sum);
        for (i = 0; i < 3; i++)
            CHECK(get16(outer + 24 + 2 * i, out) == (uint16_t)((0x100 + i) * 2 + 1), "%s->%s tag[%u]",
                  on(in), on(out), i);
        CHECK(get16(outer + 0, in) == 0x1234 && get32(outer + 16, in) == buf,
              "%s->%s the IN-only fields untouched", on(in), on(out));
        CHECK(G(outer)[30] == 0xEE, "%s->%s nothing past the structure", on(in), on(out));
    }

    /* TstFill: the seed in "in" order, everything back in "out" order */
    memset(G(fillb), 0, 64);
    put32(fillb, 0x00C0FFEEu, in);
    r.a[0] = fillb; r.d[0] = 5; r.d[1] = 0x11;
    v = gate(-42, &r);
    CHECK(v == 0x00C0FFEEu, "%s->%s TstFill seed %08x", on(in), on(out), v);
    for (i = 0; i < 5; i++)
        CHECK(get32(fillb + 4 * i, out) == 0x00C0FFEEu + i * 0x11, "%s->%s fill[%u]", on(in), on(out), i);
    CHECK(get16(fillb + 20, out) == 0xFFEE, "%s->%s fill word", on(in), on(out));
    CHECK(get64(fillb + 22, out) == (uint64_t)0x00C0FFEEu * 0x100000001ull + 0x11, "%s->%s fill quad",
          on(in), on(out));
    CHECK(gf_u2f(get32(fillb + 30, out)) == (float)0x00C0FFEEu * 0.5f, "%s->%s fill float", on(in), on(out));

    /* TstHook: the caller's function called back */
    r.a[0] = HOOK_FN; r.d[0] = 7;
    CHECK(gate(-48, &r) == 43, "%s->%s TstHook", on(in), on(out));
}

/* a malformed table for each rule gf_table_check has */
struct bad_g { uint32_t a, b; } GF_SHARED;
struct bad_n { uint32_t a, b; };
static const struct gf_field past_f[] = { { 6, 0, GF_K_U32, GF_F_IN, 1, 0 } };            /* 6 + 4 > 8 */
static const struct gf_field kind_f[] = { { 0, 0, 3, GF_F_IN, 1, 0 } };                   /* no kind 3 */
static const struct gf_field nest_f[] = { { 0, 0, GF_K_NEST, GF_F_IN, 1, 0 } };           /* no table */
static const struct gf_field array_f[] = { { 0, 0, GF_K_U16, GF_F_IN, 5, 0 } };           /* 2 * 5 > 8 */
static const struct gf_field flags_f[] = { { 0, 0, GF_K_U32, 0, 1, 0 } };                 /* no direction */
static const struct gf_table bad[] = {
    { "past", 8, 8, 1, past_f }, { "kind", 8, 8, 1, kind_f }, { "nest", 8, 8, 1, nest_f },
    { "array", 8, 8, 1, array_f }, { "flags", 8, 8, 1, flags_f },
};

int main(void)
{
    static const uint8_t ords[2] = { GFOS_BE, GFOS_LE };
    const struct gf_mod *m = &gfmod_header;
    struct gf_partner p, q;
    struct gf_regs r;
    struct gf_mod tm;
    struct gf_slot slots[16];
    const struct gf_table *badt[1];
    uint8_t buf[64];
    unsigned i, j;

    /* the 68k side: its GFSG record, with its RomTag's name and version */
    memset(&p, 0, sizeof p);
    CHECK(gf_gfsg_read(gfsg_record, &p) == 0, "the GFSG record reads");
    p.name = "gfoslibtest.library"; p.version = 1; p.revision = 2;
    CHECK(p.nslots == TM_NSLOTS && p.nslots == 10 && p.possize == TM_POSSIZE, "the record's slots and possize");
    CHECK(p.layout_sig == TM_LAYOUT_SIG && gf_tables_sig(tm_tables, 2) == TM_LAYOUT_SIG,
          "gfmodgen's layout signature (from the .fields) is the C tables' %016llx",
          (unsigned long long)gf_tables_sig(tm_tables, 2));
    for (i = 0; i < 2; i++)
        CHECK(gf_table_check(tm_tables[i]) == 0, "the generated table %s is well formed", tm_tables[i]->name);
    CHECK(m->slots[4].lvo == -30 && m->slots[9].lvo == -60, "slot order");
    CHECK(m->slots[4].flags == GF_SLOT_CCR && m->slots[8].flags == GF_SLOT_D1 && m->slots[5].mark == GF_MARK_HEAVY,
          "slot flags and marks");

    /* what makes a module lose to its 68k body */
#define MATCH(want, what) do { int w_ = gf_mod_match(&tm, &q, GFOS_CPU, GFOS_NATIVE_ORDER); \
    CHECK(w_ == (want), "%s: %s", what, gf_match_reason(w_)); tm = *m; q = p; } while (0)
    tm = *m; q = p;
    MATCH(GF_MATCH_OK, "the module serves");
    tm.magic[3] = 'X'; MATCH(GF_MATCH_MAGIC, "magic");
    tm.gate_abi = 2; MATCH(GF_MATCH_MAGIC, "a gate ABI this runtime lacks");
    CHECK(gf_mod_match(NULL, &p, GFOS_CPU, GFOS_NATIVE_ORDER) == GF_MATCH_MAGIC, "no module");
    CHECK(gf_mod_match(m, &p, GFOS_CPU == 62 ? 183 : 62, GFOS_NATIVE_ORDER) == GF_MATCH_CPU, "another CPU");
    CHECK(gf_mod_match(m, &p, GFOS_CPU, GFOS_NATIVE_ORDER == GFOS_BE ? GFOS_LE : GFOS_BE) == GF_MATCH_ORDER,
          "another byte order");
    q.name = "other.library"; MATCH(GF_MATCH_NAME, "name");
    q.name = NULL; MATCH(GF_MATCH_NAME, "no name on the 68k side");
    tm.name = NULL; q.name = NULL; MATCH(GF_MATCH_NAME, "no name on either side");
    q.revision = 3; MATCH(GF_MATCH_VERSION, "revision");
    q.nslots = 11; MATCH(GF_MATCH_SLOTS, "nslots");
    memcpy(slots, m->slots, sizeof(slots[0]) * m->nslots);
    slots[6].lvo = -48; tm.slots = slots; MATCH(GF_MATCH_SLOT_TABLE, "a slot out of place");
    memcpy(slots, m->slots, sizeof(slots[0]) * m->nslots);
    slots[7].fn = NULL; tm.slots = slots; MATCH(GF_MATCH_SLOT_TABLE, "a slot with no entry");
    memcpy(slots, m->slots, sizeof(slots[0]) * m->nslots);
    slots[7].mark = 9; tm.slots = slots; MATCH(GF_MATCH_SLOT_TABLE, "a slot marked wrong");
    tm.slots = NULL; MATCH(GF_MATCH_SLOT_TABLE, "no slots");
    q.possize = 40; MATCH(GF_MATCH_POSSIZE, "possize");
    for (i = 0; i < sizeof bad / sizeof bad[0]; i++) {
        badt[0] = &bad[i];
        CHECK(gf_table_check(&bad[i]) == -1, "table %s is refused", bad[i].name);
        CHECK(gf_struct_in(&bad[i], buf, buf + 16, 0) == -1 && gf_struct_out(&bad[i], buf, buf + 16, 0) == -1,
              "table %s converts nothing", bad[i].name);
        tm.tables = badt; tm.ntables = 1; MATCH(GF_MATCH_TABLES, bad[i].name);
    }
    memcpy(buf, p.lvo_sig, 32); buf[5] ^= 1; q.lvo_sig = buf; MATCH(GF_MATCH_LVO_SIG, "lvo_sig");
    q.lvo_sig = NULL; MATCH(GF_MATCH_LVO_SIG, "a 68k body with no record");
    q.layout_sig ^= 1; MATCH(GF_MATCH_LAYOUT_SIG, "layout_sig");
    tm.ntables = 1; MATCH(GF_MATCH_LAYOUT_SIG, "layout_sig, a table missing");

    /* every caller order against this module's order */
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            orders(ords[i], ords[j]);

    /* D1 and the CCR, written back for the slots that say so */
    memset(&r, 0, sizeof r);
    r.d[0] = 100; r.d[1] = 7; r.d[2] = 0x55;
    CHECK(gate(-54, &r) == 14 && after.d[1] == 2 && after.d[2] == 0x55, "TstDivMod: D0 14, D1 2");
    r.d[0] = 0xffffffffu; r.d[1] = 1; r.sr = 0x2000;
    CHECK(gate(-30, &r) == 0 && after.sr == 0x2015, "TstAdd carries: X Z C, %04x", after.sr);
    r.d[0] = 0x7fffffffu; r.d[1] = 1;
    CHECK(gate(-30, &r) == 0x80000000u && after.sr == 0x200a, "TstAdd overflows: N V, %04x", after.sr);
    r.a[0] = HOOK_FN; r.d[0] = 5; r.d[1] = 6; r.sr = 0x001f;
    CHECK(gate(-48, &r) == 31 && after.sr == 0x001f && after.d[1] == 6,
          "a slot without the flags leaves D1 and the CCR");

    /* a range the runtime refuses is a fault, never a NULL in the module */
    memset(&r, 0, sizeof r);
    r.a[0] = 0x10;
    if (!setjmp(fault_jb))
        gate(-36, &r);
    CHECK(faults == 1, "a refused range faults (%d)", faults);
    /* a size from the caller that wraps is a fault, not a short range */
    r.a[0] = RAM_BASE + 0x400; r.d[0] = 0x40000000u; r.d[1] = 1;
    if (!setjmp(fault_jb))
        gate(-42, &r);
    CHECK(faults == 2, "a size that wraps faults (%d)", faults);
    /* the library base's count, BE whatever the session */
    {
        const gf_gaddr base = RAM_BASE + 0x800;
        memset(G(base), 0, GF_LIB_SIZE);
        G(base)[GF_LIB_FLAGS] = GF_LIBF_DELEXP;
        r.a[6] = base;
        CHECK(gate(-6, &r) == base, "Open returns A6");
        gate(-6, &r);
        CHECK(G(base)[GF_LIB_OPENCNT] == 0 && G(base)[GF_LIB_OPENCNT + 1] == 2, "lib_OpenCnt BE");
        CHECK(!(G(base)[GF_LIB_FLAGS] & GF_LIBF_DELEXP), "DELEXP cleared");
        gate(-12, &r);
        CHECK(G(base)[GF_LIB_OPENCNT + 1] == 1, "Close");
    }
    {
        struct gf_call c;
        gf_gaddr a;
        memset(&c, 0, sizeof c);
        c.rt = &rt; c.sysbase = SYSBASE;
        a = gf_alloc_vec(&c, 100, GF_MEMF_ANY);
        CHECK(a >= RAM_BASE && allocs == 1, "AllocVec through exec's table");
        gf_free_vec(&c, a);
        CHECK(allocs == 0, "FreeVec");
    }
    printf("gfoslib: module %s %s, %d checks, %d failed\n", GFOS_CPU == 62 ? "x86-64" : GFOS_CPU == 183 ? "ARM64" :
           GFOS_CPU == 20 ? "PPC" : "68k", on(gfmod_header.order), checks, fails);
    return fails != 0;
}
