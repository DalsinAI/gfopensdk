#ifndef LIBRARIES_LOCALE_H
#define LIBRARIES_LOCALE_H
/*
 * OpenNDK: locale.library's locales, catalogs, string numbers and tags.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* GetLocaleStr()'s string numbers: the days, Sunday first */
#define DAY_1		1
#define DAY_2		2
#define DAY_3		3
#define DAY_4		4
#define DAY_5		5
#define DAY_6		6
#define DAY_7		7

/* The days, abbreviated */
#define ABDAY_1		8
#define ABDAY_2		9
#define ABDAY_3		10
#define ABDAY_4		11
#define ABDAY_5		12
#define ABDAY_6		13
#define ABDAY_7		14

/* The months, January first */
#define MON_1		15
#define MON_2		16
#define MON_3		17
#define MON_4		18
#define MON_5		19
#define MON_6		20
#define MON_7		21
#define MON_8		22
#define MON_9		23
#define MON_10		24
#define MON_11		25
#define MON_12		26

/* The months, abbreviated */
#define ABMON_1		27
#define ABMON_2		28
#define ABMON_3		29
#define ABMON_4		30
#define ABMON_5		31
#define ABMON_6		32
#define ABMON_7		33
#define ABMON_8		34
#define ABMON_9		35
#define ABMON_10	36
#define ABMON_11	37
#define ABMON_12	38

/* Words and marks */
#define YESSTR		39
#define NOSTR		40
#define AM_STR		41
#define PM_STR		42
#define SOFTHYPHEN	43
#define HARDHYPHEN	44
#define OPENQUOTE	45
#define CLOSEQUOTE	46
#define YESTERDAYSTR	47
#define TODAYSTR	48
#define TOMORROWSTR	49
#define FUTURESTR	50

/* One past the last string number */
#define MAXSTRMSG	0x47

/* The library's base */
struct LocaleBase {
	struct Library	lb_LibNode;
	BOOL		lb_SysPatches;	/* the library has patched the system */
};

/* A locale, from OpenLocale(); read only */
struct Locale {
	STRPTR	loc_LocaleName;
	STRPTR	loc_LanguageName;	/* the language driver's name */
	STRPTR	loc_PrefLanguages[10];	/* the preferred languages, in order */
	ULONG	loc_Flags;

	ULONG	loc_CodeSet;
	ULONG	loc_CountryCode;
	ULONG	loc_TelephoneCode;
	LONG	loc_GMTOffset;		/* minutes from GMT */
	UBYTE	loc_MeasuringSystem;	/* MS_ */
	UBYTE	loc_CalendarType;	/* CT_ */
	UBYTE	loc_Reserved0[2];

	STRPTR	loc_DateTimeFormat;
	STRPTR	loc_DateFormat;
	STRPTR	loc_TimeFormat;

	STRPTR	loc_ShortDateTimeFormat;
	STRPTR	loc_ShortDateFormat;
	STRPTR	loc_ShortTimeFormat;

	/* numbers */
	STRPTR	loc_DecimalPoint;
	STRPTR	loc_GroupSeparator;
	STRPTR	loc_FracGroupSeparator;
	UBYTE	*loc_Grouping;
	UBYTE	*loc_FracGrouping;

	/* money */
	STRPTR	loc_MonDecimalPoint;
	STRPTR	loc_MonGroupSeparator;
	STRPTR	loc_MonFracGroupSeparator;
	UBYTE	*loc_MonGrouping;
	UBYTE	*loc_MonFracGrouping;
	UBYTE	loc_MonFracDigits;
	UBYTE	loc_MonIntFracDigits;
	UBYTE	loc_Reserved1[2];

	STRPTR	loc_MonCS;		/* the currency symbol */
	STRPTR	loc_MonSmallCS;		/* the symbol of its small unit */
	STRPTR	loc_MonIntCS;		/* the international symbol */

	STRPTR	loc_MonPositiveSign;
	UBYTE	loc_MonPositiveSpaceSep;	/* SS_ */
	UBYTE	loc_MonPositiveSignPos;		/* SP_ */
	UBYTE	loc_MonPositiveCSPos;		/* CSP_ */
	UBYTE	loc_Reserved2;

	STRPTR	loc_MonNegativeSign;
	UBYTE	loc_MonNegativeSpaceSep;
	UBYTE	loc_MonNegativeSignPos;
	UBYTE	loc_MonNegativeCSPos;
	UBYTE	loc_Reserved3;
};

/* loc_MeasuringSystem */
#define MS_ISO		0
#define MS_AMERICAN	1
#define MS_IMPERIAL	2
#define MS_BRITISH	3

/* loc_CalendarType: the first day of the week */
#define CT_7SUN		0
#define CT_7MON		1
#define CT_7TUE		2
#define CT_7WED		3
#define CT_7THU		4
#define CT_7FRI		5
#define CT_7SAT		6

/* loc_MonPositiveSpaceSep and loc_MonNegativeSpaceSep */
#define SS_NOSPACE	0
#define SS_SPACE	1

/* loc_MonPositiveSignPos and loc_MonNegativeSignPos */
#define SP_PARENS	0	/* the amount in parentheses */
#define SP_PREC_ALL	1	/* the sign before the amount and symbol */
#define SP_SUCC_ALL	2	/* the sign after them */
#define SP_PREC_CURR	3	/* the sign just before the symbol */
#define SP_SUCC_CURR	4	/* the sign just after the symbol */

/* loc_MonPositiveCSPos and loc_MonNegativeCSPos */
#define CSP_PRECEDES	0
#define CSP_SUCCEEDS	1

/* OpenCatalogA() tags */
#define OC_TagBase		(TAG_USER + 0x90000)
#define OC_BuiltInLanguage	(OC_TagBase + 1)
#define OC_BuiltInCodeSet	(OC_TagBase + 2)
#define OC_Version		(OC_TagBase + 3)
#define OC_Language		(OC_TagBase + 4)

/* StrnCmp() and StrConvert() types */
#define SC_ASCII	0
#define SC_COLLATE1	1
#define SC_COLLATE2	2

/* A catalog, from OpenCatalogA(); read only */
struct Catalog {
	struct Node	cat_Link;
	UWORD		cat_Pad;
	STRPTR		cat_Language;
	ULONG		cat_CodeSet;
	UWORD		cat_Version;
	UWORD		cat_Revision;
};

/* More names from the 3.2 interface */
#define ALTDAY_1		52
#define ALTDAY_2		53
#define ALTDAY_3		54
#define ALTDAY_4		55
#define ALTDAY_5		56
#define ALTDAY_6		57
#define ALTDAY_7		58
#define ALTMON_1		59
#define ALTMON_10		68
#define ALTMON_11		69
#define ALTMON_12		70
#define ALTMON_2		60
#define ALTMON_3		61
#define ALTMON_4		62
#define ALTMON_5		63
#define ALTMON_6		64
#define ALTMON_7		65
#define ALTMON_8		66
#define ALTMON_9		67

#endif /* LIBRARIES_LOCALE_H */
