# opengpu.library in the Open SDK

opengpu.library draws for every Amiga program on OpenRTG: fills, copies,
compositing, scaling, blend modes, and from stream v1.6 vector drawing
(anti-aliased paths, strokes, gradients, patterns, A8 clip masks, blur).
From stream v1.8 (opengpu.library 0.23) paths can be drawn without
anti-aliasing too, and from opengpu.library 0.24 a back end says which of
the commands' flags it takes (`OGPU_QUERY_FLAG`, below). It is where OpenBrowser's drawing goes once cairo
leaves it (gfopenbrowser `docs/PLAN.md`, step 6): no cairo-like library
sits on top; a program writes the stream itself.

## What is here

| File | What |
| --- | --- |
| `Include/opengpu/opengpu.h` | the library's calls and `OGPU_Query`'s answers |
| `Include/opengpu/stream.h` | the command stream: every opcode, its words, the formats, operators, paths, gradients, patterns, and what each stream version added |
| `Include/opengpu/stream3d.h` | the 3D commands (`TRIANGLES` and the rest) |
| `Include/opengpu/module.h`, `gfx.h` | modules (SDL2.module, GL.module) and OpenGfx's calls |
| `Include/proto/opengpu.h`, `Include/inline/opengpu.h` | GCC's calls |
| `SFD/opengpu_lib.sfd`, `FD/opengpu_lib.fd` | the function table, for other compilers |
| `Docs/AutoDocs-OpenGPU.md` | the library's documentation |
| `Examples/opengpu-vector` | one batch: a path, a stroke, a clip mask, a gradient through it, a glyph from an A8 picture, an aliased triangle, a blurred shadow |
| `Include/libraries/openfont.h`, `Include/proto/openfont.h`, `Include/inline/openfont.h`, `Include/clib/openfont_protos.h`, `Include/pragmas/openfont_pragmas.h`, `SFD/openfont_lib.sfd`, `FD/openfont_lib.fd`, `Docs/openfont.doc` | openfont.library, whose `OF_DrawGlyphsA` (1.5) draws glyph runs through OpenGPU from its own glyph cache |

All of them are copies, gathered by `tools/gather.py` from
DalsinAI/gfopenrtg at the commit `manifest.json` names (`include/opengpu/`,
`include/proto/`, `include/inline/`, `library/opengpu/opengpu_lib.sfd`,
`sdk/AutoDocs-OpenGPU.md`), and openfont's from DalsinAI/gfopenfont
(`sdk/`, where its `ndkgen.py`-made files are). Change them there, then move
the pin.

`build.h` (C helpers that write the stream) is not copied: its code is
gfopenrtg's `library/opengpu/ogpu_build.c`, which includes its header by
a path inside that repository. A program can write the words itself, as the
example does: each command is its header word (`OGPU_HDR(op, words)`) and
the words `stream.h` lists, big-endian, which is a `ULONG` on the 68k.

## How a browser draws on it

What WebCore asked of cairo, and the stream commands that do it:

| WebCore | OpenGPU |
| --- | --- |
| `fillRect` of one colour, `clearRect` | `FILL`, or `COMPOSITE_PD` with `OGPU_PD_SOLID` for the other operators |
| `fillPath`, `strokePath` (caps, joins, dashes) | `PATH_FILL`, `PATH_STROKE` |
| shapes with `setShouldAntialias(false)`, SVG `crispEdges` | the same with `OGPU_PATH_ALIASED` (v1.8, 0.23) |
| linear, radial, conic gradients | `OGPU_PATH_GRADIENT` paint |
| images under a transform, patterns (repeat, reflect, pad) | `OGPU_PATH_PATTERN` paint |
| `clip` to a path, `clipOut`, rounded clips | an A8 surface filled with 255, each clip path drawn into it with `OGPU_PD_IN` (clip-outs with `OGPU_PD_OUT_REVERSE`), then `OGPU_PATH_MASK` or `COMPOSITE_PD`'s mask |
| copy and clear bounded by a path (cairo's) | `OGPU_PD_OUT_REVERSE` with an opaque paint, then `OGPU_PD_ADD` with the paint |
| shadows | the shape's coverage into an A8 surface, `BLUR`, then a colour through it |
| transparency layers | drawing into an ARGB32 surface of their own, then `COMPOSITE_PD` with `OGPU_PD_MASK_SOLID` (opacity) and the layer's operator or blend mode |
| glyph runs | openfont.library's `OF_DrawGlyphsA` (1.5): its glyph cache, inside the library, fills each glyph once into an A8 page by `PATH_FILL`, then draws each use as a `COMPOSITE_PD` with a solid colour and the page as mask (a clip mask too; a matrix fills each outline where it lies) |
| PNG out (`toDataURL`) | not OpenGPU's: the PNG datatype's `DTM_WRITE` |

Check before using a stream version: `OGPU_Query(OGPU_OP_PATH_FILL, format)`
for v1.6 (a back end that answers it takes all of v1.6),
`OGPU_Query(OGPU_OP_PALETTE, format)` for v1.7. v1.8's `OGPU_PATH_ALIASED`
is a flag, not an opcode: ask for it with the flag query below.

## Which flags a back end takes: `OGPU_QUERY_FLAG` (opengpu.library 0.24)

A newer flag on an older command (such as v1.8's `OGPU_PATH_ALIASED` on
`PATH_FILL`) can't be asked about with an opcode, and a back end that
doesn't know a flag ignores it, drawing something else. So `OGPU_Query`
takes a second form:

    answer = OGPU_Query(OGPU_QUERY_FLAG(OGPU_OP_PATH_FILL, OGPU_PATH_ALIASED_BIT), format);

`OGPU_QUERY_FLAG(op, bit)` is `0x01000000 | bit << 16 | op`. That number is
never an opcode, so opengpu.library before 0.24, and any driver that doesn't
know the form, answers `OGPU_NONE`: "not taken", which is the safe answer
(draw without the flag, or another way). From 0.24 the CPU back end answers
`OGPU_FULL` for the flags of `PATH_FILL` and `PATH_STROKE` it draws (bits 8
to 14), and the library asks a driver the same question when it loads it:
a driver that answers `OGPU_NONE` has its aliased paths drawn by the CPU,
so a program may set the flag once it has asked, whoever draws.
`stream.h` has `OGPU_QUERY_IS_FLAG`, `OGPU_QUERY_FLAG_OP` and
`OGPU_QUERY_FLAG_BIT` for a driver taking the form apart.

## Gradient stops with different alphas

OpenGPU interpolates between gradient stops in premultiplied colour, as CSS
(CSS Images 3, "premultiplied" interpolation) and browsers do: a stop that
is transparent contributes no colour, so red to transparent fades red,
not through grey. cairo (pixman) interpolates unpremultiplied, so where two
neighbouring stops differ in alpha the colours between them differ from
cairo's (equal-alpha stops draw the same). This is the behaviour the Open
stack keeps (Dale, 1 November 2026); WebCore's own gradients expect it, and
tests comparing against cairo allow for it.
