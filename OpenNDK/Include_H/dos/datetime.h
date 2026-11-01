#ifndef DOS_DATETIME_H
#define DOS_DATETIME_H
/*
 * OpenNDK: the structure DateToStr() and StrToDate() convert through.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

struct DateTime {
	struct DateStamp dat_Stamp;	/* the date being converted */
	UBYTE	dat_Format;		/* FORMAT_ */
	UBYTE	dat_Flags;		/* DTF_ */
	STRPTR	dat_StrDay;		/* day name, or NULL */
	STRPTR	dat_StrDate;		/* date text, or NULL */
	STRPTR	dat_StrTime;		/* time text, or NULL */
};

/* The buffer size each string needs */
#define LEN_DATSTRING	16

/* dat_Flags */
#define DTB_SUBST	0	/* may say Today, Monday and the like */
#define DTF_SUBST	(1<<DTB_SUBST)
#define DTB_FUTURE	1	/* day names refer to the coming week */
#define DTF_FUTURE	(1<<DTB_FUTURE)

/* dat_Format */
#define FORMAT_DOS	0	/* dd-mmm-yy */
#define FORMAT_INT	1	/* yy-mm-dd */
#define FORMAT_USA	2	/* mm-dd-yy */
#define FORMAT_CDN	3	/* dd-mm-yy */
#define FORMAT_MAX	FORMAT_CDN
#define FORMAT_DEF	4	/* the locale's own */

#endif /* DOS_DATETIME_H */
