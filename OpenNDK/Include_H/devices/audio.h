#ifndef DEVICES_AUDIO_H
#define DEVICES_AUDIO_H
/*
 * OpenNDK: audio.device's commands, flags and request.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_IO_H
#include <exec/io.h>
#endif

#define AUDIONAME		"audio.device"

#define ADHARD_CHANNELS		4

#define ADALLOC_MINPREC		-128
#define ADALLOC_MAXPREC		127

/* Commands */
#define ADCMD_FREE		(CMD_NONSTD+0)
#define ADCMD_SETPREC		(CMD_NONSTD+1)
#define ADCMD_FINISH		(CMD_NONSTD+2)
#define ADCMD_PERVOL		(CMD_NONSTD+3)
#define ADCMD_LOCK		(CMD_NONSTD+4)
#define ADCMD_WAITCYCLE		(CMD_NONSTD+5)
#define ADCMD_ALLOCATE		32

/* io_Flags */
#define ADIOB_PERVOL		4	/* set period and volume too */
#define ADIOF_PERVOL		(1<<4)
#define ADIOB_SYNCCYCLE		5	/* wait for the cycle to end */
#define ADIOF_SYNCCYCLE		(1<<5)
#define ADIOB_NOWAIT		6	/* fail rather than wait for channels */
#define ADIOF_NOWAIT		(1<<6)
#define ADIOB_WRITEMESSAGE	7	/* reply ioa_WriteMsg when play starts */
#define ADIOF_WRITEMESSAGE	(1<<7)

/* io_Error */
#define ADIOERR_NOALLOCATION	-10
#define ADIOERR_ALLOCFAILED	-11
#define ADIOERR_CHANNELSTOLEN	-12

struct IOAudio {
	struct IORequest ioa_Request;	/* io_Unit: the channel mask */
	WORD		ioa_AllocKey;
	UBYTE		*ioa_Data;	/* sample, or channel masks to try */
	ULONG		ioa_Length;
	UWORD		ioa_Period;
	UWORD		ioa_Volume;
	UWORD		ioa_Cycles;
	struct Message	ioa_WriteMsg;
};

#endif /* DEVICES_AUDIO_H */
