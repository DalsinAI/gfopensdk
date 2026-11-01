#ifndef GADGETS_SPACE_H
#define GADGETS_SPACE_H
/*
 * OpenNDK: space.gadget, an empty area for layouts or the program's own drawing.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define SPACE_Dummy		(REACTION_Dummy + 0x9000)

#define SPACE_MinHeight		(SPACE_Dummy + 1)
#define SPACE_MinWidth		(SPACE_Dummy + 2)
#define SPACE_MouseX		(SPACE_Dummy + 3)	/* (get) where it was clicked */
#define SPACE_MouseY		(SPACE_Dummy + 4)
#define SPACE_Transparent	(SPACE_Dummy + 5)	/* BOOL: not cleared before drawing */
#define SPACE_AreaBox		(SPACE_Dummy + 6)	/* (get) struct IBox *: the inside */
#define SPACE_RenderHook	(SPACE_Dummy + 7)	/* struct Hook *: the program draws */
#define SPACE_BevelStyle	(SPACE_Dummy + 8)	/* BVS_ from images/bevel.h */

/* More names from the 3.2 interface */
#define SPACE_DomainBevel	(SPACE_Dummy + 9)
#define SPACE_RenderBox		(SPACE_Dummy + 10)

#endif /* GADGETS_SPACE_H */
