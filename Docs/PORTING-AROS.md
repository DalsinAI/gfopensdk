# Porting AROS programs with aroscompat

The AROS compatibility kit builds AROS programs from AROS's own sources as AmigaOS 3.x programs, with no change to those sources and no AROS code in the result. Everything in it is the Team's own work. The macro and type names are AROS's published interface, written from how AROS programs use them; nothing was copied from AROS's headers or libraries, and its MIT licence is the SDK's. Dale chose this on 10 November 2026 ("own clean-room libraries"), so AROS's APL code serves as a reference only and is never shipped.

## Using it

Put `Include/aroscompat` before the SDK's other headers and the OS's, then link `libaroscompat.a`:

```
CFLAGS += -I$(SDK)/Include/aroscompat -I$(SDK)/Include -I$(NDK)/Include_H
LIBS   += -L$(SDK)/Lib/aroscompat/build -laroscompat
# AROS sources assume older C: keep these warnings, not errors, with GCC 14 and later
CFLAGS += -Wno-error=incompatible-pointer-types -Wno-error=int-conversion \
          -Wno-error=implicit-function-declaration -Wno-error=implicit-int
```

`Lib/aroscompat/build.sh` builds the library with a stove (`CC`, `AR`, `NDK_INC`). `Examples/aroscompat-hello` is a whole program that uses each part, and CI runs it on a 68040 under vamos.

## What it gives

| Header | What it gives AROS sources |
| --- | --- |
| `exec/types.h` | The OS's own header, then `IPTR`, `SIPTR`, `STACKED`, `BNULL`, `RAWARG`, `QUAD`/`UQUAD`, the `STACK*` types and `ADATE`. It also brings in the calling macros, as AROS's own `exec/types.h` does. |
| `exec/lists.h` | The OS's own header, then `NEWLIST`, `ForeachNode`, `ForeachNodeSafe`, `GetHead`, `GetTail`, `GetSucc`, `GetPred` and `IsListEmpty`. |
| `aros/asmcall.h` | `AROS_UFHn`/`AROS_UFHnS` (hooks and callbacks with their arguments in registers), `AROS_UFPn` and `AROS_UFCn` (calls with registers), and `AROS_PROCH`. |
| `aros/libcall.h` | `AROS_LHn` (library functions, base in A6), `AROS_LDn`, `AROS_LPn`, `AROS_LCn` and `AROS_LCnNR` (calls by LVO), `AROS_CALLn` and `AROS_SLIB_ENTRY`. |
| `aros/shcommands.h` | `AROS_SHn` and `AROS_SHnH` (Shell commands: template, defaults, help, ReadArgs), `AROS_SHA`, `AROS_SHAH` and `SHArg`. The body gets `SysBase` and `DOSBase` of its own, as AROS's does. |
| `aros/symbolsets.h` | `ADD2INIT` and `ADD2EXIT` are libnix's own, which work the same way. `ADD2LIBS` adds nothing, because libnix opens the libraries a program uses. |
| `aros/debug.h` | `D()`, `bug()`, `kprintf()` (C formats, to the serial debug output), `ASSERT` and the `Enter`/`Return` macros, all following `DEBUG`. |
| `aros/macros.h` | The byte-order macros (`AROS_BE2LONG`, `AROS_LE2WORD` and the rest) and the BSTR macros. |
| `aros/cpu.h`, `aros/config.h` | `AROS_BIG_ENDIAN` and the alignments, and `AROS_TARGET_CPU "m68k"`. |
| `aros/detach.h` | `Detach()` does nothing here. Start a program with Run to leave its Shell free. |
| `proto/workbench.h` | The OS's `proto/wb.h`. |

`tools/gen_aroscompat.py` makes `asmcall.h`, `libcall.h`, `shcommands.h` and `aroscompat_regs.h`, with 0 to 16 arguments. Run it with `--check` in CI.

## How far it gets (10 November 2026)

Of the 73 programs in AROS's `workbench/c`, 38 build and link unchanged, among them Avail, Date, Delete, Join, MakeDir, Search, Sort, Sha256Sum, Type, Which, RequestChoice, RequestFile and Print. Several were run on a 68040 under vamos: Date, Type, Sha256Sum, MakeDir, Join, Delete, Which and AROSHello.

These are known gaps:
- **AROS-only libraries and devices:** `oop`, `kms`, `task.resource`, `debug.library`, `uuid`, `log`, `arossupport`'s own calls and `exec/rawfmt.h`. A program that needs one is an AROS program, not a port.
- **AROS's `%iu` and `%ix` formats (IPTR)** in `Printf`. The OS's `Printf` does not know them; Avail prints them as text.
- **Programs with their own startup (`__startup`),** such as Copy, Beep and WaitX. They need building without libnix's startup, which is not covered yet.
- **Zune/MUI programs.** These wait for our own muimaster.library in `DalsinAI/gfopenmui`.
- **A few OS 3.2 name differences:** `UtilityBase`'s type, `SYS_Asynch`, the `SD_ACTION_*` and `LOCF_GMT_CLOCK` names.

MIT, Copyright (c) 2026 AmiCradle Team.
