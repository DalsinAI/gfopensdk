#ifndef UTILITY_DATE_H
#define UTILITY_DATE_H
/*
 * OpenNDK: a calendar date and time split into fields.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

/* Used by Amiga2Date(), Date2Amiga() and CheckDate(). */
struct ClockData {
	UWORD	sec;	/* 0-59 */
	UWORD	min;	/* 0-59 */
	UWORD	hour;	/* 0-23 */
	UWORD	mday;	/* 1-31 */
	UWORD	month;	/* 1-12 */
	UWORD	year;	/* 1978 and later */
	UWORD	wday;	/* 0 is Sunday */
};

#endif /* UTILITY_DATE_H */
