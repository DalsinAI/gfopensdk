/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* CreateTask and DeleteTask: a task and its stack in one MemList, which
 * exec frees when the task is removed. */
#include "alib.h"

struct TaskMem {
	struct MemList ml;
	struct MemEntry second;		/* the stack follows the task's entry */
};

struct Task *CreateTask(CONST_STRPTR name, LONG pri, CONST_APTR initPC, ULONG stackSize)
{
	struct TaskMem req;
	struct MemList *ml;
	struct Task *task;
	APTR stack;

	stackSize = (stackSize + 3) & ~3UL;
	req.ml.ml_NumEntries = 2;
	req.ml.ml_ME[0].me_Reqs = MEMF_PUBLIC | MEMF_CLEAR;
	req.ml.ml_ME[0].me_Length = sizeof(struct Task);
	req.second.me_Reqs = MEMF_CLEAR;
	req.second.me_Length = stackSize;
	ml = AllocEntry(&req.ml);
	if ((ULONG)ml & (1UL << 31))
		return NULL;
	task = (struct Task *)ml->ml_ME[0].me_Addr;
	stack = ml->ml_ME[1].me_Addr;
	task->tc_SPLower = stack;
	task->tc_SPUpper = (UBYTE *)stack + stackSize;
	task->tc_SPReg = task->tc_SPUpper;
	task->tc_Node.ln_Type = NT_TASK;
	task->tc_Node.ln_Pri = (BYTE)pri;
	task->tc_Node.ln_Name = (char *)name;
	NewList(&task->tc_MemEntry);
	AddHead(&task->tc_MemEntry, &ml->ml_Node);
	if (!AddTask(task, (APTR)initPC, NULL) && SysBase->LibNode.lib_Version >= 37) {
		FreeEntry(ml);
		return NULL;
	}
	return task;
}

VOID DeleteTask(struct Task *task)
{
	RemTask(task);
}
