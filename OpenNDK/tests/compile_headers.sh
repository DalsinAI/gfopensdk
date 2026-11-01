#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
# Every OpenNDK C header must compile on its own, in C (gnu99 and gnu17)
# and, when a 68k g++ is present, in C++, with warnings as errors. Uses an
# m68k cross GCC: m68k-linux-gnu-gcc (Ubuntu's gcc-m68k-linux-gnu) or $M68K_CC.
#   tests/compile_headers.sh [header ...]    (paths relative to Include_H)
set -eu
NDK=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
CC=${M68K_CC:-m68k-linux-gnu-gcc}
CXX=${M68K_CXX:-m68k-linux-gnu-g++}
command -v "$CXX" >/dev/null 2>&1 || CXX=
INC="$NDK/Include_H"
T=$(mktemp -d)
trap 'rm -rf "$T"' EXIT
if [ $# -eq 0 ]; then
    set -- $(cd "$INC" && find . -name '*.h' | sed 's|^\./||' | sort)
fi
# check/shim gives <stdint.h> (exec/types.h takes it in C99) to a compiler
# without a C library
FLAGS="-nostdinc -isystem $($CC -print-file-name=include) -idirafter $NDK/check/shim -I$INC -fsyntax-only
  -Wall -Wextra -Werror -Wno-unused-function -fomit-frame-pointer -m68040"
bad=0 n=0
for h in "$@"; do
    n=$((n + 1))
    printf '#include <%s>\n' "$h" > "$T/t.c"
    case $h in pragmas/*) PR=-Wno-unknown-pragmas ;; *) PR= ;; esac
    for std in gnu99 gnu17; do
        # shellcheck disable=SC2086
        if ! "$CC" $FLAGS $PR -std=$std "$T/t.c" 2> "$T/err"; then
            echo "FAIL $h ($std)"; sed 's/^/    /' "$T/err" | head -20; bad=$((bad + 1)); break
        fi
    done
    if [ -n "$CXX" ]; then
        cp "$T/t.c" "$T/t.cpp"
        # shellcheck disable=SC2086
        "$CXX" $FLAGS $PR -std=gnu++17 "$T/t.cpp" 2> "$T/err" || {
            echo "FAIL $h (C++)"; sed 's/^/    /' "$T/err" | head -20; bad=$((bad + 1)); }
    fi
done
echo "$n headers, $bad failed"
[ "$bad" -eq 0 ]
