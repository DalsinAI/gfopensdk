/* op_image: GFOpenDraw's picture and brushes. A picture is one byte a pixel,
 * an index into its palette of 2 to 256 colours, as Deluxe Paint's pictures
 * are; a brush is a small picture of its own with a mask of the pixels it
 * paints.
 *
 * Plain C with no Amiga calls, so the same code is tested on the host
 * (tests/host) and runs on the Amiga. GFOpenIconEdit is meant to reuse it.
 *
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef OP_IMAGE_H
#define OP_IMAGE_H

#define OP_MAX_SIDE 4096
#define OP_MAX_COLOURS 256

typedef struct op_rgb { unsigned char r, g, b; } op_rgb;

/* A box: x0,y0 inside, x1,y1 one past the right and the bottom. Empty when
 * x1 <= x0 or y1 <= y0. */
typedef struct op_rect { int x0, y0, x1, y1; } op_rect;

typedef struct op_image {
    int w, h;
    int depth;                      /* 1 to 8 bit-planes: ncolours is 1 << depth */
    int ncolours;
    unsigned char *px;              /* w * h indexes, a row after another */
    op_rgb pal[OP_MAX_COLOURS];
} op_image;

typedef struct op_brush {
    int w, h;
    int hx, hy;                     /* the handle: the pixel under the pointer */
    unsigned char *px;              /* its own colours (a brush picked up from the picture) */
    unsigned char *mask;            /* 1 where it paints */
    int custom;                     /* 1: picked up, with colours of its own; 0: a shape painted in one colour */
} op_brush;

/* A new picture of w x h in depth planes, all colour 0, with the default
 * palette (op_default_palette). 1, or 0 when out of memory or out of range. */
int op_image_init(op_image *img, int w, int h, int depth);
void op_image_free(op_image *img);
/* The default palette: Deluxe Paint's way of starting, black, white and a
 * spread of colours, made here (no table copied from anywhere). */
void op_default_palette(op_rgb *pal, int ncolours);
/* The colour of the palette's n entries nearest to c (squared distance). */
int op_nearest(const op_rgb *pal, int n, op_rgb c);

static inline int op_get(const op_image *img, int x, int y)
{
    return (x < 0 || y < 0 || x >= img->w || y >= img->h) ? -1 : img->px[y * img->w + x];
}

/* Rectangles. */
void op_rect_add(op_rect *r, int x0, int y0, int x1, int y1);      /* grow r to hold the box */
void op_rect_union(op_rect *r, const op_rect *o);
int op_rect_clip(op_rect *r, int w, int h);                         /* 0 when nothing is left */
static inline int op_rect_empty(const op_rect *r) { return r->x1 <= r->x0 || r->y1 <= r->y0; }
static inline void op_rect_clear(op_rect *r) { r->x0 = r->y0 = 0; r->x1 = r->y1 = 0; }

/* Brushes. A round or a square one of size pixels across, 1 to 64. */
int op_brush_round(op_brush *b, int size);
int op_brush_square(op_brush *b, int size);
/* Picks up the picture's pixels in r as a brush (Deluxe Paint's brush tool):
 * pixels of colour transparent (the background colour) don't paint; -1 for
 * none. The handle is the middle. */
int op_brush_grab(op_brush *b, const op_image *img, op_rect r, int transparent);
void op_brush_flip_x(op_brush *b);
void op_brush_flip_y(op_brush *b);
/* Turns it a quarter turn clockwise. 0 when out of memory (left as it was). */
int op_brush_rotate90(op_brush *b);
void op_brush_free(op_brush *b);

#endif
