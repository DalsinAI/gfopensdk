#ifndef GRAPHICS_GELS_H
#define GRAPHICS_GELS_H
/*
 * OpenNDK: the GEL system: VSprites, Bobs and animation objects.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* VSprite Flags the program sets */
#define SUSERFLAGS	0x00FF
#define VSPRITE		0x0001	/* a hardware sprite, not a Bob */
#define SAVEBACK	0x0002	/* save the background under a Bob */
#define OVERLAY		0x0004	/* draw only the Bob's set pixels */
#define MUSTDRAW	0x0008	/* draw even when sprites run out */

/* VSprite Flags the system sets */
#define BACKSAVED	0x0100
#define BOBUPDATE	0x0200
#define GELGONE		0x0400	/* wholly off the clip region */
#define VSOVERFLOW	0x0800	/* no sprite was free */

/* Bob Flags the program sets */
#define BUSERFLAGS	0x00FF
#define SAVEBOB		0x0001	/* leave an image behind when moved */
#define BOBISCOMP	0x0002	/* part of an AnimComp */

/* Bob Flags the system sets */
#define BWAITING	0x0100
#define BDRAWN		0x0200
#define BOBSAWAY	0x0400	/* remove at the next DrawGList() */
#define BOBNIX		0x0800	/* removed */
#define SAVEPRESERVE	0x1000
#define OUTSTEP		0x2000

/* Animation */
#define ANFRACSIZE	6	/* fraction bits of the AnimOb positions */
#define ANIMHALF	0x0020
#define RINGTRIGGER	0x0001

/* Room for the program's own data in each structure */
#ifndef VUserStuff
#define VUserStuff	SHORT
#endif

#ifndef BUserStuff
#define BUserStuff	SHORT
#endif

#ifndef AUserStuff
#define AUserStuff	SHORT
#endif

struct VSprite
{
    struct VSprite *NextVSprite;	/* the GEL list, kept sorted */
    struct VSprite *PrevVSprite;
    struct VSprite *DrawPath;	/* system use */
    struct VSprite *ClearPath;	/* system use */
    WORD            OldY, OldX;	/* system use */
    WORD            Flags;
    WORD            Y, X;
    WORD            Height;
    WORD            Width;	/* in words */
    WORD            Depth;
    WORD            MeMask;	/* what this GEL is */
    WORD            HitMask;	/* what it collides with */
    WORD           *ImageData;
    WORD           *BorderLine;	/* one row: every row ORed */
    WORD           *CollMask;	/* every plane ORed */
    WORD           *SprColors;	/* three colours, for a VSPRITE */
    struct Bob     *VSBob;
    BYTE            PlanePick;
    BYTE            PlaneOnOff;
    VUserStuff      VUserExt;
};

struct Bob
{
    WORD               Flags;
    WORD              *SaveBuffer;
    WORD              *ImageShadow;
    struct Bob        *Before;	/* draw this one first */
    struct Bob        *After;
    struct VSprite    *BobVSprite;
    struct AnimComp   *BobComp;
    struct DBufPacket *DBuffer;
    BUserStuff         BUserExt;
};

struct AnimComp
{
    WORD             Flags;
    WORD             Timer;
    WORD             TimeSet;
    struct AnimComp *NextComp;
    struct AnimComp *PrevComp;
    struct AnimComp *NextSeq;
    struct AnimComp *PrevSeq;
    WORD           (*AnimCRoutine)(struct AnimComp *);
    WORD             YTrans;
    WORD             XTrans;
    struct AnimOb   *HeadOb;
    struct Bob      *AnimBob;
};

struct AnimOb
{
    struct AnimOb   *NextOb, *PrevOb;
    LONG             Clock;
    WORD             AnOldY, AnOldX;
    WORD             AnY, AnX;
    WORD             YVel, XVel;
    WORD             YAccel, XAccel;
    WORD             RingYTrans, RingXTrans;
    WORD           (*AnimORoutine)(struct AnimOb *);
    struct AnimComp *HeadComp;
    AUserStuff       AUserExt;
};

/* Double-buffered Bob state */
struct DBufPacket
{
    WORD            BufY, BufX;
    struct VSprite *BufPath;
    WORD           *BufBuffer;
};

/* Start an empty animation list */
#define InitAnimate(animKey)	do { *(animKey) = 0; } while (0)
/* Ask DrawGList() to take a Bob off */
#define RemBob(b)		do { (b)->Flags |= BOBSAWAY; } while (0)

/* Bob collision cases */
#define B2NORM		0
#define B2SWAP		1
#define B2BOBBER	2

/* DoCollision()'s routines: 0 for the border, 1 to 15 by MeMask bit */
struct collTable
{
    int (*collPtrs[16])();
};

#endif /* GRAPHICS_GELS_H */
