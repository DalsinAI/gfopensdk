/* IconImage.mcc: a Workbench icon's picture, from a DiskObject or from an
 * icon file. Published names and numbers (AROS's IconImage.mcc), our own text.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_ICONIMAGE_H
#define ZUNE_ICONIMAGE_H

#ifndef LIBRARIES_MUI_H
#include <libraries/mui.h>
#endif
#ifndef MUIB_RSVD
#define MUIB_RSVD (MUIB_MUI | 0x10400000UL)
#endif
#ifndef MUIB_AROS
#define MUIB_AROS (MUIB_RSVD | 0x00070000UL)
#endif

#define MUIC_IconImage "IconImage.mcc"
#define MUIB_IconImage (MUIB_AROS | 0x00000300UL)

#define MUIA_IconImage_DiskObject (MUIB_IconImage | 0x00000000UL)   /* I.. struct DiskObject * (the program's) */
#define MUIA_IconImage_File       (MUIB_IconImage | 0x00000001UL)   /* I.. CONST_STRPTR, without ".info" */

#define IconImageObject MUIOBJMACRO_START(MUIC_IconImage)

#endif
