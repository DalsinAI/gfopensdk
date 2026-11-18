/* SystemPrefsWindow.mcc: a Prefs program's window. Its contents are a
 * PrefsEditor; it adds the Save, Use, Test and Cancel buttons and takes
 * its title from the editor's name. Names and numbers as AROS's published
 * interface. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_SYSTEMPREFSWINDOW_H
#define ZUNE_SYSTEMPREFSWINDOW_H

#include <zune/prefseditor.h>

#define MUIC_SystemPrefsWindow "SystemPrefsWindow.mcc"
#define MUIB_SystemPrefsWindow (MUIB_AROS | 0x00000600UL)

#define SystemPrefsWindowObject MUIOBJMACRO_START(MUIC_SystemPrefsWindow)

#endif
