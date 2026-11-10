/* aroscompat_sprintf: AROS amiga.lib's __sprintf(), exec's RawDoFmt formats
 * into a buffer. Arguments are 32 bits each (C's promotion), so use %ld, %lx
 * and %lu for numbers, as RawDoFmt wants. MIT, Copyright (c) 2026 AmiCradle Team. */
#include <exec/types.h>
#include <proto/exec.h>
#include <stdarg.h>

/* move.b d0,(a3)+ ; rts : RawDoFmt's PutChProc, A3 is the output pointer */
static const UWORD stuff_char[] = { 0x16c0, 0x4e75 };

STRPTR __sprintf(UBYTE *buf, const UBYTE *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	RawDoFmt((CONST_STRPTR)fmt, (APTR)ap, (void (*)())stuff_char, buf);
	va_end(ap);
	return (STRPTR)buf;
}
