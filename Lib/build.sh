#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
# Builds libopensdk.a: a stub for every public call of every Open library
# whose SFD is in SFD/ (a real function that loads the library's base and
# jumps through it), for compilers and code that don't use the inline
# headers. The stubs are made by OpenNDK's tools/ndkgen.py, as OpenNDK's
# libamiga.a is; link with -lopensdk and define each base (e.g.
# struct Library *JSONBase) as you would for any library.
#   Lib/build.sh                          with the os32-gcc16 stove (m68k-amigaos-)
#   PREFIX=m68k-linux-gnu- Lib/build.sh   with an ELF m68k GCC (cloud tests)
# Output: Lib/build/<prefix>/libopensdk.a, for the 68040 (EXTRA_CFLAGS come
# after -m68040).
set -eu
SDK=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
NDK="$SDK/OpenNDK"
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
OUT="$SDK/Lib/build/$(basename -- "$PREFIX" | sed 's/-$//')"
# SFDs whose own calls don't compile as stubs yet; each is fixed in the
# library's repository and comes back here with its next pin.
#   gfopenrtg_lib.sfd: takes struct RastPort without ==include <graphics/rastport.h>
#   pixman_lib.sfd:    says struct pixman_image where libraries/pixman.h has a union
SKIP=${SKIP-"gfopenrtg_lib.sfd pixman_lib.sfd"}
rm -rf "$OUT"
mkdir -p "$OUT/stubs" "$OUT/obj"
set --
for sfd in "$SDK"/SFD/*.sfd; do
    case " $SKIP " in *" $(basename "$sfd") "*) echo "skipped: $(basename "$sfd")"; continue ;; esac
    set -- "$@" "$sfd"
done
python3 "$NDK/tools/ndkgen.py" --out "$OUT/gen" --stubs "$OUT/stubs" "$@" >/dev/null
# the stubs call ndkgen's own inline helpers (gen/), then the libraries'
# headers (Include/) and OpenNDK's; an ELF m68k GCC isn't amigaos, so say so
CFLAGS="-D__amigaos__ -nostdinc -isystem $($CC -print-file-name=include) -idirafter $NDK/check/shim
  -I$OUT/gen/Include_H -I$SDK/Include -I$NDK/Include_H
  -O2 -m68040 -fomit-frame-pointer -fno-builtin -Wall -Wextra -Werror
  -Wno-unused-parameter ${EXTRA_CFLAGS:-}"
if "$CC" -fno-late-combine-instructions -S -o /dev/null -x c /dev/null 2>/dev/null; then CFLAGS="$CFLAGS -fno-late-combine-instructions"; fi
n=0
for src in "$OUT"/stubs/*.c; do
    # shellcheck disable=SC2086
    "$CC" $CFLAGS -c "$src" -o "$OUT/obj/$(basename "$src" .c).o"
    n=$((n + 1))
done
rm -f "$OUT/libopensdk.a"
"$AR" rcs "$OUT/libopensdk.a" "$OUT"/obj/*.o
echo "$OUT/libopensdk.a: $n objects"
