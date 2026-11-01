# Writing OpenNDK headers

Read CLEAN-ROOM.md first. In short: names, values, offsets and sizes are
the interface and must match; every comment, and every macro body, is our
own.

## Files

- `Include_H/<dir>/<name>.h`: written by hand, one per OS header.
- `SFD/<name>_lib.sfd`: each library's calls, written by hand
  (`SFD/README.md`).
- Generated from the SFDs by `tools/ndkgen.py`, never edited:
  `FD/`, `Include_H/clib/`, `Include_H/proto/`, `Include_H/inline/<lib>.h`,
  `Include_H/pragmas/`, `Include_I/lvo/`.

## A header

```c
#ifndef EXEC_NODES_H
#define EXEC_NODES_H
/*
 * OpenNDK: <one line in our own words>.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
...
#endif /* EXEC_NODES_H */
```

- The guard is the path in capitals with `/` and `.` as `_`, because
  programs test these names.
- Include each header the file needs, behind its guard, so every header
  compiles on its own (`tests/compile_headers.sh`).
- Types from `exec/types.h` only: no `<stdint.h>`, no compiler extensions
  beyond what plain C and C++ compilers for the 68k accept.
- Field order, types and array sizes give the 68k layout: 2-byte alignment
  for 16- and 32-bit fields, as every 68k Amiga compiler lays them out.
  Don't add padding fields that the OS's layout doesn't have; add `pad`
  fields where it has them.
- Constants are `#define NAME value`, values in the form a reader expects
  (flags in hex or `(1L<<n)`, with the bit number defined beside it where
  the OS defines both).
- Comments: a short line where it helps, in our own words. No banner text,
  no prose copied or paraphrased from any vendor or AROS header or autodoc.
- C++: no `class`, `new`, `delete`, `this` or `template` as field or
  argument names in a way that breaks C++; headers carry no `extern "C"`
  (the clib headers do).

## Checks

- `tests/run.sh`: generated files up to date, every header compiles in C
  and C++, the structure sizes in `tests/sizes.c`, a program built with
  `proto/` inlines, and the SFDs against the open libraries' `.lvo` tables.
- `check/compare_ndk.sh` (needs the vendor NDK, never committed): every
  structure size, field offset and constant value against the NDK's.
