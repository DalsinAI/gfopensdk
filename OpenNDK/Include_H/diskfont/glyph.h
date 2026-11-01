#ifndef DISKFONT_GLYPH_H
#define DISKFONT_GLYPH_H
/*
 * OpenNDK: an outline font engine's handle and the glyphs it renders.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif

/* An engine's handle, from OpenEngine(); the engine's own data follows */
struct GlyphEngine {
	struct Library	*gle_Library;	/* the engine library */
	STRPTR	gle_Name;	/* its name, such as "bullet" */
	/* private fields follow */
};

/* 16.16 fixed point */
typedef LONG FIXED;

/* A rendered glyph, from OT_GlyphMap */
struct GlyphMap {
	UWORD	glm_BMModulo;	/* bytes a row of glm_BitMap */
	UWORD	glm_BMRows;	/* rows in glm_BitMap */
	UWORD	glm_BlackLeft;	/* the inked box within the bitmap */
	UWORD	glm_BlackTop;
	UWORD	glm_BlackWidth;
	UWORD	glm_BlackHeight;
	FIXED	glm_XOrigin;	/* the origin, from the bitmap's top left */
	FIXED	glm_YOrigin;
	WORD	glm_X0;		/* the origin in whole pixels */
	WORD	glm_Y0;
	WORD	glm_X1;		/* the origin plus the advance */
	WORD	glm_Y1;
	FIXED	glm_Width;	/* the advance, a fraction of the em */
	UBYTE	*glm_BitMap;
};

/* One entry of OT_WidthList's list */
struct GlyphWidthEntry {
	struct MinNode	gwe_Node;
	UWORD		gwe_Code;	/* the character */
	FIXED		gwe_Width;	/* its advance, a fraction of the em */
};

/* A glyph's width, for 32-bit character codes */
struct GlyphWidthEntry32 {
	struct MinNode	gwe32_Node;
	UWORD		gwe32_reserved;
	FIXED		gwe32_Width;	/* 16.16, in ems */
	ULONG		gwe32_Code;
};

#endif /* DISKFONT_GLYPH_H */
