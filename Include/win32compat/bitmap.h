/* Copyright (c) 2026 AmigaChrome Team. MIT licence. */
#ifndef OPENSDK_WIN32COMPAT_BITMAP_H
#define OPENSDK_WIN32COMPAT_BITMAP_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

/* Checked bitmap operations, not a complete Win32/GDI implementation.
 * Storage is caller-owned. bytes must describe its real allocation; a raw
 * pointer's ownership or lifetime cannot be established by this interface.
 * INDEX8 copies palette indices. BGRX32 stores B,G,R,X bytes on every CPU. */
typedef enum OW32_Format { OW32_INDEX8 = 1, OW32_BGRX32 = 4 } OW32_Format;
typedef enum OW32_Status {
    OW32_OK = 0, OW32_EMPTY = 1, OW32_INVALID = -1,
    OW32_RANGE = -2, OW32_UNSUPPORTED = -3, OW32_ALIAS = -4
} OW32_Status;
typedef struct OW32_Bitmap {
    unsigned char *storage;
    size_t bytes;
    size_t row0;
    uint32_t width, height;
    int32_t stride;
    OW32_Format format;
} OW32_Bitmap;
typedef struct OW32_CopyArea {
    uint32_t sx, sy, dx, dy, width, height;
} OW32_CopyArea;

OW32_Status OW32_BitmapValidate(const OW32_Bitmap *bitmap);
OW32_Status OW32_BitmapInit(OW32_Bitmap *out, void *storage, size_t bytes,
    size_t row0, uint32_t width, uint32_t height, int32_t stride, OW32_Format format);
/* Decode a little-endian BITMAPINFOHEADER (>=40 bytes), BI_RGB, 8/32 bpp.
 * Pixels are supplied separately; positive DIB height means bottom-up.
 * On failure out is unchanged. No screen/viewport size enters this interface. */
OW32_Status OW32_BitmapFromDIB(OW32_Bitmap *out, void *pixels, size_t bytes,
    const void *header, size_t header_bytes);
OW32_Status OW32_BitmapRowOffset(const OW32_Bitmap *bitmap, uint32_t row, size_t *offset);
/* Unscaled SRCCOPY only. Clip jointly against source and destination bitmaps.
 * Identical-layout self copies may overlap; differing overlapping storage
 * views return OW32_ALIAS before writing. Formats must match. */
OW32_Status OW32_BitmapCopy(OW32_Bitmap *dst, int32_t dx, int32_t dy,
    const OW32_Bitmap *src, int32_t sx, int32_t sy, uint32_t width, uint32_t height,
    OW32_CopyArea *copied);
/* INDEX8: value <=255. BGRX32: value 0x00RRGGBB, X is written as zero. */
OW32_Status OW32_BitmapFill(OW32_Bitmap *dst, int32_t x, int32_t y,
    uint32_t width, uint32_t height, uint32_t value);
#ifdef __cplusplus
}
#endif
#endif
