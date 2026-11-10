/* The Open SDK's AROS compatibility: AROS's program sets. ADD2INIT and
 * ADD2EXIT are libnix's own (<stabs.h>: a function run before main and
 * after it, by priority), which work the same way. ADD2LIBS asks for a
 * library: libnix already opens each library a program uses, so it adds
 * nothing. AROS programs often hand ADD2INIT a static function; see
 * below. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef AROS_SYMBOLSETS_H
#define AROS_SYMBOLSETS_H
#include <stabs.h>
/* Each ADD2INIT/ADD2EXIT gets a small global function, named after the
 * program's function and the line, that calls it; that function goes on
 * libnix's list with libnix's own macros (both the entry and its priority,
 * whichever form this <stabs.h> uses). A static function that nothing else
 * calls is then neither dropped nor renamed by the compiler. */
#define AROSCOMPAT_CAT2_(a, b) a##b
#define AROSCOMPAT_CAT_(a, b) AROSCOMPAT_CAT2_(a, b)
#ifdef ADD2LIST2
#define AROSCOMPAT_LIST_(name, list, pri) ADD2LIST(name, list, 22); ADD2LIST2(pri + 128, list, 22)
#else
#define AROSCOMPAT_LIST_(name, list, pri) ADD2LIST(name, list, 22); \
    asm(".stabs \"_" #list "\",20,0,0," #pri "+128")
#endif
#define AROSCOMPAT_SET2_(name, fn, list, pri) \
    void name(void) __attribute__((used)); \
    void name(void) { (void)fn(); } \
    AROSCOMPAT_LIST_(name, list, pri)
#define AROSCOMPAT_SET_(fn, set, list, pri) \
    AROSCOMPAT_SET2_(AROSCOMPAT_CAT_(aroscompat_##set##_##fn##_, __LINE__), fn, list, pri)
#undef ADD2INIT
#undef ADD2EXIT
#define ADD2INIT(a, pri) AROSCOMPAT_SET_(a, init, __INIT_LIST__, pri)
#define ADD2EXIT(a, pri) AROSCOMPAT_SET_(a, exit, __EXIT_LIST__, pri)
#define ADD2LIBS(name, version, btype, base)
#define ADD2OPENLIB(name, version, base)
#define SETRELLIBOFFSET(base, type, field)
#endif
