#ifndef LIBRARIES_EXPANSION_H
#define LIBRARIES_EXPANSION_H
/*
 * OpenNDK: expansion.library's name and AddDosNode() flags.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#define EXPANSIONNAME	"expansion.library"

/* AddDosNode() and AddBootNode() flags */
#define ADNB_STARTPROC	0	/* start the handler at once */
#define ADNF_STARTPROC	(1<<ADNB_STARTPROC)

#endif /* LIBRARIES_EXPANSION_H */
