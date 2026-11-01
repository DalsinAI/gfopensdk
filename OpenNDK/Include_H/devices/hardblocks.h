#ifndef DEVICES_HARDBLOCKS_H
#define DEVICES_HARDBLOCKS_H
/*
 * OpenNDK: the Rigid Disk Block family: the blocks near the start of a
 * hard disk that describe its geometry, partitions and file systems.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* Block pointers below are block numbers; 0xffffffff means none. Each
 * block's checksum makes the sum of its summed longwords zero. */

struct RigidDiskBlock {
	ULONG	rdb_ID;			/* IDNAME_RIGIDDISK */
	ULONG	rdb_SummedLongs;	/* 64 */
	LONG	rdb_ChkSum;
	ULONG	rdb_HostID;		/* the controller's SCSI ID */
	ULONG	rdb_BlockBytes;
	ULONG	rdb_Flags;		/* RDBF_ */
	/* block lists */
	ULONG	rdb_BadBlockList;
	ULONG	rdb_PartitionList;
	ULONG	rdb_FileSysHeaderList;
	ULONG	rdb_DriveInit;
	ULONG	rdb_Reserved1[6];	/* 0xffffffff */
	/* physical geometry */
	ULONG	rdb_Cylinders;
	ULONG	rdb_Sectors;
	ULONG	rdb_Heads;
	ULONG	rdb_Interleave;
	ULONG	rdb_Park;
	ULONG	rdb_Reserved2[3];
	ULONG	rdb_WritePreComp;
	ULONG	rdb_ReducedWrite;
	ULONG	rdb_StepRate;
	ULONG	rdb_Reserved3[5];
	/* logical geometry */
	ULONG	rdb_RDBBlocksLo;	/* the blocks the RDB area may use */
	ULONG	rdb_RDBBlocksHi;
	ULONG	rdb_LoCylinder;		/* the cylinders partitions may use */
	ULONG	rdb_HiCylinder;
	ULONG	rdb_CylBlocks;
	ULONG	rdb_AutoParkSeconds;
	ULONG	rdb_HighRDSKBlock;	/* the highest block in use */
	ULONG	rdb_Reserved4;
	/* identification */
	char	rdb_DiskVendor[8];
	char	rdb_DiskProduct[16];
	char	rdb_DiskRevision[4];
	char	rdb_ControllerVendor[8];
	char	rdb_ControllerProduct[16];
	char	rdb_ControllerRevision[4];
	char	rdb_DriveInitName[40];	/* a drive-init program to run, by name */
};

#define IDNAME_RIGIDDISK	0x5244534B	/* RDSK */

#define RDB_LOCATION_LIMIT	16	/* searched for in blocks 0-15 */

#define RDBFB_LAST	0	/* no disks after this one */
#define RDBFF_LAST	0x01L
#define RDBFB_LASTLUN	1	/* no LUNs after this one */
#define RDBFF_LASTLUN	0x02L
#define RDBFB_LASTTID	2	/* no target IDs after this one */
#define RDBFF_LASTTID	0x04L
#define RDBFB_NORESELECT 3	/* the drive cannot reselect */
#define RDBFF_NORESELECT 0x08L
#define RDBFB_DISKID	4	/* the disk fields are valid */
#define RDBFF_DISKID	0x10L
#define RDBFB_CTRLRID	5	/* the controller fields are valid */
#define RDBFF_CTRLRID	0x20L
#define RDBFB_SYNCH	6	/* use synchronous SCSI */
#define RDBFF_SYNCH	0x40L

/* A bad block and its replacement */
struct BadBlockEntry {
	ULONG	bbe_BadBlock;
	ULONG	bbe_GoodBlock;
};

struct BadBlockBlock {
	ULONG	bbb_ID;			/* IDNAME_BADBLOCK */
	ULONG	bbb_SummedLongs;	/* 128 */
	LONG	bbb_ChkSum;
	ULONG	bbb_HostID;
	ULONG	bbb_Next;
	ULONG	bbb_Reserved;
	struct BadBlockEntry bbb_BlockPairs[61];
};

#define IDNAME_BADBLOCK		0x42414442	/* BADB */

/* One partition */
struct PartitionBlock {
	ULONG	pb_ID;			/* IDNAME_PARTITION */
	ULONG	pb_SummedLongs;		/* 64 */
	LONG	pb_ChkSum;
	ULONG	pb_HostID;
	ULONG	pb_Next;
	ULONG	pb_Flags;		/* PBFF_ */
	ULONG	pb_Reserved1[2];
	ULONG	pb_DevFlags;		/* OpenDevice() flags */
	UBYTE	pb_DriveName[32];	/* a BSTR: the DOS device name */
	ULONG	pb_Reserved2[15];
	ULONG	pb_Environment[20];	/* a DosEnvec */
	ULONG	pb_EReserved[12];
};

#define IDNAME_PARTITION	0x50415254	/* PART */

#define PBFB_BOOTABLE	0	/* boot from it */
#define PBFF_BOOTABLE	1L
#define PBFB_NOMOUNT	1	/* don't mount it */
#define PBFF_NOMOUNT	2L

/* A file system stored on the disk */
struct FileSysHeaderBlock {
	ULONG	fhb_ID;			/* IDNAME_FSHEADER */
	ULONG	fhb_SummedLongs;	/* 64 */
	LONG	fhb_ChkSum;
	ULONG	fhb_HostID;
	ULONG	fhb_Next;
	ULONG	fhb_Flags;
	ULONG	fhb_Reserved1[2];
	ULONG	fhb_DosType;		/* the DosType it handles */
	ULONG	fhb_Version;		/* version << 16 | revision */
	ULONG	fhb_PatchFlags;		/* which fields below to use */
	/* DeviceNode fields, patched in by PatchFlags bit order */
	ULONG	fhb_Type;
	ULONG	fhb_Task;
	ULONG	fhb_Lock;
	ULONG	fhb_Handler;
	ULONG	fhb_StackSize;
	LONG	fhb_Priority;
	LONG	fhb_Startup;
	LONG	fhb_SegListBlocks;	/* the first LoadSegBlock */
	LONG	fhb_GlobalVec;
	ULONG	fhb_Reserved2[23];
	char	fhb_FileSysName[84];	/* the file system's name, as text */
};

#define IDNAME_FSHEADER		0x46534844	/* FSHD */

/* The file system's code, in a chain of these */
struct LoadSegBlock {
	ULONG	lsb_ID;			/* IDNAME_LOADSEG */
	ULONG	lsb_SummedLongs;
	LONG	lsb_ChkSum;
	ULONG	lsb_HostID;
	ULONG	lsb_Next;
	ULONG	lsb_LoadData[123];	/* the load file, in pieces */
};

#define IDNAME_LOADSEG		0x4C534547	/* LSEG */

/* More names from the 3.2 interface */
#define IDNAME_FILESYSHEADER	0x46534844

#endif /* DEVICES_HARDBLOCKS_H */
