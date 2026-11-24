/* gfoslib's host test library: its shared structures (tests/host/test_gfoslib.c) */
#ifndef TEST_GFOSLIB_LIB_H
#define TEST_GFOSLIB_LIB_H
#include "gfos/gfoslib.h"

/* as the 68k lays them out */
struct tst_inner_g { uint32_t a; uint16_t b; uint8_t c, d; } GF_SHARED;
struct tst_outer_g {
    uint16_t kind, pad;
    uint32_t count;
    struct tst_inner_g inner;
    gf_gaddr buf;
    uint32_t sum;
} GF_SHARED;
GF_SIZE(struct tst_inner_g, 8);
GF_SIZE(struct tst_outer_g, 24);
GF_LAYOUT(struct tst_outer_g, inner, 8);
GF_LAYOUT(struct tst_outer_g, buf, 16);

/* the module's native copies */
struct tst_inner_n { uint32_t a; uint16_t b; uint8_t c, d; };
struct tst_outer_n { uint16_t kind; uint32_t count; struct tst_inner_n inner; gf_gaddr buf; uint32_t sum; };

extern const struct gf_table tst_inner_table, tst_outer_table;
extern const struct gf_table *const tst_tables[];

/* the four copies of each function that touches caller memory */
#define TST_DECL(fn, ...) \
    uint32_t fn##_v00(__VA_ARGS__); uint32_t fn##_v01(__VA_ARGS__); \
    uint32_t fn##_v10(__VA_ARGS__); uint32_t fn##_v11(__VA_ARGS__);
TST_DECL(tst_swizzle, struct gf_call *c, gf_gaddr outer)
TST_DECL(tst_fill, struct gf_call *c, gf_gaddr buf, uint32_t n, uint32_t step)
#endif
