#ifndef DOS_FILEHANDLER_H
#define DOS_FILEHANDLER_H
/*
 * OpenNDK: what a mounted device tells its file system: the disk's
 * geometry (DosEnvec), the startup message and the device node.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

/* The environment vector: a mountlist entry's numbers, longword by
 * longword. de_TableSize says how many follow it. */
struct DosEnvec {
	ULONG	de_TableSize;
	ULONG	de_SizeBlock;		/* block size in longwords */
	ULONG	de_SecOrg;		/* unused; 0 */
	ULONG	de_Surfaces;		/* heads */
	ULONG	de_SectorPerBlock;
	ULONG	de_BlocksPerTrack;
	ULONG	de_Reserved;		/* blocks reserved at the start */
	ULONG	de_PreAlloc;		/* blocks reserved at the end */
	ULONG	de_Interleave;
	ULONG	de_LowCyl;
	ULONG	de_HighCyl;
	ULONG	de_NumBuffers;
	ULONG	de_BufMemType;		/* MEMF_ for the buffers */
	ULONG	de_MaxTransfer;		/* largest single transfer, bytes */
	ULONG	de_Mask;		/* addresses the device can reach */
	LONG	de_BootPri;
	ULONG	de_DosType;
	ULONG	de_Baud;
	ULONG	de_Control;
	ULONG	de_BootBlocks;
};

/* Longword indexes into a DosEnvec */
#define DE_TABLESIZE	0
#define DE_SIZEBLOCK	1
#define DE_SECORG	2
#define DE_NUMHEADS	3
#define DE_SECSPERBLK	4
#define DE_BLKSPERTRACK	5
#define DE_RESERVEDBLKS	6
#define DE_PREFAC	7
#define DE_INTERLEAVE	8
#define DE_LOWCYL	9
#define DE_UPPERCYL	10
#define DE_NUMBUFFERS	11
#define DE_MEMBUFTYPE	12
#define DE_BUFMEMTYPE	12
#define DE_MAXTRANSFER	13
#define DE_MASK		14
#define DE_BOOTPRI	15
#define DE_DOSTYPE	16
#define DE_BAUD		17
#define DE_CONTROL	18
#define DE_BOOTBLOCKS	19

/* The startup argument a disk file system gets (dn_Startup) */
struct FileSysStartupMsg {
	ULONG	fssm_Unit;		/* exec unit number */
	BSTR	fssm_Device;		/* exec device name */
	BPTR	fssm_Environ;		/* struct DosEnvec */
	ULONG	fssm_Flags;		/* OpenDevice() flags */
};

/* A device's entry in the device list, as handlers see it */
struct DeviceNode {
	BPTR		dn_Next;
	ULONG		dn_Type;	/* DLT_DEVICE */
	struct MsgPort	*dn_Task;	/* the running handler, or 0 */
	BPTR		dn_Lock;
	BSTR		dn_Handler;	/* file to load the handler from */
	ULONG		dn_StackSize;
	LONG		dn_Priority;
	BPTR		dn_Startup;	/* often a FileSysStartupMsg */
	BPTR		dn_SegList;	/* the loaded handler */
	BPTR		dn_GlobalVec;
	BSTR		dn_Name;
};

/* More names from the 3.2 interface */
#define ENVF_DISABLENSD		0x40000
#define ENVF_SCSIDIRECT		0x10000
#define ENVF_SUPERFLOPPY	0x20000

#endif /* DOS_FILEHANDLER_H */
