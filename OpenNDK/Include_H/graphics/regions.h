#ifndef GRAPHICS_REGIONS_H
#define GRAPHICS_REGIONS_H
/*
 * OpenNDK: regions, the rectangle lists that clipping and damage use.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

/* One rectangle of a region, relative to the region's bounds */
struct RegionRectangle
{
    struct RegionRectangle *Next, *Prev;
    struct Rectangle        bounds;
};

struct Region
{
    struct Rectangle        bounds;
    struct RegionRectangle *RegionRectangle;
};

#endif /* GRAPHICS_REGIONS_H */
