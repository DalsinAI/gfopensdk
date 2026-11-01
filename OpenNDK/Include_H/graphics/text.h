#ifndef GRAPHICS_TEXT_H
#define GRAPHICS_TEXT_H
/*
 * OpenNDK: fonts and the text rendering structures.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif

#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

/* ta_Style / tf_Style */
#define FS_NORMAL	0
#define FSB_UNDERLINED	0
#define FSF_UNDERLINED	(1 << FSB_UNDERLINED)
#define FSB_BOLD	1
#define FSF_BOLD	(1 << FSB_BOLD)
#define FSB_ITALIC	2
#define FSF_ITALIC	(1 << FSB_ITALIC)
#define FSB_EXTENDED	3
#define FSF_EXTENDED	(1 << FSB_EXTENDED)
#define FSB_COLORFONT	6	/* a ColorTextFont */
#define FSF_COLORFONT	(1 << FSB_COLORFONT)
#define FSB_TAGGED	7	/* a TTextAttr with tags */
#define FSF_TAGGED	(1 << FSB_TAGGED)

/* ta_Flags / tf_Flags */
#define FPB_ROMFONT	0
#define FPF_ROMFONT	(1 << FPB_ROMFONT)
#define FPB_DISKFONT	1
#define FPF_DISKFONT	(1 << FPB_DISKFONT)
#define FPB_REVPATH	2	/* drawn right to left */
#define FPF_REVPATH	(1 << FPB_REVPATH)
#define FPB_TALLDOT	3
#define FPF_TALLDOT	(1 << FPB_TALLDOT)
#define FPB_WIDEDOT	4
#define FPF_WIDEDOT	(1 << FPB_WIDEDOT)
#define FPB_PROPORTIONAL 5
#define FPF_PROPORTIONAL (1 << FPB_PROPORTIONAL)
#define FPB_DESIGNED	6	/* this size was drawn, not scaled */
#define FPF_DESIGNED	(1 << FPB_DESIGNED)
#define FPB_REMOVED	7	/* taken off the system list */
#define FPF_REMOVED	(1 << FPB_REMOVED)

/* What a program asks OpenFont() for */
struct TextAttr
{
    STRPTR ta_Name;
    UWORD  ta_YSize;
    UBYTE  ta_Style;
    UBYTE  ta_Flags;
};

/* The same, with a tag list when FSF_TAGGED is set in tta_Style */
struct TTextAttr
{
    STRPTR          tta_Name;
    UWORD           tta_YSize;
    UBYTE           tta_Style;
    UBYTE           tta_Flags;
    struct TagItem *tta_Tags;
};

/* Tags for a TTextAttr */
#define TA_DeviceDPI	(1 | TAG_USER)	/* (x DPI << 16) | y DPI */

#define MAXFONTMATCHWEIGHT	32767

struct TextFont
{
    struct Message tf_Message;	/* on the font list */
    UWORD          tf_YSize;
    UBYTE          tf_Style;
    UBYTE          tf_Flags;
    UWORD          tf_XSize;
    UWORD          tf_Baseline;
    UWORD          tf_BoldSmear;
    UWORD          tf_Accessors;	/* open count */
    UBYTE          tf_LoChar;
    UBYTE          tf_HiChar;
    APTR           tf_CharData;	/* glyph bitplane */
    UWORD          tf_Modulo;	/* bytes per row of tf_CharData */
    APTR           tf_CharLoc;	/* per glyph: bit offset and width */
    APTR           tf_CharSpace;	/* per glyph advance, or NULL */
    APTR           tf_CharKern;	/* per glyph kerning, or NULL */
};

/* ExtendFont() keeps its extension in the reply port field */
#define tf_Extension	tf_Message.mn_ReplyPort

/* tfe_Flags0 */
#define TE0B_NOREMFONT	0
#define TE0F_NOREMFONT	0x01

struct TextFontExtension
{
    UWORD            tfe_MatchWord;
    UBYTE            tfe_Flags0;
    UBYTE            tfe_Flags1;
    struct TextFont *tfe_BackPtr;
    struct MsgPort  *tfe_OrigReplyPort;
    struct TagItem  *tfe_Tags;
    UWORD           *tfe_OFontPatchS;
    UWORD           *tfe_OFontPatchK;
};

/* ctf_Flags */
#define CT_COLORMASK	0x000F
#define CT_COLORFONT	0x0001
#define CT_GREYFONT	0x0002
#define CT_ANTIALIAS	0x0004
#define CTB_MAPCOLOR	0
#define CTF_MAPCOLOR	0x0001

struct ColorFontColors
{
    UWORD  cfc_Reserved;
    UWORD  cfc_Count;
    UWORD *cfc_ColorTable;	/* 0x0RGB entries */
};

struct ColorTextFont
{
    struct TextFont         ctf_TF;
    UWORD                   ctf_Flags;
    UBYTE                   ctf_Depth;
    UBYTE                   ctf_FgColor;
    UBYTE                   ctf_Low;
    UBYTE                   ctf_High;
    UBYTE                   ctf_PlanePick;
    UBYTE                   ctf_PlaneOnOff;
    struct ColorFontColors *ctf_ColorFontColors;
    APTR                    ctf_CharData[8];
};

/* TextExtent(): the size of a run of text */
struct TextExtent
{
    WORD             te_Width;
    WORD             te_Height;
    struct Rectangle te_Extent;	/* relative to the pen position */
};

#endif /* GRAPHICS_TEXT_H */
