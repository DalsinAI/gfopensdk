/* Copyright (c) 2026 AmiCradle Team. MIT licence (see LICENSE at the repository root).
 * GFOpenExec's atomic calls, for programs and libraries: compare-and-swap, add, or and and on a long, and
 * compare-and-swap on two longs, safe against interrupts and across cores (GFOpenMulticore, the cores board's
 * task cores). libraries/openexec/README.md, "Atomic calls", is the design; exec.lvo has the slots.
 *
 *   AtomicCAS(p, cmp, new)    -834  a0 d0 d1      d0 = *p before; *p = new only if it was cmp
 *   AtomicAdd(p, value)       -840  a0 d0         d0 = *p before; *p += value
 *   AtomicOr(p, mask)         -846  a0 d0         d0 = *p before; *p |= mask
 *   AtomicAnd(p, mask)        -852  a0 d0         d0 = *p before; *p &= mask
 *   AtomicCAS2(p1, p2, c1, c2, n1, n2)
 *                             -858  a0 a1 d0 d1 d2 d3
 *                                                 d0 = 1 if *p1 == c1 and *p2 == c2, and then *p1 = n1 and
 *                                                 *p2 = n2 as one access; 0 if not, and nothing changed
 *
 * Every call keeps every register but d0, may be called from an interrupt, and is atomic against
 * interrupts and other cores. Longs aligned to 4 bytes, and not in chip RAM on a real Amiga (the chip bus
 * does not do locked read-modify-write cycles). On a 68060 CAS2 traps to 68060.library's emulation.
 *
 * The calls are GFOpenExec's own, in slots OS 3.2's exec keeps private: on any other exec those slots do
 * something else. GFOpenExecAtomics() says whether they are there: an exec whose IdString names GFOpenExec,
 * and whose AtomicCAS answers as it should (a GFOpenExec from before the calls answers 0 there). Check once,
 * at start-up, and keep a fallback (Disable()/Enable() round the plain operation, on one core) for false.
 */
#ifndef GFOPENEXEC_ATOMIC_H
#define GFOPENEXEC_ATOMIC_H

#include <exec/types.h>
#include <exec/execbase.h>

extern struct ExecBase *SysBase;

static inline ULONG AtomicCAS(volatile ULONG *p, ULONG cmp, ULONG nv)
{
    register ULONG d0 __asm("d0") = cmp;
    register ULONG d1 __asm("d1") = nv;
    register volatile ULONG *a0 __asm("a0") = p;
    register struct ExecBase *a6 __asm("a6") = SysBase;
    __asm volatile("jsr -834(%%a6)" : "+r"(d0), "+r"(d1), "+r"(a0) : "r"(a6) : "a1", "cc", "memory");
    return d0;
}

#define GFOPENEXEC_ATOMIC_OP(name, lvo)                                                                 \
    static inline ULONG name(volatile ULONG *p, ULONG v)                                                \
    {                                                                                                   \
        register ULONG d0 __asm("d0") = v;                                                              \
        register volatile ULONG *a0 __asm("a0") = p;                                                    \
        register struct ExecBase *a6 __asm("a6") = SysBase;                                             \
        __asm volatile("jsr " #lvo "(%%a6)" : "+r"(d0), "+r"(a0) : "r"(a6) : "d1", "a1", "cc", "memory"); \
        return d0;                                                                                      \
    }
GFOPENEXEC_ATOMIC_OP(AtomicAdd, -840)
GFOPENEXEC_ATOMIC_OP(AtomicOr, -846)
GFOPENEXEC_ATOMIC_OP(AtomicAnd, -852)
#undef GFOPENEXEC_ATOMIC_OP

static inline BOOL AtomicCAS2(volatile ULONG *p1, volatile ULONG *p2, ULONG c1, ULONG c2, ULONG n1, ULONG n2)
{
    register ULONG d0 __asm("d0") = c1;
    register ULONG d1 __asm("d1") = c2;
    register ULONG d2 __asm("d2") = n1;
    register ULONG d3 __asm("d3") = n2;
    register volatile ULONG *a0 __asm("a0") = p1;
    register volatile ULONG *a1 __asm("a1") = p2;
    register struct ExecBase *a6 __asm("a6") = SysBase;
    __asm volatile("jsr -858(%%a6)" : "+r"(d0), "+r"(d1), "+r"(a0), "+r"(a1) : "r"(d2), "r"(d3), "r"(a6)
                   : "cc", "memory");
    return (BOOL)(d0 != 0);
}

static inline BOOL GFOpenExecAtomics(void)
{
    const char *id = (const char *)SysBase->LibNode.lib_IdString, *k = "GFOpenExec";
    volatile ULONG probe = 5;
    int i, j;
    if (!id) return FALSE;
    for (i = 0; id[i]; i++) {
        for (j = 0; k[j] && id[i + j] == k[j]; j++) {}
        if (!k[j]) return AtomicCAS(&probe, 5, 7) == 5 && probe == 7;
    }
    return FALSE;
}

#endif
