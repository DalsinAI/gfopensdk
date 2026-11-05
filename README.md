# The Open SDK

One kit for one platform to build and port towards and from: headers, function tables, link libraries, autodocs, examples and ACKitchen templates for every Open library. We, 4 October 2026: "one 'platform' to build and port towards and from".

Status, 6 October 2026: phase 1 in progress. The headers and function tables of what exists today (openrtg.library, opensocket.library, accontrol.device, oapspool.device), gathered at pinned commits by `tools/gather.py` from `manifest.json`, plus a Shell command template and a GadTools template. `Docs/PORTING.md` is where to start; `DESIGN.md` is the design.

Also: **OpenNDK** (`OpenNDK/`), our own native developer kit for 68k
AmigaOS 3.x: the C headers, SFD and FD files, proto, inline and pragma
headers, LVO includes and `libamiga.a`, written clean-room, so the open
libraries and third-party software build without the vendor NDK.

Also: **gfopengpu.library** (`Include/gfopengpu/`, `Docs/OPENGPU.md`,
`Examples/opengpu-vector`): the drawing every Open program shares, vector
drawing included (paths, strokes, gradients, patterns, clip masks, blur),
gathered from gfopenrtg like the other headers; and **openfont.library**
(`Include/libraries/gfopenfont.h`, `Docs/gfopenfont.doc`), whose
`OF_DrawGlyphsA` draws text through OpenGPU from its own glyph cache.

Also: **os4compat** (`Lib/os4compat`, `Docs/PORTING-OS4.md`), which builds
AmigaOS 4 source for OS 3.2 by giving each library OS 4's interfaces and
adding the OS 4 calls OS 3.2 lacks.

**Building for the 68040, soft float.** Programs are built with `-m68040`
and no `-m68881`, so one binary runs on a 68040 with or without an FPU; maths
go through the Amiga's mathieee libraries, which use the FPU when there is
one. With bebbo-style m68k-amigaos-gcc, `-m68040` alone still links libnix's
FPU maths (libm881), whose functions return in fp0 where soft-float code
reads d0/d1. Link with the SDK's specs file to get the soft maths:

    m68k-amigaos-gcc -m68040 -specs=$SDK/Lib/m68k-soft-m68040.specs -noixemul ...

The templates and `os4compat.mk` do this for you.

Part of the Open family (internally, the Great Open Source Reunification
Project): one platform, AmigaOS 3.2.x with the Open libraries, that is easy
to set up, and to build and port for.

## SDK 0.2, 5 November 2026

[Docs/LIBRARIES.md](Docs/LIBRARIES.md) lists every part with its version
and pinned commit. New in 0.2: gfopenlayout.library 11, javascript.library,
json.library, unicode.library, weblayout.library, webbrowser.library,
gfopenmedia.library, gfopenmulticore.library, gfopenntlm.library,
pixman.library, elf.library 2.0, gfopenservice.device, GFOpenDatatypes'
class headers, GFOpenGfx's graphics and layers calls and GFOpenExec's atomic
calls; every older part moved to its library's current main (gfopengpu.library
0.26 with retained surfaces and the batch builders, gfopenfont.library 1.7).
`Lib/build.sh` builds `libopensdk.a`, a stub for every call in `SFD/`.

## SDK refresh, 24 October 2026

[The SDK/NDK audit](Docs/SDK-AUDIT-20261024.md) records current interface pins,
OpenNDK compatibility checks and the isolated OpenAmigaCurl overlay builder.
OpenBrowser's curl port already exists; the overlay makes that dependency
available to other builds without replacing an active stove or runtime.
It does not provide a curl Shell command or certify every library.

## Licence

MIT, Copyright (c) 2026 AmiCradle Team (`LICENSE`), for our own files.
Third-party code keeps its own licence (see `DESIGN.md`).

If you use or build on this work, we ask (we do not require) that you credit
the AmiCradle Team, for example "based on The Open SDK by the AmiCradle
Team".

## Contributors

The Open SDK is created and maintained by [SacredTrees](https://github.com/SacredTrees) with The AmiCradle Team, copyright AmiCradle Team. Everyone whose work it includes is credited in [`CONTRIBUTORS.md`](CONTRIBUTORS.md).
