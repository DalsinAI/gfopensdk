/* aroscompat_kprintf: AROS's bug() and kprintf(), C's printf formats, to
 * the serial debug output (exec's RawPutChar, LVO -516). At most 512
 * bytes a call. MIT, Copyright (c) 2026 AmiCradle Team. */
#include <exec/types.h>
#include <proto/exec.h>
#include <stdarg.h>
#include <stdio.h>

static void raw_putc(UBYTE c)
{
	register struct ExecBase *a6 __asm("a6") = SysBase;
	register UBYTE d0 __asm("d0") = c;
	__asm volatile ("jsr -516(a6)" : "+r"(d0) : "r"(a6) : "d1", "a0", "a1", "cc", "memory");
}

int aroscompat_kprintf(const char *fmt, ...)
{
	char buf[512];
	va_list ap;
	int n, i;
	va_start(ap, fmt);
	n = vsnprintf(buf, sizeof buf, fmt, ap);
	va_end(ap);
	if (n < 0) return n;
	for (i = 0; buf[i]; i++) raw_putc((UBYTE)buf[i]);
	return n;
}
