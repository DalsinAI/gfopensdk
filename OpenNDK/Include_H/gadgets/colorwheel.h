#ifndef GADGETS_COLORWHEEL_H
#define GADGETS_COLORWHEEL_H
/*
 * OpenNDK: colorwheel.gadget, a hue and saturation wheel (made by name).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* A colour as hue, saturation and brightness, each 32 bits */
struct ColorWheelHSB
{
	ULONG	cw_Hue;
	ULONG	cw_Saturation;
	ULONG	cw_Brightness;
};

/* A colour as red, green and blue, each 32 bits */
struct ColorWheelRGB
{
	ULONG	cw_Red;
	ULONG	cw_Green;
	ULONG	cw_Blue;
};

#define WHEEL_Dummy		(TAG_USER + 0x04000000)

#define WHEEL_Hue		(WHEEL_Dummy + 1)
#define WHEEL_Saturation	(WHEEL_Dummy + 2)
#define WHEEL_Brightness	(WHEEL_Dummy + 3)
#define WHEEL_HSB		(WHEEL_Dummy + 4)	/* struct ColorWheelHSB * */
#define WHEEL_Red		(WHEEL_Dummy + 5)
#define WHEEL_Green		(WHEEL_Dummy + 6)
#define WHEEL_Blue		(WHEEL_Dummy + 7)
#define WHEEL_RGB		(WHEEL_Dummy + 8)	/* struct ColorWheelRGB * */
#define WHEEL_Screen		(WHEEL_Dummy + 9)	/* struct Screen *: where it is shown */
#define WHEEL_Abbrv		(WHEEL_Dummy + 10)	/* STRPTR: the colour letters drawn round it */
#define WHEEL_Donation		(WHEEL_Dummy + 11)	/* UWORD *: pens given to it */
#define WHEEL_BevelBox		(WHEEL_Dummy + 12)	/* BOOL: a frame round it */
#define WHEEL_GradientSlider	(WHEEL_Dummy + 13)	/* Object *: a slider it keeps in step */
#define WHEEL_MaxPens		(WHEEL_Dummy + 14)	/* how many pens it may take */

/* More names from the 3.2 interface */
#define WHEEL_KeepAspect	(WHEEL_Dummy + 15)

#endif /* GADGETS_COLORWHEEL_H */
