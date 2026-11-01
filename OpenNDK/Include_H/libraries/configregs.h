#ifndef LIBRARIES_CONFIGREGS_H
#define LIBRARIES_CONFIGREGS_H
/*
 * OpenNDK: the AutoConfig registers of Zorro II and III expansion
 * boards, and the diagnostic area a boot ROM carries.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* A board's identity, as read from its config area (stored in the
 * ConfigDev with the inverted nibbles already put right) */
struct ExpansionRom {
	UBYTE	er_Type;		/* ERT_ */
	UBYTE	er_Product;
	UBYTE	er_Flags;		/* ERF_ */
	UBYTE	er_Reserved03;
	UWORD	er_Manufacturer;
	ULONG	er_SerialNumber;
	UWORD	er_InitDiagVec;		/* offset of the DiagArea */
	UBYTE	er_Reserved0c;
	UBYTE	er_Reserved0d;
	UBYTE	er_Reserved0e;
	UBYTE	er_Reserved0f;
};

/* The registers written to configure a board, following the
 * ExpansionRom in config space */
struct ExpansionControl {
	UBYTE	ec_Interrupt;		/* ECI */
	UBYTE	ec_Z3_HighBase;		/* Zorro III: address bits 24-31 */
	UBYTE	ec_BaseAddress;		/* writing it configures the board */
	UBYTE	ec_Shutup;		/* writing it shuts the board up */
	UBYTE	ec_Reserved14;
	UBYTE	ec_Reserved15;
	UBYTE	ec_Reserved16;
	UBYTE	ec_Reserved17;
	UBYTE	ec_Reserved18;
	UBYTE	ec_Reserved19;
	UBYTE	ec_Reserved1a;
	UBYTE	ec_Reserved1b;
	UBYTE	ec_Reserved1c;
	UBYTE	ec_Reserved1d;
	UBYTE	ec_Reserved1e;
	UBYTE	ec_Reserved1f;
};

/* The address map */
#define E_SLOTSIZE		0x10000
#define E_SLOTMASK		0xffff
#define E_SLOTSHIFT		16

#define E_EXPANSIONBASE		0x00e80000	/* Zorro II config area */
#define EZ3_EXPANSIONBASE	0xff000000	/* Zorro III config area */
#define E_EXPANSIONSIZE		0x00080000
#define E_EXPANSIONSLOTS	8

#define E_MEMORYBASE		0x00200000	/* Zorro II memory space */
#define E_MEMORYSIZE		0x00800000
#define E_MEMORYSLOTS		128

#define EZ3_CONFIGAREA		0x40000000	/* Zorro III space */
#define EZ3_CONFIGAREAEND	0x7FFFFFFF
#define EZ3_SIZEGRANULARITY	0x00080000

/* er_Type */
#define ERT_TYPEMASK	0xc0
#define ERT_TYPEBIT	6
#define ERT_TYPESIZE	2
#define ERT_NEWBOARD	0xc0
#define ERT_ZORROII	ERT_NEWBOARD
#define ERT_ZORROIII	0x80

#define ERTB_MEMLIST	5	/* link the board's memory into the system */
#define ERTB_DIAGVALID	4	/* a boot ROM is present */
#define ERTB_CHAINEDCONFIG 3	/* another board follows on this card */

#define ERTF_MEMLIST	(1<<5)
#define ERTF_DIAGVALID	(1<<4)
#define ERTF_CHAINEDCONFIG (1<<3)

#define ERT_MEMMASK	0x07
#define ERT_MEMBIT	0
#define ERT_MEMSIZE	3

/* er_Flags */
#define ERFB_MEMSPACE	7	/* wants memory space */
#define ERFB_NOSHUTUP	6	/* cannot be shut up */
#define ERFB_EXTENDED	5	/* Zorro III size code is extended */
#define ERFB_ZORRO_III	4	/* Zorro III: must be 0 */

#define ERFF_MEMSPACE	(1<<7)
#define ERFF_NOSHUTUP	(1<<6)
#define ERFF_EXTENDED	(1<<5)
#define ERFF_ZORRO_III	(1<<4)

#define ERT_Z3_SSMASK	0x0F	/* Zorro III sub-size */
#define ERT_Z3_SSBIT	0
#define ERT_Z3_SSSIZE	4

/* ec_Interrupt */
#define ECIB_INTENA		1
#define ECIB_RESET		3
#define ECIB_INT2PEND		4
#define ECIB_INT6PEND		5
#define ECIB_INT7PEND		6
#define ECIB_INTERRUPTING	7

#define ECIF_INTENA		(1<<1)
#define ECIF_RESET		(1<<3)
#define ECIF_INT2PEND		(1<<4)
#define ECIF_INT6PEND		(1<<5)
#define ECIF_INT7PEND		(1<<6)
#define ECIF_INTERRUPTING	(1<<7)

/* Size and position helpers */
#define ERT_MEMNEEDED(t) \
	(((t)&ERT_MEMMASK) ? 0x10000 << (((t)&ERT_MEMMASK) - 1) : 0x800000)
#define ERT_SLOTSNEEDED(t) \
	(((t)&ERT_MEMMASK) ? 1 << (((t)&ERT_MEMMASK) - 1) : 0x80)
#define EC_MEMADDR(slot)	((slot) << E_SLOTSHIFT)

/* Byte offsets of a register within config space */
#define EROFFSET(er)	((int)&((struct ExpansionRom *)0)->er)
#define ECOFFSET(ec) \
	(sizeof(struct ExpansionRom) + ((int)&((struct ExpansionControl *)0)->ec))

/* A boot ROM's header, at er_InitDiagVec from the board's base */
struct DiagArea {
	UBYTE	da_Config;	/* DAC_ */
	UBYTE	da_Flags;
	UWORD	da_Size;	/* bytes to copy to RAM */
	UWORD	da_DiagPoint;	/* offsets from the DiagArea */
	UWORD	da_BootPoint;
	UWORD	da_Name;
	UWORD	da_Reserved01;
	UWORD	da_Reserved02;
};

/* da_Config */
#define DAC_BUSWIDTH	0xC0
#define DAC_NIBBLEWIDE	0x00
#define DAC_BYTEWIDE	0x40
#define DAC_WORDWIDE	0x80

#define DAC_BOOTTIME	0x30
#define DAC_NEVER	0x00
#define DAC_CONFIGTIME	0x10
#define DAC_BINDTIME	0x20

#endif /* LIBRARIES_CONFIGREGS_H */
