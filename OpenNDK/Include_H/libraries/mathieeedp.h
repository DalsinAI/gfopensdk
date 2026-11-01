#ifndef LIBRARIES_MATHIEEEDP_H
#define LIBRARIES_MATHIEEEDP_H
/*
 * OpenNDK: constants and C names for the IEEE double precision libraries.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifndef PI
#define PI	((DOUBLE) 3.141592653589793)
#endif
#define TWO_PI	(((DOUBLE) 2) * PI)
#define PI2	(PI / ((DOUBLE) 2))
#define PI4	(PI / ((DOUBLE) 4))
#ifndef E
#define E	((DOUBLE) 2.718281828459045)
#endif
#define LOG10	((DOUBLE) 2.302585092994046)

#define FPTEN	((DOUBLE) 10.0)
#define FPONE	((DOUBLE) 1.0)
#define FPHALF	((DOUBLE) 0.5)
#define FPZERO	((DOUBLE) 0.0)

/* Conversions written as plain C */
#define trunc(x)	((int)(x))
#define round(x)	((int)((x) + 0.5))
#define itof(i)		((DOUBLE)(i))

/* The C library's names, mapped onto the library's calls */
#define fabs	IEEEDPAbs
#define floor	IEEEDPFloor
#define ceil	IEEEDPCeil
#define tan	IEEEDPTan
#define atan	IEEEDPAtan
#define cos	IEEEDPCos
#define acos	IEEEDPAcos
#define sin	IEEEDPSin
#define asin	IEEEDPAsin
#define exp	IEEEDPExp
#define pow(a, b)	IEEEDPPow((b), (a))
#define log	IEEEDPLog
#define log10	IEEEDPLog10
#define sqrt	IEEEDPSqrt
#define sinh	IEEEDPSinh
#define cosh	IEEEDPCosh
#define tanh	IEEEDPTanh

#endif /* LIBRARIES_MATHIEEEDP_H */
