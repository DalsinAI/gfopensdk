#ifndef EXEC_IO_H
#define EXEC_IO_H
/*
 * OpenNDK: I/O requests and the standard device commands.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif

/* The head of every I/O request. */
struct IORequest {
	struct Message io_Message;
	struct Device *io_Device;
	struct Unit *io_Unit;
	UWORD	io_Command;
	UBYTE	io_Flags;
	BYTE	io_Error;
};

/* The common request with a data buffer. */
struct IOStdReq {
	struct Message io_Message;
	struct Device *io_Device;
	struct Unit *io_Unit;
	UWORD	io_Command;
	UBYTE	io_Flags;
	BYTE	io_Error;
	ULONG	io_Actual;
	ULONG	io_Length;
	APTR	io_Data;
	ULONG	io_Offset;
};

/* Device vectors after the library ones */
#define DEV_BEGINIO	(-30)
#define DEV_ABORTIO	(-36)

/* io_Flags */
#define IOB_QUICK	0
#define IOF_QUICK	(1<<0)

/* Commands every device knows */
#define CMD_INVALID	0
#define CMD_RESET	1
#define CMD_READ	2
#define CMD_WRITE	3
#define CMD_UPDATE	4
#define CMD_CLEAR	5
#define CMD_STOP	6
#define CMD_START	7
#define CMD_FLUSH	8

#define CMD_NONSTD	9

#endif /* EXEC_IO_H */
