#ifndef EXEC_INTERRUPTS_H
#define EXEC_INTERRUPTS_H
/*
 * OpenNDK: interrupt servers, vectors and software interrupt queues.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif

/* An interrupt handler or server. */
struct Interrupt {
	struct Node is_Node;
	APTR	is_Data;	/* passed in a1 */
	VOID	(*is_Code)();	/* entered with the data in a1 */
};

/* One entry of ExecBase's IntVects table. */
struct IntVector {
	APTR	iv_Data;
	VOID	(*iv_Code)();
	struct Node *iv_Node;
};

/* One software interrupt priority queue. */
struct SoftIntList {
	struct List sh_List;
	UWORD	sh_Pad;
};

#define SIH_PRIMASK	(0xf0)
#define SIH_QUEUES	5

/* The NMI's place in the interrupt vector list */
#define INTB_NMI	15
#define INTF_NMI	(1<<15)

#endif /* EXEC_INTERRUPTS_H */
