#ifndef REXX_REXXIO_H
#define REXX_REXXIO_H
/*
 * OpenNDK: ARexx's file buffers and its port resource.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REXX_STORAGE_H
#include <rexx/storage.h>
#endif

#define RXBUFFSZ	204	/* an IoBuff's buffer */

/* An open file, as a resource node */
struct IoBuff {
	struct RexxRsrc	iobNode;	/* ln_Name is the file's logical name */
	APTR		iobRpt;		/* the next character to read */
	LONG		iobRct;		/* characters left to read */
	LONG		iobDFH;		/* the DOS file handle */
	APTR		iobLock;	/* a DOS lock */
	LONG		iobBct;		/* characters in the buffer */
	BYTE		iobArea[RXBUFFSZ];
};

/* The modes a file is opened in */
#define RXIO_EXIST	-1
#define RXIO_STRF	0
#define RXIO_READ	1
#define RXIO_WRITE	2
#define RXIO_APPEND	3

/* Seek origins */
#define RXIO_BEGIN	-1L
#define RXIO_CURR	0L
#define RXIO_END	1L

/* Fields of a resource node, by use */
#define LLOFFSET(rptr)	((rptr)->rr_Arg1)	/* a library's entry offset */
#define LLVERS(rptr)	((rptr)->rr_Arg2)	/* its version */

#define CLVALUE(rptr)	((STRPTR)(rptr)->rr_Arg1)	/* a clip's value */

/* A public port owned by a program */
struct RexxMsgPort {
	struct RexxRsrc	rmp_Node;
	struct MsgPort	rmp_Port;
	struct List	rmp_ReplyList;
};

/* DOS device types */
#define DT_DEV	0L
#define DT_DIR	1L
#define DT_VOL	2L

/* Packet types for the stack and queue of a console */
#define ACTION_STACK	2002L
#define ACTION_QUEUE	2003L

#endif /* REXX_REXXIO_H */
