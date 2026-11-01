#ifndef DOS_SHELL_H
#define DOS_SHELL_H
/*
 * OpenNDK: the Shell's extended CLI structure and its line history.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* The Shell's CLI structure: CommandLineInterface's fields, then more */
struct ExtendedCommandLineInterface
{
	LONG	cle_Result2;
	BSTR	cle_SetName;		/* the current directory's name */
	BPTR	cle_CommandDir;
	LONG	cle_ReturnCode;
	BSTR	cle_CommandName;
	LONG	cle_FailLevel;
	BSTR	cle_Prompt;
	BPTR	cle_StandardInput;
	BPTR	cle_CurrentInput;
	BSTR	cle_CommandFile;
	LONG	cle_Interactive;
	LONG	cle_Background;
	BPTR	cle_CurrentOutput;
	LONG	cle_DefaultStack;	/* in longwords */
	BPTR	cle_StandardOutput;
	BPTR	cle_Module;
	struct Hook cle_Hook;		/* the SHELL_METH_ methods */
	struct ExtendedCommandLineInterface *cle_This;	/* itself, when the fields after it are there */
	LONG	cle_Version;
};

/* One line of the history */
struct HistoryNode
{
	struct MinNode hn_Node;
	STRPTR	hn_Line;
};

/* More names from the 3.2 interface */
#define SHELL_DUMMY		0x80000BB8UL
#define SHELL_ADDH_LINE		(SHELL_DUMMY + 2)
#define SHELL_FGETS_FULL	(SHELL_DUMMY + 1)
#define SHELL_METH_ADDHIST	0x41444448
#define SHELL_METH_CLRHIST	0x434C5248
#define SHELL_METH_FGETS	0x47455453
#define SHELL_METH_GETHIST	0x47455448
#define SHELL_METH_METHODS	0x4C495354

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* four characters as one ULONG, first character highest */
#define MAKE_SID(a, b, c, d)	(((ULONG)(a) << 24) | ((ULONG)(b) << 16) | ((ULONG)(c) << 8) | (ULONG)(d))

#endif /* DOS_SHELL_H */
