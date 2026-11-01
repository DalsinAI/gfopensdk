#ifndef IMAGES_LABEL_H
#define IMAGES_LABEL_H
/*
 * OpenNDK: label.image, text and pictures placed beside gadgets.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_IMAGECLASS_H
#include <intuition/imageclass.h>
#endif

#define LABEL_Dummy		(REACTION_Dummy + 0x0006000)

#define LABEL_DrawInfo		SYSIA_DrawInfo
#define LABEL_Text		(LABEL_Dummy + 1)	/* STRPTR: a line; may be given again */
#define LABEL_Image		(LABEL_Dummy + 2)	/* struct Image * */
#define LABEL_Mapping		(LABEL_Dummy + 3)	/* UWORD *: pen map for LABEL_Image */
#define LABEL_Justification	(LABEL_Dummy + 4)	/* LJ_ below */
#define LABEL_Key		(LABEL_Dummy + 5)	/* (get) the underscored key */
#define LABEL_Underscore	(LABEL_Dummy + 6)	/* the marker character, '_' by default */
#define LABEL_DisposeImage	(LABEL_Dummy + 7)	/* dispose LABEL_Image with the label */
#define LABEL_SoftStyle		(LABEL_Dummy + 8)
#define LABEL_VerticalSpacing	(LABEL_Dummy + 9)	/* pixels between lines */

#define LJ_LEFT		0
#define LJ_CENTRE	1
#define LJ_CENTER	LJ_CENTRE
#define LJ_RIGHT	2

/* More names from the 3.2 interface */
#define LABEL_CENTER		1
#define LABEL_CENTRE		1
#define LABEL_LEFT		0
#define LABEL_MenuMode		(LABEL_Dummy + 12)
#define LABEL_RIGHT		2
#define LABEL_VerticalAlignment	(LABEL_Dummy + 10)
#define LABEL_WordWrap		(LABEL_Dummy + 11)
#define LVALIGN_BASELINE	1
#define LVALIGN_BOTTOM		0

#endif /* IMAGES_LABEL_H */
