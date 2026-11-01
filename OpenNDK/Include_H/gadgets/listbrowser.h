#ifndef GADGETS_LISTBROWSER_H
#define GADGETS_LISTBROWSER_H
/*
 * OpenNDK: listbrowser.gadget, a list of rows in columns, flat or as a tree.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef INTUITION_CGHOOKS_H
#include <intuition/cghooks.h>
#endif

#define LISTBROWSER_Dummy		(REACTION_Dummy + 0x0003000)

#define LISTBROWSER_Top			(LISTBROWSER_Dummy + 1)		/* the first visible row */
#define LISTBROWSER_Labels		(LISTBROWSER_Dummy + 3)		/* struct List * of AllocListBrowserNode()s */
#define LISTBROWSER_Selected		(LISTBROWSER_Dummy + 4)		/* the selected row, -1 none */
#define LISTBROWSER_SelectedNode	(LISTBROWSER_Dummy + 5)
#define LISTBROWSER_MultiSelect		(LISTBROWSER_Dummy + 6)
#define LISTBROWSER_VertSeparators	(LISTBROWSER_Dummy + 7)		/* lines between columns */
#define LISTBROWSER_Separators		LISTBROWSER_VertSeparators
#define LISTBROWSER_ColumnInfo		(LISTBROWSER_Dummy + 8)		/* struct ColumnInfo * */
#define LISTBROWSER_MakeVisible		(LISTBROWSER_Dummy + 9)		/* scroll this row into view */
#define LISTBROWSER_VirtualWidth	(LISTBROWSER_Dummy + 10)
#define LISTBROWSER_Borderless		(LISTBROWSER_Dummy + 11)
#define LISTBROWSER_VerticalProp	(LISTBROWSER_Dummy + 12)	/* BOOL: a vertical scroller */
#define LISTBROWSER_HorizontalProp	(LISTBROWSER_Dummy + 13)
#define LISTBROWSER_Left		(LISTBROWSER_Dummy + 14)
#define LISTBROWSER_AutoFit		(LISTBROWSER_Dummy + 16)
#define LISTBROWSER_ColumnTitles	(LISTBROWSER_Dummy + 17)	/* BOOL: a title row */
#define LISTBROWSER_ShowSelected	(LISTBROWSER_Dummy + 18)
#define LISTBROWSER_VPropTotal		(LISTBROWSER_Dummy + 19)
#define LISTBROWSER_VPropTop		(LISTBROWSER_Dummy + 20)
#define LISTBROWSER_VPropVisible	(LISTBROWSER_Dummy + 21)
#define LISTBROWSER_HPropTotal		(LISTBROWSER_Dummy + 22)
#define LISTBROWSER_HPropTop		(LISTBROWSER_Dummy + 23)
#define LISTBROWSER_HPropVisible	(LISTBROWSER_Dummy + 24)
#define LISTBROWSER_MouseX		(LISTBROWSER_Dummy + 25)
#define LISTBROWSER_MouseY		(LISTBROWSER_Dummy + 26)
#define LISTBROWSER_Hierarchical	(LISTBROWSER_Dummy + 27)	/* BOOL: a tree */
#define LISTBROWSER_ShowImage		(LISTBROWSER_Dummy + 28)	/* struct Image *: a closed branch */
#define LISTBROWSER_HideImage		(LISTBROWSER_Dummy + 29)	/* an open branch */
#define LISTBROWSER_LeafImage		(LISTBROWSER_Dummy + 30)
#define LISTBROWSER_ScrollRaster	(LISTBROWSER_Dummy + 31)
#define LISTBROWSER_Spacing		(LISTBROWSER_Dummy + 32)	/* pixels between rows */
#define LISTBROWSER_Editable		(LISTBROWSER_Dummy + 33)
#define LISTBROWSER_Position		(LISTBROWSER_Dummy + 34)	/* LBP_ below */
#define LISTBROWSER_EditNode		(LISTBROWSER_Dummy + 35)
#define LISTBROWSER_EditColumn		(LISTBROWSER_Dummy + 36)
#define LISTBROWSER_RelEvent		(LISTBROWSER_Dummy + 37)	/* (get) LBRE_ below */
#define LISTBROWSER_NumSelected		(LISTBROWSER_Dummy + 38)
#define LISTBROWSER_EditTags		(LISTBROWSER_Dummy + 39)
#define LISTBROWSER_RelColumn		(LISTBROWSER_Dummy + 40)
#define LISTBROWSER_HorizSeparators	(LISTBROWSER_Dummy + 41)
#define LISTBROWSER_CheckImage		(LISTBROWSER_Dummy + 42)
#define LISTBROWSER_UncheckedImage	(LISTBROWSER_Dummy + 43)
#define LISTBROWSER_TotalNodes		(LISTBROWSER_Dummy + 44)
#define LISTBROWSER_MinNodeSize		(LISTBROWSER_Dummy + 45)
#define LISTBROWSER_TitleClickable	(LISTBROWSER_Dummy + 46)
#define LISTBROWSER_MinVisible		(LISTBROWSER_Dummy + 47)
#define LISTBROWSER_PersistSelect	(LISTBROWSER_Dummy + 50)
#define LISTBROWSER_CursorSelected	(LISTBROWSER_Dummy + 51)
#define LISTBROWSER_CursorNode		(LISTBROWSER_Dummy + 52)
#define LISTBROWSER_FastRender		(LISTBROWSER_Dummy + 53)
#define LISTBROWSER_TotalVisibleNodes	(LISTBROWSER_Dummy + 54)
#define LISTBROWSER_WrapText		(LISTBROWSER_Dummy + 55)

/* LISTBROWSER_Position: moves of the view */
#define LBP_LINEUP	1
#define LBP_LINEDOWN	2
#define LBP_PAGEUP	3
#define LBP_PAGEDOWN	4
#define LBP_TOP		5
#define LBP_BOTTOM	6
#define LBP_SHIFTLEFT	10
#define LBP_SHIFTRIGHT	11
#define LBP_LEFTEDGE	12
#define LBP_RIGHTEDGE	13

/* LISTBROWSER_RelEvent: what the last release did */
#define LBRE_NORMAL		1
#define LBRE_HIDECHILDREN	2
#define LBRE_SHOWCHILDREN	4
#define LBRE_EDIT		8
#define LBRE_DOUBLECLICK	16
#define LBRE_CHECKED		32
#define LBRE_UNCHECKED		64
#define LBRE_TITLECLICK		128
#define LBRE_COLUMNADJUST	256
#define LBRE_EDITTABNEXT	512
#define LBRE_EDITTABPREV	1024

/* A node's attributes; LBNCA_ ones apply to the column LBNA_Column chose */
#define LBNA_Dummy		(TAG_USER + 0x5003500)

#define LBNA_Selected		(LBNA_Dummy + 1)
#define LBNA_Flags		(LBNA_Dummy + 2)	/* LBFLG_ below */
#define LBNA_UserData		(LBNA_Dummy + 3)
#define LBNA_Column		(LBNA_Dummy + 4)
#define LBNCA_Text		(LBNA_Dummy + 5)	/* STRPTR */
#define LBNCA_Integer		(LBNA_Dummy + 6)	/* LONG *: shown as a number */
#define LBNCA_FGPen		(LBNA_Dummy + 7)
#define LBNCA_BGPen		(LBNA_Dummy + 8)
#define LBNCA_Image		(LBNA_Dummy + 9)
#define LBNCA_SelImage		(LBNA_Dummy + 10)
#define LBNCA_HorizJustify	(LBNA_Dummy + 11)	/* LCJ_ below */
#define LBNCA_Justification	LBNCA_HorizJustify
#define LBNA_Generation		(LBNA_Dummy + 12)	/* the depth in a tree, from 1 */
#define LBNCA_Editable		(LBNA_Dummy + 13)
#define LBNCA_MaxChars		(LBNA_Dummy + 14)
#define LBNCA_CopyText		(LBNA_Dummy + 15)	/* BOOL: keep a copy of LBNCA_Text */
#define LBNA_CheckBox		(LBNA_Dummy + 16)
#define LBNA_Checked		(LBNA_Dummy + 17)
#define LBNA_NodeSize		(LBNA_Dummy + 18)
#define LBNCA_EditTags		(LBNA_Dummy + 19)
#define LBNCA_RenderHook	(LBNA_Dummy + 20)
#define LBNCA_HookHeight	(LBNA_Dummy + 22)
#define LBNA_MemPool		(LBNA_Dummy + 23)
#define LBNA_NumColumns		(LBNA_Dummy + 24)
#define LBNA_Priority		(LBNA_Dummy + 25)
#define LBNCA_CopyInteger	(LBNA_Dummy + 26)
#define LBNCA_WordWrap		(LBNA_Dummy + 27)
#define LBNCA_VertJustify	(LBNA_Dummy + 28)

/* Justification in a column */
#define LCJ_LEFT	0
#define LCJ_CENTER	1
#define LCJ_CENTRE	LCJ_CENTER
#define LCJ_RIGHT	2

/* LBNA_Flags */
#define LBFLG_READONLY		1
#define LBFLG_CUSTOMPENS	2
#define LBFLG_HASCHILDREN	4
#define LBFLG_SHOWCHILDREN	8
#define LBFLG_HIDDEN		16

/* One column; an array of them ends with ci_Width -1 */
struct ColumnInfo
{
	WORD	ci_Width;	/* a weight, or pixels with CIF_FIXED */
	STRPTR	ci_Title;
	ULONG	ci_Flags;	/* CIF_ below */
};

#define CIF_WEIGHTED		0
#define CIF_FIXED		1
#define CIF_DRAGGABLE		2
#define CIF_NOSEPARATORS	4
#define CIF_SORTABLE		8

/* Methods */
#define LBM_ADDNODE	0x580001
#define LBM_REMNODE	0x580002
#define LBM_EDITNODE	0x580003
#define LBM_SORT	0x580004

struct lbAddNode
{
	ULONG			MethodID;	/* LBM_ADDNODE */
	struct GadgetInfo	*lba_GInfo;
	struct Node		*lba_Node;	/* insert after this one */
	struct TagItem		*lba_NodeAttrs;
};

struct lbRemNode
{
	ULONG			MethodID;	/* LBM_REMNODE */
	struct GadgetInfo	*lbr_GInfo;
	struct Node		*lbr_Node;
};

struct lbEditNode
{
	ULONG			MethodID;	/* LBM_EDITNODE */
	struct GadgetInfo	*lbe_GInfo;
	struct Node		*lbe_Node;
	struct TagItem		*lbe_NodeAttrs;
};

struct lbSort
{
	ULONG			MethodID;	/* LBM_SORT */
	struct GadgetInfo	*lbs_GInfo;
	ULONG			lbs_Column;
	ULONG			lbs_Direction;	/* LBSORT_REVERSE to sort descending */
	struct Hook		*lbs_CompareHook;	/* NULL: compare the text */
};

#define LBSORT_REVERSE	1

/* What a sort hook is given to compare two rows */
struct LBSortMsg
{
	ULONG	lbsm_TypeA;		/* LBNCA_Text or LBNCA_Integer */
	union
	{
		LONG	Integer;
		STRPTR	Text;
	}	lbsm_DataA;
	APTR	lbsm_UserDataA;
	ULONG	lbsm_TypeB;
	union
	{
		LONG	Integer;
		STRPTR	Text;
	}	lbsm_DataB;
	APTR	lbsm_UserDataB;
	UWORD	lbsm_Column;		/* the column being sorted */
	ULONG	lbsm_Direction;		/* LBMSORT_ */
};

/* What a custom-draw hook is given for one cell */
struct LBDrawMsg
{
	ULONG	lbdm_MethodID;		/* LV_DRAW */
	struct RastPort *lbdm_RastPort;
	struct DrawInfo *lbdm_DrawInfo;
	struct Rectangle lbdm_Bounds;
	ULONG	lbdm_State;		/* LBR_ */
};

/* LBM_HIDECHILDREN and LBM_SHOWCHILDREN's messages */
struct lbHideChildren
{
	ULONG	MethodID;
	struct GadgetInfo *lbhc_GInfo;
	struct Node *lbhc_Node;		/* NULL for every node */
	WORD	lbhc_Depth;
};

struct lbShowChildren
{
	ULONG	MethodID;
	struct GadgetInfo *lbsc_GInfo;
	struct Node *lbsc_Node;
	WORD	lbsc_Depth;
};

/* More names from the 3.2 interface */
#define CIF_CENTER		16
#define CIF_CENTRE		16
#define CIF_RIGHT		32
#define LBCB_OK			0
#define LBCB_UNKNOWN		1
#define LBCIA_AutoSort		(LBNA_Dummy + 58)
#define LBCIA_Column		(LBNA_Dummy + 51)
#define LBCIA_CompareHook	(LBNA_Dummy + 60)
#define LBCIA_CopyTitle		(LBNA_Dummy + 65)
#define LBCIA_DraggableSeparator	(LBNA_Dummy + 62)
#define LBCIA_Flags		(LBNA_Dummy + 55)
#define LBCIA_HorizJustify	(LBNA_Dummy + 67)
#define LBCIA_MemPool		(LBNA_Dummy + 50)
#define LBCIA_Separator		(LBNA_Dummy + 63)
#define LBCIA_SoftStyle		(LBNA_Dummy + 66)
#define LBCIA_SortArrow		(LBNA_Dummy + 64)
#define LBCIA_SortDirection	(LBNA_Dummy + 59)
#define LBCIA_Sortable		(LBNA_Dummy + 61)
#define LBCIA_Title		(LBNA_Dummy + 52)
#define LBCIA_UserData		(LBNA_Dummy + 57)
#define LBCIA_Weight		(LBNA_Dummy + 53)
#define LBCIA_Width		(LBNA_Dummy + 54)
#define LBET_DELAYEDSECOND	1
#define LBET_DOUBLECLICK	0
#define LBMSORT_FORWARD		0
#define LBMSORT_REVERSE		1
#define LBM_HIDECHILDREN	0x580006
#define LBM_SHOWCHILDREN	0x580005
#define LBNCA_FillPen		(LBNA_Dummy + 29)
#define LBNCA_SoftStyle		(LBNA_Dummy + 56)
#define LBP_PAGELEFT		14
#define LBP_PAGERIGHT		15
#define LBR_NORMAL		0
#define LBR_SELECTED		1
#define LBS_BOTH		3
#define LBS_COLUMNS		2
#define LBS_NONE		0
#define LBS_ROWS		1
#define LB_DRAW			0x202
#define LISTBROWSER_AllowNoSelection	(LISTBROWSER_Dummy + 63)
#define LISTBROWSER_AutoVirtualWidth	(LISTBROWSER_Dummy + 59)
#define LISTBROWSER_AutoWheel	(LISTBROWSER_Dummy + 64)
#define LISTBROWSER_Bottom	(LISTBROWSER_Dummy + 57)
#define LISTBROWSER_CursorSelect	(LISTBROWSER_Dummy + 51)
#define LISTBROWSER_EditTrigger	(LISTBROWSER_Dummy + 66)
#define LISTBROWSER_HintInfoHook	(LISTBROWSER_Dummy + 60)
#define LISTBROWSER_MakeNodeVisible	(LISTBROWSER_Dummy + 58)
#define LISTBROWSER_MemPool	(LISTBROWSER_Dummy + 56)
#define LISTBROWSER_Reserved1	(LISTBROWSER_Dummy + 2)
#define LISTBROWSER_Reserved2	(LISTBROWSER_Dummy + 15)
#define LISTBROWSER_Reserved6	(LISTBROWSER_Dummy + 48)
#define LISTBROWSER_Reserved7	(LISTBROWSER_Dummy + 49)
#define LISTBROWSER_SortColumn	(LISTBROWSER_Dummy + 61)
#define LISTBROWSER_StayActive	(LISTBROWSER_Dummy + 65)
#define LISTBROWSER_Striping	(LISTBROWSER_Dummy + 62)
#define LRJ_BOTTOM		0
#define LRJ_CENTER		1
#define LRJ_CENTRE		1
#define LRJ_TOP			2

/* lbSort's field under its older name */
#define lbs_Reverse		lbs_Direction

#endif /* GADGETS_LISTBROWSER_H */
