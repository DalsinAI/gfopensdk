#ifndef CLIB_DDEBUG_PROTOS_H
#define CLIB_DDEBUG_PROTOS_H
/*
 * OpenNDK: ddebug.lib's calls (dprintf and friends).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ddebug.lib: the same calls on the parallel port */
LONG KCmpStr(CONST_STRPTR a, CONST_STRPTR b);
LONG cmpstrexec(CONST_STRPTR a, CONST_STRPTR b);
LONG DGetNum(VOID);
LONG dgetnum(VOID);
VOID dputchar(LONG ch);
VOID dputch(LONG ch);
VOID DPutCh(LONG ch);
VOID dputc(LONG ch);
VOID DPutChar(LONG ch);
VOID dputstr(CONST_STRPTR string);
VOID dputs(CONST_STRPTR string);
VOID DPutS(CONST_STRPTR string);
VOID DPutStr(CONST_STRPTR string);
LONG dgetchar(VOID);
LONG dgetch(VOID);
LONG DGetCh(VOID);
LONG dgetc(VOID);
LONG DGetChar(VOID);
LONG DMayGetCh(VOID);
LONG DMayGetChar(VOID);
VOID DPutFmt(CONST_STRPTR formatString, CONST_APTR values);
VOID dprintf(CONST_STRPTR formatString, ...);
VOID DPrintF(CONST_STRPTR formatString, ...);
VOID DDoFmt(CONST_STRPTR formatString, CONST_APTR dataStream, CONST_APTR putChProc, APTR putChData);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_DDEBUG_PROTOS_H */
