#ifndef EXEC_AVL_H
#define EXEC_AVL_H
/*
 * OpenNDK: nodes and compare hooks of exec's balanced trees.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* A tree node; its contents are private. Embed it in your own structure. */
struct AVLNode {
	ULONG	reserved[4];
};

/* A search key, interpreted by the key compare hook. */
typedef APTR AVLKey;

/* Compare two nodes, or a node with a key: negative, zero or positive. */
typedef LONG (*AVLNODECOMP)(const struct AVLNode *, const struct AVLNode *);
typedef LONG (*AVLKEYCOMP)(const struct AVLNode *, AVLKey);

#endif /* EXEC_AVL_H */
