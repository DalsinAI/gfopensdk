#ifndef CLIB_MACROS_H
#define CLIB_MACROS_H
/*
 * OpenNDK: the small arithmetic macros programs take from <clib/macros.h>.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 * Each argument may be evaluated more than once, so don't pass one with
 * a side effect (MAX(i++, j)). A definition a program made first is kept.
 */

/* the larger of two values */
#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

/* the smaller of two values */
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

/* a value without its sign */
#ifndef ABS
#define ABS(x) (((x) < 0) ? -(x) : (x))
#endif

#endif /* CLIB_MACROS_H */
