#ifndef LIBRARIES_KEYMAP_H
#define LIBRARIES_KEYMAP_H
/*
 * OpenNDK: raw key codes by name.
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

/* More names from the 3.2 interface */
#define RAWKEY_BACKSPACE	65
#define RAWKEY_BREAK		110
#define RAWKEY_CAPSLOCK		98
#define RAWKEY_CRSRDOWN		77
#define RAWKEY_CRSRLEFT		79
#define RAWKEY_CRSRRIGHT	78
#define RAWKEY_CRSRUP		76
#define RAWKEY_DEL		70
#define RAWKEY_END		113
#define RAWKEY_ENTER		67
#define RAWKEY_ESC		69
#define RAWKEY_F1		80
#define RAWKEY_F10		89
#define RAWKEY_F11		75
#define RAWKEY_F12		111
#define RAWKEY_F2		81
#define RAWKEY_F3		82
#define RAWKEY_F4		83
#define RAWKEY_F5		84
#define RAWKEY_F6		85
#define RAWKEY_F7		86
#define RAWKEY_F8		87
#define RAWKEY_F9		88
#define RAWKEY_HELP		95
#define RAWKEY_HOME		112
#define RAWKEY_INSERT		71
#define RAWKEY_LALT		100
#define RAWKEY_LCOMMAND		102
#define RAWKEY_LCTRL		99
#define RAWKEY_LSHIFT		96
#define RAWKEY_MEDIA_NEXT_TRACK	117
#define RAWKEY_MEDIA_PLAY_PAUSE	115
#define RAWKEY_MEDIA_PREV_TRACK	116
#define RAWKEY_MEDIA_REPEAT	119
#define RAWKEY_MEDIA_SHUFFLE	118
#define RAWKEY_MEDIA_STOP	114
#define RAWKEY_MENU		107
#define RAWKEY_PAGEDOWN		73
#define RAWKEY_PAGEUP		72
#define RAWKEY_PRINTSCR		109
#define RAWKEY_RALT		101
#define RAWKEY_RCOMMAND		103
#define RAWKEY_RETURN		68
#define RAWKEY_RSHIFT		97
#define RAWKEY_SPACE		64
#define RAWKEY_TAB		66
#define RAWKEY_WHEEL_DOWN	123
#define RAWKEY_WHEEL_LEFT	124
#define RAWKEY_WHEEL_RIGHT	125
#define RAWKEY_WHEEL_UP		122

/* what the OS 3.2 header brings in with this one, which programs rely on */
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif

#endif /* LIBRARIES_KEYMAP_H */
