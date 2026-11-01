#ifndef HARDWARE_BLIT_H
#define HARDWARE_BLIT_H
/*
 * OpenNDK: blitter register values and the queued blit node.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* Minterms: one bit per combination of the A, B and C sources */
#define ABC	0x80
#define ABNC	0x40
#define ANBC	0x20
#define ANBNC	0x10
#define NABC	0x08
#define NABNC	0x04
#define NANBC	0x02
#define NANBNC	0x01

/* Common minterm combinations */
#define A_OR_B	(ABC | ANBC | NABC | ABNC | ANBNC | NABNC)
#define A_OR_C	(ABC | NABC | ABNC | ANBC | NANBC | ANBNC)
#define A_XOR_C	(NABC | ABNC | NANBC | ANBNC)
#define A_TO_D	(ABC | ANBC | ABNC | ANBNC)

/* bltcon0: which channels are on */
#define BC0B_DEST	8
#define BC0B_SRCC	9
#define BC0B_SRCB	10
#define BC0B_SRCA	11
#define BC0F_DEST	0x100
#define BC0F_SRCC	0x200
#define BC0F_SRCB	0x400
#define BC0F_SRCA	0x800

#define DEST	0x100
#define SRCC	0x200
#define SRCB	0x400
#define SRCA	0x800

#define ASHIFTSHIFT	12	/* bltcon0 bits of the A shift */
#define BSHIFTSHIFT	12	/* bltcon1 bits of the B shift */

/* bltcon1 in area mode */
#define BC1F_DESC	2	/* descending addresses */
#define BLITREVERSE	0x2
#define FILL_CARRYIN	0x4
#define FILL_OR		0x8
#define FILL_XOR	0x10

/* bltcon1 in line mode */
#define LINEMODE	0x1
#define ONEDOT		0x2
#define SUD		0x10
#define SUL		0x8
#define AUL		0x4
#define OVFLAG		0x20
#define SIGNFLAG	0x40

/* The octant codes for line drawing */
#define OCTANT8	24
#define OCTANT7	4
#define OCTANT6	12
#define OCTANT5	28
#define OCTANT4	20
#define OCTANT3	8
#define OCTANT2	0
#define OCTANT1	16

/* bltsize */
#define HSIZEBITS	6
#define VSIZEBITS	(16 - HSIZEBITS)
#define HSIZEMASK	0x3f
#define VSIZEMASK	0x3FF

#define MINBYTESPERROW	128
#define MAXBYTESPERROW	4096

/* A blit queued with QBlit() or QBSBlit(). */
struct bltnode {
	struct bltnode *n;
	int	(*function)();	/* called to start each step */
	char	stat;		/* CLEANUP to have cleanup called */
	short	blitsize;
	short	beamsync;	/* beam position for QBSBlit() */
	int	(*cleanup)();
};

#define CLEANUP	0x40
#define CLEANME	CLEANUP

#endif /* HARDWARE_BLIT_H */
