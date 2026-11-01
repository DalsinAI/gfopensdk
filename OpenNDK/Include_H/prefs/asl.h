#ifndef PREFS_ASL_H
#define PREFS_ASL_H
/*
 * OpenNDK: the ASL requester preferences (the ASL chunk).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif
#ifndef LIBRARIES_ASL_H
#include <libraries/asl.h>
#endif

struct AslPrefs
{
	LONG	ap_Reserved[4];
	UBYTE	ap_SortBy;		/* ASLSORTBY_ of libraries/asl.h */
	UBYTE	ap_SortDrawers;
	UBYTE	ap_SortOrder;
	UBYTE	ap_SizePosition;	/* ASLPOS_ and ASLSIZE_ */
	WORD	ap_RelativeLeft;
	WORD	ap_RelativeTop;
	UBYTE	ap_RelativeWidth;	/* percent of the screen */
	UBYTE	ap_RelativeHeight;
};

/* More names from the 3.2 interface */
#define ID_ASL			0x41534C20

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef LIBRARIES_ASL_H
#include <libraries/asl.h>
#endif

#endif /* PREFS_ASL_H */
