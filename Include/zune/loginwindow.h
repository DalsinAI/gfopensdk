/* LoginWindow.mcc: a window asking for a user name, a password and a
 * login method, with OK and Cancel (or Shutdown and Reboot at boot).
 * Names and numbers as AROS's published interface.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_LOGINWINDOW_H
#define ZUNE_LOGINWINDOW_H

#include <libraries/mui.h>

#ifndef MUIB_RSVD
#define MUIB_RSVD (MUIB_MUI | 0x10400000UL)
#endif
#ifndef MUIB_AROS
#define MUIB_AROS (MUIB_RSVD | 0x00070000UL)
#endif

#define MUIC_LoginWindow "LoginWindow.mcc"
#define MUIB_LoginWindow (MUIB_AROS | 0x00000200UL)

/* for a subclass; by default OK returns LWA_RV_OK and Cancel Quit from NewInput */
#define MUIM_LoginWindow_OK     (MUIB_LoginWindow | 0x00000000UL)
#define MUIM_LoginWindow_Cancel (MUIB_LoginWindow | 0x00000001UL)

#define MUIA_LoginWindow_Title               (MUIB_LoginWindow | 0x00000005UL)   /* I.. CONST_STRPTR */
#define MUIA_LoginWindow_LoginLogo           (MUIB_LoginWindow | 0x00000006UL)   /* I.. Object * */
#define MUIA_LoginWindow_LogoFrame           (MUIB_LoginWindow | 0x00000007UL)   /* I.. BOOL */
#define MUIA_LoginWindow_DetailsFrame        (MUIB_LoginWindow | 0x00000008UL)   /* I.. BOOL */
#define MUIA_LoginWindow_UserName            (MUIB_LoginWindow | 0x00000009UL)   /* ISG STRPTR */
#define MUIA_LoginWindow_UserName_Status     (MUIB_LoginWindow | 0x0000000aUL)   /* I.. LWA_UNT_ */
#define LWA_UNT_Input    0
#define LWA_UNT_Read     1
#define LWA_UNT_Disabled 2
#define LWA_UNT_None     3
#define MUIA_LoginWindow_UserPass            (MUIB_LoginWindow | 0x0000000bUL)   /* ..G STRPTR */
#define MUIA_LoginWindow_UserPass_Disabled   (MUIB_LoginWindow | 0x0000000cUL)   /* I.. BOOL */
#define MUIA_LoginWindow_Method              (MUIB_LoginWindow | 0x0000000dUL)   /* I.G STRPTR[] in, LONG out */
#define MUIA_LoginWindow_Method_Status       (MUIB_LoginWindow | 0x0000000eUL)   /* I.. LWA_METH_ */
#define LWA_METH_Input    0
#define LWA_METH_Disabled 1
#define LWA_METH_None     2
#define MUIA_LoginWindow_LocalLogin_Disabled (MUIB_LoginWindow | 0x0000000fUL)   /* I.. BOOL */
#define MUIA_LoginWindow_Cancel_Disabled     (MUIB_LoginWindow | 0x00000010UL)   /* I.. BOOL */
#define MUIA_LoginWindow_Prompt              (MUIB_LoginWindow | 0x00000011UL)   /* I.. CONST_STRPTR */
#define MUIA_LoginWindow_SystemMode          (MUIB_LoginWindow | 0x00000012UL)   /* I.. BOOL */

#define LoginWindowObject MUIOBJMACRO_START(MUIC_LoginWindow)

#define LWA_RV_CANCEL   MUIV_Application_ReturnID_Quit
#define LWA_RV_OK       1
#define LWA_RV_SHUTDOWN 2
#define LWA_RV_REBOOT   3
#define LWRV_CANCEL     MUIV_Application_ReturnID_Quit
#define LWRV_OK         LWA_RV_OK

#endif
