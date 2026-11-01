#ifndef GRAPHICS_GFXMACROS_H
#define GRAPHICS_GFXMACROS_H
/*
 * OpenNDK: shorthand macros for RastPort fields, user copper lists and
 * DMA control.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef GRAPHICS_RASTPORT_H
#include <graphics/rastport.h>
#endif
#ifndef GRAPHICS_GFXBASE_H
#include <graphics/gfxbase.h>
#endif
#ifndef HARDWARE_CUSTOM_H
#include <hardware/custom.h>
#endif
#ifndef HARDWARE_DMABITS_H
#include <hardware/dmabits.h>
#endif

/*
 * DMA and interrupt switches. These write the custom chips directly, so
 * the program must include <hardware/custom.h>, <hardware/dmabits.h> and
 * <hardware/intbits.h> and declare the chips as "custom".
 */
#define ON_DISPLAY	(custom.dmacon = (UWORD)(BITSET | DMAF_RASTER));
#define OFF_DISPLAY	(custom.dmacon = (UWORD)(BITCLR | DMAF_RASTER));
#define ON_SPRITE	(custom.dmacon = (UWORD)(BITSET | DMAF_SPRITE));
#define OFF_SPRITE	(custom.dmacon = (UWORD)(BITCLR | DMAF_SPRITE));
#define ON_VBLANK	(custom.intena = (UWORD)(BITSET | INTF_VERTB));
#define OFF_VBLANK	(custom.intena = (UWORD)(BITCLR | INTF_VERTB));

/* Line pattern, restarted at the first dot */
#define SetDrPt(rp, pat) \
    do { (rp)->LinePtrn = (pat); (rp)->Flags |= FRST_DOT; (rp)->linpatcnt = 15; } while (0)

/* Area pattern and its height as a power of two */
#define SetAfPt(rp, pat, sz) \
    do { (rp)->AreaPtrn = (pat); (rp)->AreaPtSz = (sz); } while (0)

/* Area outline pen; outlining on */
#define SetOPen(rp, pen) \
    do { (rp)->AOlPen = (pen); (rp)->Flags |= AREAOUTLINE; } while (0)

/* Planes drawn into */
#define SetWrMsk(rp, msk) \
    do { (rp)->Mask = (msk); } while (0)

/* The same through the V39 calls when the library has them (needs GfxBase) */
#define SafeSetOutlinePen(rp, pen) \
    do { \
	if (GfxBase->LibNode.lib_Version >= 39) SetOutlinePen((rp), (pen)); \
	else { (rp)->AOlPen = (pen); (rp)->Flags |= AREAOUTLINE; } \
    } while (0)

#define SafeSetWriteMask(rp, msk) \
    do { \
	if (GfxBase->LibNode.lib_Version >= 39) SetWriteMask((rp), (msk)); \
	else (rp)->Mask = (msk); \
    } while (0)

/* Outlining off */
#define BNDRYOFF(rp) \
    do { (rp)->Flags &= ~AREAOUTLINE; } while (0)

/* User copper lists: n instructions, a move of b to register a, a wait
   for line a and position b, and the end of the list */
#define CINIT(ucl, n)	UCopperListInit((ucl), (n))
#define CMOVE(ucl, reg, val) \
    do { CMove((ucl), (APTR)&(reg), (val)); CBump(ucl); } while (0)
#define CWAIT(ucl, v, h) \
    do { CWait((ucl), (v), (h)); CBump(ucl); } while (0)
#define CEND(ucl)	CWAIT((ucl), 10000, 255)

/* Circles as round ellipses */
#define DrawCircle(rp, cx, cy, r)	DrawEllipse((rp), (cx), (cy), (r), (r))
#define AreaCircle(rp, cx, cy, r)	AreaEllipse((rp), (cx), (cy), (r), (r))

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef GRAPHICS_GFXBASE_H
#include <graphics/gfxbase.h>
#endif
#ifndef HARDWARE_CUSTOM_H
#include <hardware/custom.h>
#endif
#ifndef HARDWARE_DMABITS_H
#include <hardware/dmabits.h>
#endif

#endif /* GRAPHICS_GFXMACROS_H */
