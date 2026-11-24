/* Copyright (c) 2026 AmiCradle Team. MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * gfoslib (GF-126): one library source builds every CPU's module:
 * name.module (68k), name.module.x86, name.module.arm64, name.module.ppc.
 * The design is amicradle-guest docs/design/Native-Modules-ABI.md
 * (GF-91), sections 4 to 8 and 12.
 *
 * Build switches
 *   GFOS_CPU           GFOS_CPU_68K (4), GFOS_CPU_X86 (62), GFOS_CPU_ARM64
 *                      (183), GFOS_CPU_PPC (20): ELF e_machine numbers, as
 *                      od_HostCPU answers. Worked out from the compiler
 *                      when the build does not set it.
 *   GFOS_NATIVE_ORDER  GFOS_BE or GFOS_LE. Checked against the compiler's
 *                      __BYTE_ORDER__: a build that says otherwise stops.
 *   GF_SWAP_IN         1 when this copy of a function reads caller data in
 *   GF_SWAP_OUT        the other byte order, or writes it back in the other
 *                      order. Each is 0 or 1; a native module compiles the
 *                      functions that touch caller memory once per pair it
 *                      serves (GF_VARIANT names them), and a session picks
 *                      its copy at open (gf_variant). A 68k build is always
 *                      BE to BE: both must be 0 there.
 *
 * Accessors: GF_GET8/16/32/64/F/D read caller memory in the session's "in"
 * order, GF_PUT8/16/32/64/F/D write it in the "out" order. With the swap
 * switch 0 they are plain loads and stores; with 1, one byte swap. No branch
 * is left in either copy.
 *
 * Field tables describe a structure the 68k shares with a library, as the
 * 68k lays it out (big-endian, 16- and 32-bit members at even offsets), and
 * the native copy of it. tools/gfmodgen.py generates them from a .fields
 * file, together with the 68k side's record of the same shapes (its GFSG
 * record), so both sides' layout signatures come from one description.
 * gf_struct_in/gf_struct_out convert one at the gate, once a call, never in
 * a module's inner loop.
 */
#ifndef GFOS_GFOSLIB_H
#define GFOS_GFOSLIB_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- CPU and byte order --------------------------------------------- */

#define GFOS_CPU_68K   4
#define GFOS_CPU_PPC   20
#define GFOS_CPU_X86   62
#define GFOS_CPU_ARM64 183

#define GFOS_BE 1
#define GFOS_LE 2

#ifndef GFOS_CPU
#if defined(__m68k__) || defined(__mc68000__)
#define GFOS_CPU GFOS_CPU_68K
#elif defined(__x86_64__)
#define GFOS_CPU GFOS_CPU_X86
#elif defined(__aarch64__)
#define GFOS_CPU GFOS_CPU_ARM64
#elif defined(__powerpc__) || defined(__PPC__)
#define GFOS_CPU GFOS_CPU_PPC
#else
#error "gfoslib: set GFOS_CPU for this target"
#endif
#endif

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define GFOS_COMPILER_ORDER GFOS_BE
#elif defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define GFOS_COMPILER_ORDER GFOS_LE
#else
#error "gfoslib: the compiler does not say its byte order"
#endif

#ifndef GFOS_NATIVE_ORDER
#define GFOS_NATIVE_ORDER GFOS_COMPILER_ORDER
#elif GFOS_NATIVE_ORDER != GFOS_COMPILER_ORDER
#error "gfoslib: GFOS_NATIVE_ORDER is not this compiler's byte order"
#endif

#ifndef GF_SWAP_IN
#define GF_SWAP_IN 0
#endif
#ifndef GF_SWAP_OUT
#define GF_SWAP_OUT 0
#endif
#if GFOS_CPU == GFOS_CPU_68K && (GF_SWAP_IN || GF_SWAP_OUT)
#error "gfoslib: a 68k build is always BE to BE; it holds no conversion code"
#endif

/* The name of this copy of a function: fn_v00, fn_v01, fn_v10, fn_v11
 * (GF_SWAP_IN then GF_SWAP_OUT). */
#define GF_VCAT_(a, b, c) a##_v##b##c
#define GF_VCAT(a, b, c) GF_VCAT_(a, b, c)
#define GF_VARIANT(fn) GF_VCAT(fn, GF_SWAP_IN, GF_SWAP_OUT)
/* index of a copy in a four-entry table: in * 2 + out */
#define GF_VINDEX(swap_in, swap_out) ((unsigned)(!!(swap_in)) * 2u + (unsigned)(!!(swap_out)))

/* ---- loads, stores, swaps --------------------------------------------- */

#define GF_BSWAP16(x) ((uint16_t)__builtin_bswap16((uint16_t)(x)))
#define GF_BSWAP32(x) ((uint32_t)__builtin_bswap32((uint32_t)(x)))
#define GF_BSWAP64(x) ((uint64_t)__builtin_bswap64((uint64_t)(x)))

/* memcpy-sized loads: one instruction on x86-64 and ARM64, any alignment */
static inline uint16_t gf_ld16(const void *p) { uint16_t v; __builtin_memcpy(&v, p, 2); return v; }
static inline uint32_t gf_ld32(const void *p) { uint32_t v; __builtin_memcpy(&v, p, 4); return v; }
static inline uint64_t gf_ld64(const void *p) { uint64_t v; __builtin_memcpy(&v, p, 8); return v; }
static inline void gf_st16(void *p, uint16_t v) { __builtin_memcpy(p, &v, 2); }
static inline void gf_st32(void *p, uint32_t v) { __builtin_memcpy(p, &v, 4); }
static inline void gf_st64(void *p, uint64_t v) { __builtin_memcpy(p, &v, 8); }
static inline float gf_u2f(uint32_t u) { float f; __builtin_memcpy(&f, &u, 4); return f; }
static inline uint32_t gf_f2u(float f) { uint32_t u; __builtin_memcpy(&u, &f, 4); return u; }
static inline double gf_u2d(uint64_t u) { double d; __builtin_memcpy(&d, &u, 8); return d; }
static inline uint64_t gf_d2u(double d) { uint64_t u; __builtin_memcpy(&u, &d, 8); return u; }

/* a load or store in a stated order, whatever this copy's switches are */
#define GF_SW16(s, x) ((s) ? GF_BSWAP16(x) : (uint16_t)(x))
#define GF_SW32(s, x) ((s) ? GF_BSWAP32(x) : (uint32_t)(x))
#define GF_SW64(s, x) ((s) ? GF_BSWAP64(x) : (uint64_t)(x))

#define GF_GET8(p)  (*(const uint8_t *)(p))
#define GF_GET16(p) GF_SW16(GF_SWAP_IN, gf_ld16(p))
#define GF_GET32(p) GF_SW32(GF_SWAP_IN, gf_ld32(p))
#define GF_GET64(p) GF_SW64(GF_SWAP_IN, gf_ld64(p))
#define GF_GETF(p)  gf_u2f(GF_GET32(p))
#define GF_GETD(p)  gf_u2d(GF_GET64(p))
#define GF_PUT8(p, v)  (*(uint8_t *)(p) = (uint8_t)(v))
#define GF_PUT16(p, v) gf_st16((p), GF_SW16(GF_SWAP_OUT, (uint16_t)(v)))
#define GF_PUT32(p, v) gf_st32((p), GF_SW32(GF_SWAP_OUT, (uint32_t)(v)))
#define GF_PUT64(p, v) gf_st64((p), GF_SW64(GF_SWAP_OUT, (uint64_t)(v)))
#define GF_PUTF(p, v)  GF_PUT32((p), gf_f2u(v))
#define GF_PUTD(p, v)  GF_PUT64((p), gf_d2u(v))

/* Guest memory as the 68k reads it, whatever the session: always BE. For
 * the library base's public fields and exec's structures. */
#define GF_SWAP_BE (GFOS_NATIVE_ORDER != GFOS_BE)
#define GF_BE_GET16(p) GF_SW16(GF_SWAP_BE, gf_ld16(p))
#define GF_BE_GET32(p) GF_SW32(GF_SWAP_BE, gf_ld32(p))
#define GF_BE_PUT16(p, v) gf_st16((p), GF_SW16(GF_SWAP_BE, (uint16_t)(v)))
#define GF_BE_PUT32(p, v) gf_st32((p), GF_SW32(GF_SWAP_BE, (uint32_t)(v)))

/* ---- guest addresses, the call frame, the runtime ------------------- */

typedef uint32_t gf_gaddr;          /* a 32-bit guest address: never a host pointer */

struct gf_regs {
    uint32_t d[8], a[8];            /* a[7] is the 68k stack pointer */
    uint16_t sr;                    /* the low five bits are the CCR (X N Z V C) */
};

struct gf_call;

/* What a module may ask of the runtime: its only imports (section 11.1).
 * The runtime runs every call into a module on one emulation thread, one at
 * a time: a module needs no locks for its own lists (Native-Modules-ABI.md
 * 4.7); two calls interleave only across a call-out. */
struct gf_rt {
    uint32_t abi;                   /* GF_GATE_ABI */
    /* a host pointer to n bytes at a guest address, checked once (5.2); NULL
     * when the range is refused. write != 0 also tells the JIT it is written */
    void *(*ptr)(struct gf_call *c, gf_gaddr at, uint32_t n, int write);
    /* the guest address of a host pointer into guest memory, or 0 */
    gf_gaddr (*gaddr)(struct gf_call *c, const void *host);
    /* a 68k routine with these registers (6.1) */
    void (*call68k)(struct gf_call *c, gf_gaddr entry, const struct gf_regs *in, struct gf_regs *out);
    /* a 68k C function: nargs longs on the stack, the answer in D0 */
    uint32_t (*callc)(struct gf_call *c, gf_gaddr fn, uint32_t nargs, const uint32_t *args);
    /* a call through a 68k library's jump table (exec, dos): io in, D0/D1 out */
    void (*lib)(struct gf_call *c, gf_gaddr base, int16_t lvo, struct gf_regs *io);
    /* module-private host memory (7.2): never visible to the 68k */
    void *(*halloc)(struct gf_call *c, size_t n);
    void (*hfree)(struct gf_call *c, void *p);
    /* a fault in the module (6.5): log, Alert, the task stopped. Never
     * returns; call it through gf_fault, which says so to the compiler. */
    void (*fault)(struct gf_call *c, uint32_t code, gf_gaddr at);
};

#define GF_GATE_ABI 1

/* A session: one open, its byte order for each direction (12.2) */
struct gf_sess {
    uint8_t in, out;                /* GFOS_BE or GFOS_LE: the caller's */
    uint8_t variant;                /* GF_VINDEX for this module's order */
    uint8_t pad;
    gf_gaddr base;                  /* the base A6 holds for this session */
    void *data;                     /* the module's own, per session */
};

struct gf_mod;

struct gf_call {
    struct gf_regs r;               /* in: as the 68k left them; out: D0, D1, CCR */
    struct gf_sess *s;              /* from A6 */
    const struct gf_mod *m;
    const struct gf_rt *rt;
    gf_gaddr task;                  /* the calling task */
    gf_gaddr sysbase;               /* exec's base, for call-outs */
    void *mdata;                    /* the module's own, per loaded library */
};

typedef void gf_entry(struct gf_call *c);

__attribute__((noreturn)) static inline void gf_fault(struct gf_call *c, uint32_t code, gf_gaddr at)
{
    c->rt->fault(c, code, at);
    __builtin_trap();               /* a runtime whose fault returned */
}

/* ---- the module header (section 8) ---------------------------------- */

enum { GF_MARK_LIGHT = 0, GF_MARK_HEAVY = 1, GF_MARK_NATIVE_ONLY = 2 };
/* what the gate writes back besides D0 (gfmodgen --d1, --ccr) */
enum { GF_SLOT_D1 = 1, GF_SLOT_CCR = 2 };

struct gf_slot {
    int16_t lvo;                    /* -6, -12, ...: -6 * (slot + 1) */
    uint8_t mark;                   /* GF_MARK_* (4.6) */
    uint8_t flags;                  /* GF_SLOT_* */
    gf_entry *fn;
    const char *name;
};

struct gf_table;

struct gf_mod {
    char magic[4];                  /* "GFMD" */
    uint16_t gate_abi;              /* GF_GATE_ABI */
    uint16_t cpu;                   /* GFOS_CPU */
    uint8_t order;                  /* GFOS_NATIVE_ORDER */
    uint8_t pad[3];
    const char *name;               /* as the RomTag: "z.library" */
    uint16_t version, revision;
    uint16_t nslots;                /* reserved slots included */
    uint16_t possize;               /* the base's positive size, bytes */
    uint8_t lvo_sig[32];            /* SHA-256 of the normalised .lvo (gfmodgen.py) */
    uint16_t ntables;               /* the shared structures' field tables: the */
    const struct gf_table *const *tables; /* loader's layout_sig is gf_tables_sig over them */
    const struct gf_slot *slots;    /* nslots, slot 0 at -6 */
    /* once, when the library loads, after the base is made: 0 or a reason;
     * it may leave its per-library data in c->mdata, which the runtime
     * keeps and passes in every call */
    uint32_t (*init)(struct gf_call *c);
    /* once, when the library goes: frees what init and the calls kept */
    void (*fini)(struct gf_call *c);
};

#define GF_SECTION __attribute__((section(".gfmod"), used))

/* Why a module loses to its 68k body (8): 0 when it serves */
enum {
    GF_MATCH_OK = 0,
    GF_MATCH_MAGIC,                 /* not a module, or a gate this runtime lacks */
    GF_MATCH_CPU,                   /* another CPU's */
    GF_MATCH_ORDER,                 /* not this CPU's byte order */
    GF_MATCH_NAME,
    GF_MATCH_VERSION,               /* version or revision not the 68k body's */
    GF_MATCH_SLOTS,                 /* LVO count */
    GF_MATCH_SLOT_TABLE,            /* a slot out of place, without an entry, or marked wrong */
    GF_MATCH_POSSIZE,               /* the base's positive size is not the 68k body's */
    GF_MATCH_TABLES,                /* a field table that is not well formed */
    GF_MATCH_LVO_SIG,
    GF_MATCH_LAYOUT_SIG
};
/* What the 68k body says of itself: its RomTag (name, version, revision),
 * its base (lib_NegSize / 6, lib_PosSize) and its GFSG record (the LVO and
 * layout signatures, which gfmodgen writes from the same .lvo and .fields). */
struct gf_partner {
    const char *name;
    uint16_t version, revision, nslots, possize;
    const uint8_t *lvo_sig;         /* 32 bytes, or NULL: no record, no partner */
    uint64_t layout_sig;
};
int gf_mod_match(const struct gf_mod *m, const struct gf_partner *p, uint16_t host_cpu, uint8_t host_order);
const char *gf_match_reason(int why);

/* the 64-byte GFSG record (gfmodgen.py --record): all big-endian */
#define GF_GFSG_SIZE 64
enum { GF_GFSG_MAGIC = 0, GF_GFSG_VERSION = 4, GF_GFSG_NSLOTS = 6, GF_GFSG_LVO_SIG = 8,
       GF_GFSG_LAYOUT_SIG = 40, GF_GFSG_POSSIZE = 48 };
/* fills p's numbers and signatures from a record (name, version and revision
 * are the RomTag's); 0, or -1 when it is not one */
int gf_gfsg_read(const uint8_t rec[GF_GFSG_SIZE], struct gf_partner *p);

/* ---- field tables (12.4) -------------------------------------------- */

enum {
    GF_K_U8 = 1, GF_K_U16 = 2, GF_K_U32 = 4, GF_K_U64 = 8,
    GF_K_GPTR = 0x14,               /* a 32-bit guest address, kept as one */
    GF_K_BYTES = 0x20,              /* count opaque bytes, never converted */
    GF_K_NEST = 0x40                /* a nested structure: nest, count times */
};
enum { GF_F_IN = 1, GF_F_OUT = 2, GF_F_INOUT = 3 };

struct gf_field {
    uint16_t goff;                  /* offset in the 68k layout */
    uint16_t noff;                  /* offset in the native copy */
    uint8_t kind;                   /* GF_K_* */
    uint8_t flags;                  /* GF_F_*: a nested structure's fields keep their own */
    uint16_t count;                 /* array length (1 for one) */
    const struct gf_table *nest;    /* GF_K_NEST */
};
struct gf_table {
    const char *name;
    uint16_t gsize;                 /* the 68k layout's size */
    uint16_t nsize;                 /* the native copy's size */
    uint16_t nfields;
    const struct gf_field *f;
};

#define GF_FLD(gtype, ntype, member, kind, flags) \
    { (uint16_t)offsetof(gtype, member), (uint16_t)offsetof(ntype, member), (kind), (flags), 1, 0 }
#define GF_FLDN(gtype, ntype, member, kind, flags, n) \
    { (uint16_t)offsetof(gtype, member), (uint16_t)offsetof(ntype, member), (kind), (flags), (n), 0 }
#define GF_FLDS(gtype, ntype, member, table, flags) \
    { (uint16_t)offsetof(gtype, member), (uint16_t)offsetof(ntype, member), GF_K_NEST, (flags), 1, &(table) }
#define GF_TABLE(name, gtype, ntype, fields) \
    { #name, (uint16_t)sizeof(gtype), (uint16_t)sizeof(ntype), \
      (uint16_t)(sizeof(fields) / sizeof((fields)[0])), (fields) }

/* The 68k layout as a contract: static assertions in every build */
#ifdef __cplusplus
#define GF_SASSERT static_assert
#else
#define GF_SASSERT _Static_assert
#endif
#define GF_LAYOUT(type, member, off) \
    GF_SASSERT(offsetof(type, member) == (off), #type "." #member " is not at " #off)
#define GF_SIZE(type, n) GF_SASSERT(sizeof(type) == (n), #type " is not " #n " bytes")
/* a guest-layout struct: no padding of its own, 2-byte aligned as on the 68k */
#define GF_SHARED __attribute__((packed, aligned(2)))

/* 0 when a table is well formed: every field's kind known, inside both
 * layouts (offset + size * count), a nested table's sizes its own, at most
 * eight levels deep; else -1 */
int gf_table_check(const struct gf_table *t);
/* guest (caller's order) to native copy: the fields marked GF_F_IN, a nested
 * structure's by its own fields' marks; 0, or -1 for a table not well formed */
int gf_struct_in(const struct gf_table *t, void *native, const void *guest, int swap);
/* native copy to guest (caller's order): the fields marked GF_F_OUT */
int gf_struct_out(const struct gf_table *t, void *guest, const void *native, int swap);
/* FNV-1a 64 over the tables' 68k-side shapes: the module's layout_sig, and
 * what gfmodgen.py works out from the .fields file for the 68k side */
uint64_t gf_tables_sig(const struct gf_table *const *t, unsigned n);

/* ---- helpers a module calls -------------------------------------------- */

/* rt->ptr, a fault when refused: these never return NULL */
const void *gf_ptr_r(struct gf_call *c, gf_gaddr at, uint32_t n);
void *gf_ptr_w(struct gf_call *c, gf_gaddr at, uint32_t n);
gf_gaddr gf_gaddr_of(struct gf_call *c, const void *host);
/* n * each + extra, a fault when it does not fit in 32 bits: for sizes made
 * from a caller's numbers before a gf_ptr_r/w */
uint32_t gf_size(struct gf_call *c, uint32_t n, uint32_t each, uint32_t extra);

/* exec through its own jump table (6.1), so a SetFunction on it holds */
#define GF_LVO_ALLOCVEC (-684)
#define GF_LVO_FREEVEC  (-690)
#define GF_MEMF_ANY     0u
#define GF_MEMF_CLEAR   0x10000u
gf_gaddr gf_alloc_vec(struct gf_call *c, uint32_t size, uint32_t flags);
void gf_free_vec(struct gf_call *c, gf_gaddr mem);

/* a session's copy: which of the four a module of this order runs */
unsigned gf_variant(uint8_t caller_in, uint8_t caller_out, uint8_t module_order);

/* struct Library, as the 68k lays it out (exec/libraries.h) */
#define GF_LIB_FLAGS    14
#define GF_LIB_NEGSIZE  16
#define GF_LIB_POSSIZE  18
#define GF_LIB_VERSION  20
#define GF_LIB_REVISION 22
#define GF_LIB_IDSTRING 24
#define GF_LIB_OPENCNT  32
#define GF_LIB_SIZE     34
#define GF_LIBF_DELEXP  0x08

#ifdef __cplusplus
}
#endif
#endif
