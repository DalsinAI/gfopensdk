/* A Shell command for AmigaOS 3.2 and AROS, from the Open SDK's template.
 * Replace "Hello" with your command's name everywhere in this drawer.
 *
 *   Hello NAME/A,TIMES/N/K,QUIET/S
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence: your own
 * command built from it is yours to licence as you like. */
#include <exec/types.h>
#include <dos/dos.h>
#include <proto/exec.h>
#include <proto/dos.h>

#ifndef __AROS__
typedef LONG SIPTR;     /* AROS has it; NDK 3.2 doesn't. ReadArgs' array is SIPTR on AROS */
#endif

static const char version[] = "$VER: Hello 1.0 (6.10.2026)";

#define TEMPLATE "NAME/A,TIMES/N/K,QUIET/S"
enum { ARG_NAME, ARG_TIMES, ARG_QUIET, ARG_COUNT };

int main(void)
{
    SIPTR args[ARG_COUNT] = { 0 };
    struct RDArgs *rd = ReadArgs((CONST_STRPTR)TEMPLATE, args, NULL);
    LONG times = 1, i;
    if (!rd) {
        PrintFault(IoErr(), (CONST_STRPTR)"Hello");
        return RETURN_FAIL;
    }
    if (args[ARG_TIMES]) times = *(LONG *)args[ARG_TIMES];
    for (i = 0; i < times; i++) {
        if (SetSignal(0, 0) & SIGBREAKF_CTRL_C) {       /* Ctrl-C stops it, as every command should */
            PrintFault(ERROR_BREAK, (CONST_STRPTR)"Hello");
            break;
        }
        if (!args[ARG_QUIET]) Printf((CONST_STRPTR)"Hello, %s!\n", (LONG)args[ARG_NAME]);
    }
    FreeArgs(rd);
    (void)version;
    return RETURN_OK;
}
