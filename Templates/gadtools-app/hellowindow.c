/* A GadTools program for AmigaOS 3.2 and AROS, from the Open SDK's template.
 * It follows the Open apps' rules: font sensitive, every action a button or
 * a menu item, underlined keys, Esc to close, plain words in a status line.
 * OpenLook themes it when installed; without it, it is the OS's own look.
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence: your own
 * program built from it is yours to licence as you like. */
#include <exec/types.h>
#include <intuition/intuition.h>
#include <intuition/gadgetclass.h>
#include <libraries/gadtools.h>
#include <graphics/text.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include <proto/gadtools.h>
#include <proto/graphics.h>

#ifndef __AROS__
typedef ULONG IPTR;     /* AROS has it; NDK 3.2 doesn't */
#endif

static const char version[] = "$VER: HelloWindow 1.0 (6.10.2026)";

enum { GID_NAME = 1, GID_SAY, GID_STATUS };
enum { MID_SAY = 1, MID_ABOUT, MID_QUIT };

static struct NewMenu menus[] = {
    { NM_TITLE, (STRPTR)"Project", NULL, 0, 0, NULL },
    { NM_ITEM, (STRPTR)"Say hello", (STRPTR)"H", 0, 0, (APTR)MID_SAY },
    { NM_ITEM, (STRPTR)"About...", (STRPTR)"?", 0, 0, (APTR)MID_ABOUT },
    { NM_ITEM, NM_BARLABEL, NULL, 0, 0, NULL },
    { NM_ITEM, (STRPTR)"Quit", (STRPTR)"Q", 0, 0, (APTR)MID_QUIT },
    { NM_END, NULL, NULL, 0, 0, NULL },
};

static char status[80] = "Type a name and choose Say hello.";

static void say(struct Window *win, struct Gadget *name, struct Gadget *st)
{
    STRPTR s = ((struct StringInfo *)name->SpecialInfo)->Buffer;
    int i = 0, j;
    const char *pre = "Hello, ";
    while (pre[i]) { status[i] = pre[i]; i++; }
    for (j = 0; s[j] && i < (int)sizeof status - 2; j++) status[i++] = s[j];
    if (!j) { const char *w = "whoever you are"; for (j = 0; w[j]; j++) status[i++] = w[j]; }
    status[i++] = '!'; status[i] = 0;
    GT_SetGadgetAttrs(st, win, NULL, GTTX_Text, (IPTR)status, TAG_DONE);
}

int main(void)
{
    struct Screen *scr = LockPubScreen(NULL);
    APTR vi = NULL;
    struct Gadget *glist = NULL, *g, *name = NULL, *st = NULL;
    struct Menu *menu = NULL;
    struct Window *win = NULL;
    struct NewGadget ng = { 0 };
    int done = 0;
    UWORD fh, m, w, lw;
    if (!scr) return 20;
    vi = GetVisualInfo(scr, TAG_DONE);
    /* Everything is sized from the screen's font, so any font works. */
    fh = scr->Font->ta_YSize;
    m = 8;
    lw = TextLength(&scr->RastPort, (STRPTR)"Name", 4) + m;
    w = 30 * fh;
    g = CreateContext(&glist);
    ng.ng_TextAttr = scr->Font;
    ng.ng_VisualInfo = vi;
    ng.ng_LeftEdge = scr->WBorLeft + m + lw;
    ng.ng_TopEdge = scr->WBorTop + fh + 1 + m;
    ng.ng_Width = w - lw - 2 * m;
    ng.ng_Height = fh + 6;
    ng.ng_GadgetText = (STRPTR)"_Name";
    ng.ng_GadgetID = GID_NAME;
    ng.ng_Flags = PLACETEXT_LEFT;
    name = g = CreateGadget(STRING_KIND, g, &ng, GTST_MaxChars, 40, GT_Underscore, '_', TAG_DONE);
    ng.ng_TopEdge += ng.ng_Height + m;
    ng.ng_LeftEdge = scr->WBorLeft + m;
    ng.ng_Width = w - 2 * m;
    ng.ng_GadgetText = (STRPTR)"_Say hello";
    ng.ng_GadgetID = GID_SAY;
    ng.ng_Flags = PLACETEXT_IN;
    g = CreateGadget(BUTTON_KIND, g, &ng, GT_Underscore, '_', TAG_DONE);
    ng.ng_TopEdge += ng.ng_Height + m;
    ng.ng_GadgetText = NULL;
    ng.ng_GadgetID = GID_STATUS;
    st = g = CreateGadget(TEXT_KIND, g, &ng, GTTX_Text, (IPTR)status, GTTX_Border, TRUE, TAG_DONE);
    menu = CreateMenus(menus, TAG_DONE);
    if (g && menu && LayoutMenus(menu, vi, GTMN_NewLookMenus, TRUE, TAG_DONE))
        win = OpenWindowTags(NULL,
            WA_Title, (IPTR)"HelloWindow", WA_PubScreen, (IPTR)scr,
            WA_InnerWidth, w, WA_InnerHeight, ng.ng_TopEdge + ng.ng_Height + m - scr->WBorTop - fh - 1,
            WA_Gadgets, (IPTR)glist, WA_NewLookMenus, TRUE,
            WA_DragBar, TRUE, WA_DepthGadget, TRUE, WA_CloseGadget, TRUE, WA_Activate, TRUE,
            WA_IDCMP, IDCMP_CLOSEWINDOW | IDCMP_REFRESHWINDOW | IDCMP_MENUPICK | IDCMP_VANILLAKEY | BUTTONIDCMP | STRINGIDCMP,
            TAG_DONE);
    UnlockPubScreen(NULL, scr);
    if (win) {
        SetMenuStrip(win, menu);
        GT_RefreshWindow(win, NULL);
        while (!done) {
            struct IntuiMessage *msg;
            WaitPort(win->UserPort);
            while ((msg = GT_GetIMsg(win->UserPort))) {
                ULONG cls = msg->Class;
                UWORD code = msg->Code;
                struct Gadget *hit = (struct Gadget *)msg->IAddress;
                GT_ReplyIMsg(msg);
                switch (cls) {
                case IDCMP_CLOSEWINDOW: done = 1; break;
                case IDCMP_REFRESHWINDOW: GT_BeginRefresh(win); GT_EndRefresh(win, TRUE); break;
                case IDCMP_GADGETUP: if (hit->GadgetID == GID_SAY || hit->GadgetID == GID_NAME) say(win, name, st); break;
                case IDCMP_VANILLAKEY:
                    if (code == 27) done = 1;                                   /* Esc */
                    else if (code == 's' || code == 'S') say(win, name, st);
                    else if (code == 'n' || code == 'N') ActivateGadget(name, win, NULL);
                    break;
                case IDCMP_MENUPICK:
                    while (code != MENUNULL) {
                        struct MenuItem *it = ItemAddress(menu, code);
                        if (!it) break;
                        switch ((IPTR)GTMENUITEM_USERDATA(it)) {
                        case MID_SAY: say(win, name, st); break;
                        case MID_ABOUT:
                            GT_SetGadgetAttrs(st, win, NULL, GTTX_Text, (IPTR)"HelloWindow 1.0, from the Open SDK.", TAG_DONE);
                            break;
                        case MID_QUIT: done = 1; break;
                        }
                        code = it->NextSelect;
                    }
                    break;
                }
            }
        }
        ClearMenuStrip(win);
        CloseWindow(win);
    }
    FreeMenus(menu);
    FreeGadgets(glist);
    FreeVisualInfo(vi);
    (void)version;
    return win ? 0 : 20;
}
