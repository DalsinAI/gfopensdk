#ifndef LIBRARIES_MATHLIBRARY_H
#define LIBRARIES_MATHLIBRARY_H
/*
 * OpenNDK: the base the IEEE math libraries share.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif

struct MathIEEEBase {
	struct Library	MathIEEEBase_LibNode;
	UBYTE		MathIEEEBase_reserved[18];
	/* called as each task opens and closes the library, when set */
	LONG		(*MathIEEEBase_TaskOpenLib)(VOID);
	LONG		(*MathIEEEBase_TaskCloseLib)(VOID);
};

#endif /* LIBRARIES_MATHLIBRARY_H */
