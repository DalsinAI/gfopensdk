#ifndef REACTION_REACTION_PREFS_H
#define REACTION_REACTION_PREFS_H
/*
 * OpenNDK: the ReAction preferences as the classes see them.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif
#ifndef GRAPHICS_TEXT_H
#include <graphics/text.h>
#endif

/* The name of the semaphore the preferences are published under */
#define RAPREFSSEMAPHORE	"REACTION-PREFS"

/* The preferences the ReAction classes read, under the semaphore */
struct UIPrefs
{
	struct SignalSemaphore cap_Semaphore;
	UWORD	cap_PrefsVersion;
	UWORD	cap_PrefsSize;
	UBYTE	cap_BevelType;		/* BVT_ */
	UWORD	cap_LayoutSpacing;
	BOOL	cap_3DLook;
	UWORD	cap_LabelPen;
	UBYTE	cap_LabelPlace;
	UBYTE	cap_3DLabel;
	ULONG	cap_Reserved1;
	BOOL	cap_SimpleRefresh;
	UBYTE	cap_Pattern[256];
	ULONG	cap_Reserved2;
	BOOL	cap_3DProp;
	UWORD	cap_Reserved3;
	UBYTE	cap_GlyphType;		/* GLT_ */
	UBYTE	cap_Reserved4;
	struct TextAttr *cap_FallbackAttr;
	struct TextAttr *cap_LabelAttr;
};

/* The extra bevel pens */
struct UIExtPens
{
	UWORD	extp_Version;
	LONG	extp_DarkPen;
	LONG	extp_LightPen;
};

/* More names from the 3.2 interface */
#define BVT_GT			0
#define BVT_THICK		2
#define BVT_THIN		1
#define BVT_XEN			3
#define BVT_XENTHIN		4
#define GLT_3D			2
#define GLT_FLAT		1
#define GLT_GT			0

#define RAPREFSSEMAPHORE	"REACTION-PREFS"
#define ClassActPrefs		UIPrefs

#endif /* REACTION_REACTION_PREFS_H */
