# lzma.library 1 (GFOpenLZMA)

LZMA and LZMA2 decoding for AmigaOS 3.x, raw and in `.lzma` and `.xz` files. It is the shared decoder for 7z readers, PhysicsFS, GFOpenCompress and ports, in place of each one's copy of the LZMA SDK or xz's liblzma.

**Host first.** The decoding is amicradle-guest's hostlib call `LZMA_DECODE_ALL` (`$00010182`, HOSTLIB-ABI.md). On AmiCradle it runs as host code, at or above the system liblzma's speed. On any other 68k, the library runs the same decoder's 68k body, which needs fewer 68040 instructions than the LZMA SDK's. CRC-32 is AC090's helper, chosen the same way. CRC-64 is the library's own.

Clean room, from the formats' published descriptions. No floating point, no C library. Memory comes from `AllocVec`, about 16-28 KB for each call, freed before it returns. Nothing is kept between calls, so any number of tasks may call it at once.

## Opening it

```c
#include <proto/lzma.h>
struct Library *LzmaBase = OpenLibrary(LZMANAME, LZMA_VERSION);
```

Alternatively, link the stub: `#include <gfopenlzma.h>` and `-lgflzma`. It gives `lzma_decode()`, `lzma_alone_info()`, `lzma_alone_decode()`, `xz_info()`, `xz_decode()` and `lzma_error_text()`. The stub opens the library at the first call and closes it at exit. When it can't open the library, every call answers `LZERR_NOLIB`.

Every call takes the whole input and writes the whole output in one go: no streaming. `done`, when not NULL, gets two longs: `done[0]` is the bytes written and `done[1]` is the bytes read. Each call answers `LZERR_NONE` (0) or a reason, from `<libraries/lzma.h>`.

| Answer | Meaning |
| --- | --- |
| `LZERR_DATA` | The data is damaged. |
| `LZERR_SHORT` | The input ended first. |
| `LZERR_ROOM` | There is more output than `outLength`. |
| `LZERR_PARAM` | The mode or props are not ones the call takes. |
| `LZERR_NOMEM` | There is no memory for the decoder. |
| `LZERR_FORMAT` | The input is not a `.lzma` or `.xz` file. |
| `LZERR_CHECK` | An `.xz` block's CRC-32 or CRC-64 is wrong. |
| `LZERR_UNSUPPORTED` | The `.xz` file uses something version 1 does not take: a BCJ or delta filter, or a SHA-256 check. |
| `LZERR_SIZE` | The output would be over 1 GB. |

## The calls

**`LONG LzmaDecode(ULONG mode, ULONG props, CONST_APTR in, ULONG inLength, APTR out, ULONG outLength, ULONG *done)`** (-30). Raw streams:
- `LZMODE_LZMA`, 7z's method 030101. `props` is `lc + 9 * (lp + 5 * pb)`. Exactly `outLength` bytes come out, and an end mark may close the stream at that point.
- `LZMODE_LZMA2`, 7z's 21 and xz's. Its chunks run to their end byte, giving at most `outLength` bytes. `props` is not needed.
- `LZMODE_LZMA_EOS`, an LZMA stream of unknown size that its end mark closes. The mark is read only while there is room, so give one byte more than the largest output.

**`LONG LzmaAloneInfo(CONST_APTR in, ULONG inLength, ULONG *size)`** (-36). Reads an `.lzma` file's 13-byte header and sets `*size` to the unpacked size. It sets `LZSIZE_UNKNOWN` when the file does not say.

**`LONG LzmaAloneDecode(CONST_APTR in, ULONG inLength, APTR out, ULONG outLength, ULONG *done)`** (-42). Unpacks an `.lzma` file. When the size is not known, give one byte more than the output, as for `LZMODE_LZMA_EOS`. On `LZERR_ROOM`, a bigger buffer may be tried.

**`LONG XzInfo(CONST_APTR in, ULONG inLength, ULONG *size)`** (-48). Reads an `.xz` file's indexes, from its end, and sets `*size` to the unpacked size of all of its streams.

**`LONG XzDecode(CONST_APTR in, ULONG inLength, APTR out, ULONG outLength, ULONG *done)`** (-54). Unpacks an `.xz` file:
- It takes one stream or several, with stream padding between them.
- Each block must have one LZMA2 filter.
- Each block's check must be none, CRC-32 or CRC-64, and every check is verified.
- The block headers, the index and the footer are checked against what was decoded.

**`CONST_STRPTR LzmaErrorText(LONG error)`** (-60). A short English text for an answer.

## UnXZ

`UnXZ FROM/A,TO,TEST/S,INFO/S,QUIET/S` unpacks an `.xz` or `.lzma` file. When TO is not given, it is FROM without `.xz` or `.lzma`, and `.txz` and `.tlz` become `.tar`. TEST decodes and checks without writing. INFO prints the sizes. The return code is 10 for damaged data and 20 when UnXZ can't run.

## Tests

- `tests/run_host_tests.sh`: the library's own 68040 code (lz_core.c, the hostlib call's 68k body, and the crc32 helper) runs under qemu-m68k on `lz_cases.py`'s 253 cases. The cases are made with liblzma as the reference encoder: raw LZMA and LZMA2 over every lc/lp/pb, `.lzma` with its size known and not, `.xz` with each check, and two streams with padding. Damaged, cut and too-small copies are included, among them `.lzma` files of unknown size with about half the room they need, which must answer `LZERR_ROOM`. A damaged `.xz` file must be refused unless liblzma also decodes it, which happens when the flipped bit is one of the range coder's last bits and the file has no check.
- `LzmaTest lzma-cases.bin`: the same cases through the library on an Amiga, or under vamos in CI.
- CI also checks UnXZ against `xz` and `xz --format=lzma` files.

MIT, Copyright (c) 2026 AmiCradle Team.
