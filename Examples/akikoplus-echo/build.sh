#!/bin/sh
# The Open SDK: Examples/akikoplus-echo built with a stove (the kitchen's stove_build sets
# STOVE and OUT), the same as `make` with that stove's compiler.
#   STOVE  compiler root holding prefix/ (default ~/AmiCradle/stoves/os32-gcc16)
#   OUT    where AkikoEcho goes (default ./build)
# Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence.
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
STOVE=${STOVE:-"$HOME/AmiCradle/stoves/os32-gcc16"}
OUT=${OUT:-"$HERE/build"}
CC=${CC:-"$STOVE/prefix/bin/m68k-amigaos-gcc"}
SDK=$(cd "$HERE/../.." && pwd)
"$CC" --version | sed -n '1p'
mkdir -p "$OUT"
"$CC" -m68040 -specs="$SDK/Lib/m68k-soft-m68040.specs" -noixemul -O2 -fno-delete-null-pointer-checks \
    -Wall -Wextra -Werror -Wno-pointer-sign -I"$SDK/Include" -o "$OUT/AkikoEcho" "$HERE/echo.c"
echo "AkikoEcho: $(wc -c < "$OUT/AkikoEcho") bytes"
