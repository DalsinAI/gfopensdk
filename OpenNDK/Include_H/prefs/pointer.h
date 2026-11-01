#ifndef PREFS_POINTER_H
#define PREFS_POINTER_H
/*
 * OpenNDK: pointer preferences (the PNTR chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_PNTR		MAKE_ID('P','N','T','R')

struct PointerPrefs
{
    ULONG pp_Reserved[4];
    UWORD pp_Which;			/* WBP_ */
    UWORD pp_Size;
    UWORD pp_Width;
    UWORD pp_Height;
    UWORD pp_Depth;
    UWORD pp_YSize;
    UWORD pp_X, pp_Y;			/* the hot spot */
    /* the colours (RGBTable) and the planes follow */
};

/* pp_Which */
#define WBP_NORMAL	0
#define WBP_BUSY	1

/* One colour as the chunk stores it */
struct RGBTable
{
    UBYTE t_Red;
    UBYTE t_Green;
    UBYTE t_Blue;
};

#endif /* PREFS_POINTER_H */
