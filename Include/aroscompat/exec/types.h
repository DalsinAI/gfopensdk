/* The Open SDK's AROS compatibility: <exec/types.h> as AROS programs use
 * it. The OS's own header (OpenNDK's or the NDK's), then AROS's types:
 * IPTR and SIPTR (integers the size of a pointer), STACKED (nothing on
 * m68k), BNULL, RAWARG, AROS's 64-bit names, ADATE, and the calling macros
 * (aros/asmcall.h, aros/libcall.h), which AROS's exec/types.h brings in. Put Include/aroscompat before the
 * OS's headers (Docs/PORTING-AROS.md). MIT, Copyright (c) 2026 AmiCradle Team. */
#include_next <exec/types.h>

#ifndef AROSCOMPAT_EXEC_TYPES_H
#define AROSCOMPAT_EXEC_TYPES_H
/* the OS's own ULONG/LONG, so a program's own `typedef ULONG IPTR;` (MorphOS and
   OS 3 builds of AROS programs have one) is the same type, not a clash */
typedef ULONG IPTR;
typedef LONG SIPTR;
#ifndef STACKED
#define STACKED
#endif
#ifndef BNULL
#define BNULL ((BPTR)0)
#endif
#ifndef __QUAD_DEFINED
#define __QUAD_DEFINED
typedef long long QUAD;
typedef unsigned long long UQUAD;
#endif
/* RawDoFmt's argument stream, as AROS names it */
typedef APTR RAWARG;
#ifndef STACKIPTR
#define STACKIPTR IPTR
#endif
#ifndef STACKULONG
#define STACKULONG ULONG
#define STACKLONG LONG
#define STACKWORD LONG
#define STACKUWORD ULONG
#define STACKBYTE LONG
#define STACKUBYTE ULONG
#endif
/* the build date AROS's build passes ($VER strings) */
#ifndef ADATE
#define ADATE "(" __DATE__ ")"
#endif
/* AROS's own startup section: a program that names one is built without
 * libnix's startup (Docs/PORTING-AROS.md) */
#ifndef __startup
#define __startup
#endif
#endif
#ifndef __AC_NO_CALL_MACROS
/* AROS's exec/types.h brings these in */
#include <aros/asmcall.h>
#include <aros/libcall.h>
#endif
