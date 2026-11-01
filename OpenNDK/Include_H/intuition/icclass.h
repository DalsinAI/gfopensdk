#ifndef INTUITION_ICCLASS_H
#define INTUITION_ICCLASS_H
/*
 * OpenNDK: icclass and modelclass, BOOPSI's interconnection classes.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* Methods */
#define ICM_Dummy	(0x0401)
#define ICM_SETLOOP	(0x0402)
#define ICM_CLEARLOOP	(0x0403)
#define ICM_CHECKLOOP	(0x0404)

/* Attributes */
#define ICA_Dummy	(TAG_USER + 0x40000)
#define ICA_TARGET	(ICA_Dummy + 1)	/* the object notified */
#define ICA_MAP		(ICA_Dummy + 2)	/* tag translations on the way */
#define ICSPECIAL_CODE	(ICA_Dummy + 3)	/* the Code of an IDCMPUPDATE */

/* ICA_TARGET: send IDCMP_IDCMPUPDATE to the window instead */
#define ICTARGET_IDCMP	(~0)

#endif /* INTUITION_ICCLASS_H */
