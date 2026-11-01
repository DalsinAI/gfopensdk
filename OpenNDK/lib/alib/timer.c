/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* TimeDelay and DoTimer: one timer.device request on a port of our own. */
#include "alib.h"
#include <devices/timer.h>

LONG DoTimer(TimeVal_Type *tv, LONG unit, LONG command)
{
	struct MsgPort *port = CreateMsgPort();
	struct timerequest *tr;
	LONG err = -1;

	if (!port)
		return -1;
	tr = (struct timerequest *)CreateIORequest(port, sizeof(*tr));
	if (tr) {
		if (OpenDevice((CONST_STRPTR)TIMERNAME, (ULONG)unit, &tr->tr_node, 0) == 0) {
			tr->tr_node.io_Command = (UWORD)command;
			tr->tr_time = *tv;
			err = DoIO(&tr->tr_node);
			*tv = tr->tr_time;
			CloseDevice(&tr->tr_node);
		}
		DeleteIORequest(tr);
	}
	DeleteMsgPort(port);
	return err;
}

LONG TimeDelay(LONG unit, ULONG seconds, ULONG micros)
{
	struct timeval tv;
	tv.tv_secs = seconds;
	tv.tv_micro = micros;
	return DoTimer(&tv, unit, TR_ADDREQUEST);
}
