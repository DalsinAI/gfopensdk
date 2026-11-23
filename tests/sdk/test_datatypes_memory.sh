#!/bin/sh
# Examples/datatypes-memory: the rule on the host, then DTMemInfo built with a
# 68k stove against this checkout's OpenNDK headers, as strictly as the open
# libraries build. The stove's gcc is CC, or $STOVE/prefix/bin/m68k-amigaos-gcc
# in the kitchen; with neither the build step is skipped and said so.
#   sh tests/sdk/test_datatypes_memory.sh
# MIT, Copyright (c) 2026 AmiCradle Team.
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)
T=$(mktemp -d)
trap 'rm -rf "$T"' EXIT
${HOSTCC:-gcc} -Wall -Wextra -Werror -I"$HERE/Examples/datatypes-memory" -o "$T/t" "$HERE/tests/host/test_dtmemory.c"
"$T/t"
grep -q 'DTST_MEMORY: the file.s bytes are in memory' "$HERE/OpenNDK/Include_H/datatypes/datatypesclass.h" ||
    { echo "FAIL the header note beside DTST_MEMORY is gone"; exit 1; }
grep -q 'Examples/datatypes-memory' "$HERE/Docs/datatypes-memory.md" ||
    { echo "FAIL Docs/datatypes-memory.md does not name the example"; exit 1; }
if [ -z "${CC:-}" ] && [ -n "${STOVE:-}" ] && [ -x "$STOVE/prefix/bin/m68k-amigaos-gcc" ]; then
    CC=$STOVE/prefix/bin/m68k-amigaos-gcc
fi
if [ -z "${CC:-}" ]; then
    echo "datatypes-memory: no 68k compiler (CC or STOVE): DTMemInfo not built"
    exit 0
fi
"$CC" --version | head -n 1
CC="$CC" NDK_INC="$HERE/OpenNDK/Include_H" OUT="$T/out" sh "$HERE/Examples/datatypes-memory/build.sh"
[ -s "$T/out/DTMemInfo" ] || { echo "FAIL DTMemInfo was not built"; exit 1; }
echo "datatypes-memory: DTMemInfo built ($(wc -c < "$T/out/DTMemInfo") bytes)"
