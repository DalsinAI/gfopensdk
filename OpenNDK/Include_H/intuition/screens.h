#ifndef INTUITION_SCREENS_H
#define INTUITION_SCREENS_H
/*
 * OpenNDK: Intuition's screens, their DrawInfo pens, public screens and
 * the tags OpenScreenTagList() takes.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif
#ifndef GRAPHICS_CLIP_H
#include <graphics/clip.h>
#endif
#ifndef GRAPHICS_VIEW_H
#include <graphics/view.h>
#endif
#ifndef GRAPHICS_RASTPORT_H
#include <graphics/rastport.h>
#endif
#ifndef GRAPHICS_LAYERS_H
#include <graphics/layers.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* ---- DrawInfo: a screen's pens and look ------------------------------ */

#define DRI_VERSION	3		/* V47; 2 in V39, 1 in V36 */

struct DrawInfo
{
    UWORD dri_Version;
    UWORD dri_NumPens;
    UWORD *dri_Pens;			/* indexed by the pen numbers below */
    struct TextFont *dri_Font;
    UWORD dri_Depth;
    struct
    {
	UWORD X;
	UWORD Y;
    } dri_Resolution;
    ULONG dri_Flags;
    struct Image *dri_CheckMark;	/* V39 */
    struct Image *dri_AmigaKey;		/* V39 */
    struct Screen *dri_Screen;		/* V47 */
    ULONG dri_Reserved[4];
};

/* dri_Flags */
#define DRIF_NEWLOOK	0x00000001

/* Indices into dri_Pens */
#define DETAILPEN	0x0000
#define BLOCKPEN	0x0001
#define TEXTPEN		0x0002
#define SHINEPEN	0x0003
#define SHADOWPEN	0x0004
#define FILLPEN		0x0005
#define FILLTEXTPEN	0x0006
#define BACKGROUNDPEN	0x0007
#define HIGHLIGHTTEXTPEN 0x0008
#define BARDETAILPEN	0x0009		/* V39 */
#define BARBLOCKPEN	0x000A		/* V39 */
#define BARTRIMPEN	0x000B		/* V39 */
#define BARCONTOURPEN	0x000C		/* V47 */

#define NUMDRIPENS	0x000D

/* SA_Pens: the colours at the top of the palette, counted back from the last */
#define PEN_C3		0xFEFC
#define PEN_C2		0xFEFD
#define PEN_C1		0xFEFE
#define PEN_C0		0xFEFF

/* ---- The screen ------------------------------------------------------ */

struct Screen
{
    struct Screen *NextScreen;
    struct Window *FirstWindow;

    WORD LeftEdge, TopEdge;
    WORD Width, Height;
    WORD MouseY, MouseX;

    UWORD Flags;

    STRPTR	Title;
    STRPTR	DefaultTitle;

    /* The bar and the window borders' sizes */
    BYTE BarHeight, BarVBorder, BarHBorder, MenuVBorder, MenuHBorder;
    BYTE WBorTop, WBorLeft, WBorRight, WBorBottom;

    struct TextAttr *Font;

    struct ViewPort ViewPort;
    struct RastPort RastPort;
    struct BitMap BitMap;		/* a copy; use RastPort.BitMap */
    struct Layer_Info LayerInfo;

    struct Gadget *FirstGadget;

    UBYTE DetailPen, BlockPen;

    UWORD SaveColor0;			/* DisplayBeep()'s */

    struct Layer *BarLayer;

    UBYTE *ExtData;
    UBYTE *UserData;
};

/* Screen.Flags and NewScreen.Type */
#define SCREENTYPE	0x000F
#define WBENCHSCREEN	0x0001
#define PUBLICSCREEN	0x0002
#define CUSTOMSCREEN	0x000F

#define SHOWTITLE	0x0010
#define BEEPING		0x0020
#define CUSTOMBITMAP	0x0040
#define SCREENBEHIND	0x0080
#define SCREENQUIET	0x0100
#define SCREENHIRES	0x0200

#define NS_EXTENDED	0x1000		/* NewScreen is an ExtNewScreen */
#define AUTOSCROLL	0x4000

#define PENSHARED	0x0400		/* V39 */

/* "As big as the display clip" */
#define STDSCREENHEIGHT	-1
#define STDSCREENWIDTH	-1

/* OpenScreenTagList()'s tags */
#define SA_Dummy	(TAG_USER + 32)

#define SA_Left		(SA_Dummy + 0x0001)
#define SA_Top		(SA_Dummy + 0x0002)
#define SA_Width	(SA_Dummy + 0x0003)
#define SA_Height	(SA_Dummy + 0x0004)
#define SA_Depth	(SA_Dummy + 0x0005)
#define SA_DetailPen	(SA_Dummy + 0x0006)
#define SA_BlockPen	(SA_Dummy + 0x0007)
#define SA_Title	(SA_Dummy + 0x0008)
#define SA_Colors	(SA_Dummy + 0x0009)
#define SA_ErrorCode	(SA_Dummy + 0x000A)
#define SA_Font		(SA_Dummy + 0x000B)
#define SA_SysFont	(SA_Dummy + 0x000C)
#define SA_Type		(SA_Dummy + 0x000D)
#define SA_BitMap	(SA_Dummy + 0x000E)
#define SA_PubName	(SA_Dummy + 0x000F)
#define SA_PubSig	(SA_Dummy + 0x0010)
#define SA_PubTask	(SA_Dummy + 0x0011)
#define SA_DisplayID	(SA_Dummy + 0x0012)
#define SA_DClip	(SA_Dummy + 0x0013)
#define SA_Overscan	(SA_Dummy + 0x0014)
#define SA_Obsolete1	(SA_Dummy + 0x0015)

/* Booleans standing for the flags */
#define SA_ShowTitle	(SA_Dummy + 0x0016)
#define SA_Behind	(SA_Dummy + 0x0017)
#define SA_Quiet	(SA_Dummy + 0x0018)
#define SA_AutoScroll	(SA_Dummy + 0x0019)
#define SA_Pens		(SA_Dummy + 0x001A)
#define SA_FullPalette	(SA_Dummy + 0x001B)

/* V39 */
#define SA_ColorMapEntries (SA_Dummy + 0x001C)
#define SA_Parent	(SA_Dummy + 0x001D)
#define SA_Draggable	(SA_Dummy + 0x001E)
#define SA_Exclusive	(SA_Dummy + 0x001F)
#define SA_SharePens	(SA_Dummy + 0x0020)
#define SA_BackFill	(SA_Dummy + 0x0021)
#define SA_Interleaved	(SA_Dummy + 0x0022)
#define SA_Colors32	(SA_Dummy + 0x0023)
#define SA_VideoControl	(SA_Dummy + 0x0024)
#define SA_FrontChild	(SA_Dummy + 0x0025)
#define SA_BackChild	(SA_Dummy + 0x0026)
#define SA_LikeWorkbench (SA_Dummy + 0x0027)
#define SA_Reserved	(SA_Dummy + 0x0028)
#define SA_MinimizeISG	(SA_Dummy + 0x0029)

/* SA_ErrorCode's answers */
#define OSERR_NOMONITOR		(1)
#define OSERR_NOCHIPS		(2)
#define OSERR_NOMEM		(3)
#define OSERR_NOCHIPMEM		(4)
#define OSERR_PUBNOTUNIQUE	(5)
#define OSERR_UNKNOWNMODE	(6)
#define OSERR_TOODEEP		(7)	/* V39 */
#define OSERR_ATTACHFAIL	(8)	/* V39 */
#define OSERR_NOTAVAILABLE	(9)	/* V39 */

/* What OpenScreen() is given */
struct NewScreen
{
    WORD LeftEdge, TopEdge, Width, Height, Depth;
    UBYTE DetailPen, BlockPen;
    UWORD ViewModes;
    UWORD Type;
    struct TextAttr *Font;
    UBYTE *DefaultTitle;
    struct Gadget *Gadgets;
    struct BitMap *CustomBitMap;
};

/* A NewScreen with tags, flagged by NS_EXTENDED in Type */
struct ExtNewScreen
{
    WORD LeftEdge, TopEdge, Width, Height, Depth;
    UBYTE DetailPen, BlockPen;
    UWORD ViewModes;
    UWORD Type;
    struct TextAttr *Font;
    UBYTE *DefaultTitle;
    struct Gadget *Gadgets;
    struct BitMap *CustomBitMap;
    struct TagItem *Extension;
};

/* SA_Overscan's and QueryOverscan()'s kinds */
#define OSCAN_TEXT	(1)
#define OSCAN_STANDARD	(2)
#define OSCAN_MAX	(3)
#define OSCAN_VIDEO	(4)

/* ---- Public screens --------------------------------------------------- */

struct PubScreenNode
{
    struct Node psn_Node;		/* ln_Name is the screen's name */
    struct Screen *psn_Screen;
    UWORD psn_Flags;
    WORD psn_Size;			/* this node's size */
    WORD psn_VisitorCount;
    struct Task *psn_SigTask;		/* told when the last visitor leaves */
    UBYTE psn_SigBit;
};

/* psn_Flags */
#define PSNF_PRIVATE	(0x0001)

/* The longest name, without the NUL */
#define MAXPUBSCREENNAME (139)

/* SetPubScreenModes()' modes */
#define SHANGHAI	0x0001
#define POPPUBSCREEN	0x0002

/* ScreenDepth()'s flags (V39) */
#define SDEPTH_TOFRONT	(0)
#define SDEPTH_TOBACK	(1)
#define SDEPTH_INFAMILY	(2)
#define SDEPTH_CHILDONLY SDEPTH_INFAMILY

/* ScreenPosition()'s flags (V39) */
#define SPOS_RELATIVE	(0)
#define SPOS_ABSOLUTE	(1)
#define SPOS_MAKEVISIBLE (2)
#define SPOS_FORCEDRAG	(4)

/* ---- Double buffering (V39) ------------------------------------------ */

struct ScreenBuffer
{
    struct BitMap *sb_BitMap;
    struct DBufInfo *sb_DBufInfo;
};

/* AllocScreenBuffer()'s flags */
#define SB_SCREEN_BITMAP	1
#define SB_COPY_BITMAP		2

/* More names from the 3.2 interface */
#define NSTAG_EXT_VPMODE	0x80000001UL
#define OSERR_NORTGBITMAP	10
#define SA_OffScreenDragging	(SA_Dummy + 42)

#ifndef INTUITION_IOBSOLETE_H
#include <intuition/iobsolete.h>
#endif

#endif /* INTUITION_SCREENS_H */
