#ifndef INTUITION_INTUITION_H
#define INTUITION_INTUITION_H
/*
 * OpenNDK: Intuition's core structures: windows, gadgets, menus,
 * requesters, images, text, messages and the flags and tags they use.
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
#ifndef GRAPHICS_TEXT_H
#include <graphics/text.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef DEVICES_INPUTEVENT_H
#include <devices/inputevent.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* ---- Menus ------------------------------------------------------------ */

struct Menu
{
    struct Menu *NextMenu;
    WORD LeftEdge, TopEdge;
    WORD Width, Height;
    UWORD Flags;
    CONST_STRPTR MenuName;
    struct MenuItem *FirstItem;
    WORD JazzX, JazzY, BeatX, BeatY;	/* Intuition's own */
};

/* Menu.Flags */
#define MENUENABLED	0x0001
#define MIDRAWN		0x0100

struct MenuItem
{
    struct MenuItem *NextItem;
    WORD LeftEdge, TopEdge;
    WORD Width, Height;
    UWORD Flags;
    LONG MutualExclude;
    APTR ItemFill;			/* struct IntuiText or struct Image */
    APTR SelectFill;
    BYTE Command;			/* the Amiga-key shortcut */
    struct MenuItem *SubItem;
    UWORD NextSelect;
};

/* MenuItem.Flags set by the program */
#define CHECKIT		0x0001
#define ITEMTEXT	0x0002
#define COMMSEQ		0x0004
#define MENUTOGGLE	0x0008
#define ITEMENABLED	0x0010

/* How an item is highlighted */
#define HIGHFLAGS	0x00C0
#define HIGHIMAGE	0x0000
#define HIGHCOMP	0x0040
#define HIGHBOX		0x0080
#define HIGHNONE	0x00C0

#define CHECKED		0x0100

/* MenuItem.Flags kept by Intuition */
#define ISDRAWN		0x1000
#define HIGHITEM	0x2000
#define MENUTOGGLED	0x4000

/* Room left for the check mark and the shortcut, high and low resolution */
#define CHECKWIDTH	19
#define COMMWIDTH	27
#define LOWCHECKWIDTH	13
#define LOWCOMMWIDTH	16

/* Menu numbers: menu in bits 0-4, item in 5-10, sub-item in 11-15 */
#define NOMENU		0x001F
#define NOITEM		0x003F
#define NOSUB		0x001F
#define MENUNULL	0xFFFF

#define MENUNUM(n)	((n) & 0x1F)
#define ITEMNUM(n)	(((n) >> 5) & 0x003F)
#define SUBNUM(n)	(((n) >> 11) & 0x001F)

#define SHIFTMENU(n)	((n) & 0x1F)
#define SHIFTITEM(n)	(((n) & 0x3F) << 5)
#define SHIFTSUB(n)	(((n) & 0x1F) << 11)

#define FULLMENUNUM(menu, item, sub) \
    (SHIFTMENU(menu) | SHIFTITEM(item) | SHIFTSUB(sub))

/* Packing the serial port's prefs bytes */
#define SRBNUM(n)	(0x08 - ((n) >> 4))
#define SWBNUM(n)	(0x08 - ((n) & 0x0F))
#define SSBNUM(n)	(0x01 + ((n) >> 4))
#define SPARNUM(n)	((n) >> 4)
#define SHAKNUM(n)	((n) & 0x0F)

/* ---- Requesters ------------------------------------------------------- */

struct Requester
{
    struct Requester *OlderRequest;
    WORD LeftEdge, TopEdge;
    WORD Width, Height;
    WORD RelLeft, RelTop;		/* with POINTREL: from the pointer */
    struct Gadget *ReqGadget;
    struct Border *ReqBorder;
    struct IntuiText *ReqText;
    UWORD Flags;
    UBYTE BackFill;
    struct Layer *ReqLayer;
    UBYTE ReqPad1[32];
    struct BitMap *ImageBMap;		/* with PREDRAWN */
    struct Window *RWindow;
    struct Image *ReqImage;		/* with USEREQIMAGE */
    UBYTE ReqPad2[32];
};

/* Requester.Flags set by the program */
#define POINTREL	0x0001
#define PREDRAWN	0x0002
#define NOISYREQ	0x0004
#define SIMPLEREQ	0x0010
#define USEREQIMAGE	0x0020
#define NOREQBACKFILL	0x0040

/* Requester.Flags kept by Intuition */
#define REQOFFWINDOW	0x1000
#define REQACTIVE	0x2000
#define SYSREQUEST	0x4000
#define DEFERREFRESH	0x8000

/* ---- Gadgets ---------------------------------------------------------- */

struct Gadget
{
    struct Gadget *NextGadget;
    WORD LeftEdge, TopEdge;
    WORD Width, Height;
    UWORD Flags;
    UWORD Activation;
    UWORD GadgetType;
    APTR GadgetRender;			/* struct Image or struct Border */
    APTR SelectRender;
    struct IntuiText *GadgetText;
    LONG MutualExclude;			/* a custom gadget's hook */
    APTR SpecialInfo;
    UWORD GadgetID;
    APTR UserData;
};

/* A gadget with GFLG_EXTENDED set */
struct ExtGadget
{
    struct ExtGadget *NextGadget;
    WORD LeftEdge, TopEdge;
    WORD Width, Height;
    UWORD Flags;
    UWORD Activation;
    UWORD GadgetType;
    APTR GadgetRender;
    APTR SelectRender;
    struct IntuiText *GadgetText;
    LONG MutualExclude;
    APTR SpecialInfo;
    UWORD GadgetID;
    APTR UserData;
    /* the extension */
    ULONG MoreFlags;
    WORD BoundsLeftEdge;
    WORD BoundsTopEdge;
    WORD BoundsWidth;
    WORD BoundsHeight;
};

/* Gadget.Flags */
#define GFLG_GADGHIGHBITS	0x0003
#define GFLG_GADGHCOMP		0x0000
#define GFLG_GADGHBOX		0x0001
#define GFLG_GADGHIMAGE		0x0002
#define GFLG_GADGHNONE		0x0003

#define GFLG_GADGIMAGE		0x0004

#define GFLG_RELBOTTOM		0x0008
#define GFLG_RELRIGHT		0x0010
#define GFLG_RELWIDTH		0x0020
#define GFLG_RELHEIGHT		0x0040

#define GFLG_RELSPECIAL		0x4000

#define GFLG_SELECTED		0x0080
#define GFLG_DISABLED		0x0100

#define GFLG_LABELMASK		0x3000
#define GFLG_LABELITEXT		0x0000
#define GFLG_LABELSTRING	0x1000
#define GFLG_LABELIMAGE		0x2000

#define GFLG_TABCYCLE		0x0200
#define GFLG_STRINGEXTEND	0x0400
#define GFLG_IMAGEDISABLE	0x0800
#define GFLG_EXTENDED		0x8000

/* Gadget.Activation */
#define GACT_RELVERIFY		0x0001
#define GACT_IMMEDIATE		0x0002
#define GACT_ENDGADGET		0x0004
#define GACT_FOLLOWMOUSE	0x0008

#define GACT_RIGHTBORDER	0x0010
#define GACT_LEFTBORDER		0x0020
#define GACT_TOPBORDER		0x0040
#define GACT_BOTTOMBORDER	0x0080
#define GACT_BORDERSNIFF	0x8000

#define GACT_TOGGLESELECT	0x0100
#define GACT_BOOLEXTEND		0x2000

#define GACT_STRINGLEFT		0x0000
#define GACT_STRINGCENTER	0x0200
#define GACT_STRINGRIGHT	0x0400
#define GACT_LONGINT		0x0800
#define GACT_ALTKEYMAP		0x1000
#define GACT_STRINGEXTEND	0x2000

#define GACT_ACTIVEGADGET	0x4000

/* Gadget.GadgetType */
#define GTYP_GADGETTYPE		0xFC00
#define GTYP_SCRGADGET		0x4000
#define GTYP_GZZGADGET		0x2000
#define GTYP_REQGADGET		0x1000

#define GTYP_SYSGADGET		0x8000
#define GTYP_SYSTYPEMASK	0x00F0

/* The system gadgets */
#define GTYP_SIZING		0x0010
#define GTYP_WDRAGGING		0x0020
#define GTYP_SDRAGGING		0x0030
#define GTYP_WDEPTH		0x0040
#define GTYP_SDEPTH		0x0050
#define GTYP_WZOOM		0x0060
#define GTYP_SUNUSED		0x0070
#define GTYP_CLOSE		0x0080

#define GTYP_WUPFRONT		GTYP_WDEPTH
#define GTYP_SUPFRONT		GTYP_SDEPTH
#define GTYP_WDOWNBACK		GTYP_WZOOM
#define GTYP_SDOWNBACK		GTYP_SUNUSED

/* The program's gadgets */
#define GTYP_GTYPEMASK		0x0007
#define GTYP_BOOLGADGET		0x0001
#define GTYP_GADGET0002		0x0002
#define GTYP_PROPGADGET		0x0003
#define GTYP_STRGADGET		0x0004
#define GTYP_CUSTOMGADGET	0x0005

/* ExtGadget.MoreFlags */
#define GMORE_BOUNDS		0x00000001
#define GMORE_GADGETHELP	0x00000002
#define GMORE_SCROLLRASTER	0x00000004

/* A boolean gadget's mask (GACT_BOOLEXTEND) */
struct BoolInfo
{
    UWORD Flags;
    UWORD *Mask;
    ULONG Reserved;
};

#define BOOLMATCH	0x0001

/* A proportional gadget */
struct PropInfo
{
    UWORD Flags;
    UWORD HorizPot;
    UWORD VertPot;
    UWORD HorizBody;
    UWORD VertBody;
    /* Intuition's working values */
    UWORD CWidth;
    UWORD CHeight;
    UWORD HPotRes, VPotRes;
    UWORD LeftBorder;
    UWORD TopBorder;
};

/* PropInfo.Flags */
#define AUTOKNOB	0x0001
#define FREEHORIZ	0x0002
#define FREEVERT	0x0004
#define PROPBORDERLESS	0x0008
#define KNOBHIT		0x0100
#define PROPNEWLOOK	0x0010

/* The smallest knob */
#define KNOBHMIN	6
#define KNOBVMIN	4
#define MAXBODY		0xFFFF
#define MAXPOT		0xFFFF

/* A string gadget */
struct StringInfo
{
    STRPTR	Buffer;
    STRPTR	UndoBuffer;
    WORD BufferPos;
    WORD MaxChars;			/* buffer size, the NUL included */
    WORD DispPos;
    /* Intuition's working values */
    WORD UndoPos;
    WORD NumChars;
    WORD DispCount;
    WORD CLeft, CTop;
    struct StringExtend *Extension;	/* with GFLG_STRINGEXTEND */
    LONG LongInt;			/* with GACT_LONGINT */
    struct KeyMap *AltKeyMap;		/* with GACT_ALTKEYMAP */
};

/* ---- Text, borders and images ----------------------------------------- */

struct IntuiText
{
    UBYTE FrontPen, BackPen;
    UBYTE DrawMode;
    WORD LeftEdge;
    WORD TopEdge;
    struct TextAttr *ITextFont;
    STRPTR IText;
    struct IntuiText *NextText;
};

struct Border
{
    WORD LeftEdge, TopEdge;
    UBYTE FrontPen, BackPen;
    UBYTE DrawMode;
    BYTE Count;				/* pairs in XY */
    WORD *XY;
    struct Border *NextBorder;
};

struct Image
{
    WORD LeftEdge;
    WORD TopEdge;
    WORD Width;
    WORD Height;
    WORD Depth;				/* CUSTOMIMAGEDEPTH: a BOOPSI image */
    UWORD *ImageData;
    UBYTE PlanePick, PlaneOnOff;
    struct Image *NextImage;
};

/* ---- IDCMP messages --------------------------------------------------- */

struct IntuiMessage
{
    struct Message ExecMessage;
    ULONG Class;
    UWORD Code;
    UWORD Qualifier;
    APTR IAddress;
    WORD MouseX, MouseY;
    ULONG Seconds, Micros;
    struct Window *IDCMPWindow;
    struct IntuiMessage *SpecialLink;	/* Intuition's own */
};

/* The message a WA_TabletMessages window gets */
struct ExtIntuiMessage
{
    struct IntuiMessage eim_IntuiMessage;
    struct TabletData *eim_TabletData;
};

/* IntuiMessage.Class and the IDCMP flags */
#define IDCMP_SIZEVERIFY	0x00000001
#define IDCMP_NEWSIZE		0x00000002
#define IDCMP_REFRESHWINDOW	0x00000004
#define IDCMP_MOUSEBUTTONS	0x00000008
#define IDCMP_MOUSEMOVE		0x00000010
#define IDCMP_GADGETDOWN	0x00000020
#define IDCMP_GADGETUP		0x00000040
#define IDCMP_REQSET		0x00000080
#define IDCMP_MENUPICK		0x00000100
#define IDCMP_CLOSEWINDOW	0x00000200
#define IDCMP_RAWKEY		0x00000400
#define IDCMP_REQVERIFY		0x00000800
#define IDCMP_REQCLEAR		0x00001000
#define IDCMP_MENUVERIFY	0x00002000
#define IDCMP_NEWPREFS		0x00004000
#define IDCMP_DISKINSERTED	0x00008000
#define IDCMP_DISKREMOVED	0x00010000
#define IDCMP_WBENCHMESSAGE	0x00020000
#define IDCMP_ACTIVEWINDOW	0x00040000
#define IDCMP_INACTIVEWINDOW	0x00080000
#define IDCMP_DELTAMOVE		0x00100000
#define IDCMP_VANILLAKEY	0x00200000
#define IDCMP_INTUITICKS	0x00400000
#define IDCMP_IDCMPUPDATE	0x00800000
#define IDCMP_MENUHELP		0x01000000
#define IDCMP_CHANGEWINDOW	0x02000000
#define IDCMP_GADGETHELP	0x04000000
#define IDCMP_EXTENDEDMOUSE	0x08000000	/* V47: the wheel */

/* Not a class a program asks for */
#define IDCMP_LONELYMESSAGE	0x80000000

/* IDCMP_CHANGEWINDOW's Code */
#define CWCODE_MOVESIZE	0x0000
#define CWCODE_DEPTH	0x0001

/* IDCMP_MENUVERIFY's Code */
#define MENUHOT		0x0001
#define MENUCANCEL	0x0002
#define MENUWAITING	0x0003

/* Old names for the requester verify answers */
#define OKOK		MENUHOT
#define OKABORT		0x0004
#define OKCANCEL	MENUCANCEL

/* IDCMP_WBENCHMESSAGE's Code */
#define WBENCHOPEN	0x0001
#define WBENCHCLOSE	0x0002

/* IDCMP_EXTENDEDMOUSE: the Code, and what IAddress points to */
#define IMSGCODE_INTUIWHEELDATA	(1 << 15)

struct IntuiWheelData
{
    UWORD Version;
    UWORD Reserved;
    WORD WheelX;
    WORD WheelY;
    struct Gadget *HoveredGadget;	/* version 2 and up */
};

/* A rectangle as Intuition stores one */
struct IBox
{
    WORD Left;
    WORD Top;
    WORD Width;
    WORD Height;
};

/* ---- Windows ---------------------------------------------------------- */

struct Window
{
    struct Window *NextWindow;
    WORD LeftEdge, TopEdge;
    WORD Width, Height;
    WORD MouseY, MouseX;		/* relative to the window's corner */
    WORD MinWidth, MinHeight;
    UWORD MaxWidth, MaxHeight;
    ULONG Flags;
    struct Menu *MenuStrip;
    STRPTR	Title;
    struct Requester *FirstRequest;
    struct Requester *DMRequest;
    WORD ReqCount;
    struct Screen *WScreen;
    struct RastPort *RPort;
    BYTE BorderLeft, BorderTop, BorderRight, BorderBottom;
    struct RastPort *BorderRPort;
    struct Gadget *FirstGadget;
    struct Window *Parent, *Descendant;	/* Intuition's own */
    UWORD *Pointer;			/* the sprite data */
    BYTE PtrHeight;
    BYTE PtrWidth;
    BYTE XOffset, YOffset;
    ULONG IDCMPFlags;
    struct MsgPort *UserPort, *WindowPort;
    struct IntuiMessage *MessageKey;
    UBYTE DetailPen, BlockPen;
    struct Image *CheckMark;
    STRPTR	ScreenTitle;
    WORD GZZMouseX;			/* a GimmeZeroZero window's inner values */
    WORD GZZMouseY;
    WORD GZZWidth;
    WORD GZZHeight;
    UBYTE *ExtData;
    BYTE *UserData;
    struct Layer *WLayer;
    struct TextFont *IFont;
    ULONG MoreFlags;
};

/* Window.Flags and NewWindow.Flags */
#define WFLG_SIZEGADGET		0x00000001
#define WFLG_DRAGBAR		0x00000002
#define WFLG_DEPTHGADGET	0x00000004
#define WFLG_CLOSEGADGET	0x00000008

#define WFLG_SIZEBRIGHT		0x00000010
#define WFLG_SIZEBBOTTOM	0x00000020

#define WFLG_REFRESHBITS	0x000000C0
#define WFLG_SMART_REFRESH	0x00000000
#define WFLG_SIMPLE_REFRESH	0x00000040
#define WFLG_SUPER_BITMAP	0x00000080
#define WFLG_OTHER_REFRESH	0x000000C0

#define WFLG_BACKDROP		0x00000100
#define WFLG_REPORTMOUSE	0x00000200
#define WFLG_GIMMEZEROZERO	0x00000400
#define WFLG_BORDERLESS		0x00000800
#define WFLG_ACTIVATE		0x00001000

/* Kept by Intuition */
#define WFLG_WINDOWACTIVE	0x00002000
#define WFLG_INREQUEST		0x00004000
#define WFLG_MENUSTATE		0x00008000

#define WFLG_RMBTRAP		0x00010000
#define WFLG_NOCAREREFRESH	0x00020000
#define WFLG_NW_EXTENDED	0x00040000	/* NewWindow is an ExtNewWindow */
#define WFLG_NEWLOOKMENUS	0x00200000

/* Kept by Intuition */
#define WFLG_WINDOWREFRESH	0x01000000
#define WFLG_WBENCHWINDOW	0x02000000
#define WFLG_WINDOWTICKED	0x04000000
#define WFLG_VISITOR		0x08000000
#define WFLG_ZOOMED		0x10000000
#define WFLG_HASZOOM		0x20000000

#define SUPER_UNUSED		0xFCFC0000

/* Messages a window holds at once by default */
#define DEFAULTMOUSEQUEUE	(5)

/* What OpenWindow() is given */
struct NewWindow
{
    WORD LeftEdge, TopEdge;
    WORD Width, Height;
    UBYTE DetailPen, BlockPen;
    ULONG IDCMPFlags;
    ULONG Flags;
    struct Gadget *FirstGadget;
    struct Image *CheckMark;
    STRPTR	Title;
    struct Screen *Screen;		/* with Type CUSTOMSCREEN */
    struct BitMap *BitMap;		/* with WFLG_SUPER_BITMAP */
    WORD MinWidth, MinHeight;
    UWORD MaxWidth, MaxHeight;
    UWORD Type;				/* a screen type, screens.h */
};

/* A NewWindow with tags, flagged by WFLG_NW_EXTENDED */
struct ExtNewWindow
{
    WORD LeftEdge, TopEdge;
    WORD Width, Height;
    UBYTE DetailPen, BlockPen;
    ULONG IDCMPFlags;
    ULONG Flags;
    struct Gadget *FirstGadget;
    struct Image *CheckMark;
    STRPTR	Title;
    struct Screen *Screen;
    struct BitMap *BitMap;
    WORD MinWidth, MinHeight;
    UWORD MaxWidth, MaxHeight;
    UWORD Type;
    struct TagItem *Extension;
};

/* OpenWindowTagList()'s tags */
#define WA_Dummy		(TAG_USER + 99)

#define WA_Left			(WA_Dummy + 0x01)
#define WA_Top			(WA_Dummy + 0x02)
#define WA_Width		(WA_Dummy + 0x03)
#define WA_Height		(WA_Dummy + 0x04)
#define WA_DetailPen		(WA_Dummy + 0x05)
#define WA_BlockPen		(WA_Dummy + 0x06)
#define WA_IDCMP		(WA_Dummy + 0x07)
#define WA_Flags		(WA_Dummy + 0x08)
#define WA_Gadgets		(WA_Dummy + 0x09)
#define WA_Checkmark		(WA_Dummy + 0x0A)
#define WA_Title		(WA_Dummy + 0x0B)
#define WA_ScreenTitle		(WA_Dummy + 0x0C)
#define WA_CustomScreen		(WA_Dummy + 0x0D)
#define WA_SuperBitMap		(WA_Dummy + 0x0E)
#define WA_MinWidth		(WA_Dummy + 0x0F)
#define WA_MinHeight		(WA_Dummy + 0x10)
#define WA_MaxWidth		(WA_Dummy + 0x11)
#define WA_MaxHeight		(WA_Dummy + 0x12)
#define WA_InnerWidth		(WA_Dummy + 0x13)
#define WA_InnerHeight		(WA_Dummy + 0x14)
#define WA_PubScreenName	(WA_Dummy + 0x15)
#define WA_PubScreen		(WA_Dummy + 0x16)
#define WA_PubScreenFallBack	(WA_Dummy + 0x17)
#define WA_WindowName		(WA_Dummy + 0x18)
#define WA_Colors		(WA_Dummy + 0x19)
#define WA_Zoom			(WA_Dummy + 0x1A)
#define WA_MouseQueue		(WA_Dummy + 0x1B)
#define WA_BackFill		(WA_Dummy + 0x1C)
#define WA_RptQueue		(WA_Dummy + 0x1D)
/* Booleans standing for the flags */
#define WA_SizeGadget		(WA_Dummy + 0x1E)
#define WA_DragBar		(WA_Dummy + 0x1F)
#define WA_DepthGadget		(WA_Dummy + 0x20)
#define WA_CloseGadget		(WA_Dummy + 0x21)
#define WA_Backdrop		(WA_Dummy + 0x22)
#define WA_ReportMouse		(WA_Dummy + 0x23)
#define WA_NoCareRefresh	(WA_Dummy + 0x24)
#define WA_Borderless		(WA_Dummy + 0x25)
#define WA_Activate		(WA_Dummy + 0x26)
#define WA_RMBTrap		(WA_Dummy + 0x27)
#define WA_WBenchWindow		(WA_Dummy + 0x28)	/* system use */
#define WA_SimpleRefresh	(WA_Dummy + 0x29)
#define WA_SmartRefresh		(WA_Dummy + 0x2A)
#define WA_SizeBRight		(WA_Dummy + 0x2B)
#define WA_SizeBBottom		(WA_Dummy + 0x2C)
/* More */
#define WA_AutoAdjust		(WA_Dummy + 0x2D)
#define WA_GimmeZeroZero	(WA_Dummy + 0x2E)
#define WA_MenuHelp		(WA_Dummy + 0x2F)
#define WA_NewLookMenus		(WA_Dummy + 0x30)
#define WA_AmigaKey		(WA_Dummy + 0x31)
#define WA_NotifyDepth		(WA_Dummy + 0x32)
/* 0x33 is not used */
#define WA_Pointer		(WA_Dummy + 0x34)
#define WA_BusyPointer		(WA_Dummy + 0x35)
#define WA_PointerDelay		(WA_Dummy + 0x36)
#define WA_TabletMessages	(WA_Dummy + 0x37)
#define WA_HelpGroup		(WA_Dummy + 0x38)
#define WA_HelpGroupWindow	(WA_Dummy + 0x39)

/* HelpControl()'s flags */
#define HC_GADGETHELP	1

/* ---- Tablets ---------------------------------------------------------- */

/* What a tablet driver passes on in an ExtIntuiMessage */
struct TabletData
{
    UWORD td_XFraction, td_YFraction;	/* below the pixel */
    ULONG td_TabletX, td_TabletY;
    ULONG td_RangeX, td_RangeY;
    struct TagItem *td_TagList;		/* TABLETA_ tags */
};

/* What a tablet driver's hook is given */
struct TabletHookData
{
    struct Screen *thd_Screen;
    ULONG thd_Width;
    ULONG thd_Height;
    LONG thd_ScreenChanged;
};

#define TABLETA_Dummy		(TAG_USER + 0x3A000)
#define TABLETA_TabletZ		(TABLETA_Dummy + 0x01)
#define TABLETA_RangeZ		(TABLETA_Dummy + 0x02)
#define TABLETA_AngleX		(TABLETA_Dummy + 0x03)
#define TABLETA_AngleY		(TABLETA_Dummy + 0x04)
#define TABLETA_AngleZ		(TABLETA_Dummy + 0x05)
#define TABLETA_Pressure	(TABLETA_Dummy + 0x06)
#define TABLETA_ButtonBits	(TABLETA_Dummy + 0x07)
#define TABLETA_InProximity	(TABLETA_Dummy + 0x08)
#define TABLETA_ResolutionX	(TABLETA_Dummy + 0x09)
#define TABLETA_ResolutionY	(TABLETA_Dummy + 0x0A)

/* ---- Remember, colours, EasyRequest ---------------------------------- */

/* AllocRemember()'s chain */
struct Remember
{
    struct Remember *NextRemember;
    ULONG RememberSize;
    UBYTE *Memory;
};

/* SA_Colors' array, ended by ColorIndex -1 */
struct ColorSpec
{
    WORD ColorIndex;
    UWORD Red;
    UWORD Green;
    UWORD Blue;
};

/* EasyRequest()'s description */
struct EasyStruct
{
    ULONG es_StructSize;
    ULONG es_Flags;
    CONST_STRPTR es_Title;
    CONST_STRPTR es_TextFormat;
    CONST_STRPTR es_GadgetFormat;
};

/* ---- Miscellany ------------------------------------------------------- */

/* DisplayAlert()'s kinds */
#define RECOVERY_ALERT	0x00000000
#define DEADEND_ALERT	0x80000000

/* AutoRequest()'s defaults */
#define AUTOFRONTPEN	0
#define AUTOBACKPEN	1
#define AUTODRAWMODE	JAM2
#define AUTOLEFTEDGE	6
#define AUTOTOPEDGE	3
#define AUTOITEXTFONT	NULL
#define AUTONEXTTEXT	NULL

/* The mouse buttons as IDCMP_MOUSEBUTTONS reports them */
#define SELECTUP	(IECODE_LBUTTON | IECODE_UP_PREFIX)
#define SELECTDOWN	(IECODE_LBUTTON)
#define MENUUP		(IECODE_RBUTTON | IECODE_UP_PREFIX)
#define MENUDOWN	(IECODE_RBUTTON)
#define MIDDLEUP	(IECODE_MBUTTON | IECODE_UP_PREFIX)
#define MIDDLEDOWN	(IECODE_MBUTTON)
#define ALTLEFT		(IEQUALIFIER_LALT)
#define ALTRIGHT	(IEQUALIFIER_RALT)
#define AMIGALEFT	(IEQUALIFIER_LCOMMAND)
#define AMIGARIGHT	(IEQUALIFIER_RCOMMAND)
#define AMIGAKEYS	(AMIGALEFT | AMIGARIGHT)

/* Raw key codes Intuition itself reacts to */
#define CURSORUP	0x4C
#define CURSORLEFT	0x4F
#define CURSORRIGHT	0x4E
#define CURSORDOWN	0x4D
#define KEYCODE_Q	0x10
#define KEYCODE_Z	0x31
#define KEYCODE_X	0x32
#define KEYCODE_V	0x34
#define KEYCODE_B	0x35
#define KEYCODE_N	0x36
#define KEYCODE_M	0x37
#define KEYCODE_LESS	0x38
#define KEYCODE_GREATER	0x39

/* Small helpers older sources use */
#ifndef FOREVER
#define FOREVER		for (;;)
#endif
#ifndef SIGN
#define SIGN(x)		(((x) > 0) - ((x) < 0))
#endif
#ifndef NOT
#define NOT		!
#endif

/* ---- The rest of Intuition's public headers -------------------------- */

#ifndef INTUITION_SCREENS_H
#include <intuition/screens.h>
#endif
#ifndef INTUITION_PREFERENCES_H
#include <intuition/preferences.h>
#endif

/* The pre-V36 names, unless the program asks for the new names only */
#ifndef INTUI_V36_NAMES_ONLY
#ifndef INTUITION_IOBSOLETE_H
#include <intuition/iobsolete.h>
#endif
#endif

/* More names from the 3.2 interface */
#define ICTRL_Dummy		0x8001C000UL
#define ALERT_TYPE		0x80000000UL
#define BOOLMASK		1
#define CWCODE_HIDE		2
#define CWCODE_SHOW		3
#define GMORE_BOOPSIGADGET	0x400
#define GMORE_FREEIMAGE		0x800
#define GMORE_HIDDEN		16
#define GMORE_PARENTHIDDEN	0x1000000
#define GTYP_ICONIFY		144
#define INTUIWHEELDATA_VERSION	2
#define MIF_EXTENDED		0x8000
#define MIF_RESERVED		0x400
#define MIF_SHIFTCOMMSEQ	0x800
#define SMARTKNOBIMAGE		32
#define SUBMENU			0x200
#define WA_Hidden		(WA_Dummy + 60)
#define WA_IconifyGadget	(WA_Dummy + 96)
#define WA_PointerType		(WA_Dummy + 80)
#define WFLG_HASICONIFY		0x40000000
#define WINDOW_BACKMOST		0
#define WINDOW_FRONTMOST	1

#endif /* INTUITION_INTUITION_H */
