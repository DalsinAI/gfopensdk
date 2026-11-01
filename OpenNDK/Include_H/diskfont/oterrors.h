#ifndef DISKFONT_OTERRORS_H
#define DISKFONT_OTERRORS_H
/*
 * OpenNDK: the error codes outline font engines return.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#define OTERR_Failure		-1	/* failed, for no reason given */
#define OTERR_Success		0
#define OTERR_BadTag		1	/* a tag the call does not take */
#define OTERR_UnknownTag	2	/* a tag the engine does not know */
#define OTERR_BadData		3	/* a tag's value is out of range */
#define OTERR_NoMemory		4
#define OTERR_NoFace		5	/* no typeface is set */
#define OTERR_BadFace		6	/* the typeface could not be read */
#define OTERR_NoGlyph		7	/* no glyph is set */
#define OTERR_BadGlyph		8	/* the glyph could not be made */
#define OTERR_NoShear		9	/* shear out of range */
#define OTERR_NoRotate		10	/* rotation out of range */
#define OTERR_TooSmall		11	/* the glyph is too small to render */
#define OTERR_UnknownGlyph	12	/* the face has no such glyph */

#endif /* DISKFONT_OTERRORS_H */
