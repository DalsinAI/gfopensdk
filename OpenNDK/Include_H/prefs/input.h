#ifndef PREFS_INPUT_H
#define PREFS_INPUT_H
/*
 * OpenNDK: input preferences: keymap, mouse and key timing (the INPT chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef DEVICES_TIMER_H
#include <devices/timer.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_INPT		MAKE_ID('I','N','P','T')

struct InputPrefs
{
    char ip_Keymap[16];
    UWORD ip_PointerTicks;
    TimeVal_Type ip_DoubleClick;
    TimeVal_Type ip_KeyRptDelay;
    TimeVal_Type ip_KeyRptSpeed;
    WORD ip_MouseAccel;
};

#endif /* PREFS_INPUT_H */
