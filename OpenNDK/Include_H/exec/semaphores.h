#ifndef EXEC_SEMAPHORES_H
#define EXEC_SEMAPHORES_H
/*
 * OpenNDK: signal semaphores and the old message semaphores.
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
#ifndef EXEC_TASKS_H
#include <exec/tasks.h>
#endif

/* A waiter queued on a semaphore. */
struct SemaphoreRequest {
	struct MinNode sr_Link;
	struct Task *sr_Waiter;
};

/* A semaphore that blocks with signals. */
struct SignalSemaphore {
	struct Node ss_Link;
	WORD	ss_NestCount;
	struct MinList ss_WaitQueue;
	struct SemaphoreRequest ss_MultipleLink;
	struct Task *ss_Owner;
	WORD	ss_QueueCount;
};

/* A request for Procure() and Vacate(). */
struct SemaphoreMessage {
	struct Message ssm_Message;
	struct SignalSemaphore *ssm_Semaphore;
};

/* Message type of a semaphore request */
#define SM_LOCKMSG	16

#define SM_SHARED	(1L)
#define SM_EXCLUSIVE	(0L)

/* The older message based semaphore. */
struct Semaphore {
	struct MsgPort sm_MsgPort;
	WORD	sm_Bids;
};

#define sm_LockMsg	mp_SigTask

#endif /* EXEC_SEMAPHORES_H */
