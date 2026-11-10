/* aroscompat_shmain: the main() of an AROS_SHn command (aros/shcommands.h):
 * its defaults, ReadArgs with its template (and its help for "?"), the
 * body, the arguments freed. MIT, Copyright (c) 2026 AmiCradle Team. */
#include <exec/types.h>
#include <exec/memory.h>
#include <dos/dos.h>
#include <dos/rdargs.h>
#include <dos/dosextens.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <aros/shcommands.h>

int aroscompat_shmain(const char *name, const char *tmpl, const char *help,
                      const IPTR *defaults, ULONG n, aroscompat_shbody body)
{
	IPTR *args;
	struct RDArgs *rda, *got;
	ULONG i, rc;
	args = (IPTR *)AllocVec(sizeof(IPTR) * (n ? n : 1), MEMF_CLEAR);
	rda = (struct RDArgs *)AllocDosObject(DOS_RDARGS, NULL);
	if (!args || !rda) {
		PrintFault(ERROR_NO_FREE_STORE, (CONST_STRPTR)name);
		if (rda) FreeDosObject(DOS_RDARGS, rda);
		if (args) FreeVec(args);
		return RETURN_FAIL;
	}
	for (i = 0; i < n; i++) args[i] = defaults[i];
	if (help && *help) rda->RDA_ExtHelp = (STRPTR)help;
	got = ReadArgs((CONST_STRPTR)tmpl, (LONG *)args, rda);
	if (!got) {
		PrintFault(IoErr(), (CONST_STRPTR)name);
		FreeDosObject(DOS_RDARGS, rda);
		FreeVec(args);
		return RETURN_FAIL;
	}
	rc = body(args, SysBase, DOSBase);
	FreeArgs(rda);
	FreeDosObject(DOS_RDARGS, rda);
	FreeVec(args);
	return (int)rc;
}
