/* Calendar.mcc: a month's days to pick one from. Names and numbers as
 * AROS's published interface. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_CALENDAR_H
#define ZUNE_CALENDAR_H

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

#define MUIC_Calendar "Calendar.mcc"
#define MUIB_Calendar (MUIB_AROS | 0x00000100UL)

#define MUIA_Calendar_Date      (MUIB_Calendar | 0x00000000UL)   /* ISG struct ClockData * */
#define MUIA_Calendar_MonthDay  (MUIB_Calendar | 0x00000001UL)   /* -SG UWORD, 1-31 */
#define MUIA_Calendar_MonthDay0 (MUIB_Calendar | 0x00000002UL)   /* -SG UWORD, 0-30 */
#define MUIA_Calendar_Month     (MUIB_Calendar | 0x00000003UL)   /* -SG UWORD, 1-12 */
#define MUIA_Calendar_Month0    (MUIB_Calendar | 0x00000004UL)   /* -SG UWORD, 0-11 */
#define MUIA_Calendar_Year      (MUIB_Calendar | 0x00000005UL)   /* -SG UWORD */
#define MUIA_Calendar_DayLabels (MUIB_Calendar | 0x00000006UL)   /* I-- STRPTR[], Sunday first */

#define CalendarObject MUIOBJMACRO_START(MUIC_Calendar)

#endif
