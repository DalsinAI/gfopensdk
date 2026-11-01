#ifndef HARDWARE_CIA_H
#define HARDWARE_CIA_H
/*
 * OpenNDK: the 8520 CIA chips' registers and bits.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/*
 * Each register sits 256 bytes after the one before. CIA-A is at
 * 0xBFE001 (odd bytes), CIA-B at 0xBFD000 (even bytes).
 */
struct CIA {
	UBYTE	ciapra;
	UBYTE	pad0[0xff];
	UBYTE	ciaprb;
	UBYTE	pad1[0xff];
	UBYTE	ciaddra;
	UBYTE	pad2[0xff];
	UBYTE	ciaddrb;
	UBYTE	pad3[0xff];
	UBYTE	ciatalo;
	UBYTE	pad4[0xff];
	UBYTE	ciatahi;
	UBYTE	pad5[0xff];
	UBYTE	ciatblo;
	UBYTE	pad6[0xff];
	UBYTE	ciatbhi;
	UBYTE	pad7[0xff];
	UBYTE	ciatodlow;
	UBYTE	pad8[0xff];
	UBYTE	ciatodmid;
	UBYTE	pad9[0xff];
	UBYTE	ciatodhi;
	UBYTE	pad10[0xff];
	UBYTE	unusedreg;
	UBYTE	pad11[0xff];
	UBYTE	ciasdr;
	UBYTE	pad12[0xff];
	UBYTE	ciaicr;
	UBYTE	pad13[0xff];
	UBYTE	ciacra;
	UBYTE	pad14[0xff];
	UBYTE	ciacrb;
};

/* Interrupt control register */
#define CIAICRB_TA		0
#define CIAICRB_TB		1
#define CIAICRB_ALRM		2
#define CIAICRB_SP		3
#define CIAICRB_FLG		4
#define CIAICRB_IR		7
#define CIAICRB_SETCLR		7

#define CIAICRF_TA		(1L<<0)
#define CIAICRF_TB		(1L<<1)
#define CIAICRF_ALRM		(1L<<2)
#define CIAICRF_SP		(1L<<3)
#define CIAICRF_FLG		(1L<<4)
#define CIAICRF_IR		(1L<<7)
#define CIAICRF_SETCLR		(1L<<7)

/* Control register A */
#define CIACRAB_START		0
#define CIACRAB_PBON		1
#define CIACRAB_OUTMODE		2
#define CIACRAB_RUNMODE		3
#define CIACRAB_LOAD		4
#define CIACRAB_INMODE		5
#define CIACRAB_SPMODE		6

#define CIACRAF_START		(1L<<0)
#define CIACRAF_PBON		(1L<<1)
#define CIACRAF_OUTMODE		(1L<<2)
#define CIACRAF_RUNMODE		(1L<<3)
#define CIACRAF_LOAD		(1L<<4)
#define CIACRAF_INMODE		(1L<<5)
#define CIACRAF_SPMODE		(1L<<6)

/* Control register B */
#define CIACRBB_START		0
#define CIACRBB_PBON		1
#define CIACRBB_OUTMODE		2
#define CIACRBB_RUNMODE		3
#define CIACRBB_LOAD		4
#define CIACRBB_INMODE0		5
#define CIACRBB_INMODE1		6
#define CIACRBB_ALARM		7

#define CIACRBF_START		(1L<<0)
#define CIACRBF_PBON		(1L<<1)
#define CIACRBF_OUTMODE		(1L<<2)
#define CIACRBF_RUNMODE		(1L<<3)
#define CIACRBF_LOAD		(1L<<4)
#define CIACRBF_INMODE0		(1L<<5)
#define CIACRBF_INMODE1		(1L<<6)
#define CIACRBF_ALARM		(1L<<7)

/* Timer B's input choices */
#define CIACRBF_IN_PHI2		0
#define CIACRBF_IN_CNT		(CIACRBF_INMODE0)
#define CIACRBF_IN_TA		(CIACRBF_INMODE1)
#define CIACRBF_IN_CNT_TA	(CIACRBF_INMODE0|CIACRBF_INMODE1)

/* CIA-A port A: fire buttons, drive status, LED and ROM overlay */
#define CIAB_GAMEPORT1		7
#define CIAB_GAMEPORT0		6
#define CIAB_DSKRDY		5
#define CIAB_DSKTRACK0		4
#define CIAB_DSKPROT		3
#define CIAB_DSKCHANGE		2
#define CIAB_LED		1
#define CIAB_OVERLAY		0

#define CIAF_GAMEPORT1		(1L<<7)
#define CIAF_GAMEPORT0		(1L<<6)
#define CIAF_DSKRDY		(1L<<5)
#define CIAF_DSKTRACK0		(1L<<4)
#define CIAF_DSKPROT		(1L<<3)
#define CIAF_DSKCHANGE		(1L<<2)
#define CIAF_LED		(1L<<1)
#define CIAF_OVERLAY		(1L<<0)

/* CIA-B port A: serial and printer lines */
#define CIAB_COMDTR		7
#define CIAB_COMRTS		6
#define CIAB_COMCD		5
#define CIAB_COMCTS		4
#define CIAB_COMDSR		3
#define CIAB_PRTRSEL		2
#define CIAB_PRTRPOUT		1
#define CIAB_PRTRBUSY		0

#define CIAF_COMDTR		(1L<<7)
#define CIAF_COMRTS		(1L<<6)
#define CIAF_COMCD		(1L<<5)
#define CIAF_COMCTS		(1L<<4)
#define CIAF_COMDSR		(1L<<3)
#define CIAF_PRTRSEL		(1L<<2)
#define CIAF_PRTRPOUT		(1L<<1)
#define CIAF_PRTRBUSY		(1L<<0)

/* CIA-B port B: floppy drive control */
#define CIAB_DSKMOTOR		7
#define CIAB_DSKSEL3		6
#define CIAB_DSKSEL2		5
#define CIAB_DSKSEL1		4
#define CIAB_DSKSEL0		3
#define CIAB_DSKSIDE		2
#define CIAB_DSKDIREC		1
#define CIAB_DSKSTEP		0

#define CIAF_DSKMOTOR		(1L<<7)
#define CIAF_DSKSEL3		(1L<<6)
#define CIAF_DSKSEL2		(1L<<5)
#define CIAF_DSKSEL1		(1L<<4)
#define CIAF_DSKSEL0		(1L<<3)
#define CIAF_DSKSIDE		(1L<<2)
#define CIAF_DSKDIREC		(1L<<1)
#define CIAF_DSKSTEP		(1L<<0)

/* More names from the 3.2 interface */
#define CIACRAB_TODIN		7
#define CIACRAF_TODIN		128

#endif /* HARDWARE_CIA_H */
