/* gfoslib's host test library: the functions that touch caller memory,
 * written once and compiled once per GF_SWAP_IN/GF_SWAP_OUT pair (run.sh). */
#include "test_gfoslib_lib.h"

uint32_t GF_VARIANT(tst_swizzle)(struct gf_call *c, gf_gaddr og)
{
    void *g = gf_ptr_w(c, og, sizeof(struct tst_outer_g));
    struct tst_outer_n n;
    const uint8_t *b;
    uint32_t i, sum;
    __builtin_memset(&n, 0, sizeof n);
    gf_struct_in(&tst_outer_table, &n, g, GF_SWAP_IN);   /* once, at the gate */
    n.count += 1;
    n.inner.a ^= 0xA5A5A5A5u;
    n.inner.b = (uint16_t)(n.inner.b + 0x0102);
    n.inner.c ^= 0xff;
    b = (const uint8_t *)gf_ptr_r(c, n.buf, n.count);
    sum = n.kind + n.inner.a + n.inner.d;
    for (i = 0; i < n.count; i++)                         /* plain C on the copy */
        sum += b[i] * (i + 1);
    n.sum = sum;
    gf_struct_out(&tst_outer_table, g, &n, GF_SWAP_OUT);
    return n.count;
}

/* buf[0] is a seed in the "in" order; the call writes seed + i * step at
 * buf[i] for i below n, then a word, a quad and a float after them, all in
 * the "out" order */
uint32_t GF_VARIANT(tst_fill)(struct gf_call *c, gf_gaddr buf, uint32_t n, uint32_t step)
{
    uint8_t *p = (uint8_t *)gf_ptr_w(c, buf, n * 4 + 2 + 8 + 4);
    const uint32_t seed = GF_GET32(p);
    uint32_t i;
    for (i = 0; i < n; i++)
        GF_PUT32(p + 4 * i, seed + i * step);
    p += 4 * n;
    GF_PUT16(p, seed & 0xffff);
    GF_PUT64(p + 2, (uint64_t)seed * 0x100000001ull + step);
    GF_PUTF(p + 10, (float)seed * 0.5f);
    return seed;
}
