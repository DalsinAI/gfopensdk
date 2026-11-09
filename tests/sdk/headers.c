/* Copyright (c) 2026 AmiCradle Team. MIT licence. */
/* Every public header in the SDK, together, as C and as C++. The cloud check
 * uses m68k-linux-gnu-gcc, so it says what m68k-amigaos-gcc says itself. */
#ifndef __amigaos__
#define __amigaos__ 1
#endif
#include <exec/types.h>
#include <dos/dos.h>
#include <proto/gfopenrtg.h>
#include <proto/gfopentls.h>
#include <proto/gfopencrypto.h>
#include <proto/gfopengpu.h>
#include <gfopengpu/stream3d.h>
#include <gfopengpu/build3d.h>
#include <gfopengpu/driver.h>
#include <gfopengpu/virgl.h>
#include <gfopenrtg/modes.h>
#include <accontrol/accontrol.h>
#include <openprint/oap_device.h>
#include <proto/gfopenfont.h>
#include <proto/gfopenlayout.h>
#include <proto/javascript.h>
#include <proto/json.h>
#include <proto/unicode.h>
#include <proto/weblayout.h>
#include <proto/webbrowser.h>
#include <proto/gfopenmedia.h>
#include <proto/gfopenmulticore.h>
#include <proto/gfopenntlm.h>
#include <proto/pixman.h>
#include <elf/openelf_public.h>
#include <devices/gfopenservice.h>
#include <proto/mitchy.h>
#include <proto/akikoplus.h>
#include <proto/physfs.h>
#include <datatypes/gfopenimage.h>
#include <datatypes/streamclass.h>
#include <proto/gfxdispatch.h>
#include <graphics/gfopenlayers.h>
#include <exec/gfopenexec_atomic.h>
int sdk_headers(void)
{
    return sizeof(struct Hook) == 20 && sizeof(struct OFGPUTarget) == 40 && sizeof(struct OFGlyphRun) == 32
        && OGPU_QUERY_FLAG(OGPU_OP_PATH_FILL, OGPU_PATH_ALIASED_BIT) == 0x010E0025UL
        && OPENLAYOUTLIB_DESKTOP_VERSION == 11 ? 0 : 1;
}
