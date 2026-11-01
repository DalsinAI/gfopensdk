/* Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * dos calls OS 4 has and OS 3.2 has not: 64-bit file positions and sizes,
 * ExamineObject() and ExamineDir(), FOpen() and FClose().
 */
#include "os4c_internal.h"
#include <string.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <dos/stdio.h>
#include <proto/utility.h>

/* the 64-bit packets, answered by filesystems that know them */
#ifndef ACTION_CHANGE_FILE_POSITION64
#define ACTION_CHANGE_FILE_POSITION64 8001
#define ACTION_GET_FILE_POSITION64    8002
#define ACTION_GET_FILE_SIZE64        8004
#endif

#define FH(f) ((struct FileHandle *)BADDR(f))

BPTR os4c_FOpen(CONST_STRPTR name, LONG mode, LONG bufsize)
{
	BPTR fh = Open((STRPTR)name, mode);
	if (fh && bufsize > 0)
		SetVBuf(fh, NULL, BUF_FULL, bufsize);
	return fh;
}

LONG os4c_FClose(BPTR file)
{
	return file ? Close(file) : DOSFALSE;
}

LONG os4c_ChangeFilePosition(BPTR file, int64 position, LONG mode)
{
	if (!file)
		return DOSFALSE;
	if (position >= -0x7fffffffLL && position <= 0x7fffffffLL) {
		/* Seek() answers -1 for an error, but also for an old position of 4 GB - 1 */
		SetIoErr(0);
		if (Seek(file, (LONG)position, mode) == -1 && IoErr())
			return DOSFALSE;
		return DOSTRUE;
	}
	Flush(file);
	if (DoPkt(FH(file)->fh_Type, ACTION_CHANGE_FILE_POSITION64,
	          FH(file)->fh_Arg1, (LONG)&position, mode, 0, 0))
		return DOSTRUE;
	if (IoErr() == ERROR_ACTION_NOT_KNOWN)
		SetIoErr(ERROR_OBJECT_TOO_LARGE);
	return DOSFALSE;
}

int64 os4c_GetFilePosition(BPTR file)
{
	int64 pos = 0;
	LONG p;
	if (!file)
		return -1;
	Flush(file);
	if (DoPkt(FH(file)->fh_Type, ACTION_GET_FILE_POSITION64, FH(file)->fh_Arg1, (LONG)&pos, 0, 0, 0))
		return pos;
	SetIoErr(0);
	p = Seek(file, 0, OFFSET_CURRENT);
	if (p == -1 && IoErr())
		return -1;
	return (int64)(ULONG)p;
}

int64 os4c_GetFileSize(BPTR file)
{
	int64 size = 0;
	struct FileInfoBlock *fib;
	if (!file)
		return -1;
	Flush(file);   /* what is still in the buffer counts, as on OS 4 */
	if (DoPkt(FH(file)->fh_Type, ACTION_GET_FILE_SIZE64, FH(file)->fh_Arg1, (LONG)&size, 0, 0, 0))
		return size;
	fib = AllocDosObject(DOS_FIB, NULL);
	if (!fib)
		return -1;
	size = ExamineFH(file, fib) ? (int64)(ULONG)fib->fib_Size : -1;
	FreeDosObject(DOS_FIB, fib);
	return size;
}

/* ---- examining ---- */
static void copy_str(UBYTE *dst, CONST_STRPTR src, ULONG size)
{
	ULONG i = 0;
	if (src)
		for (; i + 1 < size && src[i]; i++)
			dst[i] = src[i];
	dst[i] = 0;
}

static void fill(struct ExamineData *d, struct FileInfoBlock *fib)
{
	ULONG p = fib->fib_Protection;
	d->StructSize = sizeof(*d);
	d->ObjectID = (uint64)(ULONG)fib->fib_DiskKey;
	d->Type = fib->fib_DirEntryType;
	d->FileSize = fib->fib_DirEntryType < 0 ? (int64)(ULONG)fib->fib_Size : -1;
	d->Date = fib->fib_Date;
	d->RawProtection = p;
	/* RWED are "set = not allowed" in FIBF_; OS 4 gives them as "set = allowed" */
	d->Protection = p ^ (FIBF_READ | FIBF_WRITE | FIBF_EXECUTE | FIBF_DELETE);
	d->OwnerUID = fib->fib_OwnerUID;
	d->OwnerGID = fib->fib_OwnerGID;
	copy_str(d->NameBuffer, (CONST_STRPTR)fib->fib_FileName, sizeof(d->NameBuffer));
	copy_str(d->CommentBuffer, (CONST_STRPTR)fib->fib_Comment, sizeof(d->CommentBuffer));
	d->LinkBuffer[0] = 0;
	d->Name = (STRPTR)d->NameBuffer;
	d->Comment = (STRPTR)d->CommentBuffer;
	d->Link = d->RawLink = (STRPTR)d->LinkBuffer;
}

struct ExamineData *os4c_ExamineObject(struct TagItem *tags)
{
	CONST_STRPTR name = (CONST_STRPTR)GetTagData(EX_StringNameInput, 0, tags);
	BPTR lock = (BPTR)GetTagData(EX_LockInput, 0, tags);
	BPTR fh = (BPTR)GetTagData(EX_FileHandleInput, 0, tags);
	struct FileInfoBlock *fib = AllocDosObject(DOS_FIB, NULL);
	struct ExamineData *d = NULL;
	BOOL ok = FALSE;
	BPTR own = 0;

	if (!fib)
		return NULL;
	if (name) {
		own = Lock((STRPTR)name, SHARED_LOCK);
		if (own)
			ok = Examine(own, fib);
	} else if (lock) {
		ok = Examine(lock, fib);
	} else if (fh) {
		ok = ExamineFH(fh, fib);
	} else {
		SetIoErr(ERROR_REQUIRED_ARG_MISSING);
	}
	if (ok && (d = AllocVec(sizeof(*d), MEMF_PUBLIC | MEMF_CLEAR)) != NULL) {
		fill(d, fib);
		if (EXD_IS_SOFTLINK(d) && own)
			ReadLink(((struct FileLock *)BADDR(own))->fl_Task, own, (STRPTR)name,
			         (STRPTR)d->LinkBuffer, sizeof(d->LinkBuffer));
	}
	if (own)
		UnLock(own);
	FreeDosObject(DOS_FIB, fib);
	return d;
}

struct ExamineData *os4c_ExamineObjectTags(Tag tag1, ...)
{
	return os4c_ExamineObject((struct TagItem *)&tag1);
}

struct os4c_dirctx
{
	BPTR lock;
	struct FileInfoBlock *fib;
	struct Hook *match;
	UBYTE *pattern;
	struct ExamineData data;
};

APTR os4c_ObtainDirContext(struct TagItem *tags)
{
	CONST_STRPTR name = (CONST_STRPTR)GetTagData(EX_StringNameInput, 0, tags);
	BPTR lock = (BPTR)GetTagData(EX_LockInput, 0, tags);
	CONST_STRPTR match = (CONST_STRPTR)GetTagData(EX_MatchString, 0, tags);
	struct os4c_dirctx *c = AllocVec(sizeof(*c), MEMF_PUBLIC | MEMF_CLEAR);

	if (!c)
		return NULL;
	c->match = (struct Hook *)GetTagData(EX_MatchFunc, 0, tags);
	c->lock = name ? Lock((STRPTR)name, SHARED_LOCK) : lock ? DupLock(lock) : 0;
	c->fib = AllocDosObject(DOS_FIB, NULL);
	if (match) {
		ULONG len = strlen((const char *)match) * 2 + 2;
		c->pattern = AllocVec(len, MEMF_PUBLIC);
		if (c->pattern && ParsePatternNoCase((STRPTR)match, c->pattern, len) < 0) {
			FreeVec(c->pattern);
			c->pattern = NULL;
		}
	}
	if (!c->lock || !c->fib || !Examine(c->lock, c->fib)
	    || c->fib->fib_DirEntryType <= 0 || (match && !c->pattern)) {
		if (c->lock && c->fib && c->fib->fib_DirEntryType <= 0)
			SetIoErr(ERROR_OBJECT_WRONG_TYPE);
		os4c_ReleaseDirContext(c);
		return NULL;
	}
	return c;
}

APTR os4c_ObtainDirContextTags(Tag tag1, ...)
{
	return os4c_ObtainDirContext((struct TagItem *)&tag1);
}

struct ExamineData *os4c_ExamineDir(APTR context)
{
	struct os4c_dirctx *c = context;
	if (!c)
		return NULL;
	while (ExNext(c->lock, c->fib)) {
		if (c->pattern && !MatchPatternNoCase(c->pattern, (STRPTR)c->fib->fib_FileName))
			continue;
		memset(&c->data, 0, sizeof(c->data));
		fill(&c->data, c->fib);
		if (EXD_IS_SOFTLINK(&c->data)) {
			/* the link's own filesystem reads it, relative to this directory */
			struct MsgPort *fs = ((struct FileLock *)BADDR(c->lock))->fl_Task;
			ReadLink(fs, c->lock, (STRPTR)c->data.NameBuffer,
			         (STRPTR)c->data.LinkBuffer, sizeof(c->data.LinkBuffer));
		}
		if (c->match && !CallHookPkt(c->match, &c->data, NULL))
			continue;
		return &c->data;
	}
	/* IoErr() is ERROR_NO_MORE_ENTRIES at the end, as on OS 4 */
	return NULL;
}

VOID os4c_ReleaseDirContext(APTR context)
{
	struct os4c_dirctx *c = context;
	if (!c)
		return;
	if (c->lock)
		UnLock(c->lock);
	if (c->fib)
		FreeDosObject(DOS_FIB, c->fib);
	if (c->pattern)
		FreeVec(c->pattern);
	FreeVec(c);
}

VOID os4c_FreeDosObject(ULONG type, APTR object)
{
	if (type == DOS_EXAMINEDATA)
		FreeVec(object);
	else
		FreeDosObject(type, object);
}
