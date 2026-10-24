# Checked Win32 bitmap support, 0.1

The SDK's first `win32compat` component is a portable C bitmap core, not a
complete implementation of Win32, GDI, Wine or a Windows executable loader.
It was written for the Open SDK; no Wine implementation or test code is
incorporated. Wine's GDI clipping implementation and bitmap tests are useful
behaviour references:

- https://github.com/wine-mirror/wine/blob/master/dlls/win32u/dibdrv/bitblt.c
- https://github.com/wine-mirror/wine/blob/master/dlls/gdi32/tests/bitmap.c

## Supported operations

`Include/win32compat/bitmap.h` declares checked bitmap views, row addressing,
clipped unscaled copies and rectangular fills. Supported pixel formats are
8-bit palette indices and four-byte B,G,R,X pixels. The latter is a byte-defined
format on little- and big-endian CPUs; fill takes `0x00RRGGBB` and writes X=0.
Palette lookup and colour conversion are outside this first component.

`OW32_BitmapFromDIB` decodes a caller-supplied little-endian
BITMAPINFOHEADER of at least 40 bytes, with one plane, BI_RGB and 8/32 bpp.
It checks header length, signed dimensions, DWORD-aligned pitch and the supplied
pixel allocation. Positive heights use bottom-up rows and negative heights
use top-down rows. It does not use the screen size, window size or viewport to
infer the bitmap size. A scrollable backing bitmap may be larger than all of
them. `biSizeImage` is not used to establish ownership or allocation size.

Views record the real allocation size separately from width, height, row-zero
offset and signed byte stride. Every public operation revalidates the view
before accessing pixels. Rectangles are clipped jointly against both surfaces
with wide coordinate arithmetic. Invalid metadata is rejected before writes.
Copies within the same layout support horizontal and vertical overlap,
including negative pitch. Other overlapping allocation views return
`OW32_ALIAS`; they need a separate conversion/staging operation.

The caller must provide a live allocation of the stated size and own the
view throughout each operation. This interface cannot prove that an arbitrary
pointer is live, detect a false allocation size, prevent concurrent mutation,
or validate Win32 object handles. Those checks belong in the consuming handle
and surface registry. The byte ranges passed to this API must be truthful.

Unsupported formats, compressed DIBs, palettes, scaling/mirroring, raster
operations beyond raw SRCCOPY, window/DC lifetime and Win32 handle APIs are
not claimed. Extend this same component with tested behaviour when needed;
do not silently route unsupported operations through unchecked writes.

## Building and linking

Use the verified GCC 16.2.0-open3 68040/FPU stove. The isolated overlay builder
uses the SDK's existing compiler-provenance check and creates no network
requests or changes to the active stove:

```sh
python3 tools/build_win32compat.py --stove /path/to/verified-stove --out /new/empty/output
m68k-amigaos-gcc -m68040 -m68881 -mcrt=nix20 -I/output/sdk/Include \
    consumer.c -L/output/sdk/Lib -lwin32compat -o consumer
```

The output includes the native archive, public header, portable source, native
test executable and source/compiler/artifact receipt. The code uses no Amiga
OS calls and introduces no resident library, SFD, NDK interface or ROM change.
Portable source is supplied so a WebAssembly-stage consumer can build the same
core for its own target; a native m68k archive cannot be linked into a wasm32
module. Such a WebAssembly integration is not qualified yet.

## Checks and admission gates

`sh tests/sdk/win32compat/run.sh` compares 2,000 deterministic copy cases with
an independent per-pixel reference, checks guards and untouched padding,
negative strides, overlap, extreme coordinates, malformed metadata,
little-endian headers and a 2048x1024 bitmap feeding a 640x480 viewport.
The runner accepts `CC`, `TEST_CFLAGS` and `TEST_RUNNER` for cross execution.
Host ASan/UBSan and independent big-endian 68040 execution are included in CI,
and the pinned Open3 job builds the real Amiga archive and links its tests.
CI additions have not run remotely while uploads are paused.

Native execution results and hashes belong in the overlay receipt/evidence;
a successful build alone is not an AC090 runtime pass. Civ II still needs
consumer integration and the fixed-save city/research/save/two-turn replay.
Its confirmed `xfer_row` overwrite is not fixed merely by adding this archive
or rejecting the bad write: the surface dimensions, backing allocation,
stride, origin and original wrong-address calculation must be established.

## Local qualification, 24 October 2026

The archive-linked Amiga test passes on the isolated AC090 lab (RC0).
The same test/library C passes on the independent QEMU 68040 with both GCC15
and the exact GCC 16.2.0-open3 compiler (Linux headers and CRT/libc for QEMU).
Host ASan/UBSan tests pass; leak detection was disabled locally because the
sandbox does not support LeakSanitizer's ptrace operation. The C/C++ public
headers, existing SDK unit/host tests and offline gather receipts also pass.
Hashes, compiler flags and scope are recorded in
`tests/sdk/win32compat/qualification-20261024.json`. No active stove was changed,
no remote CI run is claimed and no Civ II consumer pass is claimed.
