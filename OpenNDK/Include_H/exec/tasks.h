#ifndef EXEC_TASKS_H
#define EXEC_TASKS_H
/*
 * OpenNDK: tasks, their states, flags and signals.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif

/* A task control block. */
struct Task {
	struct Node tc_Node;
	UBYTE	tc_Flags;
	UBYTE	tc_State;
	BYTE	tc_IDNestCnt;	/* interrupt disable depth */
	BYTE	tc_TDNestCnt;	/* task switch disable depth */
	ULONG	tc_SigAlloc;
	ULONG	tc_SigWait;
	ULONG	tc_SigRecvd;
	ULONG	tc_SigExcept;
	UWORD	tc_TrapAlloc;
	UWORD	tc_TrapAble;
	APTR	tc_ExceptData;
	APTR	tc_ExceptCode;
	APTR	tc_TrapData;
	APTR	tc_TrapCode;
	APTR	tc_SPReg;	/* saved stack pointer */
	APTR	tc_SPLower;
	APTR	tc_SPUpper;
	VOID	(*tc_Switch)();	/* called when the task loses the CPU */
	VOID	(*tc_Launch)();	/* called when it gets the CPU */
	struct List tc_MemEntry;	/* memory freed when the task ends */
	APTR	tc_UserData;
};

/* Stack description for StackSwap(). */
struct StackSwapStruct {
	APTR	stk_Lower;
	ULONG	stk_Upper;
	APTR	stk_Pointer;
};

/* Extended task data (V36); the fields after these are private. */
struct ETask {
	struct Message et_Message;
	APTR	et_Parent;
	ULONG	et_UniqueID;
	struct MinList et_Children;
	UWORD	et_TrapAlloc;
	UWORD	et_TrapAble;
	ULONG	et_Result1;
	APTR	et_Result2;
	struct MsgPort et_TaskMsgPort;
};

/* Return codes of the child task calls */
#define CHILD_NOTNEW	1
#define CHILD_NOTFOUND	2
#define CHILD_EXITED	3
#define CHILD_ACTIVE	4

/* tc_Flags */
#define TB_PROCTIME	0
#define TB_ETASK	3
#define TB_STACKCHK	4
#define TB_EXCEPT	5
#define TB_SWITCH	6
#define TB_LAUNCH	7

#define TF_PROCTIME	(1<<0)
#define TF_ETASK	(1<<3)
#define TF_STACKCHK	(1<<4)
#define TF_EXCEPT	(1<<5)
#define TF_SWITCH	(1<<6)
#define TF_LAUNCH	(1<<7)

/* tc_State */
#define TS_INVALID	0
#define TS_ADDED	1
#define TS_RUN		2
#define TS_READY	3
#define TS_WAIT		4
#define TS_EXCEPT	5
#define TS_REMOVED	6

/* Signals the system reserves */
#define SIGB_ABORT	0
#define SIGB_CHILD	1
#define SIGB_BLIT	4
#define SIGB_SINGLE	4
#define SIGB_INTUITION	5
#define SIGB_NET	7
#define SIGB_DOS	8

#define SIGF_ABORT	(1L<<0)
#define SIGF_CHILD	(1L<<1)
#define SIGF_BLIT	(1L<<4)
#define SIGF_SINGLE	(1L<<4)
#define SIGF_INTUITION	(1L<<5)
#define SIGF_NET	(1L<<7)
#define SIGF_DOS	(1L<<8)

/* Signals and traps every new task starts with */
#define SYS_SIGALLOC	0x0FFFF
#define SYS_TRAPALLOC	0x08000

#endif /* EXEC_TASKS_H */
