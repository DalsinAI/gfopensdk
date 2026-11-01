#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
# Checks OpenNDK against a vendor NDK 3.2 installed on this machine: every
# structure size, field offset and constant value (layouts.py), and every
# call's offset, registers and prototype (compare_sfd.py). Writes the two
# reports to check/out/ and exits 1 if anything both have differs.
#   check/compare_ndk.sh NDK_DIR
# NDK_DIR holds the vendor's Include_H and SFD folders (on Daletop,
# ~/AmigaChrome/stoves/os32/ndk). The vendor's files are only read, never
# copied: check/out/ is ignored by git and keeps only names and numbers.
# CC must be an ELF m68k GCC (Ubuntu's m68k-linux-gnu-gcc, or the aros68k
# stove's), which lists OpenNDK's structures and fields from its debug
# information; READELF any readelf. Both header sets are then measured with
# VCC, the m68k-amigaos GCC the vendor NDK is written for (found on PATH or
# under ~/AmigaChrome/stoves when not set; CC when there is none).
set -eu
NDK=${1:?usage: compare_ndk.sh NDK_DIR}
[ -d "$NDK" ] || { echo "no NDK folder at $NDK" >&2; exit 2; }
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
OUT="$HERE/out"
mkdir -p "$OUT"
if [ -z "${CC:-}" ]; then
    for c in m68k-linux-gnu-gcc "$HOME"/AmigaChrome/stoves/aros68k-gcc16/prefix/bin/m68k-aros-gcc; do
        if command -v "$c" >/dev/null 2>&1; then CC=$c; break; fi
    done
fi
[ -n "${CC:-}" ] || { echo "no ELF m68k GCC: set CC=" >&2; exit 2; }
if [ -z "${VCC:-}" ]; then
    VCC=$(command -v m68k-amigaos-gcc 2>/dev/null || true)
    [ -n "$VCC" ] || VCC=$(find "$HOME/AmigaChrome/stoves" -name m68k-amigaos-gcc \( -type f -o -type l \) 2>/dev/null | head -n 1)
    [ -n "$VCC" ] || VCC=$CC
fi
echo "listing with $CC, measuring with $VCC"
INC=$NDK/Include_H; [ -d "$INC" ] || INC=$NDK/include_h; [ -d "$INC" ] || INC=$NDK/include
SFD=$NDK/SFD; [ -d "$SFD" ] || SFD=$NDK/sfd
status=0
CC=$CC python3 "$HERE/layouts.py" dump "$HERE/../Include_H" "$OUT/probe.json"
CC=$VCC python3 "$HERE/layouts.py" measure "$HERE/../Include_H" "$OUT/probe.json" "$OUT/openndk.json"
CC=$VCC python3 "$HERE/layouts.py" measure "$INC" "$OUT/probe.json" "$OUT/ndk.json"
# the vendor's own field lists, read from the debug information, for the
# report's layout of each structure that differs (skipped if it won't build)
CC=$CC python3 "$HERE/layouts.py" dump "$INC" "$OUT/ndk-fields.json" || rm -f "$OUT/ndk-fields.json"
python3 "$HERE/layouts.py" compare "$OUT/openndk.json" "$OUT/ndk.json" --report "$OUT/layouts.md" \
    --detail "$OUT/ndk-fields.json" || status=1
if [ -d "$SFD" ]; then
    python3 "$HERE/compare_sfd.py" "$SFD" --report "$OUT/sfd.md" || status=1
fi
echo "reports: $OUT/layouts.md $OUT/sfd.md"
exit $status
