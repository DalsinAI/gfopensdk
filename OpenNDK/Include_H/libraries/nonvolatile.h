#ifndef LIBRARIES_NONVOLATILE_H
#define LIBRARIES_NONVOLATILE_H
/*
 * OpenNDK: nonvolatile.library's structures and codes.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif

/* GetNVInfo(): the storage, in tens of bytes */
struct NVInfo {
	ULONG	nvi_MaxStorage;
	ULONG	nvi_FreeStorage;
};

/* One item of GetNVList()'s list */
struct NVEntry {
	struct MinNode	nve_Node;
	STRPTR		nve_Name;
	ULONG		nve_Size;	/* in tens of bytes */
	ULONG		nve_Protection;	/* NVEF_ */
};

/* nve_Protection */
#define NVEB_DELETE	0
#define NVEB_APPNAME	31

#define NVEF_DELETE	(1<<NVEB_DELETE)
#define NVEF_APPNAME	(1UL<<NVEB_APPNAME)

/* StoreNV()'s errors */
#define NVERR_BADNAME	1
#define NVERR_WRITEPROT	2
#define NVERR_FAIL	3
#define NVERR_FATAL	4

/* The size of what GetCopyNV() returned, in bytes */
#define SizeNVData(DataPtr)	((((ULONG *)(DataPtr))[-1]) - 4)

#endif /* LIBRARIES_NONVOLATILE_H */
