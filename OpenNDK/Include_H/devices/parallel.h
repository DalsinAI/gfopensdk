#ifndef DEVICES_PARALLEL_H
#define DEVICES_PARALLEL_H
/*
 * OpenNDK: parallel.device's request, commands, flags and errors.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_IO_H
#include <exec/io.h>
#endif

/* Characters that end a read (PARF_EOFMODE), in falling order */
struct IOPArray {
	ULONG	PTermArray0;
	ULONG	PTermArray1;
};

struct IOExtPar {
	struct IOStdReq	IOPar;
	ULONG		io_PExtFlags;	/* 0 */
	UBYTE		io_Status;	/* IOPTF_ */
	UBYTE		io_ParFlags;	/* PARF_ */
	struct IOPArray	io_PTermArray;
};

/* io_ParFlags */
#define PARB_SHARED	5	/* others may open the port */
#define PARF_SHARED	(1<<5)
#define PARB_SLOWMODE	4	/* for slow printers */
#define PARF_SLOWMODE	(1<<4)
#define PARB_FASTMODE	3	/* no busy handshake */
#define PARF_FASTMODE	(1<<3)
#define PARB_RAD_BOOGIE	3	/* the old name */
#define PARF_RAD_BOOGIE	(1<<3)
#define PARB_ACKMODE	2	/* handshake on ACK */
#define PARF_ACKMODE	(1<<2)
#define PARB_EOFMODE	1	/* reads end at a term character */
#define PARF_EOFMODE	(1<<1)

/* io_Flags */
#define IOPARB_QUEUED	6
#define IOPARF_QUEUED	(1<<6)
#define IOPARB_ABORT	5
#define IOPARF_ABORT	(1<<5)
#define IOPARB_ACTIVE	4
#define IOPARF_ACTIVE	(1<<4)

/* io_Status: the port's lines */
#define IOPTB_RWDIR	3	/* writing */
#define IOPTF_RWDIR	(1<<3)
#define IOPTB_PARSEL	2	/* printer selected */
#define IOPTF_PARSEL	(1<<2)
#define IOPTB_PAPEROUT	1
#define IOPTF_PAPEROUT	(1<<1)
#define IOPTB_PARBUSY	0
#define IOPTF_PARBUSY	(1<<0)

#define PARALLELNAME	"parallel.device"

/* Commands */
#define PDCMD_QUERY	(CMD_NONSTD)
#define PDCMD_SETPARAMS	(CMD_NONSTD+1)

/* io_Error */
#define ParErr_DevBusy		1
#define ParErr_BufTooBig	2
#define ParErr_InvParam		3
#define ParErr_LineErr		4
#define ParErr_NotOpen		5
#define ParErr_PortReset	6
#define ParErr_InitErr		7

#endif /* DEVICES_PARALLEL_H */
