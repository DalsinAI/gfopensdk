/* Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * An OS 4 style program, written as for OS 4.1, built for OS 3.2 with
 * os4compat. Each step prints PASS or FAIL, so it doubles as the kit's test
 * on a real instance:  HelloOS4 [drawer]
 */
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/utility.h>
#include <proto/intuition.h>

static const char version[] = "$VER: HelloOS4 0.1 (6.10.2026) The Open SDK os4compat";
static int fails;

static void check(int ok, CONST_STRPTR what)
{
	IDOS->Printf("%s %s\n", ok ? "PASS" : "FAIL", what);
	if (!ok)
		fails++;
}

int main(int argc, char **argv)
{
	CONST_STRPTR drawer = argc > 1 ? (CONST_STRPTR)argv[1] : (CONST_STRPTR)"SYS:";
	struct MsgPort *port;
	struct List *list;
	APTR mutex, ctx;
	char buf[64];
	STRPTR s;
	struct ExamineData *d;
	int count = 0;
	BPTR fh;
	(void)version;

	IDOS->Printf("HelloOS4: OS 4 calls on OS 3.2 through os4compat %ld.%ld\n",
		(LONG)OS4COMPAT_VERSION, (LONG)OS4COMPAT_REVISION);

	port = IExec->AllocSysObjectTags(ASOT_PORT, ASOPORT_Name, "HelloOS4.port", TAG_END);
	check(port && port->mp_SigBit != 0, "AllocSysObjectTags(ASOT_PORT)");
	IExec->FreeSysObject(ASOT_PORT, port);

	list = IExec->AllocSysObjectTags(ASOT_LIST, TAG_END);
	check(list && IExec->GetHead(list) == NULL, "ASOT_LIST and GetHead on an empty list");
	IExec->FreeSysObject(ASOT_LIST, list);

	mutex = IExec->AllocSysObject(ASOT_MUTEX, NULL);
	IExec->MutexObtain(mutex);
	IExec->MutexObtain(mutex);   /* recursive */
	IExec->MutexRelease(mutex);
	IExec->MutexRelease(mutex);
	check(mutex && IExec->MutexAttempt(mutex), "Mutexes");
	IExec->MutexRelease(mutex);
	IExec->FreeSysObject(ASOT_MUTEX, mutex);

	s = IExec->AllocVecTags(16, AVT_Type, MEMF_SHARED, AVT_ClearWithValue, 0x55, TAG_END);
	check(s && (UBYTE)s[15] == 0x55, "AllocVecTags(AVT_ClearWithValue)");
	IExec->FreeVec(s);

	IUtility->SNPrintf((STRPTR)buf, sizeof(buf), "%s=%ld %04lx", "answer", 42L, 0xbeefUL);
	check(IUtility->Stricmp((STRPTR)buf, (STRPTR)"ANSWER=42 beef") == 0, "SNPrintf");
	check(IUtility->Strlcpy((STRPTR)buf, (CONST_STRPTR)"truncated text", 6) == 14
		&& IUtility->Stricmp((STRPTR)buf, (STRPTR)"trunc") == 0, "Strlcpy");
	s = IUtility->ASPrintf("%ld+%ld", 2L, 2L);
	check(s && s[0] == '2' && s[2] == '2' && s[3] == 0, "ASPrintf");
	IExec->FreeVec(s);

	ctx = IDOS->ObtainDirContextTags(EX_StringNameInput, drawer, EX_DataFields, EXF_ALL, TAG_END);
	check(ctx != NULL, "ObtainDirContextTags");
	if (ctx) {
		while ((d = IDOS->ExamineDir(ctx)) != NULL) {
			if (count < 5)
				IDOS->Printf("  %-24s %s\n", d->Name, EXD_IS_DIRECTORY(d) ? "(dir)" : "");
			count++;
		}
		check(IDOS->IoErr() == ERROR_NO_MORE_ENTRIES && count > 0, "ExamineDir to the end");
		IDOS->ReleaseDirContext(ctx);
	}

	d = IDOS->ExamineObjectTags(EX_StringNameInput, "S:Startup-Sequence", TAG_END);
	check(d && EXD_IS_FILE(d) && d->FileSize > 0, "ExamineObjectTags on S:Startup-Sequence");
	fh = IDOS->FOpen("S:Startup-Sequence", MODE_OLDFILE, 4096);
	if (fh && d) {
		check(IDOS->GetFileSize(fh) == d->FileSize, "GetFileSize matches ExamineObject");
		check(IDOS->ChangeFilePosition(fh, 10, OFFSET_BEGINNING)
			&& IDOS->GetFilePosition(fh) == 10, "ChangeFilePosition and GetFilePosition");
	}
	if (fh)
		IDOS->FClose(fh);
	if (d)
		IDOS->FreeDosObject(DOS_EXAMINEDATA, d);

	{
		struct Library *lib = IExec->OpenLibrary("utility.library", 53);  /* an OS 4 version */
		struct UtilityIFace *iu = (struct UtilityIFace *)IExec->GetInterface(lib, "main", 1, NULL);
		check(lib && iu == IUtility, "OpenLibrary(53) and GetInterface");
		IExec->DropInterface((struct Interface *)iu);
		IExec->CloseLibrary(lib);
	}

	IDOS->Printf("%s: %ld failed\n", fails ? "FAIL" : "PASS", (LONG)fails);
	return fails ? RETURN_FAIL : RETURN_OK;
}
