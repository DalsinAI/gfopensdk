/* QRCode.mcc: a QR code (ISO/IEC 18004) of a text or of bytes, drawn as
 * dark and light squares with the four-module quiet zone around them.
 * Published names and numbers (AROS's QRCode.mcc), our own text.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_QRCODE_H
#define ZUNE_QRCODE_H

#ifndef LIBRARIES_MUI_H
#include <libraries/mui.h>
#endif
#ifndef MUIB_RSVD
#define MUIB_RSVD (MUIB_MUI | 0x10400000UL)
#endif
#ifndef MUIB_AROS
#define MUIB_AROS (MUIB_RSVD | 0x00070000UL)
#endif

#define MUIC_QRCode "QRCode.mcc"
#define MUIB_QRCode (MUIB_AROS | 0x00000B00UL)

#define MUIA_QRCode_Text              (MUIB_QRCode | 0x01)   /* ISG CONST_STRPTR, UTF-8; copied */
#define MUIA_QRCode_Data              (MUIB_QRCode | 0x02)   /* ISG struct MUI_QRCodePayload *; copied */
#define MUIA_QRCode_ECC               (MUIB_QRCode | 0x03)   /* ISG ULONG, MUIV_QRCode_ECC_* */
#define MUIA_QRCode_Status            (MUIB_QRCode | 0x04)   /* ..G ULONG, MUIV_QRCode_Status_* */
#define MUIA_QRCode_ForegroundPenSpec (MUIB_QRCode | 0x05)   /* ISG struct MUI_PenSpec * (dark modules) */
#define MUIA_QRCode_BackgroundPenSpec (MUIB_QRCode | 0x06)   /* ISG struct MUI_PenSpec * (light modules) */
#define MUIA_QRCode_Transparent       (MUIB_QRCode | 0x07)   /* ISG BOOL: light modules not drawn */

#define MUIV_QRCode_ECC_L 0
#define MUIV_QRCode_ECC_M 1
#define MUIV_QRCode_ECC_Q 2
#define MUIV_QRCode_ECC_H 3

#define MUIV_QRCode_Status_Empty      0
#define MUIV_QRCode_Status_Ready      1
#define MUIV_QRCode_Status_Invalid    2
#define MUIV_QRCode_Status_NoMemory   3
#define MUIV_QRCode_Status_NoCapacity 4

struct MUI_QRCodePayload {
    const UBYTE *Bytes;
    ULONG Length;
};

#define QRCodeObject MUIOBJMACRO_START(MUIC_QRCode)

#endif
