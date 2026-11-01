#ifndef GRAPHICS_COPPER_H
#define GRAPHICS_COPPER_H
/*
 * OpenNDK: copper instruction lists, the system's and the user's.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* CopIns OpCode */
#define COPPER_MOVE	0
#define COPPER_WAIT	1
#define CPRNXTBUF	2	/* continue in another CopList */
#define CPR_NT_LOF	0x8000	/* only in the long-frame list */
#define CPR_NT_SHT	0x4000	/* only in the short-frame list */
#define CPR_NT_SYS	0x2000	/* user instruction */

/* One intermediate copper instruction */
struct CopIns
{
    WORD OpCode;
    union
    {
	struct CopList *nxtlist;
	struct
	{
	    union
	    {
		WORD VWaitPos;
		WORD DestAddr;
	    } u1;
	    union
	    {
		WORD HWaitPos;
		WORD DestData;
	    } u2;
	} u4;
    } u3;
};

#define NXTLIST		u3.nxtlist
#define VWAITPOS	u3.u4.u1.VWaitPos
#define DESTADDR	u3.u4.u1.DestAddr
#define HWAITPOS	u3.u4.u2.HWaitPos
#define DESTDATA	u3.u4.u2.DestData

/* A finished hardware copper list */
struct cprlist
{
    struct cprlist *Next;
    UWORD          *start;
    WORD            MaxCount;
};

struct CopList
{
    struct CopList  *Next;
    struct CopList  *_CopList;
    struct ViewPort *_ViewPort;
    struct CopIns   *CopIns;	/* the first instruction */
    struct CopIns   *CopPtr;	/* the next free one */
    UWORD           *CopLStart;
    UWORD           *CopSStart;
    WORD             Count;
    WORD             MaxCount;
    WORD             DyOffset;
    UWORD            SLRepeat;
    UWORD            Flags;
};

/* CopList Flags */
#define EXACT_LINE	1
#define HALF_LINE	2

/* A user copper list, built with CINIT, CMOVE, CWAIT and CEND */
struct UCopList
{
    struct UCopList *Next;
    struct CopList  *FirstCopList;
    struct CopList  *CopList;
};

/* The system's initial copper list */
struct copinit
{
    UWORD vsync_hblank[2];
    UWORD diagstrt[12];
    UWORD fm0[2];
    UWORD diwstart[10];
    UWORD bplcon2[2];
    UWORD sprfix[2 * 8];
    UWORD sprstrtup[2 * 8 * 2];
    UWORD wait14[2];
    UWORD norm_hblank[2];
    UWORD jump[2];
    UWORD wait_forever[6];
    UWORD sprstop[8];
};

#endif /* GRAPHICS_COPPER_H */
