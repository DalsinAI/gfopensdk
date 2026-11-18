/* Copyright (c) 2026 AmiCradle Team. GFOpenInput, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 * gfopeninput.library's functions, from library/gfopeninput_lib.sfd. Draft for review. */
#ifndef CLIB_OPENINPUT_PROTOS_H
#define CLIB_OPENINPUT_PROTOS_H
#include <exec/types.h>
#include <exec/ports.h>
#include <utility/tagitem.h>
#include <libraries/gfopeninput.h>

ULONG  OIN_ListControllers(struct OIControllerInfo *buffer, ULONG max, ULONG infoSize);
LONG   OIN_GetControllerInfo(ULONG id, struct OIControllerInfo *info, ULONG infoSize);
APTR   OIN_OpenControllerA(ULONG id, struct TagItem *tags);
APTR   OIN_OpenController(ULONG id, Tag tag1, ...);
VOID   OIN_CloseController(APTR controller);
LONG   OIN_ReadState(APTR controller, struct OIState *state, ULONG stateSize);
LONG   OIN_ReadRaw(APTR controller, struct OIRawState *raw, ULONG rawSize);
LONG   OIN_Rumble(APTR controller, ULONG low, ULONG high, ULONG millis);
APTR   OIN_AddNotifyA(struct MsgPort *port, struct TagItem *tags);
APTR   OIN_AddNotify(struct MsgPort *port, Tag tag1, ...);
VOID   OIN_RemNotify(APTR notify);
LONG   OIN_GetMapping(UBYTE *guid, STRPTR buffer, ULONG size);
LONG   OIN_SetMapping(STRPTR line, ULONG flags);
STRPTR OIN_ButtonLabel(ULONG id, ULONG button);
LONG   OIN_GetLegacyPort(ULONG port, struct OILegacyPort *legacy, ULONG size);
LONG   OIN_SetLegacyPortA(ULONG port, ULONG id, struct TagItem *tags);
LONG   OIN_SetLegacyPort(ULONG port, ULONG id, Tag tag1, ...);
/* revision 3 (OPENINPUT_REVISION_DRIVER) */
APTR   OIN_AddDriverPad(struct OIControllerInfo *info, ULONG infoSize);
VOID   OIN_DriverPadRaw(APTR pad, struct OIRawState *raw, ULONG rawSize);
VOID   OIN_RemDriverPad(APTR pad);

#endif /* CLIB_OPENINPUT_PROTOS_H */
