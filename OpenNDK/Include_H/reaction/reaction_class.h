#ifndef REACTION_REACTION_CLASS_H
#define REACTION_REACTION_CLASS_H
/*
 * OpenNDK: what ReAction classes share: GM_CLIPRECT and its message.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif
#ifndef INTUITION_CGHOOKS_H
#include <intuition/cghooks.h>
#endif

/* GM_CLIPRECT's message */
struct gpClipRect
{
	ULONG	MethodID;
	struct GadgetInfo *gpc_GInfo;
	struct Rectangle *gpc_ClipRect;
	ULONG	gpc_Flags;
};

/* More names from the 3.2 interface */
#define GMC_INVISIBLE		0
#define GMC_PARTIAL		1
#define GMC_VISIBLE		2
#define GM_CLIPRECT		0x550001

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef INTUITION_CGHOOKS_H
#include <intuition/cghooks.h>
#endif

#endif /* REACTION_REACTION_CLASS_H */
