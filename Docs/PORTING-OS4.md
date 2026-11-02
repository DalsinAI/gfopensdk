# Porting from AmigaOS 4 with os4compat

AmigaOS 4.1 and AmigaOS 3.2 are both big-endian and 32-bit, and OS 4's
calls are the classic library calls reached through an *interface*
(`IExec->AllocVec()` where OS 3.2 says `AllocVec()`). So most OS 4 source
builds for 68k unchanged once something answers those interfaces and the
few calls OS 3.2 does not have. That is os4compat.

## Build the kit once

```
make -C Lib/os4compat NDK=/path/to/NDK3.2
```

This reads the NDK's own SFD files and makes, for each library in `LIBS`:

| File | What it is |
| --- | --- |
| `build/include/interfaces/<lib>.h` | `struct <Lib>IFace`, one member a function, as OS 4 names them |
| `build/include/proto/<lib>.h` | the base, `I<Lib>`, and with `__USE_INLINE__` OS 4's bare-name macros |
| `build/libos4compat.a` | the members, the OS 4-only calls, `GetInterface()` |

Nothing from the NDK is copied into the SDK: the NDK stays the user's, and
the interfaces are made from it on the user's machine. ACKitchen does this
step for you.

The default `LIBS` are exec, dos, utility, graphics, intuition, layers,
gadtools, asl, icon, wb (IWorkbench), locale, diskfont, keymap, commodities,
datatypes, iffparse, rexxsyslib (IRexxSys), expansion and timer. Add any
library with an SFD file, ReAction classes included (`listbrowser`,
`layout`, ...). Keep exec, dos, utility, graphics and intuition: the kit's
own calls use them.

## Build a program

```make
SDK := path/to/gfopensdk
include $(SDK)/Lib/os4compat/os4compat.mk
prog: prog.c
	m68k-amigaos-gcc -m68040 -noixemul -O2 -fno-delete-null-pointer-checks $(OS4COMPAT_CFLAGS) -o $@ prog.c $(OS4COMPAT_LIBS)
```

`OS4COMPAT_LIBS` carries `-specs=` for the SDK's `Lib/m68k-soft-m68040.specs`,
so the link takes libnix's soft-float maths (the build is `-m68040` without
`-m68881`: one binary for 68040s with and without an FPU).

`Examples/os4compat-hello` is a complete OS 4 style program that builds this
way, and prints PASS or FAIL for each call it tries.

`-fno-delete-null-pointer-checks` matters on 68k: address 0 is memory on an
Amiga, and without it GCC puts `TRAP #7` (Software Failure 80000027) where it
can prove a pointer is NULL. The SDK's Makefiles pass it by default.

## How it works

- Each interface member is a small function that makes the classic call.
  It calls through the interface's own base, which is opened the first time
  a member is called and closed at exit. A program that only uses `IDOS`
  never opens `datatypes.library`.
- `IExec`, `IDOS` and the rest are ready at start, as with OS 4's startup
  code. A program that opens libraries itself and calls `GetInterface()`
  gets the same interface, now calling through its own base. A program that
  defines its own `struct DOSIFace *IDOS` still links: each pointer lives in
  a file of its own in the library.
- `OpenLibrary()` treats any version from 50 up (OS 4's) as 0, since OS 3.2's
  libraries are version 47.
- Only the `"main"` interface exists; other names answer `NULL`.

## The OS 4 calls it adds

| Interface | Calls |
| --- | --- |
| IExec | `AllocSysObject(Tags)`, `FreeSysObject` (ports, IORequests, hooks, interrupts, lists, nodes, semaphores, mutexes, tag lists, pools (`ASOPOOL_Protected` locks them in `AllocPooled`, `FreePooled`, `AllocVecPooled`, `FreeVecPooled` and `DeletePool`), messages), `AllocVecTagList`/`AllocVecTags` (`AVT_Type`, `AVT_ClearWithValue`), `GetInterface`, `DropInterface`, `NewList`, `NewMinList`, `GetHead`, `GetTail`, `GetSucc`, `GetPred`, `MutexObtain`, `MutexAttempt`, `MutexRelease`, `DebugPrintF` (to the serial port) |
| IDOS | `FOpen`, `FClose`, `ChangeFilePosition`, `GetFilePosition`, `GetFileSize` (64-bit), `ExamineObject(Tags)`, `ObtainDirContext(Tags)`, `ExamineDir`, `ReleaseDirContext`, `FreeDosObject(DOS_EXAMINEDATA)` |
| IUtility | `Strlcpy`, `Strlcat`, `SNPrintf`, `VSNPrintf`, `ASPrintf`, `VASPrintf` |
| IGraphics | `AllocBitMapTagList`/`Tags`, `BltBitMapTagList`/`Tags` (bitmaps and rastports), `CompositeTagList`/`Tags` (copy and clear) |
| IIntuition | `IDoMethod(A)`, `IDoSuperMethod(A)`, `ICoerceMethodA` |

OS 4's types (`uint32`, `int64`, `float64` and the rest) come with
`os4compat/os4compat.h`, as do the tags and structures these calls use
(`ASOT_`, `ASOPORT_`, `AVT_`, `EX_`, `struct ExamineData`, `BLITA_`,
`COMPTAG_`). Their names are OS 4's, so source compiles unchanged; their
values are ours, since everything is rebuilt.

## What to change by hand

| OS 4 code | On OS 3.2 |
| --- | --- |
| A hook filled in by hand: `hook.h_Entry = (HOOKFUNC)func;` | OS 3.2 calls `h_Entry` with registers. Set `h_Entry = (HOOKFUNC)HookEntry; h_SubEntry = (HOOKFUNC)func;`, or get the hook from `AllocSysObject(ASOT_HOOK)`, which does it for you |
| `newlib.library` or clib4 calls beyond C99 | link a POSIX C library for 68k (the Open SDK's choice is still to come); libnix covers C99 |
| ELF shared objects (`.so`) | link statically |
| Warp3D Nova, `ogles2.library` | need a host GPU; see OpenGPU. There is no 68040 route |
| `CompositeTags()` with alpha or scaling, or `COMPOSITE_Src_Over_Dest` from a 32-bit source | answers `COMPERR_SoftwareFallback`, as OS 4 does without hardware; draw it yourself or through OpenRTG |
| `AVT_Alignment` over 8 | not honoured: AllocVec gives 8 |
| `BMATags_NoMemory` | `AllocBitMapTags()` answers `NULL`: OS 3.2 graphics cannot make an RTG bitmap without its memory |
| `GetInterface()` for a version over 1 | answers `NULL`: every interface here is version 1 |
| 64-bit files over 2 GB | need a filesystem that answers the 64-bit packets; otherwise `ERROR_OBJECT_TOO_LARGE` |
| `ASOT_ITEMPOOL`, `ASOT_RMAP`, `ASOT_DMAENTRY`, `ASOT_EXTMEM` | answer `NULL`. For more than 2 GB of memory use openextmem.library |
| `application.library` notifications, AmiDock dockies | coming as OpenUp parts |
| A program built for a 1 GHz PowerPC | runs at 68k speed: fine on the AC090 JIT, slow on a real 68040 |

## Testing

`tests/host/run.sh` tests the generator and the plain-C calls with the host's
GCC. `Examples/os4compat-hello` is the test on an OS 3.2 instance or a real
Amiga.
