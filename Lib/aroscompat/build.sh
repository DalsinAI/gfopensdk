#!/bin/sh
# The Open SDK's AROS compatibility library: build/libaroscompat.a
# (aroscompat_shmain for AROS_SHn commands, aroscompat_kprintf for bug()).
#   CC=m68k-amigaos-gcc AR=m68k-amigaos-ar NDK_INC=<OpenNDK/Include_H> sh build.sh
# MIT, Copyright (c) 2026 AmiCradle Team.
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
SDK="$HERE/../.."
CC=${CC:-m68k-amigaos-gcc}
AR=${AR:-m68k-amigaos-ar}
B=${OUT:-"$HERE/build"}
INC="-I$SDK/Include/aroscompat -I$SDK/Include"
[ -n "${NDK_INC:-}" ] && INC="$INC -I$NDK_INC"
mkdir -p "$B/obj"
for f in shmain kprintf; do
    "$CC" -m68040 -specs="$SDK/Lib/m68k-soft-m68040.specs" -noixemul -O2 -fno-delete-null-pointer-checks \
        -Wall -Wextra -Werror -Wno-pointer-sign $INC -c "$HERE/src/$f.c" -o "$B/obj/$f.o"
done
rm -f "$B/libaroscompat.a"
"$AR" rcs "$B/libaroscompat.a" "$B"/obj/*.o
echo "$B/libaroscompat.a"
