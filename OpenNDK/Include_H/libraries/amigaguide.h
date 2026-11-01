#ifndef LIBRARIES_AMIGAGUIDE_H
#define LIBRARIES_AMIGAGUIDE_H
/*
 * OpenNDK: amigaguide.library's structures, tags, messages and codes.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef INTUITION_SCREENS_H
#include <intuition/screens.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif

/* Message types a viewer sends its client (agm_Type) */
#define APSH_TOOL_ID		11000L
#define StartupMsgID		(APSH_TOOL_ID+1L)
#define LoginToolID		(APSH_TOOL_ID+2L)
#define LogoutToolID		(APSH_TOOL_ID+3L)
#define ShutdownMsgID		(APSH_TOOL_ID+4L)
#define ActivateToolID		(APSH_TOOL_ID+5L)
#define DeactivateToolID	(APSH_TOOL_ID+6L)
#define ActiveToolID		(APSH_TOOL_ID+7L)
#define InactiveToolID		(APSH_TOOL_ID+8L)
#define ToolStatusID		(APSH_TOOL_ID+9L)
#define ToolCmdID		(APSH_TOOL_ID+10L)
#define ToolCmdReplyID		(APSH_TOOL_ID+11L)
#define ShutdownToolID		(APSH_TOOL_ID+12L)

/* Attributes */
#define AGA_Dummy		(TAG_USER)
#define AGA_Path		(AGA_Dummy+1)
#define AGA_XRefList		(AGA_Dummy+2)
#define AGA_Activate		(AGA_Dummy+3)
#define AGA_Context		(AGA_Dummy+4)
#define AGA_HelpGroup		(AGA_Dummy+5)
#define AGA_Reserved1		(AGA_Dummy+6)
#define AGA_Reserved2		(AGA_Dummy+7)
#define AGA_Reserved3		(AGA_Dummy+8)
#define AGA_ARexxPort		(AGA_Dummy+9)
#define AGA_ARexxPortName	(AGA_Dummy+10)
#define AGA_Secure		(AGA_Dummy+11)

typedef void *AMIGAGUIDECONTEXT;

/* A message from an asynchronous viewer */
struct AmigaGuideMsg {
	struct Message	agm_Msg;
	ULONG		agm_Type;	/* one of the IDs above */
	APTR		agm_Data;
	ULONG		agm_DSize;
	ULONG		agm_DType;
	ULONG		agm_Pri_Ret;	/* the primary result */
	ULONG		agm_Sec_Ret;	/* the secondary result */
	APTR		agm_System1;
	APTR		agm_System2;
};

/* What OpenAmigaGuideA() and OpenAmigaGuideAsyncA() are given */
struct NewAmigaGuide {
	BPTR		nag_Lock;	/* the directory nag_Name is in */
	STRPTR		nag_Name;	/* the database */
	struct Screen	*nag_Screen;
	STRPTR		nag_PubScreen;
	STRPTR		nag_HostPort;	/* an application's ARexx port */
	STRPTR		nag_ClientPort;	/* the viewer's own ARexx port's base name */
	STRPTR		nag_BaseName;
	ULONG		nag_Flags;	/* HTF_ */
	STRPTR		*nag_Context;	/* NULL-ended node names, for context help */
	STRPTR		nag_Node;	/* the node to show first */
	LONG		nag_Line;	/* and its line */
	struct TagItem	*nag_Extens;
	VOID		*nag_Client;	/* private */
};

/* nag_Flags */
#define HTF_LOAD_INDEX	(1L<<0)
#define HTF_LOAD_ALL	(1L<<1)
#define HTF_CACHE_NODE	(1L<<2)
#define HTF_CACHE_DB	(1L<<3)
#define HTF_UNIQUE	(1L<<15)	/* one viewer of the name only */
#define HTF_NOACTIVATE	(1L<<16)

#define HTFC_SYSGADS	0x80000000

/* Callback IDs */
#define HTH_OPEN	0
#define HTH_CLOSE	1

/* Errors */
#define HTERR_NOT_ENOUGH_MEMORY		100L
#define HTERR_CANT_OPEN_DATABASE	101L
#define HTERR_CANT_FIND_NODE		102L
#define HTERR_CANT_OPEN_NODE		103L
#define HTERR_CANT_OPEN_WINDOW		104L
#define HTERR_INVALID_COMMAND		105L
#define HTERR_CANT_COMPLETE		106L
#define HTERR_PORT_CLOSED		107L
#define HTERR_CANT_CREATE_PORT		108L
#define HTERR_KEYWORD_NOT_FOUND		113L

/* A cross reference, as AGA_XRefList lists them */
struct XRef {
	struct Node	xr_Node;
	UWORD		xr_Pad;
	struct DocFile	*xr_DF;		/* private */
	STRPTR		xr_File;
	STRPTR		xr_Name;	/* the node's name */
	LONG		xr_Line;
	ULONG		xr_Reserved[2];
};

#define XRSIZE	(sizeof (struct XRef))

/* xr_Node.ln_Type */
#define XR_GENERIC	0
#define XR_FUNCTION	1
#define XR_COMMAND	2
#define XR_INCLUDE	3
#define XR_MACRO	4
#define XR_STRUCT	5
#define XR_FIELD	6
#define XR_TYPEDEF	7
#define XR_DEFINE	8

/* A dynamic node host, from AddAmigaGuideHostA() */
struct AmigaGuideHost {
	struct Hook	agh_Dispatcher;	/* called with the HM_ messages */
	ULONG		agh_Reserved;
	ULONG		agh_Flags;
	ULONG		agh_UseCnt;
	APTR		agh_SystemData;
	APTR		agh_UserData;
};

typedef struct AmigaGuideHost *AMIGAGUIDEHOST;

/* The host's methods */
#define HM_FINDNODE	1
#define HM_OPENNODE	2
#define HM_CLOSENODE	3
#define HM_EXPUNGE	10

/* HM_FINDNODE */
struct opFindHost {
	ULONG		MethodID;
	struct TagItem	*ofh_Attrs;
	STRPTR		ofh_Node;	/* the node asked for */
	STRPTR		ofh_TOC;	/* the host fills these in */
	STRPTR		ofh_Title;
	STRPTR		ofh_Next;
	STRPTR		ofh_Prev;
};

/* HM_OPENNODE and HM_CLOSENODE */
struct opNodeIO {
	ULONG		MethodID;
	struct TagItem	*onm_Attrs;
	STRPTR		onm_Node;
	STRPTR		onm_FileName;	/* the node's text from a file */
	STRPTR		onm_DocBuffer;	/* or from memory */
	ULONG		onm_BuffLen;
	ULONG		onm_Flags;	/* HTNF_ */
};

/* onm_Flags */
#define HTNF_KEEP	(1L<<0)	/* keep the node in memory */
#define HTNF_RESERVED1	(1L<<1)
#define HTNF_RESERVED2	(1L<<2)
#define HTNF_ASCII	(1L<<3)	/* the node is plain text */
#define HTNF_RESERVED3	(1L<<4)
#define HTNF_CLEAN	(1L<<5)	/* free the buffer when done */
#define HTNF_DONE	(1L<<6)	/* nothing more to do */

/* onm_Attrs */
#define HTNA_Dummy	(TAG_USER)
#define HTNA_Screen	(HTNA_Dummy+1)
#define HTNA_Pens	(HTNA_Dummy+2)
#define HTNA_Rectangle	(HTNA_Dummy+3)
#define HTNA_HelpGroup	(HTNA_Dummy+5)

/* HM_EXPUNGE */
struct opExpungeNode {
	ULONG		MethodID;
	struct TagItem	*oen_Attrs;
};

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif

#endif /* LIBRARIES_AMIGAGUIDE_H */
