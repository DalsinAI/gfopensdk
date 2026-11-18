/* op_tools: GFOpenDraw's painting: the brush stamped along freehand strokes
 * and lines, rectangles, circles and ellipses, flood fill, the airbrush and
 * colour cycling. Studied from Deluxe Paint and DPaint.js (Steffest, MIT)
 * for what each tool does; the code is our own.
 *
 * Every call adds the pixels it may have changed to p->dirty, so the program
 * redraws only those and the undo keeps only those.
 *
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef OP_TOOLS_H
#define OP_TOOLS_H

#include "op_image.h"

/* How a brush puts down paint (Deluxe Paint's Mode menu). */
enum {
    OP_MODE_COLOR = 0,      /* the brush's shape in the colour given */
    OP_MODE_MATTE,          /* a picked-up brush in its own colours, its background left out */
    OP_MODE_REPLACE,        /* a picked-up brush in its own colours, background too */
    OP_MODE_CYCLE           /* each stamp in the next colour of the cycling range */
};

typedef struct op_paint {
    op_image *img;
    const op_brush *brush;
    int mode;
    int cycle_lo, cycle_hi;   /* the cycling range, for OP_MODE_CYCLE and op_cycle */
    int cycle_at;
    unsigned long seed;       /* the airbrush's own random numbers */
    op_rect dirty;
} op_paint;

void op_paint_init(op_paint *p, op_image *img, const op_brush *brush);

/* The colour a picked-up brush paints in its own colours with (Matte and
 * Replace); any colour 0 to 255 paints the brush's shape in that colour, as
 * the right mouse button does with the background colour. */
#define OP_OWN (-1)

/* One pixel, with no brush. */
void op_pixel(op_paint *p, int x, int y, int colour);
/* The brush, with its handle at x,y. */
void op_stamp(op_paint *p, int x, int y, int colour);
/* The brush along a line, both ends included. */
void op_line(op_paint *p, int x0, int y0, int x1, int y1, int colour);
/* The same without the first point: a freehand stroke's next piece, so the
 * point it starts from is not painted twice (that matters for Cycle). */
void op_line_on(op_paint *p, int x0, int y0, int x1, int y1, int colour);
/* A rectangle between two corners: outlined with the brush, or filled. */
void op_rectangle(op_paint *p, int x0, int y0, int x1, int y1, int filled, int colour);
/* An ellipse in the box rx, ry about cx, cy (a circle when rx == ry):
 * outlined with the brush, or filled. */
void op_ellipse(op_paint *p, int cx, int cy, int rx, int ry, int filled, int colour);
/* Fills the area of one colour that holds x,y (4-connected), as Deluxe
 * Paint's fill. The pixels changed, 0 when none. */
long op_flood(op_paint *p, int x, int y, int colour);
/* The airbrush: count stamps at random within radius of x,y. */
void op_spray(op_paint *p, int x, int y, int radius, int count, int colour);

/* Turns the palette entries lo to hi by one step (Deluxe Paint's colour
 * cycling, Tab): up when dir > 0. */
void op_cycle(op_rgb *pal, int lo, int hi, int dir);

#endif
