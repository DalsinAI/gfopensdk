#ifndef GADGETS_GRADIENTSLIDER_H
#define GADGETS_GRADIENTSLIDER_H
/*
 * OpenNDK: gradientslider.gadget, a slider over a run of colours (made by name).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

#define GRAD_Dummy		(TAG_USER + 0x05000000)

#define GRAD_MaxVal		(GRAD_Dummy + 1)	/* the highest value */
#define GRAD_CurVal		(GRAD_Dummy + 2)	/* the value */
#define GRAD_SkipVal		(GRAD_Dummy + 3)	/* the step of a click beside the knob */
#define GRAD_KnobPixels		(GRAD_Dummy + 4)	/* the knob's size */
#define GRAD_PenArray		(GRAD_Dummy + 5)	/* UWORD *: pens, ended by ~0 */

#endif /* GADGETS_GRADIENTSLIDER_H */
