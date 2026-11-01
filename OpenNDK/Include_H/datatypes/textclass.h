#ifndef DATATYPES_TEXTCLASS_H
#define DATATYPES_TEXTCLASS_H
/*
 * OpenNDK: text.datatype's attributes, lines and IFF FTXT chunks.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef DATATYPES_DATATYPESCLASS_H
#include <datatypes/datatypesclass.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define TEXTDTCLASS	"text.datatype"

/* Attributes */
#define TDTA_Buffer	(DTA_Dummy + 300)	/* the text */
#define TDTA_BufferLen	(DTA_Dummy + 301)
#define TDTA_LineList	(DTA_Dummy + 302)	/* struct MinList * of struct Line */
#define TDTA_WordSelect	(DTA_Dummy + 303)	/* the word double-clicked */
#define TDTA_WordDelim	(DTA_Dummy + 304)	/* the characters between words */
#define TDTA_WordWrap	(DTA_Dummy + 305)

/* One run of text on a line */
struct Line {
	struct MinNode	ln_Link;
	STRPTR		ln_Text;
	ULONG		ln_TextLen;
	UWORD		ln_XOffset;	/* where it is drawn */
	UWORD		ln_YOffset;
	UWORD		ln_Width;
	UWORD		ln_Height;
	UWORD		ln_Flags;	/* LNF_ */
	BYTE		ln_FgPen;
	BYTE		ln_BgPen;
	ULONG		ln_Style;	/* FSF_ */
	APTR		ln_Data;	/* a link's or an object's data */
};

/* ln_Flags */
#define LNF_LF		(1L<<0)	/* the run ends its line */
#define LNF_LINK	(1L<<1)
#define LNF_OBJECT	(1L<<2)
#define LNF_SELECTED	(1L<<3)

/* FTXT chunks */
#define ID_FTXT	MAKE_ID('F','T','X','T')
#define ID_CHRS	MAKE_ID('C','H','R','S')

#endif /* DATATYPES_TEXTCLASS_H */
