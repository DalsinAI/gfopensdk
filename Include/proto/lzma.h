/* lzma.library's proto header. MIT, Copyright (c) 2026 AmiCradle Team.
 * Programs may link the stub instead (<gfopenlzma.h>, -lgflzma): it opens
 * the library at the first call and closes it at the end. */
#ifndef PROTO_LZMA_H
#define PROTO_LZMA_H

#include <exec/types.h>
#include <libraries/lzma.h>

#ifndef __NOLIBBASE__
extern struct Library *LzmaBase;
#endif
#if defined(__GNUC__) && !defined(LZMA_NO_INLINE)
#include <inline/lzma.h>
#else
#include <clib/lzma_protos.h>
#endif

#endif
