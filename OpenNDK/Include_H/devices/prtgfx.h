#ifndef DEVICES_PRTGFX_H
#define DEVICES_PRTGFX_H
/*
 * OpenNDK: the state printer.device hands a driver's Render() while
 * dumping a picture.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef GRAPHICS_RASTPORT_H
#include <graphics/rastport.h>
#endif
#ifndef DEVICES_PRTBASE_H
#include <devices/prtbase.h>
#endif

/* Indexes into a colorEntry, and their additive names */
#define PCMYELLOW	0
#define PCMMAGENTA	1
#define PCMCYAN		2
#define PCMBLACK	3
#define PCMBLUE		PCMYELLOW
#define PCMGREEN	PCMMAGENTA
#define PCMRED		PCMCYAN
#define PCMWHITE	PCMBLACK

union colorEntry {
	ULONG	colorLong;
	UBYTE	colorByte[4];
	BYTE	colorSByte[4];
};

struct PrtInfo {
	LONG		(*pi_render)(VOID);	/* the driver's Render() */
	struct RastPort	*pi_rp;			/* the source */
	struct RastPort	*pi_temprp;
	UWORD		*pi_RowBuf;
	UWORD		*pi_HamBuf;
	union colorEntry *pi_ColorMap;
	union colorEntry *pi_ColorInt;
	union colorEntry *pi_HamInt;
	union colorEntry *pi_Dest1Int;
	union colorEntry *pi_Dest2Int;
	UWORD		*pi_ScaleX;		/* how often each pixel repeats */
	UWORD		*pi_ScaleXAlt;
	UBYTE		*pi_dmatrix;		/* the dither matrix */
	UWORD		*pi_TopBuf;
	UWORD		*pi_BotBuf;

	UWORD		pi_RowBufSize;
	UWORD		pi_HamBufSize;
	UWORD		pi_ColorMapSize;
	UWORD		pi_ColorIntSize;
	UWORD		pi_HamIntSize;
	UWORD		pi_Dest1IntSize;
	UWORD		pi_Dest2IntSize;
	UWORD		pi_ScaleXSize;
	UWORD		pi_ScaleXAltSize;

	UWORD		pi_PrefsFlags;		/* the preferences' PrintFlags */
	ULONG		pi_special;		/* io_Special */
	UWORD		pi_xstart;
	UWORD		pi_ystart;
	UWORD		pi_width;		/* source size */
	UWORD		pi_height;
	ULONG		pi_pc;			/* destination size */
	ULONG		pi_pr;
	UWORD		pi_ymult;
	UWORD		pi_ymod;
	WORD		pi_ety;
	UWORD		pi_xpos;
	UWORD		pi_threshold;
	UWORD		pi_tempwidth;
	UWORD		pi_flags;
	/* V44 */
	UWORD		*pi_ReduceBuf;
	UWORD		pi_ReduceBufSize;
	struct Hook	*pi_SourceHook;
	ULONG		*pi_InvertHookBuf;
};

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef DEVICES_PRTBASE_H
#include <devices/prtbase.h>
#endif

#endif /* DEVICES_PRTGFX_H */
