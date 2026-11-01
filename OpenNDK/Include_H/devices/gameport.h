#ifndef DEVICES_GAMEPORT_H
#define DEVICES_GAMEPORT_H
/*
 * OpenNDK: gameport.device's commands, controller types and trigger.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_IO_H
#include <exec/io.h>
#endif

#define GPD_READEVENT	(CMD_NONSTD+0)
#define GPD_ASKCTYPE	(CMD_NONSTD+1)
#define GPD_SETCTYPE	(CMD_NONSTD+2)
#define GPD_ASKTRIGGER	(CMD_NONSTD+3)
#define GPD_SETTRIGGER	(CMD_NONSTD+4)

/* gpt_Keys */
#define GPTB_DOWNKEYS	0
#define GPTF_DOWNKEYS	(1<<0)
#define GPTB_UPKEYS	1
#define GPTF_UPKEYS	(1<<1)

/* When the port reports an event */
struct GamePortTrigger {
	UWORD	gpt_Keys;	/* button transitions to report */
	UWORD	gpt_Timeout;	/* report after this many frames anyway */
	UWORD	gpt_XDelta;	/* or after this much movement */
	UWORD	gpt_YDelta;
};

/* Controller types */
#define GPCT_ALLOCATED		-1	/* in use by someone else */
#define GPCT_NOCONTROLLER	0
#define GPCT_MOUSE		1
#define GPCT_RELJOYSTICK	2
#define GPCT_ABSJOYSTICK	3

/* Errors */
#define GPDERR_SETCTYPE		1	/* the type cannot be set */

#endif /* DEVICES_GAMEPORT_H */
