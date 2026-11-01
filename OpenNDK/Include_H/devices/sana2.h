#ifndef DEVICES_SANA2_H
#define DEVICES_SANA2_H
/*
 * OpenNDK: the SANA-II network device interface (revision 4): the request
 * a protocol stack sends a network device, its commands, errors, events
 * and statistics, and the tags of the buffer management hooks it hands
 * over at OpenDevice.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef EXEC_IO_H
#include <exec/io.h>
#endif
#ifndef EXEC_ERRORS_H
#include <exec/errors.h>
#endif
#ifndef DEVICES_TIMER_H
#include <devices/timer.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* The longest hardware address a unit can have */
#define SANA2_MAX_ADDR_BITS	128
#define SANA2_MAX_ADDR_BYTES	((SANA2_MAX_ADDR_BITS + 7) / 8)

/* Every SANA-II command takes this request */
struct IOSana2Req {
	struct IORequest ios2_Req;
	ULONG	ios2_WireError;		/* S2WERR_: what went wrong on the wire */
	ULONG	ios2_PacketType;	/* the packet's type (Ethernet: its type field) */
	UBYTE	ios2_SrcAddr[SANA2_MAX_ADDR_BYTES];
	UBYTE	ios2_DstAddr[SANA2_MAX_ADDR_BYTES];
	ULONG	ios2_DataLength;	/* bytes in the packet (or, for S2_ONEVENT, the events) */
	APTR	ios2_Data;		/* the packet, as the stack's buffer management sees it */
	APTR	ios2_StatData;		/* where statistics and queries are written */
	APTR	ios2_BufferManagement;	/* what OpenDevice gave back: the stack's copy hooks */
};

/* ios2_Req.io_Flags */
#define SANA2IOB_RAW	7	/* the whole frame, link headers and all */
#define SANA2IOB_BCAST	6	/* it was, or is to be, broadcast */
#define SANA2IOB_MCAST	5	/* it was, or is to be, multicast */
#define SANA2IOB_QUICK	IOB_QUICK

#define SANA2IOF_RAW	(1 << SANA2IOB_RAW)
#define SANA2IOF_BCAST	(1 << SANA2IOB_BCAST)
#define SANA2IOF_MCAST	(1 << SANA2IOB_MCAST)
#define SANA2IOF_QUICK	IOF_QUICK

/* OpenDevice's flags */
#define SANA2OPB_MINE	0	/* this opener alone */
#define SANA2OPF_MINE	(1 << SANA2OPB_MINE)
#define SANA2OPB_PROM	1	/* every frame on the wire */
#define SANA2OPF_PROM	(1 << SANA2OPB_PROM)

/* The buffer management tags (OpenDevice's ios2_BufferManagement) */
#define S2_Dummy		(TAG_USER + 0xB0000)
#define S2_CopyToBuff		(S2_Dummy + 1)
#define S2_CopyFromBuff		(S2_Dummy + 2)
#define S2_PacketFilter		(S2_Dummy + 3)
#define S2_CopyToBuff16		(S2_Dummy + 4)
#define S2_CopyFromBuff16	(S2_Dummy + 5)
#define S2_CopyToBuff32		(S2_Dummy + 6)
#define S2_CopyFromBuff32	(S2_Dummy + 7)
#define S2_DMACopyToBuff32	(S2_Dummy + 8)
#define S2_DMACopyFromBuff32	(S2_Dummy + 9)
#define S2_DMACopyToBuff64	(S2_Dummy + 10)
#define S2_DMACopyFromBuff64	(S2_Dummy + 11)
#define S2_Log			(S2_Dummy + 12)

/* What S2_DEVICEQUERY writes */
struct Sana2DeviceQuery {
	ULONG	SizeAvailable;		/* the stack's: bytes it has room for */
	ULONG	SizeSupplied;		/* the device's: bytes it wrote */
	ULONG	DevQueryFormat;		/* 0 */
	ULONG	DeviceLevel;		/* 0 */
	UWORD	AddrFieldSize;		/* address size, in bits */
	ULONG	MTU;			/* the largest packet, in bytes */
	ULONG	BPS;			/* the wire's speed, bits a second */
	ULONG	HardwareType;		/* S2WireType_ */
	ULONG	RawMTU;			/* the largest raw frame, in bytes (revision 4) */
};

/* HardwareType: the assigned numbers */
#define S2WireType_Ethernet	1
#define S2WireType_IEEE802	6
#define S2WireType_Arcnet	7
#define S2WireType_LocalTalk	11
#define S2WireType_DyLAN	12
#define S2WireType_AmokNet	200
#define S2WireType_Liana	202
#define S2WireType_PPP		253
#define S2WireType_SLIP		254
#define S2WireType_CSLIP	255
#define S2WireType_PLIP		420

/* What S2_GETTYPESTATS writes: one packet type's counts */
struct Sana2PacketTypeStats {
	ULONG	PacketsSent;
	ULONG	PacketsReceived;
	ULONG	BytesSent;
	ULONG	BytesReceived;
	ULONG	PacketsDropped;
};

/* What S2_GETSPECIALSTATS writes: a header, then its records */
struct Sana2SpecialStatRecord {
	ULONG	Type;			/* S2SS_ */
	LONG	Count;
	STRPTR	String;			/* what it counts, for people */
};

struct Sana2SpecialStatHeader {
	ULONG	RecordCountMax;		/* the stack's: records it has room for */
	ULONG	RecordCountSupplied;	/* the device's: records it wrote */
	/* struct Sana2SpecialStatRecord [RecordCountMax] follow */
};

/* What S2_GETGLOBALSTATS writes */
struct Sana2DeviceStats {
	ULONG	PacketsReceived;
	ULONG	PacketsSent;
	ULONG	BadData;
	ULONG	Overruns;
	ULONG	Unused;
	ULONG	UnknownTypesReceived;
	ULONG	Reconfigurations;
	TimeVal_Type LastStart;		/* when the unit last went online */
};

/* Special statistics: the wire type in the upper word */
#define S2SS_ETHERNET_BADMULTICAST	((((S2WireType_Ethernet) & 0xFFFF) << 16) | 0x0000)
#define S2SS_ETHERNET_RETRIES		((((S2WireType_Ethernet) & 0xFFFF) << 16) | 0x0001)
#define S2SS_ETHERNET_FIFO_UNDERRUNS	((((S2WireType_Ethernet) & 0xFFFF) << 16) | 0x0002)

/* Commands, after exec's standard ones */
#define S2_START			(CMD_NONSTD)
#define S2_DEVICEQUERY			(S2_START + 0)
#define S2_GETSTATIONADDRESS		(S2_START + 1)
#define S2_CONFIGINTERFACE		(S2_START + 2)
#define S2_ADDMULTICASTADDRESS		(S2_START + 5)
#define S2_DELMULTICASTADDRESS		(S2_START + 6)
#define S2_MULTICAST			(S2_START + 7)
#define S2_BROADCAST			(S2_START + 8)
#define S2_TRACKTYPE			(S2_START + 9)
#define S2_UNTRACKTYPE			(S2_START + 10)
#define S2_GETTYPESTATS			(S2_START + 11)
#define S2_GETSPECIALSTATS		(S2_START + 12)
#define S2_GETGLOBALSTATS		(S2_START + 13)
#define S2_ONEVENT			(S2_START + 14)
#define S2_READORPHAN			(S2_START + 15)
#define S2_ONLINE			(S2_START + 16)
#define S2_OFFLINE			(S2_START + 17)
#define S2_END				(S2_START + 18)

/* Revision 4's commands */
#define S2_ADDMULTICASTADDRESSES	0xC000
#define S2_DELMULTICASTADDRESSES	(S2_ADDMULTICASTADDRESSES + 1)
#define S2_GETPEERADDRESS		(S2_ADDMULTICASTADDRESSES + 2)
#define S2_GETDNSADDRESS		(S2_ADDMULTICASTADDRESSES + 3)
#define S2_GETEXTENDEDGLOBALSTATS	(S2_ADDMULTICASTADDRESSES + 4)
#define S2_CONNECT			(S2_ADDMULTICASTADDRESSES + 5)
#define S2_DISCONNECT			(S2_ADDMULTICASTADDRESSES + 6)
#define S2_SAMPLE_THROUGHPUT		(S2_ADDMULTICASTADDRESSES + 7)

/* io_Error */
#define S2ERR_NO_ERROR		0
#define S2ERR_NO_RESOURCES	1	/* out of memory or another resource */
#define S2ERR_BAD_ARGUMENT	3
#define S2ERR_BAD_STATE		4	/* not in a state to do it (offline, not configured) */
#define S2ERR_BAD_ADDRESS	5
#define S2ERR_MTU_EXCEEDED	6
#define S2ERR_NOT_SUPPORTED	8
#define S2ERR_SOFTWARE		9
#define S2ERR_OUTOFSERVICE	10	/* the unit is offline */
#define S2ERR_TX_FAILURE	11

/* ios2_WireError */
#define S2WERR_GENERIC_ERROR		0
#define S2WERR_NOT_CONFIGURED		1
#define S2WERR_UNIT_ONLINE		2
#define S2WERR_UNIT_OFFLINE		3
#define S2WERR_ALREADY_TRACKED		4
#define S2WERR_NOT_TRACKED		5
#define S2WERR_BUFF_ERROR		6
#define S2WERR_SRC_ADDRESS		7
#define S2WERR_DST_ADDRESS		8
#define S2WERR_BAD_BROADCAST		9
#define S2WERR_BAD_MULTICAST		10
#define S2WERR_MULTICAST_FULL		11
#define S2WERR_BAD_EVENT		12
#define S2WERR_BAD_STATDATA		13
#define S2WERR_IS_CONFIGURED		15
#define S2WERR_NULL_POINTER		16
#define S2WERR_TOO_MANY_RETIRES		17
#define S2WERR_RCVREL_HDW_ERR		18
#define S2WERR_UNIT_DISCONNECTED	19
#define S2WERR_UNIT_CONNECTED		20
#define S2WERR_INVALID_OPTION		21
#define S2WERR_MISSING_OPTION		22
#define S2WERR_AUTHENTICATION_FAILED	23

/* S2_ONEVENT's events, a mask in ios2_WireError */
#define S2EVENT_ERROR		(1L << 0)
#define S2EVENT_TX		(1L << 1)
#define S2EVENT_RX		(1L << 2)
#define S2EVENT_ONLINE		(1L << 3)
#define S2EVENT_OFFLINE		(1L << 4)
#define S2EVENT_BUFF		(1L << 5)
#define S2EVENT_HARDWARE	(1L << 6)
#define S2EVENT_SOFTWARE	(1L << 7)
#define S2EVENT_CONFIGCHANGED	(1L << 8)
#define S2EVENT_CONNECT		(1L << 9)
#define S2EVENT_DISCONNECT	(1L << 10)

#endif /* DEVICES_SANA2_H */
