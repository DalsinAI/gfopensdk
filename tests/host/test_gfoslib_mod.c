/* gfoslib's host test library: the module's own calls, behind the gate
 * entries and field tables tools/gfmodgen.py makes from test_gfoslib.lvo and
 * test_gfoslib.fields (tstmod.c). */
#include "tstmod.h"
#include "test_gfoslib_lib.h"

typedef uint32_t swz_fn(struct gf_call *, gf_gaddr);
typedef uint32_t fill_fn(struct gf_call *, gf_gaddr, uint32_t, uint32_t);
static swz_fn *const swz[4] = { tst_swizzle_v00, tst_swizzle_v01, tst_swizzle_v10, tst_swizzle_v11 };
static fill_fn *const fill[4] = { tst_fill_v00, tst_fill_v01, tst_fill_v10, tst_fill_v11 };

/* as ADD.L: N and Z from the result, V and C from the addition, X as C */
uint32_t tm_TstAdd(struct gf_call *c, uint32_t d0, uint32_t d1, uint16_t *ccr)
{
    const uint32_t r = d0 + d1;
    const int carry = r < d0, over = (int)((~(d0 ^ d1) & (d0 ^ r)) >> 31);
    (void)c;
    *ccr = (uint16_t)((carry ? 0x11 : 0) | (r >> 31 ? 0x08 : 0) | (r ? 0 : 0x04) | (over ? 0x02 : 0));
    return r;
}
uint32_t tm_TstSwizzle(struct gf_call *c, uint32_t a0) { return swz[c->s->variant](c, a0); }
uint32_t tm_TstFill(struct gf_call *c, uint32_t a0, uint32_t d0, uint32_t d1)
{ return fill[c->s->variant](c, a0, d0, d1); }
uint32_t tm_TstHook(struct gf_call *c, uint32_t a0, uint32_t d0)
{
    uint32_t arg = d0;
    return c->rt->callc(c, a0, 1, &arg) * 2 + 1;
}
uint32_t tm_TstDivMod(struct gf_call *c, uint32_t d0, uint32_t d1, uint32_t *rem)
{
    (void)c;
    if (!d1) { *rem = d0; return 0xffffffffu; }
    *rem = d0 % d1;
    return d0 / d1;
}

uint32_t tm_LibOpen(struct gf_call *c)
{
    uint8_t *b = (uint8_t *)gf_ptr_w(c, c->r.a[6], GF_LIB_SIZE);
    GF_BE_PUT16(b + GF_LIB_OPENCNT, GF_BE_GET16(b + GF_LIB_OPENCNT) + 1);
    b[GF_LIB_FLAGS] &= (uint8_t)~GF_LIBF_DELEXP;
    return c->r.a[6];
}
uint32_t tm_LibClose(struct gf_call *c)
{
    uint8_t *b = (uint8_t *)gf_ptr_w(c, c->r.a[6], GF_LIB_SIZE);
    uint16_t n = GF_BE_GET16(b + GF_LIB_OPENCNT);
    if (n)
        GF_BE_PUT16(b + GF_LIB_OPENCNT, n - 1);
    return 0;
}
uint32_t tm_LibExpunge(struct gf_call *c) { (void)c; return 0; }
uint32_t tm_Init(struct gf_call *c) { (void)c; return 0; }
void tm_Fini(struct gf_call *c) { (void)c; }
