#ifndef RESOURCES_CARD_H
#define RESOURCES_CARD_H
/*
 * OpenNDK: card.resource: the PCMCIA slot.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_INTERRUPTS_H
#include <exec/interrupts.h>
#endif

#define CARDRESNAME	"card.resource"

/* A claim on the slot, queued by priority with OwnCard(). */
struct CardHandle {
	struct Node cah_CardNode;
	struct Interrupt *cah_CardRemoved;
	struct Interrupt *cah_CardInserted;
	struct Interrupt *cah_CardStatus;
	UBYTE	cah_CardFlags;
};

/* Filled in by DeviceTuple(). */
struct DeviceTData {
	ULONG	dtd_DTsize;	/* bytes */
	ULONG	dtd_DTspeed;	/* nanoseconds */
	UBYTE	dtd_DTtype;
	UBYTE	dtd_DTflags;
};

/* Where the card's spaces appear; the sizes are V39. */
struct CardMemoryMap {
	UBYTE	*cmm_CommonMemory;
	UBYTE	*cmm_AttributeMemory;
	UBYTE	*cmm_IOMemory;
	ULONG	cmm_CommonMemSize;
	ULONG	cmm_AttributeMemSize;
	ULONG	cmm_IOMemSize;
};

/* cah_CardFlags */
#define CARDB_RESETREMOVE	0
#define CARDF_RESETREMOVE	(1<<0)
#define CARDB_IFAVAILABLE	1
#define CARDF_IFAVAILABLE	(1<<1)
#define CARDB_DELAYOWNERSHIP	2
#define CARDF_DELAYOWNERSHIP	(1<<2)
#define CARDB_POSTSTATUS	3
#define CARDF_POSTSTATUS	(1<<3)

/* ReleaseCard() flags */
#define CARDB_REMOVEHANDLE	0
#define CARDF_REMOVEHANDLE	(1<<0)

/* ReadCardStatus() bits; some lines mean different things for I/O cards */
#define CARD_STATUSB_CCDET	6
#define CARD_STATUSF_CCDET	(1<<6)
#define CARD_STATUSB_BVD1	5
#define CARD_STATUSF_BVD1	(1<<5)
#define CARD_STATUSB_SC		5
#define CARD_STATUSF_SC		(1<<5)
#define CARD_STATUSB_BVD2	4
#define CARD_STATUSF_BVD2	(1<<4)
#define CARD_STATUSB_DA		4
#define CARD_STATUSF_DA		(1<<4)
#define CARD_STATUSB_WR		3
#define CARD_STATUSF_WR		(1<<3)
#define CARD_STATUSB_BSY	2
#define CARD_STATUSF_BSY	(1<<2)
#define CARD_STATUSB_IRQ	2
#define CARD_STATUSF_IRQ	(1<<2)

/* CardProgramVoltage() */
#define CARD_VOLTAGE_0V		0
#define CARD_VOLTAGE_5V		1
#define CARD_VOLTAGE_12V	2

/* CardMiscControl() */
#define CARD_ENABLEB_DIGAUDIO	1
#define CARD_ENABLEF_DIGAUDIO	(1<<1)
#define CARD_DISABLEB_WP	3
#define CARD_DISABLEF_WP	(1<<3)

/* CardMiscControl() interrupt enables (V39) */
#define CARD_INTB_SETCLR	7
#define CARD_INTF_SETCLR	(1<<7)
#define CARD_INTB_BVD1		5
#define CARD_INTF_BVD1		(1<<5)
#define CARD_INTB_SC		5
#define CARD_INTF_SC		(1<<5)
#define CARD_INTB_BVD2		4
#define CARD_INTF_BVD2		(1<<4)
#define CARD_INTB_DA		4
#define CARD_INTF_DA		(1<<4)
#define CARD_INTB_BSY		2
#define CARD_INTF_BSY		(1<<2)
#define CARD_INTB_IRQ		2
#define CARD_INTF_IRQ		(1<<2)

/* CardInterface() */
#define CARD_INTERFACE_AMIGA_0	0

/* The tuple that marks an executable-in-place card */
#define CISTPL_AMIGAXIP	0x91

struct TP_AmigaXIP {
	UBYTE	TPL_CODE;
	UBYTE	TPL_LINK;
	UBYTE	TP_XIPLOC[4];	/* code address, little endian */
	UBYTE	TP_XIPFLAGS;
	UBYTE	TP_XIPRESRV;
};

/* TP_XIPFLAGS */
#define XIPFLAGSB_AUTORUN	0
#define XIPFLAGSF_AUTORUN	(1<<0)

#endif /* RESOURCES_CARD_H */
