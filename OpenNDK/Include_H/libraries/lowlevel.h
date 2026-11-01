#ifndef LIBRARIES_LOWLEVEL_H
#define LIBRARIES_LOWLEVEL_H
/*
 * OpenNDK: lowlevel.library's structures, tags and answers.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* One entry of QueryKeys()'s array */
struct KeyQuery {
	UWORD	kq_KeyCode;
	BOOL	kq_Pressed;
};

/* ReadJoyPort(): what is plugged in, in the top four bits */
#define JP_TYPE_NOTAVAIL	(00<<28)
#define JP_TYPE_GAMECTLR	(01<<28)
#define JP_TYPE_MOUSE		(02<<28)
#define JP_TYPE_JOYSTK		(03<<28)
#define JP_TYPE_UNKNOWN		(04<<28)
#define JP_TYPE_MASK		(15<<28)

/* ReadJoyPort(): buttons */
#define JPB_BUTTON_BLUE		23
#define JPB_BUTTON_RED		22
#define JPB_BUTTON_YELLOW	21
#define JPB_BUTTON_GREEN	20
#define JPB_BUTTON_FORWARD	19
#define JPB_BUTTON_REVERSE	18
#define JPB_BUTTON_PLAY		17

#define JPF_BUTTON_BLUE		(1<<JPB_BUTTON_BLUE)
#define JPF_BUTTON_RED		(1<<JPB_BUTTON_RED)
#define JPF_BUTTON_YELLOW	(1<<JPB_BUTTON_YELLOW)
#define JPF_BUTTON_GREEN	(1<<JPB_BUTTON_GREEN)
#define JPF_BUTTON_FORWARD	(1<<JPB_BUTTON_FORWARD)
#define JPF_BUTTON_REVERSE	(1<<JPB_BUTTON_REVERSE)
#define JPF_BUTTON_PLAY		(1<<JPB_BUTTON_PLAY)
#define JP_BUTTON_MASK		(JPF_BUTTON_BLUE|JPF_BUTTON_RED|JPF_BUTTON_YELLOW|JPF_BUTTON_GREEN|\
				 JPF_BUTTON_FORWARD|JPF_BUTTON_REVERSE|JPF_BUTTON_PLAY)

/* ReadJoyPort(): directions, for a joystick or game controller */
#define JPB_JOY_UP	3
#define JPB_JOY_DOWN	2
#define JPB_JOY_LEFT	1
#define JPB_JOY_RIGHT	0

#define JPF_JOY_UP	(1<<JPB_JOY_UP)
#define JPF_JOY_DOWN	(1<<JPB_JOY_DOWN)
#define JPF_JOY_LEFT	(1<<JPB_JOY_LEFT)
#define JPF_JOY_RIGHT	(1<<JPB_JOY_RIGHT)
#define JP_DIRECTION_MASK	(JPF_JOY_UP|JPF_JOY_DOWN|JPF_JOY_LEFT|JPF_JOY_RIGHT)

/* ReadJoyPort(): a mouse's counters */
#define JP_MHORZ_MASK	(255<<0)
#define JP_MVERT_MASK	(255<<8)
#define JP_MOUSE_MASK	(JP_MHORZ_MASK|JP_MVERT_MASK)

/* GetKey(): the qualifiers, above the key code */
#define LLKB_LSHIFT	16
#define LLKB_RSHIFT	17
#define LLKB_CAPSLOCK	18
#define LLKB_CONTROL	19
#define LLKB_LALT	20
#define LLKB_RALT	21
#define LLKB_LAMIGA	22
#define LLKB_RAMIGA	23

#define LLKF_LSHIFT	(1<<LLKB_LSHIFT)
#define LLKF_RSHIFT	(1<<LLKB_RSHIFT)
#define LLKF_CAPSLOCK	(1<<LLKB_CAPSLOCK)
#define LLKF_CONTROL	(1<<LLKB_CONTROL)
#define LLKF_LALT	(1<<LLKB_LALT)
#define LLKF_RALT	(1<<LLKB_RALT)
#define LLKF_LAMIGA	(1<<LLKB_LAMIGA)
#define LLKF_RAMIGA	(1<<LLKB_RAMIGA)

/* SystemControlA() tags */
#define SCON_TagBase		(TAG_USER + 0x00C00000)
#define SCON_TakeOverSys	(SCON_TagBase+0)
#define SCON_KillReq		(SCON_TagBase+1)
#define SCON_CDReboot		(SCON_TagBase+2)
#define SCON_StopInput		(SCON_TagBase+3)
#define SCON_AddCreateKeys	(SCON_TagBase+4)
#define SCON_RemCreateKeys	(SCON_TagBase+5)

/* SCON_CDReboot's values */
#define CDReboot_On		1
#define CDReboot_Off		0
#define CDReboot_Default	2

/* SetJoyPortAttrsA() tags */
#define SJA_TagBase		(TAG_USER + 0x00C00100)
#define SJA_Type		(SJA_TagBase+1)
#define SJA_Reinitialize	(SJA_TagBase+2)

/* SJA_Type's values */
#define SJA_TYPE_AUTOSENSE	0
#define SJA_TYPE_GAMECTLR	1
#define SJA_TYPE_MOUSE		2
#define SJA_TYPE_JOYSTK		3

/* GetLanguageSelection() */
#define LANG_UNKNOWN	0
#define LANG_AMERICAN	1
#define LANG_ENGLISH	2
#define LANG_GERMAN	3
#define LANG_FRENCH	4
#define LANG_SPANISH	5
#define LANG_ITALIAN	6
#define LANG_PORTUGUESE	7
#define LANG_DANISH	8
#define LANG_DUTCH	9
#define LANG_NORWEGIAN	10
#define LANG_FINNISH	11
#define LANG_SWEDISH	12
#define LANG_JAPANESE	13
#define LANG_CHINESE	14
#define LANG_ARABIC	15
#define LANG_GREEK	16
#define LANG_HEBREW	17
#define LANG_KOREAN	18

/* More names from the 3.2 interface */
#define SCON_Dummy		(SCON_TagBase + 0)
#define SJA_Dummy		(SJA_TagBase + 0)
#define JPB_BTN1		23
#define JPB_BTN2		22
#define JPB_BTN3		21
#define JPB_BTN4		20
#define JPB_BTN5		19
#define JPB_BTN6		18
#define JPB_BTN7		17
#define JPB_DOWN		2
#define JPB_LEFT		1
#define JPB_RIGHT		0
#define JPB_UP			3
#define JPF_BTN1		0x800000
#define JPF_BTN2		0x400000
#define JPF_BTN3		0x200000
#define JPF_BTN4		0x100000
#define JPF_BTN5		0x80000
#define JPF_BTN6		0x40000
#define JPF_BTN7		0x20000
#define JPF_DOWN		4
#define JPF_LEFT		2
#define JPF_RIGHT		1
#define JPF_UP			8
#define RAWKEY_PORT0_BUTTON_BLUE	114
#define RAWKEY_PORT0_BUTTON_FORWARD	117
#define RAWKEY_PORT0_BUTTON_GREEN	118
#define RAWKEY_PORT0_BUTTON_PLAY	115
#define RAWKEY_PORT0_BUTTON_RED	120
#define RAWKEY_PORT0_BUTTON_REVERSE	116
#define RAWKEY_PORT0_BUTTON_YELLOW	119
#define RAWKEY_PORT0_JOY_DOWN	122
#define RAWKEY_PORT0_JOY_LEFT	124
#define RAWKEY_PORT0_JOY_RIGHT	123
#define RAWKEY_PORT0_JOY_UP	121
#define RAWKEY_PORT1_BUTTON_BLUE	0x172
#define RAWKEY_PORT1_BUTTON_FORWARD	0x175
#define RAWKEY_PORT1_BUTTON_GREEN	0x176
#define RAWKEY_PORT1_BUTTON_PLAY	0x173
#define RAWKEY_PORT1_BUTTON_RED	0x178
#define RAWKEY_PORT1_BUTTON_REVERSE	0x174
#define RAWKEY_PORT1_BUTTON_YELLOW	0x177
#define RAWKEY_PORT1_JOY_DOWN	0x17A
#define RAWKEY_PORT1_JOY_LEFT	0x17C
#define RAWKEY_PORT1_JOY_RIGHT	0x17B
#define RAWKEY_PORT1_JOY_UP	0x179
#define RAWKEY_PORT2_BUTTON_BLUE	0x272
#define RAWKEY_PORT2_BUTTON_FORWARD	0x275
#define RAWKEY_PORT2_BUTTON_GREEN	0x276
#define RAWKEY_PORT2_BUTTON_PLAY	0x273
#define RAWKEY_PORT2_BUTTON_RED	0x278
#define RAWKEY_PORT2_BUTTON_REVERSE	0x274
#define RAWKEY_PORT2_BUTTON_YELLOW	0x277
#define RAWKEY_PORT2_JOY_DOWN	0x27A
#define RAWKEY_PORT2_JOY_LEFT	0x27C
#define RAWKEY_PORT2_JOY_RIGHT	0x27B
#define RAWKEY_PORT2_JOY_UP	0x279
#define RAWKEY_PORT3_BUTTON_BLUE	0x372
#define RAWKEY_PORT3_BUTTON_FORWARD	0x375
#define RAWKEY_PORT3_BUTTON_GREEN	0x376
#define RAWKEY_PORT3_BUTTON_PLAY	0x373
#define RAWKEY_PORT3_BUTTON_RED	0x378
#define RAWKEY_PORT3_BUTTON_REVERSE	0x374
#define RAWKEY_PORT3_BUTTON_YELLOW	0x377
#define RAWKEY_PORT3_JOY_DOWN	0x37A
#define RAWKEY_PORT3_JOY_LEFT	0x37C
#define RAWKEY_PORT3_JOY_RIGHT	0x37B
#define RAWKEY_PORT3_JOY_UP	0x379

#endif /* LIBRARIES_LOWLEVEL_H */
