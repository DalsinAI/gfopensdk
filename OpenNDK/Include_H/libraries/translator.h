#ifndef LIBRARIES_TRANSLATOR_H
#define LIBRARIES_TRANSLATOR_H
/*
 * OpenNDK: translator.library's error codes.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* Translate()'s negative answers */
#define TR_NotUsed	-1	/* not used */
#define TR_NoMem	-2	/* out of memory */
#define TR_MakeBad	-4	/* the rules could not be built */

#endif /* LIBRARIES_TRANSLATOR_H */
