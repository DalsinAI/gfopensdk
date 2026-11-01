#ifndef GADGETS_TAPEDECK_H
#define GADGETS_TAPEDECK_H
/*
 * OpenNDK: tapedeck.gadget, play and wind buttons for media (made by name).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

#define TDECK_Dummy		(TAG_USER + 0x05000000)

#define TDECK_Mode		(TDECK_Dummy + 1)	/* the button down, BUT_ below */
#define TDECK_Paused		(TDECK_Dummy + 2)	/* BOOL */
#define TDECK_Tape		(TDECK_Dummy + 3)	/* BOOL: tape buttons, not animation ones */
#define TDECK_Frames		(TDECK_Dummy + 11)	/* animation: frames in all */
#define TDECK_CurrentFrame	(TDECK_Dummy + 12)

/* TDECK_Mode */
#define BUT_REWIND	0
#define BUT_PLAY	1
#define BUT_FORWARD	2
#define BUT_STOP	3
#define BUT_PAUSE	4
#define BUT_BEGIN	5
#define BUT_FRAME	6
#define BUT_END		7

#endif /* GADGETS_TAPEDECK_H */
