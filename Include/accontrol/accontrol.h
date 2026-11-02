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

#endif
