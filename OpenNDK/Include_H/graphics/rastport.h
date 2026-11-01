#ifndef GRAPHICS_RASTPORT_H
#define GRAPHICS_RASTPORT_H
/*
 * OpenNDK: the RastPort, the drawing context every rendering call takes.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

/* Vertex buffer for the area-fill calls (InitArea) */
struct AreaInfo
{
    WORD *VctrTbl;		/* start of the vector table */
    WORD *VctrPtr;		/* next free vector */
    BYTE *FlagTbl;
    BYTE *FlagPtr;
    WORD  Count;		/* vectors used */
    WORD  MaxCount;
    WORD  FirstX, FirstY;
};

/* Chip RAM work space for area fills and Flood() */
struct TmpRas
{
    BYTE *RasPtr;
    LONG  Size;
};

/* The GEL system's state for one RastPort */
struct GelsInfo
{
    BYTE              sprRsrvd;	/* hardware sprites VSprites may not use */
    UBYTE             Flags;	/* system use */
    struct VSprite   *gelHead, *gelTail;
    WORD             *nextLine;
    WORD            **lastColor;
    struct collTable *collHandler;
    WORD              leftmost, rightmost, topmost, bottommost;
    APTR              firstBlissObj, lastBlissObj;	/* system use */
};

struct RastPort
{
    struct Layer    *Layer;
    struct BitMap   *BitMap;
    UWORD           *AreaPtrn;	/* area fill pattern */
    struct TmpRas   *TmpRas;
    struct AreaInfo *AreaInfo;
    struct GelsInfo *GelsInfo;
    UBYTE            Mask;	/* planes written */
    BYTE             FgPen;
    BYTE             BgPen;
    BYTE             AOlPen;	/* area outline pen */
    BYTE             DrawMode;
    BYTE             AreaPtSz;	/* log2 of the area pattern's height */
    BYTE             linpatcnt;
    BYTE             dummy;
    UWORD            Flags;
    UWORD            LinePtrn;
    WORD             cp_x, cp_y;	/* the pen's position */
    UBYTE            minterms[8];
    WORD             PenWidth;
    WORD             PenHeight;
    struct TextFont *Font;
    UBYTE            AlgoStyle;	/* styles made by the renderer */
    UBYTE            TxFlags;
    UWORD            TxHeight;
    UWORD            TxWidth;
    UWORD            TxBaseline;
    WORD             TxSpacing;
    APTR            *RP_User;
    ULONG            longreserved[2];
#ifndef GFX_RASTPORT_1_2
    UWORD            wordreserved[7];
    UBYTE            reserved[8];
#endif
};

/* DrawMode values */
#define JAM1		0	/* foreground only */
#define JAM2		1	/* foreground and background */
#define COMPLEMENT	2	/* invert what is drawn over */
#define INVERSVID	4	/* swap the roles of the pens */

/* Flags */
#define FRST_DOT	0x01	/* draw the first dot of a line */
#define ONE_DOT		0x02	/* one-pixel lines */
#define DBUFFER		0x04	/* double-buffered */
#define AREAOUTLINE	0x08	/* outline area fills */
#define NOCROSSFILL	0x20	/* complemented area fills skip crossings */

#endif /* GRAPHICS_RASTPORT_H */
