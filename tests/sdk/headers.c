/* Copyright (c) 2026 AmigaChrome Team. MIT licence. */
#include <proto/openrtg.h>
#include <proto/opentls.h>
#include <proto/opencrypto.h>
#include <proto/opengpu.h>
#include <opengpu/stream3d.h>
#include <openrtg/modes.h>
#include <accontrol/accontrol.h>
#include <openprint/oap_device.h>
#include <proto/openfont.h>
int sdk_headers(void)
{
    return sizeof(struct Hook) == 20 && sizeof(struct OFGPUTarget) == 40 && sizeof(struct OFGlyphRun) == 32
        && OGPU_QUERY_FLAG(OGPU_OP_PATH_FILL, OGPU_PATH_ALIASED_BIT) == 0x010E0025UL ? 0 : 1;
}
