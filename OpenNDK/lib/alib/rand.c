/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* FastRand and RangeRand: a shift register with feedback, as documented
 * for amiga.lib: double the seed and, when a bit falls off the top, mix
 * in the feedback constant 0x1D872B41. */
#include "alib.h"

#define FEEDBACK 0x1D872B41UL

ULONG FastRand(ULONG seed)
{
	ULONG next = seed << 1;
	if (seed & 0x80000000UL)
		next ^= FEEDBACK;
	return next;
}

static ULONG range_seed = 1;

UWORD RangeRand(ULONG maxValue)
{
	ULONG v;
	range_seed = FastRand(range_seed);
	v = (range_seed >> 16) & 0xFFFF;
	if (maxValue == 0 || maxValue > 0xFFFF)
		maxValue = 0x10000;
	return (UWORD)((v * maxValue) >> 16);
}
