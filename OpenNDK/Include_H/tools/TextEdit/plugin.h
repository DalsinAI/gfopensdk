#ifndef TOOLS_TEXTEDIT_PLUGIN_H
#define TOOLS_TEXTEDIT_PLUGIN_H
/*
 * OpenNDK: TextEdit's plugin files.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

/* One plugin in a plugin file */
struct Plugin
{
	struct Plugin *p_Next;
	UWORD	p_Version;		/* PLUGINHEAD_VERSION */
	UWORD	p_MasterVersion;	/* MASTER_VERSION */
	UWORD	p_PluginVersion;
	UWORD	p_PluginRevision;
	UWORD	p_Identifier;
	UWORD	p_Flags;
	APTR	init;			/* called to start it */
};

/* The head of a plugin file, found by ph_Security */
struct PluginHead
{
	ULONG	ph_Security;		/* PLUGINHEAD_SECURITY */
	ULONG	ph_ID;
	BPTR	ph_SegList;
	struct PluginHead *ph_Next;
	UWORD	ph_Version;
	UWORD	ph_Reserved;
	STRPTR	ph_VersString;
	struct Plugin *ph_FirstPlugin;
};

/* More names from the 3.2 interface */
#define MASTER_VERSION		2
#define PLUGINHEAD_SECURITY	0x70FF4E75
#define PLUGINHEAD_VERSION	1

#endif /* TOOLS_TEXTEDIT_PLUGIN_H */
