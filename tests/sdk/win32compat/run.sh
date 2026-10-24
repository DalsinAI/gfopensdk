#!/bin/sh
# Copyright (c) 2026 AmigaChrome Team. MIT licence.
set -eu
root=$(CDPATH= cd -- "$(dirname -- "$0")/../../.." && pwd)
build=$(mktemp -d)
trap 'rm -rf "$build"' EXIT HUP INT TERM
${CC:-cc} -std=c99 -O2 -Wall -Wextra -Werror ${TEST_CFLAGS:-} \
    -I"$root/Include" "$root/tests/sdk/win32compat/bitmap_test.c" \
    "$root/Lib/win32compat/src/bitmap.c" -o "$build/test"
${TEST_RUNNER:-} "$build/test"
