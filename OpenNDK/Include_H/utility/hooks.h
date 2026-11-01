#ifndef UTILITY_HOOKS_H
#define UTILITY_HOOKS_H
/*
 * OpenNDK: callback hooks.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif

/*
 * A hook is called through h_Entry with a0 = the hook, a2 = the object
 * and a1 = the message. h_SubEntry and h_Data are the hook owner's.
 */
struct Hook {
	struct MinNode h_MinNode;
	ULONG	(*h_Entry)();
	ULONG	(*h_SubEntry)();
	APTR	h_Data;
};

/* The form of a hook function with its arguments named. */
typedef ULONG (*HOOKFUNC)();

#endif /* UTILITY_HOOKS_H */
