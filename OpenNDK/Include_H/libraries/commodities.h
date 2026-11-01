#ifndef LIBRARIES_COMMODITIES_H
#define LIBRARIES_COMMODITIES_H
/*
 * OpenNDK: commodities.library's brokers, objects, messages and codes.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef DEVICES_INPUTEVENT_H
#include <devices/inputevent.h>
#endif

/* What CxBroker() is given to make a broker */
struct NewBroker {
	BYTE		nb_Version;	/* NB_VERSION */
	STRPTR		nb_Name;
	STRPTR		nb_Title;
	STRPTR		nb_Descr;
	WORD		nb_Unique;	/* NBU_ */
	WORD		nb_Flags;	/* COF_ */
	BYTE		nb_Pri;
	struct MsgPort	*nb_Port;
	WORD		nb_ReservedChannel;
};

#define NB_VERSION	5

/* The longest name, title and description, with the NUL */
#define CBD_NAMELEN	24
#define CBD_TITLELEN	40
#define CBD_DESCRLEN	40

/* nb_Unique */
#define NBU_DUPLICATE	0
#define NBU_UNIQUE	1	/* refuse a second broker of the name */
#define NBU_NOTIFY	2	/* and tell the first one about it */

/* nb_Flags */
#define COF_SHOW_HIDE	4	/* the commodity has a window to show */

/* Objects and messages are handles */
typedef LONG CxObj;
typedef LONG CxMsg;

/* A custom object's function */
typedef LONG (*PFL)();

/* Object types */
#define CX_INVALID	0
#define CX_FILTER	1
#define CX_TYPEFILTER	2
#define CX_SEND		3
#define CX_SIGNAL	4
#define CX_TRANSLATE	5
#define CX_BROKER	6
#define CX_DEBUG	7
#define CX_CUSTOM	8
#define CX_ZERO		9

/* Message types */
#define CXM_IEVENT	(1<<5)
#define CXM_COMMAND	(1<<6)

/* Commands to a broker's port */
#define CXCMD_DISABLE	15
#define CXCMD_ENABLE	17
#define CXCMD_APPEAR	19
#define CXCMD_DISAPPEAR	21
#define CXCMD_KILL	23
#define CXCMD_LIST_CHG	27
#define CXCMD_UNIQUE	25

/* CxBroker()'s errors */
#define CBERR_OK	0
#define CBERR_SYSERR	1
#define CBERR_DUP	2
#define CBERR_VERSION	3

/* CxObjError()'s bits */
#define COERR_ISNULL		1
#define COERR_NULLATTACH	2
#define COERR_BADFILTER		4
#define COERR_BADTYPE		8

/* Making the objects (each is a CreateCxObj() call) */
#define CxFilter(d)		CreateCxObj(CX_FILTER, (LONG)(d), 0)
#define CxSender(port, id)	CreateCxObj(CX_SEND, (LONG)(port), (LONG)(id))
#define CxSignal(task, sig)	CreateCxObj(CX_SIGNAL, (LONG)(task), (LONG)(sig))
#define CxTranslate(ie)		CreateCxObj(CX_TRANSLATE, (LONG)(ie), 0)
#define CxDebug(id)		CreateCxObj(CX_DEBUG, (LONG)(id), 0)
#define CxCustom(action, id)	CreateCxObj(CX_CUSTOM, (LONG)(action), (LONG)(id))

/* An input expression: which events a filter passes */
struct InputXpression {
	UBYTE	ix_Version;	/* IX_VERSION */
	UBYTE	ix_Class;	/* IECLASS_ */
	UWORD	ix_Code;
	UWORD	ix_CodeMask;	/* the bits of ix_Code that count */
	UWORD	ix_Qualifier;
	UWORD	ix_QualMask;	/* the qualifier bits that count */
	UWORD	ix_QualSame;	/* IXSYM_: qualifiers that stand for each other */
};

typedef struct InputXpression IX;

#define IX_VERSION	2

/* ix_QualSame */
#define IXSYM_SHIFT	1	/* either shift */
#define IXSYM_CAPS	2	/* either shift, or caps lock */
#define IXSYM_ALT	4	/* either alt */

#define IXSYM_SHIFTMASK	(IEQUALIFIER_LSHIFT | IEQUALIFIER_RSHIFT)
#define IXSYM_CAPSMASK	(IXSYM_SHIFTMASK | IEQUALIFIER_CAPSLOCK)
#define IXSYM_ALTMASK	(IEQUALIFIER_LALT | IEQUALIFIER_RALT)

/* Every qualifier but the relative mouse bit */
#define IX_NORMALQUALS	0x7FFF

/* An expression that matches nothing */
#define NULL_IX(ix)	((ix)->ix_Class == IECLASS_NULL)

#endif /* LIBRARIES_COMMODITIES_H */
