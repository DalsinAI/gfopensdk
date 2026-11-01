#ifndef EXEC_LIBRARIES_H
#define EXEC_LIBRARIES_H
/*
 * OpenNDK: the library base and the standard library vectors.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif

/* Each jump table entry is a JMP with a 32-bit address. */
#define LIB_VECTSIZE	6
#define LIB_RESERVED	4
#define LIB_BASE	(-LIB_VECTSIZE)
#define LIB_USERDEF	(LIB_BASE - (LIB_RESERVED * LIB_VECTSIZE))
#define LIB_NONSTD	(LIB_USERDEF)

/* The four standard vectors every library has */
#define LIB_OPEN	(-6)
#define LIB_CLOSE	(-12)
#define LIB_EXPUNGE	(-18)
#define LIB_EXTFUNC	(-24)

/* The common head of every library base. */
struct Library {
	struct Node lib_Node;
	UBYTE	lib_Flags;
	UBYTE	lib_pad;
	UWORD	lib_NegSize;	/* bytes of jump table before the base */
	UWORD	lib_PosSize;	/* bytes of data after the base */
	UWORD	lib_Version;
	UWORD	lib_Revision;
	APTR	lib_IdString;
	ULONG	lib_Sum;	/* checksum of the jump table */
	UWORD	lib_OpenCnt;
};

/* lib_Flags */
#define LIBF_SUMMING	(1<<0)
#define LIBF_CHANGED	(1<<1)
#define LIBF_SUMUSED	(1<<2)
#define LIBF_DELEXP	(1<<3)

/* Old field names */
#define lh_Node		lib_Node
#define lh_Flags	lib_Flags
#define lh_pad		lib_pad
#define lh_NegSize	lib_NegSize
#define lh_PosSize	lib_PosSize
#define lh_Version	lib_Version
#define lh_Revision	lib_Revision
#define lh_IdString	lib_IdString
#define lh_Sum		lib_Sum
#define lh_OpenCnt	lib_OpenCnt

#endif /* EXEC_LIBRARIES_H */
