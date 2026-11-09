/* Automatically generated header (sfdc 1.12)! Do not edit! */

#ifndef CLIB_AKIKOPLUS_PROTOS_H
#define CLIB_AKIKOPLUS_PROTOS_H

/*
**   $VER: akikoplus_protos.h 2.0 $Id: akikoplus_lib.sfd 2.0 (9.11.2026) $
**
**   C prototypes. For use with 32 bit integers only.
**
**   Copyright (c) 2026 AmiCradle Team, MIT licence.
**       (made by sfdc from sfd/akikoplus_lib.sfd)
*/

#include <exec/types.h>
#include <libraries/akikoplus.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* akikoplus.library: AkikoPlus, the media board, and the 68k's versions of its helpers. MIT, (c) 2026 AmiCradle Team */
ULONG AP_Status(void);
LONG AP_SwapCopy(APTR dst, CONST_APTR src, ULONG count, ULONG unit);
LONG AP_SwapInPlace(APTR data, ULONG count, ULONG unit);
LONG AP_SwapInterleaved(APTR data, CONST_STRPTR layout, ULONG count, ULONG stride);
LONG AP_C2P(CONST struct APC2P * args);
LONG AP_Fill(CONST struct APFill * args);
LONG AP_CopyRect(CONST struct APCopy * args);
LONG AP_Scale(CONST struct APScale * args);
LONG AP_YUVToARGB(CONST struct APYUV * args);
LONG AP_Quantise(CONST struct APQuant * args);
LONG AP_Compress(CONST_APTR src, APTR dst, ULONG srcLength, ULONG dstLength, ULONG level);
LONG AP_Decompress(CONST_APTR src, APTR dst, ULONG srcLength, ULONG dstLength);
ULONG AP_SetThreshold(ULONG bytes);

/*--- functions in V2 or higher ---*/
ULONG AP_SetMode(ULONG mode);
LONG AP_Query(ULONG what);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CLIB_AKIKOPLUS_PROTOS_H */
