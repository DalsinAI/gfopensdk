/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* LibCreatePool and friends: exec's pools from V39 on; before that, each
 * allocation is its own AllocMem, kept on a list so DeletePool frees all. */
#include "alib.h"

struct OldPool {
	struct MinList blocks;
	ULONG flags;
};

struct OldBlock {
	struct MinNode node;
	ULONG size;
};

#define HAVE_POOLS (SysBase->LibNode.lib_Version >= 39)

APTR LibCreatePool(ULONG memFlags, ULONG puddleSize, ULONG threshSize)
{
	struct OldPool *p;
	if (HAVE_POOLS)
		return CreatePool(memFlags, puddleSize, threshSize);
	if (threshSize > puddleSize)
		return NULL;
	p = (struct OldPool *)AllocMem(sizeof(*p), MEMF_ANY);
	if (p) {
		NewList((struct List *)&p->blocks);
		p->flags = memFlags;
	}
	return p;
}

VOID LibDeletePool(APTR pool)
{
	struct OldPool *p = (struct OldPool *)pool;
	struct OldBlock *b;
	if (!pool)
		return;
	if (HAVE_POOLS) {
		DeletePool(pool);
		return;
	}
	while ((b = (struct OldBlock *)RemHead((struct List *)&p->blocks)) != NULL)
		FreeMem(b, b->size);
	FreeMem(p, sizeof(*p));
}

APTR LibAllocPooled(APTR pool, ULONG memSize)
{
	struct OldPool *p = (struct OldPool *)pool;
	struct OldBlock *b;
	if (HAVE_POOLS)
		return AllocPooled(pool, memSize);
	b = (struct OldBlock *)AllocMem(memSize + sizeof(*b), p->flags);
	if (!b)
		return NULL;
	b->size = memSize + sizeof(*b);
	AddTail((struct List *)&p->blocks, (struct Node *)&b->node);
	return b + 1;
}

VOID LibFreePooled(APTR pool, APTR memory, ULONG memSize)
{
	struct OldBlock *b;
	(void)memSize;
	if (HAVE_POOLS) {
		FreePooled(pool, memory, memSize);
		return;
	}
	b = (struct OldBlock *)memory - 1;
	Remove((struct Node *)&b->node);
	FreeMem(b, b->size);
}
