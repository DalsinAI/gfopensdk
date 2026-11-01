#ifndef WORKBENCH_STARTUP_H
#define WORKBENCH_STARTUP_H
/*
 * OpenNDK: the message Workbench starts a program with, and its
 * arguments.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

/* Sent to a program's process port when Workbench starts it */
struct WBStartup
{
    struct Message sm_Message;
    struct MsgPort *sm_Process;		/* the process's port */
    BPTR sm_Segment;			/* its code */
    LONG sm_NumArgs;			/* entries in sm_ArgList */
    STRPTR	sm_ToolWindow;		/* a window description, or NULL */
    struct WBArg *sm_ArgList;		/* the tool first, then the projects */
};

/* One argument: a name in a directory */
struct WBArg
{
    BPTR wa_Lock;			/* the directory; NULL for a volume */
    STRPTR wa_Name;			/* the name within it */
};

#endif /* WORKBENCH_STARTUP_H */
