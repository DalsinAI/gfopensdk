#ifndef DEVICES_CONSOLE_H
#define DEVICES_CONSOLE_H
/*
 * OpenNDK: console.device's commands and the numbers of its control
 * sequences.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_IO_H
#include <exec/io.h>
#endif

/* Commands */
#define CD_ASKKEYMAP		(CMD_NONSTD+0)
#define CD_SETKEYMAP		(CMD_NONSTD+1)
#define CD_ASKDEFAULTKEYMAP	(CMD_NONSTD+2)
#define CD_SETDEFAULTKEYMAP	(CMD_NONSTD+3)

/* Select graphic rendition (CSI n m) */
#define SGR_PRIMARY	0
#define SGR_BOLD	1
#define SGR_ITALIC	3
#define SGR_UNDERSCORE	4
#define SGR_NEGATIVE	7

#define SGR_NORMAL	22	/* not bold */
#define SGR_NOTITALIC	23
#define SGR_NOTUNDERSCORE 24
#define SGR_POSITIVE	27

/* Foreground colours; the names are those of the ANSI standard */
#define SGR_BLACK	30
#define SGR_RED		31
#define SGR_GREEN	32
#define SGR_YELLOW	33
#define SGR_BLUE	34
#define SGR_MAGENTA	35
#define SGR_CYAN	36
#define SGR_WHITE	37
#define SGR_DEFAULT	39

/* Background colours */
#define SGR_BLACKBG	40
#define SGR_REDBG	41
#define SGR_GREENBG	42
#define SGR_YELLOWBG	43
#define SGR_BLUEBG	44
#define SGR_MAGENTABG	45
#define SGR_CYANBG	46
#define SGR_WHITEBG	47
#define SGR_DEFAULTBG	49

/* The same, by pen number */
#define SGR_CLR0	30
#define SGR_CLR1	31
#define SGR_CLR2	32
#define SGR_CLR3	33
#define SGR_CLR4	34
#define SGR_CLR5	35
#define SGR_CLR6	36
#define SGR_CLR7	37

#define SGR_CLR0BG	40
#define SGR_CLR1BG	41
#define SGR_CLR2BG	42
#define SGR_CLR3BG	43
#define SGR_CLR4BG	44
#define SGR_CLR5BG	45
#define SGR_CLR6BG	46
#define SGR_CLR7BG	47

/* Device status report: cursor position */
#define DSR_CPR		6

/* Cursor tabulation control */
#define CTC_HSETTAB	0
#define CTC_HCLRTAB	2
#define CTC_HCLRTABSALL	5

/* Tabulation clear */
#define TBC_HCLRTAB	0
#define TBC_HCLRTABSALL	3

/* Modes for set and reset mode (CSI h, CSI l) */
#define M_LNM	20	/* line feed is also carriage return */
#define M_ASM	">1"	/* auto scroll */
#define M_AWM	"?7"	/* auto wrap */

/* CD_SETUPSCROLLBACK's data: a scroller to drive and the lines to keep */
struct ConsoleScrollback {
	struct Gadget	*cs_ScrollerGadget;
	UWORD		cs_NumLines;
};

/* More names from the 3.2 interface */
#define CD_SETSCROLLBACKPOSITION	14
#define CD_SETUPSCROLLBACK	13

#endif /* DEVICES_CONSOLE_H */
