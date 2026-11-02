#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
# Checks that the 68k stoves on this machine build with OpenNDK (after
# amicradle's scripts/stove_openndk.py use): for each stove, which folder
# its m68k-amigaos-gcc reads the NDK from, which libamiga.a it links, and
# whether a small program using exec, dos, intuition and amiga.lib compiles
# and links with -Wall -Werror. Exits 1 if a stove is not on OpenNDK or
# the program fails.
#   STOVES="os32 os32-gcc16" tests/stove/test_openndk_stoves.sh
set -u
ROOT=${STOVES_ROOT:-"$HOME/AmigaChrome/stoves"}
bad=0
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
cat > "$tmp/smoke.c" <<'C'
#include <exec/types.h>
#include <exec/memory.h>
#include <dos/dos.h>
#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#include <clib/alib_protos.h>

struct IntuitionBase *IntuitionBase;

int main(void)
{
    struct List l;
    APTR mem;
    NewList(&l);
    mem = AllocVec(64, MEMF_CLEAR);
    if (mem) FreeVec(mem);
    IntuitionBase = (struct IntuitionBase *)OpenLibrary("intuition.library", 39);
    if (IntuitionBase) {
        struct Window *w = OpenWindowTags(NULL, WA_Width, 200, WA_Height, 50, TAG_END);
        if (w) CloseWindow(w);
        CloseLibrary((struct Library *)IntuitionBase);
    }
    Printf("OpenNDK smoke %ld\n", (LONG)IsListEmpty(&l));
    return RETURN_OK;
}
C
for s in ${STOVES:-os32 os32-gcc16}; do
    gcc="$ROOT/$s/prefix/bin/m68k-amigaos-gcc"
    if [ ! -x "$gcc" ]; then echo "$s: no m68k-amigaos-gcc, skipped"; continue; fi
    inc=$("$gcc" -xc -E -v - </dev/null 2>&1 | sed -n '/search starts here:/,/End of search/p' | sed -n 's/^ //p' |
        while read -r d; do [ -f "$d/exec/types.h" ] && { echo "$d"; break; }; done)
    real=$(readlink -f "$inc" 2>/dev/null)
    case "$real" in
        */OpenNDK/Include_H) echo "$s: headers OpenNDK ($inc -> $real)" ;;
        *) echo "$s: headers NOT OpenNDK ($inc -> $real)"; bad=1 ;;
    esac
    lib=$("$gcc" -print-file-name=libamiga.a)
    echo "$s: libamiga.a $lib -> $(readlink -f "$lib")"
    [ -e "$inc.vendor" ] && echo "$s: vendor headers kept at $inc.vendor"
    if "$gcc" -noixemul -O2 -Wall -Werror -Wno-pointer-sign "$tmp/smoke.c" -o "$tmp/smoke-$s" -lamiga 2> "$tmp/err"; then
        echo "$s: smoke built and linked ($(wc -c < "$tmp/smoke-$s") bytes)"
    else
        echo "$s: smoke FAILED"; cat "$tmp/err"; bad=1
    fi
done
exit $bad
