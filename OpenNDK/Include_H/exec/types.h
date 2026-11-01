#ifndef EXEC_TYPES_H
#define EXEC_TYPES_H
/*
 * OpenNDK: the basic data types every other header builds on.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 *
 * Part of OpenNDK, an open set of headers for 68k AmigaOS 3.x software.
 * Written clean-room from the published interface: names, sizes and
 * values only (see OpenNDK/CLEAN-ROOM.md).
 *
 * The 68k ABI: char is 8 bits, short 16, int and long 32, and pointers
 * 32. Each type below has the width its name promises on that ABI.
 */

/* The header set's release: 47 is AmigaOS 3.2. */
#define INCLUDE_VERSION	47

/* The lowest library version the OS still ships (Kickstart 1.2). */
#define LIBRARY_MINIMUM	33

/* Storage-class words some older sources use. */
#define GLOBAL	extern
#define IMPORT	extern
#define STATIC	static
#define REGISTER register

#ifndef VOID
#define VOID	void
#endif

#ifndef CONST
#define CONST	const
#endif

/* C99 and later (or AMIGA_STDC_C99): the C library's fixed-width types
 * come with these, as with 3.2. Left out when the compiler finds no
 * <stdint.h> (a bare cross compiler with -nostdinc). */
#if defined(__STDC__) && ((defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(AMIGA_STDC_C99))
#ifdef __has_include
#if __has_include(<stdint.h>)
#include <stdint.h>
#endif
#else
#include <stdint.h>
#endif
#endif

/* Pointers */
typedef void		*APTR;		/* any pointer */
typedef const void	*CONST_APTR;	/* any pointer to data not written */
/* Strings: plain char in C++, as the 3.2 interface has them there, so a
 * string literal is a CONST_STRPTR without a cast; unsigned char in C */
#ifdef __cplusplus
typedef char		*STRPTR;	/* a NUL-terminated string */
typedef const char	*CONST_STRPTR;
#else
typedef unsigned char	*STRPTR;	/* a NUL-terminated string */
typedef const unsigned char *CONST_STRPTR;
#endif

/* 32 bits */
typedef int		LONG;
typedef unsigned int	ULONG;
typedef unsigned int	LONGBITS;	/* 32 flag bits */

/* 16 bits */
typedef short		WORD;
typedef unsigned short	UWORD;
typedef unsigned short	WORDBITS;

/* 8 bits */
typedef signed char	BYTE;
typedef unsigned char	UBYTE;
typedef unsigned char	BYTEBITS;

/* A 16-bit relative pointer */
typedef unsigned short	RPTR;

/* Older names still met in sources */
typedef short		SHORT;
typedef unsigned short	USHORT;
typedef short		COUNT;
typedef unsigned short	UCOUNT;
typedef ULONG		CPTR;

/* Floating point */
typedef float		FLOAT;
typedef double		DOUBLE;

/* Truth values, 16 bits wide as the OS stores them */
typedef short		BOOL;
#ifndef TRUE
#define TRUE		1
#endif
#ifndef FALSE
#define FALSE		0
#endif

/* Text */
#ifdef __cplusplus
typedef char		TEXT;
#else
typedef unsigned char	TEXT;
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL		0
#else
#define NULL		((void *)0)
#endif
#endif

#define BYTEMASK	0xFF

/* APTR and CONST_APTR are typedefs here (other headers test these) */
#define APTR_TYPEDEF
#define CONST_APTR_TYPEDEF

/* __STDARGS__, __SAVE_DS__, __REG__ and the other compiler words */
#include <clib/compiler-specific.h>

#endif /* EXEC_TYPES_H */
