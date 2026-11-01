/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* CreatePort and DeletePort: a message port with its own signal, made
 * public when it has a name. */
#include "alib.h"

struct MsgPort *CreatePort(CONST_STRPTR name, LONG pri)
{
	BYTE sig = AllocSignal(-1);
	struct MsgPort *port;

	if (sig < 0)
		return NULL;
	port = (struct MsgPort *)AllocMem(sizeof(*port), MEMF_PUBLIC | MEMF_CLEAR);
	if (!port) {
		FreeSignal(sig);
		return NULL;
	}
	port->mp_Node.ln_Name = (char *)name;
	port->mp_Node.ln_Pri = (BYTE)pri;
	port->mp_Node.ln_Type = NT_MSGPORT;
	port->mp_Flags = PA_SIGNAL;
	port->mp_SigBit = (UBYTE)sig;
	port->mp_SigTask = FindTask(NULL);
	if (name)
		AddPort(port);
	else
		NewList(&port->mp_MsgList);
	return port;
}

VOID DeletePort(struct MsgPort *port)
{
	if (!port)
		return;
	if (port->mp_Node.ln_Name)
		RemPort(port);
	/* poison the port so a late user faults rather than corrupts */
	port->mp_Node.ln_Type = 0xff;
	port->mp_MsgList.lh_Head = (struct Node *)-1;
	FreeSignal(port->mp_SigBit);
	FreeMem(port, sizeof(*port));
}
