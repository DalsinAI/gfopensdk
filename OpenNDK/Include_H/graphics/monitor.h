#ifndef GRAPHICS_MONITOR_H
#define GRAPHICS_MONITOR_H
/*
 * OpenNDK: monitor specifications and their standard timings.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif

#ifndef GRAPHICS_GFXNODES_H
#include <graphics/gfxnodes.h>
#endif

#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif
#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef GRAPHICS_VIEW_H
#include <graphics/view.h>
#endif

struct View;

struct MonitorSpec
{
    struct ExtendedNode ms_Node;
    UWORD     ms_Flags;
    LONG      ratioh;
    LONG      ratiov;
    UWORD     total_rows;
    UWORD     total_colorclocks;
    UWORD     DeniseMaxDisplayColumn;
    UWORD     BeamCon0;
    UWORD     min_row;
    struct SpecialMonitor *ms_Special;
    WORD      ms_OpenCount;
    /* the monitor's own calls, as the 3.2 interface declares them */
    LONG    (* __ASM__ ms_transform) __CLIB_PROTOTYPE((__REG__(a0, struct MonitorSpec *),
                __REG__(a1, Point *), __REG__(d0, UWORD), __REG__(a2, Point *)));
    LONG    (* __ASM__ ms_translate) __CLIB_PROTOTYPE((__REG__(a0, struct MonitorSpec *),
                __REG__(a1, Point *), __REG__(d0, UWORD), __REG__(a2, Point *)));
    LONG    (* __ASM__ ms_scale) __CLIB_PROTOTYPE((__REG__(a0, struct MonitorSpec *),
                __REG__(a1, Point *), __REG__(d0, UWORD), __REG__(a2, Point *)));
    UWORD     ms_xoffset;
    UWORD     ms_yoffset;
    struct Rectangle ms_LegalView;
    LONG    (* __ASM__ ms_maxoscan) __CLIB_PROTOTYPE((__REG__(a0, struct MonitorSpec *),
                __REG__(a1, struct Rectangle *), __REG__(d0, ULONG)));
    LONG    (* __ASM__ ms_videoscan) __CLIB_PROTOTYPE((__REG__(a0, struct MonitorSpec *),
                __REG__(a1, struct Rectangle *), __REG__(d0, ULONG)));
    UWORD     DeniseMinDisplayColumn;
    ULONG     DisplayCompatible;
    struct List DisplayInfoDataBase;
    struct SignalSemaphore DisplayInfoDataBaseSemaphore;
    LONG    (* __STDARGS__ ms_MrgCop) __CLIB_PROTOTYPE((struct View *));
    LONG    (* __STDARGS__ ms_LoadView) __CLIB_PROTOTYPE((struct View *));
    LONG    (* __ASM__ ms_KillView) __CLIB_PROTOTYPE((__REG__(a0, struct MonitorSpec *)));
};

#define TO_MONITOR	0
#define FROM_MONITOR	1
#define STANDARD_XOFFSET	9
#define STANDARD_YOFFSET	0

/* ms_Flags */
#define MSB_REQUEST_NTSC	0
#define MSB_REQUEST_PAL		1
#define MSB_REQUEST_SPECIAL	2
#define MSB_REQUEST_A2024	3
#define MSB_DOUBLE_SPRITES	4
#define MSF_REQUEST_NTSC	(1 << MSB_REQUEST_NTSC)
#define MSF_REQUEST_PAL		(1 << MSB_REQUEST_PAL)
#define MSF_REQUEST_SPECIAL	(1 << MSB_REQUEST_SPECIAL)
#define MSF_REQUEST_A2024	(1 << MSB_REQUEST_A2024)
#define MSF_DOUBLE_SPRITES	(1 << MSB_DOUBLE_SPRITES)

/* Monitor driver names */
#define DEFAULT_MONITOR_NAME	"default.monitor"
#define NTSC_MONITOR_NAME	"ntsc.monitor"
#define PAL_MONITOR_NAME	"pal.monitor"
#define VGA_MONITOR_NAME	"vga.monitor"
#define VGA70_MONITOR_NAME	"vga70.monitor"
#define STANDARD_MONITOR_MASK	(MSF_REQUEST_NTSC | MSF_REQUEST_PAL)

/* Standard NTSC and PAL timing */
#define STANDARD_NTSC_ROWS	262
#define STANDARD_PAL_ROWS	312
#define STANDARD_COLORCLOCKS	226
#define STANDARD_DENISE_MAX	455
#define STANDARD_DENISE_MIN	93
#define STANDARD_NTSC_BEAMCON	(0x0000)
#define STANDARD_PAL_BEAMCON	(0x0020)	/* BEAMCON0 PAL bit */

/* BEAMCON0 bits for programmed timing: VARVBLANK, LOLDIS, CSBLANK,
   VARVSYNC, VARHSYNC and VARBEAMEN */
#define SPECIAL_BEAMCON		0x1B8A

#define MIN_NTSC_ROW	21
#define MIN_PAL_ROW	29
#define STANDARD_VIEW_X	0x81
#define STANDARD_VIEW_Y	0x2C
#define STANDARD_HBSTRT	0x06
#define STANDARD_HSSTRT	0x0B
#define STANDARD_HSSTOP	0x1C
#define STANDARD_HBSTOP	0x2C
#define STANDARD_VBSTRT	0x0122
#define STANDARD_VSSTRT	0x02A6
#define STANDARD_VSSTOP	0x03AA
#define STANDARD_VBSTOP	0x1066

/* 31 kHz VGA */
#define VGA_COLORCLOCKS		(STANDARD_COLORCLOCKS / 2)
#define VGA_TOTAL_ROWS		(STANDARD_NTSC_ROWS * 2)
#define VGA_DENISE_MIN		59
#define MIN_VGA_ROW		29
#define VGA_HBSTRT		0x08
#define VGA_HSSTRT		0x0E
#define VGA_HSSTOP		0x1C
#define VGA_HBSTOP		0x1E
#define VGA_VBSTRT		0x0000
#define VGA_VSSTRT		0x0153
#define VGA_VSSTOP		0x0235
#define VGA_VBSTOP		0x0CCD

/* 70 Hz VGA */
#define VGA70_COLORCLOCKS	(STANDARD_COLORCLOCKS / 2)
#define VGA70_TOTAL_ROWS	449
#define VGA70_DENISE_MIN	59
#define MIN_VGA70_ROW		35
#define VGA70_HBSTRT		0x08
#define VGA70_HSSTRT		0x0E
#define VGA70_HSSTOP		0x1C
#define VGA70_HBSTOP		0x1E
#define VGA70_VBSTRT		0x0000
#define VGA70_VSSTRT		0x02A6
#define VGA70_VSSTOP		0x0388
#define VGA70_VBSTOP		0x0F73
#define VGA70_BEAMCON		0x1B88	/* VSYNCTRUE flipped */

/* Broadcast timing */
#define BROADCAST_HBSTRT	0x01
#define BROADCAST_HSSTRT	0x06
#define BROADCAST_HSSTOP	0x17
#define BROADCAST_HBSTOP	0x27
#define BROADCAST_VBSTRT	0x0000
#define BROADCAST_VSSTRT	0x02A6
#define BROADCAST_VSSTOP	0x054C
#define BROADCAST_VBSTOP	0x1C40
#define BROADCAST_BEAMCON	0x808	/* LOLDIS | CSBLANK */

/* ratioh and ratiov are fixed point with this many fraction bits */
#define RATIO_FIXEDPART		4
#define RATIO_UNITY		(1 << RATIO_FIXEDPART)

/* A start and stop position of one sync or blank signal */
struct AnalogSignalInterval
{
    UWORD asi_Start;
    UWORD asi_Stop;
};

struct SpecialMonitor
{
    struct ExtendedNode spm_Node;
    UWORD   spm_Flags;
    LONG  (* __STDARGS__ do_monitor) __CLIB_PROTOTYPE((struct MonitorSpec *));
    LONG  (* __STDARGS__ reserved1)();
    LONG  (* __STDARGS__ reserved2)();
    LONG  (* __STDARGS__ reserved3)();
    struct AnalogSignalInterval hblank;
    struct AnalogSignalInterval vblank;
    struct AnalogSignalInterval hsync;
    struct AnalogSignalInterval vsync;
};

/* More names from the 3.2 interface */
#define REQUEST_A2024		8
#define REQUEST_NTSC		1
#define REQUEST_PAL		2
#define REQUEST_SPECIAL		4

#endif /* GRAPHICS_MONITOR_H */
