#ifndef EXEC_PORTS_H
#define EXEC_PORTS_H
/*
 * OpenNDK: message ports and messages.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif

/* A place messages are queued for a task. */
struct MsgPort {
	struct Node mp_Node;
	UBYTE	mp_Flags;	/* what happens on arrival (PA_) */
	UBYTE	mp_SigBit;	/* signal bit number */
	void	*mp_SigTask;	/* task to signal, or soft interrupt */
	struct List mp_MsgList;
};

#define mp_SoftInt	mp_SigTask

/* mp_Flags */
#define PF_ACTION	3
#define PA_SIGNAL	0
#define PA_SOFTINT	1
#define PA_IGNORE	2

/* True when no message is waiting at the port. */
#define IsMsgPortEmpty(p) \
	(((struct MsgPort *)(p))->mp_MsgList.lh_TailPred == \
	 (struct Node *)(&((struct MsgPort *)(p))->mp_MsgList))

/* The head of every message. */
struct Message {
	struct Node mn_Node;
	struct MsgPort *mn_ReplyPort;
	UWORD	mn_Length;	/* total size including this header */
};

#ifndef EXEC_TASKS_H
#include <exec/tasks.h>
#endif

#endif /* EXEC_PORTS_H */
