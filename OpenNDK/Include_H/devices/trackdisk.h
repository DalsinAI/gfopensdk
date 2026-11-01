#ifndef DEVICES_TRACKDISK_H
#define DEVICES_TRACKDISK_H
/*
 * OpenNDK: trackdisk.device's commands, request, geometry and errors;
 * the commands most disk devices share.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_IO_H
#include <exec/io.h>
#endif
#ifndef EXEC_DEVICES_H
#include <exec/devices.h>
#endif

/* Physical layout of a standard floppy */
#define NUMCYLS		80
#define MAXCYL		(NUMCYLS-1)
#define NUMHEADS	2
#define NUMTRACKS	(NUMCYLS*NUMHEADS)
#define NUMSECS		11
#define NUMUNITS	4

#define TD_SECTOR	512
#define TD_SECSHIFT	9

#define TD_NAME		"trackdisk.device"

/* Commands */
#define TDF_EXTCOM	(1<<15)	/* the extended form */

#define TD_MOTOR	(CMD_NONSTD+0)
#define TD_SEEK		(CMD_NONSTD+1)
#define TD_FORMAT	(CMD_NONSTD+2)
#define TD_REMOVE	(CMD_NONSTD+3)
#define TD_CHANGENUM	(CMD_NONSTD+4)
#define TD_CHANGESTATE	(CMD_NONSTD+5)
#define TD_PROTSTATUS	(CMD_NONSTD+6)
#define TD_RAWREAD	(CMD_NONSTD+7)
#define TD_RAWWRITE	(CMD_NONSTD+8)
#define TD_GETDRIVETYPE	(CMD_NONSTD+9)
#define TD_GETNUMTRACKS	(CMD_NONSTD+10)
#define TD_ADDCHANGEINT	(CMD_NONSTD+11)
#define TD_REMCHANGEINT	(CMD_NONSTD+12)
#define TD_GETGEOMETRY	(CMD_NONSTD+13)
#define TD_EJECT	(CMD_NONSTD+14)
#define TD_LASTCOMM	(CMD_NONSTD+15)

/* The extended forms check iotd_Count against the disk change count */
#define ETD_WRITE	(CMD_WRITE|TDF_EXTCOM)
#define ETD_READ	(CMD_READ|TDF_EXTCOM)
#define ETD_MOTOR	(TD_MOTOR|TDF_EXTCOM)
#define ETD_SEEK	(TD_SEEK|TDF_EXTCOM)
#define ETD_FORMAT	(TD_FORMAT|TDF_EXTCOM)
#define ETD_UPDATE	(CMD_UPDATE|TDF_EXTCOM)
#define ETD_CLEAR	(CMD_CLEAR|TDF_EXTCOM)
#define ETD_RAWREAD	(TD_RAWREAD|TDF_EXTCOM)
#define ETD_RAWWRITE	(TD_RAWWRITE|TDF_EXTCOM)

/* 64-bit offset commands (io_Actual holds the high longword) */
#define NSCMD_TD_READ64		0xC000
#define NSCMD_TD_WRITE64	0xC001
#define NSCMD_TD_SEEK64		0xC002
#define NSCMD_TD_FORMAT64	0xC003
#define NSCMD_ETD_READ64	0xE000
#define NSCMD_ETD_WRITE64	0xE001
#define NSCMD_ETD_SEEK64	0xE002
#define NSCMD_ETD_FORMAT64	0xE003

/* The request of the extended commands */
struct IOExtTD {
	struct IOStdReq	iotd_Req;
	ULONG		iotd_Count;	/* the change count expected */
	APTR		iotd_SecLabel;	/* sector label buffer */
};

/* What TD_GETGEOMETRY fills */
struct DriveGeometry {
	ULONG	dg_SectorSize;
	ULONG	dg_TotalSectors;
	ULONG	dg_Cylinders;
	ULONG	dg_CylSectors;
	ULONG	dg_Heads;
	ULONG	dg_TrackSectors;
	ULONG	dg_BufMemType;		/* MEMF_ the device prefers */
	UBYTE	dg_DeviceType;		/* DG_ */
	UBYTE	dg_Flags;		/* DGF_ */
	UWORD	dg_Reserved;
};

/* dg_DeviceType: the SCSI peripheral types */
#define DG_DIRECT_ACCESS	0
#define DG_SEQUENTIAL_ACCESS	1
#define DG_PRINTER		2
#define DG_PROCESSOR		3
#define DG_WORM			4
#define DG_CDROM		5
#define DG_SCANNER		6
#define DG_OPTICAL_DISK		7
#define DG_MEDIUM_CHANGER	8
#define DG_COMMUNICATION	9
#define DG_UNKNOWN		31

/* dg_Flags */
#define DGB_REMOVABLE	0
#define DGF_REMOVABLE	1

/* io_Flags */
#define IOTDB_INDEXSYNC	4	/* raw I/O starts at the index pulse */
#define IOTDF_INDEXSYNC	(1<<4)
#define IOTDB_WORDSYNC	5	/* raw read starts at a sync word */
#define IOTDF_WORDSYNC	(1<<5)

/* the extra label bytes of a sector */
#define TD_LABELSIZE	16

/* OpenDevice() flags */
#define TDB_ALLOW_NON_3_5	0	/* allow 5.25" drives */
#define TDF_ALLOW_NON_3_5	(1<<0)

/* TD_GETDRIVETYPE */
#define DRIVE3_5	1
#define DRIVE5_25	2
#define DRIVE3_5_150RPM	3	/* high density */

/* io_Error */
#define TDERR_NotSpecified	20
#define TDERR_NoSecHdr		21
#define TDERR_BadSecPreamble	22
#define TDERR_BadSecID		23
#define TDERR_BadHdrSum		24
#define TDERR_BadSecSum		25
#define TDERR_TooFewSecs	26
#define TDERR_BadSecHdr		27
#define TDERR_WriteProt		28
#define TDERR_DiskChanged	29
#define TDERR_SeekError		30
#define TDERR_NoMem		31
#define TDERR_BadUnitNum	32
#define TDERR_BadDriveType	33
#define TDERR_DriveInUse	34
#define TDERR_PostReset		35

/* The public part of a trackdisk unit; programs may tune these */
struct TDU_PublicUnit {
	struct Unit	tdu_Unit;
	UWORD	tdu_Comp01Track;	/* precompensation start tracks */
	UWORD	tdu_Comp10Track;
	UWORD	tdu_Comp11Track;
	ULONG	tdu_StepDelay;		/* microseconds */
	ULONG	tdu_SettleDelay;
	UBYTE	tdu_RetryCnt;
	UBYTE	tdu_PubFlags;		/* TDPF_ */
	UWORD	tdu_CurrTrk;
	ULONG	tdu_CalibrateDelay;
	ULONG	tdu_Counter;		/* private */
	ULONG	tdu_PostWriteDelay;	/* microseconds to wait after a write */
	ULONG	tdu_SideSelectDelay;	/* microseconds to wait after choosing a side */
};

#define TDPB_NOCLICK	0	/* don't click an empty drive */
#define TDPF_NOCLICK	(1L<<0)

/* More names from the 3.2 interface */
#define TD_FORMAT64		27
#define TD_READ64		24
#define TD_SEEK64		26
#define TD_WRITE64		25

#endif /* DEVICES_TRACKDISK_H */
