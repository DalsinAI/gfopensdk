#ifndef GADGETS_PIECHART_H
#define GADGETS_PIECHART_H
/*
 * OpenNDK: piechart.gadget, a pie chart of a list of values.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 *
 * The vendor NDK 3.2 ships no gadgets/piechart.h. These are the tags
 * OpenReAction's piechart.gadget (amicradle-guest,
 * libraries/openreaction/piechart) answers to; its jump table is in
 * SFD/piechart_lib.sfd.
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define PIECHART_Dummy		(REACTION_Dummy + 0x48000)

#define PIECHART_Values		(PIECHART_Dummy + 1)	/* ULONG *: one value a slice */
#define PIECHART_NumValues	(PIECHART_Dummy + 2)	/* ULONG: how many values */
#define PIECHART_Pens		(PIECHART_Dummy + 3)	/* UWORD *: a pen a slice, NULL: DrawInfo pens */
#define PIECHART_Selected	(PIECHART_Dummy + 4)	/* LONG: the slice picked, -1 none */

#endif /* GADGETS_PIECHART_H */
