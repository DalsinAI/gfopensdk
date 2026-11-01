#ifndef GADGETS_INTEGER_H
#define GADGETS_INTEGER_H
/*
 * OpenNDK: integer.gadget, a number field with optional arrows.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define INTEGER_Dummy		(REACTION_Dummy + 0x0002000)

#define INTEGER_Number		(INTEGER_Dummy + 0x0001)	/* LONG: the value */
#define INTEGER_MaxChars	(INTEGER_Dummy + 0x0002)
#define INTEGER_Minimum		(INTEGER_Dummy + 0x0003)
#define INTEGER_Maximum		(INTEGER_Dummy + 0x0004)
#define INTEGER_Arrows		(INTEGER_Dummy + 0x0005)	/* BOOL: up and down buttons */
#define INTEGER_MinVisible	(INTEGER_Dummy + 0x0006)	/* digits always shown */
#define INTEGER_SkipVal		(INTEGER_Dummy + 0x0007)	/* the arrows' step */

#endif /* GADGETS_INTEGER_H */
