#ifndef GADGETS_GETFONT_H
#define GADGETS_GETFONT_H
/*
 * OpenNDK: getfont.gadget, a font name field with a font requester behind it.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define GETFONT_Dummy		(REACTION_Dummy + 0x40000)

#define GETFONT_TextAttr	(GETFONT_Dummy + 1)	/* struct TextAttr *: the font */
#define GETFONT_DoFrontPen	(GETFONT_Dummy + 2)
#define GETFONT_DoBackPen	(GETFONT_Dummy + 3)
#define GETFONT_DoStyle		(GETFONT_Dummy + 4)
#define GETFONT_DoDrawMode	(GETFONT_Dummy + 5)
#define GETFONT_MinHeight	(GETFONT_Dummy + 6)
#define GETFONT_MaxHeight	(GETFONT_Dummy + 7)
#define GETFONT_FixedWidthOnly	(GETFONT_Dummy + 8)
#define GETFONT_TitleText	(GETFONT_Dummy + 9)	/* the requester's title */
#define GETFONT_Height		(GETFONT_Dummy + 10)	/* the requester's box */
#define GETFONT_Width		(GETFONT_Dummy + 11)
#define GETFONT_LeftEdge	(GETFONT_Dummy + 12)
#define GETFONT_TopEdge		(GETFONT_Dummy + 13)
#define GETFONT_FrontPen	(GETFONT_Dummy + 14)
#define GETFONT_BackPen		(GETFONT_Dummy + 15)
#define GETFONT_DrawMode	(GETFONT_Dummy + 16)
#define GETFONT_MaxFrontPen	(GETFONT_Dummy + 17)
#define GETFONT_MaxBackPen	(GETFONT_Dummy + 18)
#define GETFONT_ModeList	(GETFONT_Dummy + 19)
#define GETFONT_FrontPens	(GETFONT_Dummy + 20)
#define GETFONT_BackPens	(GETFONT_Dummy + 21)
#define GETFONT_SoftStyle	(GETFONT_Dummy + 22)

/* Method: open the requester */
#define GFONT_REQUEST	0x600001

/* More names from the 3.2 interface */
#define GETFONT_CSFilterFunc	(GETFONT_Dummy + 31)
#define GETFONT_CharSet		(GETFONT_Dummy + 25)
#define GETFONT_DoCharSet	(GETFONT_Dummy + 24)
#define GETFONT_DoSpecialMode	(GETFONT_Dummy + 28)
#define GETFONT_FilterFunc	(GETFONT_Dummy + 30)
#define GETFONT_OTagOnly	(GETFONT_Dummy + 26)
#define GETFONT_SampleText	(GETFONT_Dummy + 23)
#define GETFONT_ScalableOnly	(GETFONT_Dummy + 27)
#define GETFONT_SpecialMode	(GETFONT_Dummy + 29)
#define GETFONT_SpecialModeBitMap	(GETFONT_Dummy + 32)
#define GETFONT_SpecialModeBitMapHeight	(GETFONT_Dummy + 34)
#define GETFONT_SpecialModeBitMapWidth	(GETFONT_Dummy + 33)

#define gfRequestFont(obj, win)	DoMethod((obj), GFONT_REQUEST, (win))

#endif /* GADGETS_GETFONT_H */
