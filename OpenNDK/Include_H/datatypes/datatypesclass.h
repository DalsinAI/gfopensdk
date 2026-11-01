#ifndef DATATYPES_DATATYPESCLASS_H
#define DATATYPES_DATATYPESCLASS_H
/*
 * OpenNDK: the datatypes root class: attributes, methods and messages.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef DATATYPES_DATATYPES_H
#include <datatypes/datatypes.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef INTUITION_CGHOOKS_H
#include <intuition/cghooks.h>
#endif
#ifndef DEVICES_PRINTER_H
#include <devices/printer.h>
#endif
#ifndef DEVICES_PRTBASE_H
#include <devices/prtbase.h>
#endif

#define DATATYPESCLASS	"datatypesclass"

/* Attributes */
#define DTA_Dummy		(TAG_USER+0x1000)

#define DTA_TextAttr		(DTA_Dummy+10)	/* struct TextAttr * for text */
#define DTA_TopVert		(DTA_Dummy+11)	/* the scroll position, in units */
#define DTA_VisibleVert		(DTA_Dummy+12)
#define DTA_TotalVert		(DTA_Dummy+13)
#define DTA_VertUnit		(DTA_Dummy+14)	/* pixels a unit */
#define DTA_TopHoriz		(DTA_Dummy+15)
#define DTA_VisibleHoriz	(DTA_Dummy+16)
#define DTA_TotalHoriz		(DTA_Dummy+17)
#define DTA_HorizUnit		(DTA_Dummy+18)
#define DTA_NodeName		(DTA_Dummy+19)	/* for DTM_GOTO */
#define DTA_Title		(DTA_Dummy+20)
#define DTA_TriggerMethods	(DTA_Dummy+21)	/* struct DTMethod * */
#define DTA_Data		(DTA_Dummy+22)	/* the object's own data */
#define DTA_TextFont		(DTA_Dummy+23)
#define DTA_Methods		(DTA_Dummy+24)	/* ULONG * of the methods supported */
#define DTA_PrinterStatus	(DTA_Dummy+25)
#define DTA_PrinterProc		(DTA_Dummy+26)
#define DTA_LayoutProc		(DTA_Dummy+27)
#define DTA_Busy		(DTA_Dummy+28)
#define DTA_Sync		(DTA_Dummy+29)	/* the object needs a redraw */
#define DTA_BaseName		(DTA_Dummy+30)
#define DTA_GroupID		(DTA_Dummy+31)
#define DTA_ErrorLevel		(DTA_Dummy+32)
#define DTA_ErrorNumber		(DTA_Dummy+33)
#define DTA_ErrorString		(DTA_Dummy+34)
#define DTA_Conductor		(DTA_Dummy+35)	/* a realtime conductor's name */
#define DTA_ControlPanel	(DTA_Dummy+36)
#define DTA_Immediate		(DTA_Dummy+37)	/* start playing at once */
#define DTA_Repeat		(DTA_Dummy+38)
#define DTA_SourceAddress	(DTA_Dummy+39)	/* DTST_MEMORY: the data */
#define DTA_SourceSize		(DTA_Dummy+40)	/* DTST_MEMORY: its size */
#define DTA_Reserved		(DTA_Dummy+41)

/* Attributes for creating the object */
#define DTA_Name		(DTA_Dummy+100)
#define DTA_SourceType		(DTA_Dummy+101)	/* DTST_ */
#define DTA_Handle		(DTA_Dummy+102)
#define DTA_DataType		(DTA_Dummy+103)	/* struct DataType * */
#define DTA_Domain		(DTA_Dummy+104)	/* struct IBox * */

/* Older names; GA_Left and the rest are preferred */
#define DTA_Left		(DTA_Dummy+105)
#define DTA_Top			(DTA_Dummy+106)
#define DTA_Width		(DTA_Dummy+107)
#define DTA_Height		(DTA_Dummy+108)

#define DTA_ObjName		(DTA_Dummy+109)
#define DTA_ObjAuthor		(DTA_Dummy+110)
#define DTA_ObjAnnotation	(DTA_Dummy+111)
#define DTA_ObjCopyright	(DTA_Dummy+112)
#define DTA_ObjVersion		(DTA_Dummy+113)
#define DTA_ObjectID		(DTA_Dummy+114)
#define DTA_UserData		(DTA_Dummy+115)
#define DTA_FrameInfo		(DTA_Dummy+116)	/* struct FrameInfo * */

/* Older names; GA_RelRight and the rest are preferred */
#define DTA_RelRight		(DTA_Dummy+117)
#define DTA_RelBottom		(DTA_Dummy+118)
#define DTA_RelWidth		(DTA_Dummy+119)
#define DTA_RelHeight		(DTA_Dummy+120)

#define DTA_SelectDomain	(DTA_Dummy+121)	/* struct IBox * of the selection */
#define DTA_TotalPVert		(DTA_Dummy+122)
#define DTA_TotalPHoriz		(DTA_Dummy+123)
#define DTA_NominalVert		(DTA_Dummy+124)
#define DTA_NominalHoriz	(DTA_Dummy+125)

/* Printing */
#define DTA_DestCols		(DTA_Dummy+400)
#define DTA_DestRows		(DTA_Dummy+401)
#define DTA_Special		(DTA_Dummy+402)
#define DTA_RastPort		(DTA_Dummy+403)

/* ARexx */
#define DTA_ARexxPortName	(DTA_Dummy+404)

/* DTA_SourceType */
#define DTST_RAM	1
#define DTST_FILE	2
#define DTST_CLIPBOARD	3
#define DTST_HOTLINK	4
#define DTST_MEMORY	5

/* Hung on the gadget's SpecialInfo: the scroll state */
struct DTSpecialInfo {
	struct SignalSemaphore	si_Lock;	/* held while the object is laid out */
	ULONG			si_Flags;	/* DTSIF_ */

	LONG	si_TopVert;
	LONG	si_VisVert;
	LONG	si_TotVert;
	LONG	si_OTopVert;
	LONG	si_VertUnit;

	LONG	si_TopHoriz;
	LONG	si_VisHoriz;
	LONG	si_TotHoriz;
	LONG	si_OTopHoriz;
	LONG	si_HorizUnit;
};

/* si_Flags */
#define DTSIF_LAYOUT		(1L<<0)	/* in layout */
#define DTSIF_NEWSIZE		(1L<<1)	/* the content changed size */
#define DTSIF_DRAGGING		(1L<<2)
#define DTSIF_DRAGSELECT	(1L<<3)
#define DTSIF_HIGHLIGHT		(1L<<4)
#define DTSIF_PRINTING		(1L<<5)	/* being printed */
#define DTSIF_LAYOUTPROC	(1L<<6)	/* a layout process is running */

/* Methods */
#define DTM_Dummy		(0x600)
#define DTM_FRAMEBOX		(0x601)	/* struct dtFrameBox */
#define DTM_PROCLAYOUT		(0x602)	/* struct gpLayout */
#define DTM_ASYNCLAYOUT		(0x603)	/* struct gpLayout */
#define DTM_REMOVEDTOBJECT	(0x604)
#define DTM_SELECT		(0x605)	/* struct dtSelect */
#define DTM_CLEARSELECTED	(0x606)	/* struct dtGeneral */
#define DTM_COPY		(0x607)	/* struct dtGeneral */
#define DTM_PRINT		(0x608)	/* struct dtPrint */
#define DTM_ABORTPRINT		(0x609)	/* struct dtGeneral */
#define DTM_NEWMEMBER		(0x610)
#define DTM_DISPOSEMEMBER	(0x611)
#define DTM_GOTO		(0x630)	/* struct dtGoto */
#define DTM_TRIGGER		(0x631)	/* struct dtTrigger */
#define DTM_OBTAINDRAWINFO	(0x640)	/* struct opSet */
#define DTM_DRAW		(0x641)	/* struct dtDraw */
#define DTM_RELEASEDRAWINFO	(0x642)
#define DTM_WRITE		(0x650)	/* struct dtWrite */

/* What an object's content is like, or what a frame should be */
struct FrameInfo {
	ULONG		fri_PropertyFlags;	/* DIPF_ of the display mode */
	Point		fri_Resolution;		/* the pixel aspect */

	UBYTE		fri_RedBits;
	UBYTE		fri_GreenBits;
	UBYTE		fri_BlueBits;

	struct {
		ULONG	Width;
		ULONG	Height;
		ULONG	Depth;
	} fri_Dimensions;

	struct Screen	*fri_Screen;
	struct ColorMap	*fri_ColorMap;

	ULONG		fri_Flags;		/* FIF_ */
};

/* fri_Flags */
#define FIF_SCALABLE	0x1
#define FIF_SCROLLABLE	0x2
#define FIF_REMAPPABLE	0x4

/* A method with only the GadgetInfo */
struct dtGeneral {
	ULONG			MethodID;
	struct GadgetInfo	*dtg_GInfo;
};

/* DTM_SELECT */
struct dtSelect {
	ULONG			MethodID;
	struct GadgetInfo	*dts_GInfo;
	struct Rectangle	dts_Select;
};

/* DTM_FRAMEBOX */
struct dtFrameBox {
	ULONG			MethodID;
	struct GadgetInfo	*dtf_GInfo;
	struct FrameInfo	*dtf_ContentsInfo;	/* the content's */
	struct FrameInfo	*dtf_FrameInfo;		/* to be filled in */
	ULONG			dtf_SizeFrameInfo;
	ULONG			dtf_FrameFlags;		/* FRAMEF_ */
};

/* dtf_FrameFlags */
#define FRAMEF_SPECIFY	(1<<0)	/* the frame is being given, not asked for */

/* DTM_GOTO */
struct dtGoto {
	ULONG			MethodID;
	struct GadgetInfo	*dtg_GInfo;
	STRPTR			dtg_NodeName;
	struct TagItem		*dtg_AttrList;
};

/* DTM_TRIGGER */
struct dtTrigger {
	ULONG			MethodID;
	struct GadgetInfo	*dtt_GInfo;
	ULONG			dtt_Function;	/* STM_ */
	APTR			dtt_Data;
};

/* dtt_Function */
#define STM_PAUSE		1
#define STM_PLAY		2
#define STM_CONTENTS		3
#define STM_INDEX		4
#define STM_RETRACE		5
#define STM_BROWSE_PREV		6
#define STM_BROWSE_NEXT		7
#define STM_NEXT_FIELD		8
#define STM_PREV_FIELD		9
#define STM_ACTIVATE_FIELD	10
#define STM_COMMAND		11
#define STM_REWIND		12
#define STM_FASTFORWARD		13
#define STM_STOP		14
#define STM_RESUME		15
#define STM_LOCATE		16
#define STM_HELP		17
#define STM_SEARCH		18
#define STM_SEARCH_NEXT		19
#define STM_SEARCH_PREV		20
#define STM_USER		100	/* a class's own start here */

/* dtt_Function: the method and the kind of data it takes */
#define STMF_METHOD_MASK	0x0000ffff
#define STMF_DATA_MASK		0x00ff0000
#define STMF_RESERVED_MASK	0xff000000

#define STMD_VOID	0x00010000
#define STMD_ULONG	0x00020000
#define STMD_STRPTR	0x00030000
#define STMD_TAGLIST	0x00040000

/* DTM_PRINT */
struct dtPrint {
	ULONG			MethodID;
	struct GadgetInfo	*dtp_GInfo;
	union printerIO		*dtp_PIO;
	struct TagItem		*dtp_AttrList;
};

/* DTM_DRAW */
struct dtDraw {
	ULONG		MethodID;
	struct RastPort	*dtd_RPort;
	LONG		dtd_Left;
	LONG		dtd_Top;
	LONG		dtd_Width;
	LONG		dtd_Height;
	LONG		dtd_TopHoriz;
	LONG		dtd_TopVert;
	struct TagItem	*dtd_AttrList;
};

/* DTM_WRITE */
struct dtWrite {
	ULONG			MethodID;
	struct GadgetInfo	*dtw_GInfo;
	BPTR			dtw_FileHandle;
	ULONG			dtw_Mode;	/* DTWM_ */
	struct TagItem		*dtw_AttrList;
};

/* dtw_Mode */
#define DTWM_IFF	0	/* as the IFF form the clipboard takes */
#define DTWM_RAW	1	/* as the data's own format */

/* More names from the 3.2 interface */
#define DTA_Class		(DTA_Dummy + 62)
#define STM_UNRETRACE		21

#endif /* DATATYPES_DATATYPESCLASS_H */
