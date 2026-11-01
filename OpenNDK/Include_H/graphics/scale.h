#ifndef GRAPHICS_SCALE_H
#define GRAPHICS_SCALE_H
/*
 * OpenNDK: the argument block of BitMapScale().
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

struct BitScaleArgs
{
    UWORD          bsa_SrcX, bsa_SrcY;
    UWORD          bsa_SrcWidth, bsa_SrcHeight;
    UWORD          bsa_XSrcFactor, bsa_YSrcFactor;	/* the scale is Dest / Src */
    UWORD          bsa_DestX, bsa_DestY;
    UWORD          bsa_DestWidth, bsa_DestHeight;	/* written by BitMapScale() */
    UWORD          bsa_XDestFactor, bsa_YDestFactor;
    struct BitMap *bsa_SrcBitMap;
    struct BitMap *bsa_DestBitMap;
    ULONG          bsa_Flags;	/* none defined; keep 0 */
    UWORD          bsa_XDDA, bsa_YDDA;	/* private */
    LONG           bsa_Reserved1;
    LONG           bsa_Reserved2;
};

#endif /* GRAPHICS_SCALE_H */
