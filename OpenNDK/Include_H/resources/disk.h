#ifndef RESOURCES_DISK_H
#define RESOURCES_DISK_H
/*
 * OpenNDK: disk.resource: sharing the floppy controller between drivers.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef EXEC_INTERRUPTS_H
#include <exec/interrupts.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif

/* A driver's request for the controller, given to GetUnit(). */
struct DiscResourceUnit {
	struct Message dru_Message;	/* replied when the driver gets it */
	struct Interrupt dru_DiscBlock;	/* disk block done */
	struct Interrupt dru_DiscSync;	/* sync word found */
	struct Interrupt dru_Index;	/* index pulse */
};

/* The resource's base. */
struct DiscResource {
	struct Library dr_Library;
	struct DiscResourceUnit *dr_Current;	/* the controller's owner */
	UBYTE	dr_Flags;
	UBYTE	dr_UnitInit;		/* private */
	struct Library *dr_SysLib;
	struct Library *dr_CiaResource;
	ULONG	dr_UnitID[4];
	struct List dr_Waiting;		/* requests waiting their turn */
	struct Interrupt dr_DiscBlock;
	struct Interrupt dr_DiscSync;
	struct Interrupt dr_Index;
	struct Task *dr_CurrTask;
};

/* dr_Flags */
#define DRB_ALLOC0	0
#define DRB_ALLOC1	1
#define DRB_ALLOC2	2
#define DRB_ALLOC3	3
#define DRB_ACTIVE	7

#define DRF_ALLOC0	(1<<0)
#define DRF_ALLOC1	(1<<1)
#define DRF_ALLOC2	(1<<2)
#define DRF_ALLOC3	(1<<3)
#define DRF_ACTIVE	(1<<7)

/* dsklen bit that keeps disk DMA off */
#define DSKDMAOFF	0x4000

#define DISKNAME	"disk.resource"

/* Vector offsets of the calls */
#define DR_ALLOCUNIT	(LIB_BASE - 0 * LIB_VECTSIZE)
#define DR_FREEUNIT	(LIB_BASE - 1 * LIB_VECTSIZE)
#define DR_GETUNIT	(LIB_BASE - 2 * LIB_VECTSIZE)
#define DR_GIVEUNIT	(LIB_BASE - 3 * LIB_VECTSIZE)
#define DR_GETUNITID	(LIB_BASE - 4 * LIB_VECTSIZE)
#define DR_READUNITID	(LIB_BASE - 5 * LIB_VECTSIZE)

#define DR_LASTCOMM	(DR_READUNITID)

/* Drive types GetUnitID() returns */
#define DRT_AMIGA	(0x00000000)
#define DRT_37422D2S	(0x55555555)
#define DRT_EMPTY	(0xFFFFFFFF)
#define DRT_150RPM	(0xAAAAAAAA)

/* More names from the 3.2 interface */
#define DRB_DETECT0		4
#define DRF_DETECT0		16

#endif /* RESOURCES_DISK_H */
