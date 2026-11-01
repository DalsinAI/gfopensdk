#ifndef DOS_RECORD_H
#define DOS_RECORD_H
/*
 * OpenNDK: record locking (LockRecord(), LockRecords()).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

/* Lock modes */
#define REC_EXCLUSIVE		0
#define REC_EXCLUSIVE_IMMED	1
#define REC_SHARED		2
#define REC_SHARED_IMMED	3

/* One entry of the array LockRecords() takes; a NULL rec_FH ends it */
struct RecordLock {
	BPTR	rec_FH;
	ULONG	rec_Offset;
	ULONG	rec_Length;
	ULONG	rec_Mode;
};

#endif /* DOS_RECORD_H */
