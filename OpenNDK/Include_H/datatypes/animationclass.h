#ifndef DATATYPES_ANIMATIONCLASS_H
#define DATATYPES_ANIMATIONCLASS_H
/*
 * OpenNDK: animation.datatype's attributes, methods and IFF ANIM chunks.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef DATATYPES_DATATYPESCLASS_H
#include <datatypes/datatypesclass.h>
#endif
#ifndef DATATYPES_PICTURECLASS_H
#include <datatypes/pictureclass.h>
#endif
#ifndef DATATYPES_SOUNDCLASS_H
#include <datatypes/soundclass.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ANIMATIONDTCLASS	"animation.datatype"

/* Attributes it shares with the picture and sound classes */
#define ADTA_Dummy		(DTA_Dummy + 600)
#define ADTA_ModeID		PDTA_ModeID
#define ADTA_KeyFrame		PDTA_BitMap	/* the first frame's bitmap */
#define ADTA_ColorRegisters	PDTA_ColorRegisters
#define ADTA_CRegs		PDTA_CRegs
#define ADTA_GRegs		PDTA_GRegs
#define ADTA_ColorTable		PDTA_ColorTable
#define ADTA_ColorTable2	PDTA_ColorTable2
#define ADTA_Allocated		PDTA_Allocated
#define ADTA_NumColors		PDTA_NumColors
#define ADTA_NumAlloc		PDTA_NumAlloc
#define ADTA_Remap		PDTA_Remap
#define ADTA_Screen		PDTA_Screen
#define ADTA_NumSparse		PDTA_NumSparse
#define ADTA_SparseTable	PDTA_SparseTable

/* Its own */
#define ADTA_Width		(ADTA_Dummy + 1)
#define ADTA_Height		(ADTA_Dummy + 2)
#define ADTA_Depth		(ADTA_Dummy + 3)
#define ADTA_Frames		(ADTA_Dummy + 4)	/* how many */
#define ADTA_Frame		(ADTA_Dummy + 5)	/* the current one */
#define ADTA_FramesPerSecond	(ADTA_Dummy + 6)
#define ADTA_FrameIncrement	(ADTA_Dummy + 7)
#define ADTA_PreloadFrameCount	(ADTA_Dummy + 8)

/* The sound */
#define ADTA_Sample		SDTA_Sample
#define ADTA_SampleLength	SDTA_SampleLength
#define ADTA_Period		SDTA_Period
#define ADTA_Volume		SDTA_Volume
#define ADTA_Cycles		SDTA_Cycles
#define ADTA_LeftSample		SDTA_LeftSample
#define ADTA_RightSample	SDTA_RightSample
#define ADTA_SamplesPerSec	SDTA_SamplesPerSec

/* ANIM chunks */
#define ID_ANIM	MAKE_ID('A','N','I','M')
#define ID_ANHD	MAKE_ID('A','N','H','D')
#define ID_DLTA	MAKE_ID('D','L','T','A')

/* An ANIM's ANHD chunk */
struct AnimHeader {
	UBYTE	ah_Operation;	/* the compression used */
	UBYTE	ah_Mask;
	UWORD	ah_Width;
	UWORD	ah_Height;
	WORD	ah_Left;
	WORD	ah_Top;
	ULONG	ah_AbsTime;	/* in jiffies, from the start */
	ULONG	ah_RelTime;	/* in jiffies, from the frame before */
	UBYTE	ah_Interleave;
	UBYTE	ah_Pad0;
	ULONG	ah_Flags;
	UBYTE	ah_Pad[16];
};

/* Methods */
#define ADTM_Dummy			(0x700)
#define ADTM_LOADFRAME			(0x701)	/* struct adtFrame */
#define ADTM_UNLOADFRAME		(0x702)	/* struct adtFrame */
#define ADTM_START			(0x703)	/* struct adtStart */
#define ADTM_PAUSE			(0x704)
#define ADTM_STOP			(0x705)
#define ADTM_LOCATE			(0x706)	/* struct adtStart */
#define ADTM_LOADNEWFORMATFRAME		(0x707)	/* struct adtNewFormatFrame */
#define ADTM_UNLOADNEWFORMATFRAME	(0x708)	/* struct adtNewFormatFrame */

/* ADTM_LOADFRAME and ADTM_UNLOADFRAME */
struct adtFrame {
	ULONG		MethodID;
	ULONG		alf_TimeStamp;	/* the time the frame is for */
	ULONG		alf_Frame;	/* filled in by the class */
	ULONG		alf_Duration;
	struct BitMap	*alf_BitMap;
	struct ColorMap	*alf_CMap;
	BYTE		*alf_Sample;
	ULONG		alf_SampleLength;
	ULONG		alf_Period;
	APTR		alf_UserData;	/* the class's own */
};

/* ADTM_LOADNEWFORMATFRAME and ADTM_UNLOADNEWFORMATFRAME */
struct adtNewFormatFrame {
	ULONG		MethodID;
	ULONG		alf_TimeStamp;
	ULONG		alf_Frame;
	ULONG		alf_Duration;
	struct BitMap	*alf_BitMap;
	struct ColorMap	*alf_CMap;
	BYTE		*alf_Sample;
	ULONG		alf_SampleLength;
	ULONG		alf_Period;
	APTR		alf_UserData;
	ULONG		alf_Size;	/* of this message */
	BYTE		*alf_LeftSample;
	BYTE		*alf_RightSample;
	ULONG		alf_SamplesPerSec;
};

/* ADTM_START and ADTM_LOCATE */
struct adtStart {
	ULONG	MethodID;
	ULONG	asa_Frame;
};

#endif /* DATATYPES_ANIMATIONCLASS_H */
