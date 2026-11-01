/* Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * exec calls OS 4 has and OS 3.2 has not: system objects, tagged AllocVec,
 * list helpers, mutexes and DebugPrintF.
 */
#include "os4c_internal.h"
#include <exec/execbase.h>
#include <clib/alib_protos.h>
#include <proto/exec.h>
#include <proto/utility.h>
#include <inline/macros.h>

/* exec's private serial output, as kprintf uses it */
#define RawPutChar(c) LP1NR(0x204, RawPutChar, UBYTE, c, d0, , SysBase)

static ULONG strlen0(CONST_STRPTR s)
{
	ULONG n = 0;
	if (s)
		while (s[n]) n++;
	return n;
}

static STRPTR copy_after(APTR obj, ULONG size, CONST_STRPTR s)
{
	STRPTR d = (STRPTR)obj + size;
	ULONG i = 0;
	do d[i] = s[i]; while (s[i++]);
	return d;
}

/* ---- tagged AllocVec ---- */
APTR os4c_AllocVecTagList(ULONG size, struct TagItem *tags)
{
	ULONG flags = GetTagData(AVT_Type, MEMF_ANY, tags) & ~MEMF_OS4ONLY;
	struct TagItem *clr = FindTagItem(AVT_ClearWithValue, tags);
	/* AVT_Alignment: AllocVec gives 8; more could not be freed with FreeVec */
	UBYTE *mem = AllocVec(size, flags);

	if (mem && clr) {
		UBYTE v = (UBYTE)clr->ti_Data;
		ULONG i;
		for (i = 0; i < size; i++)
			mem[i] = v;
	}
	return mem;
}

APTR os4c_AllocVecTags(ULONG size, ...)
{
	va_list ap;
	APTR r;
	va_start(ap, size);
	r = os4c_AllocVecTagList(size, (struct TagItem *)ap);
	va_end(ap);
	return r;
}

/* ---- system objects ---- */
/* What FreeSysObject needs to know about a port or semaphore lives in a
 * header in front of the object, so all of ASOPORT_Size or ASOSEM_Size is
 * the caller's, as on OS 4. 8 bytes keep the object 8-byte aligned. */
struct os4c_hdr { BYTE ownsig; BYTE pub; UBYTE pad[6]; };
#define HDR(obj) ((struct os4c_hdr *)(obj) - 1)

static APTR hdr_alloc(ULONG size, ULONG extra, ULONG mflags)
{
	struct os4c_hdr *h = AllocVec(sizeof(*h) + size + extra, mflags | MEMF_CLEAR);
	return h ? h + 1 : NULL;
}

/* ASOPOOL_Protected pools: exec's pools have no lock, so the kit keeps one
 * per protected pool and takes it in the pooled calls below */
struct os4c_ppool { struct MinNode node; APTR pool; struct SignalSemaphore lock; };
static struct MinList ppools = { (struct MinNode *)&ppools.mlh_Tail, NULL, (struct MinNode *)&ppools.mlh_Head };

static struct os4c_ppool *find_ppool(APTR pool)
{
	struct MinNode *n;
	struct os4c_ppool *found = NULL;
	if (!pool)
		return NULL;
	Forbid();
	for (n = ppools.mlh_Head; n->mln_Succ; n = n->mln_Succ)
		if (((struct os4c_ppool *)n)->pool == pool) {
			found = (struct os4c_ppool *)n;
			break;
		}
	Permit();
	return found;
}

APTR os4c_AllocPooled(APTR pool, ULONG size)
{
	struct os4c_ppool *p = find_ppool(pool);
	APTR m;
	if (!p)
		return AllocPooled(pool, size);
	ObtainSemaphore(&p->lock);
	m = AllocPooled(pool, size);
	ReleaseSemaphore(&p->lock);
	return m;
}

VOID os4c_FreePooled(APTR pool, APTR memory, ULONG size)
{
	struct os4c_ppool *p = find_ppool(pool);
	if (!p) {
		FreePooled(pool, memory, size);
		return;
	}
	ObtainSemaphore(&p->lock);
	FreePooled(pool, memory, size);
	ReleaseSemaphore(&p->lock);
}

/* the size goes in front, as AllocVec keeps it */
APTR os4c_AllocVecPooled(APTR pool, ULONG size)
{
	ULONG *m = os4c_AllocPooled(pool, size + 8);
	if (!m)
		return NULL;
	m[0] = size + 8;
	return m + 2;
}

VOID os4c_FreeVecPooled(APTR pool, APTR memory)
{
	ULONG *m = memory;
	if (m) {
		m -= 2;
		os4c_FreePooled(pool, m, m[0]);
	}
}

VOID os4c_DeletePool(APTR pool)
{
	struct os4c_ppool *p = find_ppool(pool);
	if (p) {
		Forbid();
		Remove((struct Node *)&p->node);
		Permit();
		FreeVec(p);
	}
	DeletePool(pool);
}

APTR os4c_AllocSysObject(ULONG type, struct TagItem *tags)
{
	ULONG mflags = (GetTagData(ASO_MemoryOvr, MEMF_PUBLIC, tags) & ~MEMF_OS4ONLY) | MEMF_CLEAR;

	switch (type) {
	case ASOT_IOREQUEST: {
		struct IORequest *dup = (struct IORequest *)GetTagData(ASOIOR_Duplicate, 0, tags);
		struct MsgPort *port = (struct MsgPort *)GetTagData(ASOIOR_ReplyPort,
			dup ? (ULONG)dup->io_Message.mn_ReplyPort : 0, tags);
		ULONG size = GetTagData(ASOIOR_Size,
			dup ? dup->io_Message.mn_Length : sizeof(struct IORequest), tags);
		struct IORequest *io = AllocVec(size, mflags);
		if (!io)
			return NULL;
		/* copy no more than the original holds: ASOIOR_Size may be larger */
		if (dup)
			CopyMem(dup, io, size < dup->io_Message.mn_Length ? size : dup->io_Message.mn_Length);
		io->io_Message.mn_Node.ln_Type = NT_REPLYMSG;
		io->io_Message.mn_ReplyPort = port;
		io->io_Message.mn_Length = size;
		return io;
	}
	case ASOT_HOOK: {
		ULONG size = GetTagData(ASOHOOK_Size, sizeof(struct Hook), tags);
		struct Hook *h = AllocVec(size, mflags);
		if (!h)
			return NULL;
		/* OS 4 hooks are plain C functions; HookEntry passes the registers on */
		h->h_Entry = (HOOKFUNC)HookEntry;
		h->h_SubEntry = (HOOKFUNC)GetTagData(ASOHOOK_Entry, 0, tags);
		if (FindTagItem(ASOHOOK_Subentry, tags))
			h->h_SubEntry = (HOOKFUNC)GetTagData(ASOHOOK_Subentry, 0, tags);
		h->h_Data = (APTR)GetTagData(ASOHOOK_Data, 0, tags);
		return h;
	}
	case ASOT_INTERRUPT: {
		ULONG size = GetTagData(ASOINTR_Size, sizeof(struct Interrupt), tags);
		struct Interrupt *i = AllocVec(size, mflags);
		if (!i)
			return NULL;
		i->is_Node.ln_Type = NT_INTERRUPT;
		i->is_Code = (VOID (*)())GetTagData(ASOINTR_Code, 0, tags);
		i->is_Data = (APTR)GetTagData(ASOINTR_Data, 0, tags);
		return i;
	}
	case ASOT_LIST: {
		BOOL min = GetTagData(ASOLIST_Min, FALSE, tags);
		ULONG size = GetTagData(ASOLIST_Size, min ? sizeof(struct MinList) : sizeof(struct List), tags);
		struct List *l = AllocVec(size, mflags);
		if (!l)
			return NULL;
		NewList(l);
		if (!min)
			l->lh_Type = GetTagData(ASOLIST_Type, 0, tags);
		return l;
	}
	case ASOT_NODE: {
		BOOL min = GetTagData(ASONODE_Min, FALSE, tags);
		ULONG size = GetTagData(ASONODE_Size, min ? sizeof(struct MinNode) : sizeof(struct Node), tags);
		struct Node *n = AllocVec(size, mflags);
		if (!n)
			return NULL;
		if (!min) {
			n->ln_Type = GetTagData(ASONODE_Type, 0, tags);
			n->ln_Pri = GetTagData(ASONODE_Pri, 0, tags);
			n->ln_Name = (char *)GetTagData(ASONODE_Name, 0, tags);
		}
		return n;
	}
	case ASOT_PORT: {
		CONST_STRPTR name = (CONST_STRPTR)GetTagData(ASOPORT_Name, 0, tags);
		BOOL copy = name && GetTagData(ASOPORT_CopyName, FALSE, tags);
		ULONG size = GetTagData(ASOPORT_Size, sizeof(struct MsgPort), tags);
		struct MsgPort *mp;
		LONG sig = (LONG)GetTagData(ASOPORT_Signal, (ULONG)-1, tags);
		ULONG me;

		if (size < sizeof(struct MsgPort))
			size = sizeof(struct MsgPort);
		mp = hdr_alloc(size, copy ? strlen0(name) + 1 : 0, mflags);
		if (!mp)
			return NULL;
		mp->mp_Node.ln_Type = NT_MSGPORT;
		mp->mp_Node.ln_Pri = GetTagData(ASOPORT_Pri, 0, tags);
		mp->mp_Node.ln_Name = (char *)(copy ? copy_after(mp, size, name) : name);
		mp->mp_Flags = GetTagData(ASOPORT_Action, PA_SIGNAL, tags);
		/* never one library call inside another's arguments: GCC's inline
		 * calls keep the base in a6, and the inner call leaves its own there */
		me = (ULONG)FindTask(NULL);
		mp->mp_SigTask = (APTR)GetTagData(ASOPORT_Target, me, tags);
		if (GetTagData(ASOPORT_AllocSig, TRUE, tags) && mp->mp_Flags == PA_SIGNAL) {
			sig = AllocSignal(sig);
			if (sig < 0) {
				FreeVec(HDR(mp));
				return NULL;
			}
			HDR(mp)->ownsig = 1;
		}
		mp->mp_SigBit = sig < 0 ? 0 : sig;
		NewList(&mp->mp_MsgList);
		if (GetTagData(ASOPORT_Public, FALSE, tags) && name) {
			AddPort(mp);
			HDR(mp)->pub = 1;
		}
		return mp;
	}
	case ASOT_SEMAPHORE:
	case ASOT_MUTEX: {
		CONST_STRPTR name = (CONST_STRPTR)GetTagData(ASOSEM_Name, 0, tags);
		BOOL copy = name && GetTagData(ASOSEM_CopyName, FALSE, tags);
		ULONG size = GetTagData(ASOSEM_Size, sizeof(struct SignalSemaphore), tags);
		struct SignalSemaphore *ss;

		if (size < sizeof(struct SignalSemaphore))
			size = sizeof(struct SignalSemaphore);
		ss = hdr_alloc(size, copy ? strlen0(name) + 1 : 0, mflags);
		if (!ss)
			return NULL;
		InitSemaphore(ss);
		if (type == ASOT_SEMAPHORE) {
			ss->ss_Link.ln_Pri = GetTagData(ASOSEM_Pri, 0, tags);
			ss->ss_Link.ln_Name = (char *)(copy ? copy_after(ss, size, name) : name);
			if (GetTagData(ASOSEM_Public, FALSE, tags) && name) {
				AddSemaphore(ss);
				HDR(ss)->pub = 1;
			}
		}
		return ss;
	}
	case ASOT_TAGLIST: {
		ULONG n = GetTagData(ASOTAGS_Size, 1, tags);
		struct TagItem *t = AllocVec((n ? n : 1) * sizeof(struct TagItem), mflags);
		if (t)
			t[0].ti_Tag = TAG_DONE;
		return t;
	}
	case ASOT_MEMPOOL: {
		/* OS 4 hands back the pool, which Alloc/FreePooled take; so do we */
		ULONG pf = GetTagData(ASOPOOL_MFlags, MEMF_ANY, tags) & ~MEMF_OS4ONLY;
		ULONG puddle = GetTagData(ASOPOOL_Puddle, 8192, tags);
		ULONG thresh = GetTagData(ASOPOOL_Threshold, 4096, tags);
		struct os4c_ppool *p = NULL;
		APTR pool;

		if (GetTagData(ASOPOOL_Protected, FALSE, tags)) {
			p = AllocVec(sizeof(*p), MEMF_PUBLIC | MEMF_CLEAR);
			if (!p)
				return NULL;
			InitSemaphore(&p->lock);
		}
		pool = CreatePool(pf, puddle, thresh);
		if (p) {
			if (!pool) {
				FreeVec(p);
				return NULL;
			}
			p->pool = pool;
			Forbid();
			AddTail((struct List *)&ppools, (struct Node *)&p->node);
			Permit();
		}
		return pool;
	}
	case ASOT_MESSAGE: {
		ULONG size = GetTagData(ASOMSG_Size, sizeof(struct Message), tags);
		struct Message *m = AllocVec(size, mflags);
		if (!m)
			return NULL;
		m->mn_Node.ln_Type = NT_MESSAGE;
		m->mn_Node.ln_Name = (char *)GetTagData(ASOMSG_Name, 0, tags);
		m->mn_ReplyPort = (struct MsgPort *)GetTagData(ASOMSG_ReplyPort, 0, tags);
		m->mn_Length = GetTagData(ASOMSG_Length, size, tags);
		return m;
	}
	default:
		return NULL;   /* ASOT_DMAENTRY, ASOT_ITEMPOOL, ASOT_RMAP, ASOT_EXTMEM */
	}
}

APTR os4c_AllocSysObjectTags(ULONG type, ...)
{
	va_list ap;
	APTR r;
	va_start(ap, type);
	r = os4c_AllocSysObject(type, (struct TagItem *)ap);
	va_end(ap);
	return r;
}

VOID os4c_FreeSysObject(ULONG type, APTR object)
{
	if (!object)
		return;
	switch (type) {
	case ASOT_PORT: {
		struct MsgPort *mp = object;
		if (HDR(mp)->pub)
			RemPort(mp);
		if (HDR(mp)->ownsig)
			FreeSignal(mp->mp_SigBit);
		FreeVec(HDR(mp));
		break;
	}
	case ASOT_SEMAPHORE:
	case ASOT_MUTEX:
		if (HDR(object)->pub)
			RemSemaphore((struct SignalSemaphore *)object);
		FreeVec(HDR(object));
		break;
	case ASOT_MEMPOOL:
		os4c_DeletePool(object);
		break;
	default:
		FreeVec(object);
		break;
	}
}

/* ---- lists ---- */
VOID os4c_NewList(struct List *list) { NewList(list); }
VOID os4c_NewMinList(struct MinList *list) { NewList((struct List *)list); }

struct Node *os4c_GetHead(struct List *list)
{
	return list && list->lh_Head->ln_Succ ? list->lh_Head : NULL;
}

struct Node *os4c_GetTail(struct List *list)
{
	return list && list->lh_TailPred->ln_Pred ? list->lh_TailPred : NULL;
}

struct Node *os4c_GetSucc(struct Node *node)
{
	return node && node->ln_Succ && node->ln_Succ->ln_Succ ? node->ln_Succ : NULL;
}

struct Node *os4c_GetPred(struct Node *node)
{
	return node && node->ln_Pred && node->ln_Pred->ln_Pred ? node->ln_Pred : NULL;
}

/* ---- mutexes: recursive, so a SignalSemaphore ---- */
VOID os4c_MutexObtain(APTR mutex) { ObtainSemaphore((struct SignalSemaphore *)mutex); }
BOOL os4c_MutexAttempt(APTR mutex) { return AttemptSemaphore((struct SignalSemaphore *)mutex) != 0; }
VOID os4c_MutexRelease(APTR mutex) { ReleaseSemaphore((struct SignalSemaphore *)mutex); }

/* ---- debug output to the serial port ---- */
VOID os4c_DebugPrintF(CONST_STRPTR format, ...)
{
	char buf[256];
	va_list ap;
	char *s;
	va_start(ap, format);
	os4c_VSNPrintf((STRPTR)buf, sizeof(buf), format, ap);
	va_end(ap);
	for (s = buf; *s; s++) {
		if (*s == '\n')
			RawPutChar('\r');
		RawPutChar(*s);
	}
}
