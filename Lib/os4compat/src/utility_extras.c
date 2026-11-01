/* Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * ASPrintf: a formatted string in memory the caller frees with FreeVec().
 */
#include "os4c_internal.h"
#include <proto/exec.h>

STRPTR os4c_VASPrintf(CONST_STRPTR format, va_list args)
{
	va_list again;
	LONG len;
	STRPTR s;

	va_copy(again, args);
	len = os4c_VSNPrintf(NULL, 0, format, args);
	s = AllocVec(len + 1, MEMF_PUBLIC);
	if (s)
		os4c_VSNPrintf(s, len + 1, format, again);
	va_end(again);
	return s;
}

STRPTR os4c_ASPrintf(CONST_STRPTR format, ...)
{
	va_list ap;
	STRPTR s;
	va_start(ap, format);
	s = os4c_VASPrintf(format, ap);
	va_end(ap);
	return s;
}
