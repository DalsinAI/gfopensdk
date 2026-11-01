/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* CreateExtIO, DeleteExtIO, CreateStdIO and DeleteStdIO: I/O requests
 * that reply to a given port. */
#include "alib.h"

struct IORequest *CreateExtIO(CONST struct MsgPort *port, LONG ioSize)
{
	struct IORequest *io;

	if (!port || ioSize < (LONG)sizeof(struct IORequest))
		return NULL;
	io = (struct IORequest *)AllocMem((ULONG)ioSize, MEMF_PUBLIC | MEMF_CLEAR);
	if (io) {
		io->io_Message.mn_Node.ln_Type = NT_REPLYMSG;
		io->io_Message.mn_ReplyPort = (struct MsgPort *)port;
		io->io_Message.mn_Length = (UWORD)ioSize;
	}
	return io;
}

VOID DeleteExtIO(struct IORequest *io)
{
	if (!io)
		return;
	io->io_Message.mn_Node.ln_Type = 0xff;
	io->io_Device = (struct Device *)-1;
	io->io_Unit = (struct Unit *)-1;
	FreeMem(io, io->io_Message.mn_Length);
}

struct IOStdReq *CreateStdIO(CONST struct MsgPort *port)
{
	return (struct IOStdReq *)CreateExtIO(port, sizeof(struct IOStdReq));
}

VOID DeleteStdIO(struct IOStdReq *io)
{
	DeleteExtIO((struct IORequest *)io);
}
