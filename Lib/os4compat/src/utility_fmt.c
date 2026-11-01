/* Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Strlcpy, Strlcat and SNPrintf as OS 4's utility.library has them.
 * Plain C with no OS calls, so tests/host runs it on the build machine.
 *
 * Formats follow C: %d reads an int (32 bits with GCC for m68k), %ld a long,
 * %lld 64 bits. OS 4 code written for RawDoFmt's 16-bit %d still works, since
 * its arguments arrive as ints anyway. %b prints a BSTR, as RawDoFmt does.
 * No floating point: %f, %e and %g print '?'.
 */
#include <os4compat/os4compat.h>

ULONG os4c_Strlcpy(STRPTR dst, CONST_STRPTR src, ULONG size)
{
	ULONG n = 0;
	while (src[n]) {
		if (size && n + 1 < size)
			dst[n] = src[n];
		n++;
	}
	if (size)
		dst[n < size ? n : size - 1] = 0;
	return n;
}

ULONG os4c_Strlcat(STRPTR dst, CONST_STRPTR src, ULONG size)
{
	ULONG d = 0;
	while (d < size && dst[d])
		d++;
	if (d == size)
		return size + os4c_Strlcpy(dst, src, 0);
	return d + os4c_Strlcpy(dst + d, src, size - d);
}

struct out { STRPTR buf; ULONG size, len; };

static void put(struct out *o, char c)
{
	if (o->len + 1 < o->size)
		o->buf[o->len] = c;
	o->len++;
}

static void pad(struct out *o, char c, LONG n)
{
	while (n-- > 0)
		put(o, c);
}

LONG os4c_VSNPrintf(STRPTR buffer, ULONG size, CONST_STRPTR format, va_list args)
{
	struct out o = { buffer, size, 0 };
	CONST_STRPTR f = format;

	while (*f) {
		char digits[24], sign = 0, conv;
		int left = 0, zero = 0, plus = 0, space = 0, alt = 0, lng = 0, n = 0;
		LONG width = 0, prec = -1, len;
		const char *s;
		unsigned long long u;

		if (*f != '%') {
			put(&o, *f++);
			continue;
		}
		f++;
		for (;; f++) {
			if (*f == '-') left = 1;
			else if (*f == '0') zero = 1;
			else if (*f == '+') plus = 1;
			else if (*f == ' ') space = 1;
			else if (*f == '#') alt = 1;
			else break;
		}
		if (*f == '*') {
			width = va_arg(args, int);
			if (width < 0) { left = 1; width = -width; }
			f++;
		} else
			while (*f >= '0' && *f <= '9') width = width * 10 + (*f++ - '0');
		if (*f == '.') {
			f++;
			prec = 0;
			if (*f == '*') { prec = va_arg(args, int); f++; }
			else while (*f >= '0' && *f <= '9') prec = prec * 10 + (*f++ - '0');
		}
		while (*f == 'l' || *f == 'h' || *f == 'z' || *f == 't' || *f == 'j' || *f == 'L') {
			if (*f == 'l') lng++;
			else if (*f == 'j') lng = 2;   /* intmax_t is long long */
			f++;
		}
		conv = *f ? *f++ : 0;

		switch (conv) {
		case 'd': case 'i': {
			long long v = lng >= 2 ? va_arg(args, long long) : lng ? (long long)va_arg(args, long) : va_arg(args, int);
			if (v < 0) { sign = '-'; u = (unsigned long long)(-(v + 1)) + 1; }
			else { sign = plus ? '+' : space ? ' ' : 0; u = v; }
			goto number10;
		}
		case 'u':
			u = lng >= 2 ? va_arg(args, unsigned long long) : lng ? va_arg(args, unsigned long) : va_arg(args, unsigned int);
		number10:
			do digits[n++] = '0' + u % 10; while (u /= 10);
			goto number;
		case 'x': case 'X': case 'p': {
			const char *hex = conv == 'X' ? "0123456789ABCDEF" : "0123456789abcdef";
			if (conv == 'p') { u = (unsigned long)va_arg(args, void *); alt = 1; }
			else u = lng >= 2 ? va_arg(args, unsigned long long) : lng ? va_arg(args, unsigned long) : va_arg(args, unsigned int);
			if (conv != 'p' && u == 0)
				alt = 0;   /* C prints no 0x before a zero */
			do digits[n++] = hex[u & 15]; while (u >>= 4);
			goto number;
		}
		case 'o':
			u = lng >= 2 ? va_arg(args, unsigned long long) : lng ? va_arg(args, unsigned long) : va_arg(args, unsigned int);
			do digits[n++] = '0' + (u & 7); while (u >>= 3);
			if (alt && digits[n - 1] != '0')
				digits[n++] = '0';
		number: {
			LONG zeros = prec > n ? prec - n : 0;
			LONG pre = (sign ? 1 : 0) + (alt && (conv == 'x' || conv == 'X' || conv == 'p') ? 2 : 0);
			if (prec == 0 && n == 1 && digits[0] == '0')
				n = 0;
			len = pre + zeros + n;
			if (zero && !left && prec < 0 && width > len) { zeros += width - len; len = width; }
			if (!left) pad(&o, ' ', width - len);
			if (sign) put(&o, sign);
			if (pre >= 2) { put(&o, '0'); put(&o, conv == 'X' ? 'X' : 'x'); }
			pad(&o, '0', zeros);
			while (n) put(&o, digits[--n]);
			if (left) pad(&o, ' ', width - len);
			break;
		}
		case 'c':
			if (!left) pad(&o, ' ', width - 1);
			put(&o, (char)va_arg(args, int));
			if (left) pad(&o, ' ', width - 1);
			break;
		case 's': case 'b': {
			LONG i;
			if (conv == 'b') {
				/* a BSTR: a BPTR to a length byte and the characters */
				const UBYTE *b = (const UBYTE *)BADDR(va_arg(args, BPTR));
				s = b ? (const char *)b + 1 : "";
				len = b ? b[0] : 0;
			} else {
				s = va_arg(args, const char *);
				if (!s) s = "(null)";
				for (len = 0; s[len] && (prec < 0 || len < prec); len++)
					;
			}
			if (prec >= 0 && len > prec) len = prec;
			if (!left) pad(&o, ' ', width - len);
			for (i = 0; i < len; i++) put(&o, s[i]);
			if (left) pad(&o, ' ', width - len);
			break;
		}
		case 'f': case 'e': case 'g': case 'F': case 'E': case 'G':
			(void)va_arg(args, double);
			put(&o, '?');
			break;
		case '%':
			put(&o, '%');
			break;
		case 0:
			break;
		default:
			put(&o, '%');
			put(&o, conv);
			break;
		}
	}
	if (size)
		buffer[o.len < size ? o.len : size - 1] = 0;
	return (LONG)o.len;
}

LONG os4c_SNPrintf(STRPTR buffer, ULONG size, CONST_STRPTR format, ...)
{
	va_list ap;
	LONG r;
	va_start(ap, format);
	r = os4c_VSNPrintf(buffer, size, format, ap);
	va_end(ap);
	return r;
}
