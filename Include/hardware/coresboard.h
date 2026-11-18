/* The CPU cores board: its registers, its services and their codes.
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence.
 *
 * An AutoConfig board (Zorro II, 64 KB, IO): manufacturer $DA15 (Dalsin),
 * product 7. It carries the ACSV register block at offset 0, as Mitchy, the
 * services card, does, with CLASS 2, and it offers its services by name
 * through ACSV's directory:
 *
 *   cpu.m68k/1     a 68k function on a secondary core (always)
 *   cpu.x86_64/1   a native function on an x86-64 host (when the host allows it)
 *   cpu.arm64/1    a native function on an ARM64 host, a Pi 5 (likewise)
 *
 * Most programs never touch the registers below:
 *   - 68k jobs: gfopenmulticore.library (<proto/gfopenmulticore.h>), which
 *     runs the same job on the main CPU when no board is there;
 *   - native jobs: mitchy.library (<proto/mitchy.h>), MitchyOpen("cpu.arm64/1")
 *     or "cpu.x86_64/1", with <cores/acn_job.h> for the job's own source;
 *   - task cores: GFOpenExec's, chosen in ENV:Cores/Apps;
 *   - guests: an emulator's front end, through GFOpenEmu (gfemu/core.h).
 * See Docs/CORES-BOARD.md. The full protocol is amicradle's
 * docs/architecture/CORES_BOARD.md. */
#ifndef HARDWARE_CORESBOARD_H
#define HARDWARE_CORESBOARD_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#define CORES_MANUFACTURER  0xDA15
#define CORES_PRODUCT       7
#define CORES_CLASS         2           /* ACSV's CLASS register */

/* ---- the board's own read-only registers (after ACSV's) ------------------ */
#define CORES_UNITS         0x24        /* cores the host runs; every one runs 68k */
#define CORES_ISAS          0x28        /* CORES_ISA_* */
#define CORES_QUEUED        0x2C        /* jobs waiting for a core */
#define CORES_CORE(k)       (0x100 + 16 * ((k) - 1))   /* core k, 1 to UNITS */
#define CORES_CORE_STATE    0x0         /* 0 idle, 1 a 68k job, 2 a native job */
#define CORES_CORE_LOAD     0x4         /* busy over the last second, 0 to 1000 */
#define CORES_CORE_JOBS     0x8         /* jobs finished (wraps) */
#define CORES_CORE_HOSTCPU  0xC         /* the host CPU it is pinned to, $FFFFFFFF none */

#define CORES_ISA_M68K      0x001       /* always */
#define CORES_ISA_X86_64    0x002       /* cpu.x86_64/1 is offered */
#define CORES_ISA_ARM64     0x004       /* cpu.arm64/1 is offered */
#define CORES_HOST_X86_64   0x100       /* the cores are x86-64 CPUs (offered or not) */
#define CORES_HOST_ARM64    0x200       /* the cores are ARM64 CPUs */

/* ---- every cpu.* service ------------------------------------------------- */
#define CORES_OP_RUN        1
#define CORES_OP_RUNX       2           /* cpu.m68k/1: the run block */
#define CORES_OP_INFO       3
#define CORES_OP_RANGE      4           /* cpu.m68k/1: indices 0 to count - 1 on every free core */
#define CORES_OP_CANCEL     0xFFFF      /* arg: the request's id */

/* RUN's flags: buffer i written; the core; no waiting for it. */
#define CORESF_WRITTEN(i)   (1UL << (i))
#define CORESF_CORE(n)      ((ULONG)(n) << 24)  /* 0 any free core, 1 to UNITS that one */
#define CORESF_CORE_MASK    0x1F000000UL
#define CORESF_NOWAIT       (1UL << 29)          /* the core named is busy: fail with CORES_BUSY */
/* cpu.m68k/1 RUN: bits 8-15 the number of longword stack arguments. */
#define CORESF_STACKARGS(n) ((ULONG)(n) << 8)
/* Native RUN: bits 8-23 a timeout in ms (0: 10 s). */
#define CORESF_TIMEOUT(ms)  (((ULONG)(ms) & 0xFFFF) << 8)

/* INFO's aux, cpu.m68k/1. */
#define CORES_INFO_ENGINE(aux)   ((aux) & 0xFF)  /* 1 interpreter, 2 translated */
#define CORES_INFO_MODEL(aux)    (((aux) >> 8) & 0xFF)   /* 4: a 68040 with an FPU */
#define CORES_INFO_RANGE         (1UL << 16)
#define CORES_INFO_RUNBLOCK2     (1UL << 17)
#define CORES_INFO_FAST          (1UL << 18)     /* a waiting program may poll the board briefly */

/* Completion statuses (ACSV's, and the board's own). */
#define CORES_OK            0           /* returned: result D0 (native: the low 32 bits), aux D1 (the high 32) */
#define CORES_BADREQ        (-2)
#define CORES_CANCELLED     (-3)
#define CORES_TOOBIG        (-4)        /* native: data buffers over 64 MB (result: the limit) */
#define CORES_FAULT         (-6)        /* 68k: result the vector, aux the PC; native: result the signal (31: a system call) */
#define CORES_TIMEOUT       (-7)
#define CORES_BUSY          (-8)
#define CORES_NOCORE        (-9)        /* result: UNITS */

/* ---- task cores: $800 (GFOpenExec's; programs use ENV:Cores/Apps) --------- */
#define TCOR_BASE           0x800
#define TCOR_MAGIC         0x54434F52UL   /* 'TCOR' at $800 */
#define TCOR_VERSION        0x804
#define TCOR_STATE          0x808       /* bit 0 on, bit 1 the helper attached, bit 2 a task out */
#define TCOR_OUTS           0x824       /* tasks sent out so far */
#define TCOR_SLOTS          0x828       /* version 2: cores offered for exec's slots */

/* ---- guests: $900 (an emulator's machine on the host; GFOpenEmu's) -------
 * Present when the long at $900 reads 'GCOR'. An emulator's CPU and its
 * devices run on the host beside a core; only control crosses: open, start,
 * pause, reset, close, the picture's place, focus, menus, the clipboard.
 * Front ends use gfemu/core.h, which falls back to the emulator's own CPU on
 * the 68k where the board is not there. */
#define GCOR_BASE           0x900
#define GCOR_MAGIC          0x47434F52UL   /* 'GCOR' */
#define GCOR_VERSION        0x904
#define GCOR_STATE          0x908       /* bit 0 guests offered, bit 1 INT2 held, bit 2 events wait */
#define GCOR_BODIES         0x90C       /* GBODY_* */
#define GCOR_OPEN           0x910       /* write: a struct GuestOpen's address; read: the handle (1-15), or 0 (see ERROR) */
#define GCOR_SEL            0x914       /* write: the handle the registers below act on */
#define GCOR_CTRL           0x918       /* write: GCTL_* */
#define GCOR_GSTATE         0x91C       /* read: GS_* | reason << 24 */
#define GCOR_PLACE          0x920       /* write: a struct GuestPlace's address */
#define GCOR_FOCUS          0x924       /* write: 1 the guest has the keyboard and mouse */
#define GCOR_MENU           0x928       /* write: a menu item's id */
#define GCOR_CLIP           0x92C       /* write: a struct GuestClip's address (to the guest); read: the guest's clip's length */
#define GCOR_CLIPGET        0x930       /* write: a buffer at least that long, for the guest's clip */
#define GCOR_EVENT          0x934       /* read: the SELected guest's next event (SEL 0: any guest's), handle << 24 | type << 16 | data, 0 none */
#define GCOR_ERROR          0x938       /* read: GERR_* of the last OPEN or CTRL */
#define GCOR_WANT           0x93C       /* read: width << 16 | height the guest wants */
#define GCOR_PENDING        0x940       /* read: a bit (1 << handle) for each guest with events waiting; drops INT2 until the
                                         * next event and changes nothing else, so every front end's INT2 server sees the
                                         * same bits and Signals its own task, which reads EVENT with SEL its guest (Forbid) */

#define GBODY_TEST          0x01
#define GBODY_BASILISK      0x02
#define GBODY_DOSBOX        0x04
#define GBODY_MAME          0x08
#define GBODY_SHEEPSHAVER   0x10

#define GCTL_START 1
#define GCTL_PAUSE 2
#define GCTL_RESET 3
#define GCTL_CLOSE 4

#define GS_NONE    0
#define GS_OPEN    1
#define GS_RUNNING 2
#define GS_PAUSED  3
#define GS_ENDED   4
#define GEND_BODY  0                    /* GSTATE's top byte when ended: the guest shut down */
#define GEND_HALT  1                    /* its CPU halted */
#define GEND_FAIL  2                    /* its body failed */

#define GEV_STATE  1                    /* data: the new GS_* */
#define GEV_SIZE   2                    /* see WANT */
#define GEV_TITLE  3
#define GEV_MENUS  4
#define GEV_CLIP   5                    /* see CLIP */
#define GEV_FILE   6                    /* data: the volume */
#define GEV_HANDLE(e) (((e) >> 24) & 0xFF)
#define GEV_TYPE(e)   (((e) >> 16) & 0xFF)
#define GEV_DATA(e)   ((e) & 0xFFFF)

#define GERR_NONE    0
#define GERR_NO_BODY 1
#define GERR_FULL    2
#define GERR_OPEN    3                  /* the body could not open (its options, its files) */
#define GERR_HANDLE  4
#define GERR_STATE   5
#define GERR_ARG     6

struct GuestOpen {
    STRPTR go_Body;                     /* "basilisk", "dosbox", "mame:<driver>", "test" */
    STRPTR go_Options;                  /* the icon's tooltypes: KEY=VALUE lines */
    struct Task *go_Task;               /* Signalled when an event waits */
    ULONG  go_SigBit;
};

struct GuestPlace {
    WORD  gp_X, gp_Y, gp_Width, gp_Height;
    UBYTE gp_Visible;
    UBYTE gp_Screen;                    /* 0 a window on Workbench, 1 its own screen */
    UBYTE gp_Scale;                     /* 0 fit, 1 1:1, 2 2:1 ... */
    UBYTE gp_Pad;
};

struct GuestClip {
    ULONG gc_Length;
    UBYTE gc_Data[1];                   /* gc_Length bytes */
};

#endif
