#ifndef PREFS_ICONTROL_H
#define PREFS_ICONTROL_H
/*
 * OpenNDK: Intuition control preferences (the ICTL chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

#define ID_ICTL		MAKE_ID('I','C','T','L')

struct IControlPrefs
{
    LONG ic_Reserved[4];
    UWORD ic_TimeOut;			/* verify time-out, in ticks */
    WORD ic_MetaDrag;			/* the qualifier that drags screens */
    ULONG ic_Flags;			/* ICF_ */
    UBYTE ic_WBtoFront;			/* the Amiga-key shortcuts */
    UBYTE ic_FrontToBack;
    UBYTE ic_ReqTrue;
    UBYTE ic_ReqFalse;
    UWORD ic_Version;			/* IC_CURRENTVERSION, with ICF_VERSIONED set */
    UWORD ic_VersionMagic;		/* private */
    UBYTE ic_HoverSlugishness:4;	/* how long the pointer rests first */
    UBYTE ic_HoverFlags:4;
    UBYTE ic_Pad;
    struct IBox *ic_GUIGeometry;	/* private */
};

/* ic_Flags */
#define ICB_COERCE_COLORS	0
#define ICB_COERCE_LACE		1
#define ICB_STRGAD_FILTER	2
#define ICB_MENUSNAP		3
#define ICB_MODEPROMOTE		4

#define ICF_COERCE_COLORS	(1 << 0)
#define ICF_COERCE_LACE		(1 << 1)
#define ICF_STRGAD_FILTER	(1 << 2)
#define ICF_MENUSNAP		(1 << 3)
#define ICF_MODEPROMOTE		(1 << 4)

#define ID_IEXC		MAKE_ID('I','E','X','C')

/* The IEXC chunk: a tag list, as long as the chunk */
struct IExceptionPrefs
{
    struct TagItem ie_Tags[0];
};

/* More names from the 3.2 interface */
#define ICB_CORRECT_RATIO	5
#define ICB_MORESIZEGADGETS	16
#define ICB_OFFSCRNWIN		15
#define ICB_RATIO_LSB		17
#define ICB_RATIO_MSB		18
#define ICB_VERSIONED		31
#define ICF_VERSIONED		0x80000000UL
#define IC_CURRENTVERSION	2
#define ICF_CORRECT_RATIO	32
#define ICF_HF_HOVERGADGETS	1
#define ICF_HF_REFLECTHOVER	2
#define ICF_MORESIZEGADGETS	0x10000
#define ICF_OFFSCRNWIN		0x8000
#define ICF_RATIO_1_1		0x40000
#define ICF_RATIO_8_9		0x60000
#define ICF_RATIO_9_7		0
#define ICF_RATIO_9_8		0x20000
#define ICF_RATIO_MASK		0x60000

#endif /* PREFS_ICONTROL_H */
