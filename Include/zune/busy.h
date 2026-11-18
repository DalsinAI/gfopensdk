/* Busy.mcc: a bar that moves while something is busy. Names and numbers
 * as Busy.mcc's published interface. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_BUSY_H
#define ZUNE_BUSY_H

#include <libraries/mui.h>

#define MUIC_Busy "Busy.mcc"
#define MUIB_Busy 0x80020000UL

#define MUIA_Busy_ShowHideIH (MUIB_Busy | 0xa9)   /* ISG BOOL: move only while shown */
#define MUIA_Busy_Speed      (MUIB_Busy | 0x49)   /* ISG LONG: ms between moves */
#define MUIV_Busy_Speed_Off  0
#define MUIV_Busy_Speed_User (-1)                 /* moved by MUIM_Busy_Move only */

#define MUIM_Busy_Move (MUIB_Busy | 0x01)
struct MUIP_Busy_Move { IPTR MethodID; };

#define BusyObject MUIOBJMACRO_START(MUIC_Busy)
#define BusyBar BusyObject, MUIA_Busy_Speed, MUIV_Busy_Speed_User, End

#endif
