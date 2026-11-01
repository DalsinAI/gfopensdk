#ifndef GRAPHICS_LAYERS_H
#define GRAPHICS_LAYERS_H
/*
 * OpenNDK: layers.library's Layer_Info and layer flags.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif

#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif

#ifndef GRAPHICS_CLIP_H
#include <graphics/clip.h>
#endif
#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

/* Layer Flags */
#define LAYERSIMPLE		1	/* refreshed by the owner */
#define LAYERSMART		2	/* hidden parts kept off screen */
#define LAYERSUPER		4	/* backed by a whole SuperBitMap */
#define LAYERUPDATING		0x10	/* between BeginUpdate and EndUpdate */
#define LAYERBACKDROP		0x40	/* stays behind the others */
#define LAYERREFRESH		0x80	/* has damage to repair */
#define LAYER_CLIPRECTS_LOST	0x100	/* out of memory during an operation */
#define LAYERIREFRESH		0x200
#define LAYERIREFRESH2		0x400

#define LMN_REGION	-1

struct Layer_Info
{
    struct Layer    *top_layer;
    APTR             resPtr1;	/* private */
    APTR             resPtr2;	/* private */
    struct ClipRect *FreeClipRects;	/* private */
    struct Rectangle bounds;	/* the area the layers cover */
    struct SignalSemaphore Lock;
    struct MinList   gs_Head;	/* private */
    WORD             PrivateReserve3;
    VOID            *PrivateReserve4;
    UWORD            Flags;
    BYTE             res_count;	/* private */
    BYTE             LockLayersCount;	/* private */
    BYTE             PrivateReserve5;
    BYTE             UserClipRectsCount;	/* private */
    struct Hook     *BlankHook;	/* backfill for areas no layer covers */
    APTR             resPtr5;	/* private */
};

/* Layer_Info Flags */
#define NEWLAYERINFO_CALLED	1

/* Special hook values for a layer's or Layer_Info's backfill */
#define LAYERS_NOBACKFILL	((struct Hook *)1)	/* leave the pixels alone */
#define LAYERS_BACKFILL		((struct Hook *)0)	/* clear to colour 0 */

/* More names from the 3.2 interface */
#define LAYERHIDDEN		0x1000
#define LAYERSAVEBACK		0x800
#define LAYER_BACKMOST		0
#define LAYER_FRONTMOST		1

#endif /* GRAPHICS_LAYERS_H */
