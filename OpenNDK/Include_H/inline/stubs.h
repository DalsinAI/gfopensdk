#ifndef __INLINE_STUBS_H
#define __INLINE_STUBS_H
/*
 * OpenNDK: the headers whose types the GCC inline headers of other SDKs
 * (CyberGraphX, MUI, AHI and the like, written on <inline/macros.h>) use
 * in their prototypes without including them, as the GCC toolchains'
 * <inline/stubs.h> has always brought them in: lists, DOS, BOOPSI's
 * Object and classes, display IDs and commodities. <inline/macros.h>
 * includes this; OpenNDK's own inline headers need neither.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif
#ifndef INTUITION_CLASSES_H
#include <intuition/classes.h>
#endif
#ifndef GRAPHICS_DISPLAYINFO_H
#include <graphics/displayinfo.h>
#endif
#ifndef LIBRARIES_COMMODITIES_H
#include <libraries/commodities.h>
#endif

#endif /* __INLINE_STUBS_H */
