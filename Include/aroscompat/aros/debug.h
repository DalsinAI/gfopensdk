/* The Open SDK's AROS compatibility: AROS's debug macros. With DEBUG 0
 * (the default) D(x) and the Enter/Return macros compile to nothing but
 * their returns; with DEBUG 1, bug() prints to the serial debug output
 * with C's printf formats (aroscompat_kprintf, Lib/aroscompat).
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef DEBUG
#define DEBUG 0
#endif
#ifndef AROS_DEBUG_H
#define AROS_DEBUG_H
#include <exec/types.h>

int aroscompat_kprintf(const char *fmt, ...);
#define kprintf aroscompat_kprintf
#define bug aroscompat_kprintf
#define rbug(main, sub, lvl, fmt, ...) aroscompat_kprintf(fmt, ##__VA_ARGS__)
#endif

/* these follow DEBUG each time the header is included, as AROS's do */
#undef D
#undef DB2
#undef ASSERT
#undef ASSERT_VALID_PTR
#undef ASSERT_VALID_PTR_OR_NULL
#undef EnterFunc
#undef ReturnVoid
#undef ReturnPtr
#undef ReturnStr
#undef ReturnInt
#undef ReturnXInt
#undef ReturnFloat
#undef ReturnSpecial
#undef ReturnBool
#if DEBUG
#define D(x) x
#define DB2(x) x
#define ASSERT(x) do { if (!(x)) aroscompat_kprintf("%s:%d: assertion failed: %s\n", __FILE__, __LINE__, #x); } while (0)
#define EnterFunc(x) x
#else
#define D(x)
#define DB2(x)
#define ASSERT(x) ((void)0)
#define EnterFunc(x)
#endif
#define ASSERT_VALID_PTR(x) ASSERT((x) != NULL)
#define ASSERT_VALID_PTR_OR_NULL(x) ((void)0)
#define ReturnVoid(name) return
#define ReturnPtr(name, type, val) return (val)
#define ReturnStr(name, type, val) return (val)
#define ReturnInt(name, type, val) return (val)
#define ReturnXInt(name, type, val) return (val)
#define ReturnFloat(name, type, val) return (val)
#define ReturnSpecial(name, type, val, fmt) return (val)
#define ReturnBool(name, val) return (val)
