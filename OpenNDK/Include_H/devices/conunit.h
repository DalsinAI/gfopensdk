#ifndef DEVICES_CONUNIT_H
#define DEVICES_CONUNIT_H
/*
 * OpenNDK: a console unit, as console.device keeps it per window.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef DEVICES_CONSOLE_H
#include <devices/console.h>
#endif
#ifndef DEVICES_KEYMAP_H
#include <devices/keymap.h>
#endif
#ifndef DEVICES_INPUTEVENT_H
#include <devices/inputevent.h>
#endif

struct Window;
struct TextFont;

/* Units OpenDevice() takes */
#define CONU_LIBRARY	-1	/* no window: for RawKeyConvert() only */
#define CONU_STANDARD	0
#define CONU_CHARMAP	1	/* keeps a character map, redraws on resize */
#define CONU_SNIPMAP	3	/* and allows cut and paste */

/* OpenDevice() flags */
#define CONFLAG_DEFAULT			0
#define CONFLAG_NODRAW_ON_NEWSIZE	1

/* Bits of cu_Modes past the ANSI ones */
#define PMB_ASM		(M_LNM+1)	/* auto scroll */
#define PMB_AWM		(PMB_ASM+1)	/* auto wrap */
#define MAXTABS		80

struct ConUnit {
	struct MsgPort	cu_MP;
	struct Window	*cu_Window;
	WORD	cu_XCP;			/* cursor, in characters */
	WORD	cu_YCP;
	WORD	cu_XMax;		/* last column and row */
	WORD	cu_YMax;
	WORD	cu_XRSize;		/* character size, in pixels */
	WORD	cu_YRSize;
	WORD	cu_XROrigin;		/* the text area, in pixels */
	WORD	cu_YROrigin;
	WORD	cu_XRExtant;
	WORD	cu_YRExtant;
	WORD	cu_XMinShrink;
	WORD	cu_YMinShrink;
	WORD	cu_XCCP;		/* cursor, in pixels */
	WORD	cu_YCCP;
	struct KeyMap	cu_KeyMapStruct;
	UWORD	cu_TabStops[MAXTABS];	/* 0xFFFF ends the list */
	BYTE	cu_Mask;
	BYTE	cu_FgPen;
	BYTE	cu_BgPen;
	BYTE	cu_AOLPen;
	BYTE	cu_DrawMode;
	BYTE	cu_Obsolete1;
	APTR	cu_Obsolete2;
	UBYTE	cu_Minterms[8];
	struct TextFont	*cu_Font;
	UBYTE	cu_AlgoStyle;
	UBYTE	cu_TxFlags;
	UWORD	cu_TxHeight;
	UWORD	cu_TxWidth;
	UWORD	cu_TxBaseline;
	WORD	cu_TxSpacing;
	UBYTE	cu_Modes[(PMB_AWM+7)/8];		/* mode bits */
	UBYTE	cu_RawEvents[(IECLASS_MAX+8)/8];	/* raw events asked for */
};

#endif /* DEVICES_CONUNIT_H */
