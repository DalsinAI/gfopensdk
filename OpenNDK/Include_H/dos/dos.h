#ifndef DOS_DOS_H
#define DOS_DOS_H
/*
 * OpenNDK: dos.library's basic types, file modes, error codes and the
 * structures Examine() and Info() fill.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#define DOSNAME		"dos.library"

/* dos's own truth values: true is all bits set */
#define DOSTRUE		(-1L)
#define DOSFALSE	(0L)

/* Open() modes */
#define MODE_OLDFILE	1005	/* existing file, shared */
#define MODE_NEWFILE	1006	/* new or emptied file, exclusive */
#define MODE_READWRITE	1004	/* existing or new file, shared */

/* Seek() origins */
#define OFFSET_BEGINNING	(-1)
#define OFFSET_CURRENT		0
#define OFFSET_END		1
#define OFFSET_BEGINING		OFFSET_BEGINNING	/* the old spelling */

#define BITSPERBYTE	8
#define BYTESPERLONG	4
#define BITSPERLONG	32
#define MAXINT		0x7FFFFFFF
#define MININT		0x80000000

/* Lock() access */
#define SHARED_LOCK	(-2)
#define ACCESS_READ	(-2)
#define EXCLUSIVE_LOCK	(-1)
#define ACCESS_WRITE	(-1)

/* A point in time: days since 1 January 1978, minutes since midnight,
 * and ticks (1/50 s) into the minute. */
struct DateStamp {
	LONG	ds_Days;
	LONG	ds_Minute;
	LONG	ds_Tick;
};
#define TICKS_PER_SECOND	50

/* What Examine() and ExNext() report about one object. Allocate it
 * with AllocDosObject() so it is longword aligned. */
struct FileInfoBlock {
	LONG	fib_DiskKey;
	LONG	fib_DirEntryType;	/* < 0 file, > 0 directory */
	TEXT	fib_FileName[108];
	LONG	fib_Protection;
	LONG	fib_EntryType;
	LONG	fib_Size;
	LONG	fib_NumBlocks;
	struct DateStamp fib_Date;
	TEXT	fib_Comment[80];
	UWORD	fib_OwnerUID;
	UWORD	fib_OwnerGID;
	char	fib_Reserved[32];
};

/* fib_Protection bits. RWED (bits 0-3) are set to deny; the others are
 * set to allow. */
#define FIBB_OTR_READ		15
#define FIBB_OTR_WRITE		14
#define FIBB_OTR_EXECUTE	13
#define FIBB_OTR_DELETE		12
#define FIBB_GRP_READ		11
#define FIBB_GRP_WRITE		10
#define FIBB_GRP_EXECUTE	9
#define FIBB_GRP_DELETE		8
#define FIBB_SCRIPT		6
#define FIBB_PURE		5
#define FIBB_ARCHIVE		4
#define FIBB_READ		3
#define FIBB_WRITE		2
#define FIBB_EXECUTE		1
#define FIBB_DELETE		0

#define FIBF_OTR_READ		(1<<FIBB_OTR_READ)
#define FIBF_OTR_WRITE		(1<<FIBB_OTR_WRITE)
#define FIBF_OTR_EXECUTE	(1<<FIBB_OTR_EXECUTE)
#define FIBF_OTR_DELETE		(1<<FIBB_OTR_DELETE)
#define FIBF_GRP_READ		(1<<FIBB_GRP_READ)
#define FIBF_GRP_WRITE		(1<<FIBB_GRP_WRITE)
#define FIBF_GRP_EXECUTE	(1<<FIBB_GRP_EXECUTE)
#define FIBF_GRP_DELETE		(1<<FIBB_GRP_DELETE)
#define FIBF_SCRIPT		(1<<FIBB_SCRIPT)
#define FIBF_PURE		(1<<FIBB_PURE)
#define FIBF_ARCHIVE		(1<<FIBB_ARCHIVE)
#define FIBF_READ		(1<<FIBB_READ)
#define FIBF_WRITE		(1<<FIBB_WRITE)
#define FIBF_EXECUTE		(1<<FIBB_EXECUTE)
#define FIBF_DELETE		(1<<FIBB_DELETE)

/* BCPL pointers: a longword address shifted right by two */
#ifndef BPTR_DEFINED
#define BPTR_DEFINED
typedef long	BPTR;
typedef long	BSTR;
#endif

#ifdef OBSOLETE_LIBRARIES_DOS_H
#define BADDR(bptr)	(((ULONG)(bptr)) << 2)
#else
#define BADDR(bptr)	((APTR)(((ULONG)(bptr)) << 2))
#endif
#define MKBADDR(ptr)	((BPTR)(((ULONG)(ptr)) >> 2))

/* What Info() reports about a volume */
struct InfoData {
	LONG	id_NumSoftErrors;
	LONG	id_UnitNumber;
	LONG	id_DiskState;		/* ID_WRITE_PROTECTED and friends */
	LONG	id_NumBlocks;
	LONG	id_NumBlocksUsed;
	LONG	id_BytesPerBlock;
	LONG	id_DiskType;		/* ID_DOS_DISK and friends */
	BPTR	id_VolumeNode;
	LONG	id_InUse;		/* non-zero while locks are out */
};

/* id_DiskState */
#define ID_WRITE_PROTECTED	80
#define ID_VALIDATING		81
#define ID_VALIDATED		82

/* id_DiskType: four characters packed into a longword */
#define ID_NO_DISK_PRESENT	(-1)
#define ID_UNREADABLE_DISK	(0x42414400L)	/* BAD\0 */
#define ID_DOS_DISK		(0x444F5300L)	/* DOS\0 */
#define ID_FFS_DISK		(0x444F5301L)	/* DOS\1 */
#define ID_INTER_DOS_DISK	(0x444F5302L)	/* DOS\2 */
#define ID_INTER_FFS_DISK	(0x444F5303L)	/* DOS\3 */
#define ID_FASTDIR_DOS_DISK	(0x444F5304L)	/* DOS\4 */
#define ID_FASTDIR_FFS_DISK	(0x444F5305L)	/* DOS\5 */
#define ID_LONGNAME_DOS_DISK	(0x444F5306L)	/* DOS\6 */
#define ID_LONGNAME_FFS_DISK	(0x444F5307L)	/* DOS\7 */
#define ID_NOT_REALLY_DOS	(0x4E444F53L)	/* NDOS */
#define ID_KICKSTART_DISK	(0x4B49434BL)	/* KICK */
#define ID_MSDOS_DISK		(0x4d534400L)	/* MSD\0 */

/* id_DiskType of console handlers */
#define ID_CON			(0x434F4E00L)	/* CON\0 */
#define ID_RAWCON		(0x52415700L)	/* RAW\0 */

/* IoErr() codes */
#define ERROR_NO_FREE_STORE		103
#define ERROR_TASK_TABLE_FULL		105
#define ERROR_BAD_TEMPLATE		114
#define ERROR_BAD_NUMBER		115
#define ERROR_REQUIRED_ARG_MISSING	116
#define ERROR_KEY_NEEDS_ARG		117
#define ERROR_TOO_MANY_ARGS		118
#define ERROR_UNMATCHED_QUOTES		119
#define ERROR_LINE_TOO_LONG		120
#define ERROR_FILE_NOT_OBJECT		121
#define ERROR_INVALID_RESIDENT_LIBRARY	122
#define ERROR_NO_DEFAULT_DIR		201
#define ERROR_OBJECT_IN_USE		202
#define ERROR_OBJECT_EXISTS		203
#define ERROR_DIR_NOT_FOUND		204
#define ERROR_OBJECT_NOT_FOUND		205
#define ERROR_BAD_STREAM_NAME		206
#define ERROR_OBJECT_TOO_LARGE		207
#define ERROR_ACTION_NOT_KNOWN		209
#define ERROR_INVALID_COMPONENT_NAME	210
#define ERROR_INVALID_LOCK		211
#define ERROR_OBJECT_WRONG_TYPE		212
#define ERROR_DISK_NOT_VALIDATED	213
#define ERROR_DISK_WRITE_PROTECTED	214
#define ERROR_RENAME_ACROSS_DEVICES	215
#define ERROR_DIRECTORY_NOT_EMPTY	216
#define ERROR_TOO_MANY_LEVELS		217
#define ERROR_DEVICE_NOT_MOUNTED	218
#define ERROR_SEEK_ERROR		219
#define ERROR_COMMENT_TOO_BIG		220
#define ERROR_DISK_FULL			221
#define ERROR_DELETE_PROTECTED		222
#define ERROR_WRITE_PROTECTED		223
#define ERROR_READ_PROTECTED		224
#define ERROR_NOT_A_DOS_DISK		225
#define ERROR_NO_DISK			226
#define ERROR_NO_MORE_ENTRIES		232
#define ERROR_IS_SOFT_LINK		233
#define ERROR_OBJECT_LINKED		234
#define ERROR_BAD_HUNK			235
#define ERROR_NOT_IMPLEMENTED		236
#define ERROR_RECORD_NOT_LOCKED		240
#define ERROR_LOCK_COLLISION		241
#define ERROR_LOCK_TIMEOUT		242
#define ERROR_UNLOCK_ERROR		243
#define ERROR_BUFFER_OVERFLOW		303
#define ERROR_BREAK			304
#define ERROR_NOT_EXECUTABLE		305

/* Command return codes */
#define RETURN_OK	0
#define RETURN_WARN	5
#define RETURN_ERROR	10
#define RETURN_FAIL	20

/* The break signals a console sends for CTRL-C to CTRL-F */
#define SIGBREAKB_CTRL_C	12
#define SIGBREAKB_CTRL_D	13
#define SIGBREAKB_CTRL_E	14
#define SIGBREAKB_CTRL_F	15

#define SIGBREAKF_CTRL_C	(1L<<SIGBREAKB_CTRL_C)
#define SIGBREAKF_CTRL_D	(1L<<SIGBREAKB_CTRL_D)
#define SIGBREAKF_CTRL_E	(1L<<SIGBREAKB_CTRL_E)
#define SIGBREAKF_CTRL_F	(1L<<SIGBREAKB_CTRL_F)

/* SameLock() answers */
#define LOCK_DIFFERENT		(-1)
#define LOCK_SAME		0
#define LOCK_SAME_VOLUME	1
#define LOCK_SAME_HANDLER	LOCK_SAME_VOLUME	/* the old name */

/* ChangeMode() object types */
#define CHANGE_LOCK	0
#define CHANGE_FH	1

/* MakeLink() kinds */
#define LINK_HARD	0
#define LINK_SOFT	1

/* ReadItem() answers */
#define ITEM_EQUAL	(-2)
#define ITEM_ERROR	(-1)
#define ITEM_NOTHING	0
#define ITEM_UNQUOTED	1
#define ITEM_QUOTED	2

/* AllocDosObject() types */
#define DOS_FILEHANDLE		0
#define DOS_EXALLCONTROL	1
#define DOS_FIB			2
#define DOS_STDPKT		3
#define DOS_CLI			4
#define DOS_RDARGS		5

/* More names from the 3.2 interface */
#define FAULT_MAX		82
#define FIBB_HOLD		7
#define FIBF_HOLD		128
#define ID_COMPLONG_FFS_DISK	0x444F5308
#define ID_LONG_DOS_DISK	0x444F5306
#define ID_LONG_FFS_DISK	0x444F5307

#endif /* DOS_DOS_H */
