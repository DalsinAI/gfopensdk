#ifndef GADGETS_PALETTE_H
#define GADGETS_PALETTE_H
/*
 * OpenNDK: palette.gadget, a grid of colours to pick one from.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define PALETTE_Dummy		(REACTION_Dummy + 0x4000)

#define PALETTE_Colour		(PALETTE_Dummy + 1)	/* the chosen pen */
#define PALETTE_ColourOffset	(PALETTE_Dummy + 2)	/* the first pen shown */
#define PALETTE_ColourTable	(PALETTE_Dummy + 3)	/* UBYTE *: the pens shown */
#define PALETTE_NumColours	(PALETTE_Dummy + 4)

/* More names from the 3.2 interface */
#define PALETTE_Color		(PALETTE_Dummy + 1)
#define PALETTE_ColorOffset	(PALETTE_Dummy + 2)
#define PALETTE_ColorTable	(PALETTE_Dummy + 3)
#define PALETTE_MinColours	(PALETTE_Dummy + 5)
#define PALETTE_NumColors	(PALETTE_Dummy + 4)
#define PALETTE_RenderHook	(PALETTE_Dummy + 7)
#define PBCB_OK			0
#define PBCB_UNKNOWN		1
#define PBR_NORMAL		0
#define PBR_NORMALDISABLED	2
#define PBR_SELECTED		1
#define PBR_SELECTEDDISABLED	8
#define PB_DRAW			0x202

#endif /* GADGETS_PALETTE_H */
