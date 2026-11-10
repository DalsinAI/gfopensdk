/* The Open SDK's AROS compatibility: AROS's <proto/alib.h> is the OS's
 * amiga.lib calls plus a few AROS adds (__sprintf, StrDup, DoSuperNewTags), which libaroscompat.a gives.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef AROSCOMPAT_PROTO_ALIB_H
#define AROSCOMPAT_PROTO_ALIB_H
#include_next <proto/alib.h>
#include <exec/types.h>
#include <utility/tagitem.h>
#include <intuition/classusr.h>

/* exec's RawDoFmt formats (%ld for 32 bits, %s, %lx, %b), into buf. Returns buf. */
STRPTR __sprintf(UBYTE *buf, const UBYTE *fmt, ...);

/* a copy of str in AllocVec memory (FreeVec frees it) */
STRPTR StrDup(CONST_STRPTR str);
/* OM_NEW to cl's superclass with the tags that follow (TAG_DONE ends them) */
IPTR DoSuperNewTags(struct IClass *cl, Object *obj, APTR gadgetinfo, Tag tag1, ...);

#endif
