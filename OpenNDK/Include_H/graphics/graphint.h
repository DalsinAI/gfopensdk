#ifndef GRAPHICS_GRAPHINT_H
#define GRAPHICS_GRAPHINT_H
/*
 * OpenNDK: an old interrupt server record of graphics.library's.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

struct Isrvstr
{
    struct Node     is_Node;
    struct Isrvstr *Iptr;	/* passed to the server */
    LONG          (*code)();
    LONG __STDARGS__ (*ccode) __CLIB_PROTOTYPE((APTR));
    int             Carg;
};

#endif /* GRAPHICS_GRAPHINT_H */
