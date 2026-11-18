# allegro4.library

The Allegro 4 API for AmigaOS 3.x (68040), drawing and reading the keyboard,
mouse and pads through acgame.library, so Allegro 4 games run on AGA and RTG.
Written for GFOS; its own code, not Allegro's.

## For a game

Build the game against `include/allegro.h` and link `liballeg.a`. At the first
Allegro call the stubs ask acgame.library for Allegro 4
(`ACG_OpenAllegro(4)`, acgame.library 1.2), or with an older acgame.library
open `allegro4.library` themselves: the game's own `Libs/` drawer first, then
`LIBS:`. Ship `allegro4.library` and `acgame.library` in the game's `Libs/`.

Each game that opens the library gets its own state and its own
acgame.library, so two Allegro games can run at once.

## What is there

Bitmaps, sub-bitmaps, clipping and drawing modes; blits, masked and stretched
blits, sprites (flipped, lit, translucent, rotated, scaled, RLE);
primitives; palettes, fades, colour, light and translucency tables; keyboard
(`key[]`, `readkey`, the callbacks), mouse and joystick; timers on a task of
their own (`install_int_ex`, `rest`, `retrace_count`); packfiles with
Allegro's LZSS, datafiles (`load_datafile`, `load_datafile_object`,
`file.dat#OBJECT`); PCX and BMP; samples, WAV and a 22050 Hz mixer; fonts
from datafiles and an 8x8 built-in font; `al_findfirst` and file names;
the GUI: dialogs (`do_dialog`, `init_dialog`/`update_dialog`/`shutdown_dialog`,
`popup_dialog`) and the standard objects (`d_box_proc`, `d_button_proc`,
`d_check_proc`, `d_radio_proc`, `d_edit_proc`, `d_list_proc`, `d_textbox_proc`,
`d_slider_proc`, `d_keyboard_proc` and the text ones), and menus (`do_menu`,
`init_menu`/`update_menu`/`shutdown_menu`, the `d_menu_proc` menu bar, the
`gui_menu_draw_menu*` hooks), run in the game's own code; FLI and FLC
animations (`open_fli`, `open_memory_fli`, `next_fli_frame`, `play_fli`);
`gfx_mode_select`, `palette_color`, `get_config_text` and the GUI names
Allegro's internal header gives (`gui_shadow_box_proc`, `gui_mouse_focus`,
`_default_font`...).

Colour depths 8, 15, 16, 24 and 32: truecolour bitmaps, `makecol`/`getr` for
every depth, the truecolour blenders (`set_trans_blender`, `set_alpha_blender`,
`set_add_blender`, `set_multiply_blender` and the rest), `set_color_conversion`
and loading images at the screen's depth. A truecolour screen is shown on
ACGame's 8-bit screen through a 6x7x6 colour cube; `desktop_color_depth()`
stays 8. Config files (`set_config_file`, `get_config_*`, `set_config_*`,
`push_config_state`/`pop_config_state`, override files) are read and written.

Module music through DUMB's Allegro layer (`aldumb.h`: `dumb_load_mod_quick`,
`al_start_duh`, `al_poll_duh`, `al_pause_duh`...) plays through
gfopenmusic.library (MOD, S3M, XM, IT via gfopenmodule.datatype, to AHI),
looping as DUMB does; without that library the players run silent.
Allegro 4's old names (`PALLETE`, `get_pallete`...), `bmp_read*`/`bmp_write*`
at every depth, `load_bitmap_font` and the DOS driver ids (`GFX_VGA`,
`GFX_MODEX`...) are there.

Music (1.1): MIDI plays on GFOpenSynth (`gfopensynth.library`, General MIDI
and MT-32), opened when a game installs sound with a MIDI driver. On a machine
with AkikoPlus's MIDI port the synth in the machine plays it, as a real one
plugged into the port would. With no port the synth runs from a SoundFont
(`DEVS:SoundFonts/default.sf2`, or `ENV:GFOpenSynth/SoundFont`) and is mixed
with the samples, so the music goes out the way they do: acgame.library, to
AHI or Paula. `play_midi`, `play_looped_midi`, `stop_midi`, `midi_pause`,
`midi_resume`, `midi_seek`, `midi_out`, `get_midi_length`, `midi_pos`,
`midi_time` and the MIDI volume work. Without gfopensynth.library (or
without a port and a SoundFont) music is silent and the game runs on.
A game built with liballeg 1.0 gets music too; only its `midi_time` stays 0.

Samples are mixed and pushed to acgame.library, which plays them from
acgame.library 1.3. Games written for Unix paths
work: "./data" and "../save" become "data" and "/save".

## Building

    tests/run_tests.sh     host unit tests (737 checks; SANITIZE="-fsanitize=address,undefined")
    build-amiga.sh         allegro4.library, liballeg.a, tests/A4LibSmoke (STOVE=, OUT=)
    tools/gen_lib.py       the library's calls from include/allegro.h
    package.sh OUT DEST VERSION   the GFOpenUp part (Parts/Allegro4) and the SDK

`library/calls.txt` fixes the order of the library's calls. New calls only go
at its end, so a game built against an older library runs on a later one.

Copyright (c) 2026 AmiCradle Team. MIT licence (see LICENSE).
