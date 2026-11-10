/* The Open SDK's AROS compatibility: AROS's program sets. ADD2INIT and
 * ADD2EXIT are libnix's own (<stabs.h>: a function run before main and
 * after it, by priority), which work the same way. ADD2LIBS asks for a
 * library: libnix already opens each library a program uses, so it adds
 * nothing. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef AROS_SYMBOLSETS_H
#define AROS_SYMBOLSETS_H
#include <stabs.h>
#define ADD2LIBS(name, version, btype, base)
#define ADD2OPENLIB(name, version, base)
#define SETRELLIBOFFSET(base, type, field)
#endif
