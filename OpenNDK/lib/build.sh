#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
# Builds OpenNDK's libamiga.a: a stub for every public call in SFD/ (each
# a real function that loads the base and jumps through it, for compilers
# and code that don't use the inline headers, and the varargs forms such
# as OpenWindowTags), plus the helpers in alib/.
#   lib/build.sh                 with the os32-gcc16 stove (m68k-amigaos-)
#   PREFIX=m68k-linux-gnu- lib/build.sh   with an ELF m68k GCC (cloud tests)
# Output: lib/build/<prefix>/libamiga.a, for the 68040 (EXTRA_CFLAGS come
# after -m68040, so EXTRA_CFLAGS=-m68000 makes it a 68000 one).
#   MULTILIB=1 lib/build.sh      one for each folder the compiler's
#                                -print-multi-lib lists, built with that
#                                multilib's own flags and no -m68040 (the
#                                plain one for the compiler's default CPU,
#                                the 68000 on m68k-amigaos):
#                                lib/build/<prefix>/<folder>/libamiga.a, for
#                                a toolchain's lib/<folder>/
set -eu
NDK=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
STOVE=${STOVE:-"$HOME/AmigaChrome/stoves/os32-gcc16"}
if [ -z "${PREFIX:-}" ]; then
    if [ -x "$STOVE/prefix/bin/m68k-amigaos-gcc" ]; then
        PREFIX="$STOVE/prefix/bin/m68k-amigaos-"
    else
        PREFIX=m68k-amigaos-
    fi
fi
CC=${CC:-${PREFIX}gcc}
AR=${AR:-${PREFIX}ar}
OUT="$NDK/lib/build/$(basename -- "$PREFIX" | sed 's/-$//')"
rm -rf "$OUT"
mkdir -p "$OUT/stubs"
python3 "$NDK/tools/ndkgen.py" --out "$OUT/gen" --stubs "$OUT/stubs" "$NDK"/SFD/*.sfd >/dev/null
# -nostdinc keeps the vendor NDK out even when the compiler was set up with
# one; the compiler's own include folder still gives stdarg.h
if [ "${MULTILIB:-0}" = 1 ]; then CPU=; else CPU=-m68040; fi
CFLAGS="-nostdinc -isystem $($CC -print-file-name=include) -idirafter $NDK/check/shim -I$NDK/Include_H
  -O2 $CPU -fomit-frame-pointer -fno-builtin -Wall -Wextra -Werror
  -Wno-unused-parameter ${EXTRA_CFLAGS:-}"
# GCC's late-combine pass (GCC 15 on; GCC PR 123853, in OpenAmigaGCC 16.2.0-open3) can store a copy one place late:
# alib/argarray.c's copy of argv in ArgArrayInit came out "move.l (a0)+,(a0,d3.l)", each entry a longword higher
# (entry 0 left NULL, the terminator overwritten). Off until OpenAmigaGCC open4 (openamigagcc #29), on a compiler that
# knows the option (GCC 6.5 and GCC 14 don't).
if "$CC" -fno-late-combine-instructions -S -o /dev/null -x c /dev/null 2>/dev/null; then CFLAGS="$CFLAGS -fno-late-combine-instructions"; fi
# build DIR FLAGS: DIR/libamiga.a, every object compiled with FLAGS
build() {
    mkdir -p "$1/obj"
    n=0
    for src in "$OUT"/stubs/*.c "$NDK"/lib/alib/*.c "$NDK"/lib/alib/*.S; do
        obj="$1/obj/$(basename "$src" | sed 's/\.[cS]$/.o/')"
        # shellcheck disable=SC2086
        "$CC" $CFLAGS $2 -c "$src" -o "$obj"
        n=$((n + 1))
    done
    rm -f "$1/libamiga.a"
    "$AR" rcs "$1/libamiga.a" "$1"/obj/*.o
    echo "$1/libamiga.a: $n objects${2:+ ($2)}"
}
if [ "${MULTILIB:-0}" = 1 ]; then
    # "libm020;@m68020" is the folder libm020 and the flags -m68020
    "$CC" -print-multi-lib > "$OUT/multilibs"
    while IFS=';' read -r dir flags; do
        build "$OUT/$dir" "$(printf '%s' "$flags" | sed 's/@/ -/g')"
    done < "$OUT/multilibs"
else
    build "$OUT" ""
fi
