/* op_undo: GFOpenDraw's undo and redo, as many steps as a memory budget
 * holds. A step keeps only the box of pixels it changed, and the palette
 * when that changed, so long strokes on a big picture cost little.
 *
 * Before a step, op_undo_begin copies the picture once into a spare page;
 * while a shape is dragged out, op_undo_restore puts back the box the last
 * try drew (the rubber band); op_undo_end keeps the box the step changed.
 *
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef OP_UNDO_H
#define OP_UNDO_H

#include "op_image.h"

#define OP_UNDO_MAX 64

typedef struct op_undo_step {
    op_rect r;
    unsigned char *px;      /* the box's pixels, from before (swapped with the picture's on undo and redo) */
    op_rgb *pal;            /* the palette, when the step changed it, else NULL */
    long bytes;
} op_undo_step;

typedef struct op_undo {
    long budget, used;
    int n, at;              /* steps kept; steps before 'at' can be undone, from 'at' on redone */
    op_undo_step step[OP_UNDO_MAX];
    unsigned char *spare;   /* the picture as it was when the step began */
    op_rgb spare_pal[OP_MAX_COLOURS];
    int spare_w, spare_h;
    int open;
} op_undo;

void op_undo_init(op_undo *u, long budget_bytes);
/* Forgets every step (a new or a loaded picture). */
void op_undo_clear(op_undo *u);
void op_undo_free(op_undo *u);
/* Starts a step. 0 when out of memory: the step can't be undone, but
 * painting goes on. */
int op_undo_begin(op_undo *u, const op_image *img);
/* Puts back the pixels in r as they were when the step began. */
void op_undo_restore(op_undo *u, op_image *img, op_rect r);
/* Ends the step: changed is the box it changed (empty: nothing to keep,
 * unless the palette changed). */
void op_undo_end(op_undo *u, const op_image *img, op_rect changed);
/* Undoes or redoes one step. 1 with the box to redraw in *r (the whole
 * picture when the palette changed), 0 when there is none. */
int op_undo_undo(op_undo *u, op_image *img, op_rect *r);
int op_undo_redo(op_undo *u, op_image *img, op_rect *r);
static inline int op_undo_can_undo(const op_undo *u) { return u->at > 0; }
static inline int op_undo_can_redo(const op_undo *u) { return u->at < u->n; }

#endif
