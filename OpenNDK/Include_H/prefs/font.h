#ifndef PREFS_FONT_H
#define PREFS_FONT_H
/*
 * OpenNDK: font preferences (the FONT chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef GRAPHICS_TEXT_H
#include <graphics/text.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_FONT		MAKE_ID('F','O','N','T')

#define FONTNAMESIZE	(128)

struct FontPrefs
{
    LONG fp_Reserved[3];
    UWORD fp_Reserved2;
    UWORD fp_Type;			/* FP_ */
    UBYTE fp_FrontPen;
    UBYTE fp_BackPen;
    UBYTE fp_DrawMode;
    UBYTE fp_SpecialDrawMode;		/* the byte before fp_TextAttr (3.2) */
    struct TextAttr fp_TextAttr;
    BYTE fp_Name[FONTNAMESIZE];		/* fp_TextAttr.ta_Name points here */
};

/* fp_Type: which font */
#define FP_WBFONT	0
#define FP_SYSFONT	1
#define FP_SCREENFONT	2

#endif /* PREFS_FONT_H */
