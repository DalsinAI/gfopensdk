/* Lamp.mcc: a small coloured light (on, off, ok, error ...). Names and
 * numbers as Lamp.mcc's published interface.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_LAMP_H
#define ZUNE_LAMP_H

#include <libraries/mui.h>

#define MUIC_Lamp "Lamp.mcc"

#define MUIM_Lamp_SetRGB 0x85b90008UL
struct MUIP_Lamp_SetRGB { IPTR MethodID; IPTR red; IPTR green; IPTR blue; };

#define MUIA_Lamp_Type      0x85b90001UL   /* ISG ULONG */
#define MUIA_Lamp_Color     0x85b90002UL   /* ISG ULONG *: a MUIV_Lamp_Color_ or three 32 bit parts */
#define MUIA_Lamp_ColorType 0x85b90003UL   /* --G ULONG */
#define MUIA_Lamp_Red       0x85b90004UL   /* ISG ULONG */
#define MUIA_Lamp_Green     0x85b90005UL   /* ISG ULONG */
#define MUIA_Lamp_Blue      0x85b90006UL   /* ISG ULONG */
#define MUIA_Lamp_PenSpec   0x85b90007UL   /* ISG struct MUI_PenSpec * */

#define MUIV_Lamp_Type_Tiny   0
#define MUIV_Lamp_Type_Small  1
#define MUIV_Lamp_Type_Medium 2
#define MUIV_Lamp_Type_Big    3
#define MUIV_Lamp_Type_Huge   4

#define MUIV_Lamp_ColorType_UserDefined 0
#define MUIV_Lamp_ColorType_Color       1
#define MUIV_Lamp_ColorType_PenSpec     2

#define MUIV_Lamp_Color_Off           0
#define MUIV_Lamp_Color_Ok            1
#define MUIV_Lamp_Color_Warning       2
#define MUIV_Lamp_Color_Error         3
#define MUIV_Lamp_Color_FatalError    4
#define MUIV_Lamp_Color_Processing    5
#define MUIV_Lamp_Color_LookingUp     6
#define MUIV_Lamp_Color_Connecting    7
#define MUIV_Lamp_Color_SendingData   8
#define MUIV_Lamp_Color_ReceivingData 9
#define MUIV_Lamp_Color_LoadingData   10
#define MUIV_Lamp_Color_SavingData    11

#define LampObject MUIOBJMACRO_START(MUIC_Lamp)

#endif
