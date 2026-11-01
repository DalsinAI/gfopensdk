#ifndef GADGETS_GETSCREENMODE_H
#define GADGETS_GETSCREENMODE_H
/*
 * OpenNDK: getscreenmode.gadget, a mode name field with a screen mode requester behind it.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define GETSCREENMODE_Dummy		(REACTION_Dummy + 0x41000)

#define GETSCREENMODE_TitleText		(GETSCREENMODE_Dummy + 1)	/* the requester's title */
#define GETSCREENMODE_Height		(GETSCREENMODE_Dummy + 2)	/* the requester's box */
#define GETSCREENMODE_Width		(GETSCREENMODE_Dummy + 3)
#define GETSCREENMODE_LeftEdge		(GETSCREENMODE_Dummy + 4)
#define GETSCREENMODE_TopEdge		(GETSCREENMODE_Dummy + 5)
#define GETSCREENMODE_DisplayID		(GETSCREENMODE_Dummy + 6)	/* the mode chosen */
#define GETSCREENMODE_DisplayWidth	(GETSCREENMODE_Dummy + 7)
#define GETSCREENMODE_DisplayHeight	(GETSCREENMODE_Dummy + 8)
#define GETSCREENMODE_DisplayDepth	(GETSCREENMODE_Dummy + 9)
#define GETSCREENMODE_OverscanType	(GETSCREENMODE_Dummy + 10)
#define GETSCREENMODE_AutoScroll	(GETSCREENMODE_Dummy + 11)
#define GETSCREENMODE_InfoOpened	(GETSCREENMODE_Dummy + 12)
#define GETSCREENMODE_InfoLeftEdge	(GETSCREENMODE_Dummy + 13)
#define GETSCREENMODE_InfoTopEdge	(GETSCREENMODE_Dummy + 14)
#define GETSCREENMODE_DoWidth		(GETSCREENMODE_Dummy + 15)
#define GETSCREENMODE_DoHeight		(GETSCREENMODE_Dummy + 16)
#define GETSCREENMODE_DoDepth		(GETSCREENMODE_Dummy + 17)
#define GETSCREENMODE_DoOverscanType	(GETSCREENMODE_Dummy + 18)
#define GETSCREENMODE_DoAutoScroll	(GETSCREENMODE_Dummy + 19)
#define GETSCREENMODE_PropertyFlags	(GETSCREENMODE_Dummy + 20)
#define GETSCREENMODE_PropertyMask	(GETSCREENMODE_Dummy + 21)
#define GETSCREENMODE_MinWidth		(GETSCREENMODE_Dummy + 22)
#define GETSCREENMODE_MaxWidth		(GETSCREENMODE_Dummy + 23)
#define GETSCREENMODE_MinHeight		(GETSCREENMODE_Dummy + 24)
#define GETSCREENMODE_MaxHeight		(GETSCREENMODE_Dummy + 25)
#define GETSCREENMODE_MinDepth		(GETSCREENMODE_Dummy + 26)
#define GETSCREENMODE_MaxDepth		(GETSCREENMODE_Dummy + 27)
#define GETSCREENMODE_FilterFunc	(GETSCREENMODE_Dummy + 28)
#define GETSCREENMODE_CustomSMList	(GETSCREENMODE_Dummy + 29)

/* Method: open the requester */
#define GSM_REQUEST	0x610001

/* GSM_REQUEST's message */
struct gsmRequest
{
    ULONG MethodID;
    struct Window *gsmr_Window;
};

#define RequestScreenMode(obj, win)	DoMethod((obj), GSM_REQUEST, (win))

#endif /* GADGETS_GETSCREENMODE_H */
