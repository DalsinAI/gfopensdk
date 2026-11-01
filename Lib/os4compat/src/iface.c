/* Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Interfaces: GetInterface(), DropInterface(), opening a base on first use,
 * and the exec calls whose meaning differs on OS 4.
 */
#include "os4c_internal.h"
#include <stdlib.h>
#include <exec/execbase.h>
#include <proto/exec.h>

/* the interfaces whose base we opened, linked through Data.Link: no limit */
static struct MinList opened = { (struct MinNode *)&opened.mlh_Tail, NULL, (struct MinNode *)&opened.mlh_Head };
static int atexit_done;

static void close_bases(void)
{
	struct Node *n;
	while ((n = RemHead((struct List *)&opened)) != NULL) {
		struct Interface *i = (struct Interface *)n;   /* Data.Link comes first */
		if (i->Data.LibBase && (i->Data.Flags & OS4CF_WEOPENED))
			CloseLibrary(i->Data.LibBase);
		i->Data.LibBase = NULL;
		i->Data.Flags &= ~OS4CF_WEOPENED;
	}
}

static int ends_with(CONST_STRPTR s, CONST_STRPTR tail)
{
	ULONG a = 0, b = 0;
	while (s[a]) a++;
	while (tail[b]) b++;
	if (b > a)
		return 0;
	s += a - b;
	while (*tail)
		if (*s++ != *tail++)
			return 0;
	return 1;
}

struct Library *os4c_OpenBase(struct Interface *iface)
{
	struct Library *base = NULL;
	CONST_STRPTR name = iface->Data.LibName;

	if (!name)
		return NULL;
	if (ends_with(name, ".device")) {
		/* devices are always open by someone; take the base from the list */
		Forbid();
		base = (struct Library *)FindName(&SysBase->DeviceList, (STRPTR)name);
		Permit();
	} else if (ends_with(name, ".resource")) {
		base = (struct Library *)OpenResource((STRPTR)name);
	} else {
		base = OpenLibrary((STRPTR)name, 0);
		if (base) {
			iface->Data.Flags |= OS4CF_WEOPENED;
			AddTail((struct List *)&opened, &iface->Data.Link);
			if (!atexit_done) {
				atexit(close_bases);
				atexit_done = 1;
			}
		}
	}
	iface->Data.LibBase = base;
	return base;
}

ULONG os4c_IfaceObtain(void) { return 1; }
ULONG os4c_IfaceRelease(void) { return 0; }
VOID os4c_IfaceExpunge(void) { }
struct Interface *os4c_IfaceClone(void) { return NULL; }

static int same_name(CONST_STRPTR a, CONST_STRPTR b)
{
	for (; *a && *b; a++, b++) {
		UBYTE x = *a, y = *b;
		if (x >= 'A' && x <= 'Z') x += 32;
		if (y >= 'A' && y <= 'Z') y += 32;
		if (x != y)
			return 0;
	}
	return *a == *b;
}

struct Interface *os4c_GetInterface(struct Library *library, CONST_STRPTR name,
	ULONG version, struct TagItem *tags)
{
	struct Interface *const *r;
	(void)tags;

	/* every interface here is version 1; a newer one is not available */
	if (!library || !library->lib_Node.ln_Name || version > 1)
		return NULL;
	if (name && !same_name(name, "main"))
		return NULL;   /* only the main interface exists here */
	for (r = os4c_registry; *r; r++) {
		struct Interface *i = *r;
		if (i->Data.LibName && same_name(i->Data.LibName, library->lib_Node.ln_Name)) {
			if (i->Data.LibBase != library) {
				/* the program opened it itself: call through its base */
				i->Data.LibBase = library;
				i->Data.Flags &= ~OS4CF_WEOPENED;
			}
			i->Data.RefCount++;
			return i;
		}
	}
	return NULL;
}

VOID os4c_DropInterface(struct Interface *iface)
{
	if (iface && iface->Data.RefCount)
		iface->Data.RefCount--;
}

struct Library *os4c_OpenLibrary(CONST_STRPTR name, ULONG version)
{
	/* OS 4 libraries are version 50 and up; OS 3.2's are 47 */
	if (version >= 50)
		version = 0;
	return OpenLibrary((STRPTR)name, version);
}

APTR os4c_AllocVec(ULONG size, ULONG flags)
{
	return AllocVec(size, flags & ~MEMF_OS4ONLY);
}

APTR os4c_AllocMem(ULONG size, ULONG flags)
{
	return AllocMem(size, flags & ~MEMF_OS4ONLY);
}
