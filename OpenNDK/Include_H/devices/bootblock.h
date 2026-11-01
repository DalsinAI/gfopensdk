#ifndef DEVICES_BOOTBLOCK_H
#define DEVICES_BOOTBLOCK_H
/*
 * OpenNDK: the floppy boot block's header.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* The first bytes of a bootable disk; boot code follows */
struct BootBlock {
	UBYTE	bb_id[4];	/* BBID_ */
	LONG	bb_chksum;
	LONG	bb_dosblock;	/* the root block */
};

#define BOOTSECTS	2	/* sectors the boot block occupies */

#define BBID_DOS	{ 'D', 'O', 'S', '\0' }
#define BBID_KICK	{ 'K', 'I', 'C', 'K' }

#define BBNAME_DOS	(0x444F5300L)	/* DOS\0 */
#define BBNAME_KICK	(0x4B49434BL)	/* KICK */

#endif /* DEVICES_BOOTBLOCK_H */
