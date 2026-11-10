/*
 * libraries/z.h: what a program needs to call z.library (GFOpenZlib, or the
 * Aminet z.library): z_stream and gz_header as the 68k lays them out (56 and
 * 52 bytes, zlib.h's), and zlib's return codes, flush values and levels.
 * The calls are in proto/z.h (inline/z.h, pragmas/z_pragmas.h,
 * clib/z_protos.h), made from z_lib.sfd, which follows z.lvo.
 * A program that includes zlib.h first keeps zlib.h's own types, which are
 * the same layout.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see LICENSE at the repository root).
 */
#ifndef LIBRARIES_Z_H
#define LIBRARIES_Z_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#define ZLIBRARY_NAME "z.library"
#define ZLIBRARY_MIN_VERSION 53     /* GFOpenZlib before 53.13 had another table: check the revision too */
#define ZLIBRARY_GFOPENZLIB_MIN_REVISION 13

#if !defined(ZLIB_H) && !defined(_ZLIB_H)

typedef struct z_stream_s {
    CONST UBYTE *next_in;       /* next input byte */
    ULONG avail_in;             /* bytes at next_in */
    ULONG total_in;             /* input bytes read so far */
    UBYTE *next_out;            /* next output byte goes here */
    ULONG avail_out;            /* room at next_out */
    ULONG total_out;            /* output bytes written so far */
    CONST char *msg;            /* last error message, NULL if none */
    APTR state;                 /* the library's own */
    APTR zalloc;                /* not called by z.library: set to NULL */
    APTR zfree;
    APTR opaque;
    LONG data_type;
    ULONG adler;                /* Adler-32 or CRC-32 of the data so far */
    ULONG reserved;
} z_stream;

typedef z_stream *z_streamp;

typedef struct gz_header_s {
    LONG text;
    ULONG time;
    LONG xflags;
    LONG os;
    UBYTE *extra;
    ULONG extra_len;
    ULONG extra_max;
    UBYTE *name;
    ULONG name_max;
    UBYTE *comment;
    ULONG comm_max;
    LONG hcrc;
    LONG done;
} gz_header;

typedef gz_header *gz_headerp;

#define Z_NO_FLUSH      0
#define Z_PARTIAL_FLUSH 1
#define Z_SYNC_FLUSH    2
#define Z_FULL_FLUSH    3
#define Z_FINISH        4
#define Z_BLOCK         5
#define Z_TREES         6

#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO         (-1)
#define Z_STREAM_ERROR  (-2)
#define Z_DATA_ERROR    (-3)
#define Z_MEM_ERROR     (-4)
#define Z_BUF_ERROR     (-5)
#define Z_VERSION_ERROR (-6)

#define Z_NO_COMPRESSION      0
#define Z_BEST_SPEED          1
#define Z_BEST_COMPRESSION    9
#define Z_DEFAULT_COMPRESSION (-1)

#define Z_FILTERED         1
#define Z_HUFFMAN_ONLY     2
#define Z_RLE              3
#define Z_FIXED            4
#define Z_DEFAULT_STRATEGY 0

#define Z_BINARY   0
#define Z_TEXT     1
#define Z_UNKNOWN  2

#define Z_DEFLATED 8

#endif /* !ZLIB_H */

#endif /* LIBRARIES_Z_H */
