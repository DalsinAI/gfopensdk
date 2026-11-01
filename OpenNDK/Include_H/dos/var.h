#ifndef DOS_VAR_H
#define DOS_VAR_H
/*
 * OpenNDK: shell variables and aliases (SetVar(), GetVar(), FindVar()).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif

/* A local variable, kept on the process's pr_LocalVars list */
struct LocalVar {
	struct Node	lv_Node;	/* ln_Type: LV_; ln_Name: the name */
	UWORD		lv_Flags;
	STRPTR	lv_Value;
	ULONG		lv_Len;
};

/* ln_Type of a LocalVar, and the low byte of the flags argument */
#define LV_VAR		0
#define LV_ALIAS	1

/* Set in the type to skip an entry */
#define LVB_IGNORE	7
#define LVF_IGNORE	0x80

/* The flags argument's upper bits */
#define GVB_GLOBAL_ONLY		8	/* ENV: only */
#define GVF_GLOBAL_ONLY		0x100
#define GVB_LOCAL_ONLY		9	/* this process's only */
#define GVF_LOCAL_ONLY		0x200
#define GVB_BINARY_VAR		10	/* the value is not text */
#define GVF_BINARY_VAR		0x400
#define GVB_DONT_NULL_TERM	11	/* with BINARY: no terminator */
#define GVF_DONT_NULL_TERM	0x800
#define GVB_SAVE_VAR		12	/* also write ENVARC: */
#define GVF_SAVE_VAR		0x1000

#endif /* DOS_VAR_H */
