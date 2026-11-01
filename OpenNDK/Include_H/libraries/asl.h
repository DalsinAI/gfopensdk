#ifndef LIBRARIES_ASL_H
#define LIBRARIES_ASL_H
/*
 * OpenNDK: asl.library's file, font and screen mode requesters and the
 * tags that set them up.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef WORKBENCH_STARTUP_H
#include <workbench/startup.h>
#endif
#ifndef GRAPHICS_TEXT_H
#include <graphics/text.h>
#endif
#ifndef GRAPHICS_DISPLAYINFO_H
#include <graphics/displayinfo.h>
#endif
#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif

#define AslName		"asl.library"
#define ASL_TB		(TAG_USER + 0x80000)

/* AllocAslRequest()'s kinds */
#define ASL_FileRequest		0
#define ASL_FontRequest		1
#define ASL_ScreenModeRequest	2

/* ---- The file requester ---------------------------------------------- */

struct FileRequester
{
    UBYTE fr_Reserved0[4];
    STRPTR fr_File;			/* the file chosen */
    STRPTR fr_Drawer;			/* and its drawer */
    UBYTE fr_Reserved1[10];
    WORD fr_LeftEdge;			/* where the window was */
    WORD fr_TopEdge;
    WORD fr_Width;
    WORD fr_Height;
    UBYTE fr_Reserved2[2];
    LONG fr_NumArgs;			/* multiple selection's results */
    struct WBArg *fr_ArgList;
    APTR fr_UserData;
    UBYTE fr_Reserved3[8];
    STRPTR fr_Pattern;			/* the pattern last used */
};

/* ASLFR_Flags1 */
#define FRB_FILTERFUNC		7
#define FRB_INTUIFUNC		6
#define FRB_DOSAVEMODE		5
#define FRB_PRIVATEIDCMP	4
#define FRB_DOMULTISELECT	3
#define FRB_DOPATTERNS		0

#define FRF_FILTERFUNC		(1L << FRB_FILTERFUNC)
#define FRF_INTUIFUNC		(1L << FRB_INTUIFUNC)
#define FRF_DOSAVEMODE		(1L << FRB_DOSAVEMODE)
#define FRF_PRIVATEIDCMP	(1L << FRB_PRIVATEIDCMP)
#define FRF_DOMULTISELECT	(1L << FRB_DOMULTISELECT)
#define FRF_DOPATTERNS		(1L << FRB_DOPATTERNS)

/* ASLFR_Flags2 */
#define FRB_DRAWERSONLY		0
#define FRB_FILTERDRAWERS	1
#define FRB_REJECTICONS		2

#define FRF_DRAWERSONLY		(1L << FRB_DRAWERSONLY)
#define FRF_FILTERDRAWERS	(1L << FRB_FILTERDRAWERS)
#define FRF_REJECTICONS		(1L << FRB_REJECTICONS)

/* ---- The font requester ---------------------------------------------- */

struct FontRequester
{
    APTR fo_Reserved0[2];
    struct TextAttr fo_Attr;		/* the font chosen */
    UBYTE fo_FrontPen;
    UBYTE fo_BackPen;
    UBYTE fo_DrawMode;
    UBYTE fo_SpecialDrawMode;
    APTR fo_UserData;
    WORD fo_LeftEdge;
    WORD fo_TopEdge;
    WORD fo_Width;
    WORD fo_Height;
    struct TTextAttr fo_TAttr;		/* fo_Attr with its tags */
};

/* ASLFO_Flags */
#define FOB_DOFRONTPEN		0
#define FOB_DOBACKPEN		1
#define FOB_DOSTYLE		2
#define FOB_DODRAWMODE		3
#define FOB_FIXEDWIDTHONLY	4
#define FOB_PRIVATEIDCMP	5
#define FOB_INTUIFUNC		6
#define FOB_FILTERFUNC		7

#define FOF_DOFRONTPEN		(1L << FOB_DOFRONTPEN)
#define FOF_DOBACKPEN		(1L << FOB_DOBACKPEN)
#define FOF_DOSTYLE		(1L << FOB_DOSTYLE)
#define FOF_DODRAWMODE		(1L << FOB_DODRAWMODE)
#define FOF_FIXEDWIDTHONLY	(1L << FOB_FIXEDWIDTHONLY)
#define FOF_PRIVATEIDCMP	(1L << FOB_PRIVATEIDCMP)
#define FOF_INTUIFUNC		(1L << FOB_INTUIFUNC)
#define FOF_FILTERFUNC		(1L << FOB_FILTERFUNC)

/* ---- The screen mode requester --------------------------------------- */

struct ScreenModeRequester
{
    ULONG sm_DisplayID;
    ULONG sm_DisplayWidth;
    ULONG sm_DisplayHeight;
    UWORD sm_DisplayDepth;
    UWORD sm_OverscanType;
    BOOL sm_AutoScroll;

    ULONG sm_BitMapWidth;		/* at least the display's size */
    ULONG sm_BitMapHeight;

    WORD sm_LeftEdge;
    WORD sm_TopEdge;
    WORD sm_Width;
    WORD sm_Height;

    BOOL sm_InfoOpened;			/* the mode's properties window */
    WORD sm_InfoLeftEdge;
    WORD sm_InfoTopEdge;
    WORD sm_InfoWidth;
    WORD sm_InfoHeight;

    APTR sm_UserData;
};

/* An entry of ASLSM_CustomSMList */
struct DisplayMode
{
    struct Node dm_Node;		/* ln_Name is what the list shows */
    struct DimensionInfo dm_DimensionInfo;
    ULONG dm_PropertyFlags;		/* DIPF_ */
};

/* ---- Tags common to the three requesters ------------------------------ */

/* The window */
#define ASLFR_Window		(ASL_TB + 2)
#define ASLFR_Screen		(ASL_TB + 40)
#define ASLFR_PubScreenName	(ASL_TB + 41)
#define ASLFR_PrivateIDCMP	(ASL_TB + 42)
#define ASLFR_IntuiMsgFunc	(ASL_TB + 70)
#define ASLFR_SleepWindow	(ASL_TB + 43)
#define ASLFR_UserData		(ASL_TB + 52)
#define ASLFR_PopToFront	(ASL_TB + 131)	/* V44 */
#define ASLFR_Activate		(ASL_TB + 132)	/* V45 */

/* Text */
#define ASLFR_TextAttr		(ASL_TB + 51)
#define ASLFR_Locale		(ASL_TB + 50)
#define ASLFR_TitleText		(ASL_TB + 1)
#define ASLFR_PositiveText	(ASL_TB + 18)
#define ASLFR_NegativeText	(ASL_TB + 19)

/* The window's box */
#define ASLFR_InitialLeftEdge	(ASL_TB + 3)
#define ASLFR_InitialTopEdge	(ASL_TB + 4)
#define ASLFR_InitialWidth	(ASL_TB + 5)
#define ASLFR_InitialHeight	(ASL_TB + 6)

/* The file requester's own */
#define ASLFR_InitialFile	(ASL_TB + 8)
#define ASLFR_InitialDrawer	(ASL_TB + 9)
#define ASLFR_InitialPattern	(ASL_TB + 10)
#define ASLFR_InitialShowVolumes (ASL_TB + 130)	/* V44 */

#define ASLFR_Flags1		(ASL_TB + 20)	/* FRF_ */
#define ASLFR_Flags2		(ASL_TB + 22)
#define ASLFR_DoSaveMode	(ASL_TB + 44)
#define ASLFR_DoMultiSelect	(ASL_TB + 45)
#define ASLFR_DoPatterns	(ASL_TB + 46)

#define ASLFR_DrawersOnly	(ASL_TB + 47)
#define ASLFR_FilterFunc	(ASL_TB + 49)
#define ASLFR_RejectIcons	(ASL_TB + 60)
#define ASLFR_RejectPattern	(ASL_TB + 61)
#define ASLFR_AcceptPattern	(ASL_TB + 62)
#define ASLFR_FilterDrawers	(ASL_TB + 63)
#define ASLFR_HookFunc		(ASL_TB + 7)

/* Sorting (V44) */
#define ASLFR_SetSortBy		(ASL_TB + 124)
#define ASLFR_GetSortBy		(ASL_TB + 125)
#define ASLFR_SetSortDrawers	(ASL_TB + 126)
#define ASLFR_GetSortDrawers	(ASL_TB + 127)
#define ASLFR_SetSortOrder	(ASL_TB + 128)
#define ASLFR_GetSortOrder	(ASL_TB + 129)

#define ASLFRSORTBY_Name	0
#define ASLFRSORTBY_Date	1
#define ASLFRSORTBY_Size	2

#define ASLFRSORTDRAWERS_First	0
#define ASLFRSORTDRAWERS_Mix	1
#define ASLFRSORTDRAWERS_Last	2

#define ASLFRSORTORDER_Ascend	0
#define ASLFRSORTORDER_Descend	1

/* ---- The font requester's tags ---------------------------------------- */

#define ASLFO_Window		ASLFR_Window
#define ASLFO_Screen		ASLFR_Screen
#define ASLFO_PubScreenName	ASLFR_PubScreenName
#define ASLFO_PrivateIDCMP	ASLFR_PrivateIDCMP
#define ASLFO_IntuiMsgFunc	ASLFR_IntuiMsgFunc
#define ASLFO_SleepWindow	ASLFR_SleepWindow
#define ASLFO_UserData		ASLFR_UserData
#define ASLFO_PopToFront	ASLFR_PopToFront
#define ASLFO_Activate		ASLFR_Activate

#define ASLFO_TextAttr		ASLFR_TextAttr
#define ASLFO_Locale		ASLFR_Locale
#define ASLFO_TitleText		ASLFR_TitleText
#define ASLFO_PositiveText	ASLFR_PositiveText
#define ASLFO_NegativeText	ASLFR_NegativeText

#define ASLFO_InitialLeftEdge	ASLFR_InitialLeftEdge
#define ASLFO_InitialTopEdge	ASLFR_InitialTopEdge
#define ASLFO_InitialWidth	ASLFR_InitialWidth
#define ASLFO_InitialHeight	ASLFR_InitialHeight

#define ASLFO_InitialName	(ASL_TB + 10)
#define ASLFO_InitialSize	(ASL_TB + 11)
#define ASLFO_InitialStyle	(ASL_TB + 12)
#define ASLFO_InitialFlags	(ASL_TB + 13)
#define ASLFO_InitialFrontPen	(ASL_TB + 14)
#define ASLFO_InitialBackPen	(ASL_TB + 15)
#define ASLFO_InitialDrawMode	(ASL_TB + 59)

#define ASLFO_Flags		(ASL_TB + 20)	/* FOF_ */
#define ASLFO_DoFrontPen	(ASL_TB + 44)
#define ASLFO_DoBackPen		(ASL_TB + 45)
#define ASLFO_DoStyle		(ASL_TB + 46)
#define ASLFO_DoDrawMode	(ASL_TB + 47)
#define ASLFO_SampleText	(ASL_TB + 133)	/* V45 */

#define ASLFO_FixedWidthOnly	(ASL_TB + 48)
#define ASLFO_MinHeight		(ASL_TB + 16)
#define ASLFO_MaxHeight		(ASL_TB + 17)
#define ASLFO_FilterFunc	(ASL_TB + 49)
#define ASLFO_HookFunc		(ASL_TB + 7)
#define ASLFO_MaxFrontPen	(ASL_TB + 66)
#define ASLFO_MaxBackPen	(ASL_TB + 67)

#define ASLFO_ModeList		(ASL_TB + 21)
#define ASLFO_FrontPens		(ASL_TB + 64)
#define ASLFO_BackPens		(ASL_TB + 65)

/* ---- The screen mode requester's tags --------------------------------- */

#define ASLSM_Window		ASLFR_Window
#define ASLSM_Screen		ASLFR_Screen
#define ASLSM_PubScreenName	ASLFR_PubScreenName
#define ASLSM_PrivateIDCMP	ASLFR_PrivateIDCMP
#define ASLSM_IntuiMsgFunc	ASLFR_IntuiMsgFunc
#define ASLSM_SleepWindow	ASLFR_SleepWindow
#define ASLSM_UserData		ASLFR_UserData
#define ASLSM_PopToFront	ASLFR_PopToFront
#define ASLSM_Activate		ASLFR_Activate

#define ASLSM_TextAttr		ASLFR_TextAttr
#define ASLSM_Locale		ASLFR_Locale
#define ASLSM_TitleText		ASLFR_TitleText
#define ASLSM_PositiveText	ASLFR_PositiveText
#define ASLSM_NegativeText	ASLFR_NegativeText

#define ASLSM_InitialLeftEdge	ASLFR_InitialLeftEdge
#define ASLSM_InitialTopEdge	ASLFR_InitialTopEdge
#define ASLSM_InitialWidth	ASLFR_InitialWidth
#define ASLSM_InitialHeight	ASLFR_InitialHeight

#define ASLSM_InitialDisplayID		(ASL_TB + 100)
#define ASLSM_InitialDisplayWidth	(ASL_TB + 101)
#define ASLSM_InitialDisplayHeight	(ASL_TB + 102)
#define ASLSM_InitialDisplayDepth	(ASL_TB + 103)
#define ASLSM_InitialOverscanType	(ASL_TB + 104)
#define ASLSM_InitialAutoScroll		(ASL_TB + 105)
#define ASLSM_InitialInfoOpened		(ASL_TB + 106)
#define ASLSM_InitialInfoLeftEdge	(ASL_TB + 107)
#define ASLSM_InitialInfoTopEdge	(ASL_TB + 108)

#define ASLSM_DoWidth		(ASL_TB + 109)
#define ASLSM_DoHeight		(ASL_TB + 110)
#define ASLSM_DoDepth		(ASL_TB + 111)
#define ASLSM_DoOverscanType	(ASL_TB + 112)
#define ASLSM_DoAutoScroll	(ASL_TB + 113)

#define ASLSM_PropertyFlags	(ASL_TB + 114)
#define ASLSM_PropertyMask	(ASL_TB + 115)
#define ASLSM_MinWidth		(ASL_TB + 116)
#define ASLSM_MaxWidth		(ASL_TB + 117)
#define ASLSM_MinHeight		(ASL_TB + 118)
#define ASLSM_MaxHeight		(ASL_TB + 119)
#define ASLSM_MinDepth		(ASL_TB + 120)
#define ASLSM_MaxDepth		(ASL_TB + 121)
#define ASLSM_FilterFunc	(ASL_TB + 122)

#define ASLSM_CustomSMList	(ASL_TB + 123)	/* a List of DisplayMode */

/* ---- The V36 interface ------------------------------------------------ */

/* The old generic tags, same numbers as the ones above */
#define ASL_Dummy	(TAG_USER + 0x80000)
#define ASL_Hail	(ASL_Dummy + 1)
#define ASL_Window	(ASL_Dummy + 2)
#define ASL_LeftEdge	(ASL_Dummy + 3)
#define ASL_TopEdge	(ASL_Dummy + 4)
#define ASL_Width	(ASL_Dummy + 5)
#define ASL_Height	(ASL_Dummy + 6)
#define ASL_HookFunc	(ASL_Dummy + 7)
#define ASL_File	(ASL_Dummy + 8)
#define ASL_Dir		(ASL_Dummy + 9)
#define ASL_FontName	(ASL_Dummy + 10)
#define ASL_FontHeight	(ASL_Dummy + 11)
#define ASL_FontStyles	(ASL_Dummy + 12)
#define ASL_FontFlags	(ASL_Dummy + 13)
#define ASL_FrontPen	(ASL_Dummy + 14)
#define ASL_BackPen	(ASL_Dummy + 15)
#define ASL_MinHeight	(ASL_Dummy + 16)
#define ASL_MaxHeight	(ASL_Dummy + 17)
#define ASL_OKText	(ASL_Dummy + 18)
#define ASL_CancelText	(ASL_Dummy + 19)
#define ASL_FuncFlags	(ASL_Dummy + 20)
#define ASL_ModeList	(ASL_Dummy + 21)
#define ASL_ExtFlags1	(ASL_Dummy + 22)
#define ASL_Pattern	ASL_FontName

/* The old field names */
#define rf_File		fr_File
#define rf_Dir		fr_Drawer
#define rf_LeftEdge	fr_LeftEdge
#define rf_TopEdge	fr_TopEdge
#define rf_Width	fr_Width
#define rf_Height	fr_Height
#define rf_NumArgs	fr_NumArgs
#define rf_ArgList	fr_ArgList
#define rf_UserData	fr_UserData
#define rf_Pat		fr_Pattern

/* The old flag names: ASL_FuncFlags for files */
#define FILB_DOWILDFUNC	7
#define FILB_DOMSGFUNC	6
#define FILB_SAVE	5
#define FILB_NEWIDCMP	4
#define FILB_MULTISELECT 3
#define FILB_PATGAD	0

#define FILF_DOWILDFUNC	(1L << FILB_DOWILDFUNC)
#define FILF_DOMSGFUNC	(1L << FILB_DOMSGFUNC)
#define FILF_SAVE	(1L << FILB_SAVE)
#define FILF_NEWIDCMP	(1L << FILB_NEWIDCMP)
#define FILF_MULTISELECT (1L << FILB_MULTISELECT)
#define FILF_PATGAD	(1L << FILB_PATGAD)

/* ASL_ExtFlags1 */
#define FIL1B_NOFILES	0
#define FIL1B_MATCHDIRS	1

#define FIL1F_NOFILES	(1L << FIL1B_NOFILES)
#define FIL1F_MATCHDIRS	(1L << FIL1B_MATCHDIRS)

/* ASL_FuncFlags for fonts */
#define FONB_FRONTCOLOR	0
#define FONB_BACKCOLOR	1
#define FONB_STYLES	2
#define FONB_DRAWMODE	3
#define FONB_FIXEDWIDTH	4
#define FONB_NEWIDCMP	5
#define FONB_DOMSGFUNC	6
#define FONB_DOWILDFUNC	7

#define FONF_FRONTCOLOR	(1L << FONB_FRONTCOLOR)
#define FONF_BACKCOLOR	(1L << FONB_BACKCOLOR)
#define FONF_STYLES	(1L << FONB_STYLES)
#define FONF_DRAWMODE	(1L << FONB_DRAWMODE)
#define FONF_FIXEDWIDTH	(1L << FONB_FIXEDWIDTH)
#define FONF_NEWIDCMP	(1L << FONB_NEWIDCMP)
#define FONF_DOMSGFUNC	(1L << FONB_DOMSGFUNC)
#define FONF_DOWILDFUNC	(1L << FONB_DOWILDFUNC)

/* The semaphore ASL publishes with its current preferences, under this name */
#define ASL_SEMAPHORE_NAME	"asl.library"

struct AslSemaphore
{
    struct SignalSemaphore as_Semaphore;
    UWORD as_Version;
    ULONG as_Size;			/* of this structure */
    UBYTE as_SortBy;			/* ASLSORTBY_ */
    UBYTE as_SortDrawers;
    UBYTE as_SortOrder;
    UBYTE as_SizePosition;
    WORD as_RelativeLeft;
    WORD as_RelativeTop;
    UBYTE as_RelativeWidth;
    UBYTE as_RelativeHeight;
};

/* More names from the 3.2 interface */
#define ASLFO_CSFilterFunc	(ASL_Dummy + 138)
#define ASLFO_DoCharSet		(ASL_Dummy + 135)
#define ASLFO_DoSpecialMode	(ASL_Dummy + 140)
#define ASLFO_InitialCharSet	(ASL_Dummy + 134)
#define ASLFO_InitialSpecMode	(ASL_Dummy + 139)
#define ASLFO_OTagOnly		(ASL_Dummy + 136)
#define ASLFO_ScalableOnly	(ASL_Dummy + 137)
#define ASLOPTION_ASLOverrides	64
#define ASLPOS_CenterMouse	5
#define ASLPOS_CenterScreen	2
#define ASLPOS_CenterWindow	1
#define ASLPOS_DefaultPosition	0
#define ASLPOS_MASK		15
#define ASLPOS_ScreenPosition	4
#define ASLPOS_WindowPosition	3
#define ASLSIZE_DefaultSize	0
#define ASLSIZE_MASK		48
#define ASLSIZE_RelativeSize	16
#define ASL_LAST_TAG		(ASL_Dummy + 140)
#define FO_SPECIALMODE_NONE	0
#define FO_SPECIALMODE_OUTLINE	1
#define FO_SPECIALMODE_SHADOW	2

#define ASL_SEMAPHORE_NAME	"asl.library"

#endif /* LIBRARIES_ASL_H */
