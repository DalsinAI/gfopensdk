/* bzip2.library's proto header. MIT, Copyright (c) 2026 AmiCradle Team.
 * Programs may link the stub instead (<bzlib.h>, -lbz2): it opens the
 * library at the first call and closes it at the end. */
#ifndef PROTO_BZIP2_H
#define PROTO_BZIP2_H

#include <exec/types.h>
#include <libraries/bzip2.h>

#ifndef __NOLIBBASE__
extern struct Library *BZip2Base;
#endif
#if defined(__GNUC__) && !defined(BZIP2_NO_INLINE)
#include <inline/bzip2.h>
#else
#include <clib/bzip2_protos.h>
#endif

#endif
