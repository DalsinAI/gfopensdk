#ifndef PREFS_PRINTERTXT_H
#define PREFS_PRINTERTXT_H
/*
 * OpenNDK: printer preferences: driver, port, paper and text (PTXT, PUNT and PDEV chunks).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif

#define ID_PTXT		MAKE_ID('P','T','X','T')
#define ID_PUNT		MAKE_ID('P','U','N','T')
#define ID_PDEV		MAKE_ID('P','D','E','V')

#define DRIVERNAMESIZE	30
#define DEVICENAMESIZE	32
#define UNITNAMESIZE	32

struct PrinterTxtPrefs
{
    LONG pt_Reserved[4];
    TEXT	pt_Driver[DRIVERNAMESIZE];
    UBYTE pt_Port;			/* PP_PARALLEL or PP_SERIAL */

    UWORD pt_PaperType;
    UWORD pt_PaperSize;
    UWORD pt_PaperLength;		/* lines per page */

    UWORD pt_Pitch;
    UWORD pt_Spacing;
    UWORD pt_LeftMargin;
    UWORD pt_RightMargin;
    UWORD pt_Quality;
};

/* pt_Port */
#define PP_PARALLEL	0
#define PP_SERIAL	1

/* pt_PaperType */
#define PT_FANFOLD	0
#define PT_SINGLE	1

/* pt_PaperSize */
#define PS_US_LETTER	0
#define PS_US_LEGAL	1
#define PS_N_TRACTOR	2
#define PS_W_TRACTOR	3
#define PS_CUSTOM	4
#define PS_EURO_A0	5
#define PS_EURO_A1	6
#define PS_EURO_A2	7
#define PS_EURO_A3	8
#define PS_EURO_A4	9
#define PS_EURO_A5	10
#define PS_EURO_A6	11
#define PS_EURO_A7	12
#define PS_EURO_A8	13

/* pt_Pitch */
#define PP_PICA		0
#define PP_ELITE	1
#define PP_FINE		2

/* pt_Spacing */
#define PS_SIX_LPI	0
#define PS_EIGHT_LPI	1

/* pt_Quality */
#define PQ_DRAFT	0
#define PQ_LETTER	1

/* Which unit of which device the printer is on */
struct PrinterUnitPrefs
{
    LONG pu_Reserved[4];
    LONG pu_UnitNum;
    ULONG pu_OpenDeviceFlags;
    TEXT	pu_DeviceName[DEVICENAMESIZE];	/* without ".device" */
};

/* A printer unit's name (V44) */
struct PrinterDeviceUnitPrefs
{
    LONG pd_Reserved[4];
    LONG pd_UnitNum;
    TEXT	pd_UnitName[UNITNAMESIZE];
};

#endif /* PREFS_PRINTERTXT_H */
