#ifndef INTUITION_SGHOOKS_H
#define INTUITION_SGHOOKS_H
/*
 * OpenNDK: string gadget extensions and their editing hooks.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* StringInfo.Extension, with GFLG_STRINGEXTEND */
struct StringExtend
{
    struct TextFont *Font;		/* opened by the program */
    UBYTE Pens[2];			/* text and background, inactive */
    UBYTE ActivePens[2];		/* the same, active */
    ULONG InitialModes;			/* SGM_ */
    struct Hook *EditHook;
    STRPTR	WorkBuffer;			/* as big as the gadget's buffer */
    ULONG Reserved[4];
};

/* What an edit hook's SGH_KEY or SGH_CLICK message points to */
struct SGWork
{
    struct Gadget *Gadget;
    struct StringInfo *StringInfo;
    STRPTR	WorkBuffer;
    STRPTR	PrevBuffer;
    ULONG Modes;
    struct InputEvent *IEvent;
    UWORD Code;
    WORD BufferPos;
    WORD NumChars;
    ULONG Actions;			/* SGA_ */
    LONG LongInt;
    struct GadgetInfo *GadgetInfo;
    UWORD EditOp;			/* EO_ */
};

/* SGWork.EditOp: what the default editing did */
#define EO_NOOP		(0x0001)
#define EO_DELBACKWARD	(0x0002)
#define EO_DELFORWARD	(0x0003)
#define EO_MOVECURSOR	(0x0004)
#define EO_ENTER	(0x0005)
#define EO_RESET	(0x0006)
#define EO_REPLACECHAR	(0x0007)
#define EO_INSERTCHAR	(0x0008)
#define EO_BADFORMAT	(0x0009)
#define EO_BIGCHANGE	(0x000A)
#define EO_UNDO		(0x000B)
#define EO_CLEAR	(0x000C)
#define EO_SPECIAL	(0x000D)

/* Editing modes (InitialModes, SGWork.Modes) */
#define SGM_REPLACE	(1L << 0)
#define SGM_FIXEDFIELD	(1L << 1)
#define SGM_NOFILTER	(1L << 2)
#define SGM_EXITHELP	(1L << 7)	/* V37 */

/* Kept by Intuition */
#define SGM_NOCHANGE	(1L << 3)
#define SGM_NOWORKB	(1L << 4)
#define SGM_CONTROL	(1L << 5)
#define SGM_LONGINT	(1L << 6)

/* SGWork.Actions: what happens after the hook */
#define SGA_USE		(0x1L)
#define SGA_END		(0x2L)
#define SGA_BEEP	(0x4L)
#define SGA_REUSE	(0x8L)
#define SGA_REDISPLAY	(0x10L)
#define SGA_NEXTACTIVE	(0x20L)		/* V37 */
#define SGA_PREVACTIVE	(0x40L)		/* V37 */

/* The edit hook's commands */
#define SGH_KEY		(1L)
#define SGH_CLICK	(2L)

#endif /* INTUITION_SGHOOKS_H */
