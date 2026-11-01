/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* ArgArrayInit, ArgArrayDone, ArgString and ArgInt: tool types from the
 * Shell's arguments or the program's icon, read the same way. */
#include "alib.h"
#include <dos/dos.h>
#include <workbench/startup.h>
#include <workbench/workbench.h>
#include <proto/dos.h>
/* a base of our own, so a program's IconBase is left alone */
#define ICON_BASE_NAME alib_IconBase
#define __NOLIBBASE__
#include <proto/icon.h>
#undef __NOLIBBASE__

static struct Library *alib_IconBase;
static struct DiskObject *arg_icon;
static STRPTR *arg_array;
static ULONG arg_size;

STRPTR *ArgArrayInit(LONG argc, CONST_STRPTR *argv)
{
	if (argc > 0) {
		LONG i;
		if (argc == 1)
			return NULL;
		arg_size = (ULONG)argc * sizeof(STRPTR);
		arg_array = (STRPTR *)AllocMem(arg_size, MEMF_CLEAR);
		if (!arg_array)
			return NULL;
		for (i = 1; i < argc; i++)
			arg_array[i - 1] = (STRPTR)argv[i];
		return arg_array;
	} else {
		struct WBStartup *wb = (struct WBStartup *)argv;
		BPTR old;
		if (!wb || wb->sm_NumArgs < 1)
			return NULL;
		alib_IconBase = OpenLibrary((CONST_STRPTR)"icon.library", 33);
		if (!alib_IconBase)
			return NULL;
		old = CurrentDir(wb->sm_ArgList[0].wa_Lock);
		arg_icon = GetDiskObject((CONST_STRPTR)wb->sm_ArgList[0].wa_Name);
		CurrentDir(old);
		return arg_icon ? (STRPTR *)arg_icon->do_ToolTypes : NULL;
	}
}

VOID ArgArrayDone(VOID)
{
	if (arg_array) {
		FreeMem(arg_array, arg_size);
		arg_array = NULL;
	}
	if (alib_IconBase) {
		if (arg_icon)
			FreeDiskObject(arg_icon);
		arg_icon = NULL;
		CloseLibrary(alib_IconBase);
		alib_IconBase = NULL;
	}
}

STRPTR ArgString(CONST_STRPTR *tt, CONST_STRPTR entry, CONST_STRPTR defaultString)
{
	STRPTR v;
	if (tt && alib_IconBase && (v = FindToolType((CONST STRPTR *)tt, entry)) != NULL)
		return v;
	if (tt && !alib_IconBase) {
		/* Shell arguments: NAME=value */
		for (; *tt; tt++) {
			CONST_STRPTR a = *tt, e = entry;
			while (*e && (*a | 0x20) == (*e | 0x20)) {
				a++;
				e++;
			}
			if (!*e && *a == '=')
				return (STRPTR)a + 1;
		}
	}
	return (STRPTR)defaultString;
}

LONG ArgInt(CONST_STRPTR *tt, CONST_STRPTR entry, LONG defaultVal)
{
	STRPTR s = ArgString(tt, entry, NULL);
	LONG v;
	if (s && StrToLong(s, &v) > 0)
		return v;
	return defaultVal;
}
