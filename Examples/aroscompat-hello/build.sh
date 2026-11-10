#!/bin/sh
# Builds AROSHello with a stove: CC=<m68k-amigaos-gcc> NDK_INC=<OpenNDK/Include_H> sh build.sh
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
SDK="$HERE/../.."
CC=${CC:-m68k-amigaos-gcc}
OUT=${OUT:-"$HERE/build"}
mkdir -p "$OUT"
CC="$CC" AR="${AR:-${CC%gcc}ar}" OUT="$OUT/aroscompat" sh "$SDK/Lib/aroscompat/build.sh" >/dev/null
INC="-I$SDK/Include/aroscompat -I$SDK/Include"
[ -n "${NDK_INC:-}" ] && INC="$INC -I$NDK_INC"
"$CC" -m68040 -specs="$SDK/Lib/m68k-soft-m68040.specs" -noixemul -O2 -fno-delete-null-pointer-checks \
    -Wall -Wextra -Werror -Wno-pointer-sign -Wno-format $INC -o "$OUT/AROSHello" "$HERE/hello.c" \
    -L"$OUT/aroscompat" -laroscompat
echo "$OUT/AROSHello"
