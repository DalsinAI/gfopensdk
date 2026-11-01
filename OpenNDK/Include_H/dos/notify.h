#ifndef DOS_NOTIFY_H
#define DOS_NOTIFY_H
/*
 * OpenNDK: file change notification (StartNotify(), EndNotify()).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef EXEC_TASKS_H
#include <exec/tasks.h>
#endif

/* nm_Class and nm_Code of every notification message */
#define NOTIFY_CLASS	0x40000000
#define NOTIFY_CODE	0x1234

/* What the caller fills in to watch a file or directory */
struct NotifyRequest {
	STRPTR	nr_Name;		/* the object to watch */
	STRPTR	nr_FullName;		/* dos's: the full path */
	ULONG	nr_UserData;
	ULONG	nr_Flags;		/* NRF_ */
	union {
		struct {
			struct MsgPort *nr_Port;	/* NRF_SEND_MESSAGE */
		} nr_Msg;
		struct {
			struct Task *nr_Task;		/* NRF_SEND_SIGNAL */
			UBYTE	nr_SignalNum;
			UBYTE	nr_pad[3];
		} nr_Signal;
	} nr_stuff;
	ULONG	nr_Reserved[4];		/* 0 */
	ULONG	nr_MsgCount;		/* the handler's */
	struct MsgPort *nr_Handler;	/* dos's */
};

/* The message sent for NRF_SEND_MESSAGE */
struct NotifyMessage {
	struct Message	nm_ExecMessage;
	ULONG		nm_Class;	/* NOTIFY_CLASS */
	UWORD		nm_Code;	/* NOTIFY_CODE */
	struct NotifyRequest *nm_NReq;
	ULONG		nm_DoNotTouch;
	ULONG		nm_DoNotTouch2;
};

/* nr_Flags; the high word is the handler's own */
#define NRB_SEND_MESSAGE	0
#define NRB_SEND_SIGNAL		1
#define NRB_WAIT_REPLY		3
#define NRB_NOTIFY_INITIAL	4
#define NRB_MAGIC		31

#define NRF_SEND_MESSAGE	(1L<<NRB_SEND_MESSAGE)
#define NRF_SEND_SIGNAL		(1L<<NRB_SEND_SIGNAL)
#define NRF_WAIT_REPLY		(1L<<NRB_WAIT_REPLY)
#define NRF_NOTIFY_INITIAL	(1L<<NRB_NOTIFY_INITIAL)
#define NRF_MAGIC		(1L<<NRB_MAGIC)

#define NR_HANDLER_FLAGS	0xffff0000

#endif /* DOS_NOTIFY_H */
