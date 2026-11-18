/* GFOpenDraw's reusable indexed-painting engine.
 *
 * The engine is plain C and has no Amiga dependencies. Applications provide
 * their own file, window and rendering layers and reuse the indexed image,
 * brush, paint-tool, quantization and bounded undo APIs below.
 *
 * Two ways to use it:
 *  - linked in, from the SDK's libgfopendraw.a (kept for one more release);
 *  - from gfopendraw.library (library/, docs in DESIGN.md "The library"):
 *    build with GFOPENDRAW_USE_LIBRARY defined and open the library into
 *    GFOpenDrawBase (gfd_open() below does both checks a program needs).
 *    The calls keep their names: <proto/gfopendraw.h>, included at the end
 *    of this header, makes each one a call through the library's base.
 *
 * Include this header (not op_image.h and the others alone) in a program
 * that uses the library, so every call goes to the library.
 *
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef GFOPENDRAW_H
#define GFOPENDRAW_H

#define GFOPENDRAW_ENGINE_VERSION "0.2.1"
#define GFOPENDRAW_ENGINE_VERSION_MAJOR 0
#define GFOPENDRAW_ENGINE_VERSION_MINOR 2
#define GFOPENDRAW_ENGINE_VERSION_PATCH 1

/* gfopendraw.library: its name and the version a program built with these
 * headers needs (library/gfopendraw_lib.sfd). */
#define GFOPENDRAW_LIBRARY_NAME "gfopendraw.library"
#define GFOPENDRAW_LIBRARY_VERSION 1

#ifdef __cplusplus
extern "C" {
#endif

#include "op_image.h"
#include "op_tools.h"
#include "op_undo.h"
#include "op_quant.h"

/* The engine's structures, by number, for op_struct_size: a program checks
 * the library it opened has the sizes it was built with (a structure that
 * grows makes a new library version). */
enum {
    OP_STRUCT_IMAGE = 0,
    OP_STRUCT_BRUSH,
    OP_STRUCT_PAINT,
    OP_STRUCT_UNDO,
    OP_STRUCT_COUNT
};
/* sizeof the structure, 0 for a number it does not know. */
unsigned long op_struct_size(int which);

/* The calls that take a structure by value, with a pointer instead: a
 * library call takes its arguments in registers. With the library, the
 * by-value names below are macros over these, so a program calls either. */
int op_nearest_p(const op_rgb *pal, int n, const op_rgb *c);
int op_brush_grab_p(op_brush *b, const op_image *img, const op_rect *r, int transparent);
void op_undo_restore_p(op_undo *u, op_image *img, const op_rect *r);
void op_undo_end_p(op_undo *u, const op_image *img, const op_rect *changed);

#ifdef __cplusplus
}
#endif

#if defined(GFOPENDRAW_USE_LIBRARY) && !defined(GFOPENDRAW_LIBRARY_BUILD)
#include <proto/gfopendraw.h>
#define op_nearest(pal, n, c) __extension__({ op_rgb __gfd_c = (c); op_nearest_p((pal), (n), &__gfd_c); })
#define op_brush_grab(b, img, r, t) __extension__({ op_rect __gfd_r = (r); op_brush_grab_p((b), (img), &__gfd_r, (t)); })
#define op_undo_restore(u, img, r) __extension__({ op_rect __gfd_r = (r); op_undo_restore_p((u), (img), &__gfd_r); })
#define op_undo_end(u, img, r) __extension__({ op_rect __gfd_r = (r); op_undo_end_p((u), (img), &__gfd_r); })

/* Opens gfopendraw.library into GFOpenDrawBase: 1, or 0 with why in *why
 * (not there, too old, or built with other structure sizes) and the
 * library left closed. gfd_close() closes it (when open). */
#include <proto/exec.h>
static inline int gfd_open(const char **why)
{
    static const unsigned long want[OP_STRUCT_COUNT] = {
        sizeof(op_image), sizeof(op_brush), sizeof(op_paint), sizeof(op_undo)
    };
    int i;
    GFOpenDrawBase = OpenLibrary((CONST_STRPTR)GFOPENDRAW_LIBRARY_NAME, GFOPENDRAW_LIBRARY_VERSION);
    if (!GFOpenDrawBase) {
        *why = "needs " GFOPENDRAW_LIBRARY_NAME " 1 in LIBS:";
        return 0;
    }
    for (i = 0; i < OP_STRUCT_COUNT; i++)
        if (op_struct_size(i) != want[i]) {
            CloseLibrary(GFOpenDrawBase);
            GFOpenDrawBase = 0;
            *why = GFOPENDRAW_LIBRARY_NAME " in LIBS: does not match this program (structure sizes)";
            return 0;
        }
    return 1;
}
static inline void gfd_close(void)
{
    if (GFOpenDrawBase) CloseLibrary(GFOpenDrawBase);
    GFOpenDrawBase = 0;
}
#endif

#endif
