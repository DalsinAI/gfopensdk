# The Open SDK

We, 4 October 2026: "one 'platform' to build and port towards and from",
and "that was the bones of my NDK / SDK question". The Open SDK is the kit
for that platform: AmigaOS 3.2.x with the Open family. The same sources also
build for AROS 68k, and later for OS 4. It answers the mission test too: a
newcomer builds a working program from a template without reading anything
first.

## 1. What it is, and isn't

- **One download**, with everything needed to use every Open library:
  headers, function tables, link libraries, autodocs, examples, and
  ACKitchen templates.
- **OpenNDK replaces NDK 3.2** (`OpenNDK/`, 15 October 2026): our own
  headers, function tables and `libamiga.a` for 68k AmigaOS 3.x, so nothing
  we build needs the vendor's kit. NDK 3.2 stays useful only as a test
  oracle (`OpenNDK/check/compare_ndk.sh`).
- **Beside the other OS kits, never instead of them.** These have their own
  licences and the user supplies them, as AmigaChrome's stoves already
  require:
  - the AROS SDK;
  - the OS 4.1 SDK;
  - MUI's SDK.
- **No compilers.** They are the stoves (GCC 6.5 and GCC 16 for m68k, the
  AROS crosstools; `DalsinAI/amigachrome-stoves` holds our GPL patches).
  ACKitchen sets them up.

## 2. What's in it

| Folder | Holds |
| --- | --- |
| `Include/` | Each Open library's headers, with `proto/`, `inline/` and `pragmas/` for GCC (vbcc later): `openrtg/` (modes, OS 4's RTG calls, the `os4` header), `opengpu/`, `opensocket/` (beyond the standard bsdsocket calls), `openmedia/`, `opengadtools/`, `openprint/` (oapspool.device), `openmulticore/`, `accontrol/` (clipboard, files, pace). Also: Zune's `mui.h` for `zunemaster.library` (AROS Public License), AROS's `gl/gla.h` (APL), SDL 2 and 3 (Zlib), and Mesa's GL (MIT) |
| `SFD/`, `FD/` | Each library's function table |
| `Lib/` | Link libraries: static SDL, our glue, and stubs that open each library automatically, as libnix does for the OS's. `Lib/os4compat`: OS 4's interfaces and calls for OS 3.2, made from the NDK's SFD files at build time (`Docs/PORTING-OS4.md`). `Lib/m68k-soft-m68040.specs`: the soft-float 68040 link, used by the templates and os4compat |
| `Autodocs/` | One per library, generated from the sources' comments |
| `Examples/` | One small program per library, each building for OS 3.2 and AROS |
| `Templates/` | ACKitchen project templates: a Shell command, a GadTools app, a Zune (MUI-style) app, an SDL app, a GL app, a library, a device, a datatype, and an Installer package with its Aminet readme. Each builds two binaries, OS 3.2 and AROS: separate binaries, no `#ifdef` maze |
| `Docs/` | Porting notes: from AROS, from OS 4, from Linux and SDL. The platform's rules: set FPCR to 0 when doubles matter (OS 3.2.3's ROM `mathieeesingbas` sets single precision in each task that opens it); a stack of its own through `StackSwap` (libnix ignores `__stack`); `-fno-common` for library bases |

On an Amiga it lives under an `SDK:` assign, beside `NDK:`. That follows the
assign convention amigazen's ToolKit uses; its conventions are followed and
nothing is copied. ACKitchen mounts it into instances (the tools drive idea).

## 3. Rules

- **Published interfaces only, under names that port:** OS 4's RTG calls by
  name, the standard bsdsocket numbers, MUI's function table through Zune,
  AROS's GLA calls. Nothing of our own where a published interface exists.
- **Never break.** A published call, structure, tag or ID never changes
  meaning. New things are added at the end, as OpenRTG's ModeID table is.
- **Each library's repository owns its headers and function tables.** The
  SDK repository gathers them at pinned commits, as amigachrome pins its
  vendored copies. A manifest lists each library's commit and version under
  one SDK version.
- **CI builds every example and template** for OS 3.2 and AROS. One that
  doesn't build is a broken SDK.

## 4. Licences

- **The SDK repository's own files are MIT,** Copyright (c) 2026 AmiCradle
  Team.
- **Headers keep their library's licence:**
  - ours: MIT;
  - Zune's and GLA's: the AROS Public License;
  - SDL: Zlib;
  - Mesa: MIT.
- **Not shipped:** the compilers and the OS kits.

## 5. Phases

| Phase | Delivers | Done when |
| --- | --- | --- |
| 1 | The layout, the manifest, and what exists today: OpenSocket (bsdsocket and opensocket.library), accontrol.device, oapspool.device, OpenRTG's `modes.h`. Templates: a Shell command and a GadTools app. An Aminet readme (dev/misc) | In ACKitchen, a newcomer builds both templates for OS 3.2 and AROS with no setup, and they run in instances |
| 2 | Each Open library as it lands: openrtg.library, opengpu, OpenGadTools, zunemaster.library, OpenMedia, OpenMulticore | Each has an example that builds for both |
| 3 | SDL 2 and 3, Mesa with GLA; the SDL and GL templates | An SDL game and a GL demo build from the templates |
| 4 | OS 4 (ppc-amigaos) builds for the libraries that have them; vbcc | An example builds for OS 4 unchanged |

**Repository:** `DalsinAI/openamigasdk`.
