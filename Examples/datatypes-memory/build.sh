#!/bin/sh
# Builds DTMemInfo with a stove: CC=<m68k-amigaos-gcc> NDK_INC=<OpenNDK/Include_H> sh build.sh
# MIT, Copyright (c) 2026 AmiCradle Team.
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
SDK="$HERE/../.."
CC=${CC:-m68k-amigaos-gcc}
OUT=${OUT:-"$HERE/build"}
mkdir -p "$OUT"
INC="-I$SDK/Include"
[ -n "${NDK_INC:-}" ] && INC="$INC -I$NDK_INC"
"$CC" -m68040 -specs="$SDK/Lib/m68k-soft-m68040.specs" -noixemul -O2 -fno-delete-null-pointer-checks \
    -Wall -Wextra -Werror -Wno-pointer-sign $INC -o "$OUT/DTMemInfo" "$HERE/dtmeminfo.c"
echo "$OUT/DTMemInfo"
