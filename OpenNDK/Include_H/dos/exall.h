#ifndef DOS_EXALL_H
#define DOS_EXALL_H
/*
 * OpenNDK: the buffer and control block of ExAll().
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif

/* ExAll()'s type argument: how much of each entry to fill */
#define ED_NAME		1
#define ED_TYPE		2
#define ED_SIZE		3
#define ED_PROTECTION	4
#define ED_DATE		5
#define ED_COMMENT	6
#define ED_OWNER	7

/* One entry; only the fields up to the type asked for are valid */
struct ExAllData {
	struct ExAllData *ed_Next;
	STRPTR	ed_Name;
	LONG	ed_Type;
	ULONG	ed_Size;
	ULONG	ed_Prot;
	ULONG	ed_Days;
	ULONG	ed_Mins;
	ULONG	ed_Ticks;
	STRPTR	ed_Comment;
	UWORD	ed_OwnerUID;
	UWORD	ed_OwnerGID;
};

/* ExAll()'s state; allocate it with AllocDosObject(DOS_EXALLCONTROL) */
struct ExAllControl {
	ULONG	eac_Entries;		/* entries in this buffer */
	ULONG	eac_LastKey;		/* 0 before the first call */
	STRPTR	eac_MatchString;	/* a parsed pattern, or NULL */
	struct Hook *eac_MatchFunc;	/* or a hook that picks entries */
};

#endif /* DOS_EXALL_H */
