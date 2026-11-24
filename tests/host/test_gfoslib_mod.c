/* gfoslib's host test library: the module's own calls, behind the gate
 * entries tools/gfmodgen.py makes from test_gfoslib.lvo (tstmod.c). */
#include "tstmod.h"
#include "test_gfoslib_lib.h"

static const struct gf_field inner_f[] = {
    GF_FLD(struct tst_inner_g, struct tst_inner_n, a, GF_K_U32, GF_F_INOUT),
    GF_FLD(struct tst_inner_g, struct tst_inner_n, b, GF_K_U16, GF_F_INOUT),
    GF_FLD(struct tst_inner_g, struct tst_inner_n, c, GF_K_U8, GF_F_INOUT),
    GF_FLD(struct tst_inner_g, struct tst_inner_n, d, GF_K_U8, GF_F_INOUT),
};
const struct gf_table tst_inner_table = GF_TABLE(tst_inner, struct tst_inner_g, struct tst_inner_n, inner_f);
static const struct gf_field outer_f[] = {
    GF_FLD(struct tst_outer_g, struct tst_outer_n, kind, GF_K_U16, GF_F_IN),
    GF_FLD(struct tst_outer_g, struct tst_outer_n, count, GF_K_U32, GF_F_INOUT),
    GF_FLDS(struct tst_outer_g, struct tst_outer_n, inner, tst_inner_table, GF_F_INOUT),
    GF_FLD(struct tst_outer_g, struct tst_outer_n, buf, GF_K_GPTR, GF_F_IN),
    GF_FLD(struct tst_outer_g, struct tst_outer_n, sum, GF_K_U32, GF_F_OUT),
};
const struct gf_table tst_outer_table = GF_TABLE(tst_outer, struct tst_outer_g, struct tst_outer_n, outer_f);
const struct gf_table *const tst_tables[] = { &tst_outer_table, &tst_inner_table };

typedef uint32_t swz_fn(struct gf_call *, gf_gaddr);
typedef uint32_t fill_fn(struct gf_call *, gf_gaddr, uint32_t, uint32_t);
static swz_fn *const swz[4] = { tst_swizzle_v00, tst_swizzle_v01, tst_swizzle_v10, tst_swizzle_v11 };
static fill_fn *const fill[4] = { tst_fill_v00, tst_fill_v01, tst_fill_v10, tst_fill_v11 };

uint32_t tm_TstAdd(struct gf_call *c, uint32_t d0, uint32_t d1) { (void)c; return d0 + d1; }
uint32_t tm_TstSwizzle(struct gf_call *c, uint32_t a0) { return swz[c->s->variant](c, a0); }
uint32_t tm_TstFill(struct gf_call *c, uint32_t a0, uint32_t d0, uint32_t d1)
{ return fill[c->s->variant](c, a0, d0, d1); }
uint32_t tm_TstHook(struct gf_call *c, uint32_t a0, uint32_t d0)
{
    uint32_t arg = d0;
    return c->rt->callc(c, a0, 1, &arg) * 2 + 1;
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
