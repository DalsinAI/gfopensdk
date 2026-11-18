/* PrefsEditor.mcc: the editing part of a Prefs program, a Group whose
 * subclass reads and writes its settings (ImportFH, ExportFH,
 * SetDefaults) while this class does the files: ENV: on Use and Test,
 * ENVARC: and ENV: on Save, and the settings from before a Test put back
 * on Revert and Cancel. Names and numbers as AROS's published interface.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_PREFSEDITOR_H
#define ZUNE_PREFSEDITOR_H

#include <libraries/mui.h>
#ifndef GFOPENMUI_HOST
#include <dos/dos.h>
#endif

#ifndef MUIB_RSVD
#define MUIB_RSVD (MUIB_MUI | 0x10400000UL)
#endif
#ifndef MUIB_AROS
#define MUIB_AROS (MUIB_RSVD | 0x00070000UL)
#endif

#define MUIC_PrefsEditor "PrefsEditor.mcc"
#define MUIB_PrefsEditor (MUIB_AROS | 0x00000500UL)

#define MUIM_PrefsEditor_Test        (MUIB_PrefsEditor | 0x00000000UL)
#define MUIM_PrefsEditor_Revert      (MUIB_PrefsEditor | 0x00000001UL)
#define MUIM_PrefsEditor_Save        (MUIB_PrefsEditor | 0x00000002UL)
#define MUIM_PrefsEditor_Use         (MUIB_PrefsEditor | 0x00000003UL)
#define MUIM_PrefsEditor_Cancel      (MUIB_PrefsEditor | 0x00000004UL)
#define MUIM_PrefsEditor_Import      (MUIB_PrefsEditor | 0x00000005UL)
#define MUIM_PrefsEditor_Export      (MUIB_PrefsEditor | 0x00000006UL)
#define MUIM_PrefsEditor_ImportFH    (MUIB_PrefsEditor | 0x00000007UL)
#define MUIM_PrefsEditor_ExportFH    (MUIB_PrefsEditor | 0x00000008UL)
#define MUIM_PrefsEditor_SetDefaults (MUIB_PrefsEditor | 0x00000009UL)

struct MUIP_PrefsEditor_Import { IPTR MethodID; CONST_STRPTR filename; };
struct MUIP_PrefsEditor_Export { IPTR MethodID; CONST_STRPTR filename; };
struct MUIP_PrefsEditor_ImportFH { IPTR MethodID; BPTR fh; };
struct MUIP_PrefsEditor_ExportFH { IPTR MethodID; BPTR fh; };

#define MUIA_PrefsEditor_Name     (MUIB_PrefsEditor | 0x00000000UL)   /* I-G CONST_STRPTR */
#define MUIA_PrefsEditor_Changed  (MUIB_PrefsEditor | 0x00000001UL)   /* -SG BOOL */
#define MUIA_PrefsEditor_Testing  (MUIB_PrefsEditor | 0x00000002UL)   /* -SG BOOL */
#define MUIA_PrefsEditor_Path     (MUIB_PrefsEditor | 0x00000003UL)   /* I-G CONST_STRPTR */
#define MUIA_PrefsEditor_CanSave  (MUIB_PrefsEditor | 0x00000004UL)   /* I-G BOOL */
#define MUIA_PrefsEditor_CanTest  (MUIB_PrefsEditor | 0x00000005UL)   /* I-G BOOL */
#define MUIA_PrefsEditor_IconTool (MUIB_PrefsEditor | 0x00000006UL)   /* I-G CONST_STRPTR */
#define MUIA_PrefsEditor_CanUse   (MUIB_PrefsEditor | 0x00000007UL)   /* I-G BOOL */

#define PrefsEditorObject MUIOBJMACRO_START(MUIC_PrefsEditor)

#endif
