#ifndef REACTION_REACTION_H
#define REACTION_REACTION_H
/*
 * OpenNDK: what every ReAction class shares: the base of their tag space.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* Each class's tags are an offset from here */
#define REACTION_Dummy		(TAG_USER + 0x5000000)

/* Tags any ReAction object may be given */
#define REACTION_TextAttr	(REACTION_Dummy + 5)	/* struct TextAttr *: the font */
#define REACTION_ChangePrefs	(REACTION_Dummy + 6)	/* the user's settings changed */
#define REACTION_SpecialPens	(REACTION_Dummy + 7)	/* struct SpecialPens * */

/* Extra pens for the 3D look */
struct SpecialPens
{
	WORD	sp_Version;	/* 0 */
	LONG	sp_DarkPen;	/* -1: none */
	LONG	sp_LightPen;	/* -1: none */
};

/* More names from the 3.2 interface */
#define REACTION_Justification	(REACTION_Dummy + 8)

/* ALL_REACTION_CLASSES: every ReAction class's header and proto header */
#ifdef ALL_REACTION_CLASSES
#ifndef PROTO_LAYOUT_H
#include <proto/layout.h>
#endif
#ifndef GADGETS_LAYOUT_H
#include <gadgets/layout.h>
#endif
#ifndef PROTO_BUTTON_H
#include <proto/button.h>
#endif
#ifndef GADGETS_BUTTON_H
#include <gadgets/button.h>
#endif
#ifndef PROTO_CHECKBOX_H
#include <proto/checkbox.h>
#endif
#ifndef GADGETS_CHECKBOX_H
#include <gadgets/checkbox.h>
#endif
#ifndef PROTO_CHOOSER_H
#include <proto/chooser.h>
#endif
#ifndef GADGETS_CHOOSER_H
#include <gadgets/chooser.h>
#endif
#ifndef PROTO_CLICKTAB_H
#include <proto/clicktab.h>
#endif
#ifndef GADGETS_CLICKTAB_H
#include <gadgets/clicktab.h>
#endif
#ifndef PROTO_FUELGAUGE_H
#include <proto/fuelgauge.h>
#endif
#ifndef GADGETS_FUELGAUGE_H
#include <gadgets/fuelgauge.h>
#endif
#ifndef PROTO_GETFILE_H
#include <proto/getfile.h>
#endif
#ifndef GADGETS_GETFILE_H
#include <gadgets/getfile.h>
#endif
#ifndef PROTO_GETFONT_H
#include <proto/getfont.h>
#endif
#ifndef GADGETS_GETFONT_H
#include <gadgets/getfont.h>
#endif
#ifndef PROTO_GETSCREENMODE_H
#include <proto/getscreenmode.h>
#endif
#ifndef GADGETS_GETSCREENMODE_H
#include <gadgets/getscreenmode.h>
#endif
#ifndef PROTO_INTEGER_H
#include <proto/integer.h>
#endif
#ifndef GADGETS_INTEGER_H
#include <gadgets/integer.h>
#endif
#ifndef PROTO_LISTBROWSER_H
#include <proto/listbrowser.h>
#endif
#ifndef GADGETS_LISTBROWSER_H
#include <gadgets/listbrowser.h>
#endif
#ifndef PROTO_PALETTE_H
#include <proto/palette.h>
#endif
#ifndef GADGETS_PALETTE_H
#include <gadgets/palette.h>
#endif
#ifndef PROTO_RADIOBUTTON_H
#include <proto/radiobutton.h>
#endif
#ifndef GADGETS_RADIOBUTTON_H
#include <gadgets/radiobutton.h>
#endif
#ifndef PROTO_SCROLLER_H
#include <proto/scroller.h>
#endif
#ifndef GADGETS_SCROLLER_H
#include <gadgets/scroller.h>
#endif
#ifndef PROTO_SLIDER_H
#include <proto/slider.h>
#endif
#ifndef GADGETS_SLIDER_H
#include <gadgets/slider.h>
#endif
#ifndef PROTO_SPACE_H
#include <proto/space.h>
#endif
#ifndef GADGETS_SPACE_H
#include <gadgets/space.h>
#endif
#ifndef PROTO_SPEEDBAR_H
#include <proto/speedbar.h>
#endif
#ifndef GADGETS_SPEEDBAR_H
#include <gadgets/speedbar.h>
#endif
#ifndef PROTO_STRING_H
#include <proto/string.h>
#endif
#ifndef GADGETS_STRING_H
#include <gadgets/string.h>
#endif
#ifndef PROTO_BEVEL_H
#include <proto/bevel.h>
#endif
#ifndef IMAGES_BEVEL_H
#include <images/bevel.h>
#endif
#ifndef PROTO_BITMAP_H
#include <proto/bitmap.h>
#endif
#ifndef IMAGES_BITMAP_H
#include <images/bitmap.h>
#endif
#ifndef PROTO_DRAWLIST_H
#include <proto/drawlist.h>
#endif
#ifndef IMAGES_DRAWLIST_H
#include <images/drawlist.h>
#endif
#ifndef PROTO_GLYPH_H
#include <proto/glyph.h>
#endif
#ifndef IMAGES_GLYPH_H
#include <images/glyph.h>
#endif
#ifndef PROTO_LABEL_H
#include <proto/label.h>
#endif
#ifndef IMAGES_LABEL_H
#include <images/label.h>
#endif
#ifndef PROTO_PENMAP_H
#include <proto/penmap.h>
#endif
#ifndef IMAGES_PENMAP_H
#include <images/penmap.h>
#endif
#ifndef PROTO_WINDOW_H
#include <proto/window.h>
#endif
#ifndef CLASSES_WINDOW_H
#include <classes/window.h>
#endif
#ifndef PROTO_REQUESTER_H
#include <proto/requester.h>
#endif
#ifndef CLASSES_REQUESTER_H
#include <classes/requester.h>
#endif
#ifndef PROTO_AREXX_H
#include <proto/arexx.h>
#endif
#ifndef CLASSES_AREXX_H
#include <classes/arexx.h>
#endif
#endif /* ALL_REACTION_CLASSES */

/* ALL_REACTION_MACROS: the object-building macros */
#ifdef ALL_REACTION_MACROS
#ifndef REACTION_REACTION_MACROS_H
#include <reaction/reaction_macros.h>
#endif
#endif /* ALL_REACTION_MACROS */

#endif /* REACTION_REACTION_H */
