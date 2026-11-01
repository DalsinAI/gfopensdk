#ifndef GRAPHICS_RPATTR_H
#define GRAPHICS_RPATTR_H
/*
 * OpenNDK: tags for SetRPAttrsA() and GetRPAttrsA().
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#define RPTAG_Font		0x80000000	/* struct TextFont * */
#define RPTAG_APen		0x80000002
#define RPTAG_BPen		0x80000003
#define RPTAG_DrMd		0x80000004
#define RPTAG_OutlinePen	0x80000005
#define RPTAG_OutLinePen	RPTAG_OutlinePen	/* the same tag, the other spelling */
#define RPTAG_WriteMask		0x80000006
#define RPTAG_MaxPen		0x80000007
#define RPTAG_DrawBounds	0x80000008	/* get only: struct Rectangle * */

#endif /* GRAPHICS_RPATTR_H */
