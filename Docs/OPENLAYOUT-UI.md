# Windows in HTML and CSS: OpenLayout UI

OpenLayout UI lets a program describe its window in HTML and CSS instead of
placing GadTools gadgets by hand. OpenLayout lays the window out, the
OpenGadTools theme the user chose draws it, and the program's own C
functions are called back when something happens. It has buttons,
checkboxes, radio buttons, one-line fields, lists and trees, tabs and
progress bars, in rows and columns that share the room as CSS flex boxes do.

GadTools stays the way to make a plain window. OpenLayout UI is for windows
GadTools makes badly: a tree beside a panel, panes that grow with the
window, pages of settings.

Its reference is in OpenLayout's repository, `DalsinAI/gfopenlayout`:
`docs/GFOpenLayout-UI.md` (the tags, the CSS, the events, every call) and
`include/gfopenlayout_ui.h`.

## A window

```c
#include "gfopenlayout_ui.h"
#include "gfopenlayout_ui_amiga.h"

static void ok_pressed(olui *ui, const olui_event *ev, void *data)
{
    printf("Hello, %s\n", olui_get_text(olui_find(ui, "name")));
}

...
win = OpenWindowTags(NULL, WA_Title, (ULONG)"Hello", WA_Width, 360, WA_Height, 120,
                     WA_SizeGadget, TRUE, WA_CloseGadget, TRUE, WA_DragBar, TRUE,
                     WA_ReportMouse, TRUE, WA_IDCMP, olui_amiga_idcmp(), TAG_DONE);
ui = olui_new();
a = olui_amiga_new(ui, win);
olui_amiga_theme(a, NULL);              /* the theme OpenPrefs Look chose, first */
olui_load(ui,
    "<row><label>Name</label><input id=name style='flex:1'></row>"
    "<row style='justify-content:end'><button id=ok>OK</button></row>",
    "label{width:60px}", err, sizeof err);
olui_on(ui, "ok", OLUI_CLICK, ok_pressed, NULL);
olui_amiga_layout(a);
/* each IDCMP message: olui_amiga_event(a, msg), reply it, then olui_amiga_draw(a) */
```

`Templates/olui-app` is this program whole, ready to copy.

## Building

OpenLayout UI is a link library, `libolui.a`, built in OpenLayout's
repository with the os32 stove:

```sh
OGT_ROOT=<amicradle-guest>/libraries/opengadtools \
SPECS=<this SDK>/Lib/m68k-soft-m68040.specs ./build-ui-amiga.sh
```

It uses no floating point, so programs are built soft float like every
Open program: `-m68040` and this SDK's specs file. The template's
`Makefile` takes `OLUI` (OpenLayout's repository, with `build-amiga/ui/`
built in it) and builds with OpenNDK's headers or NDK 3.2's.

## The rules it keeps

- The theme comes first and the program's CSS after it, so a program can
  change anything the theme set.
- Every widget a program wants to hear from has an `id`.
- A handler can change any widget; the window is laid out again after it.
- Text is UTF-8. The Amiga glue turns it into Latin-1 for the bitmap fonts.

## A strip of a window (gfopenlayout.library 11)

A program that draws most of its window itself, such as a browser with its
page, can give OpenLayout UI only a strip of it, for a toolbar or a status
bar:

```c
if (!olui_amiga_strip(a, 0, 0, 0, 40))  /* a toolbar 40 pixels tall, as wide as the window */
    ...                                 /* 0: a version 10 library, which takes the whole window */
olui_amiga_keys(a, OLUI_AMIGA_KEYS_FOCUS);  /* keys only while one of its widgets has the focus */
```

- `x` and `y` are from the window's inside. A `w` or `h` of 0 runs to its
  edge. A `y` below 0 counts from the bottom, so `0, -20, 0, 0` is a status
  bar.
- The buffer is the strip's size, and only presses inside the strip are
  taken.
- `IDCMP_REFRESHWINDOW` and `IDCMP_NEWSIZE` draw the strip and come back
  as `OLUI_AMIGA_NONE`, for the program's own refresh. IntuiTicks always
  come back as `OLUI_AMIGA_NONE` in a strip too.
- With `OLUI_AMIGA_KEYS_FOCUS`, a press outside the strip takes the focus
  away. A click or `olui_focus` gives it back, not Tab.
- A window opened without `IDCMP_VANILLAKEY` works too: the glue maps its
  RAWKEYs with keymap.library.
- Pop-ups (a select's list, a menu, a tooltip) are drawn inside the strip,
  so open those in a window of the program's own.
