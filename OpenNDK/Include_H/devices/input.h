#ifndef DEVICES_INPUT_H
#define DEVICES_INPUT_H
/*
 * OpenNDK: input.device's commands.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_IO_H
#include <exec/io.h>
#endif

#define IND_ADDHANDLER	(CMD_NONSTD+0)	/* io_Data: struct Interrupt */
#define IND_REMHANDLER	(CMD_NONSTD+1)
#define IND_WRITEEVENT	(CMD_NONSTD+2)	/* io_Data: struct InputEvent */
#define IND_SETTHRESH	(CMD_NONSTD+3)	/* key repeat delay */
#define IND_SETPERIOD	(CMD_NONSTD+4)	/* key repeat rate */
#define IND_SETMPORT	(CMD_NONSTD+5)	/* mouse port */
#define IND_SETMTYPE	(CMD_NONSTD+6)	/* mouse port controller type */
#define IND_SETMTRIG	(CMD_NONSTD+7)	/* mouse port trigger */

/* More names from the 3.2 interface */
#define IND_ADDEVENT		24

#endif /* DEVICES_INPUT_H */
