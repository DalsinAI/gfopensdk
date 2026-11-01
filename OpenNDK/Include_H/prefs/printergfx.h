#ifndef PREFS_PRINTERGFX_H
#define PREFS_PRINTERGFX_H
/*
 * OpenNDK: printer graphics preferences (the PGFX chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_PGFX		MAKE_ID('P','G','F','X')

struct PrinterGfxPrefs
{
    LONG pg_Reserved[4];
    UWORD pg_Aspect;			/* PA_ */
    UWORD pg_Shade;			/* PS_ */
    UWORD pg_Image;			/* PI_ */
    WORD pg_Threshold;
    UBYTE pg_ColorCorrect;		/* PCCF_ */
    UBYTE pg_Dimensions;		/* PD_ */
    UBYTE pg_Dithering;			/* PD_ */
    UWORD pg_GraphicFlags;		/* PGFF_ */
    UBYTE pg_PrintDensity;		/* 1 to 7 */
    UWORD pg_PrintMaxWidth;
    UWORD pg_PrintMaxHeight;
    UBYTE pg_PrintXOffset;
    UBYTE pg_PrintYOffset;
};

/* pg_Aspect */
#define PA_HORIZONTAL	0
#define PA_VERTICAL	1

/* pg_Shade */
#define PS_BW		0
#define PS_GREYSCALE	1
#define PS_COLOR	2
#define PS_GREY_SCALE2	3

/* pg_Image */
#define PI_POSITIVE	0
#define PI_NEGATIVE	1

/* pg_ColorCorrect */
#define PCCB_RED	1
#define PCCB_GREEN	2
#define PCCB_BLUE	3

#define PCCF_RED	(1 << 0)
#define PCCF_GREEN	(1 << 1)
#define PCCF_BLUE	(1 << 2)

/* pg_Dimensions */
#define PD_IGNORE	0
#define PD_BOUNDED	1
#define PD_ABSOLUTE	2
#define PD_PIXEL	3
#define PD_MULTIPLY	4

/* pg_Dithering */
#define PD_ORDERED	0
#define PD_HALFTONE	1
#define PD_FLOYD	2

/* pg_GraphicFlags */
#define PGFB_CENTER_IMAGE	0
#define PGFB_INTEGER_SCALING	1
#define PGFB_ANTI_ALIAS		2

#define PGFF_CENTER_IMAGE	(1 << 0)
#define PGFF_INTEGER_SCALING	(1 << 1)
#define PGFF_ANTI_ALIAS		(1 << 2)

#endif /* PREFS_PRINTERGFX_H */
