#ifndef EXEC_RESIDENT_H
#define EXEC_RESIDENT_H
/*
 * OpenNDK: the ROMTag that marks a resident module.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* A resident module's tag, found by scanning for its match word. */
struct Resident {
	UWORD	rt_MatchWord;	/* RTC_MATCHWORD */
	struct Resident *rt_MatchTag;	/* points back at this structure */
	APTR	rt_EndSkip;	/* where the scan continues */
	UBYTE	rt_Flags;
	UBYTE	rt_Version;
	UBYTE	rt_Type;	/* NT_ type of the module */
	BYTE	rt_Pri;
	char	*rt_Name;
	char	*rt_IdString;
	APTR	rt_Init;
};

/* The 68k ILLEGAL opcode marks a tag. */
#define RTC_MATCHWORD	0x4AFC

/* rt_Flags */
#define RTB_COLDSTART	0
#define RTB_SINGLETASK	1
#define RTB_AFTERDOS	2
#define RTB_AUTOINIT	7

#define RTF_COLDSTART	(1<<0)
#define RTF_SINGLETASK	(1<<1)
#define RTF_AFTERDOS	(1<<2)
#define RTF_AUTOINIT	(1<<7)

/* Old compatibility values */
#define RTW_NEVER	0
#define RTW_COLDSTART	1

#endif /* EXEC_RESIDENT_H */
