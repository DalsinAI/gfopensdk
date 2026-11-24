/* Host test: gfoslib (Include/gfos/gfoslib.h, GF-126) and a module made by
 * tools/gfmodgen.py, through a stand-in gate: a register frame, guest memory
 * at its own addresses (not the host's), exec's AllocVec and FreeVec, and a
 * "68k" function to call back. For each caller order, "in" and "out" each
 * BE or LE, the session's copy is checked, then every call's results in the
 * caller's own order. The module's order is this build's (an LE host runs
 * the LE-module rows; a BE target runs the BE-module rows: run.sh). */
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include "tstmod.h"
#include "test_gfoslib_lib.h"

extern const struct gf_mod gfmod_header;

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
    (void)c;
    const uint8_t *p = (const uint8_t *)h;
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

static struct gf_sess sess;
static uint32_t gate(int16_t lvo, const struct gf_regs *in)
{
    struct gf_call c;
    unsigned i;
    memset(&c, 0, sizeof c);
    c.r = *in;
    c.s = &sess;
    c.m = &gfmod_header;
    c.rt = &rt;
    c.sysbase = SYSBASE;
    for (i = 0; i < gfmod_header.nslots; i++)
        if (gfmod_header.slots[i].lvo == lvo) {
            gfmod_header.slots[i].fn(&c);
            return c.r.d[0];
        }
    return 0xdeadbeefu;
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
    r.d[0] = 40; r.d[1] = 2;
    CHECK(gate(-30, &r) == 42, "%s->%s TstAdd", on(in), on(out));

    /* TstSwizzle: the structure in the caller's "in" order */
    memset(G(outer), 0xEE, 64);
    put16(outer + 0, 0x1234, in);
    put32(outer + 4, 5, in);
    put32(outer + 8, 0x01020304u, in);
    put16(outer + 12, 0x0A0B, in);
    G(outer)[14] = 0x55; G(outer)[15] = 0x66;
    put32(outer + 16, buf, in);
    for (i = 0; i < 16; i++) G(buf)[i] = (uint8_t)(i * 7 + 1);
    r.a[0] = outer;
    v = gate(-36, &r);
    {
        uint32_t a = 0x01020304u ^ 0xA5A5A5A5u, sum = 0x1234 + a + 0x66;
        for (i = 0; i < 6; i++) sum += (uint32_t)(i * 7 + 1) * (i + 1);
        CHECK(v == 6, "%s->%s TstSwizzle returned %u", on(in), on(out), v);
        CHECK(get32(outer + 4, out) == 6, "%s->%s count", on(in), on(out));
        CHECK(get32(outer + 8, out) == a, "%s->%s inner.a %08x", on(in), on(out), get32(outer + 8, out));
        CHECK(get16(outer + 12, out) == 0x0B0D, "%s->%s inner.b %04x", on(in), on(out), get16(outer + 12, out));
        CHECK(G(outer)[14] == 0xAA && G(outer)[15] == 0x66, "%s->%s inner.c/d", on(in), on(out));
        CHECK(get32(outer + 20, out) == sum, "%s->%s sum %08x, want %08x", on(in), on(out),
              get32(outer + 20, out), sum);
        CHECK(get16(outer + 0, in) == 0x1234 && get32(outer + 16, in) == buf,
              "%s->%s the IN-only fields untouched", on(in), on(out));
        CHECK(G(outer)[24] == 0xEE, "%s->%s nothing past the structure", on(in), on(out));
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

int main(void)
{
    static const uint8_t ords[2] = { GFOS_BE, GFOS_LE };
    const struct gf_mod *m = &gfmod_header;
    struct gf_partner p;
    struct gf_regs r;
    uint8_t sig[32];
    unsigned i, j;
    const char *hex = TM_LVO_SIG;

    for (i = 0; i < 32; i++) {
        unsigned b;
        sscanf(hex + 2 * i, "%2x", &b);
        sig[i] = (uint8_t)b;
    }
    /* the header, and what makes a module lose to its 68k body */
    CHECK(m->nslots == TM_NSLOTS && m->nslots == 9, "nslots %u", m->nslots);
    CHECK(m->slots[4].lvo == -30 && m->slots[8].lvo == -54, "slot order");
    p.name = "gfoslibtest.library"; p.version = 1; p.revision = 2; p.nslots = 9;
    p.lvo_sig = sig; p.layout_sig = gf_tables_sig(tst_tables, 2);
    CHECK(gf_mod_match(m, &p, GFOS_CPU) == GF_MATCH_OK, "match: %s", gf_match_reason(gf_mod_match(m, &p, GFOS_CPU)));
    CHECK(gf_mod_match(m, &p, GFOS_CPU == 62 ? 183 : 62) == GF_MATCH_CPU, "another CPU");
    p.revision = 3;
    CHECK(gf_mod_match(m, &p, GFOS_CPU) == GF_MATCH_VERSION, "revision");
    p.revision = 2; p.nslots = 10;
    CHECK(gf_mod_match(m, &p, GFOS_CPU) == GF_MATCH_SLOTS, "nslots");
    p.nslots = 9; p.name = "other.library";
    CHECK(gf_mod_match(m, &p, GFOS_CPU) == GF_MATCH_NAME, "name");
    p.name = "gfoslibtest.library"; sig[5] ^= 1;
    CHECK(gf_mod_match(m, &p, GFOS_CPU) == GF_MATCH_LVO_SIG, "lvo_sig");
    sig[5] ^= 1; p.lvo_sig = NULL;
    CHECK(gf_mod_match(m, &p, GFOS_CPU) == GF_MATCH_LVO_SIG, "a 68k body with no record");
    p.lvo_sig = sig; p.layout_sig ^= 1;
    CHECK(gf_mod_match(m, &p, GFOS_CPU) == GF_MATCH_LAYOUT_SIG, "layout_sig");
    p.layout_sig = gf_tables_sig(tst_tables, 1);
    CHECK(gf_mod_match(m, &p, GFOS_CPU) == GF_MATCH_LAYOUT_SIG, "layout_sig, a table missing");

    /* every caller order against this module's order */
    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            orders(ords[i], ords[j]);

    /* a range the runtime refuses is a fault, never a NULL in the module */
    memset(&r, 0, sizeof r);
    r.a[0] = 0x10;
    if (!setjmp(fault_jb))
        gate(-36, &r);
    CHECK(faults == 1, "a refused range faults (%d)", faults);
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
        memset(&c, 0, sizeof c);
        c.rt = &rt; c.sysbase = SYSBASE;
        gf_gaddr a = gf_alloc_vec(&c, 100, GF_MEMF_ANY);
        CHECK(a >= RAM_BASE && allocs == 1, "AllocVec through exec's table");
        gf_free_vec(&c, a);
        CHECK(allocs == 0, "FreeVec");
    }
    printf("gfoslib: module %s %s, %d checks, %d failed\n", GFOS_CPU == 62 ? "x86-64" : GFOS_CPU == 183 ? "ARM64" :
           GFOS_CPU == 20 ? "PPC" : "68k", on(gfmod_header.order), checks, fails);
    return fails != 0;
}
