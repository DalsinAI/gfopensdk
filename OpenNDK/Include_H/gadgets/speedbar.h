#ifndef GADGETS_SPEEDBAR_H
#define GADGETS_SPEEDBAR_H
/*
 * OpenNDK: speedbar.gadget, a tool bar of picture buttons.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define SPEEDBAR_Dummy		(REACTION_Dummy + 0x13000)

#define SPEEDBAR_Buttons	(SPEEDBAR_Dummy + 1)	/* struct List * of AllocSpeedButtonNode()s */
#define SPEEDBAR_Orientation	(SPEEDBAR_Dummy + 2)	/* SBORIENT_ below */
#define SPEEDBAR_Background	(SPEEDBAR_Dummy + 3)	/* the background pen */
#define SPEEDBAR_Window		(SPEEDBAR_Dummy + 4)	/* struct Window *: for help texts */
#define SPEEDBAR_StrumBar	(SPEEDBAR_Dummy + 5)	/* BOOL: drag across to press */
#define SPEEDBAR_OnButton	(SPEEDBAR_Dummy + 6)	/* select this button number */
#define SPEEDBAR_OffButton	(SPEEDBAR_Dummy + 7)	/* deselect it */
#define SPEEDBAR_ScrollLeft	(SPEEDBAR_Dummy + 8)
#define SPEEDBAR_ScrollRight	(SPEEDBAR_Dummy + 9)
#define SPEEDBAR_Top		(SPEEDBAR_Dummy + 10)
#define SPEEDBAR_Visible	(SPEEDBAR_Dummy + 11)
#define SPEEDBAR_Total		(SPEEDBAR_Dummy + 12)
#define SPEEDBAR_Help		(SPEEDBAR_Dummy + 13)
#define SPEEDBAR_BevelStyle	(SPEEDBAR_Dummy + 14)
#define SPEEDBAR_Selected	(SPEEDBAR_Dummy + 15)	/* the button number last pressed */
#define SPEEDBAR_SelectedNode	(SPEEDBAR_Dummy + 16)
#define SPEEDBAR_EvenSize	(SPEEDBAR_Dummy + 17)

#define SBORIENT_HORIZ	0
#define SBORIENT_VERT	1

/* A button node's attributes */
#define SBNA_Dummy	(TAG_USER + 0x010000)

#define SBNA_Left	(SBNA_Dummy + 1)
#define SBNA_Top	(SBNA_Dummy + 2)
#define SBNA_Width	(SBNA_Dummy + 3)
#define SBNA_Height	(SBNA_Dummy + 4)
#define SBNA_UserData	(SBNA_Dummy + 5)
#define SBNA_Enabled	(SBNA_Dummy + 6)
#define SBNA_Spacing	(SBNA_Dummy + 7)
#define SBNA_Highlight	(SBNA_Dummy + 8)	/* SBH_ below */
#define SBNA_Image	(SBNA_Dummy + 9)
#define SBNA_SelImage	(SBNA_Dummy + 10)
#define SBNA_Help	(SBNA_Dummy + 11)	/* STRPTR */
#define SBNA_Toggle	(SBNA_Dummy + 12)	/* BOOL: stays down */
#define SBNA_Selected	(SBNA_Dummy + 13)
#define SBNA_MXGroup	(SBNA_Dummy + 14)	/* buttons of one group exclude each other */
#define SBNA_Disabled	(SBNA_Dummy + 15)
#define SBNA_Text	(SBNA_Dummy + 16)	/* STRPTR */

/* How a pressed button is shown */
#define SBH_NONE	0
#define SBH_BACKFILL	1
#define SBH_RECESS	2
#define SBH_IMAGE	3

/* SBM_SETNODEATTRS's message */
struct sbSetNodeAttrs
{
	ULONG	MethodID;
	struct GadgetInfo *sb_GInfo;
	struct Node *sb_Node;
	struct TagItem *sb_AttrList;
};

/* More names from the 3.2 interface */
#define SBM_SETNODEATTRS	0x58000A
#define SBNA_ButtonID		(SBNA_Dummy + 20)
#define SBNA_HintInfo		(SBNA_Dummy + 19)
#define SBNA_Separator		(SBNA_Dummy + 18)
#define SBNA_Spacer		(SBNA_Dummy + 17)
#define SBTYPE_BOTH		0
#define SBTYPE_IMAGE		2
#define SBTYPE_TEXT		1
#define SPEEDBAR_ButtonBevelStyle	(SPEEDBAR_Dummy + 2049)
#define SPEEDBAR_ButtonType	(SPEEDBAR_Dummy + 20)
#define SPEEDBAR_Font		(SPEEDBAR_Dummy + 18)
#define SPEEDBAR_HORIZONTAL	0
#define SPEEDBAR_HorizPadding	(SPEEDBAR_Dummy + 21)
#define SPEEDBAR_TopNode	(SPEEDBAR_Dummy + 19)
#define SPEEDBAR_VERTICAL	1
#define SPEEDBAR_VertPadding	(SPEEDBAR_Dummy + 22)

#endif /* GADGETS_SPEEDBAR_H */
