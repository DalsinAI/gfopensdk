#ifndef EXEC_MEMORY_H
#define EXEC_MEMORY_H
/*
 * OpenNDK: memory headers, memory lists and allocation flags.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif

/* A free block inside a MemHeader's region. */
struct MemChunk {
	struct MemChunk *mc_Next;
	ULONG	mc_Bytes;
};

/* One region of memory the allocator manages. */
struct MemHeader {
	struct Node mh_Node;
	UWORD	mh_Attributes;	/* MEMF_ flags of this region */
	struct MemChunk *mh_First;
	APTR	mh_Lower;
	APTR	mh_Upper;
	ULONG	mh_Free;
};

/* One block request or result inside a MemList. */
struct MemEntry {
	union {
		ULONG	meu_Reqs;
		APTR	meu_Addr;
	} me_Un;
	ULONG	me_Length;
};

#define me_un		me_Un
#define me_Reqs		me_Un.meu_Reqs
#define me_Addr		me_Un.meu_Addr

/* A set of blocks for AllocEntry() and tc_MemEntry. */
struct MemList {
	struct Node ml_Node;
	UWORD	ml_NumEntries;
	struct MemEntry ml_ME[1];	/* really ml_NumEntries long */
};

#define ml_me		ml_ME

/* Allocation requirements */
#define MEMF_ANY	(0L)
#define MEMF_PUBLIC	(1L<<0)
#define MEMF_CHIP	(1L<<1)
#define MEMF_FAST	(1L<<2)
#define MEMF_VIRTUAL	(1L<<3)
#define MEMF_LOCAL	(1L<<8)
#define MEMF_24BITDMA	(1L<<9)
#define MEMF_KICK	(1L<<10)

#define MEMF_CLEAR	(1L<<16)
#define MEMF_LARGEST	(1L<<17)
#define MEMF_REVERSE	(1L<<18)
#define MEMF_TOTAL	(1L<<19)

#define MEMF_NO_EXPUNGE	(1UL<<31)

/* Allocation granule */
#define MEM_BLOCKSIZE	8L
#define MEM_BLOCKMASK	(MEM_BLOCKSIZE - 1)

/* Passed to a low-memory handler (V39). */
struct MemHandlerData {
	ULONG	memh_RequestSize;
	ULONG	memh_RequestFlags;
	ULONG	memh_Flags;
};

/* memh_Flags */
#define MEMHB_RECYCLE	0
#define MEMHF_RECYCLE	(1L<<0)

/* A memory handler's return values */
#define MEM_DID_NOTHING	(0)
#define MEM_ALL_DONE	(-1)
#define MEM_TRY_AGAIN	(1)

#endif /* EXEC_MEMORY_H */
