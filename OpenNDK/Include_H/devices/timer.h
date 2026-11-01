#ifndef DEVICES_TIMER_H
#define DEVICES_TIMER_H
/*
 * OpenNDK: timer.device's units, commands and time structures.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_IO_H
#include <exec/io.h>
#endif

/* Units */
#define UNIT_MICROHZ	0	/* a delay, precise */
#define UNIT_VBLANK	1	/* a delay, to the frame */
#define UNIT_ECLOCK	2	/* a delay in E-clock ticks */
#define UNIT_WAITUNTIL	3	/* until a system time */
#define UNIT_WAITECLOCK	4	/* until an E-clock count */

#define TIMERNAME	"timer.device"

/* A time, and the request every timer command takes, by the names the
 * 3.2 interface uses. These are always there. */
struct TimeVal {
	ULONG	tv_secs;
	ULONG	tv_micro;
};

struct TimeRequest {
	struct IORequest	tr_node;
	struct TimeVal		tr_time;
};

/* The classic names. A unit that has its own (POSIX) struct timeval
 * defines __USE_NEW_TIMEVAL__ before including this, and then only the
 * names above are there. Otherwise struct timeval is defined here unless
 * a C library's header has already defined it (_TIMEVAL_DEFINED); ours
 * answers to the POSIX field names as well, so either may come first.
 * Code meant to build either way uses TimeVal_Type and TimeRequest_Type. */
#ifndef __USE_NEW_TIMEVAL__

#ifndef _TIMEVAL_DEFINED
#define _TIMEVAL_DEFINED
struct timeval {
	union {
		ULONG	tv_sec;
		ULONG	tv_secs;
	};
	union {
		ULONG	tv_usec;
		ULONG	tv_micro;
	};
};
#endif

struct timerequest {
	struct IORequest	tr_node;
	struct timeval		tr_time;
};

typedef struct timeval		TimeVal_Type;
typedef struct timerequest	TimeRequest_Type;

#else

typedef struct TimeVal		TimeVal_Type;
typedef struct TimeRequest	TimeRequest_Type;

#endif /* __USE_NEW_TIMEVAL__ */

/* Says TimeVal_Type and TimeRequest_Type are defined */
#define __TIME_TYPES_DEFINED__

/* The 64-bit E-clock count ReadEClock() gives */
struct EClockVal {
	ULONG	ev_hi;
	ULONG	ev_lo;
};

/* Commands */
#define TR_ADDREQUEST	CMD_NONSTD
#define TR_GETSYSTIME	(CMD_NONSTD+1)
#define TR_SETSYSTIME	(CMD_NONSTD+2)

#endif /* DEVICES_TIMER_H */
