#ifndef DEVICES_INPUTEVENT_H
#define DEVICES_INPUTEVENT_H
/*
 * OpenNDK: the input event that keyboard, mouse and other sources feed
 * through input.device's handler chain.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef DEVICES_TIMER_H
#include <devices/timer.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* ie_Class */
#define IECLASS_NULL		0x00
#define IECLASS_RAWKEY		0x01
#define IECLASS_RAWMOUSE	0x02
#define IECLASS_EVENT		0x03
#define IECLASS_POINTERPOS	0x04
#define IECLASS_TIMER		0x06
#define IECLASS_GADGETDOWN	0x07
#define IECLASS_GADGETUP	0x08
#define IECLASS_REQUESTER	0x09
#define IECLASS_MENULIST	0x0A
#define IECLASS_CLOSEWINDOW	0x0B
#define IECLASS_SIZEWINDOW	0x0C
#define IECLASS_REFRESHWINDOW	0x0D
#define IECLASS_NEWPREFS	0x0E
#define IECLASS_DISKREMOVED	0x0F
#define IECLASS_DISKINSERTED	0x10
#define IECLASS_ACTIVEWINDOW	0x11
#define IECLASS_INACTIVEWINDOW	0x12
#define IECLASS_NEWPOINTERPOS	0x13
#define IECLASS_MENUHELP	0x14
#define IECLASS_CHANGEWINDOW	0x15

#define IECLASS_MAX		0x15

/* ie_SubClass of IECLASS_NEWPOINTERPOS */
#define IESUBCLASS_COMPATIBLE	0x00
#define IESUBCLASS_PIXEL	0x01	/* ie_EventAddress: IEPointerPixel */
#define IESUBCLASS_TABLET	0x02	/* ie_EventAddress: IEPointerTablet */
#define IESUBCLASS_NEWTABLET	0x03	/* ie_EventAddress: IENewTablet */

struct Screen;

/* A pointer position in a given screen's pixels */
struct IEPointerPixel {
	struct Screen	*iepp_Screen;
	struct {
		WORD	X;
		WORD	Y;
	} iepp_Position;
};

/* A tablet position and its range */
struct IEPointerTablet {
	struct {
		UWORD	X;
		UWORD	Y;
	} iept_Range;
	struct {
		UWORD	X;
		UWORD	Y;
	} iept_Value;
	WORD	iept_Pressure;
};

/* A tablet event with scaling done by a callback */
struct IENewTablet {
	struct Hook	*ient_CallBack;
	UWORD		ient_ScaledX;
	UWORD		ient_ScaledY;
	UWORD		ient_ScaledXFraction;
	UWORD		ient_ScaledYFraction;
	ULONG		ient_TabletX;
	ULONG		ient_TabletY;
	ULONG		ient_RangeX;
	ULONG		ient_RangeY;
	struct TagItem	*ient_TagList;
};

/* ie_Code */
#define IECODE_UP_PREFIX	0x80	/* key or button released */
#define IECODEB_UP_PREFIX	7
#define IECODE_KEY_CODE_FIRST	0x00
#define IECODE_KEY_CODE_LAST	0x77
#define IECODE_COMM_CODE_FIRST	0x78
#define IECODE_COMM_CODE_LAST	0x7F

/* Character ranges, for cooked events */
#define IECODE_C0_FIRST		0x00
#define IECODE_C0_LAST		0x1F
#define IECODE_ASCII_FIRST	0x20
#define IECODE_ASCII_LAST	0x7E
#define IECODE_ASCII_DEL	0x7F
#define IECODE_C1_FIRST		0x80
#define IECODE_C1_LAST		0x9F
#define IECODE_LATIN1_FIRST	0xA0
#define IECODE_LATIN1_LAST	0xFF

/* IECLASS_RAWMOUSE */
#define IECODE_LBUTTON		0x68
#define IECODE_RBUTTON		0x69
#define IECODE_MBUTTON		0x6A
#define IECODE_NOBUTTON		0xFF

/* IECLASS_EVENT */
#define IECODE_NEWACTIVE	0x01
#define IECODE_NEWSIZE		0x02
#define IECODE_REFRESH		0x03

/* IECLASS_REQUESTER */
#define IECODE_REQSET		0x01
#define IECODE_REQCLEAR		0x00

/* ie_Qualifier */
#define IEQUALIFIER_LSHIFT		0x0001
#define IEQUALIFIER_RSHIFT		0x0002
#define IEQUALIFIER_CAPSLOCK		0x0004
#define IEQUALIFIER_CONTROL		0x0008
#define IEQUALIFIER_LALT		0x0010
#define IEQUALIFIER_RALT		0x0020
#define IEQUALIFIER_LCOMMAND		0x0040
#define IEQUALIFIER_RCOMMAND		0x0080
#define IEQUALIFIER_NUMERICPAD		0x0100
#define IEQUALIFIER_REPEAT		0x0200
#define IEQUALIFIER_INTERRUPT		0x0400
#define IEQUALIFIER_MULTIBROADCAST	0x0800
#define IEQUALIFIER_MIDBUTTON		0x1000
#define IEQUALIFIER_RBUTTON		0x2000
#define IEQUALIFIER_LEFTBUTTON		0x4000
#define IEQUALIFIER_RELATIVEMOUSE	0x8000

#define IEQUALIFIERB_LSHIFT		0
#define IEQUALIFIERB_RSHIFT		1
#define IEQUALIFIERB_CAPSLOCK		2
#define IEQUALIFIERB_CONTROL		3
#define IEQUALIFIERB_LALT		4
#define IEQUALIFIERB_RALT		5
#define IEQUALIFIERB_LCOMMAND		6
#define IEQUALIFIERB_RCOMMAND		7
#define IEQUALIFIERB_NUMERICPAD		8
#define IEQUALIFIERB_REPEAT		9
#define IEQUALIFIERB_INTERRUPT		10
#define IEQUALIFIERB_MULTIBROADCAST	11
#define IEQUALIFIERB_MIDBUTTON		12
#define IEQUALIFIERB_RBUTTON		13
#define IEQUALIFIERB_LEFTBUTTON		14
#define IEQUALIFIERB_RELATIVEMOUSE	15

struct InputEvent {
	struct InputEvent *ie_NextEvent;	/* the next in the chain */
	UBYTE	ie_Class;			/* IECLASS_ */
	UBYTE	ie_SubClass;
	UWORD	ie_Code;
	UWORD	ie_Qualifier;
	union {
		struct {
			WORD	ie_x;		/* mouse movement or position */
			WORD	ie_y;
		} ie_xy;
		APTR	ie_addr;		/* a class's own data */
		struct {
			UBYTE	ie_prev1DownCode;	/* previous keys, */
			UBYTE	ie_prev1DownQual;	/* for dead keys */
			UBYTE	ie_prev2DownCode;
			UBYTE	ie_prev2DownQual;
		} ie_dead;
	} ie_position;
	TimeVal_Type ie_TimeStamp;
};

#define ie_X			ie_position.ie_xy.ie_x
#define ie_Y			ie_position.ie_xy.ie_y
#define ie_EventAddress		ie_position.ie_addr
#define ie_Prev1DownCode	ie_position.ie_dead.ie_prev1DownCode
#define ie_Prev1DownQual	ie_position.ie_dead.ie_prev1DownQual
#define ie_Prev2DownCode	ie_position.ie_dead.ie_prev2DownCode
#define ie_Prev2DownQual	ie_position.ie_dead.ie_prev2DownQual

#endif /* DEVICES_INPUTEVENT_H */
