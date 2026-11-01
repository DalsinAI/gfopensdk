#ifndef GADGETS_CHOOSER_H
#define GADGETS_CHOOSER_H
/*
 * OpenNDK: chooser.gadget, a pop-up or drop-down menu of choices.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define CHOOSER_Dummy		(REACTION_Dummy + 0x0001000)

#define CHOOSER_PopUp		(CHOOSER_Dummy + 0x0001)	/* BOOL: shows the choice, pops up the list */
#define CHOOSER_DropDown	(CHOOSER_Dummy + 0x0002)	/* BOOL: shows CHOOSER_Title, drops a menu */
#define CHOOSER_Title		(CHOOSER_Dummy + 0x0003)	/* STRPTR */
#define CHOOSER_Labels		(CHOOSER_Dummy + 0x0004)	/* struct List * of AllocChooserNode()s */
#define CHOOSER_Active		(CHOOSER_Dummy + 0x0005)	/* the chosen entry, from 0 */
#define CHOOSER_Selected	CHOOSER_Active
#define CHOOSER_Width		(CHOOSER_Dummy + 0x0006)	/* the menu's width */
#define CHOOSER_AutoFit		(CHOOSER_Dummy + 0x0007)	/* BOOL: size the menu to its labels */
#define CHOOSER_MaxLabels	(CHOOSER_Dummy + 0x0009)
#define CHOOSER_Offset		(CHOOSER_Dummy + 0x000A)	/* added to CHOOSER_Active in notifications */
#define CHOOSER_Hidden		(CHOOSER_Dummy + 0x000B)	/* BOOL: no gadget, only the menu */
#define CHOOSER_LabelArray	(CHOOSER_Dummy + 0x000C)	/* STRPTR *: labels without nodes */
#define CHOOSER_Justification	(CHOOSER_Dummy + 0x000D)	/* CHJ_ below */

#define CHJ_LEFT	0
#define CHJ_CENTER	1
#define CHJ_RIGHT	2

/* A chooser node's attributes (AllocChooserNodeA and friends) */
#define CNA_Dummy	(TAG_USER + 0x5001500)

#define CNA_Text	(CNA_Dummy + 1)		/* STRPTR */
#define CNA_Image	(CNA_Dummy + 2)		/* struct Image * */
#define CNA_SelImage	(CNA_Dummy + 3)		/* struct Image *: when highlighted */
#define CNA_UserData	(CNA_Dummy + 4)
#define CNA_Separator	(CNA_Dummy + 5)		/* BOOL: a line, not a choice */
#define CNA_Disabled	(CNA_Dummy + 6)
#define CNA_BGPen	(CNA_Dummy + 7)
#define CNA_FGPen	(CNA_Dummy + 8)
#define CNA_ReadOnly	(CNA_Dummy + 9)

/* More names from the 3.2 interface */
#define CHOOSER_DeactivateOnMostRawKeys	(CHOOSER_Dummy + 16)
#define CHOOSER_ImageJustification	(CHOOSER_Dummy + 14)
#define CHOOSER_MinHeight	10
#define CHOOSER_MinWidth	36
#define CHOOSER_SelectedNode	(CHOOSER_Dummy + 15)
#define CNA_CopyText		(CNA_Dummy + 10)

#endif /* GADGETS_CHOOSER_H */
