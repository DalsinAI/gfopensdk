#ifndef CLASSES_REQUESTER_H
#define CLASSES_REQUESTER_H
/*
 * OpenNDK: requester.class, message, number and text requesters.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif

#define REQ_Dummy		(REACTION_Dummy + 0x45000)

#define REQ_Type		(REQ_Dummy + 1)		/* REQTYPE_ below */
#define REQ_TitleText		(REQ_Dummy + 2)
#define REQ_BodyText		(REQ_Dummy + 3)		/* STRPTR: may hold a format */
#define REQ_GadgetText		(REQ_Dummy + 4)		/* STRPTR: buttons split by '|' */
#define REQ_ReturnCode		(REQ_Dummy + 5)		/* (get) the button chosen */
#define REQ_TabSize		(REQ_Dummy + 6)
#define REQ_Image		(REQ_Dummy + 7)		/* REQIMAGE_ below, or struct Image * */
#define REQ_VarArgs		(REQ_Dummy + 8)		/* APTR: REQ_BodyText's arguments */

/* REQ_Image's standard pictures */
#define REQIMAGE_DEFAULT	0
#define REQIMAGE_INFO		1
#define REQIMAGE_WARNING	2
#define REQIMAGE_ERROR		3
#define REQIMAGE_QUESTION	4
#define REQIMAGE_INSERTDISK	5

/* REQTYPE_INTEGER */
#define REQI_Minimum		(REQ_Dummy + 513)
#define REQI_Maximum		(REQ_Dummy + 514)
#define REQI_Invisible		(REQ_Dummy + 515)	/* BOOL: hide what is typed */
#define REQI_Number		(REQ_Dummy + 516)	/* LONG: the value */
#define REQI_Arrows		(REQ_Dummy + 517)
#define REQI_MaxChars		(REQ_Dummy + 518)

/* REQTYPE_STRING */
#define REQS_AllowEmpty		(REQ_Dummy + 257)
#define REQS_Buffer		(REQ_Dummy + 258)	/* STRPTR: the text, edited in place */
#define REQS_ShowDefault	(REQ_Dummy + 259)
#define REQS_MaxChars		(REQ_Dummy + 260)
#define REQS_ChooserArray	(REQ_Dummy + 261)	/* STRPTR *: offer these in a chooser */
#define REQS_ChooserActive	(REQ_Dummy + 262)
#define REQS_Invisible		(REQ_Dummy + 515)	/* BOOL: hide what is typed */

/* REQ_Type */
#define REQTYPE_INFO		0
#define REQTYPE_INTEGER		1
#define REQTYPE_STRING		2

/* Method: show the requester and wait for an answer */
#define RM_OPENREQ		0x650001

struct orRequest
{
	ULONG		MethodID;	/* RM_OPENREQ */
	struct TagItem	*or_Attrs;	/* more REQ_ tags for this time */
	struct Window	*or_Window;	/* the window it belongs to */
	struct Screen	*or_Screen;	/* or the screen, without a window */
};

/* Shows obj over win (amiga.lib's DoMethod) */
#define OpenRequester(obj, win) DoMethod((Object *)(obj), RM_OPENREQ, NULL, (win), NULL)

/* More names from the 3.2 interface */
#define REQS_Dummy		(REQ_Dummy + 256)
#define REQI_Dummy		(REQS_Dummy + 256)
#define REQP_Dummy		(REQI_Dummy + 256)
#define REQI_Mark		(REQI_Dummy + 9)
#define REQI_MaxText		(REQI_Dummy + 8)
#define REQI_MinText		(REQI_Dummy + 7)
#define REQI_ReturnEnds		(REQI_Dummy + 10)
#define REQP_AbortText		(REQ_Dummy + 4)
#define REQP_CenterWindow	(REQP_Dummy + 6)
#define REQP_Current		(REQP_Dummy + 2)
#define REQP_Dynamic		(REQP_Dummy + 5)
#define REQP_LastPosition	(REQP_Dummy + 7)
#define REQP_NoText		(REQP_Dummy + 4)
#define REQP_OpenInactive	(REQP_Dummy + 3)
#define REQP_Percent		(REQP_Dummy + 8)
#define REQP_ProgressText	(REQ_Dummy + 3)
#define REQP_ShortTicks		(REQP_Dummy + 10)
#define REQP_Ticks		(REQP_Dummy + 9)
#define REQP_Total		(REQP_Dummy + 1)
#define REQS_Mark		(REQS_Dummy + 7)
#define REQS_ReturnEnds		(REQS_Dummy + 8)
#define REQTYPE_PROGRESS	3
#define REQ_CharSet		(REQ_Dummy + 14)
#define REQ_EvenButtons		(REQ_Dummy + 9)
#define REQ_ForceFocus		(REQ_Dummy + 16)
#define REQ_IDCMP_Ptr		(REQ_Dummy + 12)
#define REQ_Inactive		(REQ_Dummy + 13)
#define REQ_StayOnTop		(REQ_Dummy + 15)
#define REQ_TimeOutSecs		(REQ_Dummy + 11)
#define REQ_WrapBorder		(REQ_Dummy + 10)

#endif /* CLASSES_REQUESTER_H */
