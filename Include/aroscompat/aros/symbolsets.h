/* The Open SDK's AROS compatibility: AROS's program sets. ADD2INIT and
 * ADD2EXIT are libnix's own (<stabs.h>: a function run before main and
 * after it, by priority), which work the same way. ADD2LIBS asks for a
 * library: libnix already opens each library a program uses, so it adds
 * nothing. AROS programs often hand ADD2INIT a static function that
 * nothing else calls; the C reference below keeps the compiler from
 * dropping or renaming it, so the list's reference to it still links.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef AROS_SYMBOLSETS_H
#define AROS_SYMBOLSETS_H
#include <stabs.h>
#define AROSCOMPAT_KEEP_(a, set) \
    static void *const aroscompat_##set##_##a __attribute__((used)) = (void *)(a)
#undef ADD2INIT
#undef ADD2EXIT
#define ADD2INIT(a, pri) AROSCOMPAT_KEEP_(a, init); \
    ADD2LIST(a, __INIT_LIST__, 22); asm(".stabs \"___INIT_LIST__\",20,0,0," #pri "+128")
#define ADD2EXIT(a, pri) AROSCOMPAT_KEEP_(a, exit); \
    ADD2LIST(a, __EXIT_LIST__, 22); asm(".stabs \"___EXIT_LIST__\",20,0,0," #pri "+128")
#define ADD2LIBS(name, version, btype, base)
#define ADD2OPENLIB(name, version, base)
#define SETRELLIBOFFSET(base, type, field)
#endif
