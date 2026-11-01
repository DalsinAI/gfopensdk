#ifndef DOS_DOSASL_H
#define DOS_DOSASL_H
/*
 * OpenNDK: the anchor MatchFirst() and MatchNext() walk wildcards with,
 * and the tokens of a parsed pattern.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

/* The caller's anchor. Allocate it longword aligned, with ap_Strlen
 * bytes of ap_Buf after it when the full path is wanted. */
struct AnchorPath {
	struct AChain	*ap_Base;	/* the first level */
#define ap_First ap_Base
	struct AChain	*ap_Last;	/* the level being searched */
#define ap_Current ap_Last
	LONG	ap_BreakBits;		/* signals that stop the search */
	LONG	ap_FoundBreak;		/* which of them did */
	BYTE	ap_Flags;		/* APF_ */
	BYTE	ap_Reserved;
	WORD	ap_Strlen;		/* size of ap_Buf; 0 for none */
#define ap_Length ap_Flags		/* the old name */
	struct FileInfoBlock ap_Info;	/* the match */
	TEXT	ap_Buf[1];		/* the match's full path */
};

#define APB_DOWILD	0	/* obsolete */
#define APF_DOWILD	(1L<<APB_DOWILD)
#define APB_ITSWILD	1	/* the pattern has wildcards */
#define APF_ITSWILD	(1L<<APB_ITSWILD)
#define APB_DODIR	2	/* set by the caller to enter this directory */
#define APF_DODIR	(1L<<APB_DODIR)
#define APB_DIDDIR	3	/* the match is a directory just left */
#define APF_DIDDIR	(1L<<APB_DIDDIR)
#define APB_NOMEMERR	4	/* ran out of memory */
#define APF_NOMEMERR	(1L<<APB_NOMEMERR)
#define APB_DODOT	5	/* obsolete */
#define APF_DODOT	(1L<<APB_DODOT)
#define APB_DirChanged	6	/* the directory changed since the last match */
#define APF_DirChanged	(1L<<APB_DirChanged)
#define APB_FollowHLinks 7	/* enter hard-linked directories */
#define APF_FollowHLinks (1L<<APB_FollowHLinks)

/* One directory level of a search (private) */
struct AChain {
	struct AChain	*an_Child;
	struct AChain	*an_Parent;
	BPTR		an_Lock;
	struct FileInfoBlock an_Info;
	BYTE		an_Flags;	/* DDF_ */
	TEXT	an_String[1];	/* this level's pattern */
};

#define DDB_PatternBit	0
#define DDF_PatternBit	(1L<<DDB_PatternBit)
#define DDB_ExaminedBit	1
#define DDF_ExaminedBit	(1L<<DDB_ExaminedBit)
#define DDB_Completed	2
#define DDF_Completed	(1L<<DDB_Completed)
#define DDB_AllBit	3
#define DDF_AllBit	(1L<<DDB_AllBit)
#define DDB_Single	4
#define DDF_Single	(1L<<DDB_Single)

/* Tokens ParsePattern() writes */
#define P_ANY		0x80	/* #? and * */
#define P_SINGLE	0x81	/* ? */
#define P_ORSTART	0x82	/* ( */
#define P_ORNEXT	0x83	/* | */
#define P_OREND		0x84	/* ) */
#define P_NOT		0x85	/* ~ */
#define P_NOTEND	0x86
#define P_NOTCLASS	0x87	/* [~ */
#define P_CLASS		0x88	/* [ */
#define P_REPBEG	0x89	/* [ of # */
#define P_REPEND	0x8A
#define P_STOP		0x8B

/* Matcher state bits (private) */
#define COMPLEX_BIT	1
#define EXAMINE_BIT	2

#endif /* DOS_DOSASL_H */
