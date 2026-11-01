#ifndef LIBRARIES_EXPANSIONBASE_H
#define LIBRARIES_EXPANSIONBASE_H
/*
 * OpenNDK: expansion.library's base and the boot node list dos
 * mounts from.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif
#ifndef LIBRARIES_CONFIGVARS_H
#include <libraries/configvars.h>
#endif

/* A device to mount, on MountList; ln_Pri is its boot priority */
struct BootNode {
	struct Node	bn_Node;	/* ln_Type NT_BOOTNODE */
	UWORD		bn_Flags;
	APTR		bn_DeviceNode;	/* struct DeviceNode */
};

/* Only MountList and Flags are public */
struct ExpansionBase {
	struct Library	LibNode;
	UBYTE		Flags;		/* EBF_ */
	UBYTE		eb_Private01;
	ULONG		eb_Private02;
	ULONG		eb_Private03;
	struct CurrentBinding eb_Private04;
	struct List	eb_Private05;
	struct List	MountList;	/* struct BootNode */
};

/* Error codes some calls return */
#define EE_OK		0
#define EE_LASTBOARD	40	/* no more boards wanted config */
#define EE_NOEXPANSION	41	/* no space left for the board */
#define EE_NOMEMORY	42	/* out of memory */
#define EE_NOBOARD	43	/* no board answered */
#define EE_BADMEM	44	/* the board's memory failed */

/* Flags */
#define EBB_CLOGGED	0	/* a board could not be shut up */
#define EBF_CLOGGED	(1<<0)
#define EBB_SHORTMEM	1	/* the address space ran out */
#define EBF_SHORTMEM	(1<<1)
#define EBB_BADMEM	2	/* a memory board failed */
#define EBF_BADMEM	(1<<2)
#define EBB_DOSFLAG	3	/* dos's own */
#define EBF_DOSFLAG	(1<<3)
#define EBB_KICKBACK33	4	/* boot a V33 Kickstart from disk */
#define EBF_KICKBACK33	(1<<4)
#define EBB_KICKBACK36	5	/* boot a V36 Kickstart from disk */
#define EBF_KICKBACK36	(1<<5)
#define EBB_SILENTSTART	6	/* no boot-time display */
#define EBF_SILENTSTART	(1<<6)

/* More names from the 3.2 interface */
#define EBB_START_CC0		7
#define EBF_START_CC0		128

#endif /* LIBRARIES_EXPANSIONBASE_H */
