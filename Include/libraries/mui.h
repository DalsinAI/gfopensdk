/* libraries/mui.h: GFOpenMUI's interface, MUI's names and values.
 *
 * GFOpenMUI is muimaster.library 19.x over GFOpenLayout's UI, written
 * clean-room by the AmiCradle Team. The names and numbers below are MUI's
 * published interface (so MUI programs build against this header and run
 * unchanged); the header itself is ours. Step 1 has what Calculator and
 * the core classes use: Notify, Application, Window, Area, Group,
 * Rectangle and Text. Later steps add the rest.
 *
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef LIBRARIES_MUI_H
#define LIBRARIES_MUI_H

#ifdef GFOPENMUI_HOST
#include "host_amiga.h"
#else
#include <exec/types.h>
#include <utility/tagitem.h>
#include <utility/hooks.h>
#include <intuition/classes.h>
#include <intuition/classusr.h>
#include <intuition/intuition.h>
#include <libraries/gadtools.h>
#ifndef IPTR
#define IPTR ULONG
#endif
#endif

#ifndef MAKE_ID
#define MAKE_ID(a, b, c, d) ((ULONG)(a) << 24 | (ULONG)(b) << 16 | (ULONG)(c) << 8 | (ULONG)(d))
#endif

/* A class's dispatcher as MUI programs write it: its class, object and
 * message in A0, A2 and A1, as a hook's entry (AROS's names too) */
#ifndef BOOPSI_DISPATCHER
#ifdef GFOPENMUI_HOST
#define BOOPSI_DISPATCHER(rettype, name, cl, obj, msg) \
    static rettype name##_body(Class *cl, Object *obj, Msg msg); \
    IPTR name(struct Hook *h_, APTR o_, APTR m_) { return (IPTR)name##_body((Class *)h_, (Object *)o_, (Msg)m_); } \
    static rettype name##_body(Class *cl, Object *obj, Msg msg) {
#define BOOPSI_DISPATCHER_PROTO(rettype, name, cl, obj, msg) IPTR name(struct Hook *, APTR, APTR)
#else
#define BOOPSI_DISPATCHER(rettype, name, cl, obj, msg) \
    rettype name(register Class *cl __asm("a0"), register Object *obj __asm("a2"), register Msg msg __asm("a1")); \
    rettype name(register Class *cl __asm("a0"), register Object *obj __asm("a2"), register Msg msg __asm("a1")) {
#define BOOPSI_DISPATCHER_PROTO(rettype, name, cl, obj, msg) \
    rettype name(register Class *cl __asm("a0"), register Object *obj __asm("a2"), register Msg msg __asm("a1"))
#endif
#define BOOPSI_DISPATCHER_END }
#endif

#define MUIMASTER_NAME "muimaster.library"
#define MUIMASTER_VMIN 11
#define MUIMASTER_VLATEST 19

#ifndef MUIB_MUI
#define MUIB_MUI TAG_USER
#endif

/* ---- The classes, by name (MUI_NewObject's first argument) ---- */
#define MUIC_Notify "Notify.mui"
#define MUIC_Family "Family.mui"
#define MUIC_Application "Application.mui"
#define MUIC_Window "Window.mui"
#define MUIC_Area "Area.mui"
#define MUIC_Group "Group.mui"
#define MUIC_Rectangle "Rectangle.mui"
#define MUIC_Text "Text.mui"
#define MUIC_String "String.mui"
#define MUIC_Menustrip "Menustrip.mui"
#define MUIC_Menu "Menu.mui"
#define MUIC_Menuitem "Menuitem.mui"

/* ---- Methods ---- */
#define MUIM_Application_Input 0x8042d0f5UL
#define MUIM_Application_NewInput 0x80423ba6UL
#define MUIM_Application_PushMethod 0x80429ef8UL
#define MUIM_Application_ReturnID 0x804276efUL
#define MUIM_AskMinMax 0x80423874UL
#define MUIM_CallHook 0x8042b96bUL
#define MUIM_Cleanup 0x8042d985UL
#define MUIM_Draw 0x80426f3fUL
#define MUIM_Group_ExitChange 0x8042d1ccUL
#define MUIM_Group_InitChange 0x80420887UL
#define MUIM_HandleEvent 0x80426d66UL
#define MUIM_HandleInput 0x80422a1aUL
#define MUIM_Hide 0x8042f20fUL
#define MUIM_KillNotify 0x8042d240UL
#define MUIM_NoNotifySet 0x8042216fUL
#define MUIM_Notify 0x8042c9cbUL
#define MUIM_Set 0x8042549aUL
#define MUIM_SetAsString 0x80422590UL
#define MUIM_Setup 0x80428354UL
#define MUIM_Show 0x8042cc84UL

/* ---- Attributes ---- */
#define MUIA_ApplicationObject 0x8042d3eeUL
#define MUIA_Application_Active 0x804260abUL
#define MUIA_Application_Author 0x80424842UL
#define MUIA_Application_Base 0x8042e07aUL
#define MUIA_Application_Copyright 0x8042ef4dUL
#define MUIA_Application_Description 0x80421fc6UL
#define MUIA_Application_Iconified 0x8042a07fUL
#define MUIA_Application_DiskObject 0x804235cbUL
#define MUIA_Application_Broker 0x8042dbceUL
#define MUIA_Application_BrokerHook 0x80428f4bUL
#define MUIA_Application_BrokerPri 0x8042c8d0UL
#define MUIA_Application_BrokerPort 0x8042e0adUL
#define MUIA_Application_SingleTask 0x8042a2c8UL
#define MUIA_Application_DoubleStart 0x80423bc6UL
#define MUIA_Application_Menustrip 0x804252d9UL
#define MUIA_Window_MenuAction 0x80427521UL
#define MUIA_String_Contents 0x80428ffdUL
#define MUIA_String_MaxLen 0x80424984UL
#define MUIA_String_Acknowledge 0x8042026cUL
#define MUIA_String_Accept 0x8042e3e1UL
#define MUIA_String_Reject 0x8042179cUL
#define MUIA_String_BufferPos 0x80428b6cUL
#define MUIA_Menustrip_Enabled 0x8042815bUL
#define MUIA_Menu_Title 0x8042a0e3UL
#define MUIA_Menu_Enabled 0x8042ed48UL
#define MUIA_Menuitem_Title 0x804218beUL
#define MUIA_Menuitem_Shortcut 0x80422030UL
#define MUIA_Menuitem_Enabled 0x8042ae0fUL
#define MUIA_Menuitem_Trigger 0x80426f32UL
#define MUIA_Menuitem_Checked 0x8042562aUL
#define MUIA_Menuitem_Checkit 0x80425aceUL
#define MUIA_Menuitem_Toggle 0x80424d5cUL
#define MUIV_Menuitem_Shortcut_Check (-1)
#define MUIA_Application_Sleep 0x80425711UL
#define MUIA_Application_Title 0x804281b8UL
#define MUIA_Application_Version 0x8042b33fUL
#define MUIA_Application_Window 0x8042bfe0UL
#define MUIA_Application_WindowList 0x80429abeUL
#define MUIA_Background 0x8042545bUL
#define MUIA_ControlChar 0x8042120bUL
#define MUIA_CycleChain 0x80421ce7UL
#define MUIA_Disabled 0x80423661UL
#define MUIA_FixHeight 0x8042a92bUL
#define MUIA_FixHeightTxt 0x804276f2UL
#define MUIA_FixWidth 0x8042a3f1UL
#define MUIA_FixWidthTxt 0x8042d044UL
#define MUIA_Font 0x8042be50UL
#define MUIA_Frame 0x8042ac64UL
#define MUIA_FrameTitle 0x8042d1c7UL
#define MUIA_Group_ActivePage 0x80424199UL
#define MUIA_Group_Child 0x804226e6UL
#define MUIA_Group_ChildList 0x80424748UL
#define MUIA_Group_Columns 0x8042f416UL
#define MUIA_Group_Horiz 0x8042536bUL
#define MUIA_Group_HorizSpacing 0x8042c651UL
#define MUIA_Group_PageMode 0x80421a5fUL
#define MUIA_Group_Rows 0x8042b68fUL
#define MUIA_Group_SameHeight 0x8042037eUL
#define MUIA_Group_SameSize 0x80420860UL
#define MUIA_Group_SameWidth 0x8042b3ecUL
#define MUIA_Group_Spacing 0x8042866dUL
#define MUIA_Group_VertSpacing 0x8042e1bfUL
#define MUIA_HelpNode 0x80420b85UL
#define MUIA_HorizWeight 0x80426db9UL
#define MUIA_InnerBottom 0x8042f2c0UL
#define MUIA_InnerLeft 0x804228f8UL
#define MUIA_InnerRight 0x804297ffUL
#define MUIA_InnerTop 0x80421eb6UL
#define MUIA_InputMode 0x8042fb04UL
#define MUIA_NoNotify 0x804237f9UL
#define MUIA_Parent 0x8042e35fUL
#define MUIA_Pressed 0x80423535UL
#define MUIA_Rectangle_BarTitle 0x80426689UL
#define MUIA_Rectangle_HBar 0x8042c943UL
#define MUIA_Rectangle_VBar 0x80422204UL
#define MUIA_Revision 0x80427eaaUL
#define MUIA_Selected 0x8042654bUL
#define MUIA_ShortHelp 0x80428fe3UL
#define MUIA_ShowMe 0x80429ba8UL
#define MUIA_Text_Contents 0x8042f8dcUL
#define MUIA_Text_HiChar 0x804218ffUL
#define MUIA_Text_HiCharIdx 0x804214f5UL
#define MUIA_Text_PreParse 0x8042566dUL
#define MUIA_Text_SetMax 0x80424d0aUL
#define MUIA_Text_SetMin 0x80424e10UL
#define MUIA_Text_SetVMax 0x80420d8bUL
#define MUIA_UserData 0x80420313UL
#define MUIA_Version 0x80422301UL
#define MUIA_VertWeight 0x804298d0UL
#define MUIA_Weight 0x80421d1fUL
#define MUIA_WindowObject 0x8042669eUL
#define MUIA_Window_Activate 0x80428d2fUL
#define MUIA_Window_ActiveObject 0x80427925UL
#define MUIA_Window_AppWindow 0x804280cfUL
#define MUIA_Window_CloseRequest 0x8042e86eUL
#define MUIA_Window_DefaultObject 0x804294d7UL
#define MUIA_Window_Height 0x80425846UL
#define MUIA_Window_ID 0x804201bdUL
#define MUIA_Window_LeftEdge 0x80426c65UL
#define MUIA_Window_Menustrip 0x8042855eUL
#define MUIA_Window_NoMenus 0x80429df5UL
#define MUIA_Window_Open 0x80428aa0UL
#define MUIA_Window_PublicScreen 0x804278e4UL
#define MUIA_Window_RootObject 0x8042cba5UL
#define MUIA_Window_Screen 0x8042df4fUL
#define MUIA_Window_ScreenTitle 0x804234b0UL
#define MUIA_Window_Title 0x8042ad3dUL
#define MUIA_Window_TopEdge 0x80427c66UL
#define MUIA_Window_Width 0x8042dcaeUL
#define MUIA_Window_Window 0x80426a42UL

/* ---- Special values ---- */
#define MUIV_Application_ReturnID_Quit (-1)
#define MUIV_EveryTime 0x49893131UL
#define MUIV_Frame_Button 1UL
#define MUIV_Frame_Count 24UL
#define MUIV_Frame_Drag 14UL
#define MUIV_Frame_Gauge 8UL
#define MUIV_Frame_Group 9UL
#define MUIV_Frame_ImageButton 2UL
#define MUIV_Frame_InputList 6UL
#define MUIV_Frame_Knob 13UL
#define MUIV_Frame_None 0UL
#define MUIV_Frame_PopUp 10UL
#define MUIV_Frame_Prop 7UL
#define MUIV_Frame_ReadList 5UL
#define MUIV_Frame_Register 21UL
#define MUIV_Frame_Slider 12UL
#define MUIV_Frame_String 4UL
#define MUIV_Frame_Text 3UL
#define MUIV_Frame_Virtual 11UL
#define MUIV_NotTriggerValue 0x49893133UL
#define MUIV_TriggerValue 0x49893131UL
#define MUIV_Window_ActiveObject_Next (-1)
#define MUIV_Window_ActiveObject_None (0)
#define MUIV_Window_ActiveObject_Prev (-2)
#define MUIV_Window_AltHeight_Scaled (-1000)
#define MUIV_Window_AltLeftEdge_Centered (-1)
#define MUIV_Window_AltLeftEdge_Moused (-2)
#define MUIV_Window_AltLeftEdge_NoChange (-1000)
#define MUIV_Window_AltTopEdge_Centered (-1)
#define MUIV_Window_AltTopEdge_Moused (-2)
#define MUIV_Window_AltTopEdge_NoChange (-1000)
#define MUIV_Window_AltWidth_Scaled (-1000)
#define MUIV_Window_Button_Iconify (4)
#define MUIV_Window_Button_MUI (1)
#define MUIV_Window_Button_Popup (8)
#define MUIV_Window_Button_Snapshot (2)
#define MUIV_Window_Height_Default (-1001)
#define MUIV_Window_Height_Scaled (-1000)
#define MUIV_Window_LeftEdge_Centered (-1)
#define MUIV_Window_LeftEdge_Moused (-2)
#define MUIV_Window_Menu_NoMenu (-1)
#define MUIV_Window_TopEdge_Centered (-1)
#define MUIV_Window_TopEdge_Moused (-2)
#define MUIV_Window_Width_Default (-1001)
#define MUIV_Window_Width_Scaled (-1000)

#define MUIV_Notify_Self 1
#define MUIV_Notify_Window 2
#define MUIV_Notify_Application 3
#define MUIV_Notify_Parent 4

#define MUIV_InputMode_None 0
#define MUIV_InputMode_RelVerify 1
#define MUIV_InputMode_Immediate 2
#define MUIV_InputMode_Toggle 3

#define MUIV_Font_Inherit ((IPTR)0)
#define MUIV_Font_Normal ((IPTR)-1)
#define MUIV_Font_List ((IPTR)-2)
#define MUIV_Font_Tiny ((IPTR)-3)
#define MUIV_Font_Fixed ((IPTR)-4)
#define MUIV_Font_Title ((IPTR)-5)
#define MUIV_Font_Big ((IPTR)-6)
#define MUIV_Font_Button ((IPTR)-7)

/* MUI_MakeObject's kinds */
#define MUIO_Label 1
#define MUIO_Button 2
#define MUIO_Checkmark 3
#define MUIO_Cycle 4
#define MUIO_Radio 5
#define MUIO_Slider 6
#define MUIO_String 7
#define MUIO_PopButton 8
#define MUIO_HSpace 9
#define MUIO_VSpace 10
#define MUIO_HBar 11
#define MUIO_VBar 12
#define MUIO_MenustripNM 13
#define MUIO_Menuitem 14
#define MUIO_BarTitle 15
#define MUIO_MenustripNM_CommandKeyCheck (1 << 0)

/* MUI's standard images and backgrounds (MUIA_Background, MUIA_Image_Spec) */
#define MUII_WindowBack 0UL
#define MUII_RequesterBack 1UL
#define MUII_ButtonBack 2UL
#define MUII_ListBack 3UL
#define MUII_TextBack 4UL
#define MUII_PropBack 5UL
#define MUII_PopupBack 6UL
#define MUII_SelectedBack 7UL
#define MUII_ListCursor 8UL
#define MUII_ListSelect 9UL
#define MUII_ListSelCur 10UL
#define MUII_ArrowUp 11UL
#define MUII_ArrowDown 12UL
#define MUII_ArrowLeft 13UL
#define MUII_ArrowRight 14UL
#define MUII_CheckMark 15UL
#define MUII_RadioButton 16UL
#define MUII_Cycle 17UL
#define MUII_PopUp 18UL
#define MUII_PopFile 19UL
#define MUII_PopDrawer 20UL
#define MUII_PropKnob 21UL
#define MUII_Drawer 22UL
#define MUII_HardDisk 23UL
#define MUII_Disk 24UL
#define MUII_Chip 25UL
#define MUII_Volume 26UL
#define MUII_RegisterBack 27UL
#define MUII_Network 28UL
#define MUII_Assign 29UL
#define MUII_TapePlay 30UL
#define MUII_TapePlayBack 31UL
#define MUII_TapePause 32UL
#define MUII_TapeStop 33UL
#define MUII_TapeRecord 34UL
#define MUII_GroupBack 35UL
#define MUII_SliderBack 36UL
#define MUII_SliderKnob 37UL
#define MUII_TapeUp 38UL
#define MUII_TapeDown 39UL
#define MUII_PageBack 40UL
#define MUII_ReadListBack 41UL
#define MUII_Count 42UL
#define MUII_BACKGROUND 128UL
#define MUII_SHADOW 129UL
#define MUII_SHINE 130UL
#define MUII_FILL 131UL
#define MUII_SHADOWBACK 132UL
#define MUII_SHADOWFILL 133UL
#define MUII_SHADOWSHINE 134UL
#define MUII_FILLBACK 135UL
#define MUII_FILLSHINE 136UL
#define MUII_SHINEBACK 137UL
#define MUII_HSHINEBACK 139UL
#define MUII_HSHADOWBACK 140UL
#define MUII_HSHINESHINE 141UL
#define MUII_HSHADOWSHADOW 142UL
#define MUII_MARKSHINE 143UL
#define MUII_MARKHALFSHINE 144UL
#define MUII_MARKBACKGROUND 145UL
#define MUII_LASTPAT 146UL

/* Text's escape sequences */
#define MUIX_R "\033r"
#define MUIX_C "\033c"
#define MUIX_L "\033l"
#define MUIX_N "\033n"
#define MUIX_B "\033b"
#define MUIX_I "\033i"
#define MUIX_U "\033u"
#define MUIX_PT "\0332"
#define MUIX_PH "\0338"

/* ---- Messages (every field a stacked long, as MUI's) ---- */
struct MUIP_Notify {
    IPTR MethodID;
    IPTR TrigAttr;
    IPTR TrigVal;
    APTR DestObj;
    IPTR FollowParams;
    /* followed by the method and its arguments */
};
struct MUIP_Set {
    IPTR MethodID;
    IPTR Attr;
    IPTR Val;
};
struct MUIP_CallHook {
    IPTR MethodID;
    struct Hook *Hook;
    IPTR param1;            /* and the rest */
};
struct MUIP_Application_NewInput {
    IPTR MethodID;
    ULONG *signal;
};
struct MUIP_Application_ReturnID {
    IPTR MethodID;
    IPTR retid;
};
/* Setup, Cleanup and HandleInput: a custom class's own input (MUI_RequestIDCMP) */
struct MUIP_Setup {
    IPTR MethodID;
    struct MUI_RenderInfo *RenderInfo;
};
struct MUIP_HandleInput {
    IPTR MethodID;
    struct IntuiMessage *imsg;
    LONG muikey;
};

/* A custom class (MUI_CreateCustomClass) */
struct MUI_CustomClass {
    APTR mcc_UserData;
    struct Library *mcc_UtilityBase;
    struct Library *mcc_DOSBase;
    struct Library *mcc_GfxBase;
    struct Library *mcc_IntuitionBase;
    struct IClass *mcc_Super;
    struct IClass *mcc_Class;
    /* private after here */
};

/* ---- The other classes: lists, choices, numbers, pages, scrolling, pop-ups ---- */
#define MUIC_List "List.mui"
#define MUIC_Floattext "Floattext.mui"
#define MUIC_Volumelist "Volumelist.mui"
#define MUIC_Dirlist "Dirlist.mui"
#define MUIC_Listview "Listview.mui"
#define MUIC_Cycle "Cycle.mui"
#define MUIC_Radio "Radio.mui"
#define MUIC_Numeric "Numeric.mui"
#define MUIC_Knob "Knob.mui"
#define MUIC_Levelmeter "Levelmeter.mui"
#define MUIC_Numericbutton "Numericbutton.mui"
#define MUIC_Slider "Slider.mui"
#define MUIC_Prop "Prop.mui"
#define MUIC_Scrollbar "Scrollbar.mui"
#define MUIC_Scrollbutton "Scrollbutton.mui"
#define MUIC_Gauge "Gauge.mui"
#define MUIC_Scale "Scale.mui"
#define MUIC_Register "Register.mui"
#define MUIC_Virtgroup "Virtgroup.mui"
#define MUIC_Scrollgroup "Scrollgroup.mui"
#define MUIC_Balance "Balance.mui"
#define MUIC_Image "Image.mui"
#define MUIC_Bitmap "Bitmap.mui"
#define MUIC_Bodychunk "Bodychunk.mui"
#define MUIC_Popstring "Popstring.mui"
#define MUIC_Popobject "Popobject.mui"
#define MUIC_Poplist "Poplist.mui"
#define MUIC_Popasl "Popasl.mui"
#define MUIC_Popscreen "Popscreen.mui"
#define MUIC_Colorfield "Colorfield.mui"
#define MUIC_Coloradjust "Coloradjust.mui"
#define MUIC_Pendisplay "Pendisplay.mui"
#define MUIC_Penadjust "Penadjust.mui"
#define MUIC_Poppen "Poppen.mui"
#define MUIC_Palette "Palette.mui"
#define MUIC_Imagedisplay "Imagedisplay.mui"
#define MUIC_Imageadjust "Imageadjust.mui"
#define MUIC_Framedisplay "Framedisplay.mui"
#define MUIC_Frameadjust "Frameadjust.mui"
#define MUIC_Popimage "Popimage.mui"
#define MUIC_Popframe "Popframe.mui"
#define MUIC_Pixmap "Pixmap.mui"
#define MUIC_Dtpic "Dtpic.mui"
#define MUIC_Boopsi "Boopsi.mui"
/* Zune's: a picture of 8 bit pixels, the scrolling corner button, a Register's titles, an MCC's prefs group */
#define MUIC_ChunkyImage "ChunkyImage.mui"
#define MUIC_Title "Title.mui"
#define MUIC_Mccprefs "Mccprefs.mui"
#define MUIC_Semaphore "Semaphore.mui"
#define MUIC_Dataspace "Dataspace.mui"
#define MUIC_Process "Process.mui"
#define MUIC_Settingsgroup "Settingsgroup.mui"
#define MUIC_Settings "Settings.mui"
#define MUIC_Configdata "Configdata.mui"
#define MUIC_Aboutmui "Aboutmui.mui"
#define MUIC_Crawling "Crawling.mcc"
#define MUIC_BetterString "BetterString.mcc"
#define MUIC_NList "NList.mcc"
#define MUIC_NListview "NListview.mcc"
#define MUIC_NListtree "NListtree.mcc"
#define MUIC_TextEditor "TextEditor.mcc"
#define MUIC_Listtree "Listtree.mcc"

#define MUIM_List_Clear 0x8042ad89UL
#define MUIM_List_CreateImage 0x80429804UL
#define MUIM_List_DeleteImage 0x80420f58UL
#define MUIM_List_Exchange 0x8042468cUL
#define MUIM_List_GetEntry 0x804280ecUL
#define MUIM_List_Insert 0x80426c87UL
#define MUIM_List_InsertSingle 0x804254d5UL
#define MUIM_List_Jump 0x8042baabUL
#define MUIM_List_Move 0x804253c2UL
#define MUIM_List_NextSelected 0x80425f17UL
#define MUIM_List_Redraw 0x80427993UL
#define MUIM_List_Remove 0x8042647eUL
#define MUIM_List_Select 0x804252d8UL
#define MUIM_List_Sort 0x80422275UL
#define MUIM_List_TestPos 0x80425f48UL
#define MUIM_Numeric_Decrease 0x804243a7UL
#define MUIM_Numeric_Increase 0x80426ecdUL
#define MUIM_Numeric_ScaleToValue 0x8042032cUL
#define MUIM_Numeric_SetDefault 0x8042ab0aUL
#define MUIM_Numeric_Stringify 0x80424891UL
#define MUIM_Numeric_ValueToScale 0x80423e4fUL
#define MUIM_Popstring_Close 0x8042dc52UL
#define MUIM_Popstring_Open 0x804258baUL

#define MUIA_List_Active 0x8042391cUL
#define MUIA_List_AdjustHeight 0x8042850dUL
#define MUIA_List_AdjustWidth 0x8042354aUL
#define MUIA_List_AutoVisible 0x8042a445UL
#define MUIA_List_CompareHook 0x80425c14UL
#define MUIA_List_ConstructHook 0x8042894fUL
#define MUIA_List_DestructHook 0x804297ceUL
#define MUIA_List_DisplayHook 0x8042b4d5UL
#define MUIA_List_DragSortable 0x80426099UL
#define MUIA_List_DropMark 0x8042aba6UL
#define MUIA_List_Entries 0x80421654UL
#define MUIA_List_First 0x804238d4UL
#define MUIA_List_Format 0x80423c0aUL
#define MUIA_List_InsertPosition 0x8042d0cdUL
#define MUIA_List_MinLineHeight 0x8042d1c3UL
#define MUIA_List_MultiTestHook 0x8042c2c6UL
#define MUIA_List_Pool 0x80423431UL
#define MUIA_List_PoolPuddleSize 0x8042a4ebUL
#define MUIA_List_PoolThreshSize 0x8042c48cUL
#define MUIA_List_Quiet 0x8042d8c7UL
#define MUIA_List_ShowDropMarks 0x8042c6f3UL
#define MUIA_List_SourceArray 0x8042c0a0UL
#define MUIA_List_Title 0x80423e66UL
#define MUIA_List_Visible 0x8042191fUL
#define MUIA_Listview_ClickColumn 0x8042d1b3UL
#define MUIA_Listview_DefClickColumn 0x8042b296UL
#define MUIA_Listview_DoubleClick 0x80424635UL
#define MUIA_Listview_DragType 0x80425cd3UL
#define MUIA_Listview_Input 0x8042682dUL
#define MUIA_Listview_List 0x8042bcceUL
#define MUIA_Listview_MultiSelect 0x80427e08UL
#define MUIA_Listview_ScrollerPos 0x8042b1b4UL
#define MUIA_Listview_SelectChange 0x8042178fUL
#define MUIA_Floattext_Justify 0x8042dc03UL
#define MUIA_Floattext_SkipChars 0x80425c7dUL
#define MUIA_Floattext_TabSize 0x80427d17UL
#define MUIA_Floattext_Text 0x8042d16aUL
#define MUIM_Floattext_Append 0x8042a221UL
#define MUIA_Dirlist_AcceptPattern 0x8042760aUL
#define MUIA_Dirlist_Directory 0x8042ea41UL
#define MUIA_Dirlist_DrawersOnly 0x8042b379UL
#define MUIA_Dirlist_FilesOnly 0x8042896aUL
#define MUIA_Dirlist_FilterDrawers 0x80424ad2UL
#define MUIA_Dirlist_FilterHook 0x8042ae19UL
#define MUIA_Dirlist_MultiSelDirs 0x80428653UL
#define MUIA_Dirlist_NumBytes 0x80429e26UL
#define MUIA_Dirlist_NumDrawers 0x80429cb8UL
#define MUIA_Dirlist_NumFiles 0x8042a6f0UL
#define MUIA_Dirlist_Path 0x80426176UL
#define MUIA_Dirlist_RejectIcons 0x80424808UL
#define MUIA_Dirlist_RejectPattern 0x804259c7UL
#define MUIA_Dirlist_SortDirs 0x8042bbb9UL
#define MUIA_Dirlist_SortHighLow 0x80421896UL
#define MUIA_Dirlist_SortType 0x804228bcUL
#define MUIA_Dirlist_Status 0x804240deUL
#define MUIM_Dirlist_ReRead 0x80422d71UL
#define MUIV_Dirlist_SortDirs_First 0
#define MUIV_Dirlist_SortDirs_Last 1
#define MUIV_Dirlist_SortDirs_Mix 2
#define MUIV_Dirlist_SortType_Name 0
#define MUIV_Dirlist_SortType_Date 1
#define MUIV_Dirlist_SortType_Size 2
#define MUIV_Dirlist_Status_Invalid 0
#define MUIV_Dirlist_Status_Reading 1
#define MUIV_Dirlist_Status_Valid 2
#define MUIA_Cycle_Active 0x80421788UL
#define MUIA_Cycle_Entries 0x80420629UL
#define MUIA_Radio_Active 0x80429b41UL
#define MUIA_Radio_Entries 0x8042b6a1UL
#define MUIA_Numeric_Default 0x804263e8UL
#define MUIA_Numeric_Format 0x804263e9UL
#define MUIA_Numeric_Max 0x8042d78aUL
#define MUIA_Numeric_Min 0x8042e404UL
#define MUIA_Numeric_Reverse 0x8042f2a0UL
#define MUIA_Numeric_RevLeftRight 0x804294a7UL
#define MUIA_Numeric_RevUpDown 0x804252ddUL
#define MUIA_Numeric_Value 0x8042ae3aUL
#define MUIA_Slider_Horiz 0x8042fad1UL
#define MUIA_Slider_Quiet 0x80420b26UL
#define MUIA_Prop_Entries 0x8042fbdbUL
#define MUIA_Prop_First 0x8042d4b2UL
#define MUIA_Prop_Horiz 0x8042f4f3UL
#define MUIA_Prop_Slider 0x80429c3aUL
#define MUIA_Prop_UseWinBorder 0x8042deeeUL
#define MUIA_Prop_Visible 0x8042fea6UL
#define MUIA_Scrollbar_Type 0x8042fb6bUL
#define MUIA_Gauge_Current 0x8042f0ddUL
#define MUIA_Gauge_Divide 0x8042d8dfUL
#define MUIA_Gauge_Horiz 0x804232ddUL
#define MUIA_Gauge_InfoText 0x8042bf15UL
#define MUIA_Gauge_Max 0x8042bcdbUL
#define MUIA_Levelmeter_Label 0x80420dd5UL
#define MUIA_Colorfield_Blue 0x8042d3b0UL
#define MUIA_Colorfield_Green 0x80424466UL
#define MUIA_Colorfield_Pen 0x8042713aUL
#define MUIA_Colorfield_Red 0x804279f6UL
#define MUIA_Colorfield_RGB 0x8042677aUL
#define MUIA_Coloradjust_Blue 0x8042b8a3UL
#define MUIA_Coloradjust_Green 0x804285abUL
#define MUIA_Coloradjust_ModeID 0x8042ec59UL
#define MUIA_Coloradjust_Red 0x80420eaaUL
#define MUIA_Coloradjust_RGB 0x8042f899UL
#define MUIA_Pendisplay_Pen 0x8042a748UL
#define MUIA_Pendisplay_Reference 0x8042dc24UL
#define MUIA_Pendisplay_RGBcolor 0x8042a1a9UL
#define MUIA_Pendisplay_Spec 0x8042a204UL
#define MUIA_Penadjust_PSIMode 0x80421cbbUL
#define MUIA_Palette_Entries 0x8042a3d8UL
#define MUIA_Palette_Groupable 0x80423e67UL
#define MUIA_Palette_Names 0x8042c3a2UL
#define MUIV_Palette_Entry_End ((LONG)-1)
#define MUIA_Framedisplay_Spec 0x80421794UL
#define MUIA_Imageadjust_Spec 0x804279e1UL
#define MUIA_Imageadjust_Type 0x80422f2bUL
#define MUIA_Imagedisplay_Spec 0x8042a547UL
#define MUIA_Imagedisplay_UseDefSize 0x8042186dUL
/* Boopsi: a BOOPSI gadget (colorwheel, gradientslider ...) in a MUI window */
#define MUIA_Boopsi_Class 0x80426999UL
#define MUIA_Boopsi_ClassID 0x8042bfa3UL
#define MUIA_Boopsi_MaxHeight 0x8042757fUL
#define MUIA_Boopsi_MaxWidth 0x8042bcb1UL
#define MUIA_Boopsi_MinHeight 0x80422c93UL
#define MUIA_Boopsi_MinWidth 0x80428fb2UL
#define MUIA_Boopsi_Object 0x80420178UL
#define MUIA_Boopsi_Remember 0x8042f4bdUL
#define MUIA_Boopsi_Smart 0x8042b8d7UL
#define MUIA_Boopsi_TagDrawInfo 0x8042bae7UL
#define MUIA_Boopsi_TagScreen 0x8042bc71UL
#define MUIA_Boopsi_TagWindow 0x8042e11dUL
/* Zune's ChunkyImage and Scrollbutton (MUIB_ZUNE 0x90420000) */
#define MUIA_ChunkyImage_Pixels 0x90424000UL
#define MUIA_ChunkyImage_Palette 0x90424001UL
#define MUIA_ChunkyImage_NumColors 0x90424002UL
#define MUIA_ChunkyImage_Modulo 0x90424003UL
#define MUIA_Scrollbutton_NewPosition 0x90424100UL
#define MUIA_Scrollbutton_Horiz 0x90424101UL
#define MUIA_Scrollbutton_Vert 0x90424102UL
#define MUIA_Scrollbutton_HorizProp 0x90424103UL
#define MUIA_Scrollbutton_VertProp 0x90424104UL
#define MUIA_Bitmap_Alpha 0x80423e71UL
#define MUIA_Bitmap_Bitmap 0x804279bdUL
#define MUIA_Bitmap_Height 0x80421560UL
#define MUIA_Bitmap_MappingTable 0x8042e23dUL
#define MUIA_Bitmap_Precision 0x80420c74UL
#define MUIA_Bitmap_RemappedBitmap 0x80423a47UL
#define MUIA_Bitmap_SourceColors 0x80425360UL
#define MUIA_Bitmap_Transparent 0x80422805UL
#define MUIA_Bitmap_UseFriend 0x804239d8UL
#define MUIA_Bitmap_Width 0x8042eb3aUL
#define MUIA_Bodychunk_Body 0x8042ca67UL
#define MUIA_Bodychunk_Compression 0x8042de5fUL
#define MUIA_Bodychunk_Depth 0x8042c392UL
#define MUIA_Bodychunk_Masking 0x80423b0eUL
#define MUIA_Dtpic_Alpha 0x8042b4dbUL
#define MUIA_Dtpic_DarkenSelState 0x80423247UL
#define MUIA_Dtpic_Fade 0x80420429UL
#define MUIA_Dtpic_LightenOnMouse 0x8042966aUL
#define MUIA_Dtpic_Name 0x80423d72UL
#define MUIA_Pixmap_Alpha 0x80421fefUL
#define MUIA_Pixmap_CLUT 0x8042042aUL
#define MUIA_Pixmap_CompressedSize 0x8042e7e4UL
#define MUIA_Pixmap_Compression 0x8042ce74UL
#define MUIA_Pixmap_Data 0x80429ea0UL
#define MUIA_Pixmap_Format 0x8042ab14UL
#define MUIA_Pixmap_Height 0x804288beUL
#define MUIA_Pixmap_UncompressedData 0x8042b085UL
#define MUIA_Pixmap_Width 0x8042ccb8UL
#define MUIV_Pixmap_Compression_None 0
#define MUIV_Pixmap_Compression_RLE 1
#define MUIV_Pixmap_Compression_BZip2 2
#define MUIV_Pixmap_Format_CLUT8 0
#define MUIV_Pixmap_Format_RGB24 1
#define MUIV_Pixmap_Format_ARGB32 2
#define MUIA_Dataspace_Pool 0x80424cf9UL
#define MUIA_Process_AutoLaunch 0x80428855UL
#define MUIA_Process_Name 0x8042732bUL
#define MUIA_Process_Priority 0x80422a54UL
#define MUIA_Process_SourceClass 0x8042cf8bUL
#define MUIA_Process_SourceObject 0x804212a2UL
#define MUIA_Process_StackSize 0x804230d0UL
#define MUIA_Process_Task 0x8042b123UL
#define MUIM_Dataspace_Add 0x80423366UL
#define MUIM_Dataspace_Clear 0x8042b6c9UL
#define MUIM_Dataspace_Find 0x8042832cUL
#define MUIM_Dataspace_Merge 0x80423e2bUL
#define MUIM_Dataspace_ReadIFF 0x80420dfbUL
#define MUIM_Dataspace_Remove 0x8042dce1UL
#define MUIM_Dataspace_WriteIFF 0x80425e8eUL
#define MUIM_Process_Kill 0x804264cfUL
#define MUIM_Process_Launch 0x80425df7UL
#define MUIM_Process_Process 0x804230aaUL
#define MUIM_Process_Signal 0x8042e791UL
#define MUIM_Semaphore_Attempt 0x80426ce2UL
#define MUIM_Semaphore_AttemptShared 0x80422551UL
#define MUIM_Semaphore_Obtain 0x804276f0UL
#define MUIM_Semaphore_ObtainShared 0x8042ea02UL
#define MUIM_Semaphore_Release 0x80421f2dUL
#define MUIA_Aboutmui_Application 0x80422523UL
#define MUIM_Settingsgroup_ConfigToGadgets 0x80427043UL
#define MUIM_Settingsgroup_GadgetsToConfig 0x80425242UL
struct MUIP_Settingsgroup_ConfigToGadgets { IPTR MethodID; Object *configdata; };
struct MUIP_Settingsgroup_GadgetsToConfig { IPTR MethodID; Object *configdata; };

/* BetterString.mcc (its published values) */
#define MUIA_BetterString_SelectSize 0xad001001UL
#define MUIA_BetterString_StayActive 0xad001003UL
#define MUIA_BetterString_Columns 0xad001005UL
#define MUIA_BetterString_NoInput 0xad001007UL
#define MUIA_BetterString_KeyUpFocus 0xad001008UL
#define MUIA_BetterString_KeyDownFocus 0xad001009UL
#define MUIA_BetterString_InactiveContents 0xad00100aUL
#define MUIA_BetterString_NoShortcuts 0xad00100cUL
#define MUIA_BetterString_SelectOnActive 0xad00100dUL
#define MUIA_BetterString_NoNotify 0xad00100eUL
#define MUIM_BetterString_Insert 0xad001002UL
#define MUIM_BetterString_ClearSelected 0xad001004UL
#define MUIM_BetterString_FileNameStart 0xad001006UL
#define MUIM_BetterString_DoAction 0xad00100bUL
#define MUIV_BetterString_Insert_StartOfString 0x00000000
#define MUIV_BetterString_Insert_EndOfString 0xfffffffe
#define MUIV_BetterString_Insert_BufferPos 0xffffffff
#define MUIR_BetterString_FileNameStart_Volume (-1)
#define MUIV_BetterString_DoAction_Cut 1
#define MUIV_BetterString_DoAction_Copy 2
#define MUIV_BetterString_DoAction_Paste 3
#define MUIV_BetterString_DoAction_SelectAll 4
#define MUIV_BetterString_DoAction_SelectNone 5
#define MUIV_BetterString_DoAction_Undo 6
#define MUIV_BetterString_DoAction_Redo 7
#define MUIV_BetterString_DoAction_Revert 8
#define MUIV_BetterString_DoAction_ToggleCase 9
#define MUIV_BetterString_DoAction_ToggleCaseWord 10
#define MUIV_BetterString_DoAction_IncreaseNum 11
#define MUIV_BetterString_DoAction_DecreaseNum 12
#define MUIV_BetterString_DoAction_HexToDec 13
#define MUIV_BetterString_DoAction_DecToHex 14
#define MUIV_BetterString_DoAction_NextFileComp 15
#define MUIV_BetterString_DoAction_PrevFileComp 16
#define MUIV_BetterString_DoAction_Delete 17
struct MUIP_BetterString_Insert { IPTR MethodID; STRPTR text; IPTR pos; };
struct MUIP_BetterString_ClearSelected { IPTR MethodID; };
struct MUIP_BetterString_FileNameStart { IPTR MethodID; STRPTR buffer; IPTR pos; };
struct MUIP_BetterString_DoAction { IPTR MethodID; IPTR action; };

/* NList.mcc and NListview.mcc (their published values) */
#define MUIA_NList_Active 0x9d51004cUL
#define MUIA_NList_ActiveObjectOnClick 0x9d5100c3UL
#define MUIA_NList_AdjustHeight 0x9d51004dUL
#define MUIA_NList_AdjustWidth 0x9d51004eUL
#define MUIA_NList_AutoClip 0x9d5100c0UL
#define MUIA_NList_AutoCopyToClip 0x9d51006aUL
#define MUIA_NList_AutoVisible 0x9d51004fUL
#define MUIA_NList_ButtonClick 0x9d5100f8UL
#define MUIA_NList_ClickColumn 0x9d510045UL
#define MUIA_NList_Columns 0x9d5100f6UL
#define MUIA_NList_CompareHook 0x9d510050UL
#define MUIA_NList_CompareHook2 0x9d5100fbUL
#define MUIA_NList_ConstructHook 0x9d510051UL
#define MUIA_NList_ConstructHook2 0x9d5100fcUL
#define MUIA_NList_CopyColumnToClipHook 0x9d510068UL
#define MUIA_NList_CopyColumnToClipHook2 0x9d5100faUL
#define MUIA_NList_CopyEntryToClipHook 0x9d510064UL
#define MUIA_NList_CopyEntryToClipHook2 0x9d5100f9UL
#define MUIA_NList_CursorBackground 0x9d510041UL
#define MUIA_NList_CursorPen 0x9d51003cUL
#define MUIA_NList_DefClickColumn 0x9d510046UL
#define MUIA_NList_DefaultObjectOnClick 0x9d510044UL
#define MUIA_NList_DestructHook 0x9d510052UL
#define MUIA_NList_DestructHook2 0x9d5100fdUL
#define MUIA_NList_DisplayHook 0x9d510053UL
#define MUIA_NList_DisplayHook2 0x9d5100feUL
#define MUIA_NList_DisplayRecall 0x9d51006dUL
#define MUIA_NList_DoubleClick 0x9d510047UL
#define MUIA_NList_DragColOnly 0x9d51009aUL
#define MUIA_NList_DragSortInsert 0x9d5100f2UL
#define MUIA_NList_DragSortable 0x9d510054UL
#define MUIA_NList_DragType 0x9d510048UL
#define MUIA_NList_DropMark 0x9d510055UL
#define MUIA_NList_DropType 0x9d51009cUL
#define MUIA_NList_Entries 0x9d510056UL
#define MUIA_NList_EntryClick 0x9d510099UL
#define MUIA_NList_EntryValueDependent 0x9d51006fUL
#define MUIA_NList_Exports 0x9d5100f5UL
#define MUIA_NList_First 0x9d510057UL
#define MUIA_NList_ForcePen 0x9d51009dUL
#define MUIA_NList_Format 0x9d510058UL
#define MUIA_NList_HorizDeltaFactor 0x9d510032UL
#define MUIA_NList_Horiz_DeltaFactor 0x9d510032UL
#define MUIA_NList_Horiz_Entries 0x9d510035UL
#define MUIA_NList_Horiz_First 0x9d510033UL
#define MUIA_NList_Horiz_Visible 0x9d510034UL
#define MUIA_NList_IgnoreSpecialChars 0x9d510070UL
#define MUIA_NList_Imports 0x9d5100f4UL
#define MUIA_NList_InactiveBackground 0x9d5100c2UL
#define MUIA_NList_InactivePen 0x9d5100c1UL
#define MUIA_NList_Input 0x9d510049UL
#define MUIA_NList_InsertPosition 0x9d510059UL
#define MUIA_NList_KeepActive 0x9d510065UL
#define MUIA_NList_KeyDownFocus 0x9d5100c5UL
#define MUIA_NList_KeyLeftFocus 0x9d5100c6UL
#define MUIA_NList_KeyRightFocus 0x9d5100c7UL
#define MUIA_NList_KeyUpFocus 0x9d5100c4UL
#define MUIA_NList_LineHeight 0x9d5100f7UL
#define MUIA_NList_ListBackground 0x9d51003eUL
#define MUIA_NList_ListCompatibility 0x9d510069UL
#define MUIA_NList_ListPen 0x9d51003aUL
#define MUIA_NList_MakeActive 0x9d510066UL
#define MUIA_NList_MinColSortable 0x9d5100f3UL
#define MUIA_NList_MinLineHeight 0x9d51005aUL
#define MUIA_NList_MultiClick 0x9d510043UL
#define MUIA_NList_MultiClickAlone 0x9d5100f0UL
#define MUIA_NList_MultiSelect 0x9d51004aUL
#define MUIA_NList_MultiTestHook 0x9d51005bUL
#define MUIA_NList_Pool 0x9d51005cUL
#define MUIA_NList_PoolPuddleSize 0x9d51005dUL
#define MUIA_NList_PoolThreshSize 0x9d51005eUL
#define MUIA_NList_PrivateData 0x9d51006eUL
#define MUIA_NList_Prop_DeltaFactor 0x9d510031UL
#define MUIA_NList_Prop_Entries 0x9d510038UL
#define MUIA_NList_Prop_First 0x9d510036UL
#define MUIA_NList_Prop_Visible 0x9d510037UL
#define MUIA_NList_Quiet 0x9d51005fUL
#define MUIA_NList_SelectBackground 0x9d510040UL
#define MUIA_NList_SelectChange 0x9d51004bUL
#define MUIA_NList_SelectPen 0x9d51003bUL
#define MUIA_NList_ShowDropMarks 0x9d510060UL
#define MUIA_NList_SkipChars 0x9d51006cUL
#define MUIA_NList_SortType 0x9d5100ffUL
#define MUIA_NList_SortType2 0x9d5100edUL
#define MUIA_NList_SourceArray 0x9d510061UL
#define MUIA_NList_SourceInsert 0x9d51009eUL
#define MUIA_NList_SourceString 0x9d510067UL
#define MUIA_NList_StackCheck 0x9d510097UL
#define MUIA_NList_TabSize 0x9d51006bUL
#define MUIA_NList_Title 0x9d510062UL
#define MUIA_NList_TitleBackground 0x9d51003fUL
#define MUIA_NList_TitleClick 0x9d51009bUL
#define MUIA_NList_TitleClick2 0x9d5100eeUL
#define MUIA_NList_TitleMark 0x9d5100f1UL
#define MUIA_NList_TitleMark2 0x9d5100efUL
#define MUIA_NList_TitlePen 0x9d510039UL
#define MUIA_NList_TitleSeparator 0x9d51009fUL
#define MUIA_NList_TypeSelect 0x9d510030UL
#define MUIA_NList_UnselCurBackground 0x9d510042UL
#define MUIA_NList_UnselCurPen 0x9d51003dUL
#define MUIA_NList_VertDeltaFactor 0x9d510031UL
#define MUIA_NList_Visible 0x9d510063UL
#define MUIA_NList_WordSelectChars 0x9d510098UL
#define MUIA_NListview_HSB_Height 0x9d510024UL
#define MUIA_NListview_Horiz_ScrollBar 0x9d510022UL
#define MUIA_NListview_NList 0x9d510020UL
#define MUIA_NListview_VSB_Width 0x9d510023UL
#define MUIA_NListview_Vert_ScrollBar 0x9d510021UL
#define MUIM_NList_Clear 0x9d510070UL
#define MUIM_NList_ColToColumn 0x9d51008fUL
#define MUIM_NList_ColWidth 0x9d51008cUL
#define MUIM_NList_ColumnToCol 0x9d510091UL
#define MUIM_NList_Compare 0x9d5100a3UL
#define MUIM_NList_Construct 0x9d5100a1UL
#define MUIM_NList_ContextMenuBuild 0x9d51008dUL
#define MUIM_NList_CopyTo 0x9d510087UL
#define MUIM_NList_CopyToClip 0x9d51007fUL
#define MUIM_NList_CreateImage 0x9d510071UL
#define MUIM_NList_DeleteImage 0x9d510072UL
#define MUIM_NList_Destruct 0x9d5100a2UL
#define MUIM_NList_Display 0x9d5100a4UL
#define MUIM_NList_DoMethod 0x9d51008bUL
#define MUIM_NList_DropDraw 0x9d510089UL
#define MUIM_NList_DropEntryDrawErase 0x9d51008eUL
#define MUIM_NList_DropType 0x9d510088UL
#define MUIM_NList_Exchange 0x9d510073UL
#define MUIM_NList_GetEntry 0x9d510074UL
#define MUIM_NList_GetEntryInfo 0x9d510084UL
#define MUIM_NList_GetPos 0x9d510096UL
#define MUIM_NList_GetSelectInfo 0x9d510086UL
#define MUIM_NList_GoActive 0x9d5100a5UL
#define MUIM_NList_GoInactive 0x9d5100a6UL
#define MUIM_NList_Insert 0x9d510075UL
#define MUIM_NList_InsertSingle 0x9d510076UL
#define MUIM_NList_InsertSingleWrap 0x9d510083UL
#define MUIM_NList_InsertWrap 0x9d510082UL
#define MUIM_NList_Jump 0x9d510077UL
#define MUIM_NList_Move 0x9d510078UL
#define MUIM_NList_NextSelected 0x9d510079UL
#define MUIM_NList_PrevSelected 0x9d510093UL
#define MUIM_NList_QueryBeginning 0x9d510085UL
#define MUIM_NList_Redraw 0x9d51007aUL
#define MUIM_NList_RedrawEntry 0x9d51008aUL
#define MUIM_NList_Remove 0x9d51007bUL
#define MUIM_NList_ReplaceSingle 0x9d510081UL
#define MUIM_NList_Select 0x9d51007cUL
#define MUIM_NList_SelectChange 0x9d5100a0UL
#define MUIM_NList_SetActive 0x9d5100a7UL
#define MUIM_NList_SetColumnCol 0x9d510094UL
#define MUIM_NList_Sort 0x9d51007dUL
#define MUIM_NList_Sort2 0x9d510092UL
#define MUIM_NList_Sort3 0x9d510095UL
#define MUIM_NList_TestPos 0x9d51007eUL
#define MUIM_NList_UseImage 0x9d510080UL
#define MUIM_NListview_QueryBeginning 0x9d510085UL
#define MUIM_NListview_SetScrollers 0x9d5100a8UL
#define MUIV_NList_Active_Bottom (-3)
#define MUIV_NList_Active_Down (-5)
#define MUIV_NList_Active_Off (-1)
#define MUIV_NList_Active_PageDown (-7)
#define MUIV_NList_Active_PageUp (-6)
#define MUIV_NList_Active_Top (-2)
#define MUIV_NList_Active_Up (-4)
#define MUIV_NList_ColWidth_All (-1)
#define MUIV_NList_ColWidth_Default (-1)
#define MUIV_NList_ColWidth_Get (-2)
#define MUIV_NList_ContextMenu_Always (-1655635911)
#define MUIV_NList_ContextMenu_BarOnly (-1655635915)
#define MUIV_NList_ContextMenu_Bar_Top (-1655635913)
#define MUIV_NList_ContextMenu_Default (-1655635919)
#define MUIV_NList_ContextMenu_Never (-1655635909)
#define MUIV_NList_ContextMenu_TopOnly (-1655635917)
#define MUIV_NList_CopyToClip_Active (-1)
#define MUIV_NList_CopyToClip_All (-3)
#define MUIV_NList_CopyToClip_Entries (-4)
#define MUIV_NList_CopyToClip_Entry (-5)
#define MUIV_NList_CopyToClip_Selected (-2)
#define MUIV_NList_CopyToClip_String (-7)
#define MUIV_NList_CopyToClip_Strings (-6)
#define MUIV_NList_CopyTo_Active (-1)
#define MUIV_NList_CopyTo_All (-3)
#define MUIV_NList_CopyTo_Entries (-4)
#define MUIV_NList_CopyTo_Entry (-5)
#define MUIV_NList_CopyTo_Selected (-2)
#define MUIV_NList_DoMethod_Active (-1)
#define MUIV_NList_DoMethod_All (-3)
#define MUIV_NList_DoMethod_App (-3)
#define MUIV_NList_DoMethod_Entry (-1)
#define MUIV_NList_DoMethod_Selected (-2)
#define MUIV_NList_DoMethod_Self (-2)
#define MUIV_NList_DragType_Borders 3
#define MUIV_NList_DragType_Default 1
#define MUIV_NList_DragType_Immediate 2
#define MUIV_NList_DragType_None 0
#define MUIV_NList_DragType_Qualifier 4
#define MUIV_NList_DropType_Above 1
#define MUIV_NList_DropType_Below 2
#define MUIV_NList_DropType_Mask 255
#define MUIV_NList_DropType_None 0
#define MUIV_NList_DropType_Onto 3
#define MUIV_NList_Exchange_Active (-1)
#define MUIV_NList_Exchange_Bottom (-2)
#define MUIV_NList_Exchange_Next (-3)
#define MUIV_NList_Exchange_Previous (-4)
#define MUIV_NList_Exchange_Top 0
#define MUIV_NList_Exports_Active 1
#define MUIV_NList_Exports_All 0xffff
#define MUIV_NList_Exports_ColOrder 16
#define MUIV_NList_Exports_ColWidth 8
#define MUIV_NList_Exports_Cols 248
#define MUIV_NList_Exports_First 4
#define MUIV_NList_Exports_Selected 2
#define MUIV_NList_Exports_TitleMark 128
#define MUIV_NList_First_Bottom (-3)
#define MUIV_NList_First_Down (-5)
#define MUIV_NList_First_Down2 (-9)
#define MUIV_NList_First_Down4 (-11)
#define MUIV_NList_First_PageDown (-7)
#define MUIV_NList_First_PageUp (-6)
#define MUIV_NList_First_Top (-2)
#define MUIV_NList_First_Up (-4)
#define MUIV_NList_First_Up2 (-8)
#define MUIV_NList_First_Up4 (-10)
#define MUIV_NList_Font (-20)
#define MUIV_NList_Font_Fixed (-22)
#define MUIV_NList_Font_Little (-21)
#define MUIV_NList_ForcePen_Default (-1)
#define MUIV_NList_ForcePen_Off 0
#define MUIV_NList_ForcePen_On 1
#define MUIV_NList_GetEntryInfo_Line (-2)
#define MUIV_NList_GetEntry_Active (-1)
#define MUIV_NList_GetPos_End (-1)
#define MUIV_NList_GetPos_Start (-1)
#define MUIV_NList_Horiz_First_End (-3)
#define MUIV_NList_Horiz_First_Left (-4)
#define MUIV_NList_Horiz_First_Left2 (-8)
#define MUIV_NList_Horiz_First_Left4 (-10)
#define MUIV_NList_Horiz_First_PageLeft (-6)
#define MUIV_NList_Horiz_First_PageRight (-7)
#define MUIV_NList_Horiz_First_Right (-5)
#define MUIV_NList_Horiz_First_Right2 (-9)
#define MUIV_NList_Horiz_First_Right4 (-11)
#define MUIV_NList_Horiz_First_Start (-2)
#define MUIV_NList_Imports_Active 1
#define MUIV_NList_Imports_All 0xffff
#define MUIV_NList_Imports_ColOrder 16
#define MUIV_NList_Imports_ColWidth 8
#define MUIV_NList_Imports_Cols 248
#define MUIV_NList_Imports_First 4
#define MUIV_NList_Imports_Selected 2
#define MUIV_NList_Imports_TitleMark 128
#define MUIV_NList_Insert_Active (-1)
#define MUIV_NList_Insert_Bottom (-3)
#define MUIV_NList_Insert_Flag_Raw 1
#define MUIV_NList_Insert_Sorted (-2)
#define MUIV_NList_Insert_Top 0
#define MUIV_NList_Jump_Active (-1)
#define MUIV_NList_Jump_Active_Center (-5)
#define MUIV_NList_Jump_Bottom (-2)
#define MUIV_NList_Jump_Down (-3)
#define MUIV_NList_Jump_Top 0
#define MUIV_NList_Jump_Up (-4)
#define MUIV_NList_Menu_DefOrder_All (-1655635901)
#define MUIV_NList_Menu_DefOrder_This (-1655635903)
#define MUIV_NList_Menu_DefWidth_All (-1655635905)
#define MUIV_NList_Menu_DefWidth_This (-1655635907)
#define MUIV_NList_Menu_Default_All (-1655635905)
#define MUIV_NList_Menu_Default_This (-1655635907)
#define MUIV_NList_Move_Active (-1)
#define MUIV_NList_Move_Bottom (-2)
#define MUIV_NList_Move_Next (-3)
#define MUIV_NList_Move_Previous (-4)
#define MUIV_NList_Move_Selected (-5)
#define MUIV_NList_Move_Top 0
#define MUIV_NList_MultiSelect_Always 3
#define MUIV_NList_MultiSelect_Default 1
#define MUIV_NList_MultiSelect_None 0
#define MUIV_NList_MultiSelect_Shifted 2
#define MUIV_NList_NextSelected_End (-1)
#define MUIV_NList_NextSelected_Start (-1)
#define MUIV_NList_PrevSelected_End (-1)
#define MUIV_NList_PrevSelected_Start (-1)
#define MUIV_NList_Quiet_Full (-1)
#define MUIV_NList_Quiet_None 0
#define MUIV_NList_Quiet_Visual (-2)
#define MUIV_NList_Redraw_Active (-1)
#define MUIV_NList_Redraw_All (-2)
#define MUIV_NList_Redraw_Selected (-4)
#define MUIV_NList_Redraw_Title (-3)
#define MUIV_NList_Redraw_VisibleCols (-5)
#define MUIV_NList_Remove_Active (-1)
#define MUIV_NList_Remove_First 0
#define MUIV_NList_Remove_Last (-2)
#define MUIV_NList_Remove_Selected (-3)
#define MUIV_NList_SelectChange_Flag_Multi 1
#define MUIV_NList_Select_Active (-1)
#define MUIV_NList_Select_All (-2)
#define MUIV_NList_Select_Ask 3
#define MUIV_NList_Select_Off 0
#define MUIV_NList_Select_On 1
#define MUIV_NList_Select_Toggle 2
#define MUIV_NList_SetActive_Entry 1
#define MUIV_NList_SetActive_Jump_Center 2
#define MUIV_NList_SetColumnCol_Default (-1)
#define MUIV_NList_Sort3_SortType_1 1
#define MUIV_NList_Sort3_SortType_2 2
#define MUIV_NList_Sort3_SortType_Both 0
#define MUIV_NList_SortTypeAdd_2Values (-2147483648)
#define MUIV_NList_SortTypeAdd_4Values 0x40000000
#define MUIV_NList_SortTypeAdd_Mask (-1073741824)
#define MUIV_NList_SortTypeAdd_None 0
#define MUIV_NList_SortTypeValue_Mask 0x3fffffff
#define MUIV_NList_SortType_None (-268435456)
#define MUIV_NList_TitleMark2_Box 0x40000000
#define MUIV_NList_TitleMark2_Circle (-1073741824)
#define MUIV_NList_TitleMark2_ColMask 255
#define MUIV_NList_TitleMark2_Down 0
#define MUIV_NList_TitleMark2_None (-268435456)
#define MUIV_NList_TitleMark2_TypeMask (-268435456)
#define MUIV_NList_TitleMark2_Up (-2147483648)
#define MUIV_NList_TitleMark_Box 0x40000000
#define MUIV_NList_TitleMark_Circle (-1073741824)
#define MUIV_NList_TitleMark_ColMask 255
#define MUIV_NList_TitleMark_Down 0
#define MUIV_NList_TitleMark_None (-268435456)
#define MUIV_NList_TitleMark_TypeMask (-268435456)
#define MUIV_NList_TitleMark_Up (-2147483648)
#define MUIV_NList_TypeSelect_Char 1
#define MUIV_NList_TypeSelect_Line 0
#define MUIV_NList_UseImage_All (-1)
#define MUIV_NListview_HSB_Always 1
#define MUIV_NListview_HSB_Auto 2
#define MUIV_NListview_HSB_Default 5
#define MUIV_NListview_HSB_FullAuto 3
#define MUIV_NListview_HSB_None 4
#define MUIV_NListview_HSB_Off 0x100
#define MUIV_NListview_HSB_On 0x300
#define MUIV_NListview_VSB_Always 1
#define MUIV_NListview_VSB_Auto 2
#define MUIV_NListview_VSB_Default 5
#define MUIV_NListview_VSB_FullAuto 3
#define MUIV_NListview_VSB_Left 6
#define MUIV_NListview_VSB_None 4
#define MUIV_NListview_VSB_Off 16
#define MUIV_NListview_VSB_On 48
#define MUIV_NList_ConstructHook_String ((struct Hook *)-1)
#define MUIV_NList_DestructHook_String ((struct Hook *)-1)
#define NLIST_DISPLAY_ARRAY_MAX 64
struct MUIP_NList_Clear { IPTR MethodID; };
struct MUIP_NList_Exchange { IPTR MethodID; IPTR pos1; IPTR pos2; };
struct MUIP_NList_GetEntry { IPTR MethodID; IPTR pos; APTR *entry; };
struct MUIP_NList_Insert { IPTR MethodID; APTR *entries; IPTR count; IPTR pos; IPTR flags; };
struct MUIP_NList_InsertSingle { IPTR MethodID; APTR entry; IPTR pos; };
struct MUIP_NList_Jump { IPTR MethodID; IPTR pos; };
struct MUIP_NList_Move { IPTR MethodID; IPTR from; IPTR to; };
struct MUIP_NList_NextSelected { IPTR MethodID; LONG *pos; };
struct MUIP_NList_Redraw { IPTR MethodID; IPTR pos; };
struct MUIP_NList_Remove { IPTR MethodID; IPTR pos; };
struct MUIP_NList_Select { IPTR MethodID; IPTR pos; IPTR seltype; LONG *state; };
struct MUIP_NList_Sort { IPTR MethodID; };
struct MUIP_NList_ReplaceSingle { IPTR MethodID; APTR entry; IPTR pos; IPTR wrapcol; IPTR align; };
struct MUIP_NList_InsertWrap { IPTR MethodID; APTR *entries; IPTR count; IPTR pos; IPTR wrapcol; IPTR align; IPTR flags; };
struct MUIP_NList_InsertSingleWrap { IPTR MethodID; APTR entry; IPTR pos; IPTR wrapcol; IPTR align; };
struct MUI_NList_GetEntryInfo { LONG pos, line, entry_pos; APTR entry; LONG wrapcol, charpos, charlen; };
struct MUIP_NList_GetEntryInfo { IPTR MethodID; struct MUI_NList_GetEntryInfo *res; };
struct MUIP_NList_SetActive { IPTR MethodID; IPTR pos; IPTR flags; };
struct MUIP_NList_Construct { IPTR MethodID; APTR entry; APTR pool; };
struct MUIP_NList_Destruct { IPTR MethodID; APTR entry; APTR pool; };
struct MUIP_NList_Compare { IPTR MethodID; APTR entry1; APTR entry2; IPTR sort_type1; IPTR sort_type2; };
struct MUIP_NList_Display { IPTR MethodID; APTR entry; IPTR entry_pos; STRPTR *strings; STRPTR *preparses; };
struct NList_ConstructMessage { APTR entry; APTR pool; };
struct NList_DestructMessage { APTR entry; APTR pool; };
struct NList_CompareMessage { APTR entry1; APTR entry2; LONG sort_type; LONG sort_type2; };
struct NList_DisplayMessage { APTR entry; LONG entry_pos; char *strings[NLIST_DISPLAY_ARRAY_MAX]; char *preparses[NLIST_DISPLAY_ARRAY_MAX]; };

/* NListtree.mcc (its published values) */
#define MUIA_NListtree_Active 0xfec81201UL
#define MUIA_NListtree_ActiveList 0xfec81202UL
#define MUIA_NListtree_AutoVisible 0xfec81211UL
#define MUIA_NListtree_CloseHook 0xfec81203UL
#define MUIA_NListtree_CompareHook 0xfec8120eUL
#define MUIA_NListtree_ConstructHook 0xfec81204UL
#define MUIA_NListtree_CopyToClipHook 0xfec81217UL
#define MUIA_NListtree_DestructHook 0xfec81205UL
#define MUIA_NListtree_DisplayHook 0xfec81206UL
#define MUIA_NListtree_DoubleClick 0xfec81207UL
#define MUIA_NListtree_DragDropSort 0xfec81208UL
#define MUIA_NListtree_DropTarget 0xfec81219UL
#define MUIA_NListtree_DropTargetPos 0xfec8121aUL
#define MUIA_NListtree_DropType 0xfec81218UL
#define MUIA_NListtree_DupNodeName 0xfec81209UL
#define MUIA_NListtree_EmptyNodes 0xfec8120aUL
#define MUIA_NListtree_FindNameHook 0xfec81212UL
#define MUIA_NListtree_FindUserDataHook 0xfec8121bUL
#define MUIA_NListtree_Format 0xfec8120bUL
#define MUIA_NListtree_MultiSelect 0xfec81213UL
#define MUIA_NListtree_MultiTestHook 0xfec81214UL
#define MUIA_NListtree_OpenHook 0xfec8120cUL
#define MUIA_NListtree_Quiet 0xfec8120dUL
#define MUIA_NListtree_SelectChange 0xfec8121dUL
#define MUIA_NListtree_ShowTree 0xfec8121cUL
#define MUIA_NListtree_Title 0xfec8120fUL
#define MUIA_NListtree_TreeColumn 0xfec81210UL
#define MUIM_NListtree_Active 0xfec81115UL
#define MUIM_NListtree_Clear 0xfec8111bUL
#define MUIM_NListtree_Close 0xfec81102UL
#define MUIM_NListtree_Compare 0xfec81123UL
#define MUIM_NListtree_Construct 0xfec81120UL
#define MUIM_NListtree_Copy 0xfec81113UL
#define MUIM_NListtree_CopyToClip 0xfec81119UL
#define MUIM_NListtree_Destruct 0xfec81121UL
#define MUIM_NListtree_Display 0xfec81122UL
#define MUIM_NListtree_DoubleClick 0xfec81116UL
#define MUIM_NListtree_DropDraw 0xfec8111fUL
#define MUIM_NListtree_DropType 0xfec8111eUL
#define MUIM_NListtree_Exchange 0xfec81105UL
#define MUIM_NListtree_FindName 0xfec81108UL
#define MUIM_NListtree_FindUserData 0xfec8111aUL
#define MUIM_NListtree_GetEntry 0xfec81109UL
#define MUIM_NListtree_GetNr 0xfec8110aUL
#define MUIM_NListtree_Insert 0xfec81103UL
#define MUIM_NListtree_InsertStruct 0xfec81114UL
#define MUIM_NListtree_Move 0xfec81106UL
#define MUIM_NListtree_MultiTest 0xfec81111UL
#define MUIM_NListtree_NextSelected 0xfec81110UL
#define MUIM_NListtree_Open 0xfec81101UL
#define MUIM_NListtree_PrevSelected 0xfec81118UL
#define MUIM_NListtree_Redraw 0xfec8110dUL
#define MUIM_NListtree_Remove 0xfec81104UL
#define MUIM_NListtree_Rename 0xfec81107UL
#define MUIM_NListtree_Select 0xfec81112UL
#define MUIM_NListtree_Sort 0xfec8110bUL
#define MUIM_NListtree_TestPos 0xfec8110cUL
#define MUIV_NListtree_ActiveList_Off 0
#define MUIV_NListtree_Active_First (-3)
#define MUIV_NListtree_Active_FirstVisible (-4)
#define MUIV_NListtree_Active_LastVisible (-5)
#define MUIV_NListtree_Active_Off 0
#define MUIV_NListtree_Active_Parent (-2)
#define MUIV_NListtree_AutoVisible_Expand 3
#define MUIV_NListtree_AutoVisible_FirstOpen 2
#define MUIV_NListtree_AutoVisible_Normal 1
#define MUIV_NListtree_AutoVisible_Off 0
#define MUIV_NListtree_Close_ListNode_Active (-2)
#define MUIV_NListtree_Close_ListNode_Parent (-1)
#define MUIV_NListtree_Close_ListNode_Root 0
#define MUIV_NListtree_Close_TreeNode_Active (-2)
#define MUIV_NListtree_Close_TreeNode_All (-3)
#define MUIV_NListtree_Close_TreeNode_Head 0
#define MUIV_NListtree_Close_TreeNode_Tail (-1)
#define MUIV_NListtree_CompareHook_Head 0
#define MUIV_NListtree_CompareHook_LeavesBottom (-4)
#define MUIV_NListtree_CompareHook_LeavesMixed (-3)
#define MUIV_NListtree_CompareHook_LeavesTop (-2)
#define MUIV_NListtree_CompareHook_Tail (-1)
#define MUIV_NListtree_ConstructHook_Flag_AutoCreate 0x8000
#define MUIV_NListtree_ConstructHook_String (-1)
#define MUIV_NListtree_CopyToClipHook_Default 0
#define MUIV_NListtree_CopyToClip_Active (-1)
#define MUIV_NListtree_Copy_DestListNode_Active (-2)
#define MUIV_NListtree_Copy_DestListNode_Root 0
#define MUIV_NListtree_Copy_DestTreeNode_Active (-2)
#define MUIV_NListtree_Copy_DestTreeNode_Head 0
#define MUIV_NListtree_Copy_DestTreeNode_Sorted (-4)
#define MUIV_NListtree_Copy_DestTreeNode_Tail (-1)
#define MUIV_NListtree_Copy_Flag_KeepStructure 0x2000
#define MUIV_NListtree_Copy_SourceListNode_Active (-2)
#define MUIV_NListtree_Copy_SourceListNode_Root 0
#define MUIV_NListtree_Copy_SourceTreeNode_Active (-2)
#define MUIV_NListtree_Copy_SourceTreeNode_Head 0
#define MUIV_NListtree_Copy_SourceTreeNode_Tail (-1)
#define MUIV_NListtree_DestructHook_String (-1)
#define MUIV_NListtree_DisplayHook_Default (-1)
#define MUIV_NListtree_DoubleClick_All (-2)
#define MUIV_NListtree_DoubleClick_NoTrigger (-4)
#define MUIV_NListtree_DoubleClick_Off (-1)
#define MUIV_NListtree_DoubleClick_Tree (-3)
#define MUIV_NListtree_DropType_Above 1
#define MUIV_NListtree_DropType_Below 2
#define MUIV_NListtree_DropType_None 0
#define MUIV_NListtree_DropType_Onto 3
#define MUIV_NListtree_DropType_Sorted 4
#define MUIV_NListtree_Exchange_ListNode1_Active (-2)
#define MUIV_NListtree_Exchange_ListNode1_Root 0
#define MUIV_NListtree_Exchange_ListNode2_Active (-2)
#define MUIV_NListtree_Exchange_ListNode2_Root 0
#define MUIV_NListtree_Exchange_TreeNode1_Active (-2)
#define MUIV_NListtree_Exchange_TreeNode1_Head 0
#define MUIV_NListtree_Exchange_TreeNode1_Tail (-1)
#define MUIV_NListtree_Exchange_TreeNode2_Active (-2)
#define MUIV_NListtree_Exchange_TreeNode2_Down (-6)
#define MUIV_NListtree_Exchange_TreeNode2_Head 0
#define MUIV_NListtree_Exchange_TreeNode2_Tail (-1)
#define MUIV_NListtree_Exchange_TreeNode2_Up (-5)
#define MUIV_NListtree_FindNameHook_CaseInsensitive (-1)
#define MUIV_NListtree_FindNameHook_CaseSensitive 0
#define MUIV_NListtree_FindNameHook_Part (-2)
#define MUIV_NListtree_FindNameHook_PartCaseInsensitive (-3)
#define MUIV_NListtree_FindNameHook_PointerCompare (-4)
#define MUIV_NListtree_FindName_Flag_Activate 0x2000
#define MUIV_NListtree_FindName_Flag_Reverse 0x200
#define MUIV_NListtree_FindName_Flag_SameLevel 0x8000
#define MUIV_NListtree_FindName_Flag_Selected 0x800
#define MUIV_NListtree_FindName_Flag_StartNode 0x400
#define MUIV_NListtree_FindName_Flag_Visible 0x4000
#define MUIV_NListtree_FindName_ListNode_Active (-2)
#define MUIV_NListtree_FindName_ListNode_Root 0
#define MUIV_NListtree_FindUserDataHook_CaseInsensitive (-1)
#define MUIV_NListtree_FindUserDataHook_CaseSensitive 0
#define MUIV_NListtree_FindUserDataHook_Part (-2)
#define MUIV_NListtree_FindUserDataHook_PartCaseInsensitive (-3)
#define MUIV_NListtree_FindUserDataHook_PointerCompare (-4)
#define MUIV_NListtree_FindUserData_Flag_Activate 0x2000
#define MUIV_NListtree_FindUserData_Flag_Reverse 0x200
#define MUIV_NListtree_FindUserData_Flag_SameLevel 0x8000
#define MUIV_NListtree_FindUserData_Flag_Selected 0x800
#define MUIV_NListtree_FindUserData_Flag_StartNode 0x400
#define MUIV_NListtree_FindUserData_Flag_Visible 0x4000
#define MUIV_NListtree_FindUserData_ListNode_Active (-2)
#define MUIV_NListtree_FindUserData_ListNode_Root 0
#define MUIV_NListtree_GetEntry_Flag_SameLevel 0x8000
#define MUIV_NListtree_GetEntry_Flag_Visible 0x4000
#define MUIV_NListtree_GetEntry_ListNode_Active (-2)
#define MUIV_NListtree_GetEntry_ListNode_Root 0
#define MUIV_NListtree_GetEntry_Position_Active (-2)
#define MUIV_NListtree_GetEntry_Position_Head 0
#define MUIV_NListtree_GetEntry_Position_Next (-3)
#define MUIV_NListtree_GetEntry_Position_Parent (-5)
#define MUIV_NListtree_GetEntry_Position_Previous (-4)
#define MUIV_NListtree_GetEntry_Position_Tail (-1)
#define MUIV_NListtree_GetEntry_TreeNode_Active (-3)
#define MUIV_NListtree_GetNr_Flag_CountAll 0x8000
#define MUIV_NListtree_GetNr_Flag_CountLevel 0x4000
#define MUIV_NListtree_GetNr_Flag_CountList 0x2000
#define MUIV_NListtree_GetNr_Flag_ListEmpty 0x1000
#define MUIV_NListtree_GetNr_Flag_Visible 0x800
#define MUIV_NListtree_GetNr_TreeNode_Active (-2)
#define MUIV_NListtree_Insert_Flag_Active 0x2000
#define MUIV_NListtree_Insert_Flag_NextNode 0x1000
#define MUIV_NListtree_Insert_ListNode_Active (-2)
#define MUIV_NListtree_Insert_ListNode_ActiveFallback (-4)
#define MUIV_NListtree_Insert_ListNode_LastInserted (-3)
#define MUIV_NListtree_Insert_ListNode_Root 0
#define MUIV_NListtree_Insert_PrevNode_Active (-2)
#define MUIV_NListtree_Insert_PrevNode_Head 0
#define MUIV_NListtree_Insert_PrevNode_Sorted (-4)
#define MUIV_NListtree_Insert_PrevNode_Tail (-1)
#define MUIV_NListtree_Move_Flag_KeepStructure 0x2000
#define MUIV_NListtree_Move_NewListNode_Active (-2)
#define MUIV_NListtree_Move_NewListNode_Root 0
#define MUIV_NListtree_Move_NewTreeNode_Active (-2)
#define MUIV_NListtree_Move_NewTreeNode_Head 0
#define MUIV_NListtree_Move_NewTreeNode_Sorted (-4)
#define MUIV_NListtree_Move_NewTreeNode_Tail (-1)
#define MUIV_NListtree_Move_OldListNode_Active (-2)
#define MUIV_NListtree_Move_OldListNode_Root 0
#define MUIV_NListtree_Move_OldTreeNode_Active (-2)
#define MUIV_NListtree_Move_OldTreeNode_Head 0
#define MUIV_NListtree_Move_OldTreeNode_Tail (-1)
#define MUIV_NListtree_MultiSelect_Always 3
#define MUIV_NListtree_MultiSelect_Default 1
#define MUIV_NListtree_MultiSelect_None 0
#define MUIV_NListtree_MultiSelect_Shifted 2
#define MUIV_NListtree_NextSelected_End (-1)
#define MUIV_NListtree_NextSelected_Start (-1)
#define MUIV_NListtree_Open_ListNode_Active (-2)
#define MUIV_NListtree_Open_ListNode_Parent (-1)
#define MUIV_NListtree_Open_ListNode_Root 0
#define MUIV_NListtree_Open_TreeNode_Active (-2)
#define MUIV_NListtree_Open_TreeNode_All (-3)
#define MUIV_NListtree_Open_TreeNode_Head 0
#define MUIV_NListtree_Open_TreeNode_Tail (-1)
#define MUIV_NListtree_PrevSelected_End (-1)
#define MUIV_NListtree_PrevSelected_Start (-1)
#define MUIV_NListtree_Redraw_Active (-1)
#define MUIV_NListtree_Redraw_All (-2)
#define MUIV_NListtree_Redraw_Flag_Nr 0x8000
#define MUIV_NListtree_Remove_Flag_NoActive 0x2000
#define MUIV_NListtree_Remove_ListNode_Active (-2)
#define MUIV_NListtree_Remove_ListNode_Root 0
#define MUIV_NListtree_Remove_TreeNode_Active (-2)
#define MUIV_NListtree_Remove_TreeNode_All (-3)
#define MUIV_NListtree_Remove_TreeNode_Head 0
#define MUIV_NListtree_Remove_TreeNode_Selected (-4)
#define MUIV_NListtree_Remove_TreeNode_Tail (-1)
#define MUIV_NListtree_Rename_Flag_NoRefresh 0x200
#define MUIV_NListtree_Rename_Flag_User 0x100
#define MUIV_NListtree_Rename_TreeNode_Active (-2)
#define MUIV_NListtree_Select_Active (-1)
#define MUIV_NListtree_Select_All (-2)
#define MUIV_NListtree_Select_Ask 3
#define MUIV_NListtree_Select_Flag_Force 0x8000
#define MUIV_NListtree_Select_Off 0
#define MUIV_NListtree_Select_On 1
#define MUIV_NListtree_Select_Toggle 2
#define MUIV_NListtree_Select_Visible (-3)
#define MUIV_NListtree_ShowTree_Toggle (-1)
#define MUIV_NListtree_Sort_Flag_RecursiveAll 0x1000
#define MUIV_NListtree_Sort_Flag_RecursiveOpen 0x2000
#define MUIV_NListtree_Sort_ListNode_Active (-2)
#define MUIV_NListtree_Sort_ListNode_Root 0
#define MUIV_NListtree_Sort_TreeNode_Active (-3)
#define MUIV_NListtree_TestPos_Result_Above 1
#define MUIV_NListtree_TestPos_Result_Below 2
#define MUIV_NListtree_TestPos_Result_None 0
#define MUIV_NListtree_TestPos_Result_Onto 3
#define MUIV_NListtree_TestPos_Result_Sorted 4
#define TNF_OPEN (1 << 0)
#define TNF_LIST (1 << 1)
#define TNF_FROZEN (1 << 2)
#define TNF_NOSIGN (1 << 3)
#define TNF_SELECTED (1 << 4)
struct MUI_NListtree_TreeNode { struct MinNode tn_Node; STRPTR tn_Name; UWORD tn_Flags; APTR tn_User; };
struct MUI_NListtree_TestPos_Result { struct MUI_NListtree_TreeNode *tpr_TreeNode; UWORD tpr_Type; LONG tpr_ListEntry; UWORD tpr_ListFlags; WORD tpr_Column; };
struct MUIP_NListtree_Open { IPTR MethodID; struct MUI_NListtree_TreeNode *ListNode, *TreeNode; IPTR Flags; };
struct MUIP_NListtree_Close { IPTR MethodID; struct MUI_NListtree_TreeNode *ListNode, *TreeNode; IPTR Flags; };
struct MUIP_NListtree_Insert { IPTR MethodID; STRPTR Name; APTR User; struct MUI_NListtree_TreeNode *ListNode, *PrevNode; IPTR Flags; };
struct MUIP_NListtree_Remove { IPTR MethodID; struct MUI_NListtree_TreeNode *ListNode, *TreeNode; IPTR Flags; };
struct MUIP_NListtree_Clear { IPTR MethodID; struct MUI_NListtree_TreeNode *ListNode; IPTR Flags; };
struct MUIP_NListtree_FindName { IPTR MethodID; struct MUI_NListtree_TreeNode *ListNode; STRPTR Name; IPTR Flags; };
struct MUIP_NListtree_FindUserData { IPTR MethodID; struct MUI_NListtree_TreeNode *ListNode; APTR User; IPTR Flags; };
struct MUIP_NListtree_GetEntry { IPTR MethodID; struct MUI_NListtree_TreeNode *Node; IPTR Position; IPTR Flags; };
struct MUIP_NListtree_GetNr { IPTR MethodID; struct MUI_NListtree_TreeNode *TreeNode; IPTR Flags; };
struct MUIP_NListtree_Move { IPTR MethodID; struct MUI_NListtree_TreeNode *OldListNode, *OldTreeNode, *NewListNode, *NewTreeNode; IPTR Flags; };
struct MUIP_NListtree_Exchange { IPTR MethodID; struct MUI_NListtree_TreeNode *ListNode1, *TreeNode1, *ListNode2, *TreeNode2; IPTR Flags; };
struct MUIP_NListtree_Rename { IPTR MethodID; struct MUI_NListtree_TreeNode *TreeNode; STRPTR NewName; IPTR Flags; };
struct MUIP_NListtree_Sort { IPTR MethodID; struct MUI_NListtree_TreeNode *ListNode; IPTR Flags; };
struct MUIP_NListtree_TestPos { IPTR MethodID; IPTR X, Y; APTR Result; };
struct MUIP_NListtree_Redraw { IPTR MethodID; struct MUI_NListtree_TreeNode *TreeNode; IPTR Flags; };
struct MUIP_NListtree_Select { IPTR MethodID; struct MUI_NListtree_TreeNode *TreeNode; IPTR SelType, SelFlags; LONG *State; };
struct MUIP_NListtree_NextSelected { IPTR MethodID; struct MUI_NListtree_TreeNode **TreeNode; };
struct MUIP_NListtree_PrevSelected { IPTR MethodID; struct MUI_NListtree_TreeNode **TreeNode; };
struct MUIP_NListtree_MultiTest { IPTR MethodID; struct MUI_NListtree_TreeNode *TreeNode; IPTR SelType, SelFlags, CurrType; };
struct MUIP_NListtree_Copy { IPTR MethodID; struct MUI_NListtree_TreeNode *SourceListNode, *SourceTreeNode, *DestListNode, *DestTreeNode; IPTR Flags; };
struct MUIP_NListtree_InsertStruct { IPTR MethodID; STRPTR Name; APTR User; STRPTR Delimiter; IPTR Flags; };
struct MUIP_NListtree_Active { IPTR MethodID; IPTR Pos; struct MUI_NListtree_TreeNode *ActiveNode; };
struct MUIP_NListtree_DoubleClick { IPTR MethodID; struct MUI_NListtree_TreeNode *TreeNode; IPTR Entry, Column; };
struct MUIP_NListtree_Construct { IPTR MethodID; STRPTR Name; APTR UserData; APTR MemPool; IPTR Flags; };
struct MUIP_NListtree_Destruct { IPTR MethodID; STRPTR Name; APTR UserData; APTR MemPool; IPTR Flags; };
struct MUIP_NListtree_Display { IPTR MethodID; struct MUI_NListtree_TreeNode *TreeNode; IPTR EntryPos; STRPTR *Array; STRPTR *Preparse; };
struct MUIP_NListtree_Compare { IPTR MethodID; struct MUI_NListtree_TreeNode *TreeNode1, *TreeNode2; IPTR SortType; };
/* a hook's message is its method's, HookID the method's id */
struct MUIP_NListtree_ConstructMessage { IPTR HookID; STRPTR Name; APTR UserData; APTR MemPool; IPTR Flags; };
struct MUIP_NListtree_DestructMessage { IPTR HookID; STRPTR Name; APTR UserData; APTR MemPool; IPTR Flags; };
struct MUIP_NListtree_DisplayMessage { IPTR HookID; struct MUI_NListtree_TreeNode *TreeNode; IPTR EntryPos; STRPTR *Array; STRPTR *Preparse; };
struct MUIP_NListtree_CompareMessage { IPTR HookID; struct MUI_NListtree_TreeNode *TreeNode1, *TreeNode2; IPTR SortType; };
struct MUIP_NListtree_OpenMessage { IPTR HookID; struct MUI_NListtree_TreeNode *TreeNode; };
struct MUIP_NListtree_CloseMessage { IPTR HookID; struct MUI_NListtree_TreeNode *TreeNode; };
struct MUIP_NListtree_FindNameMessage { IPTR HookID; STRPTR Name; STRPTR NodeName; APTR UserData; IPTR Flags; };
struct MUIP_NListtree_FindUserDataMessage { IPTR HookID; APTR User; APTR UserData; STRPTR NodeName; IPTR Flags; };

/* TextEditor.mcc (its published values) */
#define MUIA_TextEditor_ActiveObjectOnClick 0xad00003aUL
#define MUIA_TextEditor_AreaMarked 0xad000014UL
#define MUIA_TextEditor_AutoClip 0xad000034UL
#define MUIA_TextEditor_ColorMap 0xad00002fUL
#define MUIA_TextEditor_Columns 0xad000033UL
#define MUIA_TextEditor_Contents 0xad000002UL
#define MUIA_TextEditor_ConvertTabs 0xad00003dUL
#define MUIA_TextEditor_CursorPosition 0xad000035UL
#define MUIA_TextEditor_CursorX 0xad000004UL
#define MUIA_TextEditor_CursorY 0xad000005UL
#define MUIA_TextEditor_DoubleClickHook 0xad000006UL
#define MUIA_TextEditor_ExportHook 0xad000008UL
#define MUIA_TextEditor_ExportWrap 0xad000009UL
#define MUIA_TextEditor_FixedFont 0xad00000aUL
#define MUIA_TextEditor_Flow 0xad00000bUL
#define MUIA_TextEditor_HasChanged 0xad00000cUL
#define MUIA_TextEditor_ImportHook 0xad00000eUL
#define MUIA_TextEditor_ImportWrap 0xad000010UL
#define MUIA_TextEditor_InVirtualGroup 0xad00001bUL
#define MUIA_TextEditor_InsertMode 0xad00000fUL
#define MUIA_TextEditor_KeyBindings 0xad000011UL
#define MUIA_TextEditor_KeyUpFocus 0xad000036UL
#define MUIA_TextEditor_Keywords 0xad000040UL
#define MUIA_TextEditor_MatchedKeyword 0xad000041UL
#define MUIA_TextEditor_MultiColorQuoting 0xad000031UL
#define MUIA_TextEditor_NumLock 0xad000018UL
#define MUIA_TextEditor_PasteColors 0xad00003cUL
#define MUIA_TextEditor_PasteStyles 0xad00003bUL
#define MUIA_TextEditor_Pen 0xad00002eUL
#define MUIA_TextEditor_Prop_DeltaFactor 0xad00000dUL
#define MUIA_TextEditor_Prop_Entries 0xad000015UL
#define MUIA_TextEditor_Prop_First 0xad000020UL
#define MUIA_TextEditor_Prop_Visible 0xad000016UL
#define MUIA_TextEditor_Quiet 0xad000017UL
#define MUIA_TextEditor_ReadOnly 0xad000019UL
#define MUIA_TextEditor_RedoAvailable 0xad000013UL
#define MUIA_TextEditor_Rows 0xad000032UL
#define MUIA_TextEditor_Separator 0xad00002cUL
#define MUIA_TextEditor_Slider 0xad00001aUL
#define MUIA_TextEditor_StyleBold 0xad00001cUL
#define MUIA_TextEditor_StyleItalic 0xad00001dUL
#define MUIA_TextEditor_StyleUnderline 0xad00001eUL
#define MUIA_TextEditor_TabSize 0xad00003fUL
#define MUIA_TextEditor_TypeAndSpell 0xad000007UL
#define MUIA_TextEditor_UndoAvailable 0xad000012UL
#define MUIA_TextEditor_UndoLevels 0xad000038UL
#define MUIA_TextEditor_WrapBorder 0xad000021UL
#define MUIA_TextEditor_WrapMode 0xad000039UL
#define MUIA_TextEditor_WrapWords 0xad00003eUL
#define MUIM_TextEditor_ARexxCmd 0xad000023UL
#define MUIM_TextEditor_AddKeyBindings 0xad000022UL
#define MUIM_TextEditor_BlockInfo 0xad000030UL
#define MUIM_TextEditor_ClearText 0xad000024UL
#define MUIM_TextEditor_ExportBlock 0xad000037UL
#define MUIM_TextEditor_ExportText 0xad000025UL
#define MUIM_TextEditor_HandleError 0xad00001fUL
#define MUIM_TextEditor_InsertText 0xad000026UL
#define MUIM_TextEditor_MacroBegin 0xad000027UL
#define MUIM_TextEditor_MacroEnd 0xad000028UL
#define MUIM_TextEditor_MacroExecute 0xad000029UL
#define MUIM_TextEditor_MarkText 0xad00002cUL
#define MUIM_TextEditor_QueryKeyAction 0xad00002dUL
#define MUIM_TextEditor_Replace 0xad00002aUL
#define MUIM_TextEditor_Search 0xad00002bUL
#define MUIM_TextEditor_SetBlock 0xad00002eUL
#define MUIV_TextEditor_ExportHook_EMail 1
#define MUIV_TextEditor_ExportHook_NoStyle 2
#define MUIV_TextEditor_ExportHook_Plain 0
#define MUIV_TextEditor_Flow_Center 1
#define MUIV_TextEditor_Flow_Justified 3
#define MUIV_TextEditor_Flow_Left 0
#define MUIV_TextEditor_Flow_Right 2
#define MUIV_TextEditor_ImportHook_EMail 2
#define MUIV_TextEditor_ImportHook_MIME 3
#define MUIV_TextEditor_ImportHook_MIMEQuoted 4
#define MUIV_TextEditor_ImportHook_Plain 0
#define MUIV_TextEditor_InsertText_Bottom 2
#define MUIV_TextEditor_InsertText_Cursor 0
#define MUIV_TextEditor_InsertText_Top 1
#define MUIV_TextEditor_KeyAction_Backspace 17
#define MUIV_TextEditor_KeyAction_Bottom 9
#define MUIV_TextEditor_KeyAction_Copy 22
#define MUIV_TextEditor_KeyAction_Cut 21
#define MUIV_TextEditor_KeyAction_DelBOL 26
#define MUIV_TextEditor_KeyAction_DelBOW 28
#define MUIV_TextEditor_KeyAction_DelEOL 27
#define MUIV_TextEditor_KeyAction_DelEOW 29
#define MUIV_TextEditor_KeyAction_DelLine 37
#define MUIV_TextEditor_KeyAction_Delete 18
#define MUIV_TextEditor_KeyAction_Down 1
#define MUIV_TextEditor_KeyAction_EndOfLine 7
#define MUIV_TextEditor_KeyAction_GotoBookmark1 31
#define MUIV_TextEditor_KeyAction_GotoBookmark2 32
#define MUIV_TextEditor_KeyAction_GotoBookmark3 33
#define MUIV_TextEditor_KeyAction_Left 2
#define MUIV_TextEditor_KeyAction_NextGadget 30
#define MUIV_TextEditor_KeyAction_NextLine 13
#define MUIV_TextEditor_KeyAction_NextSentence 15
#define MUIV_TextEditor_KeyAction_NextWord 11
#define MUIV_TextEditor_KeyAction_PageDown 5
#define MUIV_TextEditor_KeyAction_PageUp 4
#define MUIV_TextEditor_KeyAction_Paste 23
#define MUIV_TextEditor_KeyAction_PrevLine 12
#define MUIV_TextEditor_KeyAction_PrevSentence 14
#define MUIV_TextEditor_KeyAction_PrevWord 10
#define MUIV_TextEditor_KeyAction_Redo 25
#define MUIV_TextEditor_KeyAction_Return 19
#define MUIV_TextEditor_KeyAction_Right 3
#define MUIV_TextEditor_KeyAction_SelectAll 38
#define MUIV_TextEditor_KeyAction_SelectNone 39
#define MUIV_TextEditor_KeyAction_SetBookmark1 34
#define MUIV_TextEditor_KeyAction_SetBookmark2 35
#define MUIV_TextEditor_KeyAction_SetBookmark3 36
#define MUIV_TextEditor_KeyAction_StartOfLine 6
#define MUIV_TextEditor_KeyAction_SuggestWord 16
#define MUIV_TextEditor_KeyAction_Tab 20
#define MUIV_TextEditor_KeyAction_Top 8
#define MUIV_TextEditor_KeyAction_Undo 24
#define MUIV_TextEditor_KeyAction_Up 0
#define MUIV_TextEditor_MarkText_All (-1)
#define MUIV_TextEditor_MarkText_None (-1)
#define MUIV_TextEditor_SetBlock_Max (-2)
#define MUIV_TextEditor_SetBlock_Min (-1)
#define MUIV_TextEditor_TabSize_Default 0
#define MUIV_TextEditor_WrapMode_HardWrap 2
#define MUIV_TextEditor_WrapMode_NoWrap 0
#define MUIV_TextEditor_WrapMode_SoftWrap 1
#define MUIF_TextEditor_Search_FromTop (1 << 0)
#define MUIF_TextEditor_Search_Next (1 << 1)
#define MUIF_TextEditor_Search_CaseSensitive (1 << 2)
#define MUIF_TextEditor_Search_DOSPattern (1 << 3)
#define MUIF_TextEditor_Search_Backwards (1 << 4)
#define MUIF_TextEditor_ExportBlock_FullLines (1 << 0)
#define MUIF_TextEditor_ExportBlock_TakeBlock (1 << 1)
#define MUIF_TextEditor_SetBlock_Color (1 << 0)
#define MUIF_TextEditor_SetBlock_StyleBold (1 << 1)
#define MUIF_TextEditor_SetBlock_StyleItalic (1 << 2)
#define MUIF_TextEditor_SetBlock_StyleUnderline (1 << 3)
#define MUIF_TextEditor_SetBlock_Flow (1 << 4)
#define Error_ClipboardIsEmpty 0x01
#define Error_ClipboardIsNotFTXT 0x02
#define Error_MacroBufferIsFull 0x03
#define Error_MemoryAllocationFailed 0x04
#define Error_NoAreaMarked 0x05
#define Error_NoMacroDefined 0x06
#define Error_NothingToRedo 0x07
#define Error_NothingToUndo 0x08
#define Error_NotEnoughUndoMem 0x09
#define Error_StringNotFound 0x0a
#define Error_NoBookmarkInstalled 0x0b
#define Error_BookmarkHasBeenLost 0x0c
struct ClickMessage { STRPTR LineContents; ULONG ClickPosition; ULONG Qualifier; };
struct MUIP_TextEditor_ARexxCmd { IPTR MethodID; STRPTR command; };
struct MUIP_TextEditor_BlockInfo { IPTR MethodID; LONG *startx, *starty, *stopx, *stopy; };
struct MUIP_TextEditor_ClearText { IPTR MethodID; };
struct MUIP_TextEditor_ExportBlock { IPTR MethodID; IPTR flags; IPTR startx, starty, stopx, stopy; };
struct MUIP_TextEditor_ExportText { IPTR MethodID; };
struct MUIP_TextEditor_HandleError { IPTR MethodID; IPTR errorcode; };
struct MUIP_TextEditor_InsertText { IPTR MethodID; STRPTR text; IPTR pos; };
struct MUIP_TextEditor_Replace { IPTR MethodID; STRPTR NewString; IPTR Flags; };
struct MUIP_TextEditor_Search { IPTR MethodID; STRPTR SearchString; IPTR Flags; };
struct MUIP_TextEditor_MarkText { IPTR MethodID; IPTR start_crsr_x, start_crsr_y, stop_crsr_x, stop_crsr_y; };
struct MUIP_TextEditor_QueryKeyAction { IPTR MethodID; IPTR keyAction; };
struct MUIP_TextEditor_SetBlock { IPTR MethodID; IPTR startx, starty, stopx, stopy, operation, value; };

/* Listtree.mcc (its published values) */
#define MUIA_Listtree_Active 0x80020020UL
#define MUIA_Listtree_ConstructHook 0x80020016UL
#define MUIA_Listtree_DestructHook 0x80020017UL
#define MUIA_Listtree_DisplayHook 0x80020018UL
#define MUIA_Listtree_DoubleClick 0x8002000dUL
#define MUIA_Listtree_DragDropSort 0x80020031UL
#define MUIA_Listtree_Format 0x80020014UL
#define MUIA_Listtree_Quiet 0x8002000aUL
#define MUIA_Listtree_SortHook 0x80020010UL
#define MUIA_Listtree_Title 0x80020015UL
#define MUIM_Listtree_Close 0x8002001fUL
#define MUIM_Listtree_FindName 0x8002003cUL
#define MUIM_Listtree_GetEntry 0x8002002bUL
#define MUIM_Listtree_GetNr 0x8002000eUL
#define MUIM_Listtree_Insert 0x80020011UL
#define MUIM_Listtree_Open 0x8002001eUL
#define MUIM_Listtree_Remove 0x80020012UL
#define MUIM_Listtree_Rename 0x8002000cUL
#define MUIM_Listtree_SetDropMark 0x8002004cUL
#define MUIM_Listtree_TestPos 0x8002004bUL
#define MUIV_Listtree_Close_ListNode_Active (-2)
#define MUIV_Listtree_Close_ListNode_Parent (-1)
#define MUIV_Listtree_Close_ListNode_Root 0
#define MUIV_Listtree_Close_TreeNode_Active (-2)
#define MUIV_Listtree_Close_TreeNode_All (-3)
#define MUIV_Listtree_Close_TreeNode_Head 0
#define MUIV_Listtree_Close_TreeNode_Tail (-1)
#define MUIV_Listtree_FindName_Flags_SameLevel 0x8000
#define MUIV_Listtree_FindName_Flags_Visible 0x4000
#define MUIV_Listtree_FindName_ListNode_Active (-2)
#define MUIV_Listtree_FindName_ListNode_Root 0
#define MUIV_Listtree_GetEntry_Flags_SameLevel 0x8000
#define MUIV_Listtree_GetEntry_Flags_Visible 0x4000
#define MUIV_Listtree_GetEntry_ListNode_Active (-2)
#define MUIV_Listtree_GetEntry_ListNode_Root 0
#define MUIV_Listtree_GetEntry_Position_Active (-2)
#define MUIV_Listtree_GetEntry_Position_Head 0
#define MUIV_Listtree_GetEntry_Position_Next (-3)
#define MUIV_Listtree_GetEntry_Position_Parent (-5)
#define MUIV_Listtree_GetEntry_Position_Previous (-4)
#define MUIV_Listtree_GetEntry_Position_Tail (-1)
#define MUIV_Listtree_GetNr_Flags_CountAll 0x8000
#define MUIV_Listtree_GetNr_Flags_CountLevel 0x4000
#define MUIV_Listtree_GetNr_Flags_CountList 0x2000
#define MUIV_Listtree_GetNr_Flags_ListEmpty 0x1000
#define MUIV_Listtree_GetNr_TreeNode_Active (-2)
#define MUIV_Listtree_Insert_Flags_Active 0x2000
#define MUIV_Listtree_Insert_Flags_NextNode 0x1000
#define MUIV_Listtree_Insert_ListNode_Active (-2)
#define MUIV_Listtree_Insert_ListNode_Root 0
#define MUIV_Listtree_Insert_PrevNode_Active (-2)
#define MUIV_Listtree_Insert_PrevNode_Head 0
#define MUIV_Listtree_Insert_PrevNode_Sorted (-4)
#define MUIV_Listtree_Insert_PrevNode_Tail (-1)
#define MUIV_Listtree_Open_ListNode_Active (-2)
#define MUIV_Listtree_Open_ListNode_Parent (-1)
#define MUIV_Listtree_Open_ListNode_Root 0
#define MUIV_Listtree_Open_TreeNode_Active (-2)
#define MUIV_Listtree_Open_TreeNode_All (-3)
#define MUIV_Listtree_Open_TreeNode_Head 0
#define MUIV_Listtree_Open_TreeNode_Tail (-1)
#define MUIV_Listtree_Remove_ListNode_Active (-2)
#define MUIV_Listtree_Remove_ListNode_Root 0
#define MUIV_Listtree_Remove_TreeNode_Active (-2)
#define MUIV_Listtree_Remove_TreeNode_All (-3)
#define MUIV_Listtree_Remove_TreeNode_Head 0
#define MUIV_Listtree_Remove_TreeNode_Tail (-1)
#define MUIV_Listtree_Rename_Flags_NoRefresh 0x200
#define MUIV_Listtree_Rename_Flags_User 0x100
#define MUIV_Listtree_Rename_TreeNode_Active (-2)
#define MUIV_Listtree_SetDropMark_Values_None 0
#define MUIV_Listtree_TestPos_Result_Flags_Above 1
#define MUIV_Listtree_TestPos_Result_Flags_Below 2
#define MUIV_Listtree_TestPos_Result_Flags_None 0
#define MUIV_Listtree_TestPos_Result_Flags_Onto 3
#define MUIV_Listtree_TestPos_Result_Flags_Sorted 4
struct MUIS_Listtree_TreeNode { IPTR tn_Private1, tn_Private2; STRPTR tn_Name; UWORD tn_Flags; APTR tn_User; };
struct MUIS_Listtree_TestPos_Result { APTR tpr_TreeNode; UWORD tpr_Flags; LONG tpr_ListEntry; UWORD tpr_ListFlags; };
struct MUIP_Listtree_Insert { IPTR MethodID; STRPTR Name; APTR User; APTR ListNode; APTR PrevNode; IPTR Flags; };
struct MUIP_Listtree_GetEntry { IPTR MethodID; APTR Node; IPTR Position; IPTR Flags; };
struct MUIP_Listtree_GetNr { IPTR MethodID; APTR TreeNode; IPTR Flags; };
struct MUIP_Listtree_Remove { IPTR MethodID; APTR ListNode; APTR TreeNode; IPTR Flags; };
struct MUIP_Listtree_Rename { IPTR MethodID; APTR TreeNode; STRPTR NewName; IPTR Flags; };
struct MUIP_Listtree_Open { IPTR MethodID; APTR ListNode; APTR TreeNode; IPTR Flags; };
struct MUIP_Listtree_Close { IPTR MethodID; APTR ListNode; APTR TreeNode; IPTR Flags; };
struct MUIP_Listtree_TestPos { IPTR MethodID; IPTR X, Y; APTR Result; };
struct MUIP_Listtree_SetDropMark { IPTR MethodID; IPTR Entry; IPTR Values; };
struct MUIP_Listtree_FindName { IPTR MethodID; APTR ListNode; STRPTR Name; IPTR Flags; };
struct MUIP_Dataspace_Add { IPTR MethodID; APTR data; IPTR len; IPTR id; };
struct MUIP_Dataspace_Clear { IPTR MethodID; };
struct MUIP_Dataspace_Find { IPTR MethodID; IPTR id; };
struct MUIP_Dataspace_Merge { IPTR MethodID; Object *dataspace; };
struct MUIP_Dataspace_ReadIFF { IPTR MethodID; struct IFFHandle *handle; };
struct MUIP_Dataspace_Remove { IPTR MethodID; IPTR id; };
struct MUIP_Dataspace_WriteIFF { IPTR MethodID; struct IFFHandle *handle; IPTR type; IPTR id; };
struct MUIP_Process_Kill { IPTR MethodID; IPTR maxdelay; };
struct MUIP_Process_Launch { IPTR MethodID; };
struct MUIP_Process_Process { IPTR MethodID; ULONG *kill; Object *proc; };
struct MUIP_Process_Signal { IPTR MethodID; IPTR sigs; };

/* A colour as MUI keeps it: each part 32 bits (0xffffffff full), and a pen
 * spec, the text form of a pen ("r<red>,<green>,<blue>" in hex, "p<MUI pen>",
 * "m<colour map entry>") */
struct MUI_RGBcolor {
    ULONG red, green, blue;
};
struct MUI_PenSpec {
    char buf[32];
};
/* an image spec and a frame spec as text (see Imagedisplay, Framedisplay) */
struct MUI_ImageSpec {
    char buf[64];
};
struct MUI_FrameSpec {
    char buf[8];
};
/* a Palette's colour: the array ends with mpe_ID MUIV_Palette_Entry_End */
struct MUI_Palette_Entry {
    LONG mpe_ID;
    ULONG mpe_Red, mpe_Green, mpe_Blue;
    LONG mpe_Group;
};
#define MUIA_Scale_Horiz 0x8042919aUL
#define MUIA_Register_Frame 0x8042349bUL
#define MUIA_Register_Titles 0x804297ecUL
#define MUIA_Scrollgroup_Contents 0x80421261UL
#define MUIA_Scrollgroup_FreeHoriz 0x804292f3UL
#define MUIA_Scrollgroup_FreeVert 0x804224f2UL
#define MUIA_Scrollgroup_UseWinBorder 0x804284c1UL
#define MUIA_Virtgroup_Height 0x80423038UL
#define MUIA_Virtgroup_Input 0x80427f7eUL
#define MUIA_Virtgroup_Left 0x80429371UL
#define MUIA_Virtgroup_Top 0x80425200UL
#define MUIA_Virtgroup_Width 0x80427c49UL
#define MUIA_Image_FontMatch 0x8042815dUL
#define MUIA_Image_FontMatchHeight 0x80429f26UL
#define MUIA_Image_FontMatchWidth 0x804239bfUL
#define MUIA_Image_FreeHoriz 0x8042da84UL
#define MUIA_Image_FreeVert 0x8042ea28UL
#define MUIA_Image_OldImage 0x80424f3dUL
#define MUIA_Image_Spec 0x804233d5UL
#define MUIA_Image_State 0x8042a3adUL
#define MUIA_Popstring_Button 0x8042d0b9UL
#define MUIA_Popstring_CloseHook 0x804256bfUL
#define MUIA_Popstring_OpenHook 0x80429d00UL
#define MUIA_Popstring_String 0x804239eaUL
#define MUIA_Popstring_Toggle 0x80422b7aUL
#define MUIA_Popobject_Follow 0x80424cb5UL
#define MUIA_Popobject_Light 0x8042a5a3UL
#define MUIA_Popobject_Object 0x804293e3UL
#define MUIA_Popobject_ObjStrHook 0x8042db44UL
#define MUIA_Popobject_StrObjHook 0x8042fbe1UL
#define MUIA_Popobject_Volatile 0x804252ecUL
#define MUIA_Popobject_WindowHook 0x8042f194UL
#define MUIA_Poplist_Array 0x8042084cUL
#define MUIA_Popasl_Active 0x80421b37UL
#define MUIA_Popasl_StartHook 0x8042b703UL
#define MUIA_Popasl_StopHook 0x8042d8d2UL
#define MUIA_Popasl_Type 0x8042df3dUL
#define MUIA_Menuitem_CommandString 0x8042b9ccUL
#define MUIA_Menuitem_Exclude 0x80420bc6UL
#define MUIA_Family_Child 0x8042c696UL
#define MUIA_Family_List 0x80424b9eUL
#define MUIM_Application_AddInputHandler 0x8042f099UL
#define MUIM_Application_RemInputHandler 0x8042e7afUL
#define MUIM_Application_Load 0x8042f90dUL
#define MUIM_Application_Save 0x804227efUL
#define MUIM_Application_AboutMUI 0x8042d21dUL
#define MUIM_Application_OpenConfigWindow 0x804299baUL
#define MUIM_ContextMenuBuild 0x80429d2eUL
#define MUIM_ContextMenuChoice 0x80420f0eUL
#define MUIM_Window_SetCycleChain 0x80426510UL
#define MUIM_Family_AddHead 0x8042e200UL
#define MUIM_Family_AddTail 0x8042d752UL
#define MUIM_Family_Insert 0x80424d34UL
#define MUIM_Family_Remove 0x8042f8a9UL
#define MUIA_Application_MenuAction 0x80428961UL
#define MUIA_Application_HelpFile 0x804293f4UL
#define MUIA_Application_UseCommodities 0x80425ee5UL
#define MUIA_Application_UseRexx 0x80422387UL
#define MUIA_Application_Commands 0x80428648UL
#define MUIA_ContextMenu 0x8042b704UL
#define MUIA_ContextMenuTrigger 0x8042a2c1UL
#define MUIA_ShowSelState 0x8042caacUL
#define MUIA_Draggable 0x80420b6eUL
#define MUIA_Dropable 0x8042fbceUL
#define MUIA_ObjectID 0x8042d76eUL
#define MUIA_ExportID 0x8042d76eUL
#define MUIA_MaxWidth 0x8042f112UL
#define MUIA_MaxHeight 0x804293e4UL
#define MUIA_HorizDisappear 0x80429615UL
#define MUIA_VertDisappear 0x8042d12fUL
#define MUIA_Slider_Level 0x8042ae3aUL
#define MUIA_Slider_Max 0x8042d78aUL
#define MUIA_Slider_Min 0x8042e404UL
#define MUIA_String_AdvanceOnCR 0x804226deUL
#define MUIA_String_AttachedList 0x80420fd2UL
#define MUIA_String_EditHook 0x80424c33UL
#define MUIA_String_Format 0x80427484UL
#define MUIA_String_Integer 0x80426e8aUL
#define MUIA_String_Secret 0x80428769UL
#define MUIA_Window_CloseGadget 0x8042a110UL
#define MUIA_Window_DepthGadget 0x80421923UL
#define MUIA_Window_DragBar 0x8042045dUL
#define MUIA_Window_SizeGadget 0x8042e33dUL
#define MUIA_Window_Sleep 0x8042e7dbUL

#define MUIV_List_Active_Off (-1)
#define MUIV_List_Active_Top (-2)
#define MUIV_List_Active_Bottom (-3)
#define MUIV_List_Active_Up (-4)
#define MUIV_List_Active_Down (-5)
#define MUIV_List_Active_PageUp (-6)
#define MUIV_List_Active_PageDown (-7)
#define MUIV_List_ConstructHook_String ((struct Hook *)-1)
#define MUIV_List_DestructHook_String ((struct Hook *)-1)
#define MUIV_List_CopyHook_String ((struct Hook *)-1)
#define MUIV_List_CursorType_None 0
#define MUIV_List_CursorType_Bar 1
#define MUIV_List_CursorType_Rect 2
#define MUIV_List_Exchange_Top 0
#define MUIV_List_Exchange_Active (-1)
#define MUIV_List_Exchange_Bottom (-2)
#define MUIV_List_Exchange_Next (-3)
#define MUIV_List_Exchange_Previous (-4)
#define MUIV_List_GetEntry_Active (-1)
#define MUIV_List_Insert_Top 0
#define MUIV_List_Insert_Active (-1)
#define MUIV_List_Insert_Sorted (-2)
#define MUIV_List_Insert_Bottom (-3)
#define MUIV_List_Jump_Top 0
#define MUIV_List_Jump_Active (-1)
#define MUIV_List_Jump_Bottom (-2)
#define MUIV_List_Jump_Down (-3)
#define MUIV_List_Jump_Up (-4)
#define MUIV_List_Move_Top 0
#define MUIV_List_Move_Active (-1)
#define MUIV_List_Move_Bottom (-2)
#define MUIV_List_Move_Next (-3)
#define MUIV_List_Move_Previous (-4)
#define MUIV_List_NextSelected_Start (-1)
#define MUIV_List_NextSelected_End (-1)
#define MUIV_List_Redraw_Active (-1)
#define MUIV_List_Redraw_All (-2)
#define MUIV_List_Redraw_Entry (-3)
#define MUIV_List_Remove_First 0
#define MUIV_List_Remove_Active (-1)
#define MUIV_List_Remove_Last (-2)
#define MUIV_List_Remove_Selected (-3)
#define MUIV_List_Select_Active (-1)
#define MUIV_List_Select_All (-2)
#define MUIV_List_Select_Off 0
#define MUIV_List_Select_On 1
#define MUIV_List_Select_Toggle 2
#define MUIV_List_Select_Ask 3
#define MUIV_List_TestPos_Result_ColumnNone (-1)
#define MUIV_Listview_DragType_None 0
#define MUIV_Listview_DragType_Immediate 1
#define MUIV_Listview_MultiSelect_None 0
#define MUIV_Listview_MultiSelect_Default 1
#define MUIV_Listview_MultiSelect_Shifted 2
#define MUIV_Listview_MultiSelect_Always 3
#define MUIV_Listview_ScrollerPos_Default 0
#define MUIV_Listview_ScrollerPos_Left 1
#define MUIV_Listview_ScrollerPos_Right 2
#define MUIV_Listview_ScrollerPos_None 3
#define MUIV_Cycle_Active_Next (-1)
#define MUIV_Cycle_Active_Prev (-2)
#define MUIV_Group_ActivePage_First 0
#define MUIV_Group_ActivePage_Last (-1)
#define MUIV_Group_ActivePage_Prev (-2)
#define MUIV_Group_ActivePage_Next (-3)
#define MUIV_Group_ActivePage_Advance (-4)
#define MUIV_Scrollbar_Type_Default 0
#define MUIV_Scrollbar_Type_Bottom 1
#define MUIV_Scrollbar_Type_Top 2
#define MUIV_Scrollbar_Type_Sym 3
#define MUIV_String_Format_Left 0
#define MUIV_String_Format_Center 1
#define MUIV_String_Format_Right 2
#define MUIV_Application_Save_ENV ((STRPTR)0)
#define MUIV_Application_Save_ENVARC ((STRPTR)~0)
#define MUIV_Application_Load_ENV ((STRPTR)0)
#define MUIV_Application_Load_ENVARC ((STRPTR)~0)
#define MUIV_Window_Height_MinMax(p) (0 - (p))
#define MUIV_Window_Height_Visible(p) (-100 - (p))
#define MUIV_Window_Height_Screen(p) (-200 - (p))
#define MUIV_Window_Width_MinMax(p) (0 - (p))
#define MUIV_Window_Width_Visible(p) (-100 - (p))
#define MUIV_Window_Width_Screen(p) (-200 - (p))

#define MUIO_Label_SingleFrame (1 << 8)
#define MUIO_Label_DoubleFrame (1 << 9)
#define MUIO_Label_LeftAligned (1 << 10)
#define MUIO_Label_Centered (1 << 11)
#define MUIO_Label_FreeVert (1 << 12)
#define MUIO_NumericButton 16
#define MUIO_Menuitem_CopyStrings (1UL << 30)


/* A list's entries, and where the pointer is in it */
struct MUI_List_TestPos_Result {
    LONG entry;
    WORD column;
    UWORD flags;
    WORD xoffset;
    WORD yoffset;
};
#define MUI_LPR_ABOVE (1 << 0)
#define MUI_LPR_BELOW (1 << 1)
#define MUI_LPR_LEFT (1 << 2)
#define MUI_LPR_RIGHT (1 << 3)

/* An application's own signals and timers (MUIM_Application_AddInputHandler) */
struct MUI_InputHandlerNode {
    struct MinNode ihn_Node;
    Object *ihn_Object;
    union {
        ULONG ihn_sigs;
        struct {
            UWORD ihn_millis;
            UWORD ihn_current;
        } ihn_timer;
    } ihn_stuff;
    ULONG ihn_Flags;
    ULONG ihn_Method;
};
#define ihn_Signals ihn_stuff.ihn_sigs
#define ihn_Millis ihn_stuff.ihn_timer.ihn_millis
#define ihn_Current ihn_stuff.ihn_timer.ihn_current
#define MUIIHNF_TIMER (1 << 0)

/* ---- Their messages (every field a stacked long, as MUI's) ---- */
struct MUIP_List_Clear { IPTR MethodID; };
struct MUIP_List_CreateImage { IPTR MethodID; Object *obj; IPTR flags; };
struct MUIP_List_DeleteImage { IPTR MethodID; APTR listimg; };
struct MUIP_List_Exchange { IPTR MethodID; IPTR pos1; IPTR pos2; };
struct MUIP_List_GetEntry { IPTR MethodID; IPTR pos; APTR *entry; };
struct MUIP_List_Insert { IPTR MethodID; APTR *entries; IPTR count; IPTR pos; };
struct MUIP_List_InsertSingle { IPTR MethodID; APTR entry; IPTR pos; };
struct MUIP_Floattext_Append { IPTR MethodID; STRPTR Text; };
struct MUIP_List_Jump { IPTR MethodID; IPTR pos; };
struct MUIP_List_Move { IPTR MethodID; IPTR from; IPTR to; };
struct MUIP_List_NextSelected { IPTR MethodID; LONG *pos; };
struct MUIP_List_Redraw { IPTR MethodID; IPTR pos; APTR entry; };
struct MUIP_List_Remove { IPTR MethodID; IPTR pos; };
struct MUIP_List_Select { IPTR MethodID; IPTR pos; IPTR seltype; LONG *state; };
struct MUIP_List_Sort { IPTR MethodID; };
struct MUIP_List_TestPos { IPTR MethodID; IPTR x; IPTR y; struct MUI_List_TestPos_Result *res; };
struct MUIP_Numeric_Decrease { IPTR MethodID; IPTR amount; };
struct MUIP_Numeric_Increase { IPTR MethodID; IPTR amount; };
struct MUIP_Numeric_ScaleToValue { IPTR MethodID; IPTR scalemin; IPTR scalemax; IPTR scale; };
struct MUIP_Numeric_SetDefault { IPTR MethodID; };
struct MUIP_Numeric_Stringify { IPTR MethodID; IPTR value; };
struct MUIP_Numeric_ValueToScale { IPTR MethodID; IPTR scalemin; IPTR scalemax; };
struct MUIP_Popstring_Close { IPTR MethodID; IPTR result; };
struct MUIP_Popstring_Open { IPTR MethodID; };
struct MUIP_Application_AddInputHandler { IPTR MethodID; struct MUI_InputHandlerNode *ihnode; };
struct MUIP_Application_RemInputHandler { IPTR MethodID; struct MUI_InputHandlerNode *ihnode; };
struct MUIP_Family_AddHead { IPTR MethodID; Object *obj; };
struct MUIP_Family_AddTail { IPTR MethodID; Object *obj; };
struct MUIP_Family_Insert { IPTR MethodID; Object *obj; Object *pred; };
struct MUIP_Family_Remove { IPTR MethodID; Object *obj; };

/* ---- The calls ---- */
#ifdef GFOPENMUI_HOST
Object *MUI_NewObjectA(CONST_STRPTR classname, struct TagItem *tags);
Object *MUI_NewObject(CONST_STRPTR classname, ...);
Object *MUI_MakeObjectA(LONG type, IPTR *params);
Object *MUI_MakeObject(LONG type, ...);
void MUI_DisposeObject(Object *obj);
struct IClass *MUI_GetClass(CONST_STRPTR classname);
void MUI_FreeClass(struct IClass *cl);
struct MUI_CustomClass *MUI_CreateCustomClass(struct Library *base, CONST_STRPTR supername,
                                              struct MUI_CustomClass *supermcc, LONG datasize, APTR dispatcher);
BOOL MUI_DeleteCustomClass(struct MUI_CustomClass *mcc);
LONG MUI_Error(void);
LONG MUI_SetError(LONG num);
void MUI_RequestIDCMP(Object *obj, ULONG flags);
void MUI_RejectIDCMP(Object *obj, ULONG flags);
void MUI_Redraw(Object *obj, ULONG flags);
#endif

/* ---- The object macros ---- */
#define MUIOBJMACRO_START(class) MUI_NewObject(class
#define BOOPSIOBJMACRO_START(cl) NewObject(cl, NULL
#define ApplicationObject MUIOBJMACRO_START(MUIC_Application)
#define WindowObject MUIOBJMACRO_START(MUIC_Window)
#define TextObject MUIOBJMACRO_START(MUIC_Text)
#define StringObject MUIOBJMACRO_START(MUIC_String)
#define MenustripObject MUIOBJMACRO_START(MUIC_Menustrip)
#define MenuObject MUIOBJMACRO_START(MUIC_Menu)
#define MenuitemObject MUIOBJMACRO_START(MUIC_Menuitem)
#define RectangleObject MUIOBJMACRO_START(MUIC_Rectangle)
#define GroupObject MUIOBJMACRO_START(MUIC_Group)
#define VGroup MUIOBJMACRO_START(MUIC_Group)
#define HGroup MUIOBJMACRO_START(MUIC_Group), MUIA_Group_Horiz, TRUE
#define ColGroup(cols) MUIOBJMACRO_START(MUIC_Group), MUIA_Group_Columns, (cols)
#define RowGroup(rows) MUIOBJMACRO_START(MUIC_Group), MUIA_Group_Rows, (rows)
#define End TAG_DONE)

#define Child MUIA_Group_Child
#define SubWindow MUIA_Application_Window
#define WindowContents MUIA_Window_RootObject

#define NoFrame MUIA_Frame, MUIV_Frame_None
#define ButtonFrame MUIA_Frame, MUIV_Frame_Button
#define TextFrame MUIA_Frame, MUIV_Frame_Text
#define StringFrame MUIA_Frame, MUIV_Frame_String
#define ReadListFrame MUIA_Frame, MUIV_Frame_ReadList
#define InputListFrame MUIA_Frame, MUIV_Frame_InputList
#define GroupFrame MUIA_Frame, MUIV_Frame_Group
#define GroupFrameT(s) MUIA_Frame, MUIV_Frame_Group, MUIA_FrameTitle, (s)

#define GroupSpacing(x) MUIA_Group_Spacing, (x)
#define HVSpace MUI_NewObject(MUIC_Rectangle, TAG_DONE)
#define HSpace(x) MUI_MakeObject(MUIO_HSpace, (x))
#define VSpace(x) MUI_MakeObject(MUIO_VSpace, (x))
#define HBar MUI_MakeObject(MUIO_HBar, 0)
#define SimpleButton(label) MUI_MakeObject(MUIO_Button, (IPTR)(label))
#define Label(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), 0)
#define KeyButton(name, key) TextObject, ButtonFrame, MUIA_Font, MUIV_Font_Button, \
    MUIA_Text_Contents, (name), MUIA_Text_PreParse, "\33c", MUIA_Text_HiChar, (key), \
    MUIA_ControlChar, (key), MUIA_InputMode, MUIV_InputMode_RelVerify, MUIA_Background, 2, TAG_DONE)

/* get() and set(), as MUI's own headers give them */
#define get(obj, attr, store) GetAttr((ULONG)(attr), (Object *)(obj), (IPTR *)(store))
#define set(obj, attr, value) SetAttrs((APTR)(obj), (ULONG)(attr), (IPTR)(value), TAG_DONE)
#define nnset(obj, attr, value) SetAttrs((APTR)(obj), MUIA_NoNotify, TRUE, (ULONG)(attr), (IPTR)(value), TAG_DONE)
/* the same in capitals, and XGET: an attribute's value as an expression (Zune's names) */
#define SET(obj, attr, value) set(obj, attr, value)
#define NNSET(obj, attr, value) nnset(obj, attr, value)
#ifdef GFOPENMUI_HOST
static inline IPTR mui_xget_(Object *obj, ULONG attr)
{
    IPTR v = 0;
    GetAttr(attr, obj, &v);
    return v;
}
#define XGET(obj, attr) mui_xget_((Object *)(obj), (ULONG)(attr))
#else
#define XGET(obj, attr) ({ IPTR xget_v_ = 0; GetAttr((ULONG)(attr), (Object *)(obj), (ULONG *)&xget_v_); xget_v_; })
#endif

/* ---- The other classes' macros ---- */
#define FamilyObject MUIOBJMACRO_START(MUIC_Family)
#define ListObject MUIOBJMACRO_START(MUIC_List)
#define FloattextObject MUIOBJMACRO_START(MUIC_Floattext)
#define VolumelistObject MUIOBJMACRO_START(MUIC_Volumelist)
#define DirlistObject MUIOBJMACRO_START(MUIC_Dirlist)
#define ListviewObject MUIOBJMACRO_START(MUIC_Listview)
#define CycleObject MUIOBJMACRO_START(MUIC_Cycle)
#define RadioObject MUIOBJMACRO_START(MUIC_Radio)
#define NumericObject MUIOBJMACRO_START(MUIC_Numeric)
#define NumericbuttonObject MUIOBJMACRO_START(MUIC_Numericbutton)
#define KnobObject MUIOBJMACRO_START(MUIC_Knob)
#define LevelmeterObject MUIOBJMACRO_START(MUIC_Levelmeter)
#define SliderObject MUIOBJMACRO_START(MUIC_Slider)
#define PropObject MUIOBJMACRO_START(MUIC_Prop)
#define ScrollbarObject MUIOBJMACRO_START(MUIC_Scrollbar)
#define GaugeObject MUIOBJMACRO_START(MUIC_Gauge)
#define ScaleObject MUIOBJMACRO_START(MUIC_Scale)
#define RegisterObject MUIOBJMACRO_START(MUIC_Register)
#define VirtgroupObject MUIOBJMACRO_START(MUIC_Virtgroup)
#define ScrollgroupObject MUIOBJMACRO_START(MUIC_Scrollgroup)
#define BalanceObject MUIOBJMACRO_START(MUIC_Balance)
#define ImageObject MUIOBJMACRO_START(MUIC_Image)
#define BitmapObject MUIOBJMACRO_START(MUIC_Bitmap)
#define BodychunkObject MUIOBJMACRO_START(MUIC_Bodychunk)
#define PopstringObject MUIOBJMACRO_START(MUIC_Popstring)
#define PopobjectObject MUIOBJMACRO_START(MUIC_Popobject)
#define PoplistObject MUIOBJMACRO_START(MUIC_Poplist)
#define PopaslObject MUIOBJMACRO_START(MUIC_Popasl)
#define PopscreenObject MUIOBJMACRO_START(MUIC_Popscreen)
#define ColorfieldObject MUIOBJMACRO_START(MUIC_Colorfield)
#define ColoradjustObject MUIOBJMACRO_START(MUIC_Coloradjust)
#define PendisplayObject MUIOBJMACRO_START(MUIC_Pendisplay)
#define PenadjustObject MUIOBJMACRO_START(MUIC_Penadjust)
#define PoppenObject MUIOBJMACRO_START(MUIC_Poppen)
#define PaletteObject MUIOBJMACRO_START(MUIC_Palette)
#define ImagedisplayObject MUIOBJMACRO_START(MUIC_Imagedisplay)
#define ImageadjustObject MUIOBJMACRO_START(MUIC_Imageadjust)
#define FramedisplayObject MUIOBJMACRO_START(MUIC_Framedisplay)
#define FrameadjustObject MUIOBJMACRO_START(MUIC_Frameadjust)
#define PopimageObject MUIOBJMACRO_START(MUIC_Popimage)
#define PopframeObject MUIOBJMACRO_START(MUIC_Popframe)
#define PixmapObject MUIOBJMACRO_START(MUIC_Pixmap)
#define DtpicObject MUIOBJMACRO_START(MUIC_Dtpic)
#define BoopsiObject MUIOBJMACRO_START(MUIC_Boopsi)
#define ScrollbuttonObject MUIOBJMACRO_START(MUIC_Scrollbutton)
#define SemaphoreObject MUIOBJMACRO_START(MUIC_Semaphore)
#define DataspaceObject MUIOBJMACRO_START(MUIC_Dataspace)
#define ProcessObject MUIOBJMACRO_START(MUIC_Process)
#define SettingsgroupObject MUIOBJMACRO_START(MUIC_Settingsgroup)
#define SettingsObject MUIOBJMACRO_START(MUIC_Settings)
#define ConfigdataObject MUIOBJMACRO_START(MUIC_Configdata)
#define AboutmuiObject MUIOBJMACRO_START(MUIC_Aboutmui)
#define CrawlingObject MUIOBJMACRO_START(MUIC_Crawling)
#define BetterStringObject MUIOBJMACRO_START(MUIC_BetterString)
#define NListObject MUIOBJMACRO_START(MUIC_NList)
#define NListviewObject MUIOBJMACRO_START(MUIC_NListview)
#define NListtreeObject MUIOBJMACRO_START(MUIC_NListtree)
#define TextEditorObject MUIOBJMACRO_START(MUIC_TextEditor)
#define ListtreeObject MUIOBJMACRO_START(MUIC_Listtree)

#define VGroupV MUIOBJMACRO_START(MUIC_Virtgroup)
#define HGroupV MUIOBJMACRO_START(MUIC_Virtgroup), MUIA_Group_Horiz, TRUE
#define ColGroupV(cols) MUIOBJMACRO_START(MUIC_Virtgroup), MUIA_Group_Columns, (cols)
#define RowGroupV(rows) MUIOBJMACRO_START(MUIC_Virtgroup), MUIA_Group_Rows, (rows)
#define PageGroup MUIOBJMACRO_START(MUIC_Group), MUIA_Group_PageMode, TRUE
#define RegisterGroup(titles) MUIOBJMACRO_START(MUIC_Register), MUIA_Register_Titles, (titles)

#define ImageButtonFrame MUIA_Frame, MUIV_Frame_ImageButton
#define GaugeFrame MUIA_Frame, MUIV_Frame_Gauge
#define PropFrame MUIA_Frame, MUIV_Frame_Prop
#define SliderFrame MUIA_Frame, MUIV_Frame_Slider
#define VirtualFrame MUIA_Frame, MUIV_Frame_Virtual
#define InnerSpacing(h, v) MUIA_InnerLeft, (h), MUIA_InnerRight, (h), MUIA_InnerTop, (v), MUIA_InnerBottom, (v)

#define Label1(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_SingleFrame)
#define Label2(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_DoubleFrame)
#define LLabel(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_LeftAligned)
#define LLabel1(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_LeftAligned | MUIO_Label_SingleFrame)
#define LLabel2(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_LeftAligned | MUIO_Label_DoubleFrame)
#define CLabel(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_Centered)
#define CLabel1(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_Centered | MUIO_Label_SingleFrame)
#define CLabel2(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_Centered | MUIO_Label_DoubleFrame)
#define KeyLabel(label, key) MUI_MakeObject(MUIO_Label, (IPTR)(label), (IPTR)(key))
#define KeyLabel1(label, key) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_SingleFrame | (key))
#define KeyLabel2(label, key) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_DoubleFrame | (key))
#define FreeLabel(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_FreeVert)
#define FreeLLabel(label) MUI_MakeObject(MUIO_Label, (IPTR)(label), MUIO_Label_FreeVert | MUIO_Label_LeftAligned)

#define CheckMark(selected) ImageObject, ImageButtonFrame, MUIA_InputMode, MUIV_InputMode_Toggle, \
    MUIA_Image_Spec, MUII_CheckMark, MUIA_Image_FreeVert, TRUE, MUIA_Selected, (selected), \
    MUIA_Background, MUII_ButtonBack, MUIA_ShowSelState, FALSE, TAG_DONE)
#define KeyCheckMark(selected, key) ImageObject, ImageButtonFrame, MUIA_InputMode, MUIV_InputMode_Toggle, \
    MUIA_Image_Spec, MUII_CheckMark, MUIA_Image_FreeVert, TRUE, MUIA_Selected, (selected), \
    MUIA_Background, MUII_ButtonBack, MUIA_ShowSelState, FALSE, MUIA_ControlChar, (key), TAG_DONE)
#define PopButton(img) MUI_MakeObject(MUIO_PopButton, (IPTR)(img))
#define SimpleCycle(entries) MUIOBJMACRO_START(MUIC_Cycle), MUIA_Cycle_Entries, (entries), TAG_DONE)
#define Cycle(entries) SimpleCycle(entries)
#define KeyCycle(entries, key) MUIOBJMACRO_START(MUIC_Cycle), MUIA_Cycle_Entries, (entries), MUIA_ControlChar, (key), TAG_DONE)
#define Radio(name, array) MUIOBJMACRO_START(MUIC_Radio), GroupFrameT(name), MUIA_Radio_Entries, (array), TAG_DONE)
#define KeyRadio(name, array, key) MUIOBJMACRO_START(MUIC_Radio), GroupFrameT(name), MUIA_Radio_Entries, (array), \
    MUIA_ControlChar, (key), TAG_DONE)
#define Slider(min, max, level) MUIOBJMACRO_START(MUIC_Slider), MUIA_Numeric_Min, (min), MUIA_Numeric_Max, (max), \
    MUIA_Numeric_Value, (level), TAG_DONE)
#define KeySlider(min, max, level, key) MUIOBJMACRO_START(MUIC_Slider), MUIA_Numeric_Min, (min), \
    MUIA_Numeric_Max, (max), MUIA_Numeric_Value, (level), MUIA_ControlChar, (key), TAG_DONE)
#define String(contents, maxlen) StringObject, StringFrame, MUIA_String_MaxLen, (maxlen), \
    MUIA_String_Contents, (contents), TAG_DONE)
#define KeyString(contents, maxlen, key) StringObject, StringFrame, MUIA_String_MaxLen, (maxlen), \
    MUIA_String_Contents, (contents), MUIA_ControlChar, (key), TAG_DONE)
#define HCenter(obj) (HGroup, GroupSpacing(0), Child, HSpace(0), Child, (obj), Child, HSpace(0), TAG_DONE))
#define VCenter(obj) (VGroup, GroupSpacing(0), Child, VSpace(0), Child, (obj), Child, VSpace(0), TAG_DONE))
#define MenuitemBar MUI_MakeObject(MUIO_Menuitem, (IPTR)NM_BARLABEL, 0, 0, 0)

#endif
