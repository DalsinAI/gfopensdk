/* op_quant: a true-colour picture (a PNG, a JPEG, a 24-bit ILBM) made into
 * a GFOpenDraw picture of up to 256 colours: the colours used most, each
 * pixel then in the nearest of them. Plain C, integers only.
 *
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef OP_QUANT_H
#define OP_QUANT_H

#include "op_image.h"

/* rgb: w * h pixels of 3 bytes (R, G, B). img must already be w x h in the
 * depth wanted; its palette and pixels are replaced. 1, or 0 when out of
 * memory. */
int op_quantize(const unsigned char *rgb, int w, int h, op_image *img);

#endif
