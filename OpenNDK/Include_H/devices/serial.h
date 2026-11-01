#ifndef DEVICES_SERIAL_H
#define DEVICES_SERIAL_H
/*
 * OpenNDK: serial.device's request, commands, flags and errors.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_IO_H
#include <exec/io.h>
#endif

/* Characters that end a read (SERF_EOFMODE), in falling order */
struct IOTArray {
	ULONG	TermArray0;
	ULONG	TermArray1;
};

/* XON in the top byte, XOFF in the next */
#define SER_DEFAULT_CTLCHAR	0x11130000

struct IOExtSer {
	struct IOStdReq	IOSer;
	ULONG	io_CtlChar;		/* XON, XOFF, 0, 0 */
	ULONG	io_RBufLen;		/* read buffer size */
	ULONG	io_ExtFlags;		/* SEXTF_ */
	ULONG	io_Baud;
	ULONG	io_BrkTime;		/* break length, microseconds */
	struct IOTArray io_TermArray;
	UBYTE	io_ReadLen;		/* bits per character read */
	UBYTE	io_WriteLen;		/* bits per character written */
	UBYTE	io_StopBits;
	UBYTE	io_SerFlags;		/* SERF_ */
	UWORD	io_Status;		/* IO_STATF_ */
};

/* Commands */
#define SDCMD_QUERY	CMD_NONSTD
#define SDCMD_BREAK	(CMD_NONSTD+1)
#define SDCMD_SETPARAMS	(CMD_NONSTD+2)

/* io_SerFlags */
#define SERB_XDISABLED	7	/* no XON/XOFF */
#define SERF_XDISABLED	(1<<7)
#define SERB_EOFMODE	6	/* reads end at a term character */
#define SERF_EOFMODE	(1<<6)
#define SERB_SHARED	5	/* others may open the port */
#define SERF_SHARED	(1<<5)
#define SERB_RAD_BOOGIE	4	/* fast, plain mode */
#define SERF_RAD_BOOGIE	(1<<4)
#define SERB_QUEUEDBRK	3	/* queue breaks with writes */
#define SERF_QUEUEDBRK	(1<<3)
#define SERB_7WIRE	2	/* RTS/CTS handshake */
#define SERF_7WIRE	(1<<2)
#define SERB_PARTY_ODD	1	/* odd parity */
#define SERF_PARTY_ODD	(1<<1)
#define SERB_PARTY_ON	0	/* parity on */
#define SERF_PARTY_ON	(1<<0)

/* io_Status */
#define IO_STATB_XOFFREAD	12
#define IO_STATF_XOFFREAD	(1<<12)
#define IO_STATB_XOFFWRITE	11
#define IO_STATF_XOFFWRITE	(1<<11)
#define IO_STATB_READBREAK	10
#define IO_STATF_READBREAK	(1<<10)
#define IO_STATB_WROTEBREAK	9
#define IO_STATF_WROTEBREAK	(1<<9)
#define IO_STATB_OVERRUN	8
#define IO_STATF_OVERRUN	(1<<8)

/* io_ExtFlags */
#define SEXTB_MSPON	1	/* mark/space parity */
#define SEXTF_MSPON	(1<<1)
#define SEXTB_MARK	0	/* mark, else space */
#define SEXTF_MARK	(1<<0)

/* io_Error */
#define SerErr_DevBusy		1
#define SerErr_BaudMismatch	2
#define SerErr_BufErr		4
#define SerErr_InvParam		5
#define SerErr_LineErr		6
#define SerErr_ParityErr	9
#define SerErr_TimerErr		11
#define SerErr_BufOverflow	12
#define SerErr_NoDSR		13
#define SerErr_DetectedBreak	15

#define SERIALNAME	"serial.device"

/* io_Flags bits and masks the device keeps for itself */
#define IOSERB_ACTIVE		4
#define IOSERF_ACTIVE		(1<<4)
#define IOSERB_ABORT		5
#define IOSERF_ABORT		(1<<5)
#define IOSERB_QUEUED		6
#define IOSERF_QUEUED		(1<<6)
#define IOSERB_BUFRREAD		7
#define IOSERF_BUFRREAD		(1<<7)

/* io_Status bits */
#define IOSTB_OVERRUN		0
#define IOSTF_OVERRUN		(1<<0)
#define IOSTB_WROTEBREAK	1
#define IOSTF_WROTEBREAK	(1<<1)
#define IOSTB_READBREAK		2
#define IOSTF_READBREAK		(1<<2)
#define IOSTB_XOFFWRITE		3
#define IOSTF_XOFFWRITE		(1<<3)
#define IOSTB_XOFFREAD		4
#define IOSTF_XOFFREAD		(1<<4)

/* errors the device never returns any more, kept for old sources */
#define SerErr_InvBaud		3
#define SerErr_NotOpen		7
#define SerErr_PortReset	8
#define SerErr_InitErr		10
#define SerErr_NoCTS		14

#endif /* DEVICES_SERIAL_H */
