/* Copyright (c) 2026 AmiCradle Team. MIT licence.
 *
 * akikoplus.library: helpers done natively on AmiCradle's AkikoPlus board,
 * and in 68k code where there is no board, so the same program runs anywhere.
 * The two give the same bytes (the zlib streams excepted: each side's
 * decompresses to the same data on both).
 *
 * Version 2 (9 November 2026) keeps version 1's calls, their offsets and
 * their structures, and goes to the board through mitchy.library (which
 * goes through gfopenservice.device, the owner of every ACSV board's rings).
 * New in 2: AP_Compress and AP_Decompress on the 68k too, AP_SetMode and
 * AP_Query. A build with AP_NO_FALLBACK (for machines that always have the
 * board) leaves the 68k versions out: AP_Status says so, and the calls answer
 * AP_ERR_NOBOARD without the board.
 *
 * A call small enough to be quicker on the 68k stays there (AP_SetThreshold).
 * Every call returns 0, or a negative AP_ERR_ (AP_Quantise returns the
 * colours, AP_Compress and AP_Decompress the bytes written).
 * The autodoc is akikoplus.doc; the calls' offsets are sfd/akikoplus_lib.sfd's.
 */
#ifndef LIBRARIES_AKIKOPLUS_H
#define LIBRARIES_AKIKOPLUS_H

#include <exec/types.h>

#define AKIKOPLUS_NAME "akikoplus.library"
#define AKIKOPLUS_VERSION 2

#define AP_ERR_BADARGS  (-1)
#define AP_ERR_NOBOARD  (-2)   /* a board-only build (AP_NO_FALLBACK) on a machine without the board */
#define AP_ERR_TOOSMALL (-4)   /* the destination is too small */
#define AP_ERR_NOMEM    (-5)

/* AP_Status */
#define APSF_BOARD    1        /* the board's services are open */
#define APSF_FALLBACK 2        /* (2) the 68k versions are built in */

/* AP_SetMode (2): where the work runs. */
#define APMODE_AUTO   0        /* the board when fitted and the job reaches AP_SetThreshold's bytes */
#define APMODE_68K    1        /* the 68k always */
#define APMODE_BOARD  2        /* the board always, when fitted (else the 68k) */

/* AP_Query (2) */
#define APQ_SERVICES  1        /* APF_* of the board's services that are open */
#define APQ_METHOD    2        /* the board's METHOD: 0 plain C, 1 SSSE3, 2 AVX2, 3 NEON; -1 no board */
#define APQ_MODE      3        /* APMODE_* */
#define APQ_THRESHOLD 4        /* AP_SetThreshold's bytes */
#define APQ_LASTRAN   5        /* the last call, from any task: 1 the board, 0 the 68k, -1 none yet */

#define APF_SWAP     (1UL << 0)   /* akiko.swap/1 */
#define APF_C2P      (1UL << 1)   /* akiko.c2p/1 */
#define APF_FILL     (1UL << 2)   /* akiko.fill/1 */
#define APF_SCALE    (1UL << 3)   /* akiko.scale/1 */
#define APF_CONVERT  (1UL << 4)   /* akiko.convert/1 */
#define APF_Z        (1UL << 5)   /* akiko.z/1 */

struct APC2P {
    const UBYTE *ap_Chunky;
    UBYTE *ap_Planes;
    ULONG ap_ChunkyLen, ap_PlanesLen;
    UWORD ap_Width, ap_Height, ap_Depth, ap_Pad;   /* depth 1-8 */
    ULONG ap_ChunkyPitch;
    ULONG ap_RowStride;        /* bytes from a row of a plane to its next */
    ULONG ap_PlaneStride;      /* bytes from a plane to the next */
};
struct APFill {
    UBYTE *ap_Dest;
    ULONG ap_DestLen;
    UWORD ap_Width, ap_Height, ap_BytesPerPixel, ap_Pad;   /* 1-4 */
    ULONG ap_Pitch;
    ULONG ap_Pixel;            /* big-endian in its low bytes */
};
struct APCopy {
    const UBYTE *ap_Src;
    UBYTE *ap_Dest;
    ULONG ap_SrcLen, ap_DestLen;
    UWORD ap_Width, ap_Height, ap_BytesPerPixel, ap_Pad;
    ULONG ap_SrcPitch, ap_DestPitch;
};
#define APSCALE_NEAREST 1
#define APSCALE_BILINEAR 2     /* 3 or 4 bytes a pixel */
struct APScale {
    const UBYTE *ap_Src;
    UBYTE *ap_Dest;
    ULONG ap_SrcLen, ap_DestLen;
    UWORD ap_SrcWidth, ap_SrcHeight, ap_DestWidth, ap_DestHeight;
    ULONG ap_SrcPitch, ap_DestPitch;
    UWORD ap_BytesPerPixel, ap_Filter;
};
struct APYUV {                 /* 4:2:0, BT.601, studio range, to ARGB32 */
    const UBYTE *ap_Y, *ap_U, *ap_V;
    UBYTE *ap_Dest;
    ULONG ap_YLen, ap_ULen, ap_VLen, ap_DestLen;
    UWORD ap_Width, ap_Height;
    ULONG ap_YPitch, ap_UVPitch, ap_DestPitch;
};
struct APQuant {               /* ARGB32 to 8-bit, median cut */
    const UBYTE *ap_Src;
    UBYTE *ap_Dest;
    UBYTE *ap_Palette;         /* 4 bytes a colour: 0, R, G, B */
    ULONG ap_SrcLen, ap_DestLen, ap_PaletteLen;
    UWORD ap_Width, ap_Height;
    ULONG ap_SrcPitch, ap_DestPitch;
    ULONG ap_Colours;          /* 2-256 */
};

#endif
