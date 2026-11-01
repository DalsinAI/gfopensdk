#ifndef DISKFONT_DISKFONT_H
#define DISKFONT_DISKFONT_H
/*
 * OpenNDK: diskfont.library's files, lists, outline fonts and tags.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef GRAPHICS_TEXT_H
#include <graphics/text.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef DISKFONT_GLYPH_H
#include <diskfont/glyph.h>
#endif

#ifndef BPTR_DEFINED
#define BPTR_DEFINED
typedef long BPTR;
typedef long BSTR;
#endif

#define MAXFONTPATH	256	/* a font's path in its contents file, with the NUL */

/* One size in a .font file (FCH_ID) */
struct FontContents {
	TEXT	fc_FileName[MAXFONTPATH];
	UWORD	fc_YSize;
	UBYTE	fc_Style;
	UBYTE	fc_Flags;
};

/* One size in a .font file with tags (TFCH_ID, OFCH_ID); the tags sit
 * at the end of tfc_FileName */
struct TFontContents {
	TEXT	tfc_FileName[MAXFONTPATH-2];
	UWORD	tfc_TagCount;	/* tags, with the TAG_DONE */
	UWORD	tfc_YSize;
	UBYTE	tfc_Style;
	UBYTE	tfc_Flags;
};

#define FCH_ID	0x0f00	/* FontContents follow */
#define TFCH_ID	0x0f02	/* TFontContents follow */
#define OFCH_ID	0x0f03	/* TFontContents follow, and an .otag goes with it */

/* The head of a .font file */
struct FontContentsHeader {
	UWORD	fch_FileID;	/* FCH_ID, TFCH_ID or OFCH_ID */
	UWORD	fch_NumEntries;
	/* the entries follow */
};

#define DFH_ID		0x0f80
#define MAXFONTNAME	32	/* a font's name, with the NUL */

/* The start of a loaded font file's first hunk */
struct DiskFontHeader {
	struct Node	dfh_DF;		/* on diskfont.library's list */
	UWORD		dfh_FileID;	/* DFH_ID */
	UWORD		dfh_Revision;
	BPTR		dfh_Segment;	/* the font's seglist */
	TEXT	dfh_Name[MAXFONTNAME];
	struct TextFont	dfh_TF;
};

/* In the file, a tagged font keeps its tags where the seglist goes */
#define dfh_TagList	dfh_Segment

/* AvailFonts() flags, and af_Type */
#define AFB_MEMORY	0
#define AFF_MEMORY	0x0001
#define AFB_DISK	1
#define AFF_DISK	0x0002
#define AFB_SCALED	2
#define AFF_SCALED	0x0004
#define AFB_BITMAP	3
#define AFF_BITMAP	0x0008
#define AFB_OTAG	4
#define AFF_OTAG	0x0010
#define AFB_TYPE	6
#define AFF_TYPE	0x0040
#define AFB_TAGGED	16
#define AFF_TAGGED	0x10000L

/* AvailFonts()'s buffer: a header, then one of these per font */
struct AvailFonts {
	UWORD		af_Type;	/* AFF_MEMORY, AFF_DISK... */
	struct TextAttr	af_Attr;
};

struct TAvailFonts {
	UWORD		taf_Type;
	struct TTextAttr taf_Attr;
};

struct AvailFontsHeader {
	UWORD	afh_NumEntries;
	/* the entries follow */
};

/* An engine opened through diskfont.library's E calls */
struct EGlyphEngine {
	APTR			ege_Reserved;
	struct Library		*ege_BulletBase;	/* the engine library */
	struct GlyphEngine	*ege_GlyphEngine;
};

/* An outline font, from OpenOutlineFont() */
struct OutlineFont {
	STRPTR			olf_OTagPath;	/* the .otag file */
	struct TagItem		*olf_OTagList;	/* its tags, loaded */
	STRPTR			olf_EngineName;
	STRPTR			olf_LibraryName;
	struct EGlyphEngine	olf_EEngine;
	APTR			olf_Reserved;
	APTR			olf_UserData;	/* the caller's */
};

/* OpenOutlineFont() flags */
#define OFB_OPEN	0
#define OFF_OPEN	(1L<<OFB_OPEN)	/* open the engine too */

/* SetDiskFontCtrlA() and GetDiskFontCtrl() tags */
#define DFCTRL_BASE		(TAG_USER + 0x0B000000)
#define DFCTRL_XDPI		(DFCTRL_BASE + 1)
#define DFCTRL_YDPI		(DFCTRL_BASE + 2)
#define DFCTRL_XDOTP		(DFCTRL_BASE + 3)
#define DFCTRL_YDOTP		(DFCTRL_BASE + 4)
#define DFCTRL_CACHE		(DFCTRL_BASE + 5)
#define DFCTRL_SORTMODE		(DFCTRL_BASE + 6)
#define DFCTRL_CACHEFLUSH	(DFCTRL_BASE + 7)
#define DFCTRL_CHARSET		(DFCTRL_BASE + 8)

/* DFCTRL_SORTMODE */
#define DFCTRL_SORT_OFF		0
#define DFCTRL_SORT_ASCENDING	1
#define DFCTRL_SORT_DESCENDING	-1

/* ObtainCharsetInfo() tags */
#define DFCS_NUMBER	(DFCTRL_BASE + 0)
#define DFCS_NEXTNUMBER	(DFCTRL_BASE + 1)
#define DFCS_NAME	(DFCTRL_BASE + 2)
#define DFCS_MIMENAME	(DFCTRL_BASE + 3)
#define DFCS_MAPTABLE	(DFCTRL_BASE + 4)

/* More names from the 3.2 interface */
#define AFF_CHARSET		32
#define TA_CharSet		0x80000003UL

#endif /* DISKFONT_DISKFONT_H */
