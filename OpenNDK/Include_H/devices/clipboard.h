#ifndef DEVICES_CLIPBOARD_H
#define DEVICES_CLIPBOARD_H
/*
 * OpenNDK: clipboard.device's commands and requests.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef EXEC_IO_H
#include <exec/io.h>
#endif

#define CBD_POST		(CMD_NONSTD+0)
#define CBD_CURRENTREADID	(CMD_NONSTD+1)
#define CBD_CURRENTWRITEID	(CMD_NONSTD+2)
#define CBD_CHANGEHOOK		(CMD_NONSTD+3)

#define CBERR_OBSOLETEID	1	/* the clip has been replaced */

/* The public start of a clipboard unit */
struct ClipboardUnitPartial {
	struct Node	cu_Node;
	ULONG		cu_UnitNum;
};

struct IOClipReq {
	struct Message	io_Message;
	struct Device	*io_Device;
	struct ClipboardUnitPartial *io_Unit;
	UWORD		io_Command;
	UBYTE		io_Flags;
	BYTE		io_Error;
	ULONG		io_Actual;
	ULONG		io_Length;
	STRPTR		io_Data;
	ULONG		io_Offset;
	LONG		io_ClipID;	/* the clip being read or written */
};

#define PRIMARY_CLIP	0	/* the unit everyone shares */

/* Sent to a CBD_POST port when its clip is wanted */
struct SatisfyMsg {
	struct Message	sm_Msg;
	UWORD		sm_Unit;
	LONG		sm_ClipID;
};

/* The message a CBD_CHANGEHOOK hook receives */
struct ClipHookMsg {
	ULONG	chm_Type;	/* 0 */
	LONG	chm_ChangeCmd;	/* CMD_UPDATE or CBD_POST */
	LONG	chm_ClipID;
};

#endif /* DEVICES_CLIPBOARD_H */
