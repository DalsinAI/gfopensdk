/* Copyright (c) 2026 AmiCradle Team. MIT licence. */
#include <proto/gfopenrtg.h>
#include <proto/gfopentls.h>
#include <proto/gfopencrypto.h>
#include <proto/gfopengpu.h>
#include <gfopengpu/stream3d.h>
#include <gfopenrtg/modes.h>
#include <accontrol/accontrol.h>
#include <openprint/oap_device.h>
#include <proto/gfopenfont.h>
int sdk_headers(void)
{
    return sizeof(struct Hook) == 20 && sizeof(struct OFGPUTarget) == 40 && sizeof(struct OFGlyphRun) == 32
        && OGPU_QUERY_FLAG(OGPU_OP_PATH_FILL, OGPU_PATH_ALIASED_BIT) == 0x010E0025UL ? 0 : 1;
}
