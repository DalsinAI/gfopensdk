#ifndef LIBRARIES_CONFIGVARS_H
#define LIBRARIES_CONFIGVARS_H
/*
 * OpenNDK: expansion.library's record of each configured board, and
 * the binding a driver receives.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef LIBRARIES_CONFIGREGS_H
#include <libraries/configregs.h>
#endif

struct ConfigDev {
	struct Node	cd_Node;
	UBYTE		cd_Flags;	/* CDF_ */
	UBYTE		cd_Pad;
	struct ExpansionRom cd_Rom;	/* the board's identity */
	APTR		cd_BoardAddr;	/* where it was placed */
	ULONG		cd_BoardSize;
	UWORD		cd_SlotAddr;	/* private */
	UWORD		cd_SlotSize;	/* private */
	APTR		cd_Driver;	/* the driver that claimed it */
	struct ConfigDev *cd_NextCD;	/* the next board on the same card */
	ULONG		cd_Unused[4];
};

#define CDB_SHUTUP	0	/* shut up */
#define CDB_CONFIGME	1	/* still wants a driver */
#define CDB_BADMEMORY	2	/* its memory failed a test */
#define CDB_PROCESSED	3	/* private */

#define CDF_SHUTUP	0x01
#define CDF_CONFIGME	0x02
#define CDF_BADMEMORY	0x04
#define CDF_PROCESSED	0x08

/* What a driver loaded by BindDrivers finds with GetCurrentBinding() */
struct CurrentBinding {
	struct ConfigDev *cb_ConfigDev;	/* the first board to drive */
	STRPTR	cb_FileName;		/* the driver's file */
	STRPTR	cb_ProductString;	/* its PRODUCT tool type */
	STRPTR	*cb_ToolTypes;		/* its icon's tool types */
};

#endif /* LIBRARIES_CONFIGVARS_H */
