#ifndef PREFS_SOUND_H
#define PREFS_SOUND_H
/*
 * OpenNDK: sound preferences: DisplayBeep()'s flash and sound (the SOND chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_SOND		MAKE_ID('S','O','N','D')

struct SoundPrefs
{
    LONG sop_Reserved[4];
    BOOL sop_DisplayQueue;		/* flash the screen */
    BOOL sop_AudioQueue;		/* make a sound */
    UWORD sop_AudioType;		/* SPTYPE_ */
    UWORD sop_AudioVolume;
    UWORD sop_AudioPeriod;
    UWORD sop_AudioDuration;
    TEXT	sop_AudioFileName[256];	/* with SPTYPE_SAMPLE */
};

/* sop_AudioType */
#define SPTYPE_BEEP	0
#define SPTYPE_SAMPLE	1

#endif /* PREFS_SOUND_H */
