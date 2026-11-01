#ifndef GADGETS_CLICKTAB_H
#define GADGETS_CLICKTAB_H
/*
 * OpenNDK: clicktab.gadget, a row of tabs that can turn a page group.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define CLICKTAB_Dummy			(REACTION_Dummy + 0x27000)

#define CLICKTAB_Labels			(CLICKTAB_Dummy + 0x0001)	/* struct List * of AllocClickTabNode()s */
#define CLICKTAB_Current		(CLICKTAB_Dummy + 0x0002)	/* the current tab's TNA_Number */
#define CLICKTAB_CurrentNode		(CLICKTAB_Dummy + 0x0003)	/* struct Node * */
#define CLICKTAB_Orientation		(CLICKTAB_Dummy + 0x0004)	/* CTORIENT_ below */
#define CLICKTAB_PageGroup		(CLICKTAB_Dummy + 0x0005)	/* a page.gadget turned with the tabs */
#define CLICKTAB_PageGroupBackFill	(CLICKTAB_Dummy + 0x0006)	/* struct Hook *: the page's backfill */

#define CTORIENT_HORIZ	0
#define CTORIENT_VERT	1

/* A tab node's attributes (AllocClickTabNodeA and friends) */
#define TNA_Dummy	(TAG_USER + 0x010000)

#define TNA_UserData	(TNA_Dummy + 1)
#define TNA_Enabled	(TNA_Dummy + 2)
#define TNA_Spacing	(TNA_Dummy + 3)
#define TNA_Highlight	(TNA_Dummy + 4)
#define TNA_Image	(TNA_Dummy + 5)		/* struct Image * */
#define TNA_SelImage	(TNA_Dummy + 6)
#define TNA_Text	(TNA_Dummy + 7)		/* STRPTR */
#define TNA_Number	(TNA_Dummy + 8)		/* the value CLICKTAB_Current takes */
#define TNA_TextPen	(TNA_Dummy + 9)
#define TNA_Disabled	(TNA_Dummy + 10)

/* One tab, for CLICKTAB_Labels given as an array */
struct tagTabLabel
{
	STRPTR	tl_Label;
	WORD	tl_Pens[4];
	struct TagItem *tl_Attrs;
};

/* More names from the 3.2 interface */
#define CLICKTAB_AutoFit	(CLICKTAB_Dummy + 12)
#define CLICKTAB_AutoTabNumbering	(CLICKTAB_Dummy + 13)
#define CLICKTAB_ChooserFlagImage	(CLICKTAB_Dummy + 18)
#define CLICKTAB_CloseImage	(CLICKTAB_Dummy + 14)
#define CLICKTAB_ClosePlacement	(CLICKTAB_Dummy + 17)
#define CLICKTAB_Closed		(CLICKTAB_Dummy + 15)
#define CLICKTAB_EvenSize	(CLICKTAB_Dummy + 9)
#define CLICKTAB_FlagImage	(CLICKTAB_Dummy + 8)
#define CLICKTAB_LabelTruncate	(CLICKTAB_Dummy + 7)
#define CLICKTAB_MinorLabelChange	(CLICKTAB_Dummy + 19)
#define CLICKTAB_NodeClosed	(CLICKTAB_Dummy + 16)
#define CLICKTAB_PageBorder	(CLICKTAB_Dummy + 11)
#define CLICKTAB_PageGroupBorder	(CLICKTAB_Dummy + 11)
#define CLICKTAB_TabsOffsetAsLayoutSpacing	(CLICKTAB_Dummy + 20)
#define CLICKTAB_Total		(CLICKTAB_Dummy + 10)
#define CTORIENT_HORIZFLIP	2
#define CTORIENT_VERTFLIP	3
#define PLACECLOSE_LEFT		0
#define PLACECLOSE_RIGHT	1
#define TNA_CloseGadget		(TNA_Dummy + 13)
#define TNA_Flagged		(TNA_Dummy + 11)
#define TNA_HelpText		(TNA_Dummy + 15)
#define TNA_HintInfo		(TNA_Dummy + 12)
#define TNA_SoftStyle		(TNA_Dummy + 14)

#endif /* GADGETS_CLICKTAB_H */
