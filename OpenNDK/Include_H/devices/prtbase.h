#ifndef DEVICES_PRTBASE_H
#define DEVICES_PRTBASE_H
/*
 * OpenNDK: what a printer driver sees: the unit's PrinterData, and the
 * PrinterSegment and PrinterExtendedData a driver begins with.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef EXEC_TASKS_H
#include <exec/tasks.h>
#endif
#ifndef DEVICES_PARALLEL_H
#include <devices/parallel.h>
#endif
#ifndef DEVICES_SERIAL_H
#include <devices/serial.h>
#endif
#ifndef DEVICES_TIMER_H
#include <devices/timer.h>
#endif
#ifndef DOS_DOSEXTENS_H
#include <dos/dosextens.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef LIBRARIES_DOSEXTENS_H
#include <libraries/dosextens.h>
#endif

/* The device's library node and command table */
/* The driver's and the device's calls take their arguments on the stack */
#ifndef PRT_STDARGS
#define PRT_STDARGS __STDARGS__
#endif

struct Hook;
struct PrtErrMsg;
struct PrinterData;
union printerIO;

struct DeviceData {
	struct Library	dd_Device;
	APTR		dd_Segment;
	APTR		dd_ExecBase;
	APTR		dd_CmdVectors;
	APTR		dd_CmdBytes;
	UWORD		dd_NumCommands;
};

#define P_OLDSTKSIZE	0x0800
#define P_STKSIZE	0x1000
#define P_BUFSIZE	256
#define P_SAFESIZE	128

struct PrinterUnit;

/* One unit's state, passed to the driver */
struct PrinterData {
	struct DeviceData	pd_Device;
	struct MsgPort		pd_Unit;
	BPTR			pd_PrinterSegment;	/* the driver */
	UWORD			pd_PrinterType;
	struct PrinterSegment	*pd_SegmentData;
	UBYTE			*pd_PrintBuf;
	LONG	(* PRT_STDARGS pd_PWrite)(APTR buffer, LONG length);		/* write to the port */
	LONG	(* PRT_STDARGS pd_PBothReady)(void);	/* wait for both writes */
	union {
		struct IOExtPar	pd_p0;
		struct IOExtSer	pd_s0;
	} pd_ior0;
	union {
		struct IOExtPar	pd_p1;
		struct IOExtSer	pd_s1;
	} pd_ior1;
	struct timerequest	pd_TIOR;
	struct MsgPort		pd_IORPort;
	struct Task		pd_TC;
	UBYTE			pd_OldStk[P_OLDSTKSIZE];
	UBYTE			pd_Flags;
	UBYTE			pd_pad;
	struct Preferences	pd_Preferences;		/* the unit's copy */
	UBYTE			pd_PWaitEnabled;
	/* V36 */
	UBYTE			pd_Flags1;
	UBYTE			pd_Stk[P_STKSIZE];
	/* V44 */
	struct PrinterUnit	*pd_PUnit;
	LONG	(* PRT_STDARGS pd_PRead)(APTR buffer, LONG *length, TimeVal_Type *tv);		/* read from the port */
	LONG	(* PRT_STDARGS pd_CallErrHook)(struct Hook *hook, union printerIO *ior, struct PrtErrMsg *pem);	/* report an error */
	ULONG			pd_UnitNumber;
	STRPTR			pd_DriverName;
	LONG	(* PRT_STDARGS pd_PQuery)(LONG *numofchars);		/* port status */
};

#define pd_PIOR0	pd_ior0.pd_p0
#define pd_SIOR0	pd_ior0.pd_s0
#define pd_PIOR1	pd_ior1.pd_p1
#define pd_SIOR1	pd_ior1.pd_s1

/* ped_PrinterClass bits */
#define PPCB_GFX	0	/* graphics */
#define PPCF_GFX	0x1
#define PPCB_COLOR	1	/* colour */
#define PPCF_COLOR	0x2

/* ped_PrinterClass values */
#define PPC_BWALPHA	0x00	/* black and white text */
#define PPC_BWGFX	0x01	/* black and white graphics */
#define PPC_COLORALPHA	0x02	/* colour text */
#define PPC_COLORGFX	0x03	/* colour graphics */
#define PPC_EXTENDED	0x04	/* ped_TagList is valid */

/* ped_ColorClass */
#define PCC_BW		0x01	/* black only */
#define PCC_YMC		0x02	/* yellow, magenta, cyan */
#define PCC_YMC_BW	0x03	/* those or black, not mixed */
#define PCC_YMCB	0x04	/* those and black */
#define PCC_4COLOR	0x04
#define PCC_ADDITIVE	0x08	/* red, green, blue */
#define PCC_WB		0x09	/* white only */
#define PCC_BGR		0x0A	/* blue, green, red */
#define PCC_BGR_WB	0x0B	/* those or white */
#define PCC_BGRW	0x0C	/* those and white */
#define PCC_MULTI_PASS	0x10	/* one pass per colour */

/* What a driver describes itself with */
struct PrinterExtendedData {
	STRPTR	ped_PrinterName;
	VOID	(* PRT_STDARGS ped_Init)(struct PrinterData *pd);
	VOID	(* PRT_STDARGS ped_Expunge)(void);
	int	(* PRT_STDARGS ped_Open)(struct IORequest *ior);
	VOID	(* PRT_STDARGS ped_Close)(struct IORequest *ior);
	UBYTE	ped_PrinterClass;	/* PPC_ */
	UBYTE	ped_ColorClass;		/* PCC_ */
	UBYTE	ped_MaxColumns;
	UBYTE	ped_NumCharSets;
	UWORD	ped_NumRows;		/* pins in the print head */
	ULONG	ped_MaxXDots;
	ULONG	ped_MaxYDots;
	UWORD	ped_XDotsInch;
	UWORD	ped_YDotsInch;
	STRPTR	**ped_Commands;	/* the escape sequence of each aXXX */
	LONG	(* PRT_STDARGS ped_DoSpecial)(UWORD *command, UBYTE output_buffer[], BYTE *current_line_position, BYTE *current_line_spacing, BYTE *crlf_flag, STRPTR params);
	LONG	(* PRT_STDARGS ped_Render)(LONG ct, LONG x, LONG y, LONG status, ...);
	LONG	ped_TimeoutSecs;
	/* V33 */
	STRPTR	*ped_8BitChars;	/* text for 0xA0-0xFF */
	LONG	ped_PrintMode;
	/* V34 */
	LONG	(* PRT_STDARGS ped_ConvFunc)(STRPTR buf, TEXT c, LONG crlf_flag);
	/* V44 */
	struct TagItem *ped_TagList;	/* PRTA_, with PPC_EXTENDED */
	LONG	(* PRT_STDARGS ped_DoPreferences)(union printerIO *ior, LONG command);
	VOID	(* PRT_STDARGS ped_CallErrHook)(union printerIO *ior, struct Hook *hook);
};

/* ped_TagList tags */
#define PRTA_Dummy		(TAG_USER + 0x50000)
#define PRTA_8BitGuns		(PRTA_Dummy + 1)
#define PRTA_ConvertSource	(PRTA_Dummy + 2)
#define PRTA_FloydDithering	(PRTA_Dummy + 3)
#define PRTA_AntiAlias		(PRTA_Dummy + 4)
#define PRTA_ColorCorrection	(PRTA_Dummy + 5)
#define PRTA_NoIO		(PRTA_Dummy + 6)
#define PRTA_NewColor		(PRTA_Dummy + 7)
#define PRTA_ColorSize		(PRTA_Dummy + 8)
#define PRTA_NoScaling		(PRTA_Dummy + 9)

/* The start of a driver's first hunk */
struct PrinterSegment {
	BPTR	ps_NextSegment;
	ULONG	ps_runAlert;		/* code: MOVEQ #0,D0 then RTS */
	UWORD	ps_Version;
	UWORD	ps_Revision;
	struct PrinterExtendedData ps_PED;
};

/* More names from the 3.2 interface */
#define DUB_STOPPED		0
#define DUF_STOPPED		1
#define IOB_CURRENT		5
#define IOB_DONE		7
#define IOB_QUEUED		4
#define IOB_SERVICING		6
#define IOF_CURRENT		32
#define IOF_DONE		128
#define IOF_QUEUED		16
#define IOF_SERVICING		64
#define PB_EXPUNGED		7
#define PB_IOOPENED		2
#define PB_IOR0			0
#define PB_IOR1			1
#define PF_EXPUNGED		128
#define PF_IOOPENDED		4
#define PF_IOR0			1
#define PF_IOR1			2
#define PPCB_EXTENDED		2
#define PPCB_NOSTRIP		3
#define PPCF_EXTENDED		4
#define PPCF_NOSTRIP		8
#define PRTA_ColorCorrect	(PRTA_Dummy + 22)
#define PRTA_DensityInfo	(PRTA_Dummy + 23)
#define PRTA_DitherNames	(PRTA_Dummy + 20)
#define PRTA_LeftBorder		(PRTA_Dummy + 30)
#define PRTA_MixBWColor		(PRTA_Dummy + 32)
#define PRTA_Preferences	(PRTA_Dummy + 40)
#define PRTA_ShadingNames	(PRTA_Dummy + 21)
#define PRTA_TopBorder		(PRTA_Dummy + 31)

#endif /* DEVICES_PRTBASE_H */
