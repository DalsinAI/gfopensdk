#ifndef GADGETS_GETCOLOR_H
#define GADGETS_GETCOLOR_H
/*
 * OpenNDK: getcolor.gadget, a colour swatch with a colour requester behind it.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define GETCOLOR_Dummy		(REACTION_Dummy + 0x43000)

#define GETCOLOR_TitleText	(GETCOLOR_Dummy + 1)	/* the requester's title */
/* The requester's box: not in the 3.2 interface. These are OpenReAction's
 * own tags, placed after the 3.2 ones so they can't clash with them. */
#define GETCOLOR_LeftEdge	(GETCOLOR_Dummy + 40)
#define GETCOLOR_TopEdge	(GETCOLOR_Dummy + 41)
#define GETCOLOR_Width		(GETCOLOR_Dummy + 42)
#define GETCOLOR_Height		(GETCOLOR_Dummy + 43)
#define GETCOLOR_Screen		(GETCOLOR_Dummy + 2)
#define GETCOLOR_Color		(GETCOLOR_Dummy + 3)	/* ULONG: 0x00RRGGBB */
#define GETCOLOR_RGB		(GETCOLOR_Dummy + 10)	/* ULONG *: three 32-bit values */

/* Method: open the requester */
#define GCOLOR_REQUEST	0x630001

/* GCOLOR_REQUEST's message */
struct gcRequest
{
    ULONG MethodID;
    struct Window *gcr_Window;		/* the requester's parent */
};

/* What a palette box's draw hook is given */
struct PBoxDrawMsg
{
    ULONG pbdm_MethodID;
    struct RastPort *pbdm_RastPort;
    struct DrawInfo *pbdm_DrawInfo;
    struct Rectangle pbdm_Bounds;
    ULONG pbdm_State;
    ULONG pbdm_Color;
    struct Gadget *pbdm_Gadget;
};

/* More names from the 3.2 interface */
#define GETCOLOR_Blue		(GETCOLOR_Dummy + 6)
#define GETCOLOR_Brightness	(GETCOLOR_Dummy + 9)
#define GETCOLOR_ColorWheel	(GETCOLOR_Dummy + 12)
#define GETCOLOR_Green		(GETCOLOR_Dummy + 5)
#define GETCOLOR_HSB		(GETCOLOR_Dummy + 11)
#define GETCOLOR_HSBSliders	(GETCOLOR_Dummy + 14)
#define GETCOLOR_Hue		(GETCOLOR_Dummy + 7)
#define GETCOLOR_Initial	(GETCOLOR_Dummy + 16)
#define GETCOLOR_RGBSliders	(GETCOLOR_Dummy + 13)
#define GETCOLOR_Red		(GETCOLOR_Dummy + 4)
#define GETCOLOR_Saturation	(GETCOLOR_Dummy + 8)
#define GETCOLOR_ShowHSB	(GETCOLOR_Dummy + 18)
#define GETCOLOR_ShowRGB	(GETCOLOR_Dummy + 17)
#define GETCOLOR_SmallTextAttr	(GETCOLOR_Dummy + 19)
#define GETCOLOR_SwitchMode	(GETCOLOR_Dummy + 15)

#define RequestColor(obj, win)	DoMethod((obj), GCOLOR_REQUEST, (win))

#endif /* GADGETS_GETCOLOR_H */
