#ifndef INTUITION_IMAGECLASS_H
#define INTUITION_IMAGECLASS_H
/*
 * OpenNDK: imageclass and the built-in image classes: their tags,
 * methods and method messages.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* Image.Depth of a BOOPSI image */
#define CUSTOMIMAGEDEPTH	(-1)

/* A gadget's or image's box as a struct IBox, and an image's pens */
#define GADGET_BOX(g)	((struct IBox *)&((struct Gadget *)(g))->LeftEdge)
#define IM_BOX(im)	((struct IBox *)&((struct Image *)(im))->LeftEdge)
#define IM_FGPEN(im)	((im)->PlanePick)
#define IM_BGPEN(im)	((im)->PlaneOnOff)

/* ---- Attributes ------------------------------------------------------- */

#define IA_Dummy		(TAG_USER + 0x20000)
#define IA_Left			(IA_Dummy + 0x01)
#define IA_Top			(IA_Dummy + 0x02)
#define IA_Width		(IA_Dummy + 0x03)
#define IA_Height		(IA_Dummy + 0x04)
#define IA_FGPen		(IA_Dummy + 0x05)
#define IA_BGPen		(IA_Dummy + 0x06)
#define IA_Data			(IA_Dummy + 0x07)
#define IA_LineWidth		(IA_Dummy + 0x08)
#define IA_ShadowPen		(IA_Dummy + 0x09)
#define IA_HighlightPen		(IA_Dummy + 0x0A)
#define SYSIA_Size		(IA_Dummy + 0x0B)	/* SYSISIZE_ */
#define SYSIA_Depth		(IA_Dummy + 0x0C)
#define SYSIA_Which		(IA_Dummy + 0x0D)	/* which glyph */
#define IA_Pens			(IA_Dummy + 0x0E)
#define IA_Resolution		(IA_Dummy + 0x0F)
#define IA_APattern		(IA_Dummy + 0x10)
#define IA_APatSize		(IA_Dummy + 0x11)
#define IA_Mode			(IA_Dummy + 0x12)
#define IA_Font			(IA_Dummy + 0x13)
#define IA_Outline		(IA_Dummy + 0x14)
#define IA_Recessed		(IA_Dummy + 0x15)
#define IA_DoubleEmboss		(IA_Dummy + 0x16)
#define IA_EdgesOnly		(IA_Dummy + 0x17)
#define SYSIA_DrawInfo		(IA_Dummy + 0x18)
#define SYSIA_ReferenceFont	(IA_Dummy + 0x19)	/* V39 */
#define IA_SupportsDisable	(IA_Dummy + 0x1A)	/* V39 */
#define IA_FrameType		(IA_Dummy + 0x1B)	/* V39: FRAME_ */
#define IA_Underscore		(IA_Dummy + 0x1C)	/* V44 */
#define IA_Scalable		(IA_Dummy + 0x1D)	/* V44 */
#define IA_ActivateKey		(IA_Dummy + 0x1E)	/* V44 */
#define IA_Screen		(IA_Dummy + 0x1F)	/* V44 */
#define IA_Precision		(IA_Dummy + 0x20)	/* V44 */

/* Same as IA_Pens, for sysiclass */
#define SYSIA_Pens		IA_Pens

/* SYSIA_Size */
#define SYSISIZE_MEDRES	(0)
#define SYSISIZE_LOWRES	(1)
#define SYSISIZE_HIRES	(2)

/* SYSIA_Which: sysiclass's glyphs */
#define DEPTHIMAGE	(0x00)
#define ZOOMIMAGE	(0x01)
#define SIZEIMAGE	(0x02)
#define CLOSEIMAGE	(0x03)
#define SDEPTHIMAGE	(0x05)
#define LEFTIMAGE	(0x0A)
#define UPIMAGE		(0x0B)
#define RIGHTIMAGE	(0x0C)
#define DOWNIMAGE	(0x0D)
#define CHECKIMAGE	(0x0E)
#define MXIMAGE		(0x0F)
#define MENUCHECK	(0x10)	/* V39 */
#define AMIGAKEY	(0x11)	/* V39 */
#define ICONIFYIMAGE	(0x16)	/* V47 */

/* IA_FrameType: frameiclass's frames */
#define FRAME_DEFAULT		0
#define FRAME_BUTTON		1
#define FRAME_RIDGE		2
#define FRAME_ICONDROPBOX	3

/* ---- Methods ---------------------------------------------------------- */

#define IM_DRAW		0x202
#define IM_HITTEST	0x203
#define IM_ERASE	0x204
#define IM_MOVE		0x205
#define IM_DRAWFRAME	0x206
#define IM_FRAMEBOX	0x207
#define IM_HITFRAME	0x208
#define IM_ERASEFRAME	0x209
#define IM_DOMAINFRAME	0x20A	/* V44 */

/* The states an image draws */
#define IDS_NORMAL		(0)
#define IDS_SELECTED		(1)
#define IDS_DISABLED		(2)
#define IDS_BUSY		(3)
#define IDS_INDETERMINATE	(4)
#define IDS_INACTIVENORMAL	(5)
#define IDS_INACTIVESELECTED	(6)
#define IDS_INACTIVEDISABLED	(7)
#define IDS_SELECTEDDISABLED	(8)

/* Old name */
#define IDS_INDETERMINANT	IDS_INDETERMINATE

/* IM_FRAMEBOX */
struct impFrameBox
{
    ULONG MethodID;
    struct IBox *imp_ContentsBox;
    struct IBox *imp_FrameBox;		/* filled in */
    struct DrawInfo *imp_DrInfo;
    ULONG imp_FrameFlags;
};

/* imp_FrameFlags */
#define FRAMEF_SPECIFY	(1<<0)	/* keep the frame's size; fit the contents */

/* IM_DRAW and IM_DRAWFRAME */
struct impDraw
{
    ULONG MethodID;
    struct RastPort *imp_RPort;
    struct
    {
	WORD X;
	WORD Y;
    } imp_Offset;
    ULONG imp_State;
    struct DrawInfo *imp_DrInfo;
    struct
    {
	WORD Width;
	WORD Height;
    } imp_Dimensions;			/* IM_DRAWFRAME only */
};

/* IM_ERASE and IM_ERASEFRAME */
struct impErase
{
    ULONG MethodID;
    struct RastPort *imp_RPort;
    struct
    {
	WORD X;
	WORD Y;
    } imp_Offset;
    struct
    {
	WORD Width;
	WORD Height;
    } imp_Dimensions;			/* IM_ERASEFRAME only */
};

/* IM_HITTEST and IM_HITFRAME */
struct impHitTest
{
    ULONG MethodID;
    struct
    {
	WORD X;
	WORD Y;
    } imp_Point;
    struct
    {
	WORD Width;
	WORD Height;
    } imp_Dimensions;			/* IM_HITFRAME only */
};

/* IM_DOMAINFRAME */
struct impDomainFrame
{
    ULONG MethodID;
    struct DrawInfo *imp_DrInfo;
    struct RastPort *imp_RPort;
    LONG imp_Which;
    struct IBox imp_Domain;		/* filled in */
    struct TagItem *imp_Attrs;
};

/* imp_Which */
#define IDOMAIN_MINIMUM	(0)
#define IDOMAIN_NOMINAL	(1)
#define IDOMAIN_MAXIMUM	(2)

/* More names from the 3.2 interface */
#define FRAMEF_MINIMAL		2
#define FRAME_CONTEXT		7
#define FRAME_DISPLAY		6
#define FRAME_PROPBORDER	4
#define FRAME_PROPKNOB		5
#define IA_EraseBackground	(IA_Dummy + 45)
#define IA_Label		(IA_Dummy + 40)
#define IA_LabelPen		(IA_Dummy + 56)
#define IA_Orientation		(IA_Dummy + 35)
#define MENUMX			27
#define MENUSUB			28
#define SDOWNBACKMAGE		6
#define SHIFTKEYIMAGE		42

#ifndef INTUITION_IOBSOLETE_H
#include <intuition/iobsolete.h>
#endif

#endif /* INTUITION_IMAGECLASS_H */
