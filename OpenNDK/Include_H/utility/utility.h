#ifndef UTILITY_UTILITY_H
#define UTILITY_UTILITY_H
/*
 * OpenNDK: utility.library's base.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif

#define UTILITYNAME	"utility.library"

struct UtilityBase {
	struct Library ub_LibNode;
	UBYTE	ub_Language;	/* the system's language */
	UBYTE	ub_Reserved;
};

#endif /* UTILITY_UTILITY_H */
