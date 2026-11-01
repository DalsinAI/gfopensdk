#ifndef RESOURCES_BATTMEMBITSAMIGA_H
#define RESOURCES_BATTMEMBITSAMIGA_H
/*
 * OpenNDK: battery-backed memory bits the Amiga OS owns.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

/* Bit offsets and lengths, as passed to ReadBattMem() and WriteBattMem() */

/* Set means the bits below are not valid */
#define BATTMEM_AMIGA_AMNESIA_ADDR	0
#define BATTMEM_AMIGA_AMNESIA_LEN	1

/* SCSI selection timeout: 0 short, 1 long */
#define BATTMEM_SCSI_TIMEOUT_ADDR	1
#define BATTMEM_SCSI_TIMEOUT_LEN	1

/* Set to scan LUNs above 0 */
#define BATTMEM_SCSI_LUNS_ADDR		2
#define BATTMEM_SCSI_LUNS_LEN		1

#endif /* RESOURCES_BATTMEMBITSAMIGA_H */
