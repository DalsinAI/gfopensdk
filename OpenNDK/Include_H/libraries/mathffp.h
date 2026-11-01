#ifndef LIBRARIES_MATHFFP_H
#define LIBRARIES_MATHFFP_H
/*
 * OpenNDK: constants and C names for mathffp.library's fast floating point.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef PI
#define PI	((FLOAT) 3.141592653589793)
#endif
#define TWO_PI	(((FLOAT) 2) * PI)
#define PI2	(PI / ((FLOAT) 2))
#define PI4	(PI / ((FLOAT) 4))
#ifndef E
#define E	((FLOAT) 2.718281828459045)
#endif
#define LOG10	((FLOAT) 2.302585092994046)

#define FPTEN	((FLOAT) 10.0)
#define FPONE	((FLOAT) 1.0)
#define FPHALF	((FLOAT) 0.5)
#define FPZERO	((FLOAT) 0.0)

/* Conversions written as plain C */
#define trunc(x)	((int)(x))
#define round(x)	((int)((x) + 0.5))
#define itof(i)		((FLOAT)(i))

/* The C library's names, mapped onto the library's calls */
#define fabs	SPAbs
#define floor	SPFloor
#define ceil	SPCeil
#define tan	SPTan
#define atan	SPAtan
#define cos	SPCos
#define acos	SPAcos
#define sin	SPSin
#define asin	SPAsin
#define exp	SPExp
#define pow(a, b)	SPPow((b), (a))
#define log	SPLog
#define log10	SPLog10
#define sqrt	SPSqrt
#define sinh	SPSinh
#define cosh	SPCosh
#define tanh	SPTanh

#endif /* LIBRARIES_MATHFFP_H */
