/* The Open SDK's AROS compatibility: AROS's <proto/alib.h> is the OS's
 * amiga.lib calls plus a few AROS adds (__sprintf), which libaroscompat.a gives.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef AROSCOMPAT_PROTO_ALIB_H
#define AROSCOMPAT_PROTO_ALIB_H
#include_next <proto/alib.h>
#include <exec/types.h>

/* exec's RawDoFmt formats (%ld for 32 bits, %s, %lx, %b), into buf. Returns buf. */
STRPTR __sprintf(UBYTE *buf, const UBYTE *fmt, ...);

#endif
