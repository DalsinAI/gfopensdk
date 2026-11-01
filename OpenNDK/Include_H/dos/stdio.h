#ifndef DOS_STDIO_H
#define DOS_STDIO_H
/*
 * OpenNDK: shorthand for buffered I/O on the process's own streams.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#define ReadChar()		FGetC(Input())
#define WriteChar(ch)		FPutC(Output(), (ch))
#define UnReadChar(ch)		UnGetC(Input(), (ch))
#define ReadChars(buf, num)	FRead(Input(), (buf), 1, (num))
#define ReadLn(buf, len)	FGets(Input(), (buf), (len))
#define WriteStr(str)		FPuts(Output(), (str))
#define VWritef(fmt, argv)	VFWritef(Output(), (fmt), (argv))

/* SetVBuf() modes */
#define BUF_LINE	0	/* flush at each newline */
#define BUF_FULL	1	/* flush when full */
#define BUF_NONE	2	/* no buffering */

/* FGetC()'s end of file */
#define ENDSTREAMCH	-1

#endif /* DOS_STDIO_H */
