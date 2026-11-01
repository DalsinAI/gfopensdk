#ifndef GRAPHICS_SPRITE_H
#define GRAPHICS_SPRITE_H
/*
 * OpenNDK: hardware sprites, simple and extended.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#define SPRITE_ATTACHED	0x80

struct SimpleSprite
{
    UWORD *posctldata;	/* the sprite's control words and image */
    UWORD  height;
    UWORD  x, y;
    UWORD  num;		/* hardware sprite number */
};

/* What AllocSpriteDataA() returns */
struct ExtSprite
{
    struct SimpleSprite es_SimpleSprite;
    UWORD es_wordwidth;	/* graphics use only */
    UWORD es_flags;	/* graphics use only */
};

/* AllocSpriteDataA() tags */
#define SPRITEA_Width		0x81000000
#define SPRITEA_XReplication	0x81000002
#define SPRITEA_YReplication	0x81000004
#define SPRITEA_OutputHeight	0x81000006
#define SPRITEA_Attached	0x81000008
#define SPRITEA_OldDataFormat	0x8100000A

/* GetExtSpriteA() tags */
#define GSTAG_SPRITE_NUM	0x82000020
#define GSTAG_ATTACHED		0x82000022
#define GSTAG_SOFTSPRITE	0x82000024

/* ChangeExtSpriteA() tags */
#define GSTAG_SCANDOUBLED	0x83000000

#endif /* GRAPHICS_SPRITE_H */
