#ifndef DATATYPES_SOUNDCLASS_H
#define DATATYPES_SOUNDCLASS_H
/*
 * OpenNDK: sound.datatype's attributes and IFF 8SVX chunks.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef DATATYPES_DATATYPESCLASS_H
#include <datatypes/datatypesclass.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif
#ifndef DEVICES_TIMER_H
#include <devices/timer.h>
#endif

#define SOUNDDTCLASS	"sound.datatype"

/* Attributes */
#define SDTA_Dummy		(DTA_Dummy + 500)
#define SDTA_VoiceHeader	(SDTA_Dummy + 1)	/* struct VoiceHeader * */
#define SDTA_Sample		(SDTA_Dummy + 2)	/* BYTE * of 8-bit samples */
#define SDTA_SampleLength	(SDTA_Dummy + 3)
#define SDTA_Period		(SDTA_Dummy + 4)	/* the audio period */
#define SDTA_Volume		(SDTA_Dummy + 5)	/* 0 to 64 */
#define SDTA_Cycles		(SDTA_Dummy + 6)
#define SDTA_SignalTask		(SDTA_Dummy + 7)	/* signalled when done */
#define SDTA_SignalBit		(SDTA_Dummy + 8)	/* a signal mask */
#define SDTA_SignalBitMask	SDTA_SignalBit
#define SDTA_Continuous		(SDTA_Dummy + 9)
#define SDTA_SignalBitNumber	(SDTA_Dummy + 10)	/* a signal number */
#define SDTA_SamplesPerSec	(SDTA_Dummy + 11)
#define SDTA_ReplayPeriod	(SDTA_Dummy + 12)	/* struct timeval * */
#define SDTA_LeftSample		(SDTA_Dummy + 13)	/* stereo halves */
#define SDTA_RightSample	(SDTA_Dummy + 14)
#define SDTA_Pan		(SDTA_Dummy + 15)
#define SDTA_FreeSampleData	(SDTA_Dummy + 16)
#define SDTA_SyncSampleChange	(SDTA_Dummy + 17)

/* vh_Compression */
#define CMP_NONE	0
#define CMP_FIBDELTA	1

/* An 8SVX's VHDR chunk */
struct VoiceHeader {
	ULONG	vh_OneShotHiSamples;	/* samples played once */
	ULONG	vh_RepeatHiSamples;	/* samples of the repeating part */
	ULONG	vh_SamplesPerHiCycle;
	UWORD	vh_SamplesPerSec;
	UBYTE	vh_Octaves;
	UBYTE	vh_Compression;		/* CMP_ */
	ULONG	vh_Volume;		/* 16.16, 1.0 the loudest */
};

/* 8SVX chunks */
#define ID_8SVX	MAKE_ID('8','S','V','X')
#define ID_VHDR	MAKE_ID('V','H','D','R')
#define ID_CHAN	MAKE_ID('C','H','A','N')
#ifndef ID_BODY
#define ID_BODY	MAKE_ID('B','O','D','Y')
#endif

/* More names from the 3.2 interface */
#define SAMPLETYPE_Left		2
#define SAMPLETYPE_Right	4
#define SAMPLETYPE_Stereo	6
#define SDTA_BitsPerSample	(SDTA_Dummy + 18)
#define Unity			0x10000

#endif /* DATATYPES_SOUNDCLASS_H */
