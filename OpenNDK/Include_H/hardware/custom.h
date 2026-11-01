#ifndef HARDWARE_CUSTOM_H
#define HARDWARE_CUSTOM_H
/*
 * OpenNDK: the custom chip registers, laid out as they sit at 0xDFF000.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* Offsets in the comments are from the start of the register block. */
struct Custom {
	UWORD	bltddat;	/* 000 */
	UWORD	dmaconr;
	UWORD	vposr;
	UWORD	vhposr;
	UWORD	dskdatr;	/* 008 */
	UWORD	joy0dat;
	UWORD	joy1dat;
	UWORD	clxdat;
	UWORD	adkconr;	/* 010 */
	UWORD	pot0dat;
	UWORD	pot1dat;
	UWORD	potinp;
	UWORD	serdatr;	/* 018 */
	UWORD	dskbytr;
	UWORD	intenar;
	UWORD	intreqr;
	APTR	dskpt;		/* 020 */
	UWORD	dsklen;
	UWORD	dskdat;
	UWORD	refptr;		/* 028 */
	UWORD	vposw;
	UWORD	vhposw;
	UWORD	copcon;
	UWORD	serdat;		/* 030 */
	UWORD	serper;
	UWORD	potgo;
	UWORD	joytest;
	UWORD	strequ;		/* 038 */
	UWORD	strvbl;
	UWORD	strhor;
	UWORD	strlong;
	UWORD	bltcon0;	/* 040 */
	UWORD	bltcon1;
	UWORD	bltafwm;
	UWORD	bltalwm;
	APTR	bltcpt;		/* 048 */
	APTR	bltbpt;
	APTR	bltapt;		/* 050 */
	APTR	bltdpt;
	UWORD	bltsize;	/* 058 */
	UBYTE	pad2d;
	UBYTE	bltcon0l;	/* 05B: low byte of bltcon0, ECS */
	UWORD	bltsizv;	/* 05C */
	UWORD	bltsizh;
	UWORD	bltcmod;	/* 060 */
	UWORD	bltbmod;
	UWORD	bltamod;
	UWORD	bltdmod;
	UWORD	pad34[4];	/* 068 */
	UWORD	bltcdat;	/* 070 */
	UWORD	bltbdat;
	UWORD	bltadat;
	UWORD	pad3b[3];
	UWORD	deniseid;	/* 07C */
	UWORD	dsksync;
	ULONG	cop1lc;		/* 080 */
	ULONG	cop2lc;
	UWORD	copjmp1;	/* 088 */
	UWORD	copjmp2;
	UWORD	copins;
	UWORD	diwstrt;
	UWORD	diwstop;	/* 090 */
	UWORD	ddfstrt;
	UWORD	ddfstop;
	UWORD	dmacon;
	UWORD	clxcon;		/* 098 */
	UWORD	intena;
	UWORD	intreq;
	UWORD	adkcon;
	struct AudChannel {	/* 0A0, 16 bytes each */
		UWORD	*ac_ptr;
		UWORD	ac_len;
		UWORD	ac_per;
		UWORD	ac_vol;
		UWORD	ac_dat;
		UWORD	ac_pad[2];
	} aud[4];
	APTR	bplpt[8];	/* 0E0 */
	UWORD	bplcon0;	/* 100 */
	UWORD	bplcon1;
	UWORD	bplcon2;
	UWORD	bplcon3;
	WORD	bpl1mod;	/* 108 */
	WORD	bpl2mod;
	UWORD	bplcon4;
	UWORD	clxcon2;
	UWORD	bpldat[8];	/* 110 */
	APTR	sprpt[8];	/* 120 */
	struct SpriteDef {	/* 140, 8 bytes each */
		UWORD	pos;
		UWORD	ctl;
		UWORD	dataa;
		UWORD	datab;
	} spr[8];
	UWORD	color[32];	/* 180 */
	UWORD	htotal;		/* 1C0 */
	UWORD	hsstop;
	UWORD	hbstrt;
	UWORD	hbstop;
	UWORD	vtotal;
	UWORD	vsstop;
	UWORD	vbstrt;
	UWORD	vbstop;
	UWORD	sprhstrt;	/* 1D0 */
	UWORD	sprhstop;
	UWORD	bplhstrt;
	UWORD	bplhstop;
	UWORD	hhposw;
	UWORD	hhposr;
	UWORD	beamcon0;	/* 1DC */
	UWORD	hsstrt;
	UWORD	vsstrt;		/* 1E0 */
	UWORD	hcenter;
	UWORD	diwhigh;
	UWORD	padf3[11];
	UWORD	fmode;		/* 1FC */
};

#ifdef ECS_SPECIFIC

/* beamcon0 */
#define VARVBLANK	0x1000
#define LOLDIS		0x0800
#define CSCBLANKEN	0x0400
#define VARVSYNC	0x0200
#define VARHSYNC	0x0100
#define VARBEAM		0x0080
#define DISPLAYDUAL	0x0040
#define DISPLAYPAL	0x0020
#define VARCSYNC	0x0010
#define CSBLANK		0x0008
#define CSYNCTRUE	0x0004
#define VSYNCTRUE	0x0002
#define HSYNCTRUE	0x0001

/* bplcon0 bit that enables bplcon3 */
#define USE_BPLCON3	1

/* bplcon2 */
#define BPLCON2_ZDCTEN		(1<<10)
#define BPLCON2_ZDBPEN		(1<<11)
#define BPLCON2_ZDBPSEL0	(1<<12)
#define BPLCON2_ZDBPSEL1	(1<<13)
#define BPLCON2_ZDBPSEL2	(1<<14)

/* bplcon3 */
#define BPLCON3_EXTBLNKEN	(1<<0)
#define BPLCON3_EXTBLKZD	(1<<1)
#define BPLCON3_ZDCLKEN		(1<<2)
#define BPLCON3_BRDNTRAN	(1<<4)
#define BPLCON3_BRDNBLNK	(1<<5)

#endif /* ECS_SPECIFIC */

#endif /* HARDWARE_CUSTOM_H */
