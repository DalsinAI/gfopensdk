#ifndef PREFS_WORKBENCH_H
#define PREFS_WORKBENCH_H
/*
 * OpenNDK: Workbench preferences (the WBNC chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_WBNC		MAKE_ID('W','B','N','C')
#define ID_WBHD		MAKE_ID('W','B','H','D')	/* a hidden device's name */
#define ID_WBTF		MAKE_ID('W','B','T','F')	/* the screen title's format */

struct WorkbenchPrefs
{
    /* V44 */
    ULONG wbp_DefaultStackSize;
    ULONG wbp_TypeRestartTime;		/* ticks before type-ahead restarts */
    ULONG wbp_IconPrecision;		/* PRECISION_ of graphics/view.h */
    struct Rectangle wbp_EmbossRect;
    BOOL wbp_Borderless;
    LONG wbp_MaxNameLength;
    BOOL wbp_NewIconsSupport;
    BOOL wbp_ColorIconSupport;
};

/* The longer form the Workbench prefs editor saves, the basic part first */
struct WorkbenchExtendedPrefs
{
    struct WorkbenchPrefs wbe_BasicPrefs;
    ULONG wbe_IconMemoryType;		/* MEMF_ for icon images */
    BOOL wbe_LockPens;
    BOOL wbe_DisableTitleBar;
    BOOL wbe_DisableVolumeGauge;
    UWORD wbe_TitleUpdateDelay;		/* seconds between title updates */
    ULONG wbe_CopyBufferSize;
    ULONG wbe_Flags;			/* private */
};

/* A hidden device's name (ID_WBHD) */
struct WorkbenchHiddenDevicePrefs
{
    TEXT	whdp_Name[0];			/* NUL-terminated, as long as the chunk */
};

/* The screen title's format (ID_WBTF) */
struct WorkbenchTitleFormatPrefs
{
    TEXT	wtfp_Format[0];		/* NUL-terminated, as long as the chunk */
};

#endif /* PREFS_WORKBENCH_H */
