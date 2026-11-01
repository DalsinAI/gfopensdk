#ifndef DOS_RDARGS_H
#define DOS_RDARGS_H
/*
 * OpenNDK: ReadArgs()'s input source and state.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif

/* A string to parse in place of the command line */
struct CSource {
	STRPTR	CS_Buffer;
	LONG	CS_Length;
	LONG	CS_CurChr;	/* where parsing has reached */
};

/* ReadArgs()'s control block; allocate it with
 * AllocDosObject(DOS_RDARGS) when filling any field */
struct RDArgs {
	struct CSource RDA_Source;	/* the input, when CS_Buffer is set */
	LONG	RDA_DAList;		/* private */
	STRPTR	RDA_Buffer;		/* optional buffer for the answers */
	LONG	RDA_BufSiz;
	STRPTR	RDA_ExtHelp;		/* text shown for "?" */
	LONG	RDA_Flags;		/* RDAF_ */
};

#define RDAB_STDIN	0	/* read from Input() */
#define RDAF_STDIN	(1L<<RDAB_STDIN)
#define RDAB_NOALLOC	1	/* use only RDA_Buffer */
#define RDAF_NOALLOC	(1L<<RDAB_NOALLOC)
#define RDAB_NOPROMPT	2	/* never prompt for missing arguments */
#define RDAF_NOPROMPT	(1L<<RDAB_NOPROMPT)

#define MAX_TEMPLATE_ITEMS	100
#define MAX_MULTIARGS		128

#endif /* DOS_RDARGS_H */
