#ifndef GADGETS_VIRTUAL_H
#define GADGETS_VIRTUAL_H
/*
 * OpenNDK: virtual.gadget, a scrolling view onto a layout larger than itself.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif
#ifndef GADGETS_LAYOUT_H
#include <gadgets/layout.h>
#endif

#define VIRTUALA_Dummy		(REACTION_Dummy + 0x2B000)

#define VIRTUALA_Contents	0x85024500	/* Object *: the layout inside */
#define VIRTUALA_Scroller	0x85024501	/* which scrollers it has */

/* More names from the 3.2 interface */
#define VIRTUALA_Base		0x85024500UL
#define VIRTUALA_InputScroll	(VIRTUALA_Base + 12)
#define VIRTUALA_MapX		(VIRTUALA_Base + 16)
#define VIRTUALA_MapY		(VIRTUALA_Base + 17)
#define VIRTUALA_NoDispose	(VIRTUALA_Base + 13)
#define VIRTUALA_ScrollX	(VIRTUALA_Base + 2)
#define VIRTUALA_ScrollY	(VIRTUALA_Base + 3)
#define VIRTUALA_ScrollerX	(VIRTUALA_Base + 10)
#define VIRTUALA_ScrollerY	(VIRTUALA_Base + 11)
#define VIRTUALA_TargetX	(VIRTUALA_Base + 14)
#define VIRTUALA_TargetY	(VIRTUALA_Base + 15)
#define VIRTUALA_TopX		(VIRTUALA_Base + 6)
#define VIRTUALA_TopY		(VIRTUALA_Base + 7)
#define VIRTUALA_TotalX		(VIRTUALA_Base + 8)
#define VIRTUALA_TotalY		(VIRTUALA_Base + 9)
#define VIRTUALA_VisibleX	(VIRTUALA_Base + 4)
#define VIRTUALA_VisibleY	(VIRTUALA_Base + 5)

#endif /* GADGETS_VIRTUAL_H */
