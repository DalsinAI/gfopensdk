#ifndef GADGETS_FUELGAUGE_H
#define GADGETS_FUELGAUGE_H
/*
 * OpenNDK: fuelgauge.gadget, a bar showing how full or how far along.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define FUELGAUGE_Dummy		(REACTION_Dummy + 0x12000)

#define FUELGAUGE_Min		(FUELGAUGE_Dummy + 0x0001)
#define FUELGAUGE_Max		(FUELGAUGE_Dummy + 0x0002)
#define FUELGAUGE_Level		(FUELGAUGE_Dummy + 0x0003)
#define FUELGAUGE_Orientation	(FUELGAUGE_Dummy + 0x0004)	/* FGORIENT_ below */
#define FUELGAUGE_Percent	(FUELGAUGE_Dummy + 0x0005)	/* BOOL: show the percentage */
#define FUELGAUGE_Ticks		(FUELGAUGE_Dummy + 0x0006)	/* how many tick marks */
#define FUELGAUGE_ShortTicks	(FUELGAUGE_Dummy + 0x0007)	/* BOOL: half ticks between them */
#define FUELGAUGE_TickSize	(FUELGAUGE_Dummy + 0x0008)
#define FUELGAUGE_TickPen	(FUELGAUGE_Dummy + 0x0009)
#define FUELGAUGE_PercentPen	(FUELGAUGE_Dummy + 0x000A)
#define FUELGAUGE_FillPen	(FUELGAUGE_Dummy + 0x000B)
#define FUELGAUGE_EmptyPen	(FUELGAUGE_Dummy + 0x000C)
#define FUELGAUGE_VarArgs	(FUELGAUGE_Dummy + 0x000D)	/* arguments for a GA_Text format */
#define FUELGAUGE_Justification	(FUELGAUGE_Dummy + 0x000E)	/* FGJ_ below */

#define FGORIENT_HORIZ	0
#define FGORIENT_VERT	1

#define FGJ_LEFT	0
#define FGJ_CENTER	1
#define FGJ_CENTRE	FGJ_CENTER

/* More names from the 3.2 interface */
#define FUELGAUGE_HORIZONTAL	0
#define FUELGAUGE_VERTICAL	1

#endif /* GADGETS_FUELGAUGE_H */
