# bzip2.library 1.0

`bzip2.library` is libbzip2, the library of upstream bzip2 1.0.8, as a shared AmigaOS library. Every program that compresses or unpacks bzip2 data can open it instead of carrying its own copy. The calls work the way libbzip2's documentation (upstream's `manual.html`) says, and give the same answers.

## Two ways to use it

- **The link stub.** Include upstream's `<bzlib.h>` and link `libbz2.a` with `-lbz2`. A port that already uses libbzip2 links unchanged. The stub opens `bzip2.library` version 1 at the first call and closes it when the program ends. If the library can't be opened, every call answers `BZ_CONFIG_ERROR`, and `BZ2_bzlibVersion` answers `""`.
- **The library itself.** Use `<proto/bzip2.h>` with `BZip2Base` from `OpenLibrary("bzip2.library", 1)`. The `strm` argument is a `bz_stream *` from `<bzlib.h>`.

| Library call (offset) | libbzip2 call | Registers |
| --- | --- | --- |
| `BZ2CompressInit` (-30) | `BZ2_bzCompressInit` | a0, d0, d1, d2 |
| `BZ2Compress` (-36) | `BZ2_bzCompress` | a0, d0 |
| `BZ2CompressEnd` (-42) | `BZ2_bzCompressEnd` | a0 |
| `BZ2DecompressInit` (-48) | `BZ2_bzDecompressInit` | a0, d0, d1 |
| `BZ2Decompress` (-54) | `BZ2_bzDecompress` | a0 |
| `BZ2DecompressEnd` (-60) | `BZ2_bzDecompressEnd` | a0 |
| `BZ2BuffToBuffCompress` (-66) | `BZ2_bzBuffToBuffCompress` | a0, a1, a2, d0, d1, d2, d3 |
| `BZ2BuffToBuffDecompress` (-72) | `BZ2_bzBuffToBuffDecompress` | a0, a1, a2, d0, d1, d2 |
| `BZ2LibVersion` (-78) | `BZ2_bzlibVersion` | |

`include/sfd/bzip2_lib.sfd` is the source of truth for this table.

## What to know

- **Memory.** A `bz_stream` whose `bzalloc` and `bzfree` are 0 gets its memory from `AllocVec(MEMF_ANY)`. Compressing at block size 9 takes about 7.6 MB. Decompressing takes about 3.7 MB, or about 2.3 MB with `small` set. These are upstream's figures (`manual.html`, 2.2).
- **Stack.** Compressing needs about 12 KB of the caller's stack. When the caller has less than 32 KB free, `BZ2Compress` and `BZ2BuffToBuffCompress` run on a 32 KB stack of the library's own, through exec's `StackSwap`, so a program with the default 4 KB stack still works. If that stack can't be allocated, they answer `BZ_MEM_ERROR`. Decompressing runs on the caller's stack.
- **Tasks.** The library keeps nothing between calls except its base, so any number of tasks can use it at once, each with its own `bz_stream`.
- **No floating point, no C library.** The library and the stub are built `-m68040 -msoft-float`, and the build fails if either one has a floating-point routine.
- **Not in version 1:** libbzip2's FILE calls (`BZ2_bzopen`, `BZ2_bzReadOpen`, `BZ2_bzWrite` and the rest), because a shared library has no C library to give them a FILE. Use the stream calls instead.
- `verbosity` is taken but nothing is printed, because the library is built with `BZ_NO_STDIO`.
