#ifndef GADGETS_SKETCHBOARD_H
#define GADGETS_SKETCHBOARD_H
/*
 * OpenNDK: the sketchboard gadget class, a drawing surface.
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
#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif

/* A method that takes only the gadget's context */
struct spGeneral
{
	ULONG	MethodID;
	struct GadgetInfo GInfo;
};

/* Scrolling the drawing */
struct spScrollRaster
{
	ULONG	MethodID;
	struct GadgetInfo *GInfo;
	LONG	DeltaX;
	LONG	DeltaY;
};

/* More names from the 3.2 interface */
#define SKETCHBOARD_Dummy	0x85024600UL
#define SGA_APen		(SKETCHBOARD_Dummy + 5)
#define SGA_AfPt		(SKETCHBOARD_Dummy + 11)
#define SGA_AfPtSize		(SKETCHBOARD_Dummy + 12)
#define SGA_BitMap		(SKETCHBOARD_Dummy + 0)
#define SGA_Changed		(SKETCHBOARD_Dummy + 20)
#define SGA_DoubleScaleX	(SKETCHBOARD_Dummy + 25)
#define SGA_DoubleScaleY	(SKETCHBOARD_Dummy + 26)
#define SGA_HPropTop		(SKETCHBOARD_Dummy + 14)
#define SGA_HPropTotal		(SKETCHBOARD_Dummy + 13)
#define SGA_HPropVisible	(SKETCHBOARD_Dummy + 15)
#define SGA_Height		(SKETCHBOARD_Dummy + 4)
#define SGA_HotSpot		(SKETCHBOARD_Dummy + 19)
#define SGA_MaxScale		(SKETCHBOARD_Dummy + 33)
#define SGA_MaxUndoSteps	(SKETCHBOARD_Dummy + 31)
#define SGA_MouseX		(SKETCHBOARD_Dummy + 1)
#define SGA_MouseY		(SKETCHBOARD_Dummy + 2)
#define SGA_RastPort		(SKETCHBOARD_Dummy + 21)
#define SGA_RedoAvailable	(SKETCHBOARD_Dummy + 8)
#define SGA_Scale		(SKETCHBOARD_Dummy + 10)
#define SGA_ScrollWheelResponse	(SKETCHBOARD_Dummy + 30)
#define SGA_ShowGrid		(SKETCHBOARD_Dummy + 9)
#define SGA_SketchBoardRect	(SKETCHBOARD_Dummy + 22)
#define SGA_SubHeight		(SKETCHBOARD_Dummy + 24)
#define SGA_SubWidth		(SKETCHBOARD_Dummy + 23)
#define SGA_Tool		(SKETCHBOARD_Dummy + 6)
#define SGA_TopLayerBitmap	(SKETCHBOARD_Dummy + 27)
#define SGA_TopLayerWidth	(SKETCHBOARD_Dummy + 28)
#define SGA_UndoAvailable	(SKETCHBOARD_Dummy + 7)
#define SGA_UpdatedBitMap	(SKETCHBOARD_Dummy + 32)
#define SGA_VPropTop		(SKETCHBOARD_Dummy + 17)
#define SGA_VPropTotal		(SKETCHBOARD_Dummy + 16)
#define SGA_VPropVisible	(SKETCHBOARD_Dummy + 18)
#define SGA_Width		(SKETCHBOARD_Dummy + 3)
#define SGA_WithBevel		(SKETCHBOARD_Dummy + 29)
#define SGM_Clear		0x580100
#define SGM_Redo		0x580102
#define SGM_Scroll		0x580103
#define SGM_Undo		0x580101
#define SGSCROLLWHEEL_NOTHING	0
#define SGSCROLLWHEEL_SCROLLANDZOOM	1
#define SGSCROLLWHEEL_ZOOM	2
#define SGTOOL_ELLIPSE		2
#define SGTOOL_ELLIPSE_FILLED	3
#define SGTOOL_FILL		7
#define SGTOOL_FREEHAND		1
#define SGTOOL_FREEHAND_DOTS	0
#define SGTOOL_GETPEN		8
#define SGTOOL_HOTSPOT		9
#define SGTOOL_LINE		6
#define SGTOOL_MOVE		11
#define SGTOOL_RECT		4
#define SGTOOL_RECT_FILLED	5
#define SGTOOL_SELECT		10

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif

#endif /* GADGETS_SKETCHBOARD_H */
