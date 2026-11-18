# GFOpenDraw design, v0.2

Team, 30 October 2026.

Renamed from GFOpenPaint for the GFOffice suite on 8 November 2026. The rename
keeps the original engine, history and MIT provenance; it does not introduce a
separate drawing implementation.

## What it is

Our own paint program for AmigaOS 3.2, written from scratch in C, in the spirit
of Deluxe Paint. SacredTrees asked for Deluxe Paint to be rewritten; the
"next GFOpenBench apps" review recommended doing it as our own native program,
studying Steffest's DPaint.js (MIT) for what such a program does, rather than
porting GrafX2 (GPL v2, which our own-code rule rules out). Nothing is taken
from DPaint.js or Deluxe Paint: the tools, the keys and the feel are studied,
the code is ours.

Target: 68040 under AmigaOS 3.2.3, soft float (the engine uses integers only),
on Workbench, from an AGA screen in 16 colours to GFOpenRTG true colour. No
GFOpenGPU, no MUI, no class libraries beyond the OS.

## How it is built

| Part | Where | What |
|---|---|---|
| Engine | `engine/`, `include/gfopendraw.h` | The picture (one byte a pixel, 2 to 256 colours), brushes, every tool, undo and redo, the true-colour to palette step. Plain C, no Amiga headers, host tests in `tests/host`. |
| Library | `library/` | The engine as `gfopendraw.library`, which the programs open ("The library", below). |
| Picture on screen | `app/op_view.c` | The canvas, the colours in use, the palette strip, the toolbox's pictures: shared by both programs. |
| Window | `app/op_chrome_gt.c` / `app/op_chrome_ol.c` | The toolbox and the status line, and where everything goes: GadTools and GFOpenGadTools (GFOpenDraw), or GFOpenLayout UI (GFOpenDrawOL). |
| Files | `app/op_file.c` | Datatypes in and out; asl requesters; EasyRequest questions. |
| Small windows | `app/op_dialog.c` / `app/op_dialog_ol.c` | New picture, Palette: GadTools, or GFOpenLayout UI. |
| Program | `app/opendraw.c` | Start-up, menus, keys, the mouse, the event loop: shared. |

The engine is the part GFOpenIconEdit is meant to reuse: an icon is a small
picture with a palette, painted with the same tools. Its files come from
GFOpenBench's `icon_core.c`, so the engine knows nothing of files.

## The library

Dale, 17 November 2026: GFOffice's programs are not monoliths; each has its
library, and they share code where it makes sense. GFOpenDraw's is
`gfopendraw.library`, the engine and nothing else.

- **Calls:** `library/gfopendraw_lib.sfd`, the engine's own calls with their
  names and types, new ones at the end. The four that take a structure by
  value (`op_nearest`, `op_brush_grab`, `op_undo_restore`, `op_undo_end`) go
  as `_p` calls with a pointer; `gfopendraw.h` keeps the by-value names as
  macros over them, so a program's code is the same linked or on the library.
- **Made from the SFD:** `library/gfopendraw_calls.h` (the library side, with
  GFOffice's `gen-lib-calls.py`) and `library/sdk` (with GFOpenSDK's
  `ndkgen.py`), by `scripts/gen-sdk.sh`; `--check` says when one is stale.
- **The library file:** `library/gfopendraw_library.c`, the resident tag,
  vectors and open/close/expunge, as GFOffice's `owf*.library` files are.
- **No C library:** `library/gfd_runtime.c` gives the few calls the engine
  makes: `malloc` and the others over one Exec pool behind a semaphore (what
  the library allocates goes back to it through the engine's own `_free`
  calls), and `memcpy` (Exec's `CopyMem`), `memset`, `memmove`, `memcmp`,
  `abs`. Tasks paint at once: the engine keeps no state between calls.
- **Versions:** a program checks `op_struct_size` against its own sizes
  (`gfd_open`); a structure that grows makes a new library version.
- **Tests:** on the host, `tests/host/run.sh` and `make test`: the engine,
  `op_lib.c`'s calls, the runtime (`test_runtime.c`), the SFD against the
  headers and registers (`check_sfd.py`), and the C calls the runtime must
  give (`check-library-libc.sh`). On the Amiga, `GFDLibTest`: the same engine
  tests through the library.
- **Shared code:** the engine has no file, PDF, fill or text code, so it
  shares nothing with GFOffice's `owf.library` today. The programs' savers
  (`app/op_file.c`, through datatypes) move to the shared picture writers in
  GFOffice's core once a library exports an indexed (palette) PNG and ILBM
  writer, rather than gfopendraw building a pinned copy of libowf.

## The window

- One window on Workbench (or a public screen named with PUBSCREEN), first 800
  x 600 in the middle of the screen, or the whole of a smaller one.
- The toolbox on the left, two cells a row as Deluxe Paint's: four built-in
  brushes, then freehand, dotted freehand, line, airbrush, rectangle, circle,
  ellipse, fill, brush, pick colour, zoom in, zoom out, undo, redo. A shape's
  cell is split on the diagonal: the upper left half picks the outline, the
  lower right half the filled shape.
- Under the toolbox, the foreground colour over the background colour; a click
  there opens the Palette.
- The canvas in a sunken bevel, the palette strip along the foot (one row up to
  32 colours, more rows above that), and the status line: tool, the pixel under
  the pointer (or the picture's size), the colours, the zoom.
- Menus Project, Edit, View, Settings, Help, as the GFOpen Apps rule has them.
- The right mouse button is GFOpenDraw's over the canvas and the palette (the
  background colour, as Deluxe Paint's), and shows the menus everywhere else.

## Full screen

- View ▸ Full screen (Amiga-F, F9, or `FULLSCREEN` from the Shell) moves
  GFOpenDraw onto a screen of its own: the Workbench's mode and size
  (`SA_LikeWorkbench`), one plane more than the picture needs on a palette
  screen of fewer colours (so the picture's colours and the screen's own pens
  both fit), else the Workbench's depth. One borderless backdrop window covers
  it below the screen's title bar, which keeps the menus and shows the
  picture's name. The picture, its undo steps and the brush carry over; if the
  screen can't be opened, GFOpenDraw stays in its window and says why.
- View ▸ Hide tools (F10, as Deluxe Paint's) hides the toolbox, the palette and
  the status line, in a window or full screen, so the picture fills it all.

## GFOpenDrawOL: the windows in GFOpenLayout UI

SacredTrees asked for a version of GFOpenDraw on GFOpenLayout UI, extending it
where needed. GFOpenDrawOL is that: the same program built with
`op_chrome_ol.c` and `op_dialog_ol.c` in place of the GadTools pair.

- The main window is markup: a column of nine rows of two `button`s, each
  holding an `img` that GFOpenDraw draws (`op_glyph`, the same pictures as
  GFOpenDraw's); a `div` for the colours in use; the canvas `div` in a frame
  over the palette strip `div`; a `row` of labels for the status line. Sizes
  come from the theme font's height, colours from the theme's keys.
- The canvas, the palette strip and the colours are `olui_amiga_own` boxes:
  GFOpenDraw draws them in the picture's own colours, and only redraws the
  picture when its box moved or was covered, not when a button lights up.
- The mouse over those boxes, a stroke under way, the right button, every
  key and the menus stay GFOpenDraw's; GFOpenLayout UI gets the pointer over
  the buttons. The tool in use is `button:checked`; Undo and Redo are
  `:disabled` when there is nothing to do.
- The status line's position is set at most ten times a second (each
  change lays the window out again).
- New picture: two fields and eight radio buttons. Palette: the swatches
  (drawn by GFOpenDraw), three `slider`s with their values, Spread, Copy, Use
  and Cancel. Return in a field makes the picture; Esc cancels.
- F10 and Full screen build the window's markup again for the new room.

What GFOpenLayout UI needed for it (gfopenlayout, GFOpenLayout UI 0.2):

- `slider` (min, max, value; dragged, keyed, OLUI_CHANGE as it moves), for
  the Palette: sliders were on its "not yet" list.
- `olui_box`: where a widget is, for the shape buttons' filled half.
- `olui_amiga_images`: the Amiga glue drew nothing for `img`; now a program
  draws its pictures there, in buttons too.
- `img` stays inline (it was made a block, so GFOpenLayout never placed it).

## Look

- `ogt_look_load` gives the theme, light or dark, the accent, Lite and (with
  GFOpenGadTools' Scale change) Look's Scale; `ogt_open_font` opens the theme's
  font at that size. Every measure in the window comes from the font's height,
  so Scale grows the toolbox, the strip and the margins with it.
- Everything but the picture is drawn with GFOpenGadTools in the theme's keys
  (`window`, `button`, `accent`, `track`, `string.shadow`...). No literal colours.
- The picture is drawn in its own colours: exactly through cybergraphics'
  `WriteLUTPixelArray` on a true-colour screen (GFOpenRTG, Picasso96), else with
  `WriteChunkyPixels` in the nearest pens (`ObtainBestPen`, shared).

## Files

- Open: any picture the system has a datatype for. Up to 256 colours it is
  read as it is (`PDTM_READPIXELARRAY`, LUT8); a true-colour picture is read as
  RGB and given the 256 colours it uses most (`engine/op_quant.c`).
- Save: IFF ILBM through picture.datatype's own writer (`DTM_WRITE`,
  `DTWM_IFF`) on an empty picture object; PNG through gfopenpng.datatype
  (`DTWM_RAW`). GFOpenDraw writes no file format itself.
- Safe saving: into a short free name beside it (`OP_tmpN`, so a 30-character
  file system can neither refuse it nor cut it back to the file's own name),
  which takes the name only once whole and closed.

## Phase 2 (not built)

- Text, polygon and curve tools; gradient fills; symmetry; the stencil.
- Brush resize and bend; the spare page (J).
- Colour cycling ranges saved in ILBM (CRNG): needs the ILBM datatype to write
  them, so it goes into gfopendatatypes first.
- A FULLSCREEN ToolType, and the picture's own screen mode (Full screen now
  takes the Workbench's).
- Window size and place remembered; Buttons style for the toolbox.
- GFOpenIconEdit on the same engine: built (README, "GFOpenIconEdit"). Still to do: writing
  PNG and ARGB icons back as true colour (needs a deflate writer), the icon's fields
  (default tool, tool types) in a window of its own.
