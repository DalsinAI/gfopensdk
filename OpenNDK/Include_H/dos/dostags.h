#ifndef DOS_DOSTAGS_H
#define DOS_DOSTAGS_H
/*
 * OpenNDK: tags for SystemTagList(), CreateNewProc() and
 * AllocDosObject().
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* SystemTagList() */
#define SYS_Dummy	(TAG_USER + 32)
#define SYS_Input	(SYS_Dummy + 1)		/* input stream; 0 for NIL: */
#define SYS_Output	(SYS_Dummy + 2)		/* output stream; 0 for NIL: */
#define SYS_Asynch	(SYS_Dummy + 3)		/* run without waiting */
#define SYS_UserShell	(SYS_Dummy + 4)		/* the user's shell */
#define SYS_CustomShell	(SYS_Dummy + 5)		/* a named shell */

/* CreateNewProc() */
#define NP_Dummy	(TAG_USER + 1000)
#define NP_Seglist	(NP_Dummy + 1)		/* the code as a seglist */
#define NP_FreeSeglist	(NP_Dummy + 2)		/* free it at exit */
#define NP_Entry	(NP_Dummy + 3)		/* or the code as a function */
#define NP_Input	(NP_Dummy + 4)
#define NP_Output	(NP_Dummy + 5)
#define NP_CloseInput	(NP_Dummy + 6)
#define NP_CloseOutput	(NP_Dummy + 7)
#define NP_Error	(NP_Dummy + 8)
#define NP_CloseError	(NP_Dummy + 9)
#define NP_CurrentDir	(NP_Dummy + 10)
#define NP_StackSize	(NP_Dummy + 11)
#define NP_Name		(NP_Dummy + 12)
#define NP_Priority	(NP_Dummy + 13)
#define NP_ConsoleTask	(NP_Dummy + 14)
#define NP_WindowPtr	(NP_Dummy + 15)
#define NP_HomeDir	(NP_Dummy + 16)
#define NP_CopyVars	(NP_Dummy + 17)
#define NP_Cli		(NP_Dummy + 18)		/* give it a CLI */
#define NP_Path		(NP_Dummy + 19)		/* the CLI's path */
#define NP_CommandName	(NP_Dummy + 20)
#define NP_Arguments	(NP_Dummy + 21)
#define NP_NotifyOnDeath (NP_Dummy + 22)	/* reserved */
#define NP_Synchronous	(NP_Dummy + 23)		/* reserved */
#define NP_ExitCode	(NP_Dummy + 24)		/* called at exit */
#define NP_ExitData	(NP_Dummy + 25)

/* AllocDosObject() */
#define ADO_Dummy	(TAG_USER + 2000)
#define ADO_FH_Mode	(ADO_Dummy + 1)		/* DOS_FILEHANDLE: its mode */
#define ADO_DirLen	(ADO_Dummy + 2)		/* DOS_CLI: buffer sizes */
#define ADO_CommNameLen	(ADO_Dummy + 3)
#define ADO_CommFileLen	(ADO_Dummy + 4)
#define ADO_PromptLen	(ADO_Dummy + 5)

/* More names from the 3.2 interface */
#define SYS_CmdName		(SYS_Dummy + 11)
#define SYS_CmdStream		(SYS_Dummy + 8)
#define SYS_Error		(SYS_Dummy + 6)
#define SYS_ExecuteInputStream	(SYS_Dummy + 7)
#define SYS_InName		(SYS_Dummy + 9)
#define SYS_OutName		(SYS_Dummy + 10)

#endif /* DOS_DOSTAGS_H */
