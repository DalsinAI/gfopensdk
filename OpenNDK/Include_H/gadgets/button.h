#ifndef GADGETS_BUTTON_H
#define GADGETS_BUTTON_H
/*
 * OpenNDK: button.gadget, push and toggle buttons with text, glyphs or pictures.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif
#ifndef IMAGES_BEVEL_H
#include <images/bevel.h>
#endif

#define BUTTON_Dummy		0x84000000

#define BUTTON_PushButton	(BUTTON_Dummy + 1)	/* BOOL: stays down when clicked */
#define BUTTON_Glyph		(BUTTON_Dummy + 2)	/* struct Image *: drawn in the text's pen */
#define BUTTON_TextPen		(BUTTON_Dummy + 5)
#define BUTTON_FillPen		(BUTTON_Dummy + 6)
#define BUTTON_FillTextPen	(BUTTON_Dummy + 7)
#define BUTTON_BackgroundPen	(BUTTON_Dummy + 8)
#define BUTTON_RenderImage	GA_Image
#define BUTTON_SelectImage	GA_SelectRender
#define BUTTON_BevelStyle	(BUTTON_Dummy + 13)	/* BVS_ from images/bevel.h */
#define BUTTON_Transparent	(BUTTON_Dummy + 15)
#define BUTTON_Justification	(BUTTON_Dummy + 16)	/* BCJ_ below */
#define BUTTON_SoftStyle	(BUTTON_Dummy + 17)
#define BUTTON_AutoButton	(BUTTON_Dummy + 18)	/* BAG_ below: a ready-made symbol button */
#define BUTTON_VarArgs		(BUTTON_Dummy + 19)	/* arguments for a GA_Text format */
#define BUTTON_DomainString	(BUTTON_Dummy + 20)	/* size the button for this text */
#define BUTTON_Integer		(BUTTON_Dummy + 21)	/* show a number */
#define BUTTON_BitMap		(BUTTON_Dummy + 22)	/* struct BitMap * */

/* Where the label sits */
#define BCJ_LEFT	0
#define BCJ_CENTER	1
#define BCJ_RIGHT	2

/* BUTTON_AutoButton kinds */
#define BAG_POPFILE	1
#define BAG_POPDRAWER	2
#define BAG_POPFONT	3
#define BAG_CHECKBOX	4
#define BAG_CANCELBOX	5
#define BAG_UPARROW	6
#define BAG_DNARROW	7
#define BAG_RTARROW	8
#define BAG_LFARROW	9
#define BAG_POPTIME	10
#define BAG_POPSCREEN	11
#define BAG_POPUP	12

/* More names from the 3.2 interface */
#define BAG_POPCOLOR		14
#define BAG_POPCOLOUR		14
#define BAG_POPDATE		13
#define BALIGN_BOTTOM		2
#define BALIGN_CENTER		1
#define BALIGN_LEFT		0
#define BALIGN_RIGHT		2
#define BALIGN_TOP		0
#define BCJ_CENTRE		1
#define BUTTON_AddAnimImageNumber	(BUTTON_Dummy + 55)
#define BUTTON_AnimButton	(BUTTON_Dummy + 50)
#define BUTTON_AnimImageNumber	(BUTTON_Dummy + 54)
#define BUTTON_AnimImages	(BUTTON_Dummy + 51)
#define BUTTON_Array		(BUTTON_Dummy + 3)
#define BUTTON_Current		(BUTTON_Dummy + 9)
#define BUTTON_EraseBackground	(BUTTON_Dummy + 57)
#define BUTTON_HorizAlignment	(BUTTON_Dummy + 58)
#define BUTTON_MaxAnimImages	(BUTTON_Dummy + 53)
#define BUTTON_SelAnimImages	(BUTTON_Dummy + 52)
#define BUTTON_SubAnimImageNumber	(BUTTON_Dummy + 56)
#define BUTTON_TextPadding	(BUTTON_Dummy + 40)
#define BUTTON_VertAlignment	(BUTTON_Dummy + 59)

#endif /* GADGETS_BUTTON_H */
