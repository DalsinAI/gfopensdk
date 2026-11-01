#ifndef PREFS_REACTION_H
#define PREFS_REACTION_H
/*
 * OpenNDK: the ReAction preferences (the RACT chunk).
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

struct ReactionPrefs
{
	UWORD	rp_BevelType;		/* BVT_ of reaction/reaction_prefs.h */
	UWORD	rp_GlyphType;		/* GLT_ */
	UWORD	rp_LayoutSpacing;
	BOOL	rp_3DProp;
	UWORD	rp_LabelPen;
	UWORD	rp_LabelPlace;
	BOOL	rp_3DLabel;
	BOOL	rp_SimpleRefresh;
	BOOL	rp_3DLook;
	struct TextAttr rp_FallbackAttr;
	struct TextAttr rp_LabelAttr;
	UBYTE	rp_FallbackName[128];	/* the fonts' names */
	UBYTE	rp_LabelName[128];
	UBYTE	rp_Pattern[256];	/* a backdrop pattern file */
};

/* More names from the 3.2 interface */
#define ID_RACT			0x52414354

#endif /* PREFS_REACTION_H */
