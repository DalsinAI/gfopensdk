/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * allegro.h: the Allegro 4 API for AmigaOS 3.x, on allegro4.library, which
 * sits on acgame.library (ACGame's AGA and RTG 8-bit screens, keyboard,
 * mouse, pads and clock). Written by the AmiCradle Team from the Allegro 4
 * documentation; the names, numbers and file formats are Allegro 4's, so a
 * game builds unchanged.
 *
 * Colour depth: 8-bit (256 colours, 6-bit palette), which is ACGame's frame.
 * See allegro4/README.md for what is in and what is not.
 */
#ifndef ALLEGRO_H
#define ALLEGRO_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <stdarg.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- version and base ---------------------------------------------------- */

#define ALLEGRO_VERSION          4
#define ALLEGRO_SUB_VERSION      4
#define ALLEGRO_WIP_VERSION      3
#define ALLEGRO_VERSION_STR      "4.4.3 (allegro4.library)"
#define ALLEGRO_DATE_STR         "2026"
#define ALLEGRO_DATE             20261116
#define ALLEGRO_AMIGA            1
#define ALLEGRO_BIG_ENDIAN       1
#define ALLEGRO_COLOR8           1
#define ALLEGRO_NO_ASM           1

#ifndef TRUE
#define TRUE  -1
#define FALSE 0
#endif
#undef MIN
#undef MAX
#undef MID
#define MIN(x, y)     (((x) < (y)) ? (x) : (y))
#define MAX(x, y)     (((x) > (y)) ? (x) : (y))
#define MID(x, y, z)  MAX((x), MIN((y), (z)))
#undef ABS
#define ABS(x)        (((x) >= 0) ? (x) : (-(x)))
#undef SGN
#define SGN(x)        (((x) >= 0) ? 1 : -1)
#define CLAMP(x, y, z) MAX((x), MIN((y), (z)))

#define AL_CONST      const
#define AL_ID(a, b, c, d) (((a) << 24) | ((b) << 16) | ((c) << 8) | (d))
#define AL_INLINE(type, name, args, code) static inline type name args code
#define AL_FUNC(type, name, args) type name args
#define AL_VAR(type, name) extern type name
#define AL_ARRAY(type, name) extern type name[]
#define AL_FUNCPTR(type, name, args) extern type (*name) args
#define INLINE inline
#define ZERO_SIZE_ARRAY(type, name) type name[]
#define _AL_DLL
#define LOCK_DATA(d, s)
#define LOCK_CODE(c, s)
#define UNLOCK_DATA(d, s)
#define LOCK_VARIABLE(x)
#define LOCK_FUNCTION(x)
#define END_OF_FUNCTION(x)
#define END_OF_STATIC_FUNCTION(x)
#define END_OF_MAIN()
#define ALLEGRO_ERROR_SIZE 256
#define OTHER_PATH_SEPARATOR '\\'
#define DEVICE_SEPARATOR ':'

/* Allegro's debugging checks: nothing unless DEBUGMODE */
#ifdef DEBUGMODE
#define ASSERT(c) do { if (!(c)) allegro_message("ASSERT %s:%d: %s\n", __FILE__, __LINE__, #c); } while (0)
#define TRACE allegro_message
#else
#define ASSERT(c) ((void)0)
#define TRACE(...) ((void)0)
#endif

extern char allegro_id[];
extern char allegro_error[ALLEGRO_ERROR_SIZE];
extern int *allegro_errno;
extern int os_type, os_version, os_revision, os_multitasking;
extern int cpu_family, cpu_model, cpu_capabilities;
extern char cpu_vendor[];

#define OSTYPE_UNKNOWN 0
#define OSTYPE_AMIGA   AL_ID('A','M','I','G')
/* Allegro 4.4's others, for games that switch on os_type */
#define OSTYPE_WIN3      AL_ID('W','I','N','3')
#define OSTYPE_WIN95     AL_ID('W','9','5',' ')
#define OSTYPE_WIN98     AL_ID('W','9','8',' ')
#define OSTYPE_WINME     AL_ID('W','M','E',' ')
#define OSTYPE_WINNT     AL_ID('W','N','T',' ')
#define OSTYPE_WIN2000   AL_ID('W','2','K',' ')
#define OSTYPE_WINXP     AL_ID('W','X','P',' ')
#define OSTYPE_WIN2003   AL_ID('W','2','K','3')
#define OSTYPE_WINVISTA  AL_ID('W','V','S','T')
#define OSTYPE_WIN2008   AL_ID('W','2','K','8')
#define OSTYPE_WIN7      AL_ID('W','I','N','7')
#define OSTYPE_WIN8      AL_ID('W','I','N','8')
#define OSTYPE_WIN81     AL_ID('W','8','.','1')
#define OSTYPE_WIN10     AL_ID('W','1','0',' ')
#define OSTYPE_OS2       AL_ID('O','S','2',' ')
#define OSTYPE_WARP      AL_ID('W','A','R','P')
#define OSTYPE_DOSEMU    AL_ID('D','E','M','U')
#define OSTYPE_OPENDOS   AL_ID('O','D','O','S')
#define OSTYPE_LINUX     AL_ID('T','U','X',' ')
#define OSTYPE_SUNOS     AL_ID('S','U','N',' ')
#define OSTYPE_FREEBSD   AL_ID('F','B','S','D')
#define OSTYPE_NETBSD    AL_ID('N','B','S','D')
#define OSTYPE_OPENBSD   AL_ID('O','B','S','D')
#define OSTYPE_IRIX      AL_ID('I','R','I','X')
#define OSTYPE_DARWIN    AL_ID('D','A','R','W')
#define OSTYPE_QNX       AL_ID('Q','N','X',' ')
#define OSTYPE_UNIX      AL_ID('U','N','I','X')
#define OSTYPE_BEOS      AL_ID('B','E','O','S')
#define OSTYPE_HAIKU     AL_ID('H','A','I','K')
#define OSTYPE_MACOS     AL_ID('M','A','C',' ')
#define OSTYPE_MACOSX    AL_ID('M','A','C','X')
#define OSTYPE_PSP       AL_ID('K','P','S','P')

#define SYSTEM_AUTODETECT 0
#define SYSTEM_NONE       AL_ID('N','O','N','E')

int install_allegro(int system_id, int *errno_ptr, int (*atexit_ptr)(void (*)(void)));
#define allegro_init() install_allegro(SYSTEM_AUTODETECT, &errno, atexit)
void allegro_exit(void);
void allegro_message(const char *msg, ...);
void set_window_title(const char *name);
int set_close_button_callback(void (*proc)(void));
int desktop_color_depth(void);
int get_desktop_resolution(int *width, int *height);
void check_cpu(void);
void yield_timeslice(void);
int set_display_switch_mode(int mode);
int set_display_switch_callback(int dir, void (*cb)(void));
void remove_display_switch_callback(void (*cb)(void));
int get_display_switch_mode(void);
#define SWITCH_NONE 0
#define SWITCH_PAUSE 1
#define SWITCH_AMNESIA 2
#define SWITCH_BACKGROUND 3
#define SWITCH_BACKAMNESIA 4
#define SWITCH_IN 0
#define SWITCH_OUT 1
const char *get_config_string(const char *section, const char *name, const char *def);
int get_config_int(const char *section, const char *name, int def);
int get_config_hex(const char *section, const char *name, int def);
float get_config_float(const char *section, const char *name, float def);
int get_config_id(const char *section, const char *name, int def);
void set_config_file(const char *filename);
void set_config_data(const char *data, int length);
void set_config_string(const char *section, const char *name, const char *val);
void set_config_int(const char *section, const char *name, int val);
void set_config_hex(const char *section, const char *name, int val);
void set_config_float(const char *section, const char *name, float val);
void set_config_id(const char *section, const char *name, int val);
void override_config_file(const char *filename);
void override_config_data(const char *data, int length);
void flush_config_file(void);
void push_config_state(void);
void pop_config_state(void);
char **get_config_argv(const char *section, const char *name, int *argc);

/* ---- fixed point ------------------------------------------------------------ */

typedef int32_t fixed;
static inline fixed itofix(int x) { return (fixed)((uint32_t)x << 16); }
static inline int fixtoi(fixed x) { return (int)((x >> 16) + ((x & 0x8000) >> 15)); }
#define ftofix(x)   ((fixed)((x) * 65536.0 + ((x) < 0 ? -0.5 : 0.5)))
#define fixtof(x)   ((double)(x) / 65536.0)
static inline int fixfloor(fixed x) { return (int)(x >> 16); }
static inline int fixceil(fixed x) { return (int)((x + 0xFFFF) >> 16); }
static inline fixed fixmul(fixed x, fixed y) { return (fixed)(((int64_t)x * y) >> 16); }
static inline fixed fixdiv(fixed x, fixed y) {
    if (y == 0) return x < 0 ? -0x7FFFFFFF : 0x7FFFFFFF;
    return (fixed)(((int64_t)x * 65536) / y);
}
static inline fixed fixadd(fixed x, fixed y) { return x + y; }
static inline fixed fixsub(fixed x, fixed y) { return x - y; }
fixed fixsin(fixed x);
fixed fixcos(fixed x);
fixed fixtan(fixed x);
fixed fixatan(fixed x);
fixed fixatan2(fixed y, fixed x);
fixed fixsqrt(fixed x);
fixed fixhypot(fixed x, fixed y);
extern const fixed fixtorad_r, radtofix_r;
/* Allegro 4's older fixed-point names (alcompat.h) */
#ifndef ALLEGRO_NO_FIX_ALIASES
#define fadd(x, y)     fixadd((x), (y))
#define fsub(x, y)     fixsub((x), (y))
#define fmul(x, y)     fixmul((x), (y))
#define fdiv(x, y)     fixdiv((x), (y))
#define fceil(x)       fixceil(x)
#define ffloor(x)      fixfloor(x)
#define fsin(x)        fixsin(x)
#define fcos(x)        fixcos(x)
#define ftan(x)        fixtan(x)
#define fatan(x)       fixatan(x)
#define fatan2(y, x)   fixatan2((y), (x))
#define fsqrt(x)       fixsqrt(x)
#define fhypot(x, y)   fixhypot((x), (y))
#endif

struct BITMAP;

/* ---- palette ---------------------------------------------------------------- */

#define PAL_SIZE 256
typedef struct RGB { unsigned char r, g, b, filler; } RGB;
typedef RGB PALETTE[PAL_SIZE];
typedef struct RGB_MAP { unsigned char data[32][32][32]; } RGB_MAP;
typedef struct COLOR_MAP { unsigned char data[PAL_SIZE][PAL_SIZE]; } COLOR_MAP;

extern PALETTE black_palette, desktop_palette, default_palette;
extern RGB_MAP *rgb_map;
extern COLOR_MAP *color_map;
extern int _color_depth;
/* palette index -> colour to draw with: in 8-bit, palette_color[i] == i */
#define A4_HAS_PALETTE_COLOR 1
extern int *palette_color;

void set_color(int idx, const RGB *p);
void set_palette(const PALETTE p);
void set_palette_range(const PALETTE p, int from, int to, int retracesync);
void get_color(int idx, RGB *p);
void get_palette(PALETTE p);
void get_palette_range(PALETTE p, int from, int to);
void fade_interpolate(const PALETTE source, const PALETTE dest, PALETTE output, int pos, int from, int to);
void fade_from_range(const PALETTE source, const PALETTE dest, int speed, int from, int to);
void fade_in_range(const PALETTE p, int speed, int from, int to);
void fade_out_range(int speed, int from, int to);
void fade_from(const PALETTE source, const PALETTE dest, int speed);
void fade_in(const PALETTE p, int speed);
void fade_out(int speed);
void select_palette(const PALETTE p);
void unselect_palette(void);
void generate_332_palette(PALETTE pal);
int generate_optimized_palette(struct BITMAP *image, PALETTE pal, const signed char rsvdcols[256]);
void create_rgb_table(RGB_MAP *table, const PALETTE pal, void (*callback)(int pos));
void create_light_table(COLOR_MAP *table, const PALETTE pal, int r, int g, int b, void (*callback)(int pos));
void create_trans_table(COLOR_MAP *table, const PALETTE pal, int r, int g, int b, void (*callback)(int pos));
void create_color_table(COLOR_MAP *table, const PALETTE pal,
                        void (*blend)(const PALETTE pal, int x, int y, RGB *rgb), void (*callback)(int pos));
void create_blender_table(COLOR_MAP *table, const PALETTE pal, void (*callback)(int pos));
void hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b);
void rgb_to_hsv(int r, int g, int b, float *h, float *s, float *v);
int bestfit_color(const PALETTE pal, int r, int g, int b);
int makecol(int r, int g, int b);
int makecol8(int r, int g, int b);
int makecol_depth(int color_depth, int r, int g, int b);
int makeacol(int r, int g, int b, int a);
int makeacol_depth(int color_depth, int r, int g, int b, int a);
int getr(int c);
int getg(int c);
int getb(int c);
int geta(int c);
int getr8(int c);
int getg8(int c);
int getb8(int c);
int makecol15(int r, int g, int b);
int makecol16(int r, int g, int b);
int makecol24(int r, int g, int b);
int makecol32(int r, int g, int b);
int makeacol32(int r, int g, int b, int a);
int getr15(int c);
int getg15(int c);
int getb15(int c);
int getr16(int c);
int getg16(int c);
int getb16(int c);
int getr24(int c);
int getg24(int c);
int getb24(int c);
int getr32(int c);
int getg32(int c);
int getb32(int c);
int geta32(int c);
int geta_depth(int color_depth, int c);
int getr_depth(int color_depth, int c);
int getg_depth(int color_depth, int c);
int getb_depth(int color_depth, int c);
void set_color_depth(int depth);
int get_color_depth(void);
void set_color_conversion(int mode);
int get_color_conversion(void);
#define COLORCONV_NONE 0
#define COLORCONV_TOTAL 0xFFFFFFF
#define COLORCONV_KEEP_TRANS 0x4000000
#define COLORCONV_8_TO_15 0x1
#define COLORCONV_8_TO_16 0x2
#define COLORCONV_8_TO_24 0x4
#define COLORCONV_8_TO_32 0x8
#define COLORCONV_15_TO_8 0x10
#define COLORCONV_15_TO_16 0x20
#define COLORCONV_15_TO_24 0x40
#define COLORCONV_15_TO_32 0x80
#define COLORCONV_16_TO_15 0x200
#define COLORCONV_16_TO_24 0x400
#define COLORCONV_16_TO_32 0x800
#define COLORCONV_24_TO_15 0x2000
#define COLORCONV_24_TO_16 0x4000
#define COLORCONV_24_TO_32 0x8000
#define COLORCONV_32_TO_15 0x20000
#define COLORCONV_32_TO_16 0x40000
#define COLORCONV_32_TO_24 0x80000
#define COLORCONV_16_TO_8 0x100
#define COLORCONV_24_TO_8 0x1000
#define COLORCONV_32_TO_8 0x10000
#define COLORCONV_32A_TO_8 0x200000
#define COLORCONV_EXPAND_256 (COLORCONV_8_TO_15 | COLORCONV_8_TO_16 | COLORCONV_8_TO_24 | COLORCONV_8_TO_32)
#define COLORCONV_REDUCE_TO_256 (COLORCONV_15_TO_8 | COLORCONV_16_TO_8 | COLORCONV_24_TO_8 | COLORCONV_32_TO_8 | COLORCONV_32A_TO_8)
#define COLORCONV_DITHER 0x6000000
/* the pixel formats (Allegro 4's own on a PC): 15 = 0RRRRRGGGGGBBBBB,
 * 16 = RRRRRGGGGGGBBBBB, 24 and 32 = 0xAARRGGBB; a 24-bit pixel is three
 * bytes R, G, B in memory, a 15/16/32-bit one a native word */
#define A4_HAS_TRUECOLOUR 1
extern int _rgb_r_shift_15, _rgb_g_shift_15, _rgb_b_shift_15;
extern int _rgb_r_shift_16, _rgb_g_shift_16, _rgb_b_shift_16;
extern int _rgb_r_shift_24, _rgb_g_shift_24, _rgb_b_shift_24;
extern int _rgb_r_shift_32, _rgb_g_shift_32, _rgb_b_shift_32, _rgb_a_shift_32;
extern int _rgb_scale_5[32], _rgb_scale_6[64];
#define MASK_COLOR_8 0
#define MASK_COLOR_15 0x7C1F
#define MASK_COLOR_16 0xF81F
#define MASK_COLOR_24 0xFF00FF
#define MASK_COLOR_32 0xFF00FF

/* ---- bitmaps ---------------------------------------------------------------- */

typedef struct GFX_VTABLE {
    int color_depth;                /* 8, 15, 16, 24 or 32 */
    int mask_color;
} GFX_VTABLE;
typedef struct BITMAP {
    int w, h;                       /* width and height in pixels */
    int clip;                       /* clipping on */
    int cl, cr, ct, cb;             /* clip left, right (excl), top, bottom (excl) */
    struct GFX_VTABLE *vtable;
    void *write_bank;
    void *read_bank;
    void *dat;                      /* the pixels (an owned bitmap), or NULL */
    unsigned long id;
    void *extra;
    int x_ofs, y_ofs;               /* a sub-bitmap's place in its parent */
    int seg;
    ZERO_SIZE_ARRAY(unsigned char *, line);
} BITMAP;

#define BMP_ID_VIDEO     0x80000000
#define BMP_ID_SYSTEM    0x40000000
#define BMP_ID_SUB       0x20000000
#define BMP_ID_PLANAR    0x10000000
#define BMP_ID_LOCKED    0x08000000
#define BMP_ID_AUTOLOCK  0x04000000
#define BMP_ID_MASK      0x01FFFFFF

extern BITMAP *screen;
extern int _a4_screen_w, _a4_screen_h;
#define SCREEN_W  _a4_screen_w
#define SCREEN_H  _a4_screen_h
#define VIRTUAL_W _a4_screen_w
#define VIRTUAL_H _a4_screen_h

BITMAP *create_bitmap(int width, int height);
BITMAP *create_bitmap_ex(int color_depth, int width, int height);
BITMAP *create_sub_bitmap(BITMAP *parent, int x, int y, int width, int height);
BITMAP *create_video_bitmap(int width, int height);
BITMAP *create_system_bitmap(int width, int height);
void destroy_bitmap(BITMAP *bitmap);
int bitmap_color_depth(BITMAP *bmp);
int bitmap_mask_color(BITMAP *bmp);
int is_same_bitmap(BITMAP *bmp1, BITMAP *bmp2);
int is_linear_bitmap(BITMAP *bmp);
int is_planar_bitmap(BITMAP *bmp);
int is_memory_bitmap(BITMAP *bmp);
int is_screen_bitmap(BITMAP *bmp);
int is_video_bitmap(BITMAP *bmp);
int is_system_bitmap(BITMAP *bmp);
int is_sub_bitmap(BITMAP *bmp);
void acquire_bitmap(BITMAP *bmp);
void release_bitmap(BITMAP *bmp);
#define acquire_screen() acquire_bitmap(screen)
#define release_screen() release_bitmap(screen)
void set_clip_rect(BITMAP *bitmap, int x1, int y1, int x2, int y2);
void add_clip_rect(BITMAP *bitmap, int x1, int y1, int x2, int y2);
void get_clip_rect(BITMAP *bitmap, int *x1, int *y1, int *x2, int *y2);
void set_clip_state(BITMAP *bitmap, int state);
int get_clip_state(BITMAP *bitmap);
int is_inside_bitmap(BITMAP *bmp, int x, int y, int clip);
#define set_clip(bmp, x1, y1, x2, y2) set_clip_rect((bmp), (x1), (y1), (x2), (y2))
void lock_bitmap(BITMAP *bmp);
int show_video_bitmap(BITMAP *bitmap);
int request_video_bitmap(BITMAP *bitmap);
int scroll_screen(int x, int y);
int request_scroll(int x, int y);
int poll_scroll(void);
int enable_triple_buffer(void);
unsigned long bmp_write_line(BITMAP *bmp, int line);
unsigned long bmp_read_line(BITMAP *bmp, int line);
void bmp_unwrite_line(BITMAP *bmp);
#define bmp_select(bmp)
#define bmp_write8(addr, c)  (*((uint8_t *)(addr)) = (c))
#define bmp_read8(addr)      (*((uint8_t *)(addr)))
#define bmp_write15(addr, c) (*((uint16_t *)(addr)) = (uint16_t)(c))
#define bmp_write16(addr, c) (*((uint16_t *)(addr)) = (uint16_t)(c))
#define bmp_write32(addr, c) (*((uint32_t *)(addr)) = (uint32_t)(c))
#define bmp_read15(addr)     (*((uint16_t *)(addr)))
#define bmp_read16(addr)     (*((uint16_t *)(addr)))
#define bmp_read32(addr)     (*((uint32_t *)(addr)))
/* 24-bit pixels are three bytes R, G, B (0xRRGGBB) */
#define bmp_write24(addr, c) do { uint8_t *_p24 = (uint8_t *)(addr); int _c24 = (int)(c); \
                                  _p24[0] = (uint8_t)(_c24 >> 16); _p24[1] = (uint8_t)(_c24 >> 8); _p24[2] = (uint8_t)_c24; } while (0)
#define bmp_read24(addr)     ((((const uint8_t *)(addr))[0] << 16) | (((const uint8_t *)(addr))[1] << 8) | ((const uint8_t *)(addr))[2])

/* ---- graphics modes ------------------------------------------------------------ */

#define GFX_TEXT                -1
#define GFX_AUTODETECT          0
#define GFX_AUTODETECT_FULLSCREEN 1
#define GFX_AUTODETECT_WINDOWED 2
#define GFX_SAFE                AL_ID('S','A','F','E')
#define GFX_ACGAME              AL_ID('A','C','G','M')
#define GFX_ACGAME_AGA          AL_ID('A','C','G','A')
#define GFX_ACGAME_RTG          AL_ID('A','C','G','R')
/* the DOS drivers' ids: a game that asks for one gets ACGame's own screen */
#define GFX_VGA                 AL_ID('V','G','A',' ')
#define GFX_MODEX               AL_ID('M','O','D','X')
#define GFX_VESA1               AL_ID('V','B','E','1')
#define GFX_VESA2B              AL_ID('V','B','B','N')
#define GFX_VESA2L              AL_ID('V','B','F','L')
#define GFX_VESA3               AL_ID('V','B','E','3')
#define GFX_VBEAF               AL_ID('V','B','A','F')
#define GFX_XTENDED             AL_ID('X','T','N','D')

typedef struct GFX_DRIVER {
    int id;
    const char *name;
    const char *desc;
    const char *ascii_name;
    int w, h;
    int linear;
    long bank_size, bank_gran, vid_mem, vid_phys_base;
    int windowed;
} GFX_DRIVER;
extern GFX_DRIVER *gfx_driver;
extern int gfx_capabilities;
#define GFX_CAN_SCROLL 0x00000001
#define GFX_HW_CURSOR  0x00000004

typedef struct GFX_MODE { int width, height, bpp; } GFX_MODE;
typedef struct GFX_MODE_LIST { int num_modes; GFX_MODE *mode; } GFX_MODE_LIST;

int set_gfx_mode(int card, int w, int h, int v_w, int v_h);
void request_refresh_rate(int rate);
int get_refresh_rate(void);
int get_gfx_mode(void);
int get_gfx_mode_type(int graphics_card);
GFX_MODE_LIST *get_gfx_mode_list(int card);
int is_windowed_mode(void);            /* 0: ACGame's screens are full screens */
void destroy_gfx_mode_list(GFX_MODE_LIST *gfx_mode_list);
void vsync(void);
/* allegro4.library: show the screen bitmap now (it is shown at vsync(),
 * rest(), the input polls and after a large blit to it anyway). */
void a4_flush_screen(void);

/* ---- drawing --------------------------------------------------------------------- */

#define DRAW_MODE_SOLID          0
#define DRAW_MODE_XOR            1
#define DRAW_MODE_COPY_PATTERN   2
#define DRAW_MODE_SOLID_PATTERN  3
#define DRAW_MODE_MASKED_PATTERN 4
#define DRAW_MODE_TRANS          5
void drawing_mode(int mode, BITMAP *pattern, int x_anchor, int y_anchor);
void xor_mode(int on);
void solid_mode(void);
/* truecolour translucency (DRAW_MODE_TRANS, draw_trans_sprite, draw_lit_sprite):
 * the blender and its colour/alpha; 8-bit uses color_map instead */
typedef unsigned long (*BLENDER_FUNC)(unsigned long x, unsigned long y, unsigned long n);
void set_trans_blender(int r, int g, int b, int a);
void set_alpha_blender(void);
void set_write_alpha_blender(void);
void set_add_blender(int r, int g, int b, int a);
void set_burn_blender(int r, int g, int b, int a);
void set_difference_blender(int r, int g, int b, int a);
void set_dodge_blender(int r, int g, int b, int a);
void set_invert_blender(int r, int g, int b, int a);
void set_multiply_blender(int r, int g, int b, int a);
void set_screen_blender(int r, int g, int b, int a);

void clear_bitmap(BITMAP *bitmap);
void clear_to_color(BITMAP *bitmap, int color);
/* a function, not a macro, so C++'s std::string::clear() and the like still
 * work (Allegro 4.4's alcompat.h); ALLEGRO_NO_CLEAR_BITMAP_ALIAS leaves it out */
#ifndef ALLEGRO_NO_CLEAR_BITMAP_ALIAS
static __attribute__((unused)) __inline__ void clear(BITMAP *bmp) { clear_bitmap(bmp); }
#endif
void putpixel(BITMAP *bmp, int x, int y, int color);
void _putpixel(BITMAP *bmp, int x, int y, int color);
int getpixel(BITMAP *bmp, int x, int y);
int _getpixel(BITMAP *bmp, int x, int y);
void _putpixel15(BITMAP *bmp, int x, int y, int color);
void _putpixel16(BITMAP *bmp, int x, int y, int color);
void _putpixel24(BITMAP *bmp, int x, int y, int color);
void _putpixel32(BITMAP *bmp, int x, int y, int color);
int _getpixel15(BITMAP *bmp, int x, int y);
int _getpixel16(BITMAP *bmp, int x, int y);
int _getpixel24(BITMAP *bmp, int x, int y);
int _getpixel32(BITMAP *bmp, int x, int y);
#define putpixel8 _putpixel
#define getpixel8 _getpixel
#define _putpixel8 _putpixel
#define _getpixel8 _getpixel
void vline(BITMAP *bmp, int x, int y1, int y2, int color);
void hline(BITMAP *bmp, int x1, int y, int x2, int color);
void do_line(BITMAP *bmp, int x1, int y1, int x2, int y2, int d, void (*proc)(BITMAP *, int, int, int));
void line(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
void fastline(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
void triangle(BITMAP *bmp, int x1, int y1, int x2, int y2, int x3, int y3, int color);
void polygon(BITMAP *bmp, int vertices, const int *points, int color);
void rect(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
void rectfill(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
void do_circle(BITMAP *bmp, int x, int y, int radius, int d, void (*proc)(BITMAP *, int, int, int));
void circle(BITMAP *bmp, int x, int y, int radius, int color);
void circlefill(BITMAP *bmp, int x, int y, int radius, int color);
void do_ellipse(BITMAP *bmp, int x, int y, int rx, int ry, int d, void (*proc)(BITMAP *, int, int, int));
void ellipse(BITMAP *bmp, int x, int y, int rx, int ry, int color);
void ellipsefill(BITMAP *bmp, int x, int y, int rx, int ry, int color);
void floodfill(BITMAP *bmp, int x, int y, int color);
void spline(BITMAP *bmp, const int points[8], int color);
void do_arc(BITMAP *bmp, int x, int y, fixed ang1, fixed ang2, int r, int d, void (*proc)(BITMAP *, int, int, int));
void arc(BITMAP *bmp, int x, int y, fixed ang1, fixed ang2, int r, int color);

/* ---- blits and sprites ------------------------------------------------------------------ */

void blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
void masked_blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int dest_x, int dest_y, int width, int height);
void stretch_blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int source_width, int source_height,
                  int dest_x, int dest_y, int dest_width, int dest_height);
void masked_stretch_blit(BITMAP *source, BITMAP *dest, int source_x, int source_y, int source_w, int source_h,
                         int dest_x, int dest_y, int dest_w, int dest_h);
void stretch_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int w, int h);
void draw_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y);
void draw_sprite_ex(BITMAP *bmp, BITMAP *sprite, int x, int y, int mode, int flip);
void draw_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y);
void draw_sprite_h_flip(BITMAP *bmp, BITMAP *sprite, int x, int y);
void draw_sprite_vh_flip(BITMAP *bmp, BITMAP *sprite, int x, int y);
void draw_trans_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y);
void draw_lit_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int color);
void draw_character_ex(BITMAP *bmp, BITMAP *sprite, int x, int y, int color, int bg);
void rotate_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle);
void rotate_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle);
void rotate_scaled_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle, fixed scale);
void rotate_scaled_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, fixed angle, fixed scale);
void pivot_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle);
void pivot_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle);
void pivot_scaled_sprite(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle, fixed scale);
void pivot_scaled_sprite_v_flip(BITMAP *bmp, BITMAP *sprite, int x, int y, int cx, int cy, fixed angle, fixed scale);
#define DRAW_SPRITE_NORMAL 0
#define DRAW_SPRITE_LIT 1
#define DRAW_SPRITE_TRANS 2
#define DRAW_SPRITE_NO_FLIP 0
#define DRAW_SPRITE_H_FLIP 1
#define DRAW_SPRITE_V_FLIP 2
#define DRAW_SPRITE_VH_FLIP 3

typedef struct RLE_SPRITE {
    int w, h;
    int color_depth;
    int size;
    ZERO_SIZE_ARRAY(signed char, dat);
} RLE_SPRITE;
RLE_SPRITE *get_rle_sprite(BITMAP *bitmap);
void destroy_rle_sprite(RLE_SPRITE *sprite);
void draw_rle_sprite(BITMAP *bmp, const RLE_SPRITE *sprite, int x, int y);
void draw_trans_rle_sprite(BITMAP *bmp, const RLE_SPRITE *sprite, int x, int y);
void draw_lit_rle_sprite(BITMAP *bmp, const RLE_SPRITE *sprite, int x, int y, int color);

typedef BITMAP COMPILED_SPRITE;
#define get_compiled_sprite(bmp, planar) (create_sub_bitmap((bmp), 0, 0, (bmp)->w, (bmp)->h))
#define destroy_compiled_sprite(s) destroy_bitmap(s)
#define draw_compiled_sprite(bmp, s, x, y) draw_sprite((bmp), (s), (x), (y))

/* ---- text -------------------------------------------------------------------------- */

typedef struct FONT_GLYPH { short w, h; ZERO_SIZE_ARRAY(unsigned char, dat); } FONT_GLYPH;
struct FONT_VTABLE;
typedef struct FONT {
    void *data;
    int height;
    struct FONT_VTABLE *vtable;
} FONT;
extern FONT *font;
extern int allegro_404_char;

void textout_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg);
void textout_centre_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg);
void textout_right_ex(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color, int bg);
void textout_justify_ex(BITMAP *bmp, const FONT *f, const char *s, int x1, int x2, int y, int diff, int color, int bg);
void textprintf_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int bg, const char *format, ...);
void textprintf_centre_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int bg, const char *format, ...);
void textprintf_right_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int bg, const char *format, ...);
void textprintf_justify_ex(BITMAP *bmp, const FONT *f, int x1, int x2, int y, int diff, int color, int bg, const char *format, ...);
int text_length(const FONT *f, const char *str);
int text_height(const FONT *f);
void destroy_font(FONT *f);
int font_has_alpha(FONT *f);
int is_color_font(FONT *f);
int is_mono_font(FONT *f);
int get_font_ranges(FONT *f);
int get_font_range_begin(FONT *f, int range);
int get_font_range_end(FONT *f, int range);
/* the old text calls: the background is text_mode()'s */
int text_mode(int mode);
void textout(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color);
void textout_centre(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color);
void textout_right(BITMAP *bmp, const FONT *f, const char *s, int x, int y, int color);
void textout_justify(BITMAP *bmp, const FONT *f, const char *s, int x1, int x2, int y, int diff, int color);
void textprintf(BITMAP *bmp, const FONT *f, int x, int y, int color, const char *format, ...);
void textprintf_centre(BITMAP *bmp, const FONT *f, int x, int y, int color, const char *format, ...);
void textprintf_right(BITMAP *bmp, const FONT *f, int x, int y, int color, const char *format, ...);
void textprintf_justify(BITMAP *bmp, const FONT *f, int x1, int x2, int y, int diff, int color, const char *format, ...);

/* ---- text strings (ASCII/Latin-1: U_ASCII and U_UTF8 strings are passed as they are) */

#define U_ASCII     AL_ID('A','S','C','8')
#define U_ASCII_CP  AL_ID('A','S','C','P')
#define U_UNICODE   AL_ID('U','N','I','C')
#define U_UTF8      AL_ID('U','T','F','8')
#define U_CURRENT   AL_ID('c','u','r','.')
void set_uformat(int type);
int get_uformat(void);
const char *uconvert(const char *s, int type, char *buf, int newtype, int size);
#define uconvert_ascii(s, buf) uconvert((s), U_ASCII, (buf), U_CURRENT, sizeof(buf))
#define uconvert_toascii(s, buf) uconvert((s), U_CURRENT, (buf), U_ASCII, sizeof(buf))
#define ugetc(s) ((int)(unsigned char)*(s))
#define ugetx(s) ((int)(unsigned char)*((*(s))++))
#define ugetxc(s) ((int)(unsigned char)*((*(s))++))
#define usetc(s, c) ((*(s) = (char)(c)), 1)
#define uwidth(s) 1
#define ucwidth(c) 1
#define uisok(c) ((c) >= 0 && (c) < 256)
#define uoffset(s, i) (i)
#define ugetat(s, i) ((int)(unsigned char)(s)[(i)])
#define ustrlen(s) ((int)strlen(s))
#define ustrsize(s) ((int)strlen(s))
#define ustrsizez(s) ((int)strlen(s) + 1)
#define ustrcmp(a, b) strcmp((a), (b))
#define ustrncmp(a, b, n) strncmp((a), (b), (n))
#define ustrchr(s, c) strchr((s), (c))
#define ustrrchr(s, c) strrchr((s), (c))
#define ustrstr(s, t) strstr((s), (t))
#define ustrtol(s, e, b) strtol((s), (e), (b))
#define ustrtod(s, e) strtod((s), (e))
#define ustrdup(s) _a4_strdup(s)
#define ustrcpy(d, s) strcpy((d), (s))
#define ustrcat(d, s) strcat((d), (s))
#define ustrncpy(d, s, n) strncpy((d), (s), (n))
#define utolower(c) (((c) >= 'A' && (c) <= 'Z') ? (c) + 32 : (c))
#define utoupper(c) (((c) >= 'a' && (c) <= 'z') ? (c) - 32 : (c))
#define uisspace(c) ((c) == ' ' || (c) == '\t' || (c) == '\n' || (c) == '\r' || (c) == '\f' || (c) == '\v')
#define uisdigit(c) ((c) >= '0' && (c) <= '9')
char *_a4_strdup(const char *s);
char *ustrzcpy(char *dest, int size, const char *src);
char *ustrzcat(char *dest, int size, const char *src);
char *ustrzncpy(char *dest, int size, const char *src, int n);
int ustricmp(const char *s1, const char *s2);
/* the C library names Allegro gives where the platform has none (alconfig.h) */
#ifndef stricmp
#define stricmp(a, b) ustricmp((a), (b))
#endif
#ifndef strlwr
#define strlwr(s) ustrlwr(s)
#endif
#ifndef strupr
#define strupr(s) ustrupr(s)
#endif
int ustrnicmp(const char *s1, const char *s2, int n);
char *ustrlwr(char *s);
char *ustrupr(char *s);
char *ustrtok(char *s, const char *set);
char *ustrtok_r(char *s, const char *set, char **last);
int usetat(char *s, int index, int c);
int uinsert(char *s, int index, int c);
int uremove(char *s, int index);
int usprintf(char *buf, const char *format, ...);
int uszprintf(char *buf, int size, const char *format, ...);
int uvszprintf(char *buf, int size, const char *format, va_list args);
#define ustrncat(d, s, n) strncat((d), (s), (n))

/* ---- keyboard ------------------------------------------------------------------------ */

/* keyboard_needs_poll()'s old cousins: the scancode sets a callback sees */
#define KB_NORMAL        1
#define KB_EXTENDED      2

#define KB_SHIFT_FLAG    0x0001
#define KB_CTRL_FLAG     0x0002
#define KB_ALT_FLAG      0x0004
#define KB_LWIN_FLAG     0x0008
#define KB_RWIN_FLAG     0x0010
#define KB_MENU_FLAG     0x0020
#define KB_COMMAND_FLAG  0x0040
#define KB_SCROLOCK_FLAG 0x0100
#define KB_NUMLOCK_FLAG  0x0200
#define KB_CAPSLOCK_FLAG 0x0400
#define KB_INALTSEQ_FLAG 0x0800
#define KB_ACCENT1_FLAG  0x1000
#define KB_ACCENT2_FLAG  0x2000
#define KB_ACCENT3_FLAG  0x4000
#define KB_ACCENT4_FLAG  0x8000

enum {
    KEY_A = 1, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M,
    KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,
    KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
    KEY_0_PAD, KEY_1_PAD, KEY_2_PAD, KEY_3_PAD, KEY_4_PAD, KEY_5_PAD, KEY_6_PAD, KEY_7_PAD, KEY_8_PAD, KEY_9_PAD,
    KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12,
    KEY_ESC, KEY_TILDE, KEY_MINUS, KEY_EQUALS, KEY_BACKSPACE, KEY_TAB, KEY_OPENBRACE, KEY_CLOSEBRACE,
    KEY_ENTER, KEY_COLON, KEY_QUOTE, KEY_BACKSLASH, KEY_BACKSLASH2, KEY_COMMA, KEY_STOP, KEY_SLASH,
    KEY_SPACE, KEY_INSERT, KEY_DEL, KEY_HOME, KEY_END, KEY_PGUP, KEY_PGDN, KEY_LEFT, KEY_RIGHT,
    KEY_UP, KEY_DOWN, KEY_SLASH_PAD, KEY_ASTERISK, KEY_MINUS_PAD, KEY_PLUS_PAD, KEY_DEL_PAD,
    KEY_ENTER_PAD, KEY_PRTSCR, KEY_PAUSE, KEY_ABNT_C1, KEY_YEN, KEY_KANA, KEY_CONVERT, KEY_NOCONVERT,
    KEY_AT, KEY_CIRCUMFLEX, KEY_COLON2, KEY_KANJI, KEY_EQUALS_PAD, KEY_BACKQUOTE, KEY_SEMICOLON,
    KEY_COMMAND, KEY_UNKNOWN1, KEY_UNKNOWN2, KEY_UNKNOWN3, KEY_UNKNOWN4, KEY_UNKNOWN5,
    KEY_UNKNOWN6, KEY_UNKNOWN7, KEY_UNKNOWN8,
    KEY_MODIFIERS,
    KEY_LSHIFT = KEY_MODIFIERS, KEY_RSHIFT, KEY_LCONTROL, KEY_RCONTROL, KEY_ALT, KEY_ALTGR,
    KEY_LWIN, KEY_RWIN, KEY_MENU, KEY_SCRLOCK, KEY_NUMLOCK, KEY_CAPSLOCK,
    KEY_MAX
};

extern volatile char key[KEY_MAX];
extern volatile int key_shifts;
extern int three_finger_flag;
extern int key_led_flag;
extern int (*keyboard_callback)(int key);
extern int (*keyboard_ucallback)(int key, int *scancode);
extern void (*keyboard_lowlevel_callback)(int scancode);

int install_keyboard(void);
void remove_keyboard(void);
int poll_keyboard(void);
int keyboard_needs_poll(void);
int keypressed(void);
int readkey(void);
int ureadkey(int *scancode);
void simulate_keypress(int keycode);
void simulate_ukeypress(int keycode, int scancode);
void clear_keybuf(void);
void set_leds(int leds);
void set_keyboard_rate(int delay, int repeat);
int scancode_to_ascii(int scancode);
const char *scancode_to_name(int scancode);
void install_keyboard_hooks(int (*keypressed)(void), int (*readkey)(void));
#define clear_key() clear_keybuf()

/* ---- mouse ----------------------------------------------------------------------------- */

extern volatile int mouse_x, mouse_y, mouse_z, mouse_w, mouse_b, mouse_pos;
extern BITMAP *mouse_sprite;
extern int mouse_x_focus, mouse_y_focus;
extern int freeze_mouse_flag;
extern void (*mouse_callback)(int flags);
#define MOUSE_FLAG_MOVE 1
#define MOUSE_FLAG_LEFT_DOWN 2
#define MOUSE_FLAG_LEFT_UP 4
#define MOUSE_FLAG_RIGHT_DOWN 8
#define MOUSE_FLAG_RIGHT_UP 16
#define MOUSE_FLAG_MIDDLE_DOWN 32
#define MOUSE_FLAG_MIDDLE_UP 64
#define MOUSE_FLAG_MOVE_Z 128
#define MOUSE_FLAG_MOVE_W 256
#define MOUSE_CURSOR_NONE 0
#define MOUSE_CURSOR_ALLEGRO 1
#define MOUSE_CURSOR_ARROW 2
int install_mouse(void);
void remove_mouse(void);
int poll_mouse(void);
int mouse_needs_poll(void);
void enable_hardware_cursor(void);
void disable_hardware_cursor(void);
void select_mouse_cursor(int cursor);
void show_mouse(BITMAP *bmp);
void scare_mouse(void);
void scare_mouse_area(int x, int y, int w, int h);
void unscare_mouse(void);
void position_mouse(int x, int y);
void position_mouse_z(int z);
void set_mouse_range(int x1, int y1, int x2, int y2);
void set_mouse_speed(int xspeed, int yspeed);
void set_mouse_sprite(BITMAP *sprite);
void set_mouse_sprite_focus(int x, int y);
void get_mouse_mickeys(int *mickeyx, int *mickeyy);
int show_os_cursor(int cursor);

/* ---- joystick ------------------------------------------------------------------------- */

#define MAX_JOYSTICKS 8
#define MAX_JOYSTICK_AXIS 3
#define MAX_JOYSTICK_STICKS 5
#define MAX_JOYSTICK_BUTTONS 32
#define JOY_TYPE_AUTODETECT -1
#define JOY_TYPE_NONE 0
#define JOYFLAG_DIGITAL 1
#define JOYFLAG_ANALOGUE 2
#define JOYFLAG_CALIB_DIGITAL 4
#define JOYFLAG_CALIB_ANALOGUE 8
#define JOYFLAG_CALIBRATE 16
#define JOYFLAG_SIGNED 32
#define JOYFLAG_UNSIGNED 64
typedef struct JOYSTICK_AXIS_INFO { int pos; int d1, d2; const char *name; } JOYSTICK_AXIS_INFO;
typedef struct JOYSTICK_STICK_INFO { int flags; int num_axis; JOYSTICK_AXIS_INFO axis[MAX_JOYSTICK_AXIS]; const char *name; } JOYSTICK_STICK_INFO;
typedef struct JOYSTICK_BUTTON_INFO { int b; const char *name; } JOYSTICK_BUTTON_INFO;
typedef struct JOYSTICK_INFO {
    int flags; int num_sticks; int num_buttons;
    JOYSTICK_STICK_INFO stick[MAX_JOYSTICK_STICKS];
    JOYSTICK_BUTTON_INFO button[MAX_JOYSTICK_BUTTONS];
} JOYSTICK_INFO;
extern JOYSTICK_INFO joy[MAX_JOYSTICKS];
extern int num_joysticks;
int install_joystick(int type);
void remove_joystick(void);
int poll_joystick(void);
int calibrate_joystick(int n);
const char *calibrate_joystick_name(int n);
int save_joystick_data(const char *filename);
int load_joystick_data(const char *filename);
int initialise_joystick(void);

/* ---- timers --------------------------------------------------------------------------- */

#define TIMERS_PER_SECOND 1193181L
#define SECS_TO_TIMER(x)  ((long)(x) * TIMERS_PER_SECOND)
#define MSEC_TO_TIMER(x)  ((long)(x) * (TIMERS_PER_SECOND / 1000))
#define BPS_TO_TIMER(x)   (TIMERS_PER_SECOND / (long)(x))
#define BPM_TO_TIMER(x)   ((60 * TIMERS_PER_SECOND) / (long)(x))
extern volatile int retrace_count;
extern void (*retrace_proc)(void);
int install_timer(void);
void remove_timer(void);
int install_int_ex(void (*proc)(void), long speed);
int install_int(void (*proc)(void), long speed);
void remove_int(void (*proc)(void));
int install_param_int_ex(void (*proc)(void *param), void *param, long speed);
int install_param_int(void (*proc)(void *param), void *param, long speed);
void remove_param_int(void (*proc)(void *param), void *param);
void rest(unsigned int time);
void rest_callback(unsigned int time, void (*callback)(void));
int timer_can_simulate_retrace(void);
void timer_simulate_retrace(int enable);
int timer_is_using_retrace(void);

/* ---- files ------------------------------------------------------------------------------- */

#define F_READ          "r"
#define F_WRITE         "w"
#define F_READ_PACKED   "rp"
#define F_WRITE_PACKED  "wp"
#define F_WRITE_NOPACK  "w!"
#define F_BUF_SIZE      4096
#define F_PACK_MAGIC    0x736C6821L
#define F_NOPACK_MAGIC  0x736C682EL
#define F_EXE_MAGIC     0x736C682BL
#define FA_NONE   0
#define FA_RDONLY 1
#define FA_HIDDEN 2
#define FA_SYSTEM 4
#define FA_LABEL  8
#define FA_DIREC  16
#define FA_ARCH   32
#define FA_ALL    (~FA_NONE)

typedef struct PACKFILE PACKFILE;
typedef struct PACKFILE_VTABLE {
    int (*pf_fclose)(void *userdata);
    int (*pf_getc)(void *userdata);
    int (*pf_ungetc)(int c, void *userdata);
    long (*pf_fread)(void *p, long n, void *userdata);
    int (*pf_putc)(int c, void *userdata);
    long (*pf_fwrite)(const void *p, long n, void *userdata);
    int (*pf_fseek)(void *userdata, int offset);
    int (*pf_feof)(void *userdata);
    int (*pf_ferror)(void *userdata);
} PACKFILE_VTABLE;

PACKFILE *pack_fopen(const char *filename, const char *mode);
PACKFILE *pack_fopen_vtable(const PACKFILE_VTABLE *vtable, void *userdata);
int pack_fclose(PACKFILE *f);
int pack_fseek(PACKFILE *f, int offset);
PACKFILE *pack_fopen_chunk(PACKFILE *f, int pack);
PACKFILE *pack_fclose_chunk(PACKFILE *f);
int pack_getc(PACKFILE *f);
int pack_putc(int c, PACKFILE *f);
int pack_feof(PACKFILE *f);
int pack_ferror(PACKFILE *f);
int pack_ungetc(int c, PACKFILE *f);
int pack_igetw(PACKFILE *f);
long pack_igetl(PACKFILE *f);
int pack_iputw(int w, PACKFILE *f);
long pack_iputl(long l, PACKFILE *f);
int pack_mgetw(PACKFILE *f);
long pack_mgetl(PACKFILE *f);
int pack_mputw(int w, PACKFILE *f);
long pack_mputl(long l, PACKFILE *f);
long pack_fread(void *p, long n, PACKFILE *f);
long pack_fwrite(const void *p, long n, PACKFILE *f);
char *pack_fgets(char *p, int max, PACKFILE *f);
int pack_fputs(const char *p, PACKFILE *f);
void packfile_password(const char *password);

int file_exists(const char *filename, int attrib, int *aret);
int exists(const char *filename);
long file_size(const char *filename);
uint64_t file_size_ex(const char *filename);
time_t file_time(const char *filename);
int delete_file(const char *filename);
char *get_filename(const char *path);
char *get_extension(const char *filename);
void put_backslash(char *filename);
char *fix_filename_case(char *path);
char *fix_filename_slashes(char *path);
char *fix_filename_path(char *dest, const char *path, int size);
char *canonicalize_filename(char *dest, const char *filename, int size);
char *make_absolute_filename(char *dest, const char *path, const char *filename, int size);
char *make_relative_filename(char *dest, const char *path, const char *filename, int size);
int is_relative_filename(const char *filename);
char *replace_filename(char *dest, const char *path, const char *filename, int size);
char *replace_extension(char *dest, const char *filename, const char *ext, int size);
char *append_filename(char *dest, const char *path, const char *filename, int size);
void get_executable_name(char *output, int size);
int find_allegro_resource(char *dest, const char *resource, const char *ext, const char *datafile,
                          const char *objectname, const char *envvar, const char *subdir, int size);

struct al_ffblk {
    int attrib;
    time_t time;
    long size;
    char name[512];
    void *ff_data;
};
int al_findfirst(const char *pattern, struct al_ffblk *info, int attrib);
int al_findnext(struct al_ffblk *info);
void al_findclose(struct al_ffblk *info);
int for_each_file_ex(const char *name, int in_attrib, int out_attrib,
                     int (*callback)(const char *filename, int attrib, void *param), void *param);

/* ---- datafiles -------------------------------------------------------------------------- */

#define DAT_ID(a, b, c, d) AL_ID(a, b, c, d)
#define DAT_MAGIC      DAT_ID('A','L','L','.')
#define DAT_FILE       DAT_ID('F','I','L','E')
#define DAT_DATA       DAT_ID('D','A','T','A')
#define DAT_FONT       DAT_ID('F','O','N','T')
#define DAT_SAMPLE     DAT_ID('S','A','M','P')
#define DAT_MIDI       DAT_ID('M','I','D','I')
#define DAT_PATCH      DAT_ID('P','A','T',' ')
#define DAT_FLI        DAT_ID('F','L','I','C')
#define DAT_BITMAP     DAT_ID('B','M','P',' ')
#define DAT_RLE_SPRITE DAT_ID('R','L','E',' ')
#define DAT_C_SPRITE   DAT_ID('C','M','P',' ')
#define DAT_XC_SPRITE  DAT_ID('X','C','M','P')
#define DAT_PALETTE    DAT_ID('P','A','L',' ')
#define DAT_PROPERTY   DAT_ID('p','r','o','p')
#define DAT_NAME       DAT_ID('N','A','M','E')
#define DAT_END        -1

typedef struct DATAFILE_PROPERTY { char *dat; int type; } DATAFILE_PROPERTY;
typedef struct DATAFILE { void *dat; int type; long size; DATAFILE_PROPERTY *prop; } DATAFILE;
typedef struct DATAFILE_INDEX { char *filename; long *offset; } DATAFILE_INDEX;

DATAFILE *load_datafile(const char *filename);
DATAFILE *load_datafile_callback(const char *filename, void (*callback)(DATAFILE *));
void unload_datafile(DATAFILE *dat);
DATAFILE *load_datafile_object(const char *filename, const char *objectname);
void unload_datafile_object(DATAFILE *dat);
DATAFILE *find_datafile_object(const DATAFILE *dat, const char *objectname);
const char *get_datafile_property(const DATAFILE *dat, int type);
void register_datafile_object(int id, void *(*load)(PACKFILE *f, long size), void (*destroy)(void *data));
void fixup_datafile(DATAFILE *data);
DATAFILE_INDEX *create_datafile_index(const char *filename);
DATAFILE *load_datafile_object_indexed(const DATAFILE_INDEX *index, int item);
void destroy_datafile_index(DATAFILE_INDEX *index);

/* ---- images ------------------------------------------------------------------------------ */

BITMAP *load_bitmap(const char *filename, RGB *pal);
BITMAP *load_bmp(const char *filename, RGB *pal);
BITMAP *load_bmp_pf(PACKFILE *f, RGB *pal);
BITMAP *load_pcx(const char *filename, RGB *pal);
BITMAP *load_pcx_pf(PACKFILE *f, RGB *pal);
BITMAP *load_tga(const char *filename, RGB *pal);
int save_bitmap(const char *filename, BITMAP *bmp, const RGB *pal);
int save_bmp(const char *filename, BITMAP *bmp, const RGB *pal);
int save_bmp_pf(PACKFILE *f, BITMAP *bmp, const RGB *pal);
int save_pcx(const char *filename, BITMAP *bmp, const RGB *pal);
int save_pcx_pf(PACKFILE *f, BITMAP *bmp, const RGB *pal);
void register_bitmap_file_type(const char *ext, BITMAP *(*load)(const char *filename, RGB *pal),
                               int (*save)(const char *filename, BITMAP *bmp, const RGB *pal));
FONT *load_font(const char *filename, RGB *pal, void *param);
/* param: NULL, or char *names[2] = { font object, palette object } (either NULL: the first) */
FONT *load_dat_font(const char *filename, RGB *pal, void *param);
/* glyphs in boxes of the border colour (the top-left pixel), from ' ' on */
FONT *grab_font_from_bitmap(BITMAP *bmp);
/* a font from a picture of a glyph grid (PCX, BMP): grab_font_from_bitmap's rules */
FONT *load_bitmap_font(const char *filename, RGB *pal, void *param);
/* kept: a colour font draws with its mask colour clear at every depth */
void make_trans_font(FONT *f);

/* ---- sound ------------------------------------------------------------------------------- */

#define DIGI_AUTODETECT -1
#define DIGI_NONE 0
#define MIDI_AUTODETECT -1
#define MIDI_NONE 0
#define MIDI_TRACKS 32
#define PLAYMODE_PLAY 0
#define PLAYMODE_LOOP 1
#define PLAYMODE_FORWARD 0
#define PLAYMODE_BACKWARD 2
#define PLAYMODE_BIDIR 4
#define DIGI_VOICES 64

typedef struct SAMPLE {
    int bits;                       /* 8 or 16 */
    int stereo;
    int freq;
    int priority;
    unsigned long len;              /* in sample frames */
    unsigned long loop_start;
    unsigned long loop_end;
    unsigned long param;
    void *data;                     /* unsigned 8-bit, or unsigned 16-bit (0x8000 is silence) */
} SAMPLE;
typedef struct MIDI {
    struct { unsigned char *data; int len; } track[MIDI_TRACKS];
    int divisions;
} MIDI;
typedef struct DIGI_DRIVER { int id; const char *name; const char *desc; const char *ascii_name; int voices; } DIGI_DRIVER;
typedef struct MIDI_DRIVER { int id; const char *name; const char *desc; const char *ascii_name; int voices; } MIDI_DRIVER;
extern DIGI_DRIVER *digi_driver;

/* the other drivers: one each, read for their names */
typedef struct TIMER_DRIVER { int id; const char *name; const char *desc; const char *ascii_name; } TIMER_DRIVER;
typedef struct KEYBOARD_DRIVER { int id; const char *name; const char *desc; const char *ascii_name; int autorepeat; } KEYBOARD_DRIVER;
typedef struct MOUSE_DRIVER { int id; const char *name; const char *desc; const char *ascii_name; } MOUSE_DRIVER;
typedef struct JOYSTICK_DRIVER { int id; const char *name; const char *desc; const char *ascii_name; } JOYSTICK_DRIVER;
extern TIMER_DRIVER *timer_driver;
extern KEYBOARD_DRIVER *keyboard_driver;
extern MOUSE_DRIVER *mouse_driver;
extern JOYSTICK_DRIVER *joystick_driver;
extern MIDI_DRIVER *midi_driver;
extern volatile long midi_pos;
extern volatile long midi_time;
extern long midi_loop_start, midi_loop_end;

int detect_digi_driver(int driver_id);
int detect_midi_driver(int driver_id);
void reserve_voices(int digi_voices, int midi_voices);
void set_volume_per_voice(int scale);
int install_sound(int digi, int midi, const char *cfg_path);
int get_mixer_quality(void);
void set_mixer_quality(int quality);
int get_mixer_voices(void);
int get_mixer_frequency(void);
int get_mixer_bits(void);
int get_mixer_channels(void);
void remove_sound(void);
void set_volume(int digi_volume, int midi_volume);
void get_volume(int *digi_volume, int *midi_volume);
void set_hardware_volume(int digi_volume, int midi_volume);
SAMPLE *load_sample(const char *filename);
SAMPLE *load_wav(const char *filename);
SAMPLE *load_wav_pf(PACKFILE *f);
SAMPLE *load_voc(const char *filename);
SAMPLE *create_sample(int bits, int stereo, int freq, int len);
void destroy_sample(SAMPLE *spl);
int save_sample(const char *filename, SAMPLE *spl);
int play_sample(const SAMPLE *spl, int vol, int pan, int freq, int loop);
void stop_sample(const SAMPLE *spl);
void adjust_sample(const SAMPLE *spl, int vol, int pan, int freq, int loop);
int allocate_voice(const SAMPLE *spl);
void deallocate_voice(int voice);
void reallocate_voice(int voice, const SAMPLE *spl);
void release_voice(int voice);
void voice_start(int voice);
void voice_stop(int voice);
void voice_set_priority(int voice, int priority);
SAMPLE *voice_check(int voice);
void voice_set_playmode(int voice, int playmode);
int voice_get_position(int voice);
void voice_set_position(int voice, int position);
int voice_get_volume(int voice);
void voice_set_volume(int voice, int volume);
int voice_get_frequency(int voice);
void voice_set_frequency(int voice, int frequency);
int voice_get_pan(int voice);
void voice_set_pan(int voice, int pan);
MIDI *load_midi(const char *filename);
void destroy_midi(MIDI *midi);
int play_midi(MIDI *midi, int loop);
int play_looped_midi(MIDI *midi, int loop_start, int loop_end);
void stop_midi(void);
void midi_pause(void);
void midi_out(unsigned char *data, int length);
void midi_resume(void);
int midi_seek(int target);
int get_midi_length(MIDI *midi);
/* allegro4.library: mix 'frames' stereo frames of the playing samples into
 * out (signed 16-bit, interleaved). The library calls it itself; a test or
 * a game with its own audio output may call it. */
void a4_mix_s16stereo(int16_t *out, int frames, int rate);

/* ---- GUI: alert (the dialog engine is in a4_gui.h) ----------------------------------------------------------------- */

int alert(const char *s1, const char *s2, const char *s3, const char *b1, const char *b2, int c1, int c2);
int alert3(const char *s1, const char *s2, const char *s3, const char *b1, const char *b2, const char *b3,
           int c1, int c2, int c3);

#ifdef __cplusplus
}
#endif

/* the old 'pallete' names (Allegro 4's alcompat.h) */
#ifndef ALLEGRO_NO_COMPATIBILITY
#define PALLETE                     PALETTE
#define black_pallete               black_palette
#define desktop_pallete             desktop_palette
#define set_pallete                 set_palette
#define get_pallete                 get_palette
#define set_pallete_range           set_palette_range
#define get_pallete_range           get_palette_range
#define fli_pallete                 fli_palette
#define pallete_color               palette_color
#define DAT_PALLETE                 DAT_PALETTE
#define select_pallete              select_palette
#define unselect_pallete            unselect_palette
#define generate_332_pallete        generate_332_palette
#define generate_optimised_pallete  generate_optimized_palette
#endif

/* the dialog engine: game-side, in liballeg.a (not library calls) */
#include "a4_gui.h"

#endif
