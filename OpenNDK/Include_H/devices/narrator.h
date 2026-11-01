#ifndef DEVICES_NARRATOR_H
#define DEVICES_NARRATOR_H
/*
 * OpenNDK: narrator.device's request, voice settings and errors.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_IO_H
#include <exec/io.h>
#endif

/* flags */
#define NDB_NEWIORB	0	/* the request is the V37 form */
#define NDB_WORDSYNC	1	/* reply a read at each word */
#define NDB_SYLSYNC	2	/* reply a read at each syllable */

#define NDF_NEWIORB	(1<<NDB_NEWIORB)
#define NDF_WORDSYNC	(1<<NDB_WORDSYNC)
#define NDF_SYLSYNC	(1<<NDB_SYLSYNC)

/* io_Error */
#define ND_NoMem	-2
#define ND_NoAudLib	-3
#define ND_MakeBad	-4
#define ND_UnitErr	-5
#define ND_CantAlloc	-6
#define ND_Unimpl	-7
#define ND_NoWrite	-8
#define ND_Expunged	-9
#define ND_PhonErr	-20
#define ND_RateErr	-21
#define ND_PitchErr	-22
#define ND_SexErr	-23
#define ND_ModeErr	-24
#define ND_FreqErr	-25
#define ND_VolErr	-26
#define ND_DCentErr	-27
#define ND_CentPhonErr	-28

/* Defaults */
#define DEFPITCH	110
#define DEFRATE		150
#define DEFVOL		64
#define DEFFREQ		22200
#define MALE		0
#define FEMALE		1
#define NATURALF0	0
#define ROBOTICF0	1
#define MANUALF0	2
#define DEFSEX		MALE
#define DEFMODE		NATURALF0
#define DEFARTIC	100
#define DEFCENTRAL	0
#define DEFF0PERT	0
#define DEFF0ENTHUS	32
#define DEFPRIORITY	100

/* Limits */
#define MINRATE		40
#define MAXRATE		400
#define MINPITCH	65
#define MAXPITCH	320
#define MINFREQ		5000
#define MAXFREQ		28000
#define MINVOL		0
#define MAXVOL		64
#define MINCENT		0
#define MAXCENT		100

/* The write request */
struct narrator_rb {
	struct IOStdReq	message;
	UWORD	rate;		/* words per minute */
	UWORD	pitch;		/* Hz */
	UWORD	mode;		/* NATURALF0 and friends */
	UWORD	sex;
	UBYTE	*ch_masks;	/* audio channel masks to try */
	UWORD	nm_masks;
	UWORD	volume;
	UWORD	sampfreq;
	UBYTE	mouths;		/* non-zero: make mouth shapes */
	UBYTE	chanmask;	/* private */
	UBYTE	numchan;	/* private */
	UBYTE	flags;		/* NDF_ */
	UBYTE	F0enthusiasm;
	UBYTE	F0perturb;
	BYTE	F1adj;
	BYTE	F2adj;
	BYTE	F3adj;
	BYTE	A1adj;
	BYTE	A2adj;
	BYTE	A3adj;
	UBYTE	articulate;
	UBYTE	centralize;
	char	*centphon;
	BYTE	AVbias;
	BYTE	AFbias;
	BYTE	priority;
	BYTE	pad1;
};

/* The read request: mouth shapes and sync marks */
struct mouth_rb {
	struct narrator_rb voice;
	UBYTE	width;
	UBYTE	height;
	UBYTE	shape;		/* private */
	UBYTE	sync;		/* what the read was replied for */
};

#endif /* DEVICES_NARRATOR_H */
