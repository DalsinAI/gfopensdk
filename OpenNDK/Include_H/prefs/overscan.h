#ifndef PREFS_OVERSCAN_H
#define PREFS_OVERSCAN_H
/*
 * OpenNDK: overscan preferences (the OSCN chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_OSCN		MAKE_ID('O','S','C','N')

#define OSCAN_MAGIC	0xFEDCBA89

struct OverscanPrefs
{
    ULONG os_Reserved;
    ULONG os_Magic;			/* OSCAN_MAGIC */
    UWORD os_HStart;
    UWORD os_HStop;
    UWORD os_VStart;
    UWORD os_VStop;
    ULONG os_DisplayID;
    Point os_ViewPos;
    Point os_Text;
    struct Rectangle os_Standard;
};

#endif /* PREFS_OVERSCAN_H */
