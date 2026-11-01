#ifndef GADGETS_SCROLLER_H
#define GADGETS_SCROLLER_H
/*
 * OpenNDK: scroller.gadget, a proportional scroller with optional arrows.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define SCROLLER_Dummy		(REACTION_Dummy + 0x0005000)

#define SCROLLER_Top		(SCROLLER_Dummy + 0x0001)	/* the first visible unit */
#define SCROLLER_Visible	(SCROLLER_Dummy + 0x0002)	/* units in view */
#define SCROLLER_Total		(SCROLLER_Dummy + 0x0003)	/* units in all */
#define SCROLLER_Orientation	(SCROLLER_Dummy + 0x0004)	/* SORIENT_ below */
#define SCROLLER_Arrows		(SCROLLER_Dummy + 0x0005)	/* BOOL */
#define SCROLLER_Stretch	(SCROLLER_Dummy + 0x0006)
#define SCROLLER_ArrowDelta	(SCROLLER_Dummy + 0x0007)	/* units an arrow click moves */

/* The same values as propgclass's FREEHORIZ and FREEVERT */
#define SORIENT_HORIZ	0x0002
#define SORIENT_VERT	0x0004

/* More names from the 3.2 interface */
#define SCROLLER_HORIZONTAL	2
#define SCROLLER_SignalTask	(SCROLLER_Dummy + 10)
#define SCROLLER_SignalTaskBit	(SCROLLER_Dummy + 11)
#define SCROLLER_VERTICAL	4

#endif /* GADGETS_SCROLLER_H */
