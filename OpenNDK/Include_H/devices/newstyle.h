#ifndef DEVICES_NEWSTYLE_H
#define DEVICES_NEWSTYLE_H
/*
 * OpenNDK: the New Style Device query: how a device says what it is
 * and which commands it takes.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* Commands 0x4000-0x7FFF are the standard's; 0xC000 and up are each
 * device class's own. */
#define NSCMD_DEVICEQUERY	0x4000

/* What NSCMD_DEVICEQUERY fills; set nsdqr_SizeAvailable to 0 before asking */
struct NSDeviceQueryResult {
	ULONG	nsdqr_DevQueryFormat;		/* 0 */
	ULONG	nsdqr_SizeAvailable;		/* bytes the device filled */
	UWORD	nsdqr_DeviceType;		/* NSDEVTYPE_ */
	UWORD	nsdqr_DeviceSubType;
	UWORD	*nsdqr_SupportedCommands;	/* 0-terminated */
};

#define NSDEVTYPE_UNKNOWN	0
#define NSDEVTYPE_GAMEPORT	1
#define NSDEVTYPE_TIMER		2
#define NSDEVTYPE_KEYBOARD	3
#define NSDEVTYPE_INPUT		4
#define NSDEVTYPE_TRACKDISK	5
#define NSDEVTYPE_CONSOLE	6
#define NSDEVTYPE_SANA2		7
#define NSDEVTYPE_AUDIO		8
#define NSDEVTYPE_CLIPBOARD	9
#define NSDEVTYPE_PRINTER	10
#define NSDEVTYPE_SERIAL	11
#define NSDEVTYPE_PARALLEL	12

/* More names from the 3.2 interface */
#define NSDEVTYPE_AUDIOARD	8

/* the high 32 bits of a 64-bit offset ride in io_Actual */
#define io_HighOffset		io_Actual

#endif /* DEVICES_NEWSTYLE_H */
