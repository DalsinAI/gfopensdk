#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
# Compares the C types behind exec/types.h's names (STRPTR, TEXT, LONG and
# the rest) in the vendor NDK 3.2 and in OpenNDK, with the os32 stove's
# gcc. Only the answers to "is STRPTR the same type as char *?" are read;
# no vendor text is printed or kept. Exits 1 if any name differs.
#   tests/stove/test_ndk_basic_types.sh [VENDOR_INCLUDE_DIR]
set -u
HERE=$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)
OURS="$HERE/OpenNDK/Include_H"
GCC=${GCC:-"$HOME/AmigaChrome/stoves/os32/prefix/bin/m68k-amigaos-gcc"}
VENDOR=${1:-}
if [ -z "$VENDOR" ]; then
    for d in "$HOME/AmigaChrome/stoves/os32/prefix/m68k-amigaos/ndk-include.vendor" \
             "$HOME/AmigaChrome/stoves/os32/prefix/m68k-amigaos/ndk-include" \
             "$HOME/AmigaChrome/stoves/os32/ndk/Include_H"; do
        r=$(readlink -f "$d" 2>/dev/null)
        case "$r" in */OpenNDK/Include_H) continue ;; esac
        [ -f "$d/exec/types.h" ] && { VENDOR=$d; break; }
    done
fi
[ -n "$VENDOR" ] || { echo "no vendor NDK headers found"; exit 2; }
names=$(sed -n 's/^typedef[^;]*[ \t*]\([A-Z_][A-Z_0-9]*\);.*/\1/p' "$OURS/exec/types.h")
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
i=0
: > "$tmp/map"
{
    echo '#include <exec/types.h>'
    for n in $names; do
        for c in "char" "signed char" "unsigned char" "short" "unsigned short" "int" "unsigned int" \
                 "long" "unsigned long" "float" "double" "void *" "const void *" "char *" "signed char *" \
                 "unsigned char *" "const char *" "const unsigned char *"; do
            i=$((i + 1))
            echo "$i $n $c" >> "$tmp/map"
            echo "char t$i[__builtin_types_compatible_p($n, $c) ? 1 : -1];"
        done
    done
} > "$tmp/t.c"
answer() {   # the type each name is, from which lines compile
    # the NDK's exec/types.h wants <stdint.h>, which the stove may lack
    "$GCC" -nostdinc -ffreestanding -isystem "$1" -isystem "$("$GCC" -print-file-name=include)" \
        -idirafter "$HERE/OpenNDK/check/shim" -fsyntax-only -fmax-errors=0 "$tmp/t.c" 2> "$tmp/err" >/dev/null
    if grep -v "t\.c:[0-9]*:[0-9]*: error: size of array" "$tmp/err" | grep -q "error"; then
        echo "the headers in $1 don't compile here:" >&2; grep error "$tmp/err" | grep -v "size of array" | head -5 >&2
        exit 2
    fi
    sed -n 's/.*t\.c:\([0-9]*\):.*error.*/\1/p' "$tmp/err" | sort -un > "$tmp/badlines"
    while read -r k n c; do
        line=$((k + 1))
        grep -qx "$line" "$tmp/badlines" || echo "$n=$c"
    done < "$tmp/map"
}
answer "$VENDOR" > "$tmp/vendor" || exit 2
answer "$OURS" > "$tmp/ours" || exit 2
bad=0
for n in $names; do
    v=$(sed -n "s/^$n=//p" "$tmp/vendor" | head -1)
    o=$(sed -n "s/^$n=//p" "$tmp/ours" | head -1)
    if [ "$v" = "$o" ]; then echo "same      $n: $o"; else echo "DIFFERENT $n: NDK ${v:-?}, OpenNDK ${o:-?}"; bad=1; fi
done
exit $bad
