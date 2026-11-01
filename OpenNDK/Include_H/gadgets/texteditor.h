#ifndef GADGETS_TEXTEDITOR_H
#define GADGETS_TEXTEDITOR_H
/*
 * OpenNDK: texteditor.gadget, a multi-line text editing field.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif
#ifndef INTUITION_CGHOOKS_H
#include <intuition/cghooks.h>
#endif
#ifndef IMAGES_BEVEL_H
#include <images/bevel.h>
#endif

#define GA_TEXTEDITOR_Dummy		(REACTION_Dummy + 0x26000)

#define GA_TEXTEDITOR_Contents		0x45002	/* STRPTR: the whole text */
#define GA_TEXTEDITOR_PopWindow_Open	0x45003
#define GA_TEXTEDITOR_CursorX		0x45004
#define GA_TEXTEDITOR_CursorY		0x45005
#define GA_TEXTEDITOR_DoubleClickHook	0x45006
#define GA_TEXTEDITOR_TypeAndSpell	0x45007
#define GA_TEXTEDITOR_ExportHook	0x45008
#define GA_TEXTEDITOR_ExportWrap	0x45009
#define GA_TEXTEDITOR_FixedFont		0x4500A
#define GA_TEXTEDITOR_Flow		0x4500B	/* GV_TEXTEDITOR_Flow_ below */
#define GA_TEXTEDITOR_HasChanged	0x4500C
#define GA_TEXTEDITOR_Prop_DeltaFactor	0x4500D
#define GA_TEXTEDITOR_ImportHook	0x4500E
#define GA_TEXTEDITOR_InsertMode	0x4500F
#define GA_TEXTEDITOR_ImportWrap	0x45010
#define GA_TEXTEDITOR_KeyBindings	0x45011
#define GA_TEXTEDITOR_UndoAvailable	0x45012
#define GA_TEXTEDITOR_RedoAvailable	0x45013
#define GA_TEXTEDITOR_AreaMarked	0x45014
#define GA_TEXTEDITOR_Prop_Entries	0x45015	/* for a scroller: lines in all */
#define GA_TEXTEDITOR_Prop_Visible	0x45016	/* lines in view */
#define GA_TEXTEDITOR_Quiet		0x45017	/* BOOL: hold off redrawing */
#define GA_TEXTEDITOR_NumLock		0x45018
#define GA_TEXTEDITOR_ReadOnly		0x45019
#define GA_TEXTEDITOR_InVirtualGadget	(GA_TEXTEDITOR_Dummy + 0x1B)
#define GA_TEXTEDITOR_StyleBold		0x4501C
#define GA_TEXTEDITOR_StyleItalic	0x4501D
#define GA_TEXTEDITOR_StyleUnderline	0x4501E
#define GA_TEXTEDITOR_Prop_First	0x45020	/* the first line in view */
#define GA_TEXTEDITOR_WrapBorder	0x45021
#define GA_TEXTEDITOR_Separator		0x4502C
#define GA_TEXTEDITOR_Pen		0x4502E
#define GA_TEXTEDITOR_ColorMap		0x4502F
#define GA_TEXTEDITOR_Rows		(GA_TEXTEDITOR_Dummy + 0x32)
#define GA_TEXTEDITOR_Columns		(GA_TEXTEDITOR_Dummy + 0x33)
#define GA_TEXTEDITOR_AutoClip		(GA_TEXTEDITOR_Dummy + 0x34)

/* Values */
#define GV_TEXTEDITOR_ExportHook_Plain		0
#define GV_TEXTEDITOR_ExportHook_EMail		1
#define GV_TEXTEDITOR_ImportHook_Plain		0
#define GV_TEXTEDITOR_ImportHook_EMail		2
#define GV_TEXTEDITOR_ImportHook_MIME		3
#define GV_TEXTEDITOR_ImportHook_MIMEQuoted	4
#define GV_TEXTEDITOR_Flow_Left			0
#define GV_TEXTEDITOR_Flow_Center		1
#define GV_TEXTEDITOR_Flow_Right		2
#define GV_TEXTEDITOR_Flow_Justified		3
#define GV_TEXTEDITOR_InsertText_Cursor		0
#define GV_TEXTEDITOR_InsertText_Top		1
#define GV_TEXTEDITOR_InsertText_Bottom		2

/* GM_TEXTEDITOR_Search and _Replace flags */
#define GF_TEXTEDITOR_Search_FromTop		(1 << 0)
#define GF_TEXTEDITOR_Search_Next		(1 << 1)
#define GF_TEXTEDITOR_Search_CaseSensitive	(1 << 2)
#define GF_TEXTEDITOR_Search_DOSPattern		(1 << 3)
#define GF_TEXTEDITOR_Search_Backwards		(1 << 4)

/* Methods */
#define GM_TEXTEDITOR_Dummy		0x45000

#define GM_TEXTEDITOR_HandleError	(GM_TEXTEDITOR_Dummy + 0x1F)
#define GM_TEXTEDITOR_AddKeyBindings	(GM_TEXTEDITOR_Dummy + 0x22)
#define GM_TEXTEDITOR_ARexxCmd		(GM_TEXTEDITOR_Dummy + 0x23)
#define GM_TEXTEDITOR_ClearText		(GM_TEXTEDITOR_Dummy + 0x24)
#define GM_TEXTEDITOR_ExportText	(GM_TEXTEDITOR_Dummy + 0x25)
#define GM_TEXTEDITOR_InsertText	(GM_TEXTEDITOR_Dummy + 0x26)
#define GM_TEXTEDITOR_MacroBegin	(GM_TEXTEDITOR_Dummy + 0x27)
#define GM_TEXTEDITOR_MacroEnd		(GM_TEXTEDITOR_Dummy + 0x28)
#define GM_TEXTEDITOR_MacroExecute	(GM_TEXTEDITOR_Dummy + 0x29)
#define GM_TEXTEDITOR_Replace		(GM_TEXTEDITOR_Dummy + 0x2A)
#define GM_TEXTEDITOR_Search		(GM_TEXTEDITOR_Dummy + 0x2B)
#define GM_TEXTEDITOR_MarkText		(GM_TEXTEDITOR_Dummy + 0x2C)
#define GM_TEXTEDITOR_BlockInfo		(GM_TEXTEDITOR_Dummy + 0x30)
#define GM_TEXTEDITOR_QueryKeyAction	(GM_TEXTEDITOR_Dummy + 0x31)

struct GP_TEXTEDITOR_ARexxCmd
{
	ULONG			MethodID;
	struct GadgetInfo	*GInfo;
	STRPTR			command;	/* a command line; the answer is the method's result */
};

struct GP_TEXTEDITOR_BlockInfo
{
	ULONG			MethodID;
	struct GadgetInfo	*GInfo;
	ULONG			*startx;	/* filled in with the marked block's corners */
	ULONG			*starty;
	ULONG			*stopx;
	ULONG			*stopy;
};

struct GP_TEXTEDITOR_ClearText
{
	ULONG			MethodID;
	struct GadgetInfo	*GInfo;
};

struct GP_TEXTEDITOR_ExportText
{
	ULONG			MethodID;
	struct GadgetInfo	*GInfo;
};

struct GP_TEXTEDITOR_InsertText
{
	ULONG			MethodID;
	struct GadgetInfo	*GInfo;
	STRPTR			text;
	LONG			pos;		/* GV_TEXTEDITOR_InsertText_ */
};

struct GP_TEXTEDITOR_MarkText
{
	ULONG			MethodID;
	struct GadgetInfo	*GInfo;
	ULONG			start_crsr_x;
	ULONG			start_crsr_y;
	ULONG			stop_crsr_x;
	ULONG			stop_crsr_y;
};

struct GP_TEXTEDITOR_Replace
{
	ULONG			MethodID;
	struct GadgetInfo	*GInfo;
	STRPTR			newstring;
	ULONG			flags;
};

struct GP_TEXTEDITOR_Search
{
	ULONG			MethodID;
	struct GadgetInfo	*GInfo;
	STRPTR			string;
	ULONG			flags;		/* GF_TEXTEDITOR_Search_ */
};

struct GP_TEXTEDITOR_ReplaceAll
{
	ULONG			MethodID;
	struct GadgetInfo	*GInfo;
	STRPTR			string;
	STRPTR			newstring;
	ULONG			flags;
};

struct GP_TEXTEDITOR_AddChangeListener
{
	ULONG			MethodID;
	struct ChangeListener	*listener;	/* tools/TextEdit/extension.h */
};

struct GP_TEXTEDITOR_HandleError
{
	ULONG			MethodID;
	ULONG			errorcode;	/* Error_ */
};

/* What a syntax highlighter is given for each line */
struct HighlightMessage
{
	ULONG			Version;
	STRPTR			Text;
	ULONG			StatusOfPrevBlock;
};

/* A word to colour */
struct WordColorEntry
{
	UBYTE			ColorWord[8];
};

/* More names from the 3.2 interface */
#define TEXTEDITOR_Dummy	(GM_TEXTEDITOR_Dummy + 0)
#define Error_BookmarkHasBeenLost	12
#define Error_ClipboardIsEmpty	1
#define Error_ClipboardIsNotFTXT	2
#define Error_MacroBufferIsFull	3
#define Error_MemoryAllocationFailed	4
#define Error_NoAreaMarked	5
#define Error_NoBookmarkInstalled	11
#define Error_NoMacroDefined	6
#define Error_NotEnoughUndoMem	9
#define Error_NothingToRedo	7
#define Error_NothingToUndo	8
#define Error_StringNotFound	10
#define GA_TEXTEDITOR_AutoIndent	(GM_TEXTEDITOR_Dummy + 59)
#define GA_TEXTEDITOR_BevelStyle	(GM_TEXTEDITOR_Dummy + 71)
#define GA_TEXTEDITOR_CursorBlinkSpeed	(GM_TEXTEDITOR_Dummy + 56)
#define GA_TEXTEDITOR_CutCopyLineWhenNoSelection	(GM_TEXTEDITOR_Dummy + 60)
#define GA_TEXTEDITOR_Dragging	(GM_TEXTEDITOR_Dummy + 68)
#define GA_TEXTEDITOR_EOLMarker	(GM_TEXTEDITOR_Dummy + 69)
#define GA_TEXTEDITOR_ErrorCode	(GM_TEXTEDITOR_Dummy + 54)
#define GA_TEXTEDITOR_ExitHelp	(GM_TEXTEDITOR_Dummy + 52)
#define GA_TEXTEDITOR_HProp_DeltaFactor	(GM_TEXTEDITOR_Dummy + 48)
#define GA_TEXTEDITOR_HProp_Entries	(GM_TEXTEDITOR_Dummy + 49)
#define GA_TEXTEDITOR_HProp_First	(GM_TEXTEDITOR_Dummy + 50)
#define GA_TEXTEDITOR_HProp_Visible	(GM_TEXTEDITOR_Dummy + 51)
#define GA_TEXTEDITOR_HighlighterHook	(GM_TEXTEDITOR_Dummy + 55)
#define GA_TEXTEDITOR_HorizScroller	(GM_TEXTEDITOR_Dummy + 64)
#define GA_TEXTEDITOR_HorizontalScroll	(GM_TEXTEDITOR_Dummy + 45)
#define GA_TEXTEDITOR_IndentWidth	(GM_TEXTEDITOR_Dummy + 54)
#define GA_TEXTEDITOR_Keymap	(GM_TEXTEDITOR_Dummy + 55)
#define GA_TEXTEDITOR_LeftBarHook	(GM_TEXTEDITOR_Dummy + 57)
#define GA_TEXTEDITOR_Length	(GM_TEXTEDITOR_Dummy + 58)
#define GA_TEXTEDITOR_LineEndingExport	(GM_TEXTEDITOR_Dummy + 62)
#define GA_TEXTEDITOR_LineEndingImported	(GM_TEXTEDITOR_Dummy + 61)
#define GA_TEXTEDITOR_LookAhead	(GM_TEXTEDITOR_Dummy + 70)
#define GA_TEXTEDITOR_MaxUndoLevels	(GM_TEXTEDITOR_Dummy + 73)
#define GA_TEXTEDITOR_MaxUndoSize	(GM_TEXTEDITOR_Dummy + 74)
#define GA_TEXTEDITOR_Prop_Release	(GM_TEXTEDITOR_Dummy + 1)
#define GA_TEXTEDITOR_RectangularSelections	(GM_TEXTEDITOR_Dummy + 58)
#define GA_TEXTEDITOR_ShowLineNumbers	(GM_TEXTEDITOR_Dummy + 56)
#define GA_TEXTEDITOR_SpacesPerTAB	(GM_TEXTEDITOR_Dummy + 53)
#define GA_TEXTEDITOR_TabKeyPolicy	(GM_TEXTEDITOR_Dummy + 63)
#define GA_TEXTEDITOR_TabSize	(GM_TEXTEDITOR_Dummy + 53)
#define GA_TEXTEDITOR_TabToSpaces	(GM_TEXTEDITOR_Dummy + 67)
#define GA_TEXTEDITOR_TextAttr	(GM_TEXTEDITOR_Dummy + 66)
#define GA_TEXTEDITOR_Transparent	(GM_TEXTEDITOR_Dummy + 72)
#define GA_TEXTEDITOR_VertScroller	(GM_TEXTEDITOR_Dummy + 65)
#define GF_TEXTEDITOR_Highlight_All	19
#define GF_TEXTEDITOR_Replace_All	1
#define GF_TEXTEDITOR_SearchType_Mask	19
#define GF_TEXTEDITOR_Search_Cyclic	128
#define GF_TEXTEDITOR_Search_Incremental	3
#define GF_TEXTEDITOR_Search_WholeWord	64
#define GF_TEXTEDITOR_Search_Wildstar	32
#define GF_TEXTEDITOR_Search_Word	64
#define GM_TEXTEDITOR_AddChangeListener	(GM_TEXTEDITOR_Dummy + 49)
#define GM_TEXTEDITOR_ExportBlock	(GM_TEXTEDITOR_Dummy + 68)
#define GM_TEXTEDITOR_ReplaceAll	(GM_TEXTEDITOR_Dummy + 75)
#define GV_TEXTEDITOR_LengthHook_ANSI	1
#define GV_TEXTEDITOR_LengthHook_HTML	2
#define GV_TEXTEDITOR_LengthHook_MAIL	3
#define GV_TEXTEDITOR_LengthHook_Plain	0
#define GV_TEXTEDITOR_TabKey_IndentsAfter	1
#define GV_TEXTEDITOR_TabKey_IndentsLine	0
#define LEFTBAR_MOUSECOMMAND	1
#define LEFTBAR_RENDERCOMMAND	0
#define LINEENDING_ASIMPORT	3
#define LINEENDING_CR		1
#define LINEENDING_CRLF		2
#define LINEENDING_LF		0
#define LNSB_Bottom		2
#define LNSB_Middle		1
#define LNSB_StrikeThru		3
#define LNSB_Thick		4
#define LNSB_Top		0
#define LNSF_Bottom		4
#define LNSF_Middle		2
#define LNSF_StrikeThru		8
#define LNSF_Thick		16
#define LNSF_Top		1
#define TBSTYLE_BOLD		2
#define TBSTYLE_COLORMASK	0xFF00
#define TBSTYLE_ITALIC		4
#define TBSTYLE_NOTSET		0xFF00
#define TBSTYLE_SETCOLOR	8
#define TBSTYLE_SPELLERROR	64
#define TBSTYLE_STYLEMASK	255
#define TBSTYLE_UNDERLINE	1

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef IMAGES_BEVEL_H
#include <images/bevel.h>
#endif

#endif /* GADGETS_TEXTEDITOR_H */
