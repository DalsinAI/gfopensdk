/* gfopenusb.library's calls (libraries/gfopenusb.h has the structures and the
 * class contract). LVOs from -30, in this order. A device pointer stays
 * good between OUSB_LockList() and OUSB_UnlockList(), or for a class from
 * its Attach to its Detach. A pipe belongs to the task that opened it: its
 * calls, and its signal, are that task's. MIT, AmiCradle Team. */
#ifndef CLIB_OPENUSB_PROTOS_H
#define CLIB_OPENUSB_PROTOS_H

#include <exec/types.h>
#include <libraries/gfopenusb.h>

struct OUSBPipe;

/* -30  start a host controller driver (UHCMD interface): its bus number,
 *      or -OUSB_NOHARDWARE etc.; the same name and unit again: its number */
LONG OUSB_AddHardware(CONST_STRPTR name, ULONG unit);
/* -36, -42  the device lists, shared */
void OUSB_LockList(void);
void OUSB_UnlockList(void);
/* -48  the next device, every bus in turn; NULL: the first */
struct OUSBDevice *OUSB_NextDevice(struct OUSBDevice *prev);
/* -54  goes up whenever a device is added or removed */
ULONG OUSB_Generation(void);
/* -60  a bus's host controller driver, and its unit */
STRPTR OUSB_HardwareName(ULONG bus, ULONG *unit);
/* -66  a control transfer on endpoint 0; setup is 8 bytes as on the wire;
 *      timeout in ms (0: 5 s) */
LONG OUSB_Control(struct OUSBDevice *dev, const UBYTE *setup, APTR data, ULONG len, ULONG timeout, ULONG *actual);
/* -72, -78  a bulk or interrupt endpoint ($80 for IN) */
struct OUSBPipe *OUSB_OpenPipe(struct OUSBDevice *dev, ULONG endpoint);
void OUSB_ClosePipe(struct OUSBPipe *pipe);
/* -84  a transfer, waited for; timeout in ms, 0: as long as the device NAKs */
LONG OUSB_Transfer(struct OUSBPipe *pipe, APTR data, ULONG len, ULONG timeout, ULONG *actual);
/* -90, -96, -102, -108, -114  the same, started and waited for apart:
 *      Wait() on OUSB_PipeSignal() with your other signals */
LONG OUSB_SendTransfer(struct OUSBPipe *pipe, APTR data, ULONG len, ULONG timeout);
LONG OUSB_WaitTransfer(struct OUSBPipe *pipe, ULONG *actual);
LONG OUSB_CheckTransfer(struct OUSBPipe *pipe);
void OUSB_AbortTransfer(struct OUSBPipe *pipe);
ULONG OUSB_PipeSignal(struct OUSBPipe *pipe);
/* -120  CLEAR_FEATURE(ENDPOINT_HALT) after OUSB_STALL */
LONG OUSB_ClearHalt(struct OUSBPipe *pipe);
/* -126  the stack's event log, oldest first: 0 past its end */
LONG OUSB_ReadLog(ULONG index, CONST_STRPTR *what, ULONG *args);

#endif
