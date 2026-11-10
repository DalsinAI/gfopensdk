#!/bin/sh
# Builds AROS workbench programs unchanged with the aroscompat kit: More and the
# commodities AltKeyQ, AutoPoint, Blanker, ClickToFront, DepthMenu and NoCapsLock.
# The AROS sources are fetched at build time from the commits in sources.txt
# (SHA-256 checked) and never kept in this repo or shipped with the SDK.
#   STOVE=<stove folder> OUT=<output folder> sh build-amiga.sh      (Cradle's stove_build)
#   CC=<m68k-amigaos-gcc> OUT=<folder> sh build-amiga.sh              (any toolchain)
# MIT, Copyright (c) 2026 AmiCradle Team (this script; the programs are AROS's, APL 1.1).
set -eu
HERE=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
SDK="$HERE/../.."
if [ -z "${CC:-}" ]; then CC="${STOVE:?set STOVE or CC}/prefix/bin/m68k-amigaos-gcc"; fi
AR=${AR:-${CC%gcc}ar}
OUT=${OUT:-"$HERE/build/out"}
W=${WORK:-"$HERE/build/work"}
mkdir -p "$OUT" "$W/src"

# 1 fetch
while read -r sum repo commit path dest; do
    case "$repo" in
        aros) url="https://raw.githubusercontent.com/aros-development-team/AROS/$commit/$path" ;;
        *)    url="https://raw.githubusercontent.com/aros-translation-team/$repo/$commit/$path" ;;
    esac
    f="$W/src/$dest"
    mkdir -p "$(dirname "$f")"
    if [ ! -f "$f" ] || ! echo "$sum  $f" | sha256sum -c - >/dev/null 2>&1; then
        curl -fsSL -o "$f" "$url"
        echo "$sum  $f" | sha256sum -c - >/dev/null || { echo "checksum mismatch: $path" >&2; exit 1; }
    fi
done < "$HERE/sources.txt"

# 2 the kit, and OpenNDK's libamiga.a (InvertString)
CC="$CC" AR="$AR" NDK_INC="$SDK/OpenNDK/Include_H" OUT="$W/aroscompat" sh "$SDK/Lib/aroscompat/build.sh" >/dev/null
PREFIX="${CC%gcc}" sh "$SDK/OpenNDK/lib/build.sh" >/dev/null
NDKLIB=$(dirname "$(ls "$SDK"/OpenNDK/lib/build/*/libamiga.a | head -1)")

# 3 the programs
CFLAGS="-m68040 -specs=$SDK/Lib/m68k-soft-m68040.specs -noixemul -O2 -fno-delete-null-pointer-checks
  -I$SDK/Include/aroscompat -I$SDK/Include -I$SDK/OpenNDK/Include_H
  -Wno-error=incompatible-pointer-types -Wno-error=int-conversion
  -Wno-error=implicit-function-declaration -Wno-error=implicit-int -w"
LIBS="-L$NDKLIB -L$W/aroscompat -laroscompat"
prog() { # name srcdir cdfile files...
    n=$1; d=$2; cd_=$3; shift 3
    mkdir -p "$W/gen/$n"
    python3 "$SDK/tools/catcomp_h.py" "$cd_" -o "$W/gen/$n/strings.h"
    # shellcheck disable=SC2086
    "$CC" $CFLAGS -I"$W/gen/$n" -I"$d" -o "$OUT/$n" "$@" $LIBS
    echo "$n $(wc -c < "$OUT/$n") bytes"
}
S="$W/src"
prog More "$S/More" "$S/More/catalogs/more.cd" "$S/More/more.c" "$S/More/req.c" "$S/More/locale.c" "$S/More/misc.c"
for n in AltKeyQ AutoPoint Blanker ClickToFront DepthMenu NoCapsLock; do
    prog "$n" "$S/commodities" "$S/commodities/catalogs/commodities.cd" "$S/commodities/$n.c"
done
(cd "$OUT" && sha256sum More AltKeyQ AutoPoint Blanker ClickToFront DepthMenu NoCapsLock > SHA256SUMS)
echo DONE
