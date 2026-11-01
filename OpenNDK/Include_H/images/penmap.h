#ifndef IMAGES_PENMAP_H
#define IMAGES_PENMAP_H
/*
 * OpenNDK: penmap.image, a chunky picture drawn with pens it obtains.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_IMAGECLASS_H
#include <intuition/imageclass.h>
#endif

#define PENMAP_Dummy		(REACTION_Dummy + 0x18000)

#define PENMAP_SelectBGPen	(PENMAP_Dummy + 1)	/* background pen when selected */
#define PENMAP_SelectData	(PENMAP_Dummy + 2)	/* the picture for the selected state */
#define PENMAP_Transparent	(PENMAP_Dummy + 6)	/* BOOL: colour 0 is not drawn */
#define PENMAP_Palette		(PENMAP_Dummy + 3)	/* ULONG *: the picture's colours */
#define PENMAP_Screen		(PENMAP_Dummy + 4)	/* struct Screen *: where pens come from */

/* More names from the 3.2 interface */
#define IMAGE_CHUNKY		0
#define IMAGE_DRAWLIST		2
#define IMAGE_IMAGE		1
#define PENMAP_ColorMap		(PENMAP_Dummy + 9)
#define PENMAP_Compressed	(PENMAP_Dummy + 11)
#define PENMAP_ImageType	(PENMAP_Dummy + 5)
#define PENMAP_MaskBlit		(PENMAP_Dummy + 10)
#define PENMAP_MaskPlane	(PENMAP_Dummy + 12)
#define PENMAP_Precision	(PENMAP_Dummy + 8)
#define PENMAP_RenderBGPen	0x80020006UL
#define PENMAP_RenderData	0x80020007UL
#define PENMAP_SelectMaskPlane	(PENMAP_Dummy + 13)

/* a pen map's size: its first two UWORDs */
#define IMAGE_WIDTH(i)		(((UWORD *)(i))[0])
#define IMAGE_HEIGHT(i)		(((UWORD *)(i))[1])

#endif /* IMAGES_PENMAP_H */
