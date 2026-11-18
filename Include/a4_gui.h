/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Allegro 4's GUI: dialogs (DIALOG, do_dialog, init/update/shutdown_dialog),
 * their messages and the standard objects (d_box_proc, d_button_proc,
 * d_edit_proc, d_list_proc, d_slider_proc...). Included by allegro.h.
 *
 * The dialog engine runs in the game's own code (src/a4_gui.c, part of
 * liballeg.a): a dialog's objects are the game's procedures and data, and
 * they draw and read input through allegro4.library's calls. So nothing
 * here is a library call (tools/gen_lib.py reads allegro.h only).
 */
#ifndef A4_GUI_H
#define A4_GUI_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct DIALOG {
    int (*proc)(int msg, struct DIALOG *d, int c);
    int x, y, w, h;
    int fg, bg;
    int key;                        /* the ASCII keyboard shortcut */
    int flags;
    int d1, d2;
    void *dp, *dp2, *dp3;
} DIALOG;

typedef struct DIALOG_PLAYER {
    int obj;                        /* the object that closed the dialog; -1 for Esc */
    int res;
    int mouse_obj;
    int focus_obj;
    int joy_on;
    int click_wait;
    int mouse_ox, mouse_oy, mouse_oz, mouse_b;
    DIALOG *dialog;
    /* ours */
    DIALOG *prev_active;
    long last_click_ms;
    int last_click_obj;
} DIALOG_PLAYER;

/* object flags */
#define D_EXIT          1
#define D_SELECTED      2
#define D_GOTFOCUS      4
#define D_GOTMOUSE      8
#define D_HIDDEN        16
#define D_DISABLED      32
#define D_DIRTY         64
#define D_INTERNAL      128
#define D_USER          256

/* what a dialog procedure returns */
#define D_O_K           0
#define D_CLOSE         1
#define D_REDRAW        2
#define D_REDRAWME      4
#define D_WANTFOCUS     8
#define D_USED_CHAR     16
#define D_REDRAW_ALL    32
#define D_DONTWANTMOUSE 64

/* messages */
#define MSG_START       1
#define MSG_END         2
#define MSG_DRAW        3
#define MSG_CLICK       4
#define MSG_DCLICK      5
#define MSG_KEY         6
#define MSG_CHAR        7
#define MSG_UCHAR       8
#define MSG_XCHAR       9
#define MSG_WANTFOCUS   10
#define MSG_GOTFOCUS    11
#define MSG_LOSTFOCUS   12
#define MSG_GOTMOUSE    13
#define MSG_LOSTMOUSE   14
#define MSG_IDLE        15
#define MSG_RADIO       16
#define MSG_WHEEL       17
#define MSG_LPRESS      18
#define MSG_LRELEASE    19
#define MSG_MPRESS      20
#define MSG_MRELEASE    21
#define MSG_RPRESS      22
#define MSG_RRELEASE    23
#define MSG_WANTMOUSE   24
#define MSG_USER        25

extern int gui_fg_color, gui_mg_color, gui_bg_color;
extern int gui_font_baseline;
extern int (*gui_mouse_x)(void);
extern int (*gui_mouse_y)(void);
extern int (*gui_mouse_z)(void);
extern int (*gui_mouse_b)(void);
extern DIALOG *active_dialog;
extern DIALOG_PLAYER *active_dialog_player;

int gui_textout_ex(BITMAP *bmp, const char *s, int x, int y, int color, int bg, int centre);
int gui_textout(BITMAP *bmp, const char *s, int x, int y, int color, int centre);
int gui_strlen(const char *s);
void gui_set_screen(BITMAP *bmp);
BITMAP *gui_get_screen(void);

void position_dialog(DIALOG *dialog, int x, int y);
void centre_dialog(DIALOG *dialog);
void set_dialog_color(DIALOG *dialog, int fg, int bg);
int find_dialog_focus(DIALOG *dialog);
int offer_focus(DIALOG *dialog, int obj, int *focus_obj, int force);
int object_message(DIALOG *dialog, int msg, int c);
int dialog_message(DIALOG *dialog, int msg, int c, int *obj);
int broadcast_dialog_message(int msg, int c);
int do_dialog(DIALOG *dialog, int focus_obj);
int popup_dialog(DIALOG *dialog, int focus_obj);
DIALOG_PLAYER *init_dialog(DIALOG *dialog, int focus_obj);
int update_dialog(DIALOG_PLAYER *player);
int shutdown_dialog(DIALOG_PLAYER *player);

int d_yield_proc(int msg, DIALOG *d, int c);
int d_clear_proc(int msg, DIALOG *d, int c);
int d_box_proc(int msg, DIALOG *d, int c);
int d_shadow_box_proc(int msg, DIALOG *d, int c);
int d_bitmap_proc(int msg, DIALOG *d, int c);
int d_text_proc(int msg, DIALOG *d, int c);
int d_ctext_proc(int msg, DIALOG *d, int c);
int d_rtext_proc(int msg, DIALOG *d, int c);
int d_button_proc(int msg, DIALOG *d, int c);
int d_check_proc(int msg, DIALOG *d, int c);
int d_radio_proc(int msg, DIALOG *d, int c);
int d_icon_proc(int msg, DIALOG *d, int c);
int d_keyboard_proc(int msg, DIALOG *d, int c);
int d_edit_proc(int msg, DIALOG *d, int c);
int d_list_proc(int msg, DIALOG *d, int c);
int d_text_list_proc(int msg, DIALOG *d, int c);
int d_textbox_proc(int msg, DIALOG *d, int c);
int d_slider_proc(int msg, DIALOG *d, int c);

/* Allegro's helper for list-like objects of a game's own (guiproc.c): the
 * frame round d and, when listsize rows do not fit in height, the scroll bar */
#define A4_HAS_DRAW_SCROLLABLE_FRAME 1
void _draw_scrollable_frame(DIALOG *d, int listsize, int offset, int height, int fg_color, int bg);
/* and its text-box helper: wraps thetext into the box, sets *listsize, draws from offset when draw */
void _draw_textbox(char *thetext, int *listsize, int draw, int offset, int wword, int tabsize,
                   int x, int y, int w, int h, int disabled, int fore, int deselect, int disable);

/* the old window calls: Amiga screens have no close button, so they only
 * keep what they are given (set_close_button_callback is the newer one) */
int set_window_close_button(int enable);
void set_window_close_hook(void (*proc)(void));


/* ---- menus (a4_menu.c) ------------------------------------------------------------------ */

typedef struct MENU {
    char *text;                     /* "&File", "Open\tCtrl+O"; "" is a separator; NULL ends the list */
    int (*proc)(void);              /* called when the item is chosen */
    struct MENU *child;             /* a menu of its own, opened from this item */
    int flags;                      /* D_SELECTED (a tick), D_DISABLED */
    void *dp;
} MENU;

typedef struct MENU_PLAYER MENU_PLAYER;

extern MENU *active_menu;           /* the item whose proc is being called */
extern void (*gui_menu_draw_menu)(int x, int y, int w, int h);
extern void (*gui_menu_draw_menu_item)(MENU *m, int x, int y, int w, int h, int bar, int sel);

int do_menu(MENU *menu, int x, int y);
MENU_PLAYER *init_menu(MENU *menu, int x, int y);
int update_menu(MENU_PLAYER *player);
int shutdown_menu(MENU_PLAYER *player);
int d_menu_proc(int msg, DIALOG *d, int c);

/* ---- what Allegro's internal header gives GUI code (allegro/internal/aintern.h) ---------- */

extern int gui_mouse_focus;         /* kept; this dialog engine gives focus on a click */
/* the objects alert() and the selectors are made of: games set their own;
 * allegro4.library's alert draws its own look and does not read them */
extern int (*gui_shadow_box_proc)(int msg, DIALOG *d, int c);
extern int (*gui_ctext_proc)(int msg, DIALOG *d, int c);
extern int (*gui_button_proc)(int msg, DIALOG *d, int c);
extern int (*gui_edit_proc)(int msg, DIALOG *d, int c);
extern int (*gui_list_proc)(int msg, DIALOG *d, int c);
extern int (*gui_text_list_proc)(int msg, DIALOG *d, int c);

/* ---- small game-side calls ---------------------------------------------------------------- */

extern int *palette_color;          /* colour index of palette entry i: i itself in 8-bit */
extern FONT *_a4_default_font;      /* the font allegro_init set up */
#define _default_font (*_a4_default_font)
const char *get_config_text(const char *msg);   /* no language files: msg itself */
void reload_config_texts(const char *new_language);    /* kept for get_config_text */
/* the screen mode selector: one dialog with the sizes this screen can open;
 * the card is always GFX_AUTODETECT and the depth 8 */
int gfx_mode_select(int *card, int *w, int *h);
int gfx_mode_select_ex(int *card, int *w, int *h, int *color_depth);

/* ---- FLI and FLC animations (a4_fli.c) ---------------------------------------------------- */

#define FLI_OK          0
#define FLI_EOF         -1
#define FLI_ERROR       -2
#define FLI_NOT_OPEN    -3

extern BITMAP *fli_bitmap;          /* the current frame */
extern PALETTE fli_palette;
extern int fli_bmp_dirty_from, fli_bmp_dirty_to;    /* rows changed by the last frame */
extern int fli_pal_dirty_from, fli_pal_dirty_to;    /* palette entries changed */
extern int fli_frame;               /* frames read since open */
extern volatile int fli_timer;      /* goes up once per frame time while a FLI is open */

int open_fli(const char *filename);
int open_memory_fli(void *fli_data);
void close_fli(void);
int next_fli_frame(int loop);
void reset_fli_variables(void);
int play_fli(const char *filename, BITMAP *bmp, int loop, int (*callback)(void));
int play_memory_fli(void *fli_data, BITMAP *bmp, int loop, int (*callback)(void));

#ifdef __cplusplus
}
#endif

#endif
