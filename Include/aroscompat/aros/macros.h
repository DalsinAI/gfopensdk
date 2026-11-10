/* The Open SDK's AROS compatibility: AROS's byte-order and BSTR macros on
 * a big-endian 68k. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef AROS_MACROS_H
#define AROS_MACROS_H
#include <exec/types.h>
#include <dos/dos.h>
#include <aros/cpu.h>

#define AROS_SWAP_BYTES_WORD(x) ((UWORD)((((UWORD)(x) & 0xFF) << 8) | (((UWORD)(x) >> 8) & 0xFF)))
#define AROS_SWAP_BYTES_LONG(x) ((ULONG)(((ULONG)(x) << 24) | (((ULONG)(x) & 0xFF00) << 8) | \
                                         (((ULONG)(x) >> 8) & 0xFF00) | ((ULONG)(x) >> 24)))
#define AROS_SWAP_BYTES_QUAD(x) ((UQUAD)AROS_SWAP_BYTES_LONG((UQUAD)(x) >> 32) | \
                                 ((UQUAD)AROS_SWAP_BYTES_LONG((UQUAD)(x)) << 32))
/* big-endian: BE is the CPU's own order */
#define AROS_BE2WORD(x) ((UWORD)(x))
#define AROS_WORD2BE(x) ((UWORD)(x))
#define AROS_BE2LONG(x) ((ULONG)(x))
#define AROS_LONG2BE(x) ((ULONG)(x))
#define AROS_BE2QUAD(x) ((UQUAD)(x))
#define AROS_QUAD2BE(x) ((UQUAD)(x))
#define AROS_LE2WORD(x) AROS_SWAP_BYTES_WORD(x)
#define AROS_WORD2LE(x) AROS_SWAP_BYTES_WORD(x)
#define AROS_LE2LONG(x) AROS_SWAP_BYTES_LONG(x)
#define AROS_LONG2LE(x) AROS_SWAP_BYTES_LONG(x)
#define AROS_LE2QUAD(x) AROS_SWAP_BYTES_QUAD(x)
#define AROS_QUAD2LE(x) AROS_SWAP_BYTES_QUAD(x)
/* BCPL strings: a length byte, then the characters */
#define AROS_BSTR_ADDR(s) ((STRPTR)BADDR(s) + 1)
#define AROS_BSTR_strlen(s) (*(UBYTE *)BADDR(s))
#define AROS_BSTR_setstrlen(s, l) (*(UBYTE *)BADDR(s) = (l))
#define AROS_BSTR_getchar(s, i) (AROS_BSTR_ADDR(s)[i])
#define AROS_BSTR_putchar(s, i, c) (AROS_BSTR_ADDR(s)[i] = (c))
#define AROS_BSTR_MEMSIZE4LEN(l) ((l) + 1)
#define AROS_BSTR_TYPE BSTR
#define AROS_ASMSYMNAME(s) "_" #s
#endif
