#include <win32compat/bitmap.h>
/* Copyright (c) 2026 AmigaChrome Team. MIT licence. */
#include <proto/openrtg.h>
#include <proto/opentls.h>
#include <proto/opencrypto.h>
#include <openrtg/modes.h>
#include <accontrol/accontrol.h>
#include <openprint/oap_device.h>
int sdk_headers(void) { return sizeof(struct Hook) == 20 ? 0 : 1; }
