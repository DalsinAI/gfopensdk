#ifndef PREFS_WBPATTERN_H
#define PREFS_WBPATTERN_H
/*
 * OpenNDK: Workbench backdrop patterns and pictures (the PTRN chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_PTRN		MAKE_ID('P','T','R','N')

struct WBPatternPrefs
{
    ULONG wbp_Reserved[4];
    UWORD wbp_Which;			/* WBP_ */
    UWORD wbp_Flags;			/* WBPF_ */
    BYTE wbp_Revision;
    BYTE wbp_Depth;
    UWORD wbp_DataLength;		/* bytes of pattern or file name that follow */
};

/* wbp_Which */
#define WBP_ROOT	0
#define WBP_DRAWER	1
#define WBP_SCREEN	2

/* wbp_Flags */
#define WBPF_PATTERN	0x0001		/* a pattern, not a picture's name */
#define WBPF_NOREMAP	0x0010		/* use the picture's colours as they are */

/* V44: how a picture is dithered, how exactly its colours are kept, and
 * how it is placed */
#define WBPF_DITHER_MASK	0x0300
#define WBPF_DITHER_DEF		0x0000
#define WBPF_DITHER_BAD		0x0100
#define WBPF_DITHER_GOOD	0x0200
#define WBPF_DITHER_BEST	0x0300

#define WBPF_PRECISION_MASK	0x0C00
#define WBPF_PRECISION_DEF	0x0000
#define WBPF_PRECISION_ICON	0x0400
#define WBPF_PRECISION_IMAGE	0x0800
#define WBPF_PRECISION_EXACT	0x0C00

#define WBPF_PLACEMENT_MASK	0x3000
#define WBPF_PLACEMENT_TILE	0x0000
#define WBPF_PLACEMENT_CENTER	0x1000
#define WBPF_PLACEMENT_SCALE	0x2000

/* Pattern limits */
#define MAXDEPTH	3
#define DEFPATDEPTH	2
#define PAT_WIDTH	16
#define PAT_HEIGHT	16

/* More names from the 3.2 interface */
#define WBPF_ALIGNMENT_LEFTTOP	0x4000
#define WBPF_ALIGNMENT_MASK	0xC000
#define WBPF_ALIGNMENT_MIDDLE	0
#define WBPF_ALIGNMENT_RIGHTBOTTOM	0x8000
#define WBPF_PLACEMENT_SCALEGOOD	0x3000

#endif /* PREFS_WBPATTERN_H */
