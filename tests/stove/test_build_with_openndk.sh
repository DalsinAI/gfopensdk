#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
# Builds a small program against this checkout's OpenNDK (not the stove's
# own include folder) with each 68k stove's gcc, as strictly as the open
# libraries build: -Wall -Wextra -Werror, string literals passed to calls
# that take CONST_STRPTR, printf-style formats on LONG values. It also
# compiles OpenNDK headers together with the stove's C library headers in
# both orders (struct timeval is in both) and with __USE_NEW_TIMEVAL__.
# Exits 1 if a stove fails.
#   STOVES="os32 os32-gcc16" tests/stove/test_build_with_openndk.sh
set -u
HERE=$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)
ROOT=${STOVES_ROOT:-"$HOME/AmigaChrome/stoves"}
bad=0
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
cat > "$tmp/t.c" <<'C'
#include <exec/types.h>
#include <exec/memory.h>
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <graphics/gfxbase.h>
#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <clib/alib_protos.h>

struct IntuitionBase *IntuitionBase;
struct GfxBase *GfxBase;

int main(void)
{
    struct List l;
    LONG n = 5;
    ULONG u = 7;
    APTR mem;
    BPTR fh;
    NewList(&l);
    mem = AllocVec(64, MEMF_CLEAR);
    if (mem) FreeVec(mem);
    GfxBase = (struct GfxBase *)OpenLibrary("graphics.library", 39);
    IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library", 39);
    if (IntuitionBase) {
        struct Window *w = OpenWindowTags(NULL, WA_Width, 200, WA_Height, 50, WA_Title, (ULONG)"t", TAG_END);
        if (w) CloseWindow(w);
        CloseLibrary((struct Library *)IntuitionBase);
    }
    if (GfxBase) CloseLibrary((struct Library *)GfxBase);
    fh = Open("RAM:t", MODE_NEWFILE);
    if (fh) Close(fh);
    Printf("%ld %lu %ld\n", n, u, (LONG)IsListEmpty(&l));
    return RETURN_OK;
}
C
cat > "$tmp/tv.c" <<'C'
#ifdef LIBC_FIRST
#include <stdio.h>
#include <sys/time.h>
#endif
#include <devices/timer.h>
#include <devices/inputevent.h>
#include <intuition/preferences.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/timer.h>
#ifndef LIBC_FIRST
#include <stdio.h>
#include <sys/time.h>
#endif

struct Device *TimerBase;

int main(void)
{
    TimeVal_Type a, b;
    struct TimeVal c;
    struct TimeRequest *tr = NULL;
    TimeRequest_Type *tq = NULL;
    a.tv_secs = 1; a.tv_micro = 2; b = a;
    c.tv_secs = 3; c.tv_micro = 4;
    if (TimerBase) { GetSysTime(&a); AddTime(&a, &b); }
    printf("%d %d %d\n", (int)sizeof(a), (int)(c.tv_secs + (tr != NULL)), (int)(tq != NULL));
    return 0;
}
C
for s in ${STOVES:-os32 os32-gcc16}; do
    gcc="$ROOT/$s/prefix/bin/m68k-amigaos-gcc"
    if [ ! -x "$gcc" ]; then echo "$s: no m68k-amigaos-gcc, skipped"; continue; fi
    if "$gcc" -nostdinc -isystem "$HERE/OpenNDK/Include_H" -isystem "$("$gcc" -print-file-name=include)" \
        -noixemul -m68000 -O2 -Wall -Wextra -Werror "$tmp/t.c" -o "$tmp/t-$s" -lamiga 2> "$tmp/err"; then
        echo "$s: built and linked against this OpenNDK ($(wc -c < "$tmp/t-$s") bytes)"
    else
        echo "$s: FAILED"; cat "$tmp/err"; bad=1
    fi
    for mode in "" -DLIBC_FIRST "-D__USE_NEW_TIMEVAL__ -DLIBC_FIRST" -D__USE_NEW_TIMEVAL__; do
        # shellcheck disable=SC2086
        if "$gcc" -isystem "$HERE/OpenNDK/Include_H" -noixemul -m68000 -O2 -Wall -Wextra -Werror \
            $mode -c "$tmp/tv.c" -o "$tmp/tv.o" 2> "$tmp/err"; then
            echo "$s: OpenNDK with the C library's headers${mode:+ ($mode)}: compiles"
        else
            echo "$s: OpenNDK with the C library's headers${mode:+ ($mode)}: FAILED"; cat "$tmp/err"; bad=1
        fi
    done
done
exit $bad
