#ifndef DEVICES_PRINTER_H
#define DEVICES_PRINTER_H
/*
 * OpenNDK: printer.device's commands, requests, ANSI-style command
 * numbers and graphic dump options.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef EXEC_IO_H
#include <exec/io.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif

struct RastPort;
struct ColorMap;
struct Window;
struct EasyStruct;

/* Commands */
#define PRD_RAWWRITE		(CMD_NONSTD+0)
#define PRD_PRTCOMMAND		(CMD_NONSTD+1)
#define PRD_DUMPRPORT		(CMD_NONSTD+2)
#define PRD_QUERY		(CMD_NONSTD+3)
#define PRD_RESETPREFS		(CMD_NONSTD+4)
#define PRD_LOADPREFS		(CMD_NONSTD+5)
#define PRD_USEPREFS		(CMD_NONSTD+6)
#define PRD_SAVEPREFS		(CMD_NONSTD+7)
#define PRD_READPREFS		(CMD_NONSTD+8)
#define PRD_WRITEPREFS		(CMD_NONSTD+9)
#define PRD_EDITPREFS		(CMD_NONSTD+10)
#define PRD_SETERRHOOK		(CMD_NONSTD+11)
#define PRD_DUMPRPORTTAGS	(CMD_NONSTD+12)
#define PRD_PRIVATE		(CMD_NONSTD+13)

/* Printer command numbers for PRD_PRTCOMMAND, and the escape
 * sequences written to the device that select them */
#define aRIS		0	/* ESCc	reset */
#define aRIN		1	/* ESC#1 initialise */
#define aIND		2	/* ESCD	line feed */
#define aNEL		3	/* ESCE	return and line feed */
#define aRI		4	/* ESCM	reverse line feed */

#define aSGR0		5	/* normal characters */
#define aSGR3		6	/* italics on */
#define aSGR23		7	/* italics off */
#define aSGR4		8	/* underline on */
#define aSGR24		9	/* underline off */
#define aSGR1		10	/* bold on */
#define aSGR22		11	/* bold off */
#define aSFC		12	/* foreground colour */
#define aSBC		13	/* background colour */

#define aSHORP0		14	/* normal pitch */
#define aSHORP2		15	/* elite on */
#define aSHORP1		16	/* elite off */
#define aSHORP4		17	/* condensed on */
#define aSHORP3		18	/* condensed off */
#define aSHORP6		19	/* enlarged on */
#define aSHORP5		20	/* enlarged off */

#define aDEN6		21	/* shadow print on */
#define aDEN5		22	/* shadow print off */
#define aDEN4		23	/* double strike on */
#define aDEN3		24	/* double strike off */
#define aDEN2		25	/* NLQ on */
#define aDEN1		26	/* NLQ off */

#define aSUS2		27	/* superscript on */
#define aSUS1		28	/* superscript off */
#define aSUS4		29	/* subscript on */
#define aSUS3		30	/* subscript off */
#define aSUS0		31	/* normalise the line */
#define aPLU		32	/* partial line up */
#define aPLD		33	/* partial line down */

#define aFNT0		34	/* character sets */
#define aFNT1		35
#define aFNT2		36
#define aFNT3		37
#define aFNT4		38
#define aFNT5		39
#define aFNT6		40
#define aFNT7		41
#define aFNT8		42
#define aFNT9		43
#define aFNT10		44

#define aPROP2		45	/* proportional on */
#define aPROP1		46	/* proportional off */
#define aPROP0		47	/* proportional clear */
#define aTSS		48	/* proportional offset */
#define aJFY5		49	/* auto left justify */
#define aJFY7		50	/* auto right justify */
#define aJFY6		51	/* auto full justify */
#define aJFY0		52	/* justification off */
#define aJFY3		53	/* letter space */
#define aJFY1		54	/* word fill */

#define aVERP0		55	/* 1/8" line spacing */
#define aVERP1		56	/* 1/6" line spacing */
#define aSLPP		57	/* form length */
#define aPERF		58	/* perforation skip */
#define aPERF0		59	/* perforation skip off */

#define aLMS		60	/* left margin */
#define aRMS		61	/* right margin */
#define aTMS		62	/* top margin */
#define aBMS		63	/* bottom margin */
#define aSTBM		64	/* top and bottom margins */
#define aSLRM		65	/* left and right margins */
#define aCAM		66	/* clear margins */

#define aHTS		67	/* set horizontal tab */
#define aVTS		68	/* set vertical tab */
#define aTBC0		69	/* clear horizontal tab */
#define aTBC3		70	/* clear all horizontal tabs */
#define aTBC1		71	/* clear vertical tab */
#define aTBC4		72	/* clear all vertical tabs */
#define aTBCALL		73	/* clear all tabs */
#define aTBSALL		74	/* default tabs */

#define aEXTEND		75	/* extended commands */
#define aRAW		76	/* the next n bytes are raw */

/* PRD_PRTCOMMAND's request */
struct IOPrtCmdReq {
	struct Message	io_Message;
	struct Device	*io_Device;
	struct Unit	*io_Unit;
	UWORD		io_Command;
	UBYTE		io_Flags;
	BYTE		io_Error;
	UWORD		io_PrtCommand;	/* a command number above */
	UBYTE		io_Parm0;
	UBYTE		io_Parm1;
	UBYTE		io_Parm2;
	UBYTE		io_Parm3;
};

/* PRD_DUMPRPORT's request */
struct IODRPReq {
	struct Message	io_Message;
	struct Device	*io_Device;
	struct Unit	*io_Unit;
	UWORD		io_Command;
	UBYTE		io_Flags;
	BYTE		io_Error;
	struct RastPort	*io_RastPort;
	struct ColorMap	*io_ColorMap;
	ULONG		io_Modes;	/* the display mode ID */
	UWORD		io_SrcX;
	UWORD		io_SrcY;
	UWORD		io_SrcWidth;
	UWORD		io_SrcHeight;
	LONG		io_DestCols;
	LONG		io_DestRows;
	UWORD		io_Special;	/* SPECIAL_ */
};

/* PRD_DUMPRPORTTAGS's request: the same with a tag list */
struct IODRPTagsReq {
	struct Message	io_Message;
	struct Device	*io_Device;
	struct Unit	*io_Unit;
	UWORD		io_Command;
	UBYTE		io_Flags;
	BYTE		io_Error;
	struct RastPort	*io_RastPort;
	struct ColorMap	*io_ColorMap;
	ULONG		io_Modes;
	UWORD		io_SrcX;
	UWORD		io_SrcY;
	UWORD		io_SrcWidth;
	UWORD		io_SrcHeight;
	LONG		io_DestCols;
	LONG		io_DestRows;
	UWORD		io_Special;
	struct TagItem	*io_TagList;	/* DRPA_ */
};

/* io_Special */
#define SPECIAL_MILCOLS		0x0001	/* io_DestCols in 1/1000" */
#define SPECIAL_MILROWS		0x0002	/* io_DestRows in 1/1000" */
#define SPECIAL_FULLCOLS	0x0004	/* the full page width */
#define SPECIAL_FULLROWS	0x0008	/* the full page height */
#define SPECIAL_FRACCOLS	0x0010	/* a fraction of the width */
#define SPECIAL_FRACROWS	0x0020	/* a fraction of the height */
#define SPECIAL_CENTER		0x0040	/* centre on the page */
#define SPECIAL_ASPECT		0x0080	/* keep the aspect ratio */
#define SPECIAL_DENSITY1	0x0100	/* the lowest density */
#define SPECIAL_DENSITY2	0x0200
#define SPECIAL_DENSITY3	0x0300
#define SPECIAL_DENSITY4	0x0400
#define SPECIAL_DENSITY5	0x0500
#define SPECIAL_DENSITY6	0x0600
#define SPECIAL_DENSITY7	0x0700	/* the highest density */
#define SPECIAL_NOFORMFEED	0x0800	/* no page eject afterwards */
#define SPECIAL_TRUSTME		0x1000	/* send no reset first */
#define SPECIAL_NOPRINT		0x2000	/* only work out the size */

/* io_Error */
#define PDERR_NOERR		0
#define PDERR_CANCEL		1	/* the user cancelled */
#define PDERR_NOTGRAPHICS	2	/* the printer has no graphics */
#define PDERR_INVERTHAM		3	/* obsolete */
#define PDERR_BADDIMENSION	4
#define PDERR_DIMENSIONOVFLOW	5	/* obsolete */
#define PDERR_INTERNALMEMORY	6
#define PDERR_BUFFERMEMORY	7
#define PDERR_TOOKCONTROL	8	/* the driver printed it itself */
#define PDERR_BADPREFERENCES	9

#define PDERR_LASTSTANDARD	31
#define PDERR_FIRSTCUSTOM	32
#define PDERR_LASTCUSTOM	126

#define SPECIAL_DENSITYMASK	0x0700
#define SPECIAL_DIMENSIONSMASK \
	(SPECIAL_MILCOLS|SPECIAL_MILROWS|SPECIAL_FULLCOLS|SPECIAL_FULLROWS \
	|SPECIAL_FRACCOLS|SPECIAL_FRACROWS|SPECIAL_ASPECT)

/* PRD_EDITPREFS's request */
struct IOPrtPrefsReq {
	struct Message	io_Message;
	struct Device	*io_Device;
	struct Unit	*io_Unit;
	UWORD		io_Command;
	UBYTE		io_Flags;
	BYTE		io_Error;
	struct TagItem	*io_TagList;
};

/* PRD_SETERRHOOK's request */
struct IOPrtErrReq {
	struct Message	io_Message;
	struct Device	*io_Device;
	struct Unit	*io_Unit;
	UWORD		io_Command;
	UBYTE		io_Flags;
	BYTE		io_Error;
	struct Hook	*io_Hook;	/* or a PDHOOK_ value */
};

#define PDHOOK_NONE	((struct Hook *)0)	/* no requesters */
#define PDHOOK_DEFAULT	((struct Hook *)1)	/* the device's own */

#define PDHOOK_VERSION	1

/* The message an error hook receives */
struct PrtErrMsg {
	ULONG		pe_Version;	/* PDHOOK_VERSION */
	ULONG		pe_ErrorLevel;
	struct Window	*pe_Window;
	struct EasyStruct *pe_ES;
	ULONG		*pe_IDCMP;
	APTR		pe_ArgList;
};

/* PRD_DUMPRPORTTAGS tags */
#define DRPA_Dummy		(TAG_USER + 0x60000)
#define DRPA_ICCProfile		(DRPA_Dummy+1)	/* a colour profile */
#define DRPA_ICCName		(DRPA_Dummy+2)	/* or its name */
#define DRPA_NoColCorrect	(DRPA_Dummy+3)
#define DRPA_SourceHook		(DRPA_Dummy+4)	/* pixels from a hook */
#define DRPA_AspectX		(DRPA_Dummy+5)
#define DRPA_AspectY		(DRPA_Dummy+6)

/* What DRPA_SourceHook's hook is asked for: a block of RGB pixels */
struct DRPSourceMsg {
	LONG	x;
	LONG	y;
	LONG	width;
	LONG	height;
	ULONG	*buf;	/* width * height of 0x00RRGGBB */
};

/* PRD_READPREFS and PRD_WRITEPREFS's request: the four prefs to read or set */
struct IOPrefsReq {
	struct Message	io_Message;
	struct Device	*io_Device;
	struct Unit	*io_Unit;
	UWORD		io_Command;
	UBYTE		io_Flags;
	BYTE		io_Error;
	struct PrinterTxtPrefs *io_TxtPrefs;
	struct PrinterUnitPrefs *io_UnitPrefs;
	struct PrinterDeviceUnitPrefs *io_DevUnitPrefs;
	struct PrinterGfxPrefs *io_GfxPrefs;
};

/* Room for any of the printer's requests */
union printerIO {
	struct IOStdReq		ios;
	struct IODRPReq		iodrp;
	struct IOPrtCmdReq	iopc;
};

/* More names from the 3.2 interface */
#define PPRA_Dummy		0x80070000UL
#define PDHOOK_STD		((struct Hook *)1)	/* the device's own, by its 3.2 name */
#define PPRA_PubScreen		(PPRA_Dummy + 3)
#define PPRA_Screen		(PPRA_Dummy + 2)
#define PPRA_Window		(PPRA_Dummy + 1)
#define PRD_LASTSAVEDPREFS	23
#define PRD_PRIVATECMD		22

#endif /* DEVICES_PRINTER_H */
