#ifndef DEVICES_TRACKFILE_H
#define DEVICES_TRACKFILE_H
/*
 * OpenNDK: trackfile.device, which presents disk image files as floppy drives.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_IO_H
#include <exec/io.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif
#ifndef DEVICES_TRACKDISK_H
#include <devices/trackdisk.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

#define TRACKFILENAME	"trackfile.device"

/* A unit's checksum, 64 bits */
struct TrackFileChecksum
{
	ULONG	tfc_high;
	ULONG	tfc_low;
};

/* What the device says about one unit */
struct TrackFileUnitData
{
	struct TrackFileUnitData *tfud_Next;
	ULONG	tfud_Size;		/* of this structure */
	ULONG	tfud_UnitNumber;
	ULONG	tfud_DriveType;		/* DRIVE3_5 and so on */
	STRPTR	tfud_DeviceName;
	STRPTR	tfud_FileName;		/* the image file, NULL if none */
	BOOL	tfud_IsActive;
	BOOL	tfud_IsWritable;
	BOOL	tfud_MediumIsPresent;
	BOOL	tfud_IsBusy;
	BOOL	tfud_ChecksumsEnabled;
	struct TrackFileChecksum tfud_Checksum;
	BOOL	tfud_VolumeValid;	/* the next two are set */
	TEXT	tfud_VolumeName[32];
	struct DateStamp tfud_VolumeDate;
	ULONG	tfud_FileSysSignature;	/* the boot block's DOS type */
	ULONG	tfud_BootBlockChecksum;
	BOOL	tfud_CacheEnabled;
	ULONG	tfud_CacheAccesses;
	ULONG	tfud_CacheMisses;
};

/* More names from the 3.2 interface */
#define TF_Dummy		0xA0200400UL
#define TFEFS_Unsupported	(-1)
#define TFERROR_Aborted		(-202049)
#define TFERROR_AlreadyInUse	(-202044)
#define TFERROR_Denied		(-202057)
#define TFERROR_DuplicateDisk	(-202055)
#define TFERROR_DuplicateVolume	(-202056)
#define TFERROR_InvalidDriveType	(-202050)
#define TFERROR_InvalidFile	(-202046)
#define TFERROR_InvalidFileSize	(-202047)
#define TFERROR_NoFileGiven	(-202048)
#define TFERROR_NoMediumPresent	(-202052)
#define TFERROR_NotSupported	(-202058)
#define TFERROR_OutOfMemory	(-202042)
#define TFERROR_ProcessFailed	(-202051)
#define TFERROR_ReadOnlyFile	(-202054)
#define TFERROR_ReadOnlyVolume	(-202053)
#define TFERROR_UnitBusy	(-202041)
#define TFERROR_UnitNotActive	(-202045)
#define TFERROR_UnitNotFound	(-202043)
#define TFGUD_AllUnits		(-1)
#define TFSU_NextAvailableUnit	(-1)
#define TFUNIT_CONTROL		(-1)
#define TF_DriveType		(TF_Dummy + 4)
#define TF_EnableChecksums	(TF_Dummy + 6)
#define TF_EnableUnitCache	(TF_Dummy + 9)
#define TF_ImageFileHandle	(TF_Dummy + 2)
#define TF_ImageFileName	(TF_Dummy + 1)
#define TF_MINIMUM_CACHE_SIZE	0xB3B0
#define TF_MaxCacheMemory	(TF_Dummy + 8)
#define TF_PrefillUnitCache	(TF_Dummy + 10)
#define TF_TagItemFailed	(TF_Dummy + 7)
#define TF_Timeout		(TF_Dummy + 5)
#define TF_WriteProtected	(TF_Dummy + 3)

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef DEVICES_TRACKDISK_H
#include <devices/trackdisk.h>
#endif

#define TRACKFILENAME		"trackfile.device"

#endif /* DEVICES_TRACKFILE_H */
