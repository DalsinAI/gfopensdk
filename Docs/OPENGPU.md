# opengpu.library in the Open SDK

opengpu.library draws for every Amiga program on OpenRTG: fills, copies,
compositing, scaling, blend modes, and from stream v1.6 vector drawing
(anti-aliased paths, strokes, gradients, patterns, A8 clip masks, blur).
From stream v1.8 (opengpu.library 0.23) paths can be drawn without
anti-aliasing too. It is where OpenBrowser's drawing goes once cairo
leaves it (openamigabrowser `docs/PLAN.md`, step 6): no cairo-like library
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

All of them are copies, gathered by `tools/gather.py` from
DalsinAI/openamigartg at the commit `manifest.json` names (`include/opengpu/`,
`include/proto/`, `include/inline/`, `library/opengpu/opengpu_lib.sfd`,
`sdk/AutoDocs-OpenGPU.md`). Change them there, then move the pin.

`build.h` (C helpers that write the stream) is not copied: its code is
openamigartg's `library/opengpu/ogpu_build.c`, which includes its header by
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
| glyph runs | glyphs drawn once into an A8 cache by `PATH_FILL`, each then a `COMPOSITE_PD` with a solid colour and the cache as mask |
| PNG out (`toDataURL`) | not OpenGPU's: the PNG datatype's `DTM_WRITE` |

Check before using a stream version: `OGPU_Query(OGPU_OP_PATH_FILL, format)`
for v1.6 (a back end that answers it takes all of v1.6),
`OGPU_Query(OGPU_OP_PALETTE, format)` for v1.7, and opengpu.library 0.23 or
later (`lib_Revision`) for v1.8's `OGPU_PATH_ALIASED`, which is a flag, not
an opcode.
