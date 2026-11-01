#ifndef GRAPHICS_DISPLAYINFO_H
#define GRAPHICS_DISPLAYINFO_H
/*
 * OpenNDK: the display database records GetDisplayInfoData() returns.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

#ifndef GRAPHICS_MONITOR_H
#include <graphics/monitor.h>
#endif

#ifndef GRAPHICS_MODEID_H
#include <graphics/modeid.h>
#endif

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* What FindDisplayInfo() returns */
typedef APTR DisplayInfoHandle;

/* GetDisplayInfoData() record types */
#define DTAG_DISP	0x80000000
#define DTAG_DIMS	0x80001000
#define DTAG_MNTR	0x80002000
#define DTAG_NAME	0x80003000
#define DTAG_VEC	0x80004000	/* private */

/* Every record starts with this */
struct QueryHeader
{
    ULONG StructID;	/* the DTAG_ type */
    ULONG DisplayID;
    ULONG SkipID;	/* TAG_SKIP */
    ULONG Length;	/* in 8-byte units */
};

struct DisplayInfo
{
    struct QueryHeader Header;
    UWORD NotAvailable;	/* 0 when the mode can be shown */
    ULONG PropertyFlags;	/* DIPF_ */
    Point Resolution;	/* ticks per pixel */
    UWORD PixelSpeed;	/* nanoseconds */
    UWORD NumStdSprites;
    UWORD PaletteRange;
    Point SpriteResolution;
    UBYTE pad[4];
    UBYTE RedBits;
    UBYTE GreenBits;
    UBYTE BlueBits;
    UBYTE pad2[5];
    ULONG reserved[2];
};

/* NotAvailable */
#define DI_AVAIL_NOCHIPS	0x0001
#define DI_AVAIL_NOMONITOR	0x0002
#define DI_AVAIL_NOTWITHGENLOCK	0x0004

/* PropertyFlags */
#define DIPF_IS_LACE		0x00000001
#define DIPF_IS_DUALPF		0x00000002
#define DIPF_IS_PF2PRI		0x00000004
#define DIPF_IS_HAM		0x00000008
#define DIPF_IS_ECS		0x00000010
#define DIPF_IS_AA		0x00010000
#define DIPF_IS_PAL		0x00000020
#define DIPF_IS_SPRITES		0x00000040
#define DIPF_IS_GENLOCK		0x00000080
#define DIPF_IS_WB		0x00000100
#define DIPF_IS_DRAGGABLE	0x00000200
#define DIPF_IS_PANELLED	0x00000400
#define DIPF_IS_BEAMSYNC	0x00000800
#define DIPF_IS_EXTRAHALFBRITE	0x00001000
#define DIPF_IS_SPRITES_ATT		0x00002000
#define DIPF_IS_SPRITES_CHNG_RES	0x00004000
#define DIPF_IS_SPRITES_BORDER		0x00008000
#define DIPF_IS_SCANDBL			0x00020000
#define DIPF_IS_SPRITES_CHNG_BASE	0x00040000
#define DIPF_IS_SPRITES_CHNG_PRI	0x00080000
#define DIPF_IS_DBUFFER			0x00100000
#define DIPF_IS_PROGBEAM		0x00200000
#define DIPF_IS_FOREIGN			0x80000000

struct DimensionInfo
{
    struct QueryHeader Header;
    UWORD MaxDepth;
    UWORD MinRasterWidth;
    UWORD MinRasterHeight;
    UWORD MaxRasterWidth;
    UWORD MaxRasterHeight;
    struct Rectangle Nominal;
    struct Rectangle MaxOScan;
    struct Rectangle VideoOScan;
    struct Rectangle TxtOScan;
    struct Rectangle StdOScan;
    UBYTE pad[14];
    ULONG reserved[2];
};

struct MonitorInfo
{
    struct QueryHeader  Header;
    struct MonitorSpec *Mspc;
    Point ViewPosition;
    Point ViewResolution;
    struct Rectangle ViewPositionRange;
    UWORD TotalRows;
    UWORD TotalColorClocks;
    UWORD MinRow;
    WORD  Compatibility;	/* MCOMPAT_ */
    UBYTE pad[32];
    Point MouseTicks;
    Point DefaultViewPosition;
    ULONG PreferredModeID;
    ULONG reserved[2];
};

/* Compatibility */
#define MCOMPAT_MIXED	0	/* shares the display with other monitors */
#define MCOMPAT_SELF	1	/* only with itself */
#define MCOMPAT_NOBODY	-1	/* only alone */

#define DISPLAYNAMELEN	32

struct NameInfo
{
    struct QueryHeader Header;
    UBYTE Name[DISPLAYNAMELEN];
    ULONG reserved[2];
};

/* Private */
struct VecInfo
{
    struct QueryHeader Header;
    APTR  Vec;
    APTR  Data;
    UWORD Type;
    UWORD pad[3];
    ULONG reserved[2];
};

/* BestModeIDA() tags */
#define BIDTAG_DIPFMustHave	0x80000001	/* DIPF_ bits the mode must have */
#define BIDTAG_DIPFMustNotHave	0x80000002
#define BIDTAG_ViewPort		0x80000003	/* match this ViewPort */
#define BIDTAG_NominalWidth	0x80000004
#define BIDTAG_NominalHeight	0x80000005
#define BIDTAG_DesiredWidth	0x80000006
#define BIDTAG_DesiredHeight	0x80000007
#define BIDTAG_Depth		0x80000008
#define BIDTAG_MonitorID	0x80000009
#define BIDTAG_SourceID		0x8000000A	/* start from this mode's properties */
#define BIDTAG_RedBits		0x8000000B
#define BIDTAG_BlueBits		0x8000000C
#define BIDTAG_GreenBits	0x8000000D
#define BIDTAG_GfxPrivate	0x8000000E	/* private */

#endif /* GRAPHICS_DISPLAYINFO_H */
