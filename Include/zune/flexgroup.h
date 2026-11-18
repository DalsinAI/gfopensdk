/* Flexgroup.mcc: a Group laid out as a CSS flexbox: its direction, how
 * its children share spare room along it (Justify), how they sit across
 * it (Align) and the gap between them. A child's weight along the main
 * axis is how it grows; weight 0 keeps it at its natural size. Names and
 * numbers as AROS's published interface. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_FLEXGROUP_H
#define ZUNE_FLEXGROUP_H

#include <libraries/mui.h>

#ifndef MUIB_RSVD
#define MUIB_RSVD (MUIB_MUI | 0x10400000UL)
#endif
#ifndef MUIB_AROS
#define MUIB_AROS (MUIB_RSVD | 0x00070000UL)
#endif

#define MUIC_Flexgroup "Flexgroup.mcc"
#define MUIB_Flexgroup (MUIB_AROS | 0x00000700UL)

#define MUIA_Flexgroup_Direction (MUIB_Flexgroup | 0x00000000UL)   /* ISG LONG */
#define MUIA_Flexgroup_Justify   (MUIB_Flexgroup | 0x00000001UL)   /* ISG LONG */
#define MUIA_Flexgroup_Align     (MUIB_Flexgroup | 0x00000002UL)   /* ISG LONG */
#define MUIA_Flexgroup_Gap       (MUIB_Flexgroup | 0x00000003UL)   /* ISG LONG, pixels */

enum { MUIV_Flexgroup_Direction_Row = 0, MUIV_Flexgroup_Direction_Column };
enum {
    MUIV_Flexgroup_Justify_Start = 0, MUIV_Flexgroup_Justify_End, MUIV_Flexgroup_Justify_Center,
    MUIV_Flexgroup_Justify_SpaceBetween, MUIV_Flexgroup_Justify_SpaceAround, MUIV_Flexgroup_Justify_SpaceEvenly
};
enum { MUIV_Flexgroup_Align_Stretch = 0, MUIV_Flexgroup_Align_Start, MUIV_Flexgroup_Align_End, MUIV_Flexgroup_Align_Center };

#define FlexgroupObject MUIOBJMACRO_START(MUIC_Flexgroup)

#endif
