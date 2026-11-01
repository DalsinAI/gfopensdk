#ifndef IMAGES_BEVEL_H
#define IMAGES_BEVEL_H
/*
 * OpenNDK: bevel.image, the frames ReAction draws round gadgets and groups.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_IMAGECLASS_H
#include <intuition/imageclass.h>
#endif

#define BEVEL_Dummy		(REACTION_Dummy + 0x16000)

#define BEVEL_Style		(BEVEL_Dummy + 1)	/* BVS_ below */
#define BEVEL_Label		(BEVEL_Dummy + 3)	/* STRPTR: a title in or on the frame */
#define BEVEL_LabelImage	(BEVEL_Dummy + 4)	/* struct Image *: a picture title */
#define BEVEL_LabelPlace	(BEVEL_Dummy + 5)	/* BVJ_ below */
#define BEVEL_InnerTop		(BEVEL_Dummy + 6)	/* (get) the inside box */
#define BEVEL_InnerLeft		(BEVEL_Dummy + 7)
#define BEVEL_InnerWidth	(BEVEL_Dummy + 8)
#define BEVEL_InnerHeight	(BEVEL_Dummy + 9)
#define BEVEL_HorizSize		(BEVEL_Dummy + 10)	/* (get) the edges' thickness */
#define BEVEL_VertSize		(BEVEL_Dummy + 11)
#define BEVEL_FillPen		(BEVEL_Dummy + 12)	/* fill inside the frame */
#define BEVEL_FillPattern	(BEVEL_Dummy + 13)
#define BEVEL_TextPen		(BEVEL_Dummy + 14)	/* the label's pen */
#define BEVEL_Transparent	(BEVEL_Dummy + 15)	/* leave the inside alone */
#define BEVEL_SoftStyle		(BEVEL_Dummy + 16)	/* the label's font style */
#define BEVEL_ColorMap		(BEVEL_Dummy + 17)
#define BEVEL_Flags		(BEVEL_Dummy + 18)

/* Frame kinds */
#define BVS_THIN	0	/* one pixel each side */
#define BVS_BUTTON	1	/* raised */
#define BVS_GROUP	2	/* a group's etched line */
#define BVS_FIELD	3	/* a text field's double edge */
#define BVS_NONE	4
#define BVS_DROPBOX	5	/* a drop target */
#define BVS_SBAR_HORIZ	6	/* a separator bar */
#define BVS_SBAR_VERT	7
#define BVS_BOX		8	/* a plain box */

/* Where BEVEL_Label goes */
#define BVJ_TOP_CENTER	0
#define BVJ_TOP_LEFT	1
#define BVJ_TOP_RIGHT	2
#define BVJ_IN_CENTER	3
#define BVJ_IN_LEFT	4
#define BVJ_IN_RIGHT	5

/* More names from the 3.2 interface */
#define BEVEL_ColourMap		(BEVEL_Dummy + 17)
#define BEVEL_HorzSize		(BEVEL_Dummy + 10)
#define BFLG_TRANS		2
#define BFLG_XENFILL		1
#define BVJ_BOT_CENTER		6
#define BVJ_BOT_LEFT		7
#define BVJ_BOT_RIGHT		8
#define BVS_CONTAINER		12
#define BVS_DISPLAY		14
#define BVS_FOCUS		9
#define BVS_KNOB		13
#define BVS_RADIOBUTTON		10
#define BVS_SBAR_HORZ		6
#define BVS_STANDARD		11

#endif /* IMAGES_BEVEL_H */
