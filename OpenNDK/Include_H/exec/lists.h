#ifndef EXEC_LISTS_H
#define EXEC_LISTS_H
/*
 * OpenNDK: doubly linked list headers and helper macros.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif

/* A list of struct Node. Head and tail nodes overlap at lh_Tail. */
struct List {
	struct Node *lh_Head;
	struct Node *lh_Tail;
	struct Node *lh_TailPred;
	UBYTE	lh_Type;
	UBYTE	l_pad;
};

/* A list of struct MinNode. */
struct MinList {
	struct MinNode *mlh_Head;
	struct MinNode *mlh_Tail;
	struct MinNode *mlh_TailPred;
};

/* True when the list holds no nodes. */
#define IsListEmpty(l) \
	(((struct List *)(l))->lh_TailPred == (struct Node *)(l))
#define IsMinListEmpty(l) \
	(((struct MinList *)(l))->mlh_TailPred == (struct MinNode *)(l))

#endif /* EXEC_LISTS_H */
