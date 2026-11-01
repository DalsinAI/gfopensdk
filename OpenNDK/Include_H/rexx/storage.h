#ifndef REXX_STORAGE_H
#define REXX_STORAGE_H
/*
 * OpenNDK: ARexx's strings, argument blocks, messages and resources.
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
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif

/* An interpreter string: its value as a number, then the text */
struct NexxStr {
	LONG	ns_Ivalue;	/* the integer value */
	UWORD	ns_Length;
	UBYTE	ns_Flags;	/* NSF_ */
	UBYTE	ns_Hash;
	BYTE	ns_Buff[8];	/* the text, NUL ended; longer strings run on */
};

#define IVALUE(nsPtr)	((nsPtr)->ns_Ivalue)

/* The head and the NUL a string adds to its length */
#define NXADDLEN	9

/* ns_Flags */
#define NSB_KEEP	0	/* a permanent string */
#define NSB_STRING	1	/* has a string value */
#define NSB_NOTNUM	2	/* is not a number */
#define NSB_NUMBER	3	/* has a numeric value */
#define NSB_BINARY	4	/* the integer value is valid */
#define NSB_FLOAT	5	/* the value is floating point */
#define NSB_EXT		6	/* an external string */
#define NSB_SOURCE	7	/* part of the program's source */

#define NSF_KEEP	(1<<NSB_KEEP)
#define NSF_STRING	(1<<NSB_STRING)
#define NSF_NOTNUM	(1<<NSB_NOTNUM)
#define NSF_NUMBER	(1<<NSB_NUMBER)
#define NSF_BINARY	(1<<NSB_BINARY)
#define NSF_FLOAT	(1<<NSB_FLOAT)
#define NSF_EXT		(1<<NSB_EXT)
#define NSF_SOURCE	(1<<NSB_SOURCE)

/* Combinations */
#define NSF_INTNUM	(NSF_NUMBER | NSF_BINARY | NSF_STRING)
#define NSF_DPNUM	(NSF_NUMBER | NSF_FLOAT)
#define NSF_ALPHA	(NSF_NOTNUM | NSF_STRING)
#define NSF_OWNED	(NSF_SOURCE | NSF_EXT | NSF_KEEP)
#define KEEPSTR		(NSF_STRING | NSF_SOURCE | NSF_NOTNUM)
#define KEEPNUM		(NSF_STRING | NSF_SOURCE | NSF_NUMBER | NSF_BINARY)

/* An argstring's block; the argstring points at ra_Buff */
struct RexxArg {
	LONG	ra_Size;	/* the whole allocation */
	UWORD	ra_Length;
	UBYTE	ra_Flags;
	UBYTE	ra_Hash;
	BYTE	ra_Buff[8];
};

/* The message ARexx and its hosts exchange */
struct RexxMsg {
	struct Message	rm_Node;
	APTR		rm_TaskBlock;	/* the interpreter's */
	APTR		rm_LibBase;	/* rexxsyslib.library's base */
	LONG		rm_Action;	/* the command code and flags */
	LONG		rm_Result1;	/* the return code */
	LONG		rm_Result2;	/* a result string or a secondary code */
	STRPTR		rm_Args[16];	/* argstrings */

	/* extension fields, for the interpreter */
	struct MsgPort	*rm_PassPort;
	STRPTR		rm_CommAddr;	/* the host's port name */
	STRPTR		rm_FileExt;	/* the scripts' file extension */
	LONG		rm_Stdin;	/* input stream */
	LONG		rm_Stdout;	/* output stream */
	LONG		rm_avail;
};

/* Arguments by number */
#define ARG0(rmp)	((rmp)->rm_Args[0])
#define ARG1(rmp)	((rmp)->rm_Args[1])
#define ARG2(rmp)	((rmp)->rm_Args[2])

#define MAXRMARG	15	/* the highest argument number */

/* rm_Action: command codes */
#define RXCOMM		0x01000000	/* a command */
#define RXFUNC		0x02000000	/* a function call */
#define RXCLOSE		0x03000000	/* close the port */
#define RXQUERY		0x04000000
#define RXADDFH		0x07000000	/* add a function host */
#define RXADDLIB	0x08000000	/* add a function library */
#define RXREMLIB	0x09000000
#define RXADDCON	0x0A000000	/* add a clip list entry */
#define RXREMCON	0x0B000000
#define RXTCOPN		0x0C000000	/* open the trace console */
#define RXTCCLS		0x0D000000	/* close it */

/* rm_Action: modifier flags */
#define RXFB_NOIO	16	/* no inherited IO */
#define RXFB_RESULT	17	/* a result string is wanted */
#define RXFB_STRING	18	/* the command is a string, not a file */
#define RXFB_TOKEN	19	/* split the command into tokens */
#define RXFB_NONRET	20	/* no reply is wanted */
#define RXFB_SCRIPT	21	/* the command is a script file */

#define RXFF_NOIO	(1L<<RXFB_NOIO)
#define RXFF_RESULT	(1L<<RXFB_RESULT)
#define RXFF_STRING	(1L<<RXFB_STRING)
#define RXFF_TOKEN	(1L<<RXFB_TOKEN)
#define RXFF_NONRET	(1L<<RXFB_NONRET)
#define RXFF_SCRIPT	(1L<<RXFB_SCRIPT)

#define RXCODEMASK	0xFF000000
#define RXARGMASK	0x0000000F

/* An entry of one of the resource lists */
struct RexxRsrc {
	struct Node	rr_Node;
	WORD		rr_Func;	/* a library's function offset */
	APTR		rr_Base;	/* a library's base */
	LONG		rr_Size;	/* the whole allocation */
	LONG		rr_Arg1;
	LONG		rr_Arg2;
};

/* rr_Node.ln_Type */
#define RRT_ANY		0
#define RRT_LIB		1	/* a function library */
#define RRT_PORT	2	/* a public port */
#define RRT_FILE	3	/* a file IoBuff */
#define RRT_HOST	4	/* a function host */
#define RRT_CLIP	5	/* a clip list entry */

/* The interpreter's global data area */
#define GLOBALSZ	200

/* A running program's environment */
struct RexxTask {
	BYTE		rt_Global[GLOBALSZ];
	struct MsgPort	rt_MsgPort;
	UBYTE		rt_Flags;	/* RTF_ */
	BYTE		rt_SigBit;
	APTR		rt_ClientID;
	APTR		rt_MsgPkt;
	APTR		rt_TaskID;
	APTR		rt_RexxPort;
	APTR		rt_ErrTrap;
	APTR		rt_StackPtr;
	struct List	rt_Header1;	/* the environment's lists */
	struct List	rt_Header2;
	struct List	rt_Header3;
	struct List	rt_Header4;
	struct List	rt_Header5;
};

/* rt_Flags */
#define RTFB_TRACE	0	/* tracing on */
#define RTFB_HALT	1	/* halt requested */
#define RTFB_SUSP	2	/* suspend requested */
#define RTFB_TCUSE	3	/* the trace console is in use */
#define RTFB_WAIT	6	/* waiting for a reply */
#define RTFB_CLOSE	7	/* closing */

/* Memory is handed out in these units */
#define MEMQUANT	16L
#define MEMMASK		0xFFFFFFF0

#define MEMQUICK	(1L<<0)
#define MEMCLEAR	(1L<<16)

/* A node of the source list */
struct SrcNode {
	struct SrcNode	*sn_Succ;
	struct SrcNode	*sn_Pred;
	APTR		sn_Ptr;		/* the block */
	LONG		sn_Size;	/* and its size */
};

/* a message from ARexx: it carries rexxsyslib's base and a task block */
#define CHECKREXXMSG(msg)	(RexxSysBase && (msg)->rm_LibBase == RexxSysBase && (msg)->rm_TaskBlock && IsRexxMsg(msg))

#endif /* REXX_STORAGE_H */
