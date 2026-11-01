#ifndef PREFS_PALETTE_H
#define PREFS_PALETTE_H
/*
 * OpenNDK: palette preferences: the pens and colours (the PALT chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_PALT		MAKE_ID('P','A','L','T')

struct PalettePrefs
{
    LONG pap_Reserved[4];
    UWORD pap_4ColorPens[32];		/* DrawInfo pens for 4-colour screens */
    UWORD pap_8ColorPens[32];		/* and for 8 and more */
    struct ColorSpec pap_Colors[32];	/* ended by ColorIndex -1 */
};

#endif /* PREFS_PALETTE_H */
