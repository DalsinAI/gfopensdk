#ifndef INTUITION_PREFERENCES_H
#define INTUITION_PREFERENCES_H
/*
 * OpenNDK: the old fixed-size struct Preferences (GetPrefs, SetPrefs)
 * and the values its fields take.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef DEVICES_TIMER_H
#include <devices/timer.h>
#endif

/* Array sizes */
#define FILENAME_SIZE	30
#define DEVNAME_SIZE	16

/* The pointer image: a 16-row sprite with its control words */
#define POINTERSIZE	((1 + 16 + 1) * 2)

/* FontHeight */
#define TOPAZ_EIGHTY	8
#define TOPAZ_SIXTY	9

struct Preferences
{
    BYTE FontHeight;			/* TOPAZ_ */
    UBYTE PrinterPort;			/* PARALLEL_PRINTER or SERIAL_PRINTER */
    UWORD BaudRate;			/* BAUD_ */

    /* Timing */
    TimeVal_Type KeyRptSpeed;
    TimeVal_Type KeyRptDelay;
    TimeVal_Type DoubleClick;

    /* The pointer */
    UWORD PointerMatrix[POINTERSIZE];
    BYTE XOffset;
    BYTE YOffset;
    UWORD color17;
    UWORD color18;
    UWORD color19;
    UWORD PointerTicks;

    /* Workbench colours */
    UWORD color0;
    UWORD color1;
    UWORD color2;
    UWORD color3;

    /* Where the display starts */
    BYTE ViewXOffset;
    BYTE ViewYOffset;
    WORD ViewInitX, ViewInitY;

    BOOL EnableCLI;

    /* The printer */
    UWORD PrinterType;
    TEXT	PrinterFilename[FILENAME_SIZE];

    UWORD PrintPitch;
    UWORD PrintQuality;
    UWORD PrintSpacing;
    UWORD PrintLeftMargin;
    UWORD PrintRightMargin;
    UWORD PrintImage;
    UWORD PrintAspect;
    UWORD PrintShade;
    WORD PrintThreshold;

    UWORD PaperSize;
    UWORD PaperLength;
    UWORD PaperType;

    /* The serial port */
    UBYTE SerRWBits;			/* read bits high nibble, write bits low */
    UBYTE SerStopBuf;			/* stop bits high, buffer size low */
    UBYTE SerParShk;			/* parity high, handshake low */
    UBYTE LaceWB;

    UBYTE Pad[12];
    TEXT	PrtDevName[DEVNAME_SIZE];	/* without ".device" */

    UBYTE DefaultPrtUnit;
    UBYTE DefaultSerUnit;

    BYTE RowSizeChange;
    BYTE ColumnSizeChange;

    UWORD PrintFlags;
    UWORD PrintMaxWidth;
    UWORD PrintMaxHeight;
    UBYTE PrintDensity;
    UBYTE PrintXOffset;

    UWORD wb_Width;
    UWORD wb_Height;
    UBYTE wb_Depth;

    UBYTE ext_size;			/* reserved */
};

/* LaceWB */
#define LACEWB		(1 << 0)
#define LW_RESERVED	1

/* Flags kept in the old fields */
#define SCREEN_DRAG	(1 << 14)
#define MOUSE_ACCEL	(1 << 15)

/* PrinterPort */
#define PARALLEL_PRINTER 0x00
#define SERIAL_PRINTER	0x01

/* BaudRate */
#define BAUD_110	0x00
#define BAUD_300	0x01
#define BAUD_1200	0x02
#define BAUD_2400	0x03
#define BAUD_4800	0x04
#define BAUD_9600	0x05
#define BAUD_19200	0x06
#define BAUD_MIDI	0x07

/* PaperType */
#define FANFOLD		0x00
#define SINGLE		0x80

/* PrintPitch */
#define PICA		0x000
#define ELITE		0x400
#define FINE		0x800

/* PrintQuality */
#define DRAFT		0x000
#define LETTER		0x100

/* PrintSpacing */
#define SIX_LPI		0x000
#define EIGHT_LPI	0x200

/* PrintImage */
#define IMAGE_POSITIVE	0x00
#define IMAGE_NEGATIVE	0x01

/* PrintAspect */
#define ASPECT_HORIZ	0x00
#define ASPECT_VERT	0x01

/* PrintShade */
#define SHADE_BW	0x00
#define SHADE_GREYSCALE	0x01
#define SHADE_COLOR	0x02

/* PaperSize */
#define US_LETTER	0x00
#define US_LEGAL	0x10
#define N_TRACTOR	0x20
#define W_TRACTOR	0x30
#define CUSTOM		0x40
#define EURO_A0		0x50
#define EURO_A1		0x60
#define EURO_A2		0x70
#define EURO_A3		0x80
#define EURO_A4		0x90
#define EURO_A5		0xA0
#define EURO_A6		0xB0
#define EURO_A7		0xC0
#define EURO_A8		0xD0

/* PrinterType */
#define CUSTOM_NAME		0x00
#define ALPHA_P_101		0x01
#define BROTHER_15XL		0x02
#define CBM_MPS1000		0x03
#define DIAB_630		0x04
#define DIAB_ADV_D25		0x05
#define DIAB_C_150		0x06
#define EPSON			0x07
#define EPSON_JX_80		0x08
#define OKIMATE_20		0x09
#define QUME_LP_20		0x0A
#define HP_LASERJET		0x0B
#define HP_LASERJET_PLUS	0x0C

/* SerStopBuf's buffer size */
#define SBUF_512	0x00
#define SBUF_1024	0x01
#define SBUF_2048	0x02
#define SBUF_4096	0x03
#define SBUF_8000	0x04
#define SBUF_16000	0x05

/* The serial bytes' nibbles */
#define SREAD_BITS	0xF0
#define SWRITE_BITS	0x0F

#define SSTOP_BITS	0xF0
#define SBUFSIZE_BITS	0x0F

#define SPARITY_BITS	0xF0
#define SHSHAKE_BITS	0x0F

/* Parity */
#define SPARITY_NONE	0
#define SPARITY_EVEN	1
#define SPARITY_ODD	2
#define SPARITY_MARK	3		/* V39 */
#define SPARITY_SPACE	4		/* V39 */

/* Handshake */
#define SHSHAKE_XON	0
#define SHSHAKE_RTS	1
#define SHSHAKE_NONE	2

/* PrintFlags */
#define CORRECT_RED		0x0001
#define CORRECT_GREEN		0x0002
#define CORRECT_BLUE		0x0004

#define CENTER_IMAGE		0x0008

#define IGNORE_DIMENSIONS	0x0000
#define BOUNDED_DIMENSIONS	0x0010
#define ABSOLUTE_DIMENSIONS	0x0020
#define PIXEL_DIMENSIONS	0x0040
#define MULTIPLY_DIMENSIONS	0x0080

#define INTEGER_SCALING		0x0100

#define ORDERED_DITHERING	0x0000
#define HALFTONE_DITHERING	0x0200
#define FLOYD_DITHERING		0x0400

#define ANTI_ALIAS		0x0800
#define GREY_SCALE2		0x1000

/* Masks over PrintFlags */
#define CORRECT_RGB_MASK	(CORRECT_RED | CORRECT_GREEN | CORRECT_BLUE)
#define DIMENSIONS_MASK \
    (BOUNDED_DIMENSIONS | ABSOLUTE_DIMENSIONS | PIXEL_DIMENSIONS | MULTIPLY_DIMENSIONS)
#define DITHERING_MASK		(HALFTONE_DITHERING | FLOYD_DITHERING)

#endif /* INTUITION_PREFERENCES_H */
