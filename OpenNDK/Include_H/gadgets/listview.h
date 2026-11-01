#ifndef GADGETS_LISTVIEW_H
#define GADGETS_LISTVIEW_H
/*
 * OpenNDK: the older listview gadget class.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

/* One row of a listview */
struct ListLabelNode
{
	struct Node lvn_Node;		/* ln_Name is the text */
	APTR	lvn_UserData;
	WORD	lvn_RenderForeground;	/* pens while not selected */
	WORD	lvn_RenderBackground;
	WORD	lvn_SelectForeground;	/* pens while selected */
	WORD	lvn_SelectBackground;
	struct Image *lvn_RenderImage;
	struct Image *lvn_SelectImage;
	UWORD	lvn_TextLength;
	WORD	lvn_LeftEdge;
	WORD	lvn_TopEdge;
	WORD	lvn_Width;
	WORD	lvn_Height;
	UWORD	lvn_Justification;
	UWORD	lvn_Selected;
};

/* More names from the 3.2 interface */
#define LISTVIEW_Dummy		0x84000000UL
#define LISTVIEW_CallHook	(LISTVIEW_Dummy + 11)
#define LISTVIEW_ItemHeight	(LISTVIEW_Dummy + 10)
#define LISTVIEW_Labels		(LISTVIEW_Dummy + 1)
#define LISTVIEW_MakeVisible	(LISTVIEW_Dummy + 8)
#define LISTVIEW_MultiSelect	(LISTVIEW_Dummy + 9)
#define LISTVIEW_ScrollDown	(LISTVIEW_Dummy + 13)
#define LISTVIEW_ScrollLeft	(LISTVIEW_Dummy + 14)
#define LISTVIEW_ScrollRight	(LISTVIEW_Dummy + 15)
#define LISTVIEW_ScrollUp	(LISTVIEW_Dummy + 12)
#define LISTVIEW_Selected	(LISTVIEW_Dummy + 7)
#define LISTVIEW_SelectedNode	(LISTVIEW_Dummy + 7)
#define LISTVIEW_ShowSelected	(LISTVIEW_Dummy + 6)
#define LISTVIEW_Spacing	(LISTVIEW_Dummy + 16)
#define LISTVIEW_Top		(LISTVIEW_Dummy + 2)
#define LISTVIEW_Total		(LISTVIEW_Dummy + 4)
#define LISTVIEW_Visible	(LISTVIEW_Dummy + 3)
#define LVJ_CENTER		1
#define LVJ_LEFT		0
#define LVJ_RIGHT		2

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#endif /* GADGETS_LISTVIEW_H */
