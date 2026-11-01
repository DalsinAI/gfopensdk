#ifndef WORKBENCH_WORKBENCH_H
#define WORKBENCH_WORKBENCH_H
/*
 * OpenNDK: Workbench's icons (struct DiskObject), drawer data and the
 * application windows, icons and menu items of workbench.library.
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
#ifndef EXEC_TASKS_H
#include <exec/tasks.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif
#ifndef WORKBENCH_STARTUP_H
#include <workbench/startup.h>
#endif

#define WORKBENCH_NAME	"workbench.library"

/* DiskObject.do_Type: what an icon stands for */
#define WBDISK		1
#define WBDRAWER	2
#define WBTOOL		3
#define WBPROJECT	4
#define WBGARBAGE	5
#define WBDEVICE	6
#define WBKICK		7
#define WBAPPICON	8

/* A drawer's window as icons stored it before V36 */
struct OldDrawerData
{
    struct NewWindow dd_NewWindow;
    LONG dd_CurrentX;			/* the scroll position */
    LONG dd_CurrentY;
};

/* The size of an OldDrawerData in an icon file */
#define OLDDRAWERDATAFILESIZE	(sizeof(struct OldDrawerData))

/* A drawer's window as icons store it */
struct DrawerData
{
    struct NewWindow dd_NewWindow;
    LONG dd_CurrentX;
    LONG dd_CurrentY;
    ULONG dd_Flags;			/* DDFLAGS_ */
    UWORD dd_ViewModes;			/* DDVM_ */
};

/* The size of a DrawerData in an icon file */
#define DRAWERDATAFILESIZE	(sizeof(struct DrawerData))

/* dd_Flags: which files the drawer shows */
#define DDFLAGS_SHOWDEFAULT	0
#define DDFLAGS_SHOWICONS	1
#define DDFLAGS_SHOWALL		2

/* dd_ViewModes */
#define DDVM_BYDEFAULT		0
#define DDVM_BYICON		1
#define DDVM_BYNAME		2
#define DDVM_BYDATE		3
#define DDVM_BYSIZE		4
#define DDVM_BYTYPE		5

/* An icon */
struct DiskObject
{
    UWORD do_Magic;			/* WB_DISKMAGIC */
    UWORD do_Version;			/* WB_DISKVERSION */
    struct Gadget do_Gadget;		/* its images and box */
    UBYTE do_Type;			/* WBDISK and friends */
    STRPTR do_DefaultTool;
    STRPTR *do_ToolTypes;		/* NULL-ended */
    LONG do_CurrentX;
    LONG do_CurrentY;
    struct DrawerData *do_DrawerData;
    STRPTR do_ToolWindow;
    LONG do_StackSize;
};

#define WB_DISKMAGIC		0xE310
#define WB_DISKVERSION		1
#define WB_DISKREVISION		1
#define WB_DISKREVISIONMASK	255

/* What icon.library frees together with an icon */
struct FreeList
{
    WORD fl_NumFree;
    struct List fl_MemList;
};

/* do_Gadget.Flags: the second image is a backfill */
#define GFLG_GADGBACKFILL	0x0001
#define GADGBACKFILL		0x0001

/* do_CurrentX and do_CurrentY of an icon Workbench may place */
#define NO_ICON_POSITION	(0x80000000)

/* ---- Application windows, icons and menu items ---------------------- */

/* The message sent to an AppWindow, AppIcon or AppMenuItem's port */
struct AppMessage
{
    struct Message am_Message;
    UWORD am_Type;			/* AMTYPE_ */
    ULONG am_UserData;
    ULONG am_ID;
    LONG am_NumArgs;
    struct WBArg *am_ArgList;
    UWORD am_Version;			/* AM_VERSION */
    UWORD am_Class;			/* AMCLASSICON_ for an AppIcon */
    WORD am_MouseX;
    WORD am_MouseY;
    ULONG am_Seconds;
    ULONG am_Micros;
    ULONG am_Reserved[8];
};

#define AM_VERSION	1

/* am_Type */
#define AMTYPE_APPWINDOW	7
#define AMTYPE_APPICON		8
#define AMTYPE_APPMENUITEM	9
#define AMTYPE_APPWINDOWZONE	10	/* V44 */

/* am_Class of an AppIcon's message (V44) */
#define AMCLASSICON_Open		0
#define AMCLASSICON_Copy		1
#define AMCLASSICON_Rename		2
#define AMCLASSICON_Information		3
#define AMCLASSICON_Snapshot		4
#define AMCLASSICON_UnSnapshot		5
#define AMCLASSICON_LeaveOut		6
#define AMCLASSICON_PutAway		7
#define AMCLASSICON_Delete		8
#define AMCLASSICON_FormatDisk		9
#define AMCLASSICON_EmptyTrash		10

#define AMCLASSICON_Selected		11
#define AMCLASSICON_Unselected		12

/* Handles; their insides belong to workbench.library */
struct AppWindow
{
    APTR aw_PRIVATE;
};

struct AppWindowDropZone
{
    APTR awdz_PRIVATE;
};

struct AppIcon
{
    APTR ai_PRIVATE;
};

struct AppMenuItem
{
    APTR ami_PRIVATE;
};

/* ---- workbench.library's tags (V44) ---------------------------------- */

#define WBA_Dummy	(TAG_USER + 0xA000)

/* AddAppIconA() */
#define WBAPPICONA_SupportsOpen		(WBA_Dummy + 1)
#define WBAPPICONA_SupportsCopy		(WBA_Dummy + 2)
#define WBAPPICONA_SupportsRename	(WBA_Dummy + 3)
#define WBAPPICONA_SupportsInformation	(WBA_Dummy + 4)
#define WBAPPICONA_SupportsSnapshot	(WBA_Dummy + 5)
#define WBAPPICONA_SupportsUnSnapshot	(WBA_Dummy + 6)
#define WBAPPICONA_SupportsLeaveOut	(WBA_Dummy + 7)
#define WBAPPICONA_SupportsPutAway	(WBA_Dummy + 8)
#define WBAPPICONA_SupportsDelete	(WBA_Dummy + 9)
#define WBAPPICONA_SupportsFormatDisk	(WBA_Dummy + 10)
#define WBAPPICONA_SupportsEmptyTrash	(WBA_Dummy + 11)
#define WBAPPICONA_PropagatePosition	(WBA_Dummy + 12)
#define WBAPPICONA_RenderHook		(WBA_Dummy + 13)
#define WBAPPICONA_NotifySelectState	(WBA_Dummy + 14)

/* AddAppMenuItemA() */
#define WBAPPMENUA_CommandKeyString	(WBA_Dummy + 15)

/* OpenWorkbenchObjectA() */
#define WBOPENA_ArgLock			(WBA_Dummy + 16)
#define WBOPENA_ArgName			(WBA_Dummy + 17)

/* WorkbenchControlA() */
#define WBCTRLA_IsOpen			(WBA_Dummy + 18)
#define WBCTRLA_DuplicateSearchPath	(WBA_Dummy + 19)
#define WBCTRLA_FreeSearchPath		(WBA_Dummy + 20)
#define WBCTRLA_GetDefaultStackSize	(WBA_Dummy + 21)
#define WBCTRLA_SetDefaultStackSize	(WBA_Dummy + 22)
#define WBCTRLA_RedrawAppIcon		(WBA_Dummy + 23)
#define WBCTRLA_GetProgramList		(WBA_Dummy + 24)
#define WBCTRLA_FreeProgramList		(WBA_Dummy + 25)

/* AddAppWindowDropZoneA() */
#define WBDZA_Left			(WBA_Dummy + 26)
#define WBDZA_RelRight			(WBA_Dummy + 27)
#define WBDZA_Top			(WBA_Dummy + 28)
#define WBDZA_RelBottom			(WBA_Dummy + 29)
#define WBDZA_Width			(WBA_Dummy + 30)
#define WBDZA_RelWidth			(WBA_Dummy + 31)
#define WBDZA_Height			(WBA_Dummy + 32)
#define WBDZA_RelHeight			(WBA_Dummy + 33)
#define WBDZA_Box			(WBA_Dummy + 34)
#define WBDZA_Hook			(WBA_Dummy + 35)

/* What a drop zone's hook is told (V44) */
struct AppWindowDropZoneMsg
{
    struct RastPort *adzm_RastPort;	/* the window's */
    struct IBox adzm_DropZoneBox;
    ULONG adzm_ID;
    ULONG adzm_UserData;
    LONG adzm_Action;			/* ADZMACTION_ */
};

#define ADZMACTION_Enter	(0)
#define ADZMACTION_Leave	(1)

/* What an AppIcon's render hook is told (V44) */
struct AppIconRenderMsg
{
    struct RastPort *arm_RastPort;
    struct DiskObject *arm_Icon;
    STRPTR arm_Label;
    struct TagItem *arm_Tags;		/* for DrawIconStateA() */
    WORD arm_Left;
    WORD arm_Top;
    WORD arm_Width;
    WORD arm_Height;
    ULONG arm_State;			/* IDS_ */
};

/* Handles AddAppMenu() and friends return */
struct AppMenu
{
    APTR am_PRIVATE;
};

/* What the copy, delete, text-input and setup hooks of WorkbenchControl() get */
struct CopyBeginMsg
{
    ULONG cbm_Length;			/* of this message */
    LONG cbm_Action;			/* CPACTION_Begin */
    BPTR cbm_SourceDrawer;
    BPTR cbm_DestinationDrawer;
};

struct CopyDataMsg
{
    ULONG cdm_Length;
    LONG cdm_Action;			/* CPACTION_Copy */
    BPTR cdm_SourceLock;
    STRPTR cdm_SourceName;
    BPTR cdm_DestinationLock;
    STRPTR cdm_DestinationName;
    LONG cdm_DestinationX;		/* where the icon goes */
    LONG cdm_DestinationY;
};

struct CopyEndMsg
{
    ULONG cem_Length;
    LONG cem_Action;			/* CPACTION_End */
};

struct DeleteBeginMsg
{
    ULONG dbm_Length;
    LONG dbm_Action;			/* DLACTION_BeginDiscard and so on */
};

struct DeleteDataMsg
{
    ULONG ddm_Length;
    LONG ddm_Action;
    BPTR ddm_Lock;
    STRPTR ddm_Name;
};

struct DeleteEndMsg
{
    ULONG dem_Length;
    LONG dem_Action;
};

struct TextInputMsg
{
    ULONG tim_Length;
    LONG tim_Action;
    STRPTR tim_Prompt;			/* TIACTION_ in tim_Action */
};

struct SetupCleanupHookMsg
{
    ULONG schm_Length;
    LONG schm_State;			/* SCHMSTATE_ */
};

/* One icon, as a selection hook sees it */
struct IconSelectMsg
{
    ULONG ism_Length;
    BPTR ism_Drawer;
    STRPTR ism_Name;
    UWORD ism_Type;			/* WBDISK and so on */
    BOOL ism_Selected;
    struct TagItem *ism_Tags;
    struct Window *ism_DrawerWindow;
    struct Window *ism_ParentWindow;
    WORD ism_Left;
    WORD ism_Top;
    WORD ism_Width;
    WORD ism_Height;
};

/* More names from the 3.2 interface */
#define AMCLASSICON_EjectDisk	13
#define CPACTION_Begin		0
#define CPACTION_Copy		1
#define CPACTION_End		2
#define DDFLAGS_SHOWMASK	3
#define DDFLAGS_SORTASC		0x100
#define DDFLAGS_SORTDEFAULT	0
#define DDFLAGS_SORTDESC	0x200
#define DDFLAGS_SORTMASK	0x300
#define DLACTION_BeginDiscard	0
#define DLACTION_BeginEmptyTrash	1
#define DLACTION_DeleteContents	3
#define DLACTION_DeleteObject	4
#define DLACTION_End		5
#define ISMACTION_Ignore	2
#define ISMACTION_Select	1
#define ISMACTION_Stop		3
#define ISMACTION_Unselect	0
#define SCHMSTATE_Cleanup	1
#define SCHMSTATE_Setup		2
#define SCHMSTATE_TryCleanup	0
#define TIACTION_Execute	3
#define TIACTION_NewDrawer	2
#define TIACTION_RelabelVolume	1
#define TIACTION_Rename		0
#define UPDATEWB_ObjectAdded	1
#define UPDATEWB_ObjectRemoved	0
#define WBAPPICONA_SupportsEjectDisk	(WBA_Dummy + 158)
#define WBAPPMENUA_GetKey	(WBA_Dummy + 65)
#define WBAPPMENUA_GetTitleKey	(WBA_Dummy + 77)
#define WBAPPMENUA_UseKey	(WBA_Dummy + 66)
#define WBA_LAST_TAG		(WBA_Dummy + 160)
#define WBA_Reserved1		(WBA_Dummy + 40)
#define WBA_Reserved10		(WBA_Dummy + 55)
#define WBA_Reserved11		(WBA_Dummy + 56)
#define WBA_Reserved12		(WBA_Dummy + 57)
#define WBA_Reserved13		(WBA_Dummy + 58)
#define WBA_Reserved14		(WBA_Dummy + 59)
#define WBA_Reserved15		(WBA_Dummy + 60)
#define WBA_Reserved16		(WBA_Dummy + 61)
#define WBA_Reserved17		(WBA_Dummy + 62)
#define WBA_Reserved18		(WBA_Dummy + 63)
#define WBA_Reserved19		(WBA_Dummy + 64)
#define WBA_Reserved2		(WBA_Dummy + 41)
#define WBA_Reserved20		(WBA_Dummy + 67)
#define WBA_Reserved21		(WBA_Dummy + 68)
#define WBA_Reserved22		(WBA_Dummy + 80)
#define WBA_Reserved23		(WBA_Dummy + 81)
#define WBA_Reserved24		(WBA_Dummy + 82)
#define WBA_Reserved25		(WBA_Dummy + 83)
#define WBA_Reserved26		(WBA_Dummy + 84)
#define WBA_Reserved27		(WBA_Dummy + 85)
#define WBA_Reserved28		(WBA_Dummy + 100)
#define WBA_Reserved29		(WBA_Dummy + 101)
#define WBA_Reserved3		(WBA_Dummy + 46)
#define WBA_Reserved30		(WBA_Dummy + 102)
#define WBA_Reserved31		(WBA_Dummy + 103)
#define WBA_Reserved32		(WBA_Dummy + 104)
#define WBA_Reserved33		(WBA_Dummy + 105)
#define WBA_Reserved34		(WBA_Dummy + 108)
#define WBA_Reserved35		(WBA_Dummy + 109)
#define WBA_Reserved36		(WBA_Dummy + 112)
#define WBA_Reserved37		(WBA_Dummy + 113)
#define WBA_Reserved38		(WBA_Dummy + 114)
#define WBA_Reserved39		(WBA_Dummy + 115)
#define WBA_Reserved4		(WBA_Dummy + 49)
#define WBA_Reserved40		(WBA_Dummy + 118)
#define WBA_Reserved41		(WBA_Dummy + 119)
#define WBA_Reserved42		(WBA_Dummy + 120)
#define WBA_Reserved43		(WBA_Dummy + 121)
#define WBA_Reserved44		(WBA_Dummy + 122)
#define WBA_Reserved45		(WBA_Dummy + 123)
#define WBA_Reserved46		(WBA_Dummy + 124)
#define WBA_Reserved47		(WBA_Dummy + 125)
#define WBA_Reserved48		(WBA_Dummy + 126)
#define WBA_Reserved49		(WBA_Dummy + 127)
#define WBA_Reserved5		(WBA_Dummy + 50)
#define WBA_Reserved50		(WBA_Dummy + 128)
#define WBA_Reserved51		(WBA_Dummy + 129)
#define WBA_Reserved52		(WBA_Dummy + 130)
#define WBA_Reserved53		(WBA_Dummy + 131)
#define WBA_Reserved54		(WBA_Dummy + 132)
#define WBA_Reserved55		(WBA_Dummy + 133)
#define WBA_Reserved56		(WBA_Dummy + 134)
#define WBA_Reserved57		(WBA_Dummy + 135)
#define WBA_Reserved58		(WBA_Dummy + 136)
#define WBA_Reserved59		(WBA_Dummy + 137)
#define WBA_Reserved6		(WBA_Dummy + 51)
#define WBA_Reserved60		(WBA_Dummy + 138)
#define WBA_Reserved61		(WBA_Dummy + 139)
#define WBA_Reserved62		(WBA_Dummy + 140)
#define WBA_Reserved63		(WBA_Dummy + 141)
#define WBA_Reserved64		(WBA_Dummy + 142)
#define WBA_Reserved65		(WBA_Dummy + 143)
#define WBA_Reserved66		(WBA_Dummy + 144)
#define WBA_Reserved67		(WBA_Dummy + 145)
#define WBA_Reserved68		(WBA_Dummy + 146)
#define WBA_Reserved69		(WBA_Dummy + 147)
#define WBA_Reserved7		(WBA_Dummy + 52)
#define WBA_Reserved70		(WBA_Dummy + 148)
#define WBA_Reserved71		(WBA_Dummy + 149)
#define WBA_Reserved72		(WBA_Dummy + 150)
#define WBA_Reserved73		(WBA_Dummy + 151)
#define WBA_Reserved74		(WBA_Dummy + 152)
#define WBA_Reserved75		(WBA_Dummy + 153)
#define WBA_Reserved76		(WBA_Dummy + 154)
#define WBA_Reserved77		(WBA_Dummy + 155)
#define WBA_Reserved78		(WBA_Dummy + 156)
#define WBA_Reserved79		(WBA_Dummy + 157)
#define WBA_Reserved8		(WBA_Dummy + 53)
#define WBA_Reserved9		(WBA_Dummy + 54)
#define WBCTRLA_AddHiddenDeviceName	(WBA_Dummy + 44)
#define WBCTRLA_AddSetupCleanupHook	(WBA_Dummy + 78)
#define WBCTRLA_FreeHiddenDeviceList	(WBA_Dummy + 43)
#define WBCTRLA_FreeOpenDrawerList	(WBA_Dummy + 39)
#define WBCTRLA_FreeSelectedIconList	(WBA_Dummy + 37)
#define WBCTRLA_GetCopyHook	(WBA_Dummy + 69)
#define WBCTRLA_GetDeleteHook	(WBA_Dummy + 71)
#define WBCTRLA_GetDiskInfoHook	(WBA_Dummy + 159)
#define WBCTRLA_GetGlobalFlags	(WBA_Dummy + 131)
#define WBCTRLA_GetHiddenDeviceList	(WBA_Dummy + 42)
#define WBCTRLA_GetOpenDrawerList	(WBA_Dummy + 38)
#define WBCTRLA_GetSelectedIconList	(WBA_Dummy + 36)
#define WBCTRLA_GetTextInputHook	(WBA_Dummy + 73)
#define WBCTRLA_GetTypeRestartTime	(WBA_Dummy + 47)
#define WBCTRLA_RemSetupCleanupHook	(WBA_Dummy + 79)
#define WBCTRLA_RemoveHiddenDeviceName	(WBA_Dummy + 45)
#define WBCTRLA_SetCopyHook	(WBA_Dummy + 70)
#define WBCTRLA_SetDeleteHook	(WBA_Dummy + 72)
#define WBCTRLA_SetDiskInfoHook	(WBA_Dummy + 160)
#define WBCTRLA_SetGlobalFlags	(WBA_Dummy + 130)
#define WBCTRLA_SetTextInputHook	(WBA_Dummy + 74)
#define WBCTRLA_SetTypeRestartTime	(WBA_Dummy + 48)
#define WBF_BOUNDTEXTVIEW	128
#define WBF_DRAWERPOSFREE	0
#define WBF_DRAWERPOSHEAD	1
#define WBF_DRAWERPOSMASK	3
#define WBF_DRAWERPOSTAIL	2
#define WBF_OLDDATESFIRST	0x10000
#define WBOBJA_DrawerFlags	(WBA_Dummy + 116)
#define WBOBJA_DrawerModes	(WBA_Dummy + 117)
#define WBOBJA_DrawerPath	(WBA_Dummy + 98)
#define WBOBJA_DrawerPathSize	(WBA_Dummy + 99)
#define WBOBJA_FullPath		(WBA_Dummy + 95)
#define WBOBJA_FullPathSize	(WBA_Dummy + 96)
#define WBOBJA_Height		(WBA_Dummy + 90)
#define WBOBJA_IsFake		(WBA_Dummy + 92)
#define WBOBJA_IsLink		(WBA_Dummy + 97)
#define WBOBJA_Left		(WBA_Dummy + 87)
#define WBOBJA_Name		(WBA_Dummy + 93)
#define WBOBJA_NameSize		(WBA_Dummy + 94)
#define WBOBJA_State		(WBA_Dummy + 91)
#define WBOBJA_Top		(WBA_Dummy + 88)
#define WBOBJA_Type		(WBA_Dummy + 86)
#define WBOBJA_Width		(WBA_Dummy + 89)
#define WBOPENA_Show		(WBA_Dummy + 75)
#define WBOPENA_ViewBy		(WBA_Dummy + 76)
#define WBO_DRAWER		1
#define WBO_ICON		2
#define WBO_NONE		0

#endif /* WORKBENCH_WORKBENCH_H */
