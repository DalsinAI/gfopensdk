/* GFOpenLZMA's link stub (-lgflzma): lzma.library's calls as plain C
 * functions. The stub opens the library at the first call and closes it
 * when the program ends; without it every call answers LZERR_NOLIB. The
 * answers and modes are <libraries/lzma.h>'s; docs/lzma.library.md is the
 * contract. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef GFOPENLZMA_H
#define GFOPENLZMA_H

#include <libraries/lzma.h>

#ifdef __cplusplus
extern "C" {
#endif

long lzma_decode(unsigned long mode, unsigned long props, const void *in, unsigned long in_len,
                 void *out, unsigned long out_len, unsigned long *done);
long lzma_alone_info(const void *in, unsigned long in_len, unsigned long *size);
long lzma_alone_decode(const void *in, unsigned long in_len, void *out, unsigned long out_len,
                       unsigned long *done);
long xz_info(const void *in, unsigned long in_len, unsigned long *size);
long xz_decode(const void *in, unsigned long in_len, void *out, unsigned long out_len,
               unsigned long *done);
const char *lzma_error_text(long error);

#ifdef __cplusplus
}
#endif

#endif
