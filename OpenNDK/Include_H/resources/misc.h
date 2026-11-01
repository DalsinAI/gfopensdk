#ifndef RESOURCES_MISC_H
#define RESOURCES_MISC_H
/*
 * OpenNDK: misc.resource: ownership of the serial and parallel hardware.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif

/* Units for AllocMiscResource() */
#define MR_SERIALPORT	0
#define MR_SERIALBITS	1
#define MR_PARALLELPORT	2
#define MR_PARALLELBITS	3

#define NUMMRTYPES	4

/* The resource's base: each unit holds its owner's name, or 0. */
struct MiscResource {
	struct Library mr_Library;
	ULONG	mr_AllocArray[NUMMRTYPES];
};

/* Vector offsets of the calls */
#define MR_ALLOCMISCRESOURCE	(LIB_BASE)
/* The second value is the one the OS headers have always carried. */
#define MR_FREEMISCRESOURCE	(-12)

#define MISCNAME	"misc.resource"

#endif /* RESOURCES_MISC_H */
