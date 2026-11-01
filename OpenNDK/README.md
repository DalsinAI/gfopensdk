# OpenNDK

An open native developer kit for 68k AmigaOS 3.x: the C headers, function
tables and link library a program needs to build, written from the
published interface and owned by the Team. It sits in The Open SDK beside
the Open libraries' own headers, so the open libraries, the boot-disk
commands and third-party software can be built with no vendor NDK.

MIT, Copyright (c) 2026 AmiCradle Team. What it may and may not be written from
is in [CLEAN-ROOM.md](CLEAN-ROOM.md); how to add to it is in
[CONTRIBUTING.md](CONTRIBUTING.md).

## What's in it

| Folder | Holds |
| --- | --- |
| `Include_H/` | The C headers, under the OS's own paths (`exec/`, `dos/`, `graphics/`, `intuition/`, `utility/`, `libraries/`, `devices/`, `hardware/`, `resources/`, `workbench/`, `datatypes/`, `rexx/`, `diskfont/`, `prefs/`, and ReAction's `gadgets/`, `images/`, `classes/` and `reaction/`) |
| `Include_H/sys/`, `netinet/`, `arpa/`, `net/`, `netdb.h`, `libraries/bsdsocket.h`, `amitcp/` | bsdsocket.library's headers and `SFD/bsdsocket_lib.sfd`: OpenSocket's own (DalsinAI/openamigasocket `sdk/`), copied by `tools/gather.py` at the commit `manifest.json` pins. Change them there, never here |
| `Include_H/proto/`, `clib/`, `inline/`, `pragmas/` | Generated from the SFDs: the header a program includes, the prototypes, GCC inline calls and SAS/C-style pragmas. `inline/macros.h` gives the LPn macros for hand-written inline headers |
| `Include_I/lvo/` | Generated `_LVO` equates for assembler |
| `SFD/`, `FD/` | Each library's calls: the SFDs are written by hand, the FDs generated |
| `lib/` | `libamiga.a`: a stub for every call (including the varargs forms such as `OpenWindowTags`) and the classic helpers (`NewList`, `CreatePort`, `CreateExtIO`, `CreateTask`, `BeginIO`, `DoMethod` and the other BOOPSI helpers, `HookEntry`, `CallHook`, `FastRand`, `RangeRand`, the `Lib*Pool` calls, `TimeDelay`, `ArgArrayInit` and friends, `HotKey`) |
| `tools/` | `ndkgen.py`, the generator; `mkmacros.py` for `inline/macros.h` |
| `tests/` | `run.sh`: the cloud tests, needing only an m68k GCC |
| `check/` | `compare_ndk.sh`: the full comparison with a vendor NDK where one is installed; `check_lvo.py`: the SFDs against the open libraries' `.lvo` tables |

The layout follows the vendor NDK's (`Include_H`, `Include_I`, `SFD`,
`FD`), so a stove can point at OpenNDK where it pointed at `ndk/`.

## Using it

With the os32-gcc16 stove (GCC 16 for m68k-amigaos):

```sh
sh OpenNDK/lib/build.sh                     # makes lib/build/<prefix>/libamiga.a
m68k-amigaos-gcc -nostdinc -isystem "$(m68k-amigaos-gcc -print-file-name=include)" \
    -I OpenNDK/Include_H -m68040 -O2 -fomit-frame-pointer -c prog.c
```

When you link against libnix, add the SDK's soft-float specs file
(`-specs=<SDK>/Lib/m68k-soft-m68040.specs`, an absolute path): without it
`-m68040` links libnix's FPU maths, which soft-float code can't call
(see the SDK's README).

`-nostdinc` keeps a vendor NDK installed in the compiler's own search path
out. A C library (libnix, clib2) brings its own `stdio.h` and friends:
put its include folder after OpenNDK's.

The inline calls bind the library base to `a6`, so code using them needs
a frame pointer other than `a6`: `-fomit-frame-pointer`, or the amigaos
GCC's default (`a5`). A call's base can be swapped by defining
`<LIBRARY>_BASE_NAME` (for example `INTUITION_BASE_NAME`) before including
its `proto/` header, and `__NOLIBBASE__` leaves out the base's declaration.
`__OPENNDK_NO_INLINE__` uses the stubs in `libamiga.a` instead of inlines.

## Windows in HTML and CSS

OpenLayout UI (`DalsinAI/openamigalayout`, `docs/OpenLayout-UI.md`; the
SDK's `Docs/OPENLAYOUT-UI.md`) builds with OpenNDK's headers alone: its
Intuition glue uses exec, dos, graphics, layers, intuition and diskfont
from `Include_H/`, and cybergraphics.library through `inline/macros.h`'s
LP macros, as OpenGadTools does. Its sources were checked against
`Include_H/` (`-fsyntax-only`, 30 October 2026). Add OpenLayout's
`include/` after OpenNDK's:

```sh
m68k-amigaos-gcc -nostdinc -isystem "$(m68k-amigaos-gcc -print-file-name=include)" \
    -I OpenNDK/Include_H -I <openamigalayout>/include -m68040 -O2 -fomit-frame-pointer \
    -c prog.c
```

## Status, 15 October 2026

- **Written:** 220 C headers in the OS's own paths and 77 SFDs: exec, dos,
  graphics, layers, intuition, utility, gadtools, asl, icon, workbench,
  expansion, the other disk libraries (amigaguide, commodities, datatypes,
  diskfont, iffparse, keymap, locale, lowlevel, the six math libraries,
  nonvolatile, realtime, rexxsyslib, translator, bullet), the devices and
  resources with calls, and the ReAction classes. With the generated files,
  530 headers in all.
- **Checked here** (`tests/run.sh`, about 20 minutes): every header compiles
  alone in C and C++ and all together in one unit; 89 structure sizes that
  the open libraries' own tests measured against NDK 3.2; a program's calls;
  `libamiga.a` (1,278 objects). 73 SFDs match the open libraries' `.lvo`
  tables with no difference; icon, workbench, input and translator have no
  table to compare with yet.
- **Checked against NDK 3.2** (`check/compare_ndk.sh`, run four times on
  Daletop on 15 October; reports in `check/results/`). The SFDs match in
  every call's name, offset and registers; the types of some 170 calls
  were brought into line along the way, and the calls and SFDs OpenNDK
  lacked were added. The fourth run measured both header sets' structures
  and constants with the os32 stove's GCC (`check/shim/` supplies the
  `<stdint.h>` the NDK's `exec/types.h` wants) and listed the NDK's own
  field layouts. Since then the 53 structure differences it found are
  fixed (`Layer`, `Layer_Info`, `ClipRect`, `CopList`, `GfxBase`,
  `EasyStruct`, `IControlPrefs`, `WorkbenchPrefs`, `XRef`,
  `TDU_PublicUnit` and others), and its 62 missing structures, 1,362
  missing constants and 11 of its 14 missing headers are added, each
  checked against that run's figures; a fifth run on Daletop is what
  confirms them. Still
  open: `dos/ansiio.h`, `resources/ciabase.h`,
  `reaction/reaction_author.h` and the TextEdit
  `filetypes.h`. OpenNDK keeps `struct DiscResourceUnit` in `GetUnit`,
  which the NDK's SFD names differently; it is the same layout. Timer's
  calls take `TimeVal_Type`, and `devices/timer.h` works beside a C
  library's own `struct timeval` (`_TIMEVAL_DEFINED`,
  `__USE_NEW_TIMEVAL__`). `reaction/reaction_macros.h`
  defines `CheckMark` as the NDK's does, so a unit that includes it can't
  name the `CheckMark` field of `struct Window` either.
- **Not yet written:** the assembler structure includes (`Include_I` other
  than `lvo/`), `debug.lib`, autodocs, vbcc's inline headers, and the
  OS 4.1 headers (OS 4.1 builds keep using Hyperion's SDK for now).
- **Beyond the vendor NDK:** `gadgets/piechart.h`, the GETCOLOR box tags
  (`GETCOLOR_LeftEdge` to `GETCOLOR_Height`, at +40 to +43) and
  `mmu_lib.sfd` (MMULib's mmu.library) are OpenNDK's own, read from the
  open libraries in amigachrome-guest; the 3.2 NDK has none of them.
