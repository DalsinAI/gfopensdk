#ifndef RESOURCES_FILESYSRES_H
#define RESOURCES_FILESYSRES_H
/*
 * OpenNDK: FileSystem.resource: the file systems the system knows.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

#ifndef BPTR_DEFINED
#define BPTR_DEFINED
typedef long BPTR;
typedef long BSTR;
#endif

#define FSRNAME	"FileSystem.resource"

/* The resource itself: a node, not a library. */
struct FileSysResource {
	struct Node fsr_Node;
	char	*fsr_Creator;		/* who made the resource */
	struct List fsr_FileSysEntries;	/* struct FileSysEntry nodes */
};

/*
 * One file system. fse_PatchFlags has a bit for each field from fse_Type
 * on (bit 0 for fse_Type) that is copied into a mounted DeviceNode.
 */
struct FileSysEntry {
	struct Node fse_Node;	/* ln_Name: who added the entry */
	ULONG	fse_DosType;
	ULONG	fse_Version;	/* version << 16 | revision */
	ULONG	fse_PatchFlags;
	ULONG	fse_Type;
	APTR	fse_Task;
	BPTR	fse_Lock;
	BSTR	fse_Handler;
	ULONG	fse_StackSize;
	LONG	fse_Priority;
	BPTR	fse_Startup;
	BPTR	fse_SegList;
	BPTR	fse_GlobalVec;
};

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

#endif /* RESOURCES_FILESYSRES_H */
