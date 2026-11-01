#ifndef EXEC_DEVICES_H
#define EXEC_DEVICES_H
/*
 * OpenNDK: device and unit bases.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif

/* A device is a library with BeginIO and AbortIO. */
struct Device {
	struct Library dd_Library;
};

/* The common head of a device unit. */
struct Unit {
	struct MsgPort unit_MsgPort;	/* queue of pending requests */
	UBYTE	unit_flags;
	UBYTE	unit_pad;
	UWORD	unit_OpenCnt;
};

/* unit_flags */
#define UNITF_ACTIVE	(1<<0)
#define UNITF_INTASK	(1<<1)

#endif /* EXEC_DEVICES_H */
