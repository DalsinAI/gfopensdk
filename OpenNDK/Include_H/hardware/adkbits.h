#ifndef HARDWARE_ADKBITS_H
#define HARDWARE_ADKBITS_H
/*
 * OpenNDK: bits of the adkcon and adkconr registers (audio and disk control).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#define ADKB_SETCLR	15
#define ADKB_PRECOMP1	14
#define ADKB_PRECOMP0	13
#define ADKB_MFMPREC	12
#define ADKB_UARTBRK	11
#define ADKB_WORDSYNC	10
#define ADKB_MSBSYNC	9
#define ADKB_FAST	8
#define ADKB_USE3PN	7
#define ADKB_USE2P3	6
#define ADKB_USE1P2	5
#define ADKB_USE0P1	4
#define ADKB_USE3VN	3
#define ADKB_USE2V3	2
#define ADKB_USE1V2	1
#define ADKB_USE0V1	0

#define ADKF_SETCLR	(1L<<15)
#define ADKF_PRECOMP1	(1L<<14)
#define ADKF_PRECOMP0	(1L<<13)
#define ADKF_MFMPREC	(1L<<12)
#define ADKF_UARTBRK	(1L<<11)
#define ADKF_WORDSYNC	(1L<<10)
#define ADKF_MSBSYNC	(1L<<9)
#define ADKF_FAST	(1L<<8)
#define ADKF_USE3PN	(1L<<7)
#define ADKF_USE2P3	(1L<<6)
#define ADKF_USE1P2	(1L<<5)
#define ADKF_USE0P1	(1L<<4)
#define ADKF_USE3VN	(1L<<3)
#define ADKF_USE2V3	(1L<<2)
#define ADKF_USE1V2	(1L<<1)
#define ADKF_USE0V1	(1L<<0)

/* Write precompensation choices */
#define ADKF_PRE000NS	0
#define ADKF_PRE140NS	(ADKF_PRECOMP0)
#define ADKF_PRE280NS	(ADKF_PRECOMP1)
#define ADKF_PRE560NS	(ADKF_PRECOMP0|ADKF_PRECOMP1)

#endif /* HARDWARE_ADKBITS_H */
