#ifndef GADGETS_LAYOUT_H
#define GADGETS_LAYOUT_H
/*
 * OpenNDK: layout.gadget, the group that sizes and places ReAction
 * gadgets, and the page class that comes with it.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif
#ifndef IMAGES_BEVEL_H
#include <images/bevel.h>
#endif

#define LAYOUT_Dummy		(REACTION_Dummy + 0x7000)

#define LAYOUT_Orientation	(LAYOUT_Dummy + 1)	/* LAYOUT_ORIENT_ below */
#define LAYOUT_FixedHoriz	(LAYOUT_Dummy + 2)	/* BOOL: children keep their widths */
#define LAYOUT_FixedVert	(LAYOUT_Dummy + 3)
#define LAYOUT_HorizAlignment	(LAYOUT_Dummy + 4)	/* LALIGN_ below */
#define LAYOUT_VertAlignment	(LAYOUT_Dummy + 5)
#define LAYOUT_ShrinkWrap	(LAYOUT_Dummy + 6)	/* BOOL: no spare space */
#define LAYOUT_EvenSize		(LAYOUT_Dummy + 7)	/* BOOL: children the same size */
#define LAYOUT_InnerSpacing	(LAYOUT_Dummy + 9)	/* pixels between children */
#define LAYOUT_TopSpacing	(LAYOUT_Dummy + 10)	/* pixels inside the edges */
#define LAYOUT_BottomSpacing	(LAYOUT_Dummy + 11)
#define LAYOUT_LeftSpacing	(LAYOUT_Dummy + 12)
#define LAYOUT_RightSpacing	(LAYOUT_Dummy + 13)
#define LAYOUT_BevelState	(LAYOUT_Dummy + 14)	/* IDS_ state of the frame */
#define LAYOUT_BevelStyle	(LAYOUT_Dummy + 15)	/* BVS_ from images/bevel.h */
#define LAYOUT_Label		(LAYOUT_Dummy + 16)	/* STRPTR: the group's title */
#define LAYOUT_LabelImage	(LAYOUT_Dummy + 17)
#define LAYOUT_LabelPlace	(LAYOUT_Dummy + 18)	/* BVJ_ from images/bevel.h */
#define LAYOUT_RemoveChild	(LAYOUT_Dummy + 19)	/* Object * */
#define LAYOUT_AddChild		(LAYOUT_Dummy + 20)	/* Object *: a gadget */
#define LAYOUT_AddImage		(LAYOUT_Dummy + 21)	/* Object *: an image */
#define LAYOUT_ModifyChild	(LAYOUT_Dummy + 22)	/* Object *: CHILD_ tags that follow apply to it */
#define LAYOUT_RelVerify	(LAYOUT_Dummy + 23)
#define LAYOUT_RelCode		(LAYOUT_Dummy + 24)
#define LAYOUT_Parent		(LAYOUT_Dummy + 25)
#define LAYOUT_DeferLayout	(LAYOUT_Dummy + 26)	/* BOOL: lay out on the input task */
#define LAYOUT_RequestLayout	(LAYOUT_Dummy + 27)
#define LAYOUT_RequestRefresh	(LAYOUT_Dummy + 28)
#define LAYOUT_TextPen		(LAYOUT_Dummy + 29)
#define LAYOUT_FillPen		(LAYOUT_Dummy + 30)
#define LAYOUT_FillPattern	(LAYOUT_Dummy + 31)
#define LAYOUT_PageBackFill	(LAYOUT_Dummy + 32)
#define LAYOUT_BackFill		GA_BackFill
#define LAYOUT_TabVerify	(LAYOUT_Dummy + 33)
#define LAYOUT_LabelColumn	(LAYOUT_Dummy + 34)
#define LAYOUT_LabelWidth	(LAYOUT_Dummy + 35)
#define LAYOUT_AlignLabels	(LAYOUT_Dummy + 36)
#define LAYOUT_SpaceInner	(LAYOUT_Dummy + 37)	/* BOOL: the user's spacing between children */
#define LAYOUT_SpaceOuter	(LAYOUT_Dummy + 38)	/* BOOL: the user's spacing round them */
#define LAYOUT_RelAddress	(LAYOUT_Dummy + 39)
#define LAYOUT_HelpHit		(LAYOUT_Dummy + 40)
#define LAYOUT_HelpGadget	(LAYOUT_Dummy + 41)

/* Tags about the child added or modified just before */
#define CHILD_Dummy		(LAYOUT_Dummy + 0x100)

#define CHILD_MinWidth		(CHILD_Dummy + 1)
#define CHILD_MinHeight		(CHILD_Dummy + 2)
#define CHILD_MaxWidth		(CHILD_Dummy + 3)
#define CHILD_MaxHeight		(CHILD_Dummy + 4)
#define CHILD_WeightedWidth	(CHILD_Dummy + 5)	/* its share of spare width */
#define CHILD_WeightedHeight	(CHILD_Dummy + 6)
#define CHILD_ReplaceObject	(CHILD_Dummy + 7)	/* Object *: put this in its place */
#define CHILD_ReplaceImage	0x85007008
#define CHILD_CacheDomain	(CHILD_Dummy + 9)
#define CHILD_WeightMinimum	(CHILD_Dummy + 10)
#define CHILD_NominalSize	(CHILD_Dummy + 11)
#define CHILD_Label		(CHILD_Dummy + 12)	/* Object *: a label.image beside it */
#define CHILD_NoDispose		(CHILD_Dummy + 13)	/* BOOL: not disposed with the layout */
#define CHILD_ScaleHeight	(CHILD_Dummy + 14)	/* percent of the font's height */
#define CHILD_ScaleWidth	(CHILD_Dummy + 15)

/* LAYOUT_Orientation */
#define LAYOUT_ORIENT_HORIZ	0
#define LAYOUT_ORIENT_VERT	1

/* LAYOUT_HorizAlignment and LAYOUT_VertAlignment */
#define LALIGN_LEFT	0
#define LALIGN_RIGHT	1
#define LALIGN_CENTER	2
#define LALIGN_TOP	0
#define LALIGN_BOTTOM	1

/* The default spacing, in pixels */
#define INTERSPACING	1

/* Methods */
#define LM_ADDCHILD	0x540001
#define LM_ADDIMAGE	0x540002
#define LM_REMOVECHILD	0x540003
#define LM_MODIFYCHILD	0x540004

struct lmAddChild
{
	ULONG		MethodID;	/* LM_ADDCHILD or LM_ADDIMAGE */
	struct Window	*lm_Window;
	Object		*lm_Object;
	struct TagItem	*lm_ObjectAttrs;	/* CHILD_ tags */
};

struct lmRemoveChild
{
	ULONG		MethodID;	/* LM_REMOVECHILD */
	struct Window	*lm_Window;
	Object		*lm_Object;
};

struct lmModifyChild
{
	ULONG		MethodID;	/* LM_MODIFYCHILD */
	struct Window	*lm_Window;
	Object		*lm_Object;
	struct TagItem	*lm_ObjectAttrs;
};

/* LayoutLimits() fills this in */
struct LayoutLimits
{
	UWORD	MinWidth;
	UWORD	MinHeight;
	UWORD	MaxWidth;
	UWORD	MaxHeight;
};

/* The page class (PAGE_GetClass()): one of several layouts shown at a time */
#define PAGE_Dummy		(LAYOUT_Dummy + 0x0200)

#define PAGE_Add		(PAGE_Dummy + 1)	/* Object *: a new page */
#define PAGE_Remove		(PAGE_Dummy + 2)
#define PAGE_Current		(PAGE_Dummy + 3)	/* the page shown, from 0 */
#define PAGE_FixedVert		(PAGE_Dummy + 4)
#define PAGE_FixedHoriz		(PAGE_Dummy + 5)
#define PAGE_Transparent	(PAGE_Dummy + 6)

/* LM_ADDIMAGE's message */
struct lmAddImage
{
	ULONG	MethodID;
	struct Window *lm_Window;
	Object	*lm_Object;
	struct TagItem *lm_ObjectAttrs;
};

/* What a weight bar is told about its neighbours */
struct WeightObject
{
	LONG	wb_SuccHeight;
	LONG	wb_PredHeight;
	ULONG	wb_Reserved1;
	LONG	wb_SuccWidth;
	LONG	wb_PredWidth;
	ULONG	wb_Reserved2;
};

/* More names from the 3.2 interface */
#define CHILD_DataType		(CHILD_Dummy + 16)
#define CHILD_WeightBar		(LAYOUT_Dummy + 43)
#define INTERSPACE		1
#define LALIGN_CENTRE		2
#define LAYOUT_ALIGN_BOTTOM	1
#define LAYOUT_ALIGN_CENTER	2
#define LAYOUT_ALIGN_LEFT	0
#define LAYOUT_ALIGN_RIGHT	1
#define LAYOUT_ALIGN_TOP	0
#define LAYOUT_CharSet		(LAYOUT_Dummy + 47)
#define LAYOUT_DisposeLabels	(LAYOUT_Dummy + 0)
#define LAYOUT_DoImmediate	(LAYOUT_Dummy + 49)
#define LAYOUT_HORIZONTAL	0
#define LAYOUT_HorizSpacing	(LAYOUT_Dummy + 9)
#define LAYOUT_Immediate	(LAYOUT_Dummy + 48)
#define LAYOUT_Inverted		(LAYOUT_Dummy + 42)
#define LAYOUT_LayoutBackFill	(LAYOUT_Dummy + 45)
#define LAYOUT_LayoutMagic	(LAYOUT_Dummy + 46)
#define LAYOUT_NoLayout		(LAYOUT_Dummy + 44)
#define LAYOUT_VERTICAL		1
#define LAYOUT_VertSpacing	(LAYOUT_Dummy + 9)
#define LAYOUT_WeightBar	(LAYOUT_Dummy + 43)
#define LCLABEL_NOLABEL		1
#define PAGE_NoDispose		(PAGE_Dummy + 7)

#endif /* GADGETS_LAYOUT_H */
