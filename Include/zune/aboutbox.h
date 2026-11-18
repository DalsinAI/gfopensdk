/* Aboutbox.mcc: a program's About window from its application's details,
 * with credits and a build string. Names and numbers as Aboutbox.mcc's
 * published interface. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_ABOUTBOX_H
#define ZUNE_ABOUTBOX_H

#include <libraries/mui.h>

#define MUIC_Aboutbox "Aboutbox.mcc"

#define MUIA_Aboutbox_Credits          0xFED10001UL   /* I.. STRPTR (MUI text escapes) */
#define MUIA_Aboutbox_LogoData         0xFED10002UL   /* I.. APTR */
#define MUIA_Aboutbox_LogoFallbackMode 0xFED10003UL   /* I.. ULONG */
#define MUIA_Aboutbox_LogoFile         0xFED10004UL   /* I.. STRPTR */
#define MUIA_Aboutbox_Build            0xFED1001EUL   /* I.. STRPTR */

#define MUIV_Aboutbox_LogoFallbackMode_NoLogo 0
#define MUIV_Aboutbox_LogoFallbackMode_Auto   (((ULONG)'D' << 24) | ((ULONG)'E' << 16) | ((ULONG)'I' << 8))

#define AboutboxObject MUIOBJMACRO_START(MUIC_Aboutbox)

#endif
