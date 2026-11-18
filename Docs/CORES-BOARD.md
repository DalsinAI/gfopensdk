# The CPU cores board, for programs

The CPU cores board is an AutoConfig card in AmiCradle's machines (Dalsin `$DA15`, product 7). Behind it the host runs extra CPU cores, up to 16. There are four ways a program uses them. Each has a fallback, so the same program runs on a real Amiga or a PiStorm with no board.

| Way | What runs on the core | How a program asks | Without the board |
|---|---|---|---|
| **68k jobs** | A 68k function of the program's own | `gfopenmulticore.library`: `OMC_Run68k`, `OMC_Submit`, `OMC_RunRange` | The library runs the same job on the main CPU |
| **Native jobs** | A function built for the host: ARM64 on a Pi 5, x86-64 on a PC | `mitchy.library`: `MitchyOpen("cpu.arm64/1")` or `"cpu.x86_64/1"`, then RUN | `MitchyOpen` fails; the program does the work on the 68k |
| **Task cores** | A whole chosen task's own code, run by GFOpenExec | List the program in `ENV:Cores/Apps` | The task runs on the main CPU as always |
| **Guests** | An emulator's machine: its CPU and its devices (the Mac of Basilisk II, DOSBox's PC, a MAME driver) | GFOpenEmu's `gfemu/core.h`, from the emulator's front end | The emulator runs its own CPU on the 68k |

The headers:
- `hardware/coresboard.h`: the registers, the services' ops and flags, the statuses, and the task-core (`$800`) and guest (`$900`) blocks;
- `cores/acn_job.h`: a native job's own source;
- `libraries/gfopenmulticore.h` and `proto/gfopenmulticore.h`: 68k jobs;
- `libraries/mitchy.h` and `proto/mitchy.h`: any ACSV service by name.

The full protocol is amicradle's `docs/architecture/CORES_BOARD.md`.

## What the board says about itself

These are read-only registers in the board's 64 KB (find it with `FindConfigDev(NULL, 0xDA15, 7)`, or `MitchyFindBoard(NULL, MITCHY_CLASS_CORES)`):

- `CORES_UNITS` (`$24`): the cores; every one runs 68k.
- `CORES_ISAS` (`$28`):
  - bit 0: m68k, always;
  - bit 1: native x86-64 jobs are offered;
  - bit 2: native ARM64 jobs are offered;
  - bits 8 and 9: what the cores themselves are (x86-64, ARM64), whether or not native jobs are offered.
- `CORES_QUEUED` (`$2C`): jobs waiting.
- `CORES_CORE(k)`: core k's state, load (0–1000 over the last second), jobs finished, and the host CPU it is pinned to.

`gfopenmulticore.library` reads these for you (`OMC_CoreCount`, `OMC_CoreInfo`).

## 68k jobs

Use `gfopenmulticore.library`; `Docs/gfopenmulticore.doc` is the reference.

- **What a job is.** A job is a function with no OS calls. It may use only the memory it is granted, so a job is something like a decoder, a mixer, a hash or a physics step.
- **Choosing a core.** `OMC_CORE(board, n)` picks a core. `OMCF_NOWAIT` fails rather than waiting.
- **Ranges.** `OMC_RunRange` splits one loop across every free core.

## Native jobs

A native job is C built for the host and run in a sandbox. It is the fastest way to do heavy work: it runs at the host CPU's full speed, with no emulation.

1. **Write the job** against `cores/acn_job.h`: one function `uint64_t entry(acn_job *job)`.
   - It must be position independent, with no libc and no system calls.
   - It sees the request's buffers 1–3 as `job->buf[0..2]` and `mr_Extra[0..3]` as `job->x[0..3]`.
   - The Amiga's data is big-endian; `acn_be32` reads it.
2. **Build it twice** with host compilers, `-fPIC -ffreestanding -nostdlib`. Then take the function's bytes out with `objcopy -O binary`: `job.x86_64.bin`, `job.arm64.bin`.
3. **From the Amiga:**
   - `MitchyOpen("cpu.arm64/1")`, else `"cpu.x86_64/1"`;
   - load the matching `.bin`;
   - then send a request:
     - `mr_Op = CORES_OP_RUN`;
     - buffer 0 the code, `mr_Arg` the entry's offset in it;
     - buffers 1–3 the data;
     - `mr_Flags`: `CORESF_WRITTEN(i)` for each buffer the job writes, plus `CORESF_TIMEOUT(ms)` and `CORESF_CORE(n)` if wanted.
4. **The answer:** `mr_Result` is the low 32 bits of the function's return, and `mr_Aux` the high 32. Written buffers come back only when the job returns.
   - `CORES_FAULT` (-6): the job crashed (result: the signal) or made a system call (result 31).
   - `CORES_TIMEOUT` (-7): the job ran past its timeout.

The host offers native jobs only when its user allows them: `AC_NATIVE=1`, an instance setting. If `MitchyOpen` fails, do the work on the 68k.

`Examples/cores-native-job` does all of this. `make check` runs the job's x86-64 build on a PC, placed as the board places it.

## Task cores

These are for programs that were never written for cores. GFOpenExec moves a chosen task's own code onto a core; its OS calls come back to the main CPU. A program needs nothing: the user lists it in `ENV:Cores/Apps`. The `$800` registers in `hardware/coresboard.h` are GFOpenExec's; programs do not write them.

## Guests

These are for emulators. A guest is a whole emulated machine on the host: its CPU on a core of its own (a 68k core for the Mac, the host's own CPU for DOSBox's x86), and its devices built for the host beside it. Only control crosses to the Amiga:
- open, start, pause, reset and close;
- where the picture goes;
- focus, menus and the clipboard.

So the emulator's Amiga program is a thin front end, and the main CPU stays free.

**Finding it.** The block is present when the long at board offset `$900` reads `'GCOR'`. `GCOR_BODIES` says which emulators this host carries.

**Using it.** Front ends use GFOpenEmu's `gfemu/core.h`, which drives these registers. It also falls back to the emulator's own CPU on the 68k when the board, or the body, isn't there. The design is Team 4's salvor/Design-Guest-Cores-20261118.md.

Status, 18 November 2026: the guest block is new. It is being built in gfosmotherboards (`a1200-x86/native/guests.c`), on a team4 branch. Until a program reads `'GCOR'` at `$900`, it must behave as if there is no board.
