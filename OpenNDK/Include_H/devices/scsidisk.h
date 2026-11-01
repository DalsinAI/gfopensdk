#ifndef DEVICES_SCSIDISK_H
#define DEVICES_SCSIDISK_H
/*
 * OpenNDK: HD_SCSICMD, the direct SCSI command many disk devices take.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#define HD_SCSICMD	28	/* io_Data: struct SCSICmd */

struct SCSICmd {
	UWORD	*scsi_Data;		/* word aligned */
	ULONG	scsi_Length;		/* even */
	ULONG	scsi_Actual;
	UBYTE	*scsi_Command;		/* the command block */
	UWORD	scsi_CmdLength;
	UWORD	scsi_CmdActual;
	UBYTE	scsi_Flags;		/* SCSIF_ */
	UBYTE	scsi_Status;		/* the target's status byte */
	UBYTE	*scsi_SenseData;	/* for autosense */
	UWORD	scsi_SenseLength;
	UWORD	scsi_SenseActual;
};

/* scsi_Flags */
#define SCSIF_WRITE		0	/* data out */
#define SCSIF_READ		1	/* data in */
#define SCSIB_READ_WRITE	0

#define SCSIF_NOSENSE		0
#define SCSIF_AUTOSENSE		2	/* request sense on check condition */
#define SCSIF_OLDAUTOSENSE	6	/* the 2.0 form */
#define SCSIB_AUTOSENSE		1
#define SCSIB_OLDAUTOSENSE	2

/* io_Error */
#define HFERR_SelfUnit		40	/* cannot address itself */
#define HFERR_DMA		41
#define HFERR_Phase		42
#define HFERR_Parity		43
#define HFERR_SelTimeout	44	/* the target did not answer */
#define HFERR_BadStatus		45
#define HFERR_NoBoard		50

#endif /* DEVICES_SCSIDISK_H */
