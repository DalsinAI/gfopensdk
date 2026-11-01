#ifndef DISKFONT_DISKFONTTAG_H
#define DISKFONT_DISKFONTTAG_H
/*
 * OpenNDK: the tags of outline font engines and .otag files.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* Tag levels: 0 is the engine's, 1 must be in an .otag file, 2 may be,
 * 3 is engine specific. An indirect tag's data is an offset from the tag
 * itself in the loaded file. */
#define OT_Level0	TAG_USER
#define OT_Level1	(TAG_USER | 0x1000)
#define OT_Level2	(TAG_USER | 0x2000)
#define OT_Level3	(TAG_USER | 0x3000)
#define OT_Indirect	0x8000

/* Asking for and about glyphs (FIXED values are 16.16) */
#define OT_DeviceDPI	(OT_Level0 | 0x01)	/* x dpi << 16 | y dpi */
#define OT_DotSize	(OT_Level0 | 0x02)	/* dot size in percent, x << 16 | y */
#define OT_PointHeight	(OT_Level0 | 0x08)	/* FIXED points */
#define OT_SetFactor	(OT_Level0 | 0x09)	/* FIXED width over height */
#define OT_ShearSin	(OT_Level0 | 0x0a)
#define OT_ShearCos	(OT_Level0 | 0x0b)
#define OT_RotateSin	(OT_Level0 | 0x0c)
#define OT_RotateCos	(OT_Level0 | 0x0d)
#define OT_EmboldenX	(OT_Level0 | 0x0e)
#define OT_EmboldenY	(OT_Level0 | 0x0f)
#define OT_PointSize	(OT_Level0 | 0x10)	/* older: whole points */
#define OT_GlyphCode	(OT_Level0 | 0x11)
#define OT_GlyphCode2	(OT_Level0 | 0x12)	/* the next glyph, for kerning */
#define OT_GlyphWidth	(OT_Level0 | 0x13)
#define OT_OTagPath	(OT_Level0 | OT_Indirect | 0x14)
#define OT_OTagList	(OT_Level0 | OT_Indirect | 0x15)
#define OT_GlyphMap	(OT_Level0 | OT_Indirect | 0x20)	/* struct GlyphMap * */
#define OT_WidthList	(OT_Level0 | OT_Indirect | 0x21)	/* struct MinList * of GlyphWidthEntry */
#define OT_TextKernPair	(OT_Level0 | OT_Indirect | 0x22)
#define OT_DesignKernPair (OT_Level0 | OT_Indirect | 0x23)
#define OT_UnderLined	(OT_Level0 | 0x24)	/* OTUL_ */
#define OT_StrikeThrough (OT_Level0 | 0x25)

/* OT_UnderLined */
#define OTUL_None		0
#define OTUL_Solid		1
#define OTUL_Broken		2
#define OTUL_DoubleSolid	3
#define OTUL_DoubleBroken	4

/* .otag files */
#define OTSUFFIX	".otag"
#define OT_FileIdent	(OT_Level1 | 0x01)	/* the file's size, as a check */
#define OT_Engine	(OT_Level1 | OT_Indirect | 0x02)	/* the engine's name */
#define OTE_Bullet	"bullet"
#define OT_Family	(OT_Level1 | OT_Indirect | 0x03)
#define OT_BName	(OT_Level2 | OT_Indirect | 0x05)	/* the bold face's name */
#define OT_IName	(OT_Level2 | OT_Indirect | 0x06)	/* the italic's */
#define OT_BIName	(OT_Level2 | OT_Indirect | 0x07)	/* the bold italic's */
#define OT_SymbolSet	(OT_Level1 | 0x10)
#define OT_YSizeFactor	(OT_Level1 | 0x11)
#define OT_SpaceWidth	(OT_Level2 | 0x12)
#define OT_IsFixed	(OT_Level2 | 0x13)
#define OT_SerifFlag	(OT_Level1 | 0x14)
#define OT_StemWeight	(OT_Level1 | 0x15)	/* OTS_ weights */
#define OT_SlantStyle	(OT_Level1 | 0x16)	/* OTS_ slants */
#define OT_HorizStyle	(OT_Level1 | 0x17)	/* OTH_ */
#define OT_SpaceFactor	(OT_Level2 | 0x18)
#define OT_InhibitAlgoStyle (OT_Level2 | 0x19)	/* FSF_ styles not to fake */
#define OT_AvailSizes	(OT_Level1 | OT_Indirect | 0x20)	/* UWORD count, then sizes */
#define OT_MAXAVAILSIZES 20
#define OT_SpecCount	(OT_Level1 | 0x100)	/* how many engine specs follow */
#define OT_Spec		(OT_Level1 | 0x100)
#define OT_Spec1	(OT_Level1 | 0x101)	/* the first; OT_Indirect when a pointer */

/* OT_StemWeight */
#define OTS_UltraThin	8
#define OTS_ExtraThin	24
#define OTS_Thin	40
#define OTS_ExtraLight	56
#define OTS_Light	72
#define OTS_DemiLight	88
#define OTS_SemiLight	104
#define OTS_Book	120
#define OTS_Medium	136
#define OTS_SemiBold	152
#define OTS_DemiBold	168
#define OTS_Bold	184
#define OTS_ExtraBold	200
#define OTS_Black	216
#define OTS_ExtraBlack	232
#define OTS_UltraBlack	248

/* OT_SlantStyle */
#define OTS_Upright	0
#define OTS_Italic	1
#define OTS_LeftItalic	2

/* OT_HorizStyle */
#define OTH_UltraCompressed	16
#define OTH_ExtraCompressed	48
#define OTH_Compressed		80
#define OTH_Condensed		112
#define OTH_Normal		144
#define OTH_SemiExpanded	176
#define OTH_Expanded		208
#define OTH_ExtraExpanded	240

/* More names from the 3.2 interface */
#define DFCTRL_SORT_ASC		1
#define DFCTRL_SORT_DES		(-1)
#define OT_BMSize		0x80002021UL
#define OT_BaseLine		0x8000801CUL
#define OT_GlyphCode2_32	0x80000019UL
#define OT_GlyphCode_32		0x80000018UL
#define OT_GlyphMap8Bit		0x8000801AUL
#define OT_GlyphName		0x80008026UL
#define OT_HasGlyphs		0x8000801FUL
#define OT_IsUnderlined		0x80002023UL
#define OT_MemPtr		0x80008016UL
#define OT_MemSize		0x80000017UL
#define OT_NumGlyphs		0x8000801DUL
#define OT_NumKernPairs		0x8000801EUL
#define OT_RName		0x8000A009UL
#define OT_WidthList32		0x8000801BUL
#define OUTL_DoubleBroken	4

#endif /* DISKFONT_DISKFONTTAG_H */
