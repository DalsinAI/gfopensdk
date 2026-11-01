/* OpenNDK: a small program built only with OpenNDK, to show the
 * proto/ headers, the inline calls and libamiga.a's helpers working
 * together. tests/run.sh compiles it and looks for the calls it expects.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */
#include <exec/types.h>
#include <exec/execbase.h>
#include <dos/dos.h>
#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <clib/alib_protos.h>

struct ExecBase *SysBase;
struct DosLibrary *DOSBase;
struct GfxBase *GfxBase;
struct IntuitionBase *IntuitionBase;

int hello(void)
{
	struct Window *win;
	SysBase = *(struct ExecBase **)4;
	DOSBase = (struct DosLibrary *)OpenLibrary((CONST_STRPTR)"dos.library", 37);
	if (!DOSBase)
		return 20;
	PutStr((CONST_STRPTR)"Hello from OpenNDK\n");
	IntuitionBase = (struct IntuitionBase *)OpenLibrary((CONST_STRPTR)"intuition.library", 39);
	GfxBase = (struct GfxBase *)OpenLibrary((CONST_STRPTR)"graphics.library", 39);
	if (IntuitionBase && GfxBase) {
		win = OpenWindowTags(NULL, WA_Title, (ULONG)"OpenNDK", WA_Width, 320, WA_Height, 100,
				     WA_Flags, WFLG_CLOSEGADGET | WFLG_DRAGBAR | WFLG_ACTIVATE,
				     WA_IDCMP, IDCMP_CLOSEWINDOW, TAG_DONE);
		if (win) {
			SetAPen(win->RPort, 1);
			Move(win->RPort, 20, 40);
			Text(win->RPort, (CONST_STRPTR)"Hello", 5);
			WaitPort(win->UserPort);
			CloseWindow(win);
		}
	}
	if (GfxBase)
		CloseLibrary((struct Library *)GfxBase);
	if (IntuitionBase)
		CloseLibrary((struct Library *)IntuitionBase);
	CloseLibrary((struct Library *)DOSBase);
	return 0;
}
