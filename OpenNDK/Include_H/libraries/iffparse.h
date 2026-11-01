#ifndef LIBRARIES_IFFPARSE_H
#define LIBRARIES_IFFPARSE_H
/*
 * OpenNDK: iffparse.library's handles, contexts, errors and codes.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef DEVICES_CLIPBOARD_H
#include <devices/clipboard.h>
#endif

/* An IFF stream being read or written; AllocIFF() makes it */
struct IFFHandle {
	ULONG	iff_Stream;	/* the stream hook's own: a file, a clip... */
	ULONG	iff_Flags;	/* IFFF_ */
	LONG	iff_Depth;	/* how many chunks are open */
	/* private fields follow */
};

/* iff_Flags */
#define IFFF_READ	0L
#define IFFF_WRITE	1L
#define IFFF_RWBITS	(IFFF_READ | IFFF_WRITE)
#define IFFF_FSEEK	(1L<<1)		/* the stream seeks forward */
#define IFFF_RSEEK	(1L<<2)		/* the stream seeks both ways */
#define IFFF_RESERVED	0xFFFF0000L

/* What a stream hook is given */
struct IFFStreamCmd {
	LONG	sc_Command;	/* IFFCMD_ */
	APTR	sc_Buf;
	LONG	sc_NBytes;
};

/* One open chunk */
struct ContextNode {
	struct MinNode	cn_Node;
	LONG		cn_ID;
	LONG		cn_Type;
	LONG		cn_Size;	/* of the chunk's data */
	LONG		cn_Scan;	/* bytes read or written so far */
	/* private fields follow */
};

/* A piece of data stored with a context */
struct LocalContextItem {
	struct MinNode	lci_Node;
	ULONG		lci_ID;
	ULONG		lci_Type;
	ULONG		lci_Ident;
	/* private fields follow */
};

/* A property chunk's data, from FindProp() */
struct StoredProperty {
	LONG	sp_Size;
	APTR	sp_Data;
};

/* One chunk of a collection, from FindCollection() */
struct CollectionItem {
	struct CollectionItem	*ci_Next;
	LONG			ci_Size;
	APTR			ci_Data;
};

/* What OpenClipboard() returns */
struct ClipboardHandle {
	struct IOClipReq	cbh_Req;
	struct MsgPort		cbh_CBport;
	struct MsgPort		cbh_SatisfyPort;
};

/* Errors */
#define IFFERR_EOF	-1L	/* the end of the file */
#define IFFERR_EOC	-2L	/* the end of a context */
#define IFFERR_NOSCOPE	-3L	/* no valid scope for a property */
#define IFFERR_NOMEM	-4L
#define IFFERR_READ	-5L
#define IFFERR_WRITE	-6L
#define IFFERR_SEEK	-7L
#define IFFERR_MANGLED	-8L	/* the data is corrupt */
#define IFFERR_SYNTAX	-9L	/* not good IFF */
#define IFFERR_NOTIFF	-10L	/* not an IFF file at all */
#define IFFERR_NOHOOK	-11L	/* no stream hook */
#define IFF_RETURN2CLIENT -12L	/* a handler asks ParseIFF() to return */

/* An ID from four characters */
#define MAKE_ID(a,b,c,d)	\
	((ULONG)(a)<<24 | (ULONG)(b)<<16 | (ULONG)(c)<<8 | (ULONG)(d))

/* The grouping chunks */
#define ID_FORM		MAKE_ID('F','O','R','M')
#define ID_LIST		MAKE_ID('L','I','S','T')
#define ID_CAT		MAKE_ID('C','A','T',' ')
#define ID_PROP		MAKE_ID('P','R','O','P')
#define ID_NULL		MAKE_ID(' ',' ',' ',' ')

/* Identities of the library's own context items */
#define IFFLCI_PROP		MAKE_ID('p','r','o','p')
#define IFFLCI_COLLECTION	MAKE_ID('c','o','l','l')
#define IFFLCI_ENTRYHANDLER	MAKE_ID('e','n','h','d')
#define IFFLCI_EXITHANDLER	MAKE_ID('e','x','h','d')

/* ParseIFF()'s control */
#define IFFPARSE_SCAN		0L
#define IFFPARSE_STEP		1L
#define IFFPARSE_RAWSTEP	2L

/* Where StoreLocalItem() puts an item */
#define IFFSLI_ROOT	1L
#define IFFSLI_TOP	2L
#define IFFSLI_PROP	3L

/* PushChunk()'s size when it is not yet known */
#define IFFSIZE_UNKNOWN	-1L

/* Stream hook commands */
#define IFFCMD_INIT	0
#define IFFCMD_CLEANUP	1
#define IFFCMD_READ	2
#define IFFCMD_WRITE	3
#define IFFCMD_SEEK	4
#define IFFCMD_ENTRY	5
#define IFFCMD_EXIT	6
#define IFFCMD_PURGELCI	7

/* Older names for the stream commands */
#define IFFSCC_INIT	IFFCMD_INIT
#define IFFSCC_CLEANUP	IFFCMD_CLEANUP
#define IFFSCC_READ	IFFCMD_READ
#define IFFSCC_WRITE	IFFCMD_WRITE
#define IFFSCC_SEEK	IFFCMD_SEEK

#endif /* LIBRARIES_IFFPARSE_H */
