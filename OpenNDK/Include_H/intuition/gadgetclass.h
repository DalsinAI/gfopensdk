#ifndef INTUITION_GADGETCLASS_H
#define INTUITION_GADGETCLASS_H
/*
 * OpenNDK: gadgetclass and the built-in gadget classes: their tags,
 * methods and method messages.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* ---- gadgetclass's attributes ----------------------------------------- */

#define GA_Dummy		(TAG_USER + 0x30000)

#define GA_Left			(GA_Dummy + 0x0001)
#define GA_RelRight		(GA_Dummy + 0x0002)
#define GA_Top			(GA_Dummy + 0x0003)
#define GA_RelBottom		(GA_Dummy + 0x0004)
#define GA_Width		(GA_Dummy + 0x0005)
#define GA_RelWidth		(GA_Dummy + 0x0006)
#define GA_Height		(GA_Dummy + 0x0007)
#define GA_RelHeight		(GA_Dummy + 0x0008)
#define GA_Text			(GA_Dummy + 0x0009)
#define GA_Image		(GA_Dummy + 0x000A)
#define GA_Border		(GA_Dummy + 0x000B)
#define GA_SelectRender		(GA_Dummy + 0x000C)
#define GA_Highlight		(GA_Dummy + 0x000D)
#define GA_Disabled		(GA_Dummy + 0x000E)
#define GA_GZZGadget		(GA_Dummy + 0x000F)
#define GA_ID			(GA_Dummy + 0x0010)
#define GA_UserData		(GA_Dummy + 0x0011)
#define GA_SpecialInfo		(GA_Dummy + 0x0012)
#define GA_Selected		(GA_Dummy + 0x0013)
#define GA_EndGadget		(GA_Dummy + 0x0014)
#define GA_Immediate		(GA_Dummy + 0x0015)
#define GA_RelVerify		(GA_Dummy + 0x0016)
#define GA_FollowMouse		(GA_Dummy + 0x0017)
#define GA_RightBorder		(GA_Dummy + 0x0018)
#define GA_LeftBorder		(GA_Dummy + 0x0019)
#define GA_TopBorder		(GA_Dummy + 0x001A)
#define GA_BottomBorder		(GA_Dummy + 0x001B)
#define GA_ToggleSelect		(GA_Dummy + 0x001C)
#define GA_SysGadget		(GA_Dummy + 0x001D)
#define GA_SysGType		(GA_Dummy + 0x001E)
#define GA_Previous		(GA_Dummy + 0x001F)
#define GA_Next			(GA_Dummy + 0x0020)
#define GA_DrawInfo		(GA_Dummy + 0x0021)
#define GA_IntuiText		(GA_Dummy + 0x0022)
#define GA_LabelImage		(GA_Dummy + 0x0023)
#define GA_TabCycle		(GA_Dummy + 0x0024)
#define GA_GadgetHelp		(GA_Dummy + 0x0025)
#define GA_Bounds		(GA_Dummy + 0x0026)
#define GA_RelSpecial		(GA_Dummy + 0x0027)
#define GA_TextAttr		(GA_Dummy + 0x0028)	/* V42 */
#define GA_ReadOnly		(GA_Dummy + 0x0029)	/* V42 */
#define GA_Underscore		(GA_Dummy + 0x002A)	/* V44 */
#define GA_ActivateKey		(GA_Dummy + 0x002B)	/* V44 */
#define GA_BackFill		(GA_Dummy + 0x002C)	/* V44 */
#define GA_GadgetHelpText	(GA_Dummy + 0x002D)	/* V44 */
#define GA_UserInput		(GA_Dummy + 0x002E)	/* V44 */

/* ---- propgclass ------------------------------------------------------- */

#define PGA_Dummy		(TAG_USER + 0x31000)

#define PGA_Freedom		(PGA_Dummy + 0x0001)	/* FREEHORIZ or FREEVERT */
#define PGA_Borderless		(PGA_Dummy + 0x0002)
#define PGA_HorizPot		(PGA_Dummy + 0x0003)
#define PGA_HorizBody		(PGA_Dummy + 0x0004)
#define PGA_VertPot		(PGA_Dummy + 0x0005)
#define PGA_VertBody		(PGA_Dummy + 0x0006)
#define PGA_Total		(PGA_Dummy + 0x0007)
#define PGA_Visible		(PGA_Dummy + 0x0008)
#define PGA_Top			(PGA_Dummy + 0x0009)
#define PGA_NewLook		(PGA_Dummy + 0x000A)	/* V39 */

/* ---- strgclass -------------------------------------------------------- */

#define STRINGA_Dummy		(TAG_USER + 0x32000)

#define STRINGA_MaxChars	(STRINGA_Dummy + 0x0001)
#define STRINGA_Buffer		(STRINGA_Dummy + 0x0002)
#define STRINGA_UndoBuffer	(STRINGA_Dummy + 0x0003)
#define STRINGA_WorkBuffer	(STRINGA_Dummy + 0x0004)
#define STRINGA_BufferPos	(STRINGA_Dummy + 0x0005)
#define STRINGA_DispPos		(STRINGA_Dummy + 0x0006)
#define STRINGA_AltKeyMap	(STRINGA_Dummy + 0x0007)
#define STRINGA_Font		(STRINGA_Dummy + 0x0008)
#define STRINGA_Pens		(STRINGA_Dummy + 0x0009)
#define STRINGA_ActivePens	(STRINGA_Dummy + 0x000A)
#define STRINGA_EditHook	(STRINGA_Dummy + 0x000B)
#define STRINGA_EditModes	(STRINGA_Dummy + 0x000C)
#define STRINGA_ReplaceMode	(STRINGA_Dummy + 0x000D)
#define STRINGA_FixedFieldMode	(STRINGA_Dummy + 0x000E)
#define STRINGA_NoFilterMode	(STRINGA_Dummy + 0x000F)
#define STRINGA_Justification	(STRINGA_Dummy + 0x0010)	/* GACT_STRINGLEFT and friends */
#define STRINGA_LongVal		(STRINGA_Dummy + 0x0011)
#define STRINGA_TextVal		(STRINGA_Dummy + 0x0012)
#define STRINGA_ExitHelp	(STRINGA_Dummy + 0x0013)	/* V37 */

/* The buffer size when STRINGA_MaxChars isn't given */
#define SG_DEFAULTMAXCHARS	(128)

/* ---- groupgclass layout ----------------------------------------------- */

#define LAYOUTA_Dummy		(TAG_USER + 0x38000)
#define LAYOUTA_LayoutObj	(LAYOUTA_Dummy + 0x0001)
#define LAYOUTA_Spacing		(LAYOUTA_Dummy + 0x0002)
#define LAYOUTA_Orientation	(LAYOUTA_Dummy + 0x0003)
#define LAYOUTA_ChildMaxWidth	(LAYOUTA_Dummy + 0x0004)	/* V42 */
#define LAYOUTA_ChildMaxHeight	(LAYOUTA_Dummy + 0x0005)	/* V42 */

/* LAYOUTA_Orientation's values */
#define LORIENT_NONE	0
#define LORIENT_HORIZ	1
#define LORIENT_VERT	2

/* ---- gadgetclass's methods ------------------------------------------- */

#define GM_Dummy	(-1)
#define GM_HITTEST	(0)
#define GM_RENDER	(1)
#define GM_GOACTIVE	(2)
#define GM_HANDLEINPUT	(3)
#define GM_GOINACTIVE	(4)
#define GM_HELPTEST	(5)	/* V39 */
#define GM_LAYOUT	(6)	/* V39 */
#define GM_DOMAIN	(7)	/* V42 */
#define GM_KEYTEST	(8)	/* V44 */
#define GM_KEYGOACTIVE	(9)	/* V44 */
#define GM_KEYGOINACTIVE (10)	/* V44 */

/* GM_HITTEST and GM_HELPTEST */
struct gpHitTest
{
    ULONG MethodID;
    struct GadgetInfo *gpht_GInfo;
    struct
    {
	WORD X;
	WORD Y;
    } gpht_Mouse;			/* relative to the gadget */
};

/* GM_HITTEST's answers */
#define GMR_GADGETHIT	(0x00000004)

/* GM_HELPTEST's answers */
#define GMR_NOHELPHIT	(0x00000000)
#define GMR_HELPHIT	(0xFFFFFFFF)
#define GMR_HELPCODE	(0x00010000)	/* the low word is the code */

/* GM_RENDER */
struct gpRender
{
    ULONG MethodID;
    struct GadgetInfo *gpr_GInfo;
    struct RastPort *gpr_RPort;
    LONG gpr_Redraw;
};

/* gpr_Redraw */
#define GREDRAW_UPDATE	(2)
#define GREDRAW_REDRAW	(1)
#define GREDRAW_TOGGLE	(0)

/* GM_GOACTIVE and GM_HANDLEINPUT */
struct gpInput
{
    ULONG MethodID;
    struct GadgetInfo *gpi_GInfo;
    struct InputEvent *gpi_IEvent;
    LONG *gpi_Termination;		/* IDCMP_GADGETUP's Code */
    struct
    {
	WORD X;
	WORD Y;
    } gpi_Mouse;
    struct TabletData *gpi_TabletData;	/* V39; NULL without a tablet */
};

/* GM_GOACTIVE's and GM_HANDLEINPUT's answers */
#define GMR_MEACTIVE	(0)
#define GMR_NOREUSE	(1 << 1)
#define GMR_REUSE	(1 << 2)
#define GMR_VERIFY	(1 << 3)
#define GMR_NEXTACTIVE	(1 << 4)	/* V37 */
#define GMR_PREVACTIVE	(1 << 5)	/* V37 */

/* GM_GOINACTIVE */
struct gpGoInactive
{
    ULONG MethodID;
    struct GadgetInfo *gpgi_GInfo;
    ULONG gpgi_Abort;			/* V37: 1 if Intuition took it away */
};

/* GM_LAYOUT */
struct gpLayout
{
    ULONG MethodID;
    struct GadgetInfo *gpl_GInfo;
    ULONG gpl_Initial;			/* set the first time */
};

/* GM_DOMAIN */
struct gpDomain
{
    ULONG MethodID;
    struct GadgetInfo *gpd_GInfo;
    struct RastPort *gpd_RPort;
    LONG gpd_Which;
    struct IBox gpd_Domain;		/* filled in by the gadget */
    struct TagItem *gpd_Attrs;
};

/* gpd_Which */
#define GDOMAIN_MINIMUM	(0)
#define GDOMAIN_NOMINAL	(1)
#define GDOMAIN_MAXIMUM	(2)

/* GM_KEYTEST */
struct gpKeyTest
{
    ULONG MethodID;
    struct GadgetInfo *gpkt_GInfo;
    struct IntuiMessage *gpkt_IMsg;
    ULONG gpkt_VanillaKey;
};

/* GM_KEYGOACTIVE */
struct gpKeyInput
{
    ULONG MethodID;
    struct GadgetInfo *gpk_GInfo;
    struct InputEvent *gpk_IEvent;
    LONG *gpk_Termination;
};

/* GM_KEYGOINACTIVE */
struct gpKeyGoInactive
{
    ULONG MethodID;
    struct GadgetInfo *gpki_GInfo;
    ULONG gpki_Abort;
};

/* More names from the 3.2 interface */
#define GA_CustomMousePointer	(GA_Dummy + 60)
#define GA_Hidden		(GA_Dummy + 54)
#define GA_ParentHidden		(GA_Dummy + 62)
#define GA_PointerType		(GA_Dummy + 61)
#define GMR_KEYACTIVE		16
#define GMR_KEYVERIFY		32
#define GM_HANDLESCROLL		14
#define GM_QUERYHOVERED		15
#define PGA_KnobImage		(PGA_Dummy + 13)

#ifndef INTUITION_IOBSOLETE_H
#include <intuition/iobsolete.h>
#endif

#endif /* INTUITION_GADGETCLASS_H */
