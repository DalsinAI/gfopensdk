#ifndef DEVICES_KEYBOARD_H
#define DEVICES_KEYBOARD_H
/*
 * OpenNDK: keyboard.device's commands.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_IO_H
#include <exec/io.h>
#endif

#define KBD_READEVENT		(CMD_NONSTD+0)
#define KBD_READMATRIX		(CMD_NONSTD+1)	/* the key state bitmap */
#define KBD_ADDRESETHANDLER	(CMD_NONSTD+2)	/* run at CTRL-Amiga-Amiga */
#define KBD_REMRESETHANDLER	(CMD_NONSTD+3)
#define KBD_RESETHANDLERDONE	(CMD_NONSTD+4)

#endif /* DEVICES_KEYBOARD_H */
