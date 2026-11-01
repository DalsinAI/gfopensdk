/* Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * graphics calls OS 4 has and OS 3.2 has not: tagged AllocBitMap and
 * BltBitMap, and the part of CompositeTags() a blit can do. Alpha blending
 * and scaling answer COMPERR_SoftwareFallback, as OS 4 itself does without
 * hardware, so a program draws those itself.
 */
#include "os4c_internal.h"
#include <graphics/rastport.h>
#include <proto/exec.h>
#include <proto/graphics.h>
#include <proto/utility.h>

#ifndef BMF_SPECIALFMT
#define BMF_SPECIALFMT 0x80
#endif

struct BitMap *os4c_AllocBitMapTagList(ULONG width, ULONG height, ULONG depth, struct TagItem *tags)
{
	ULONG flags = 0, fmt;
	struct BitMap *friend;
	/* a BitMap with no planes for the caller to fill: graphics cannot make
	 * one for RTG, so this is unsupported rather than a wrong allocation */
	if (GetTagData(BMATags_NoMemory, FALSE, tags))
		return NULL;
	if (GetTagData(BMATags_Clear, FALSE, tags)) flags |= BMF_CLEAR;
	if (GetTagData(BMATags_Displayable, FALSE, tags)) flags |= BMF_DISPLAYABLE;
	if (GetTagData(BMATags_Interleaved, FALSE, tags)) flags |= BMF_INTERLEAVED;
	fmt = GetTagData(BMATags_PixelFormat, 0, tags);
	if (fmt)
		flags |= BMF_SPECIALFMT | (fmt << 24);   /* the RTG pixel-format convention */
	/* not inside AllocBitMap's arguments: see exec_extras.c, ASOT_PORT */
	friend = (struct BitMap *)GetTagData(BMATags_Friend, 0, tags);
	return AllocBitMap(width, height, depth, flags, friend);
}

struct BitMap *os4c_AllocBitMapTags(ULONG width, ULONG height, ULONG depth, ...)
{
	va_list ap;
	struct BitMap *r;
	va_start(ap, depth);
	r = os4c_AllocBitMapTagList(width, height, depth, (struct TagItem *)ap);
	va_end(ap);
	return r;
}

LONG os4c_BltBitMapTagList(struct TagItem *tags)
{
	APTR src = (APTR)GetTagData(BLITA_Source, 0, tags);
	APTR dst = (APTR)GetTagData(BLITA_Dest, 0, tags);
	ULONG st = GetTagData(BLITA_SrcType, BLITT_BITMAP, tags);
	ULONG dt = GetTagData(BLITA_DestType, BLITT_BITMAP, tags);
	LONG sx = GetTagData(BLITA_SrcX, 0, tags), sy = GetTagData(BLITA_SrcY, 0, tags);
	LONG dx = GetTagData(BLITA_DestX, 0, tags), dy = GetTagData(BLITA_DestY, 0, tags);
	LONG w = GetTagData(BLITA_Width, 0, tags), h = GetTagData(BLITA_Height, 0, tags);
	ULONG minterm = GetTagData(BLITA_Minterm, 0xc0, tags);
	ULONG mask = GetTagData(BLITA_Mask, 0xff, tags);

	if (!src || !dst || w <= 0 || h <= 0 || GetTagData(BLITA_UseSrcAlpha, FALSE, tags))
		return FALSE;
	if (st == BLITT_RASTPORT && dt == BLITT_RASTPORT) {
		ClipBlit(src, sx, sy, dst, dx, dy, w, h, minterm);
		return TRUE;
	}
	if (st == BLITT_RASTPORT && dt == BLITT_BITMAP) {
		src = ((struct RastPort *)src)->BitMap;
		st = BLITT_BITMAP;
	}
	if (st == BLITT_BITMAP && dt == BLITT_RASTPORT) {
		BltBitMapRastPort(src, sx, sy, dst, dx, dy, w, h, minterm);
		return TRUE;
	}
	if (st == BLITT_BITMAP && dt == BLITT_BITMAP)
		return BltBitMap(src, sx, sy, dst, dx, dy, w, h, minterm, mask, NULL) != 0;
	return FALSE;   /* chunky, ARGB and template sources: not yet */
}

LONG os4c_BltBitMapTags(Tag tag1, ...)
{
	return os4c_BltBitMapTagList((struct TagItem *)&tag1);
}

ULONG os4c_CompositeTagList(ULONG op, struct BitMap *src, struct BitMap *dst, struct TagItem *tags)
{
	LONG sx, sy, w, h, dx, dy;
	ULONG depth;
	if (!dst || (!src && op != COMPOSITE_Clear))
		return COMPERR_MissingInput;
	if (GetTagData(COMPTAG_ScaleX, 0x10000, tags) != 0x10000
	    || GetTagData(COMPTAG_ScaleY, 0x10000, tags) != 0x10000
	    || GetTagData(COMPTAG_SrcAlpha, 0x10000, tags) != 0x10000
	    || FindTagItem(COMPTAG_SrcAlphaMask, tags) || FindTagItem(COMPTAG_DestAlphaMask, tags))
		return COMPERR_SoftwareFallback;
	sx = GetTagData(COMPTAG_SrcX, 0, tags);
	sy = GetTagData(COMPTAG_SrcY, 0, tags);
	w = src ? GetBitMapAttr(src, BMA_WIDTH) : 0;
	h = src ? GetBitMapAttr(src, BMA_HEIGHT) : 0;
	w = GetTagData(COMPTAG_SrcWidth, w, tags);
	h = GetTagData(COMPTAG_SrcHeight, h, tags);
	dx = GetTagData(COMPTAG_DestX, 0, tags) + GetTagData(COMPTAG_OffsetX, 0, tags);
	dy = GetTagData(COMPTAG_DestY, 0, tags) + GetTagData(COMPTAG_OffsetY, 0, tags);
	switch (op) {
	case COMPOSITE_Src:
	case COMPOSITE_Src_Over_Dest:
		/* only an opaque source is a copy; a 32-bit one may carry alpha */
		depth = src ? GetBitMapAttr(src, BMA_DEPTH) : 0;
		if (op == COMPOSITE_Src_Over_Dest && depth >= 32)
			return COMPERR_SoftwareFallback;
		if (w > 0 && h > 0)
			BltBitMap(src, sx, sy, dst, dx, dy, w, h, 0xc0, 0xff, NULL);
		return COMPERR_Success;
	case COMPOSITE_Dest:
		return COMPERR_Success;
	case COMPOSITE_Clear:
		w = GetBitMapAttr(dst, BMA_WIDTH);
		h = GetBitMapAttr(dst, BMA_HEIGHT);
		w = GetTagData(COMPTAG_DestWidth, w, tags);
		h = GetTagData(COMPTAG_DestHeight, h, tags);
		BltBitMap(dst, dx, dy, dst, dx, dy, w, h, 0x00, 0xff, NULL);
		return COMPERR_Success;
	default:
		return COMPERR_SoftwareFallback;
	}
}

ULONG os4c_CompositeTags(ULONG op, struct BitMap *src, struct BitMap *dst, ...)
{
	va_list ap;
	ULONG r;
	va_start(ap, dst);
	r = os4c_CompositeTagList(op, src, dst, (struct TagItem *)ap);
	va_end(ap);
	return r;
}
