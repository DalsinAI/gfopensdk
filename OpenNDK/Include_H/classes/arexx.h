#ifndef CLASSES_AREXX_H
#define CLASSES_AREXX_H
/*
 * OpenNDK: arexx.class, an ARexx host port with a table of commands.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef EXEC_MEMORY_H
#include <exec/memory.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif
#ifndef DOS_RDARGS_H
#include <dos/rdargs.h>
#endif
#ifndef REXX_STORAGE_H
#include <rexx/storage.h>
#endif
#ifndef REXX_RXSLIB_H
#include <rexx/rxslib.h>
#endif
#ifndef REXX_ERRORS_H
#include <rexx/errors.h>
#endif
#ifndef INTUITION_CLASSES_H
#include <intuition/classes.h>
#endif
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif

#ifndef BPTR_DEFINED
#define BPTR_DEFINED
typedef long BPTR;
typedef long BSTR;
#endif

#define AREXX_Dummy		(REACTION_Dummy + 0x30000)

#define AREXX_HostName		(AREXX_Dummy + 1)	/* STRPTR: the port's base name */
#define AREXX_DefExtension	(AREXX_Dummy + 2)	/* STRPTR: scripts' extension, "rexx" by default */
#define AREXX_Commands		(AREXX_Dummy + 3)	/* struct ARexxCmd *, ended by a NULL ac_Name */
#define AREXX_ErrorCode		(AREXX_Dummy + 4)	/* ULONG *: why OM_NEW failed, RXERR_ below */
#define AREXX_SigMask		(AREXX_Dummy + 5)	/* (get) the port's signal */
#define AREXX_NoSlot		(AREXX_Dummy + 6)	/* BOOL: no ".1" added to the name */
#define AREXX_ReplyHook		(AREXX_Dummy + 7)	/* struct Hook *: replies to our own commands */
#define AREXX_MsgPort		(AREXX_Dummy + 8)	/* (get) struct MsgPort * */

/* AREXX_ErrorCode */
#define RXERR_NO_COMMAND_LIST		1
#define RXERR_NO_PORT_NAME		2
#define RXERR_PORT_ALREADY_EXISTS	3
#define RXERR_OUT_OF_MEMORY		4

/* Methods */
#define AM_HANDLEEVENT	0x590001	/* run the commands waiting on the port */
#define AM_EXECUTE	0x590002	/* struct apExecute: send a command */
#define AM_FLUSH	0x590003	/* drop replies still owed */

struct apExecute
{
	ULONG	MethodID;		/* AM_EXECUTE */
	STRPTR	ape_CommandString;
	STRPTR	ape_PortName;		/* NULL: our own port */
	LONG	*ape_RC;
	LONG	*ape_RC2;
	STRPTR	*ape_Result;
	BPTR	ape_IO;
};

struct RexxMsg;			/* rexx/storage.h */

/* One command the host knows */
struct ARexxCmd
{
	STRPTR	ac_Name;		/* the command's name */
	UWORD	ac_ID;
	VOID	(*ac_Func)(struct ARexxCmd *cmd, struct RexxMsg *msg);	/* A0 the command, A1 the message */
	STRPTR	ac_ArgTemplate;		/* a ReadArgs() template */
	ULONG	ac_Flags;
	ULONG	*ac_ArgList;		/* the parsed arguments */
	LONG	ac_RC;			/* set by ac_Func */
	LONG	ac_RC2;
	STRPTR	ac_Result;
};

/* More names from the 3.2 interface */
#define AREXX_DefExtention	(AREXX_Dummy + 2)

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef EXEC_MEMORY_H
#include <exec/memory.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif
#ifndef DOS_RDARGS_H
#include <dos/rdargs.h>
#endif
#ifndef REXX_STORAGE_H
#include <rexx/storage.h>
#endif
#ifndef REXX_RXSLIB_H
#include <rexx/rxslib.h>
#endif
#ifndef REXX_ERRORS_H
#include <rexx/errors.h>
#endif
#ifndef INTUITION_CLASSES_H
#include <intuition/classes.h>
#endif
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif

#endif /* CLASSES_AREXX_H */
