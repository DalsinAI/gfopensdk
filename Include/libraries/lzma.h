/* lzma.library (GFOpenLZMA): the modes and the answers. docs/lzma.library.md
 * is the contract. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef LIBRARIES_LZMA_H
#define LIBRARIES_LZMA_H

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#define LZMANAME "lzma.library"
#define LZMA_VERSION 1

/* LzmaDecode's modes */
#define LZMODE_LZMA     1   /* raw LZMA (7z's 030101): props lc + 9 (lp + 5 pb); outLength bytes exactly */
#define LZMODE_LZMA2    2   /* raw LZMA2 (7z's 21, xz's): its chunks to their end, at most outLength */
#define LZMODE_LZMA_EOS 3   /* raw LZMA of unknown size: its end mark closes it, outLength one byte more */

/* the answers: LZERR_NONE, or why not */
#define LZERR_NONE        0
#define LZERR_DATA        1   /* the data is damaged */
#define LZERR_SHORT       2   /* the input ended first */
#define LZERR_ROOM        3   /* more output than outLength */
#define LZERR_PARAM       4   /* a mode or props the call does not take */
#define LZERR_NOMEM       5   /* no memory for the decoder's probabilities (at most 28 KB, more for lc + lp over 4) */
#define LZERR_FORMAT      6   /* not a .lzma or .xz file */
#define LZERR_CHECK       7   /* an .xz block's CRC-32 or CRC-64 is wrong */
#define LZERR_UNSUPPORTED 8   /* an .xz filter (BCJ, delta) or check (SHA-256) this version does not take */
#define LZERR_SIZE        9   /* the output would be over 1 GB */
#define LZERR_NOLIB       20  /* the link stub: lzma.library 1 could not be opened */

/* done[0]: the bytes written; done[1]: the bytes read */
#define LZDONE_OUT 0
#define LZDONE_IN  1
#define LZSIZE_UNKNOWN 0xFFFFFFFFUL  /* LzmaAloneInfo: the file does not say */

#endif
