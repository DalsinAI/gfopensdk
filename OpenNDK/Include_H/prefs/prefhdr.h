#ifndef PREFS_PREFHDR_H
#define PREFS_PREFHDR_H
/*
 * OpenNDK: the header chunk every preferences file starts with.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_PREF		MAKE_ID('P','R','E','F')
#define ID_PRHD		MAKE_ID('P','R','H','D')

/* The PRHD chunk */
struct PrefHeader
{
    UBYTE ph_Version;			/* the format's version */
    UBYTE ph_Type;			/* 0 */
    ULONG ph_Flags;			/* 0 */
};

#endif /* PREFS_PREFHDR_H */
