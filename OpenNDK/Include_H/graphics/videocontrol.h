#ifndef GRAPHICS_VIDEOCONTROL_H
#define GRAPHICS_VIDEOCONTROL_H
/*
 * OpenNDK: the tags VideoControl() reads and writes on a ColorMap.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#define VTAG_END_CM		0x00000000
#define VTAG_CHROMAKEY_CLR               0x80000000
#define VTAG_CHROMAKEY_SET               0x80000001
#define VTAG_BITPLANEKEY_CLR             0x80000002
#define VTAG_BITPLANEKEY_SET             0x80000003
#define VTAG_BORDERBLANK_CLR             0x80000004
#define VTAG_BORDERBLANK_SET             0x80000005
#define VTAG_BORDERNOTRANS_CLR           0x80000006
#define VTAG_BORDERNOTRANS_SET           0x80000007
#define VTAG_CHROMA_PEN_CLR              0x80000008
#define VTAG_CHROMA_PEN_SET              0x80000009
#define VTAG_CHROMA_PLANE_SET            0x8000000A
#define VTAG_ATTACH_CM_SET               0x8000000B
#define VTAG_NEXTBUF_CM                  0x8000000C
#define VTAG_BATCH_CM_CLR                0x8000000D
#define VTAG_BATCH_CM_SET                0x8000000E
#define VTAG_NORMAL_DISP_GET             0x8000000F
#define VTAG_NORMAL_DISP_SET             0x80000010
#define VTAG_COERCE_DISP_GET             0x80000011
#define VTAG_COERCE_DISP_SET             0x80000012
#define VTAG_VIEWPORTEXTRA_GET           0x80000013
#define VTAG_VIEWPORTEXTRA_SET           0x80000014
#define VTAG_CHROMAKEY_GET               0x80000015
#define VTAG_BITPLANEKEY_GET             0x80000016
#define VTAG_BORDERBLANK_GET             0x80000017
#define VTAG_BORDERNOTRANS_GET           0x80000018
#define VTAG_CHROMA_PLANE_GET            0x8000001A
#define VTAG_CHROMA_PEN_GET              0x80000019
#define VTAG_ATTACH_CM_GET               0x8000001B
#define VTAG_BATCH_CM_GET                0x8000001C
#define VTAG_BATCH_ITEMS_GET             0x8000001D
#define VTAG_BATCH_ITEMS_SET             0x8000001E
#define VTAG_BATCH_ITEMS_ADD             0x8000001F
#define VTAG_VPMODEID_GET                0x80000020
#define VTAG_VPMODEID_SET                0x80000021
#define VTAG_VPMODEID_CLR                0x80000022
#define VTAG_USERCLIP_GET                0x80000023
#define VTAG_USERCLIP_SET                0x80000024
#define VTAG_USERCLIP_CLR                0x80000025

/* V39 */
#define VTAG_PF1_BASE_GET                0x80000026
#define VTAG_PF2_BASE_GET                0x80000027
#define VTAG_SPEVEN_BASE_GET             0x80000028
#define VTAG_SPODD_BASE_GET              0x80000029
#define VTAG_PF1_BASE_SET                0x8000002A
#define VTAG_PF2_BASE_SET                0x8000002B
#define VTAG_SPEVEN_BASE_SET             0x8000002C
#define VTAG_SPODD_BASE_SET              0x8000002D
#define VTAG_BORDERSPRITE_GET            0x8000002E
#define VTAG_BORDERSPRITE_SET            0x8000002F
#define VTAG_BORDERSPRITE_CLR            0x80000030
#define VTAG_SPRITERESN_SET              0x80000031
#define VTAG_SPRITERESN_GET              0x80000032
#define VTAG_PF1_TO_SPRITEPRI_SET        0x80000033
#define VTAG_PF1_TO_SPRITEPRI_GET        0x80000034
#define VTAG_PF2_TO_SPRITEPRI_SET        0x80000035
#define VTAG_PF2_TO_SPRITEPRI_GET        0x80000036
#define VTAG_IMMEDIATE                   0x80000037
#define VTAG_FULLPALETTE_SET             0x80000038
#define VTAG_FULLPALETTE_GET             0x80000039
#define VTAG_FULLPALETTE_CLR             0x8000003A
#define VTAG_DEFSPRITERESN_SET           0x8000003B
#define VTAG_DEFSPRITERESN_GET           0x8000003C

/* Taking effect on the next MakeVPort() (V40) */
#define VC_IntermediateCLUpdate		0x80000080	/* update the copper list for each colour change */
#define VC_IntermediateCLUpdate_Query	0x80000081
#define VC_NoColorPaletteLoad		0x80000082	/* leave the palette out of the copper list */
#define VC_NoColorPaletteLoad_Query	0x80000083
#define VC_DUALPF_Disable		0x80000084	/* bitplanes as one playfield in dual playfield */
#define VC_DUALPF_Disable_Query		0x80000085

#endif /* GRAPHICS_VIDEOCONTROL_H */
