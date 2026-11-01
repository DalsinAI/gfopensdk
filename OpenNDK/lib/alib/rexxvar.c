/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* CheckRexxMsg, GetRexxVar and SetRexxVar: a host reads or sets a variable
 * of the ARexx program whose command message it holds (before it replies).
 * The work is rexxsyslib.library's: GetRexxVarFromMsg and
 * SetRexxVarFromMsg (V45, OS 3.2's and OpenRexx's), opened for each call,
 * so the program's own RexxSysBase is never needed or touched. C entry
 * only (arguments on the stack). */
#include "alib.h"
#include <rexx/storage.h>
#include <rexx/rxslib.h>
#include <rexx/errors.h>
#define __NOLIBBASE__
#include <proto/rexxsyslib.h>
#undef __NOLIBBASE__

/* ARexx's strings are at most 65535 bytes (a NexxStr's length is a UWORD) */
#define RV_LONGEST 65535
/* GetRexxVarFromMsg fills a buffer of 256 bytes: the value and its NUL */
#define RV_BUFFER 256

/* GetRexxVar's copy of the last value it read: the program's own data, so
 * each program (and each run of a -resident one) has its own */
static UBYTE rv_value[RV_BUFFER];

/* A message from an ARexx program, which the variable calls need: it is
 * named "REXX" (as rexxsyslib's own RexxMsgs are) and carries the
 * interpreter's environment and rexxsyslib's base. */
BOOL CheckRexxMsg(CONST struct RexxMsg *rexxmsg)
{
	const char *n;

	if (!rexxmsg || !rexxmsg->rm_TaskBlock || !rexxmsg->rm_LibBase)
		return FALSE;
	n = (const char *)rexxmsg->rm_Node.mn_Node.ln_Name;
	return (BOOL)(n && n[0] == 'R' && n[1] == 'E' && n[2] == 'X' && n[3] == 'X' && n[4] == 0);
}

static struct Library *rv_open(void)
{
	return OpenLibrary((CONST_STRPTR)RXSNAME, 45);
}

LONG GetRexxVar(struct RexxMsg *rexxmsg, CONST_STRPTR name, STRPTR *result)
{
	struct Library *rxs;
	LONG rc;

	if (result)
		*result = NULL;
	if (!CheckRexxMsg(rexxmsg) || !name)
		return ERR10_010;
	if (!(rxs = rv_open()))
		return ERR10_014;
	rc = __GetRexxVarFromMsg_base(rxs, name, rexxmsg, rv_value);
	CloseLibrary(rxs);
	if (rc == 0 && result)
		*result = (STRPTR)rv_value;
	return rc;
}

/* The value is length bytes, with or without a NUL after them: it is
 * copied with one, as SetRexxVarFromMsg takes it (so a value stops at its
 * first NUL). */
LONG SetRexxVar(struct RexxMsg *rexxmsg, CONST_STRPTR name, CONST_STRPTR value, LONG length)
{
	struct Library *rxs;
	UBYTE *copy;
	LONG rc;

	if (!CheckRexxMsg(rexxmsg) || !name || (!value && length > 0))
		return ERR10_010;
	if (length < 0 || length > RV_LONGEST)
		return ERR10_009;
	if (!(rxs = rv_open()))
		return ERR10_014;
	copy = (UBYTE *)AllocVec((ULONG)length + 1, MEMF_ANY);
	if (!copy) {
		CloseLibrary(rxs);
		return ERR10_003;
	}
	if (length > 0)
		CopyMem((CONST_APTR)value, copy, (ULONG)length);
	copy[length] = 0;
	rc = __SetRexxVarFromMsg_base(rxs, name, rexxmsg, copy);
	FreeVec(copy);
	CloseLibrary(rxs);
	return rc;
}
