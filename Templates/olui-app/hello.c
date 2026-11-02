/* A window in HTML and CSS: a name and an OK button (OpenLayout UI).
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#include <exec/types.h>
#include <intuition/intuition.h>
#include <dos/dos.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>

#include <string.h>

#include "gfopenlayout_ui.h"
#include "gfopenlayout_ui_amiga.h"

static const char version[] = "$VER: HelloUI 0.1 (30.10.2026) AmiCradle Team";

static const char markup[] =
    "<row><label>Name</label><input id=name placeholder='Your name' style='flex:1'></row>"
    "<label id=answer> </label>"
    "<spacer></spacer>"
    "<row style='justify-content:end'><button id=ok>OK</button><button id=quit>Quit</button></row>";

static const char css[] = "label{width:60px} #answer{width:auto} button{width:70px}";

static int done;

static void ok_pressed(olui *ui, const olui_event *ev, void *data)
{
    static char line[128];
    const char *name = olui_get_text(olui_find(ui, "name"));
    (void)ev; (void)data;
    strncpy(line, "Hello, ", sizeof(line) - 1);
    strncat(line, name[0] ? name : "whoever you are", sizeof(line) - strlen(line) - 1);
    olui_set_text(ui, olui_find(ui, "answer"), line);
}

static void quit_pressed(olui *ui, const olui_event *ev, void *data)
{
    (void)ui; (void)ev; (void)data;
    done = 1;
}

int main(void)
{
    struct Window *win;
    olui *ui = NULL;
    olui_amiga *a = NULL;
    char err[128];
    (void)version;

    win = OpenWindowTags(NULL, WA_Title, (ULONG)"Hello", WA_Width, 360, WA_Height, 140,
                         WA_MinWidth, 240, WA_MinHeight, 110, WA_MaxWidth, ~0UL, WA_MaxHeight, ~0UL,
                         WA_DragBar, TRUE, WA_DepthGadget, TRUE, WA_CloseGadget, TRUE, WA_SizeGadget, TRUE,
                         WA_Activate, TRUE, WA_SimpleRefresh, TRUE, WA_ReportMouse, TRUE,
                         WA_IDCMP, olui_amiga_idcmp(), TAG_DONE);
    if (!win) return RETURN_FAIL;
    if ((ui = olui_new()) && (a = olui_amiga_new(ui, win))) {
        olui_amiga_theme(a, NULL);
        if (olui_load(ui, markup, css, err, sizeof(err))) {
            olui_on(ui, "ok", OLUI_CLICK, ok_pressed, NULL);
            olui_on(ui, "name", OLUI_SUBMIT, ok_pressed, NULL);
            olui_on(ui, "quit", OLUI_CLICK, quit_pressed, NULL);
            olui_focus(ui, olui_find(ui, "name"));
            if (olui_amiga_layout(a)) {
                while (!done) {
                    struct IntuiMessage *m;
                    if (Wait((1UL << win->UserPort->mp_SigBit) | SIGBREAKF_CTRL_C) & SIGBREAKF_CTRL_C) break;
                    while ((m = (struct IntuiMessage *)GetMsg(win->UserPort))) {
                        if (olui_amiga_event(a, m) == OLUI_AMIGA_CLOSE) done = 1;
                        ReplyMsg(&m->ExecMessage);
                    }
                    olui_amiga_draw(a);
                }
            }
        } else {
            Printf((STRPTR)"HelloUI: %s\n", (ULONG)err);
        }
    }
    olui_amiga_free(a);
    olui_free(ui);
    CloseWindow(win);
    return RETURN_OK;
}
