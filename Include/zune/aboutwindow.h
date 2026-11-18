/* AboutWindow.mcc: a program's About window: its logo, name, version,
 * copyright, description, authors and sponsors. Names and numbers as
 * AROS's published interface. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_ABOUTWINDOW_H
#define ZUNE_ABOUTWINDOW_H

#include <libraries/mui.h>

#ifndef MUIB_RSVD
#define MUIB_RSVD (MUIB_MUI | 0x10400000UL)
#endif
#ifndef MUIB_AROS
#define MUIB_AROS (MUIB_RSVD | 0x00070000UL)
#endif

#define MUIC_AboutWindow "AboutWindow.mcc"
#define MUIB_AboutWindow (MUIB_AROS | 0x00000400UL)

/* each I--; a string left out comes from the application, one given as NULL is left out */
#define MUIA_AboutWindow_Image          (MUIB_AboutWindow | 0x00000000UL)   /* Object * */
#define MUIA_AboutWindow_Title          (MUIB_AboutWindow | 0x00000001UL)   /* CONST_STRPTR */
#define MUIA_AboutWindow_Version_Number (MUIB_AboutWindow | 0x00000002UL)   /* CONST_STRPTR */
#define MUIA_AboutWindow_Version_Date   (MUIB_AboutWindow | 0x00000003UL)   /* CONST_STRPTR */
#define MUIA_AboutWindow_Version_Extra  (MUIB_AboutWindow | 0x00000004UL)   /* CONST_STRPTR */
#define MUIA_AboutWindow_Copyright      (MUIB_AboutWindow | 0x00000005UL)   /* CONST_STRPTR */
#define MUIA_AboutWindow_Description    (MUIB_AboutWindow | 0x00000006UL)   /* CONST_STRPTR */
#define MUIA_AboutWindow_Authors        (MUIB_AboutWindow | 0x00000007UL)   /* struct TagItem * */
#define MUIA_AboutWindow_Sponsors       (MUIB_AboutWindow | 0x00000008UL)   /* struct TagItem * */

/* The Authors and Sponsors lists: sections, each an id and its names */
#define SECTION_ID      (MUIB_AboutWindow | 0x000000F0UL)
#define NAME_STRING     (MUIB_AboutWindow | 0x000000F1UL)
#define SID_NONE        0
#define SID_PROGRAMMING 1
#define SID_TRANSLATING 2
#define SECTION(id, ...) SECTION_ID, (id), __VA_ARGS__
#define NAME(name)       NAME_STRING, ((IPTR)(name))
#ifndef TAGLIST
#define TAGLIST(...) ((struct TagItem *)(IPTR[]){ __VA_ARGS__, TAG_DONE })
#endif

#define AboutWindowObject MUIOBJMACRO_START(MUIC_AboutWindow)

#endif
