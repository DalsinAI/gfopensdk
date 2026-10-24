# Pinned wasm2c allocation-capacity patch

The Open SDK maintains a small patch over WABT 1.0.41's non-mmap memory runtime.
`tools/patch_wasm2c_memory.py --runtime <generated-C-directory>` verifies exact
upstream hashes before changing `wasm-rt.h` and
`wasm-rt-mem-impl-helper.inc`. Apply it **before** other compatibility patches.
An unexpected version/template or a second application is refused. The upstream
source retains its Apache-2.0 notices; this is not a new wasm2c converter fork.

## Demonstrated problem

On the isolated AC090 lab, the unpatched Civ II replay tries to grow a
contiguous linear-memory buffer from 89,718,784 to 90,832,896 bytes. At failure,
274,782,128 bytes are free but the largest block is 89,628,128 bytes. Exact-size
whole-buffer reallocations after small memory.grow requests fragment this
allocation pattern. A simple standalone realloc sequence still passes, so a
general compiler arithmetic or realloc correctness defect is not established.

The failed grow makes a 1,091,988-byte guest calloc return zero. The Win32 shim
creates a 556x491, 32-bpp bitmap with a null pixel pointer anyway, then xfer_row
writes grey pixels into low linear memory, including the libc stream callback.
Width, height, stride, coordinates and little-endian scalar reads are correct
at the captured blit. printf exposes the overwrite; it is not the first writer.

## Runtime policy and limits

Track physical capacity separately from the logical memory size. Reserve
capacity geometrically on growth, bounded by the declared memory limit and
SIZE_MAX. If the larger reserve fails, retry the exact requested size. Growth
inside the capacity does not reallocate. Newly exposed bytes are cleared;
reserved spare bytes remain outside the module's logical bounds. Failed growth
keeps the old allocation and metadata intact. Zero growth does not allocate.
Initial allocation failure is rejected rather than returning a null instance.

This profile supports forward-addressed wasm32 memory, ordinary 64KiB pages,
non-mmap allocation, and unshared memories. memory64, custom page sizes,
reversed-memory big-endian mode, mmap/guard-page mode and shared memory are not
qualified here. Big-endian hosts use an independently tested forward/little-
endian scalar boundary, as Civ II's existing adaptation does.

**The memory-structure ABI changes.** Rebuild all generated C, host adapters
and runtime objects together against the patched header. Never mix old objects
or runtime libraries. No active compiler/stove files are modified.

## Reproduction and qualification

The small unmodified fixture under `tests/sdk/wasm2c/upstream-1.0.41` records its
upstream source, individual hashes and licence. It is only a runtime test
fixture, not another maintained converter implementation.

```sh
python3 tests/sdk/wasm2c/run.py
python3 tests/sdk/wasm2c/run.py --cc m68k-linux-gnu-gcc \
  --flags='-m68040 -static' --runner='qemu-m68k -cpu m68040'
```

Tests cover old-data preservation, zeroed newly exposed bytes, physical capacity
versus logical bounds, no-op growth, max limits, failure preserving old state,
exact-size fallback, zero initial memory and teardown. Initial allocation
failure is injected and must terminate through the controlled failure hook.
The native Open3 test also passed on the isolated AC090 lab (normal RC0,
controlled failure RC75). Remote CI remains unrun while uploads are paused.

The first clean full-SDL Civ II rebuild using this SDK patch passes the former
crash, manual save, two turns and clean exit (RC0). Save reload and further
consumer qualification are recorded separately in the gameports evidence.
The patch does not make unchecked bitmap allocation failures safe in arbitrary
Win32 shims; consumers still need to handle allocation errors and validate
surfaces. The SDK's checked bitmap core provides the latter operations.
