/* bzip2.library (GFOpenBZip2): its name, version and answers. The answers
 * are libbzip2's own (<bzlib.h>); docs/bzip2.library.md is the contract.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef LIBRARIES_BZIP2_H
#define LIBRARIES_BZIP2_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#define BZIP2NAME "bzip2.library"
#define BZIP2_VERSION 1

/* The bytes of stack the compressing calls want. With less free, the
 * library runs them on a stack of its own of this size. */
#define BZIP2_COMPRESS_STACK 32768

/* libbzip2's answers, as in <bzlib.h> */
#ifndef BZ_OK
#define BZ_RUN               0
#define BZ_FLUSH             1
#define BZ_FINISH            2
#define BZ_OK                0
#define BZ_RUN_OK            1
#define BZ_FLUSH_OK          2
#define BZ_FINISH_OK         3
#define BZ_STREAM_END        4
#define BZ_SEQUENCE_ERROR    (-1)
#define BZ_PARAM_ERROR       (-2)
#define BZ_MEM_ERROR         (-3)
#define BZ_DATA_ERROR        (-4)
#define BZ_DATA_ERROR_MAGIC  (-5)
#define BZ_IO_ERROR          (-6)
#define BZ_UNEXPECTED_EOF    (-7)
#define BZ_OUTBUFF_FULL      (-8)
#define BZ_CONFIG_ERROR      (-9)
#endif

#endif
