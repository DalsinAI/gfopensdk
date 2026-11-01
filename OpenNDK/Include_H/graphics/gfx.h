#ifndef GRAPHICS_GFX_H
#define GRAPHICS_GFX_H
/*
 * OpenNDK: graphics.library's basic shapes: rectangles, points and bitmaps.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* Set and clear forms of a custom-chip control word */
#define BITSET	0x8000
#define BITCLR	0

/* Chip RAM addresses need no translation on any shipped Agnus */
#define AGNUS
#define TOBB(a)	((long)(a))

/* A rectangle in 16-bit and 32-bit coordinates; Max is inclusive */
struct Rectangle
{
    WORD MinX, MinY;
    WORD MaxX, MaxY;
};

struct Rect32
{
    LONG MinX, MinY;
    LONG MaxX, MaxY;
};

typedef struct tPoint
{
    WORD x, y;
} Point;

/* One bitplane */
typedef UBYTE *PLANEPTR;

struct BitMap
{
    UWORD    BytesPerRow;
    UWORD    Rows;
    UBYTE    Flags;
    UBYTE    Depth;
    UWORD    pad;
    PLANEPTR Planes[8];
};

/* Bytes in one plane of w by h pixels, rows padded to whole words */
#define RASSIZE(w, h)	((ULONG)(h) * ((((ULONG)(w) + 15) >> 3) & 0xFFFE))

/* AllocBitMap() flags */
#define BMB_CLEAR	0
#define BMB_DISPLAYABLE	1
#define BMB_INTERLEAVED	2
#define BMB_STANDARD	3
#define BMB_MINPLANES	4
#define BMB_SPECIALFMT	7	/* pixel format in the top byte (SHIFT_PIXFMT) */

#define BMF_CLEAR	(1L << BMB_CLEAR)
#define BMF_DISPLAYABLE	(1L << BMB_DISPLAYABLE)
#define BMF_INTERLEAVED	(1L << BMB_INTERLEAVED)
#define BMF_STANDARD	(1L << BMB_STANDARD)
#define BMF_MINPLANES	(1L << BMB_MINPLANES)
#define BMF_SPECIALFMT	(1L << BMB_SPECIALFMT)

#define SHIFT_PIXFMT(fmt)	(((ULONG)(fmt)) << 24UL)	/* spelt as CyberGraphX's and Picasso96's headers spell it, so either may follow */

/* GetBitMapAttr() attributes */
#define BMA_HEIGHT	0
#define BMA_DEPTH	4
#define BMA_WIDTH	8
#define BMA_FLAGS	12

/* More names from the 3.2 interface */
#define BMATags_Alignment	0x8000000FUL
#define BMATags_BitmapColors	0x80000029UL
#define BMATags_BitmapColors32	0x80000043UL
#define BMATags_BitmapErrorCode	0x8000002AUL
#define BMATags_BitmapInvisible	0x80000037UL
#define BMATags_Clear		0x80000003UL
#define BMATags_ConstantBytesPerRow	0x80000010UL
#define BMATags_Depth		0x80000001UL
#define BMATags_DisplayID	0x80000032UL
#define BMATags_Displayable	0x80000004UL
#define BMATags_Friend		0x80000000UL
#define BMATags_ModeHeight	0x8000000BUL
#define BMATags_ModeWidth	0x8000000AUL
#define BMATags_NoMemory	0x80000006UL
#define BMATags_NoSprite	0x80000007UL
#define BMATags_PixelFormat	0x80000002UL
#define BMATags_Private1	0x80000005UL
#define BMATags_Private2	0x80000008UL
#define BMATags_Private3	0x80000009UL
#define BMATags_Private4	0x80000012UL
#define BMATags_Private5	0x80000013UL
#define BMATags_Private6	0x80000014UL
#define BMATags_Private7	0x80000015UL
#define BMATags_RenderFunc	0x8000000CUL
#define BMATags_SaveFunc	0x8000000DUL
#define BMATags_UserData	0x8000000EUL
#define BMATags_UserPrivate	0x80000011UL
#define BMB_FRIENDISTAG		10
#define BMB_HIJACKED		7
#define BMB_INVALID		11
#define BMB_RTGCHECK		9
#define BMB_RTGTAGS		8
#define BMF_CHECKMASK		0xF80
#define BMF_CHECKVALUE		0x700
/* A bitmap whose flags carry the RTG tags */
#define BITMAPFLAGS_ARE_EXTENDED(f)	(((f) & BMF_CHECKMASK) == BMF_CHECKVALUE)
#define BMF_FRIENDISTAG		0x400
#define BMF_HIJACKED		128
#define BMF_INVALID		0x800
#define BMF_RTGCHECK		0x200
#define BMF_RTGTAGS		0x100

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* a BitMap with the extended layout: its flags field says so */
#define BITMAPFLAGS_ARE_EXTENDED(f)	(((f) & BMF_CHECKMASK) == BMF_CHECKVALUE)

#endif /* GRAPHICS_GFX_H */
