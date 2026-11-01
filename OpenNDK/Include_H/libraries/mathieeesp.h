#ifndef LIBRARIES_MATHIEEESP_H
#define LIBRARIES_MATHIEEESP_H
/*
 * OpenNDK: constants and C names for the IEEE single precision libraries.
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
#define fabs	IEEESPAbs
#define floor	IEEESPFloor
#define ceil	IEEESPCeil
#define tan	IEEESPTan
#define atan	IEEESPAtan
#define cos	IEEESPCos
#define acos	IEEESPAcos
#define sin	IEEESPSin
#define asin	IEEESPAsin
#define exp	IEEESPExp
#define pow(a, b)	IEEESPPow((b), (a))
#define log	IEEESPLog
#define log10	IEEESPLog10
#define sqrt	IEEESPSqrt
#define sinh	IEEESPSinh
#define cosh	IEEESPCosh
#define tanh	IEEESPTanh

#endif /* LIBRARIES_MATHIEEESP_H */
