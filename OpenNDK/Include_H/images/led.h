#ifndef IMAGES_LED_H
#define IMAGES_LED_H
/*
 * OpenNDK: led.image, digits drawn as seven-segment displays.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef INTUITION_IMAGECLASS_H
#include <intuition/imageclass.h>
#endif

#define LED_Dummy		(TAG_USER + 0x4000000)

#define LED_Pairs		(LED_Dummy + 1)	/* how many two-digit groups */
#define LED_Values		(LED_Dummy + 2)	/* UWORD *: one value a group */
#define LED_Colon		(LED_Dummy + 3)	/* BOOL: colons between groups */
#define LED_Hexadecimal		(LED_Dummy + 7)	/* BOOL: show values in hex */
#define LED_Negative		(LED_Dummy + 4)	/* BOOL: a minus sign in front */
#define LED_EditMode		(LED_Dummy + 6)	/* BOOL */

/* More names from the 3.2 interface */
#define LED_Raw			(LED_Dummy + 8)
#define LED_Signed		(LED_Dummy + 5)
#define LED_Time		(LED_Dummy + 6)

#endif /* IMAGES_LED_H */
