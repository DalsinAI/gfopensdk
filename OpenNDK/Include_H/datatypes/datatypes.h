#ifndef DATATYPES_DATATYPES_H
#define DATATYPES_DATATYPES_H
/*
 * OpenNDK: datatypes.library's descriptors, tools, sources and errors.
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
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

/* A descriptor file: FORM DTYP */
#define ID_DTYP	MAKE_ID('D','T','Y','P')

/* Its header chunk */
#define ID_DTHD	MAKE_ID('D','T','H','D')

/* What a data type is and how it is recognised */
struct DataTypeHeader {
	STRPTR	dth_Name;	/* a descriptive name */
	STRPTR	dth_BaseName;	/* the class's base name */
	STRPTR	dth_Pattern;	/* a file name pattern */
	WORD	*dth_Mask;	/* the first bytes to compare; -1 matches any */
	ULONG	dth_GroupID;	/* GID_ */
	ULONG	dth_ID;		/* the IFF FORM type, or an ID of its own */
	WORD	dth_MaskLen;	/* entries in dth_Mask */
	WORD	dth_Pad;
	UWORD	dth_Flags;	/* DTF_ */
	UWORD	dth_Priority;
};

#define DTHSIZE	sizeof(struct DataTypeHeader)

/* dth_Flags */
#define DTF_TYPE_MASK	0x000F
#define DTF_BINARY	0x0000
#define DTF_ASCII	0x0001
#define DTF_IFF		0x0002
#define DTF_MISC	0x0003

#define DTF_CASE	0x0010	/* the mask is case sensitive */
#define DTF_SYSTEM1	0x1000	/* the system's own */

/* dth_GroupID: the kinds of data */
#define GID_SYSTEM	MAKE_ID('s','y','s','t')
#define GID_TEXT	MAKE_ID('t','e','x','t')
#define GID_DOCUMENT	MAKE_ID('d','o','c','u')
#define GID_SOUND	MAKE_ID('s','o','u','n')
#define GID_INSTRUMENT	MAKE_ID('i','n','s','t')
#define GID_MUSIC	MAKE_ID('m','u','s','i')
#define GID_PICTURE	MAKE_ID('p','i','c','t')
#define GID_ANIMATION	MAKE_ID('a','n','i','m')
#define GID_MOVIE	MAKE_ID('m','o','v','i')

/* The descriptor's recognition code */
#define ID_CODE	MAKE_ID('D','T','C','D')

/* What a descriptor's recognition hook is given */
struct DTHookContext {
	struct Library		*dthc_SysBase;
	struct Library		*dthc_DOSBase;
	struct Library		*dthc_IFFParseBase;
	struct Library		*dthc_UtilityBase;

	/* for a file */
	BPTR			dthc_Lock;
	struct FileInfoBlock	*dthc_FIB;
	BPTR			dthc_FileHandle;
	struct IFFHandle	*dthc_IFF;	/* for IFF data only */
	STRPTR			dthc_Buffer;	/* the first bytes of the data */
	ULONG			dthc_BufferLength;
};

/* A descriptor's tool chunk */
#define ID_TOOL	MAKE_ID('D','T','T','L')

struct Tool {
	UWORD	tn_Which;	/* TW_ */
	UWORD	tn_Flags;	/* TF_ */
	STRPTR	tn_Program;	/* the command to run */
};

/* tn_Which */
#define TW_INFO		1
#define TW_BROWSE	2
#define TW_EDIT		3
#define TW_PRINT	4
#define TW_MAIL		5

/* tn_Flags */
#define TF_LAUNCH_MASK	0x000F
#define TF_SHELL	0x0001
#define TF_WORKBENCH	0x0002
#define TF_RX		0x0003

/* Tags for finding and launching tools */
#define TOOLA_Dummy		(TAG_USER)
#define TOOLA_Program		(TOOLA_Dummy + 1)
#define TOOLA_Which		(TOOLA_Dummy + 2)
#define TOOLA_LaunchType	(TOOLA_Dummy + 3)

/* A descriptor's tag chunk */
#define ID_TAGS	MAKE_ID('D','T','T','G')

#ifndef ID_NAME
#define ID_NAME	MAKE_ID('N','A','M','E')
#endif

/* A data type, from ObtainDataTypeA(); read only */
struct DataType {
	struct Node		dtn_Node1;	/* the system's */
	struct Node		dtn_Node2;	/* the system's */
	struct DataTypeHeader	*dtn_Header;
	struct List		dtn_ToolList;	/* struct ToolNode */
	STRPTR			dtn_FunctionName;
	struct TagItem		*dtn_AttrList;
	ULONG			dtn_Length;	/* of the whole block */
};

#define DTNSIZE	sizeof(struct DataType)

/* One of a data type's tools */
struct ToolNode {
	struct Node	tn_Node;
	struct Tool	tn_Tool;
	ULONG		tn_Length;	/* of the whole block */
};

#define TNSIZE	sizeof(struct ToolNode)

/* Errors (IoErr() and DTA_ErrorNumber) */
#define DTERROR_UNKNOWN_DATATYPE	2000
#define DTERROR_COULDNT_SAVE		2001
#define DTERROR_COULDNT_OPEN		2002
#define DTERROR_COULDNT_SEND_MESSAGE	2003
#define DTERROR_COULDNT_OPEN_CLIPBOARD	2004
#define DTERROR_Reserved		2005
#define DTERROR_UNKNOWN_COMPRESSION	2006
#define DTERROR_NOT_ENOUGH_DATA		2007
#define DTERROR_INVALID_DATA		2008
#define DTERROR_NOT_AVAILABLE		2009

/* GetDTString()'s message numbers start here */
#define DTMSG_TYPE_OFFSET	2100

/* A trigger method an object offers */
struct DTMethod {
	STRPTR	dtm_Label;	/* for a menu or gadget */
	STRPTR	dtm_Command;	/* the ARexx command */
	ULONG	dtm_Method;	/* the STM_ trigger */
};

/* the old names, as the OS 3.2 header keeps them */
#define DATATYPE
#define TSIZE			sizeof(struct Tool)

#endif /* DATATYPES_DATATYPES_H */
