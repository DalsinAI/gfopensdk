/* PrefsWindow.mcc: the older Prefs window. Its contents are the
 * program's; it adds Test, Revert, Save, Use and Cancel buttons that call
 * its own methods, for a subclass to do the work. Names and numbers as
 * AROS's published interface. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_PREFSWINDOW_H
#define ZUNE_PREFSWINDOW_H

#include <libraries/mui.h>

#ifndef MUIB_RSVD
#define MUIB_RSVD (MUIB_MUI | 0x10400000UL)
#endif
#ifndef MUIB_AROS
#define MUIB_AROS (MUIB_RSVD | 0x00070000UL)
#endif

#define MUIC_PrefsWindow "PrefsWindow.mcc"
#define MUIB_PrefsWindow (MUIB_AROS | 0x00000200UL)

#define MUIM_PrefsWindow_Test        (MUIB_PrefsWindow | 0x00000000UL)
#define MUIM_PrefsWindow_Revert      (MUIB_PrefsWindow | 0x00000001UL)
#define MUIM_PrefsWindow_Save        (MUIB_PrefsWindow | 0x00000002UL)
#define MUIM_PrefsWindow_Use         (MUIB_PrefsWindow | 0x00000003UL)
#define MUIM_PrefsWindow_Cancel      (MUIB_PrefsWindow | 0x00000004UL)
#define MUIM_PrefsWindow_Import      (MUIB_PrefsWindow | 0x00000005UL)
#define MUIM_PrefsWindow_Export      (MUIB_PrefsWindow | 0x00000006UL)
#define MUIM_PrefsWindow_SetDefaults (MUIB_PrefsWindow | 0x00000007UL)

struct MUIP_PrefsWindow_Export { IPTR MethodID; IPTR withIcon; };

#define MUIA_PrefsWindow_Test_Disabled   (MUIB_PrefsWindow | 0x00000000UL)   /* ISG BOOL */
#define MUIA_PrefsWindow_Revert_Disabled (MUIB_PrefsWindow | 0x00000001UL)   /* ISG BOOL */
#define MUIA_PrefsWindow_Save_Disabled   (MUIB_PrefsWindow | 0x00000002UL)   /* ISG BOOL */
#define MUIA_PrefsWindow_Use_Disabled    (MUIB_PrefsWindow | 0x00000003UL)   /* ISG BOOL */
#define MUIA_PrefsWindow_Cancel_Disabled (MUIB_PrefsWindow | 0x00000004UL)   /* ISG BOOL */

#define PrefsWindowObject MUIOBJMACRO_START(MUIC_PrefsWindow)

#endif
