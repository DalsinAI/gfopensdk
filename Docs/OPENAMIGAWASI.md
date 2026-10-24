# OpenAmigaWASI SDK integration

Owner direction, 24 October 2026: maintain an upstream-derived WASI project
under the OpenAmigaWASI name, fix verified Amiga issues, and package its usable
artifacts through the Open SDK. Keep the downstream difference small. This is
not an instruction to write a new WebAssembly-to-C converter.

## Current status

Integration scope only. No OpenAmigaWASI fork, native library, SDK manifest pin,
resident library or NDK ABI has been created or qualified by this document.
Uploads remain paused. Existing Civ II compatibility code is experimental.

## Two build boundaries

1. The WASI SDK 25 sysroot supplies wasi-libc when the game is compiled to
   WebAssembly. wasm2c subsequently converts that linked library together with
   the application. Patches here require rebuilding the WebAssembly module and
   regenerating C; adding a native archive at the final link does not replace
   those already-converted functions.
2. A native WASI import implementation serves the converted program's file,
   directory, clock, argument and environment calls. This is the component that
   can be built as a 68040 archive and linked from the Open SDK. It must adapt
   generated import names and memory access without importing game-specific
   global state into a shared library interface.

Keep the WASI guest library and native import implementation distinct, even
when their source pins, patches, build tools and tests are maintained together.
Graphics, audio and input continue through the existing Open/SDL interfaces;
WASI does not replace those interfaces.

## Packaging and dependencies

Use the SDK's existing Include/, Lib/ and Docs/ layout. A proposed static
archive is Lib/libopenamigawasi.a with public headers under
Include/openamigawasi/. These names are provisional until the first build and
consumer integration establish the interface. No linker invocation is claimed
working yet. The target is the verified GCC 16.2.0-open3 68040/FPU stove.

Build native OS calls against OpenNDK and existing framework interfaces. Do not
copy upstream libc into OpenNDK's clean-room OS headers. Do not invent library
vectors, an SFD or a ROM requirement for a static implementation. If a resident
openamigawasi.library becomes justified later, its actual interface needs its
own versioning, tests and SDK/NDK integration.

Retain upstream licences and notices. Record the exact wasi-libc revision used
by WASI SDK 25 before forking or modifying it. Pin every native dependency and
compiler input. Keep WABT upstream with the existing checked compatibility
patches; a converter fork is outside this scope.

## Qualification before SDK admission

Prove little-endian scalar access and memory-growth behaviour on big-endian
68040 hosts, including unaligned and boundary cases. Check every guest buffer
and result region before host I/O. Define instance state, descriptor ownership,
short reads/writes, invalid descriptors, Amiga volume paths, directory records,
clock units, environment, traps and teardown. Test each supported WASI import;
reject or return the specified error for unsupported behaviour.

Use tiny data-free fixtures as well as Civ II. Compare AC090 with the
independent 68040 using the same compiler where possible; record the remaining
OS, headers, linker and libc differences. Package only verified artifacts with
source/build hashes, examples and a licence receipt, then add an exact source
pin and artifact hashes to manifest.json through the existing gather workflow.

## Civ II blocker is separate

The current Amiga replay fails when converted printf_core calls __fwritex.
The captured guest stream is filled with repeated CF CF CF 00 bytes and its
callback index is 0x00CFCFCF, beyond a 774-entry function table. A subsequent store watch and stack/disassembly capture identified the write
in the reconstructed Win32/GDI `xfer_row` function (src/platform/gdi.c): it
stores the grey pixel value over the guest stream callback. Why its graphics
destination points there remains unresolved. This does not prove a wasi-libc
defect. Fix and regress the original overwrite before calling a
fork, replacement adapter or SDK package a solution to the game failure.
