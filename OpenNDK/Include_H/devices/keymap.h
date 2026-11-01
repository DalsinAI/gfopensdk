#ifndef DEVICES_KEYMAP_H
#define DEVICES_KEYMAP_H
/*
 * OpenNDK: the keymap: per-key types and the tables that turn raw key
 * codes into characters.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef LIBRARIES_KEYMAP_H
#include <libraries/keymap.h>
#endif

/* Lo tables cover keys 0x00-0x3F, Hi tables keys 0x40-0x77 */
struct KeyMap {
	UBYTE	*km_LoKeyMapTypes;
	ULONG	*km_LoKeyMap;
	UBYTE	*km_LoCapsable;		/* one bit per key */
	UBYTE	*km_LoRepeatable;
	UBYTE	*km_HiKeyMapTypes;
	ULONG	*km_HiKeyMap;
	UBYTE	*km_HiCapsable;
	UBYTE	*km_HiRepeatable;
};

/* A named keymap on keymap.resource's list */
struct KeyMapNode {
	struct Node	kn_Node;
	struct KeyMap	kn_KeyMap;
};

/* keymap.resource */
struct KeyMapResource {
	struct Node	kr_Node;
	struct List	kr_List;	/* struct KeyMapNode */
};

/* Key types (the KeyMapTypes bytes) */
#define KCB_NOP		7	/* the key gives nothing */
#define KCF_NOP		0x80

#define KC_NOQUAL	0
#define KC_VANILLA	7	/* shift, alt and control all apply */
#define KCB_SHIFT	0
#define KCF_SHIFT	0x01
#define KCB_ALT		1
#define KCF_ALT		0x02
#define KCB_CONTROL	2
#define KCF_CONTROL	0x04
#define KCB_DOWNUP	3
#define KCF_DOWNUP	0x08

#define KCB_DEAD	5	/* the entry points to dead-key data */
#define KCF_DEAD	0x20

#define KCB_STRING	6	/* the entry points to strings */
#define KCF_STRING	0x40

/* Dead-key data: the first byte of each pair */
#define DPB_MOD		0	/* a key modified by a dead key */
#define DPF_MOD		0x01
#define DPB_DEAD	3	/* a dead key */
#define DPF_DEAD	0x08

#define DP_2DINDEXMASK	0x0f	/* the dead key's index */
#define DP_2DFACSHIFT	4	/* its factor for double dead keys */

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef LIBRARIES_KEYMAP_H
#include <libraries/keymap.h>
#endif

#endif /* DEVICES_KEYMAP_H */
