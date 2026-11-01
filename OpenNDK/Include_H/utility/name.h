#ifndef UTILITY_NAME_H
#define UTILITY_NAME_H
/*
 * OpenNDK: named objects and name spaces (V39).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* The public part of a named object. */
struct NamedObject {
	APTR	no_Object;	/* the user's data */
};

/* Tags for AllocNamedObject() */
#define ANO_NameSpace	4000
#define ANO_UserSpace	4001
#define ANO_Priority	4002
#define ANO_Flags	4003

/* Name space flags */
#define NSB_NODUPS	0
#define NSB_CASE	1

#define NSF_NODUPS	(1L<<NSB_NODUPS)	/* names must be unique */
#define NSF_CASE	(1L<<NSB_CASE)		/* names compare case sensitive */

#endif /* UTILITY_NAME_H */
