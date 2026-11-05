The Open SDK 0.2, 5 November 2026: every Open library's current interface.

New: gfopenlayout.library 11, javascript.library, json.library,
unicode.library, weblayout.library, webbrowser.library,
gfopenmedia.library, gfopenmulticore.library, gfopenntlm.library,
pixman.library, elf.library 2.0, gfopenservice.device, GFOpenDatatypes'
class headers, GFOpenGfx's graphics and layers calls and GFOpenExec's
atomic calls, each with its headers, SFD/FD, LVO includes and autodocs
where it has them.

Updated: every older part to its library's current main, among them
gfopengpu.library 0.26 (retained surfaces, the batch builders,
OGPU_OP_DWT_INV) and gfopenfont.library 1.7 (OF_DrawGlyphsA).

`Lib/build.sh` builds `libopensdk.a`, a stub for every call in `SFD/`
(395). OpenNDK matches today's OS libraries: 73 SFDs, 0 differences.

What's in it, part by part: `Docs/LIBRARIES.md`. Start with `Docs/PORTING.md`.

MIT, Copyright (c) 2026 AmiCradle Team. Designed, tested and delivered by The AmiCradle Team.
