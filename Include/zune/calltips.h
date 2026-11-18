/* Calltips.mcc: a small borderless window that follows a place in another
 * object (an editor's cursor, say), shown under it.
 * Published names and numbers (Calltips.mcc), our own text.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_CALLTIPS_H
#define ZUNE_CALLTIPS_H

#ifndef LIBRARIES_MUI_H
#include <libraries/mui.h>
#endif
#ifndef STACKED
#define STACKED
#endif

#define MUIC_Calltips "Calltips.mcc"
#define TAGBASE_Calltips 0xfecf4100UL

#define MUIA_Calltips_Rectangle  (TAGBASE_Calltips + 0)   /* ISG struct Rectangle *, in the Source's box (copied) */
#define MUIA_Calltips_Layout     (TAGBASE_Calltips + 1)   /* ISG ULONG, MUIV_Calltips_Layout_* */
#define MUIA_Calltips_Source     (TAGBASE_Calltips + 2)   /* ISG Object *: the object it follows */
#define MUIA_Calltips_MarginLeft (TAGBASE_Calltips + 4)   /* ISG LONG, pixels right of the rectangle */
#define MUIA_Calltips_MarginTop  (TAGBASE_Calltips + 5)   /* ISG LONG, pixels under it */

#define MUIV_Calltips_Layout_Exact 0

#define MUIM_Calltips_SetRectangle         (TAGBASE_Calltips + 0)
#define MUIM_Calltips_ParentSetup          (TAGBASE_Calltips + 1)
#define MUIM_Calltips_ParentCleanup        (TAGBASE_Calltips + 2)
#define MUIM_Calltips_ParentShow           (TAGBASE_Calltips + 3)
#define MUIM_Calltips_ParentHide           (TAGBASE_Calltips + 4)
#define MUIM_Calltips_ParentWindowArranged (TAGBASE_Calltips + 5)

struct MUIP_Calltips_SetRectangle {
    STACKED IPTR id;
    STACKED IPTR MinX, MinY, MaxX, MaxY;    /* LONGs, IPTR-wide */
};

#define CalltipsObject MUIOBJMACRO_START(MUIC_Calltips)

#endif
