/* Clock.mcc: a clock showing the time, or one being set. Names and
 * numbers as AROS's published interface. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_CLOCK_H
#define ZUNE_CLOCK_H

#include <libraries/mui.h>
#ifndef GFOPENMUI_HOST
#include <utility/date.h>
#endif

#ifndef MUIB_RSVD
#define MUIB_RSVD (MUIB_MUI | 0x10400000UL)
#endif
#ifndef MUIB_AROS
#define MUIB_AROS (MUIB_RSVD | 0x00070000UL)
#endif

#define MUIC_Clock "Clock.mcc"
#define MUIB_Clock (MUIB_AROS | 0x00000000UL)

#define MUIA_Clock_Hour     (MUIB_Clock | 0x00000000UL)   /* -SG UWORD */
#define MUIA_Clock_Min      (MUIB_Clock | 0x00000001UL)   /* -SG UWORD */
#define MUIA_Clock_Sec      (MUIB_Clock | 0x00000002UL)   /* -SG UWORD */
#define MUIA_Clock_Time     (MUIB_Clock | 0x00000003UL)   /* ISG struct ClockData * */
#define MUIA_Clock_Ticked   (MUIB_Clock | 0x00000004UL)   /* --- BOOL: notifies each second */
#define MUIA_Clock_Frozen   (MUIB_Clock | 0x00000005UL)   /* ISG BOOL: stops following the time */
#define MUIA_Clock_EditHand (MUIB_Clock | 0x00000006UL)   /* ISG WORD */
#define MUIV_Clock_EditHand_Hour   0
#define MUIV_Clock_EditHand_Minute 1
#define MUIV_Clock_EditHand_Second 2

#define MUIM_Clock_Timer (MUIB_Clock | 0x00000000UL)

#define ClockObject MUIOBJMACRO_START(MUIC_Clock)

#endif
