/* Rawimage.mcc: a Pixmap from one block of memory: a 16-byte header (width,
 * height, format, size; big-endian) and the pixels after it, raw or packed.
 * Published names and numbers (MUI's Rawimage.mcc), our own text.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_RAWIMAGE_H
#define ZUNE_RAWIMAGE_H

#ifndef LIBRARIES_MUI_H
#include <libraries/mui.h>
#endif

#define MUIC_Rawimage "Rawimage.mcc"

#define MUIA_Rawimage_Data 0xFED10014UL   /* IS. struct MUI_RawimageData * (the program's, kept) */

#ifndef MAKE_ID
#define MAKE_ID(a, b, c, d) ((ULONG)(a) << 24 | (ULONG)(b) << 16 | (ULONG)(c) << 8 | (ULONG)(d))
#endif
#define RAWIMAGE_PIXELFORMAT_ARGB 0
#define RAWIMAGE_PIXELFORMAT_RGB  1
#define RAWIMAGE_FORMAT_RAW_ARGB_ID  RAWIMAGE_PIXELFORMAT_ARGB
#define RAWIMAGE_FORMAT_RAW_RGB_ID   RAWIMAGE_PIXELFORMAT_RGB
#define RAWIMAGE_FORMAT_BZ2_ARGB_ID  MAKE_ID('B', 'Z', '2', RAWIMAGE_PIXELFORMAT_ARGB)
#define RAWIMAGE_FORMAT_BZ2_RGB_ID   MAKE_ID('B', 'Z', '2', RAWIMAGE_PIXELFORMAT_RGB)
#define RAWIMAGE_FORMAT_Z_ARGB_ID    MAKE_ID('Z', 0, 0, RAWIMAGE_PIXELFORMAT_ARGB)
#define RAWIMAGE_FORMAT_Z_RGB_ID     MAKE_ID('Z', 0, 0, RAWIMAGE_PIXELFORMAT_RGB)
#define RAWIMAGE_FORMAT_RLE_ARGB_ID  MAKE_ID('R', 'L', 'E', RAWIMAGE_PIXELFORMAT_ARGB)
#define RAWIMAGE_FORMAT_RLE_RGB_ID   MAKE_ID('R', 'L', 'E', RAWIMAGE_PIXELFORMAT_RGB)
#define RAWIMAGE_FORMAT_LZMA_ARGB_ID MAKE_ID('L', 'Z', 'M', RAWIMAGE_PIXELFORMAT_ARGB)
#define RAWIMAGE_FORMAT_LZMA_RGB_ID  MAKE_ID('L', 'Z', 'M', RAWIMAGE_PIXELFORMAT_RGB)

struct MUI_RawimageData {
    ULONG ri_Width;
    ULONG ri_Height;
    ULONG ri_Format;
    ULONG ri_Size;
    ULONG ri_Data[];        /* the pixels, ri_Size bytes when packed */
};

#define RawimageObject MUIOBJMACRO_START(MUIC_Rawimage)

#endif
