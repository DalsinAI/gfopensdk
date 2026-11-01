#ifndef TOOLS_TEXTEDIT_EXTENSION_H
#define TOOLS_TEXTEDIT_EXTENSION_H
/*
 * OpenNDK: TextEdit's extension plugins.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef DEVICES_TIMER_H
#include <devices/timer.h>
#endif
#ifndef GRAPHICS_RASTPORT_H
#include <graphics/rastport.h>
#endif
#ifndef TOOLS_TEXTEDIT_PLUGIN_H
#include <tools/TextEdit/plugin.h>
#endif
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif

/* What TextEdit offers an extension; each entry is a function */
struct TextEditInterface
{
	APTR	installChangeListener;
	APTR	installLeftBarHook;
	APTR	executeRexxCommand;
	APTR	insertMenu;
	APTR	installTopGadget;
	APTR	installBottomGadget;
	APTR	installSideGadget;
	APTR	setWindowFormatStrings;
	APTR	activateGadget;
};

/* An extension: its data, then the functions TextEdit calls */
struct Extension
{
	APTR	extensionData;
	struct TextEditInterface *tei;
	ULONG	sigMask;		/* signals the extension waits on */
	APTR	setWindowPointer;
	APTR	onNewDocument;
	APTR	onCurrentDocumentChanged;
	APTR	onDisposeDocument;
	APTR	handleGadgetUp;
	APTR	handleRawKey;
	APTR	handleSignal;
	APTR	aboutToQuit;
	APTR	terminate;
};

/* Functions called as the text changes */
struct ChangeListener
{
	APTR	onCharsInserted;
	APTR	onCharsDeleted;
	APTR	onCharEntered;
	APTR	Reserved1;
	APTR	Reserved2;
	APTR	Reserved3;
	APTR	Reserved4;
	APTR	Reserved5;
};

/* A click in the text */
struct ClickMessage
{
	STRPTR	LineContents;
	ULONG	ClickPosition;
};

/* A mouse event in the left bar */
struct LeftBarMouseMessage
{
	UWORD	Command;
	UWORD	Version;
	ULONG	BlockNum;
	UWORD	Code;
	UWORD	Qualifier;
	WORD	X;
	WORD	Y;
	struct TimeVal TimeStamp;
};

/* Drawing one line of the left bar */
struct LeftBarRenderMessage
{
	UWORD	Command;
	UWORD	Version;
	ULONG	BlockNum;
	ULONG	LineSubNum;
	struct RastPort *RastPort;
};

/* More names from the 3.2 interface */
#define EXTENSIONPLUGINHEAD_ID	0x45585453
#define EXTENSIONPLUGIN_VERSION	1

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif

#endif /* TOOLS_TEXTEDIT_EXTENSION_H */
