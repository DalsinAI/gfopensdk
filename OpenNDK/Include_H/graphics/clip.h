#ifndef GRAPHICS_CLIP_H
#define GRAPHICS_CLIP_H
/*
 * OpenNDK: layers and their clip rectangles.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif

#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* Layer_Info locking is by semaphore */
#define NEWLOCKS

struct Layer
{
    struct Layer      *front, *back;	/* depth order */
    struct ClipRect   *ClipRect;	/* where rendering goes */
    struct RastPort   *rp;
    struct Rectangle   bounds;	/* on the screen */
    struct Layer      *nlink;	/* private */
    UWORD              priority;	/* private */
    UWORD              Flags;	/* LAYERSIMPLE and friends */
    struct BitMap     *SuperBitMap;
    struct ClipRect   *SuperClipRect;	/* private */
    APTR               Window;	/* free for the owner (Intuition) */
    WORD               Scroll_X, Scroll_Y;
    struct ClipRect   *OnScreen;	/* private: the visible pieces */
    struct ClipRect   *OffScreen;	/* private: the hidden pieces */
    struct ClipRect   *Backup;	/* private */
    struct ClipRect   *SuperSaveClipRects;	/* private */
    struct Region     *Undamaged;	/* private */
    struct Layer_Info *LayerInfo;
    struct SignalSemaphore Lock;
    struct Hook       *BackFill;
    ULONG              reserved1;
    struct Region     *ClipRegion;
    struct Region     *clipped;	/* private: the region before clipping */
    WORD               Width, Height;
    UBYTE              reserved2[18];
    struct Region     *DamageList;	/* to repair after a refresh */
};

struct ClipRect
{
    struct ClipRect *Next;
    struct ClipRect *reservedlink;	/* private */
    LONG             obscured;	/* nonzero when hidden by another layer */
    struct BitMap   *BitMap;	/* private backing store */
    struct Rectangle bounds;
    struct ClipRect *vlink;	/* private */
    struct Layer_Info *home;	/* private: the Layer_Info whose pool it came from, or NULL */
    APTR             reserved;	/* private */
#ifdef NEWCLIPRECTS_1_1
    LONG             Flags;	/* private: layers' own bits for this piece */
#endif
};

/* Private ClipRect bits */
#define CR_USERCLIPPED		16	/* clipped by the user's region */
#define CR_DAMAGECLIPPED	32	/* clipped by the damage list */

/* Outcodes */
#define ISLESSX	1
#define ISLESSY	2
#define ISGRTRX	4
#define ISGRTRY	8

#endif /* GRAPHICS_CLIP_H */
