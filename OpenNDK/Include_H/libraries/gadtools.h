#ifndef LIBRARIES_GADTOOLS_H
#define LIBRARIES_GADTOOLS_H
/*
 * OpenNDK: gadtools.library's gadget kinds, NewGadget and NewMenu, and
 * the tags its calls take.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

/* ---- Gadget kinds ----------------------------------------------------- */

#define GENERIC_KIND	0
#define BUTTON_KIND	1
#define CHECKBOX_KIND	2
#define INTEGER_KIND	3
#define LISTVIEW_KIND	4
#define MX_KIND		5
#define NUMBER_KIND	6
#define CYCLE_KIND	7
#define PALETTE_KIND	8
#define SCROLLER_KIND	9
/* 10 is not used */
#define SLIDER_KIND	11
#define STRING_KIND	12
#define TEXT_KIND	13

#define NUM_KINDS	14

/* The IDCMP classes each kind needs */
#define ARROWIDCMP	(IDCMP_GADGETUP | IDCMP_GADGETDOWN | \
			 IDCMP_INTUITICKS | IDCMP_MOUSEBUTTONS)

#define BUTTONIDCMP	(IDCMP_GADGETUP)
#define CHECKBOXIDCMP	(IDCMP_GADGETUP)
#define INTEGERIDCMP	(IDCMP_GADGETUP)
#define LISTVIEWIDCMP	(IDCMP_GADGETUP | IDCMP_GADGETDOWN | \
			 IDCMP_MOUSEMOVE | ARROWIDCMP)

#define MXIDCMP		(IDCMP_GADGETDOWN)
#define NUMBERIDCMP	(0L)
#define CYCLEIDCMP	(IDCMP_GADGETUP)
#define PALETTEIDCMP	(IDCMP_GADGETUP)

#define SCROLLERIDCMP	(IDCMP_GADGETUP | IDCMP_GADGETDOWN | IDCMP_MOUSEMOVE)
#define SLIDERIDCMP	(IDCMP_GADGETUP | IDCMP_GADGETDOWN | IDCMP_MOUSEMOVE)
#define STRINGIDCMP	(IDCMP_GADGETUP)

#define TEXTIDCMP	(0L)

/* ---- NewGadget -------------------------------------------------------- */

struct NewGadget
{
    WORD ng_LeftEdge, ng_TopEdge;
    WORD ng_Width, ng_Height;
    CONST_STRPTR ng_GadgetText;		/* the label */
    struct TextAttr *ng_TextAttr;
    UWORD ng_GadgetID;
    ULONG ng_Flags;			/* PLACETEXT_ and NG_ */
    APTR ng_VisualInfo;			/* from GetVisualInfo() */
    APTR ng_UserData;
};

/* ng_Flags: where the label goes */
#define PLACETEXT_LEFT	0x0001
#define PLACETEXT_RIGHT	0x0002
#define PLACETEXT_ABOVE	0x0004
#define PLACETEXT_BELOW	0x0008
#define PLACETEXT_IN	0x0010

#define NG_HIGHLABEL	0x0020		/* the label in the highlight pen */
#define NG_GRIDLAYOUT	0x0080		/* V47: the box is in design-font units */

/* ---- NewMenu ---------------------------------------------------------- */

struct NewMenu
{
    UBYTE nm_Type;			/* NM_ */
    CONST_STRPTR nm_Label;		/* text, or an Image with MENU_IMAGE */
    CONST_STRPTR nm_CommKey;
    UWORD nm_Flags;
    LONG nm_MutualExclude;
    APTR nm_UserData;
};

/* nm_Type */
#define MENU_IMAGE	128

#define NM_TITLE	1
#define NM_ITEM		2
#define NM_SUB		3

#define IM_ITEM		(NM_ITEM | MENU_IMAGE)
#define IM_SUB		(NM_SUB | MENU_IMAGE)

#define NM_END		0		/* the array's end */
#define NM_IGNORE	64		/* skip this entry */

/* nm_Label of a separator line */
#define NM_BARLABEL	((STRPTR)-1)

/* nm_Flags, beside the MenuItem flags */
#define NM_MENUDISABLED	MENUENABLED
#define NM_ITEMDISABLED	ITEMENABLED

#define NM_COMMANDSTRING COMMSEQ	/* nm_CommKey is a whole string */

/* The MenuItem flags nm_Flags may carry */
#define NM_FLAGMASK	(~(COMMSEQ | ITEMTEXT | HIGHFLAGS))
#define NM_FLAGMASK_V39	(~(ITEMTEXT | HIGHFLAGS))

/* The nm_UserData GadTools stores just past each Menu and MenuItem */
#define GTMENU_USERDATA(menu)		(*((APTR *)(((struct Menu *)(menu)) + 1)))
#define GTMENUITEM_USERDATA(menuitem)	(*((APTR *)(((struct MenuItem *)(menuitem)) + 1)))

/* GTMN_SecondaryError's answers */
#define GTMENU_TRIMMED	0x00000001	/* too many menus, items or sub-items */
#define GTMENU_INVALID	0x00000002	/* the NewMenu array is malformed */
#define GTMENU_NOMEM	0x00000003

/* ---- Tags ------------------------------------------------------------- */

#define GT_TagBase	(TAG_USER + 0x80000)

#define GTVI_NewWindow	(GT_TagBase + 1)
#define GTVI_NWTags	(GT_TagBase + 2)

#define GTCB_Checked	(GT_TagBase + 4)

#define GTLV_Top	(GT_TagBase + 5)
#define GTLV_Labels	(GT_TagBase + 6)
#define GTLV_ReadOnly	(GT_TagBase + 7)
#define GTLV_ScrollWidth (GT_TagBase + 8)

#define GTMX_Labels	(GT_TagBase + 9)
#define GTMX_Active	(GT_TagBase + 10)

#define GTTX_Text	(GT_TagBase + 11)
#define GTTX_CopyText	(GT_TagBase + 12)

#define GTNM_Number	(GT_TagBase + 13)

#define GTCY_Labels	(GT_TagBase + 14)
#define GTCY_Active	(GT_TagBase + 15)

#define GTPA_Depth	(GT_TagBase + 16)
#define GTPA_Color	(GT_TagBase + 17)
#define GTPA_ColorOffset (GT_TagBase + 18)
#define GTPA_IndicatorWidth (GT_TagBase + 19)
#define GTPA_IndicatorHeight (GT_TagBase + 20)

#define GTSC_Top	(GT_TagBase + 21)
#define GTSC_Total	(GT_TagBase + 22)
#define GTSC_Visible	(GT_TagBase + 23)
#define GTSC_Overlap	(GT_TagBase + 24)

/* 25 to 37 are not used */

#define GTSL_Min	(GT_TagBase + 38)
#define GTSL_Max	(GT_TagBase + 39)
#define GTSL_Level	(GT_TagBase + 40)
#define GTSL_MaxLevelLen (GT_TagBase + 41)
#define GTSL_LevelFormat (GT_TagBase + 42)
#define GTSL_LevelPlace	(GT_TagBase + 43)
#define GTSL_DispFunc	(GT_TagBase + 44)

#define GTST_String	(GT_TagBase + 45)
#define GTST_MaxChars	(GT_TagBase + 46)

#define GTIN_Number	(GT_TagBase + 47)
#define GTIN_MaxChars	(GT_TagBase + 48)

#define GTMN_TextAttr	(GT_TagBase + 49)
#define GTMN_FrontPen	(GT_TagBase + 50)

#define GTBB_Recessed	(GT_TagBase + 51)

#define GT_VisualInfo	(GT_TagBase + 52)

#define GTLV_ShowSelected (GT_TagBase + 53)
#define GTLV_Selected	(GT_TagBase + 54)

#define GTTX_Border	(GT_TagBase + 57)
#define GTNM_Border	(GT_TagBase + 58)

#define GTSC_Arrows	(GT_TagBase + 59)

#define GTMN_Menu	(GT_TagBase + 60)
#define GTMX_Spacing	(GT_TagBase + 61)

/* V37 */
#define GTMN_FullMenu	(GT_TagBase + 62)
#define GTMN_SecondaryError (GT_TagBase + 63)
#define GT_Underscore	(GT_TagBase + 64)
#define GTST_EditHook	(GT_TagBase + 55)
#define GTIN_EditHook	GTST_EditHook

/* V39 */
#define GTMN_Checkmark	(GT_TagBase + 65)
#define GTMN_AmigaKey	(GT_TagBase + 66)
#define GTMN_NewLookMenus (GT_TagBase + 67)

#define GTCB_Scaled	(GT_TagBase + 68)
#define GTMX_Scaled	(GT_TagBase + 69)

#define GTPA_NumColors	(GT_TagBase + 70)

#define GTMX_TitlePlace	(GT_TagBase + 71)

#define GTTX_FrontPen	(GT_TagBase + 72)
#define GTTX_BackPen	(GT_TagBase + 73)
#define GTTX_Justification (GT_TagBase + 74)

#define GTNM_FrontPen	(GT_TagBase + 72)
#define GTNM_BackPen	(GT_TagBase + 73)
#define GTNM_Justification (GT_TagBase + 74)
#define GTNM_Format	(GT_TagBase + 75)
#define GTNM_MaxNumberLen (GT_TagBase + 76)

#define GTBB_FrameType	(GT_TagBase + 77)

#define GTLV_MakeVisible (GT_TagBase + 78)
#define GTLV_ItemHeight	(GT_TagBase + 79)

#define GTSL_MaxPixelLen (GT_TagBase + 80)
#define GTSL_Justification (GT_TagBase + 81)

#define GTPA_ColorTable	(GT_TagBase + 82)

#define GTLV_CallBack	(GT_TagBase + 83)
#define GTLV_MaxPen	(GT_TagBase + 84)

#define GTTX_Clipped	(GT_TagBase + 85)
#define GTNM_Clipped	(GT_TagBase + 85)

/* V47: the grid layout (SetDesignFontA, NG_GRIDLAYOUT) */
#define GTBB_Scale	(GT_TagBase + 92)
#define GTVI_LeftBorder	(GT_TagBase + 96)
#define GTVI_TopBorder	(GT_TagBase + 97)
#define GTVI_AlignRight	(GT_TagBase + 98)
#define GTVI_AlignBottom (GT_TagBase + 99)
#define GTVI_MinFontWidth (GT_TagBase + 100)
#define GTVI_MinFontHeight (GT_TagBase + 101)

/* Text and number justification */
#define GTJ_LEFT	0
#define GTJ_RIGHT	1
#define GTJ_CENTER	2

/* GTBB_FrameType */
#define BBFT_BUTTON	1
#define BBFT_RIDGE	2
#define BBFT_ICONDROPBOX 3

/* Suggested spacing between gadgets */
#define INTERWIDTH	8
#define INTERHEIGHT	4

/* The fixed sizes of unscaled checkboxes and radio buttons */
#define CHECKBOXWIDTH	26
#define CHECKBOXHEIGHT	11
#define MXWIDTH		17
#define MXHEIGHT	9

/* ---- Listview call-back (GTLV_CallBack) ------------------------------ */

/* The method a list view's item hook is called with */
#define LV_DRAW		(0x202)

/* The hook's answers */
#define LVCB_OK		(0)
#define LVCB_UNKNOWN	(1)

/* How to draw the item */
#define LVR_NORMAL		(0)
#define LVR_SELECTED		(1)
#define LVR_NORMALDISABLED	(2)
#define LVR_SELECTEDDISABLED	(8)

struct LVDrawMsg
{
    ULONG lvdm_MethodID;		/* LV_DRAW */
    struct RastPort *lvdm_RastPort;
    struct DrawInfo *lvdm_DrawInfo;
    struct Rectangle lvdm_Bounds;
    ULONG lvdm_State;			/* LVR_ */
};

/* More names from the 3.2 interface */
#define BBFT_CTXTFRAME		7
#define BBFT_DISPLAY		6
#define CHECKBOX_HEIGHT		11
#define CHECKBOX_WIDTH		26
#define GADTOOLBIT		0x8000
#define GADTOOLMASK		(-32769)
#define GTBB_Headline		(GT_TagBase + 93)
#define GTBB_HeadlineFont	(GT_TagBase + 95)
#define GTBB_HeadlinePen	(GT_TagBase + 94)
#define GTBB_reserved1		(GT_TagBase + 90)
#define GTLV_Total		(GT_TagBase + 92)
#define GTLV_Visible		(GT_TagBase + 93)
#define GTMN_reserved1		(GT_TagBase + 91)
#define GTMX_ScaledSpacing	(GT_TagBase + 102)
#define GTNW_Active		(GT_TagBase + 15)
#define GTNW_Labels		(GT_TagBase + 14)
#define GT_Private0		(GT_TagBase + 3)
#define GT_Reserved0		(GT_TagBase + 55)
#define GT_Reserved1		(GT_TagBase + 56)
#define MX_HEIGHT		9
#define MX_WIDTH		17
#define NWAYIDCMP		64
#define NWAY_KIND		7

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

/* the user data GadTools keeps right after a menu item */
#define MENU_USERDATA(menuitem)	(*(APTR *)((menuitem) + 1))

#endif /* LIBRARIES_GADTOOLS_H */
