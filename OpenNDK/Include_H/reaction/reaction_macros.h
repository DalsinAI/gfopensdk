#ifndef REACTION_REACTION_MACROS_H
#define REACTION_REACTION_MACROS_H
/*
 * OpenNDK: shorthand for building ReAction object trees in one expression.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 *
 * Each XxxObject opens a NewObject() call on the class (its library must
 * be open, or the class made by name), the tags follow, and an End macro
 * closes it, the result an Object *. The *_GetClass() calls come from
 * the classes' proto headers.
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif

/* Closing a NewObject() call */
#define End		TAG_END)
#define EndObject	TAG_END)

/* Classes */
#define WindowObject		(Object *)NewObject(WINDOW_GetClass(), NULL
#define RequesterObject		(Object *)NewObject(REQUESTER_GetClass(), NULL
#define ARexxObject		(Object *)NewObject(AREXX_GetClass(), NULL

#define WindowEnd		TAG_END)
#define EndWindow		TAG_END)
#define RequesterEnd		TAG_END)
#define ARexxEnd		TAG_END)

/* Gadgets */
#define ButtonObject		(Object *)NewObject(BUTTON_GetClass(), NULL
#define CheckBoxObject		(Object *)NewObject(CHECKBOX_GetClass(), NULL
#define ChooserObject		(Object *)NewObject(CHOOSER_GetClass(), NULL
#define ClickTabObject		(Object *)NewObject(CLICKTAB_GetClass(), NULL
#define DateBrowserObject	(Object *)NewObject(DATEBROWSER_GetClass(), NULL
#define FuelGaugeObject		(Object *)NewObject(FUELGAUGE_GetClass(), NULL
#define GetColorObject		(Object *)NewObject(GETCOLOR_GetClass(), NULL
#define GetFileObject		(Object *)NewObject(GETFILE_GetClass(), NULL
#define GetFontObject		(Object *)NewObject(GETFONT_GetClass(), NULL
#define GetScreenModeObject	(Object *)NewObject(GETSCREENMODE_GetClass(), NULL
#define IntegerObject		(Object *)NewObject(INTEGER_GetClass(), NULL
#define LayoutObject		(Object *)NewObject(LAYOUT_GetClass(), NULL
#define ListBrowserObject	(Object *)NewObject(LISTBROWSER_GetClass(), NULL
#define PageObject		(Object *)NewObject(PAGE_GetClass(), NULL
#define PaletteObject		(Object *)NewObject(PALETTE_GetClass(), NULL
#define RadioButtonObject	(Object *)NewObject(RADIOBUTTON_GetClass(), NULL
#define ScrollerObject		(Object *)NewObject(SCROLLER_GetClass(), NULL
#define SketchBoardObject	(Object *)NewObject(SKETCHBOARD_GetClass(), NULL
#define SliderObject		(Object *)NewObject(SLIDER_GetClass(), NULL
#define SpaceObject		(Object *)NewObject(SPACE_GetClass(), NULL
#define SpeedBarObject		(Object *)NewObject(SPEEDBAR_GetClass(), NULL
#define StringObject		(Object *)NewObject(STRING_GetClass(), NULL
#define TabsObject		(Object *)NewObject(TABS_GetClass(), NULL
#define TextEditorObject	(Object *)NewObject(TEXTEDITOR_GetClass(), NULL
#define VirtualObject		(Object *)NewObject(VIRTUAL_GetClass(), NULL
#define ColorWheelObject	(Object *)NewObject(NULL, "colorwheel.gadget"
#define GradientSliderObject	(Object *)NewObject(NULL, "gradientslider.gadget"

#define ButtonEnd		TAG_END)
#define CheckBoxEnd		TAG_END)
#define ChooserEnd		TAG_END)
#define ClickTabEnd		TAG_END)
#define DateBrowserEnd		TAG_END)
#define FuelGaugeEnd		TAG_END)
#define GetColorEnd		TAG_END)
#define GetFileEnd		TAG_END)
#define GetFontEnd		TAG_END)
#define GetScreenModeEnd	TAG_END)
#define IntegerEnd		TAG_END)
#define LayoutEnd		TAG_END)
#define ListBrowserEnd		TAG_END)
#define PageEnd			TAG_END)
#define PaletteEnd		TAG_END)
#define RadioButtonEnd		TAG_END)
#define ScrollerEnd		TAG_END)
#define SketchBoardEnd		TAG_END)
#define SliderEnd		TAG_END)
#define SpaceEnd		TAG_END)
#define SpeedBarEnd		TAG_END)
#define StringEnd		TAG_END)
#define TabsEnd			TAG_END)
#define TextEditorEnd		TAG_END)
#define VirtualEnd		TAG_END)
#define ColorWheelEnd		TAG_END)
#define GradientSliderEnd	TAG_END)

/* Images */
#define BevelObject		(Object *)NewObject(BEVEL_GetClass(), NULL
#define BitMapObject		(Object *)NewObject(BITMAP_GetClass(), NULL
#define DrawListObject		(Object *)NewObject(DRAWLIST_GetClass(), NULL
#define GlyphObject		(Object *)NewObject(GLYPH_GetClass(), NULL
#define LabelObject		(Object *)NewObject(LABEL_GetClass(), NULL
#define LEDObject		(Object *)NewObject(LED_GetClass(), NULL
#define PenMapObject		(Object *)NewObject(PENMAP_GetClass(), NULL

#define BevelEnd		TAG_END)
#define BitMapEnd		TAG_END)
#define DrawListEnd		TAG_END)
#define GlyphEnd		TAG_END)
#define LabelEnd		TAG_END)
#define LEDEnd			TAG_END)
#define PenMapEnd		TAG_END)
#define EndImage		TAG_END)

/* Groups: a layout laid out across or down */
#define HLayoutObject		LayoutObject, LAYOUT_Orientation, LAYOUT_ORIENT_HORIZ
#define VLayoutObject		LayoutObject, LAYOUT_Orientation, LAYOUT_ORIENT_VERT
#define HGroupObject		HLayoutObject
#define VGroupObject		VLayoutObject
#define EndGroup		TAG_END)

/* Children of a layout */
#define StartMember		LAYOUT_AddChild
#define StartImage		LAYOUT_AddImage
#define EndMember		TAG_END)
#define StartHGroup		LAYOUT_AddChild, HLayoutObject
#define StartVGroup		LAYOUT_AddChild, VLayoutObject
#define StartHLayout		StartHGroup
#define StartVLayout		StartVGroup
#define MemberLabel(text)	CHILD_Label, LabelObject, LABEL_Text, (text), LabelEnd
#define Label(text)		MemberLabel(text)

/* A few common gadgets in one go */
#define Button(text, id)	ButtonObject, GA_ID, (id), GA_Text, (text), GA_RelVerify, TRUE, ButtonEnd
#define PushButton(text, id)	ButtonObject, GA_ID, (id), GA_Text, (text), GA_RelVerify, TRUE, \
				BUTTON_PushButton, TRUE, ButtonEnd
#define TextLine(text)		ButtonObject, GA_Text, (text), GA_ReadOnly, TRUE, \
				BUTTON_BevelStyle, BVS_NONE, BUTTON_Transparent, TRUE, ButtonEnd

/* window.class's methods, through amiga.lib's DoMethod() */
#define RA_OpenWindow(win)	((struct Window *)DoMethod((Object *)(win), WM_OPEN, NULL))
#define RA_CloseWindow(win)	DoMethod((Object *)(win), WM_CLOSE, NULL)
#define RA_HandleInput(win, codeptr) DoMethod((Object *)(win), WM_HANDLEINPUT, (codeptr))
#define RA_Iconify(win)		DoMethod((Object *)(win), WM_ICONIFY, NULL)
#define RA_Uniconify(win)	RA_OpenWindow(win)

/* requester.class's method */
#define RA_OpenRequester(req, win) DoMethod((Object *)(req), RM_OPENREQ, NULL, (win), NULL)

/* Fill in a hook for a ReAction class */
#define RA_SetUpHook(hook, func, data) \
	((hook).h_Entry = (HOOKFUNC)(func), (hook).h_SubEntry = NULL, (hook).h_Data = (APTR)(data))

/* More names from the 3.2 interface */
#define BAligned		1
#define ButtonFrame		1
#define CheckMark		7
#define DropBoxFrame		5
#define DropDown		5
#define EvenSized		1
#define GetFile			9
#define GetPath			10
#define GetScreen		11
#define GetTime			12
#define GroupFrame		2
#define HBarFrame		6
#define HCentered		2
#define LAligned		0
#define MxFrame			10
#define PopUp			6
#define RAligned		1
#define RadioFrame		10
#define RidgeFrame		3
#define StandardFrame		11
#define StringFrame		3
#define TAligned		0
#define ThinFrame		0
#define VBarFrame		7
#define VCentered		2

/* older and shorter names */
#define ArrowUp			GLYPH_UPARROW
#define ArrowDown		GLYPH_DOWNARROW
#define ArrowLeft		GLYPH_LEFTARROW
#define ArrowRight		GLYPH_RIGHTARROW
#define ClickTabsObject		ClickTabObject
#define ClickTabsEnd		End
#define FuelObject		FuelGaugeObject
#define MxObject		RadioButtonObject
#define EndHGroup		End
#define EndVGroup		End

/* objects of classes outside the set, by name or by their GetClass call */
#define DropDownObject		NewObject(CHOOSER_GetClass(), NULL, CHOOSER_DropDown, TRUE
#define PopUpObject		NewObject(CHOOSER_GetClass(), NULL, CHOOSER_PopUp, TRUE
#define ToggleObject		NewObject(NULL, "button.gadget", GA_ToggleSelect, TRUE
#define BoingBallObject		NewObject(NULL, "boingball.image"
#define BoingBallEnd		End
#define GradientObject		NewObject(NULL, "gradientslider.gadget"
#define LedObject		NewObject(NULL, "led.image"
#define LedEnd			End
#define StatusObject		NewObject(STATUSBAR_GetClass(), NULL
#define StatusEnd		End
#define StatusbarEnd		End
#define TextFieldObject		NewObject(TEXTFIELD_GetClass(), NULL
#define TextFieldEnd		End

/* layout spacing and alignment tags */
#define LOffset(p)		LAYOUT_LeftSpacing, (p)
#define TOffset(p)		LAYOUT_TopSpacing, (p)
#define ROffset(p)		LAYOUT_RightSpacing, (p)
#define BOffset(p)		LAYOUT_BottomSpacing, (p)
#define Offset(x1, y1, x2, y2)	LAYOUT_LeftSpacing, (x1), LAYOUT_TopSpacing, (y1), LAYOUT_RightSpacing, (x2), LAYOUT_BottomSpacing, (y2)
#define Spacing(p)		LAYOUT_InnerSpacing, (p)
#define HAlign(p)		LAYOUT_HorizAlignment, (p)
#define VAlign(p)		LAYOUT_VertAlignment, (p)

/* a string gadget, with a label, and with a button beside it */
#define String(text, id, maxchars)	StringObject, STRINGA_TextVal, (text), STRINGA_MaxChars, (maxchars), GA_ID, (id), GA_RelVerify, TRUE, GA_TabCycle, TRUE, StringEnd
#define LabelString(text, id, maxchars, label)	String(text, id, maxchars), Label(label)
#define LabelTextLine(text, label)	TextLine(text), Label(label)
#define PopString(text, id, maxchars, image)	LAYOUT_AddChild, HLayoutObject, String(text, 0, maxchars), ButtonObject, BUTTON_AutoButton, (image), GA_RelVerify, TRUE, GA_ID, (id), ButtonEnd, LayoutEnd

/* struct NewMenu lines */
#define Title(t)		{ NM_TITLE, (t), NULL, 0, 0, NULL }
#define Item(t, s, i)		{ NM_ITEM, (t), (s), 0, 0, (APTR)(i) }
#define ItemBar			{ NM_ITEM, NM_BARLABEL, NULL, 0, 0, NULL }
#define SubItem(t, s, i)	{ NM_SUB, (t), (s), 0, 0, (APTR)(i) }
#define SubBar			{ NM_SUB, NM_BARLABEL, NULL, 0, 0, NULL }
#define EndMenu			{ NM_END, NULL, NULL, 0, 0, NULL }

/* ARexx class calls */
#define RA_HandleRexx(obj)	DoMethod((obj), AM_HANDLEEVENT)
#define RA_FlushRexx(obj)	DoMethod((obj), AM_FLUSH)

#endif /* REACTION_REACTION_MACROS_H */
