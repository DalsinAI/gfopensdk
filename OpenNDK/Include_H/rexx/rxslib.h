#ifndef REXX_RXSLIB_H
#define REXX_RXSLIB_H
/*
 * OpenNDK: rexxsyslib.library's base and the interpreter's constants.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REXX_STORAGE_H
#include <rexx/storage.h>
#endif

#define RXSNAME		"rexxsyslib.library"
#define RXSDIR		"REXX"		/* the resident process's port, and the scripts' assign */
#define RXSTNAME	"ARexx"

/* The library's base; read only */
struct RxsLib {
	struct Library	rl_Node;
	UBYTE		rl_Flags;	/* RLF_ */
	UBYTE		rl_Shadow;
	APTR		rl_SysBase;
	APTR		rl_DOSBase;
	APTR		rl_IeeeDPBase;
	LONG		rl_SegList;
	LONG		rl_NIL;		/* a stream on NIL: */
	LONG		rl_Chunk;	/* the allocation unit */
	LONG		rl_MaxNest;	/* the deepest nesting allowed */
	struct NexxStr	*rl_NULL;	/* the library's own strings */
	struct NexxStr	*rl_FALSE;
	struct NexxStr	*rl_TRUE;
	struct NexxStr	*rl_REXX;
	struct NexxStr	*rl_COMMAND;
	struct NexxStr	*rl_STDIN;
	struct NexxStr	*rl_STDOUT;
	struct NexxStr	*rl_STDERR;
	STRPTR		rl_Version;
	STRPTR		rl_TaskName;
	LONG		rl_TaskPri;
	LONG		rl_TaskSeg;
	LONG		rl_StackSize;
	STRPTR		rl_RexxDir;
	STRPTR		rl_CTABLE;	/* the character attribute table, CTF_ */
	STRPTR		rl_Notice;
	struct MsgPort	rl_RexxPort;
	UWORD		rl_ReadLock;	/* LockRexxBase()'s count */
	LONG		rl_TraceFH;
	struct List	rl_TaskList;
	WORD		rl_NumTask;
	struct List	rl_LibList;	/* function libraries and hosts */
	WORD		rl_NumLib;
	struct List	rl_ClipList;
	WORD		rl_NumClip;
	struct List	rl_MsgList;	/* messages out from the interpreter */
	WORD		rl_NumMsg;
	struct List	rl_PgmList;	/* cached programs */
	WORD		rl_NumPgm;
	UWORD		rl_TraceCnt;	/* tasks being traced */
	WORD		rl_avail;
	APTR		rl_UtilityBase;
};

/* rl_Flags */
#define RLFB_TRACE	RTFB_TRACE
#define RLFB_HALT	RTFB_HALT
#define RLFB_SUSP	RTFB_SUSP
#define RLFB_STOP	6
#define RLFB_CLOSE	7

#define RLFMASK		((1<<RLFB_TRACE) | (1<<RLFB_HALT) | (1<<RLFB_SUSP))

/* The interpreter's defaults */
#define RXSCHUNK	1024
#define RXSNEST		32
#define RXSTPRI		0
#define RXSSTACK	4096

/* rl_CTABLE: one byte of these bits per character */
#define CTB_SPACE	0
#define CTB_DIGIT	1
#define CTB_ALPHA	2
#define CTB_REXXSYM	3
#define CTB_REXXOPR	4
#define CTB_REXXSPC	5
#define CTB_UPPER	6
#define CTB_LOWER	7

#define CTF_SPACE	(1<<CTB_SPACE)
#define CTF_DIGIT	(1<<CTB_DIGIT)
#define CTF_ALPHA	(1<<CTB_ALPHA)
#define CTF_REXXSYM	(1<<CTB_REXXSYM)
#define CTF_REXXOPR	(1<<CTB_REXXOPR)
#define CTF_REXXSPC	(1<<CTB_REXXSPC)
#define CTF_UPPER	(1<<CTB_UPPER)
#define CTF_LOWER	(1<<CTB_LOWER)

#endif /* REXX_RXSLIB_H */
