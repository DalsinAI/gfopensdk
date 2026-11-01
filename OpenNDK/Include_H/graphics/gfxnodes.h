#ifndef GRAPHICS_GFXNODES_H
#define GRAPHICS_GFXNODES_H
/*
 * OpenNDK: the extended nodes GfxNew() makes and GfxAssociate() links.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

struct ExtendedNode
{
    struct Node *xln_Succ;
    struct Node *xln_Pred;
    UBYTE        xln_Type;
    BYTE         xln_Pri;
    char        *xln_Name;
    UBYTE        xln_Subsystem;
    UBYTE        xln_Subtype;
    LONG         xln_Library;	/* the GfxBase that made it */
    LONG       (* __ASM__ xln_Init) __CLIB_PROTOTYPE((__REG__(a0, struct ExtendedNode *), __REG__(d0, UWORD)));
};

/* xln_Subsystem */
#define SS_GRAPHICS	0x02

/* GfxNew() node types (xln_Subtype) */
#define VIEW_EXTRA_TYPE		1
#define VIEWPORT_EXTRA_TYPE	2
#define SPECIAL_MONITOR_TYPE	3
#define MONITOR_SPEC_TYPE	4

#endif /* GRAPHICS_GFXNODES_H */
