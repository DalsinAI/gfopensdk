/* GFOpenGPU's vector drawing from the Open SDK: what a browser draws with
 * once cairo is gone. One batch of stream words (<gfopengpu/stream.h>) into
 * a 160 x 100 ARGB32 picture in memory, written as a PPM file:
 *   - a background and a rectangle (FILL);
 *   - an anti-aliased star, even-odd (PATH_FILL), and its outline stroked
 *     with round joins (PATH_STROKE);
 *   - a clip that is a circle: an A8 mask filled with 255, the circle drawn
 *     into it with OGPU_PD_IN, then a linear gradient filled through it
 *     (OGPU_PATH_MASK): how clipPath works without cairo;
 *   - a glyph-like A8 picture drawn in one colour through COMPOSITE_PD with
 *     a solid source and the A8 slot as its mask (how a glyph cache draws);
 *   - from gfopengpu.library 0.23 (stream v1.8), the same triangle with and
 *     without anti-aliasing (OGPU_PATH_ALIASED: crisp edges);
 *   - a blurred shadow (BLUR) under a square.
 *
 *   OpenGPUVector [FILE]        (default RAM:opengpu-vector.ppm)
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence: your own
 * program built from it is yours to licence as you like. */
#include <exec/types.h>
#include <exec/memory.h>
#include <exec/libraries.h>
#include <dos/dos.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/gfopengpu.h>

static const char version[] = "$VER: OpenGPUVector 1.0 (1.11.2026)";

struct Library *OpenGPUBase;

#define W 160
#define H 100

/* Everything the batch points at, in one block of public memory: the
 * picture, the mask, a glyph, path words, a gradient, PATH_FILL's work. */
struct Memory {
    ULONG picture[W * H];           /* ARGB32: A, R, G, B in memory, as a ULONG on the 68k */
    UBYTE mask[W * H];              /* A8 */
    UBYTE glyph[16 * 16];           /* A8 */
    ULONG path[256];
    ULONG gradient[OGPU_GRAD_WORDS(3)];
    ULONG stream[512];
    ULONG work[W * 32 * 2 / 4];     /* 32 bytes a pixel of the width, two rows' worth */
};

static ULONG *s, *p;                /* the stream and path writers */

static void word(ULONG w) { *s++ = w; }
static void pw(ULONG w) { *p++ = w; }
static void move(LONG x, LONG y) { pw(OGPU_PATH_MOVE); pw((ULONG)x); pw((ULONG)y); }
static void line(LONG x, LONG y) { pw(OGPU_PATH_LINE); pw((ULONG)x); pw((ULONG)y); }
static void cubic(LONG x1, LONG y1, LONG x2, LONG y2, LONG x, LONG y)
{
    pw(OGPU_PATH_CUBIC); pw((ULONG)x1); pw((ULONG)y1); pw((ULONG)x2); pw((ULONG)y2); pw((ULONG)x); pw((ULONG)y);
}
#define PX(v) ((LONG)((v) * 256))       /* a pixel coordinate as 24.8 */

/* A circle as four cubics (24.8). */
static void circle(LONG cx, LONG cy, LONG r)
{
    LONG k = r * 4433 / 8027;           /* 0.5523 r */
    move(cx + r, cy);
    cubic(cx + r, cy + k, cx + k, cy + r, cx, cy + r);
    cubic(cx - k, cy + r, cx - r, cy + k, cx - r, cy);
    cubic(cx - r, cy - k, cx - k, cy - r, cx, cy - r);
    cubic(cx + k, cy - r, cx + r, cy - k, cx + r, cy);
    pw(OGPU_PATH_CLOSE);
}

/* PATH_FILL (or PATH_STROKE: then stroke words follow) of the path from
 * start to p, the identity matrix. */
static void path_cmd(struct Memory *m, ULONG flags, ULONG paint, int mask_slot, ULONG *start, int stroke)
{
    word(OGPU_HDR(stroke ? OGPU_OP_PATH_STROKE : OGPU_OP_PATH_FILL, stroke ? 22 : 16));
    word(flags); word(paint); word(0);
    word((ULONG)mask_slot); word(0);
    word((ULONG)start); word((ULONG)(p - start));
    word(0x10000); word(0); word(0); word(0); word(0x10000); word(0);
    word((ULONG)m->work); word(sizeof m->work);
}

static void build(struct Memory *m, int aliased)
{
    ULONG *start;
    int i;
    s = m->stream;
    p = m->path;
    /* slot 0: the picture, the target; slot 1: the mask; slot 2: the glyph */
    word(OGPU_HDR(OGPU_OP_SURFACE, 6)); word(0); word((ULONG)m->picture); word(W * 4); word(OGPU_XY(W, H)); word(OGPU_FMT_ARGB32);
    word(OGPU_HDR(OGPU_OP_SURFACE, 6)); word(1); word((ULONG)m->mask); word(W); word(OGPU_XY(W, H)); word(OGPU_FMT_A8);
    word(OGPU_HDR(OGPU_OP_SURFACE, 6)); word(2); word((ULONG)m->glyph); word(16); word(OGPU_XY(16, 16)); word(OGPU_FMT_A8);
    word(OGPU_HDR(OGPU_OP_TARGET, 2)); word(0);
    word(OGPU_HDR(OGPU_OP_FILL, 4)); word(OGPU_XY(0, 0)); word(OGPU_XY(W, H)); word(0xFFF0F0F0UL);
    word(OGPU_HDR(OGPU_OP_FILL, 4)); word(OGPU_XY(4, 4)); word(OGPU_XY(40, 24)); word(0xFF3366CCUL);

    /* a five-pointed star, even-odd (its middle stays empty), then its outline */
    start = p;
    {
        static const short pts[5][2] = { { 30, 30 }, { 42, 66 }, { 12, 44 }, { 48, 44 }, { 18, 66 } };
        for (i = 0; i < 5; i++)
            if (i) line(PX(pts[i][0]), PX(pts[i][1])); else move(PX(pts[i][0]), PX(pts[i][1]));
        pw(OGPU_PATH_CLOSE);
    }
    path_cmd(m, OGPU_PD_OVER | OGPU_PATH_EVENODD, 0xFFCC3333UL, 0, start, 0);
    path_cmd(m, OGPU_PD_OVER, 0x80000000UL, 0, start, 1);
    word(3UL << 16);                                    /* width 3 */
    word(OGPU_CAP_ROUND | OGPU_JOIN_ROUND); word(4UL << 16); word(0); word(0); word(0);

    /* the clip: the mask all 255, the circle drawn into it with IN */
    word(OGPU_HDR(OGPU_OP_TARGET, 2)); word(1);
    word(OGPU_HDR(OGPU_OP_FILL, 4)); word(OGPU_XY(0, 0)); word(OGPU_XY(W, H)); word(255);
    start = p;
    circle(PX(85), PX(40), PX(22));
    path_cmd(m, OGPU_PD_IN, 0xFF000000UL, 0, start, 0);
    word(OGPU_HDR(OGPU_OP_TARGET, 2)); word(0);
    /* a gradient from blue to green to yellow, filled over a rectangle, through the mask */
    {
        ULONG *g = m->gradient;
        g[0] = OGPU_GRAD_LINEAR | OGPU_SPREAD_PAD << 8; g[1] = 3;
        g[2] = 0x10000; g[3] = 0; g[4] = 0; g[5] = 0; g[6] = 0x10000; g[7] = 0;
        g[8] = 60UL << 16; g[9] = 0; g[10] = 110UL << 16; g[11] = 0; g[12] = 0; g[13] = 0;
        g[14] = 0; g[15] = 0xFF2040C0UL; g[16] = 0x8000; g[17] = 0xFF20C040UL; g[18] = 0x10000; g[19] = 0xFFE0E020UL;
    }
    start = p;
    move(PX(55), PX(10)); line(PX(115), PX(10)); line(PX(115), PX(70)); line(PX(55), PX(70)); pw(OGPU_PATH_CLOSE);
    path_cmd(m, OGPU_PD_OVER | OGPU_PATH_GRADIENT | OGPU_PATH_MASK, (ULONG)m->gradient, 1, start, 0);

    /* a glyph: an A8 picture drawn in one colour, COMPOSITE_PD with a solid source and the glyph as mask */
    for (i = 0; i < 16 * 16; i++) {
        int x = i % 16, y = i / 16;
        m->glyph[i] = (UBYTE)((x >= 3 && x <= 5) || (y >= 12 && y <= 14 && x >= 3 && x <= 12) ? 255 : 0);   /* an L */
    }
    for (i = 0; i < 4; i++) {
        word(OGPU_HDR(OGPU_OP_COMPOSITE_PD, 8));
        word(OGPU_PD_OVER | OGPU_PD_SOLID | OGPU_PD_MASK); word(0xFF202020UL);
        word(0); word(2); word(OGPU_XY(0, 0));
        word(OGPU_XY(124 + i * 9, 6)); word(OGPU_XY(16, 16));
    }

    /* the same triangle anti-aliased and, from 0.23, aliased */
    for (i = 0; i < 2; i++) {
        start = p;
        move(PX(125 + i * 18) + 77, PX(30)); line(PX(140 + i * 18), PX(60) + 128); line(PX(122 + i * 18), PX(58)); pw(OGPU_PATH_CLOSE);
        path_cmd(m, OGPU_PD_OVER | (i && aliased ? OGPU_PATH_ALIASED : 0), 0xFF008040UL, 0, start, 0);
    }

    /* a shadow, as a browser draws one: the shape's coverage into the A8
     * mask (the clip is done with it), blurred there, then a translucent
     * black through it, then the shape */
    word(OGPU_HDR(OGPU_OP_TARGET, 2)); word(1);
    word(OGPU_HDR(OGPU_OP_FILL, 4)); word(OGPU_XY(0, 70)); word(OGPU_XY(50, 30)); word(0);
    word(OGPU_HDR(OGPU_OP_FILL, 4)); word(OGPU_XY(18, 78)); word(OGPU_XY(14, 14)); word(255);
    word(OGPU_HDR(OGPU_OP_BLUR, 6)); word(OGPU_XY(4, 70)); word(OGPU_XY(42, 30)); word(OGPU_XY(6 * 16, 6 * 16));
    word((ULONG)m->work); word(sizeof m->work);
    word(OGPU_HDR(OGPU_OP_TARGET, 2)); word(0);
    word(OGPU_HDR(OGPU_OP_COMPOSITE_PD, 8));
    word(OGPU_PD_OVER | OGPU_PD_SOLID | OGPU_PD_MASK); word(0xA0000000UL);
    word(0); word(1); word(OGPU_XY(4, 70));
    word(OGPU_XY(4, 70)); word(OGPU_XY(42, 30));
    word(OGPU_HDR(OGPU_OP_FILL, 4)); word(OGPU_XY(14, 74)); word(OGPU_XY(14, 14)); word(0xFFF0A020UL);
}

static int save(struct Memory *m, CONST_STRPTR name)
{
    BPTR f = Open(name, MODE_NEWFILE);
    UBYTE row[W * 3];
    int x, y, ok;
    if (!f)
        return 0;
    ok = FPrintf(f, (CONST_STRPTR)"P6\n%ld %ld\n255\n", (LONG)W, (LONG)H) >= 0;
    for (y = 0; ok && y < H; y++) {
        for (x = 0; x < W; x++) {
            ULONG v = m->picture[y * W + x];       /* opaque here: premultiplied is the colour */
            row[x * 3] = (UBYTE)(v >> 16);
            row[x * 3 + 1] = (UBYTE)(v >> 8);
            row[x * 3 + 2] = (UBYTE)v;
        }
        ok = Write(f, row, sizeof row) == (LONG)sizeof row;
    }
    Close(f);
    return ok;
}

int main(int argc, char **argv)
{
    CONST_STRPTR name = (CONST_STRPTR)(argc > 1 ? argv[1] : "RAM:opengpu-vector.ppm");
    struct Memory *m;
    ULONG fence = 0;
    LONG r;
    int aliased;
    (void)version;
    if (!(OpenGPUBase = OpenLibrary((CONST_STRPTR)OPENGPU_NAME, OPENGPU_VERSION))) {
        Printf((CONST_STRPTR)"OpenGPUVector: no %s\n", (LONG)OPENGPU_NAME);
        return RETURN_FAIL;
    }
    /* stream v1.6 is all or nothing: a back end that answers PATH_FILL takes it all */
    if (OGPU_ANSWER(OGPU_Query(OGPU_OP_PATH_FILL, OGPU_FMT_ARGB32)) == OGPU_NONE) {
        Printf((CONST_STRPTR)"OpenGPUVector: gfopengpu.library %ld.%ld has no stream v1.6\n", (LONG)OpenGPUBase->lib_Version,
               (LONG)OpenGPUBase->lib_Revision);
        CloseLibrary(OpenGPUBase);
        return RETURN_FAIL;
    }
    /* v1.8's OGPU_PATH_ALIASED is a flag, not an opcode: the library's version says */
    aliased = OpenGPUBase->lib_Version > 0 || OpenGPUBase->lib_Revision >= 23;
    if (!(m = AllocVec(sizeof *m, MEMF_PUBLIC | MEMF_CLEAR))) {
        CloseLibrary(OpenGPUBase);
        return RETURN_FAIL;
    }
    build(m, aliased);
    r = OGPU_Submit(m->stream, (ULONG)(s - m->stream), &fence);
    if (fence)
        OGPU_Wait(fence);
    if (r)
        Printf((CONST_STRPTR)"OpenGPUVector: the batch said %ld\n", r);
    else if (!save(m, name))
        Printf((CONST_STRPTR)"OpenGPUVector: can't write %s\n", (LONG)name);
    else
        Printf((CONST_STRPTR)"OpenGPUVector: %s (%s, the second triangle %s)\n", (LONG)name,
               (LONG)OGPU_BackEndName(OGPU_BACKEND(OGPU_Query(OGPU_OP_PATH_FILL, OGPU_FMT_ARGB32))),
               (LONG)(aliased ? "without anti-aliasing" : "anti-aliased: gfopengpu.library is older than 0.23"));
    FreeVec(m);
    CloseLibrary(OpenGPUBase);
    return r ? RETURN_ERROR : RETURN_OK;
}
