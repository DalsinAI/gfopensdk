/* accontrol.device: AmiCradle's control plane for Amiga programs.
 *
 * OpenDevice("accontrol.device", 0, (struct IORequest *)io, 0) with a
 * struct IOStdReq, then DoIO / SendIO. The device drives the ACBridge
 * control board (Zorro II, product 1; AmiCradle Team $DA15, or 2011 before AmiCradle Team),
 * one command at a time for every program that opens it.
 *
 *   ACCMD_GETPACE   io_Actual = the CPU's pace in Hz (0: hyper, as fast as
 *                   the host)
 *   ACCMD_SETPACE   io_Offset = the pace in Hz (0 hyper, else 1 to 200 MHz,
 *                   timing accurate); io_Actual = the pace now.
 *                   ACCERR_REFUSED if the machine will not take it.
 *   ACCMD_BOARD     io_Offset = a board query for the host (ACC_QUERY_*);
 *                   the answer (JSON text) goes to io_Data, at most io_Length
 *                   bytes; io_Actual = its length. ACCERR_HOST if the host
 *                   could not answer.
 *   ACCMD_CLIPSEQ   io_Actual = the number of the PC's latest clip (it goes
 *                   up each time the host PC's clipboard brings new text).
 *   ACCMD_CLIPGET   the PC's clip into io_Data, at most io_Length bytes;
 *                   io_Actual = its whole length (more than io_Length: call
 *                   again with room for it). Latin-1 text, LF line ends.
 *   ACCMD_CLIPPUT   io_Data, io_Length bytes of Latin-1 text, to the host
 *                   PC's clipboard.
 *                   The three clipboard commands (DSK-10, ACBridge 1.2) give
 *                   ACCERR_NOCLIP on a board without the clipboard.
 *   ACCMD_FILENEXT  the next file dropped on the instance's window: io_Offset
 *                   = 1 and io_Actual = its size, its name (Latin-1, NUL
 *                   ended) in io_Data (at most io_Length bytes); io_Offset =
 *                   0 when none waits.
 *   ACCMD_FILEREAD  that file's bytes from io_Offset into io_Data, at most
 *                   io_Length; io_Actual = the bytes read.
 *   ACCMD_FILEDONE  done with that file: the next one, if any, comes next.
 *   ACCMD_FILEPUT   a file for the host PC's tray: io_Data points to a struct
 *                   ACFilePut (its name, its bytes and their count).
 *                   The four file commands (ACBridge capability bit 12) give
 *                   ACCERR_NOFILES on a board without them.
 *   ACCMD_FLOPPYLIST  the disks for a floppy drive: io_Offset = the drive (0
 *                   DF0 to 3 DF3); text into io_Data, at most io_Length bytes,
 *                   io_Actual its length: a line "DFn<TAB>1|0<TAB>what is in
 *                   it" (1 a disk is in), then a line for each disk the host
 *                   can put in: a name in the instance's floppy directory,
 *                   "repo:NAME" from its install media, "__builtin__" the
 *                   AROS boot disk. UTF-8 names, LF line ends.
 *   ACCMD_FLOPPYINSERT  put one of those disks in the drive: io_Offset = the
 *                   drive, io_Data = its name, NUL ended (NULL or "" ejects);
 *                   io_Actual = 1 a disk is in, 0 the drive is empty. The
 *                   host keeps the choice, so a reboot starts from it.
 *   ACCMD_FLOPPYPUT  an ADF from the Amiga into the drive: io_Offset = the
 *                   drive, io_Data points to a struct ACFilePut (the ADF's
 *                   name, its bytes, 901120 of them); the host keeps it in
 *                   the instance's floppy directory and puts it in.
 *                   io_Actual = 1.
 *                   The three floppy commands (ACBridge capability bit 14)
 *                   give ACCERR_NOFLOPPY on a board without them, and
 *                   ACCERR_HOST when the host refuses: io_Actual is then its
 *                   reason's number (2 the drive is not fitted, 3 the runtime
 *                   can't change disks, 4 not an 880 KB ADF, 6 it didn't go in).
 *   ACCMD_SHARES    the host's network shares (1.4, ACBridge capability bit
 *                   18; amicradle-teams designs/NETSHARES-DESIGN-20261110.md):
 *                   io_Data holds one request line, NUL ended, tab-separated
 *                   ("LIST", "MOUNT<TAB>NET0", ...); the host's answer replaces
 *                   it, NUL ended, at most io_Length - 1 bytes: "OK", "WARN",
 *                   "WAIT" or "ERROR", a tab, a plain sentence, then any rows.
 *                   io_Actual = the answer's length; io_Offset = 0 OK, 5 a
 *                   warning, 10 an error. A request may carry a password: the
 *                   host keeps it and never sends it back; clear the buffer
 *                   after the call. ACCERR_NOSHARES on a board without them.
 *   ACCMD_POWER     the machine restarted or powered off by its host (1.5,
 *                   ACBridge capability bit 19): io_Offset = ACC_POWER_RESTART
 *                   (a cold start: the host starts the machine again) or
 *                   ACC_POWER_OFF (an appliance shuts down cleanly; on a PC the
 *                   instance closes). The host answers before it acts, so the
 *                   request completes; ask the user first, as nothing is
 *                   saved. ACCERR_HOST (io_Actual the host's reason) when it
 *                   refuses, ACCERR_NOPOWER on a board without it.
 *   ACCMD_POWERLEVEL  the host's power level and sensors (1.6, ACBridge
 *                   capability bit 20; CM4 item 9): io_Offset =
 *                   ACC_POWERLEVEL_READ only reads, ACC_POWERLEVEL_QUIET,
 *                   _BALANCED or _FULL set the host's level (its cpufreq
 *                   governor and top clock). io_Data receives the host's
 *                   sensors as JSON text, NUL ended, at most io_Length - 1
 *                   bytes: tempMilliC, clockKHz, clockMaxKHz, throttled,
 *                   underVoltage, fanRPM, powerLevel ("Quiet", "Balanced",
 *                   "Full" or "Custom") and powerLevelCanSet, each only when
 *                   the host has it (a real 68k or a host without sensors
 *                   sends none). io_Actual = the text's length; io_Offset =
 *                   the host's result: 0 done, 3 not a level, 5 this host
 *                   can't set it. ACCERR_HOST when the host doesn't answer,
 *                   ACCERR_NOPOWERLEVEL on a board without it.
 *   ACCMD_CHIPLIMIT  the Chip RAM limiter (1.7, ACBridge capability bit 21;
 *                   CM4 item 15): an AA+ machine runs as a stock A1200
 *                   (2 MB of Chip RAM, the 21-bit DMA mask, no AA+ card)
 *                   from its next power-on, or gets its full board back.
 *                   io_Offset = ACC_CHIP_READ, ACC_CHIP_2MB or ACC_CHIP_FULL,
 *                   ORed with ACC_CHIP_NOW to power off and on at once (the
 *                   host answers first; nothing is saved, so ask the user).
 *                   io_Actual = MB now | MB from the next power-on << 8 |
 *                   MB of the full board << 16. The size changes only at a
 *                   power-on, never on a warm reset; the instance keeps it.
 *                   ACCERR_HOST (io_Offset the host's result: 3 a bad
 *                   request, 5 no AA+ board) when the host refuses,
 *                   ACCERR_NOCHIPLIMIT on a board without it.
 *   ACCMD_MACHINE   the machine's settings, global and per program (1.8,
 *                   ACBridge capability bit 22; gfosdesign
 *                   gfos/machines/machine-settings). The words: FPU=DOUBLE or
 *                   EXTENDED, PACE=HYPER, A1200 or MHz (1-200). io_Offset's
 *                   low byte is the operation:
 *                   ACC_MACHINE_PUSH  io_Data the words, NUL ended: in force
 *                     over the global ones before the Amiga's next
 *                     instruction, for the program about to start; the
 *                     calling task is the owner. io_Actual = the push's id;
 *                     io_Data gets back the words refused (unknown, or not
 *                     applied by this machine), "" when none.
 *                     ACCERR_REFUSED when 16 are pushed already.
 *                   ACC_MACHINE_POP  io_Offset = ACC_MACHINE_POP | id << 8:
 *                     that push taken away, in any order; ACCERR_HOST when
 *                     it isn't pushed. A reset takes every push away.
 *                   ACC_MACHINE_GET  io_Data gets what is in force (first
 *                     line), "global" and the global words, then a line per
 *                     push: "push <id> <owner> <words>".
 *                   ACC_MACHINE_SET  io_Data the global words (GFOpenPrefs):
 *                     the pace at once, the FPU from the next reset (it is
 *                     never switched under running programs); io_Data gets
 *                     back the words refused.
 *                   ACCERR_NOMACHINE on a board without it.
 *   ACCMD_FRAMEHISTORY  the host's frame history (1.9, ACBridge capability
 *                   bit 23): the copies of each screen the host keeps for its
 *                   browser page's timed frames and screenshots. io_Offset =
 *                   ACC_FRAMEHIST_READ, _ONDEMAND or _ON; io_Actual = the mode
 *                   now (0 ALWAYSOFF, 1 ONDEMAND, 2 ON). The host's
 *                   ac.framehistory decides where it starts (ONDEMAND unless
 *                   set); ALWAYSOFF there (no frames sent at all) can't be
 *                   undone from the Amiga: ACCERR_REFUSED.
 *                   ACCERR_NOFRAMEHISTORY on a board without it.
 *   NSCMD_DEVICEQUERY  the standard query (NSDEVTYPE_UNKNOWN; the commands
 *                   above).
 *
 * Every command completes at once (the machine answers the board while the
 * Amiga's CPU waits), so AbortIO has nothing to abort.
 */
#ifndef DEVICES_ACCONTROL_H
#define DEVICES_ACCONTROL_H

#include <exec/io.h>

#define ACCONTROL_NAME "accontrol.device"

#define ACCMD_GETPACE  (CMD_NONSTD + 0)
#define ACCMD_SETPACE  (CMD_NONSTD + 1)
#define ACCMD_BOARD    (CMD_NONSTD + 2)
#define ACCMD_CLIPSEQ  (CMD_NONSTD + 3)
#define ACCMD_CLIPGET  (CMD_NONSTD + 4)
#define ACCMD_CLIPPUT  (CMD_NONSTD + 5)
#define ACCMD_FILENEXT (CMD_NONSTD + 6)
#define ACCMD_FILEREAD (CMD_NONSTD + 7)
#define ACCMD_FILEDONE (CMD_NONSTD + 8)
#define ACCMD_FILEPUT  (CMD_NONSTD + 9)
#define ACCMD_FLOPPYLIST   (CMD_NONSTD + 10)
#define ACCMD_FLOPPYINSERT (CMD_NONSTD + 11)
#define ACCMD_FLOPPYPUT    (CMD_NONSTD + 12)
#define ACCMD_SHARES       (CMD_NONSTD + 13)
#define ACCMD_POWER        (CMD_NONSTD + 14)

#define ACC_POWER_RESTART  1               /* ACCMD_POWER's io_Offset: start the machine again (cold) */
#define ACC_POWER_OFF      2               /* ... power it off (a PC: close the instance) */
#define ACCMD_POWERLEVEL   (CMD_NONSTD + 15)
#define ACCMD_CHIPLIMIT    (CMD_NONSTD + 16)
#define ACCMD_MACHINE      (CMD_NONSTD + 17)
#define ACCMD_FRAMEHISTORY (CMD_NONSTD + 18)

#define ACC_MACHINE_PUSH   1               /* ACCMD_MACHINE's io_Offset (low byte): a program's words over the global ones */
#define ACC_MACHINE_POP    2               /* ... that push taken away: its id in io_Offset's upper 24 bits */
#define ACC_MACHINE_GET    3               /* ... what is in force, the global words, the pushes */
#define ACC_MACHINE_SET    4               /* ... the global words */

#define ACC_FRAMEHIST_READ 0               /* ACCMD_FRAMEHISTORY's io_Offset: only read */
#define ACC_FRAMEHIST_ONDEMAND 1           /* ... no history: the host reads a frame only when its page asks */
#define ACC_FRAMEHIST_ON   2               /* ... the host keeps one (the browser page's timed frames, screenshots) */
#define ACC_FRAMEHIST_ALWAYSOFF 0          /* io_Actual: the host's config says ALWAYSOFF; the Amiga can't turn it on */

#define ACC_CHIP_READ  0                   /* ACCMD_CHIPLIMIT's io_Offset: only read */
#define ACC_CHIP_2MB   1                   /* ... a stock A1200 (2 MB) from the next power-on */
#define ACC_CHIP_FULL  2                   /* ... the board's full Chip RAM from the next power-on */
#define ACC_CHIP_NOW   0x100               /* ... ORed in: power off and on now */

#define ACC_POWERLEVEL_READ     0          /* ACCMD_POWERLEVEL's io_Offset: only read the level and sensors */
#define ACC_POWERLEVEL_QUIET    1          /* ... set Quiet: a dynamic governor, the clock capped halfway */
#define ACC_POWERLEVEL_BALANCED 2          /* ... set Balanced: a dynamic governor, the full clock */
#define ACC_POWERLEVEL_FULL     3          /* ... set Full: the performance governor */

#define ACC_ADF_BYTES 901120UL             /* an 880 KB DD disk: what ACCMD_FLOPPYPUT takes */

/* ACCMD_FILEPUT's and ACCMD_FLOPPYPUT's io_Data */
struct ACFilePut {
    const char *name;                       /* the file's name for the PC (no path) */
    const UBYTE *data;                      /* its bytes */
    ULONG size;                             /* how many */
};

/* ACCMD_BOARD's queries (the ACBridge board's host commands) */
#define ACC_QUERY_STATUS    7      /* the host's system status */
#define ACC_QUERY_REFRESH   8      /* the same, read again */
#define ACC_QUERY_CATALOG   9      /* the machines and boot environments the host knows */

/* io_Error, beyond exec's */
#define ACCERR_NOBOARD   40        /* no ACBridge board: not an AmiCradle machine */
#define ACCERR_OLDBOARD  41        /* an ACBridge from before ABI 1.1 (no pace) */
#define ACCERR_REFUSED   42        /* the machine refused the request (a pace outside 1-200 MHz) */
#define ACCERR_HOST      43        /* the host could not answer a query */
#define ACCERR_NOCLIP    44        /* an ACBridge from before ABI 1.2 (no clipboard) */
#define ACCERR_NOFILES   45        /* an ACBridge without files (capability bit 12) */
#define ACCERR_NOFLOPPY  46        /* an ACBridge without the floppy changer (capability bit 14) */
#define ACCERR_NOSHARES  47        /* an ACBridge without network shares (capability bit 18) */
#define ACCERR_NOPOWER   48        /* an ACBridge without restart and power off (capability bit 19) */
#define ACCERR_NOPOWERLEVEL 49     /* an ACBridge without the power level (capability bit 20) */
#define ACCERR_NOCHIPLIMIT  50     /* an ACBridge without the Chip RAM limiter (capability bit 21) */
#define ACCERR_NOMACHINE    51     /* an ACBridge without the machine's settings (capability bit 22) */
#define ACCERR_NOFRAMEHISTORY 52   /* an ACBridge without the frame history switch (capability bit 23) */

#endif
