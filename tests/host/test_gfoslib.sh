#!/bin/sh
# Copyright (c) 2026 AmiCradle Team. MIT licence (LICENSE).
# gfoslib's host test (GF-126; amicradle-guest docs/design/Native-Modules-ABI.md
# 12.5): tools/gfmodgen.py makes a test module's gate entries, field tables
# and GFSG record from test_gfoslib.lvo and test_gfoslib.fields;
# test_gfoslib_body.c is compiled once per GF_SWAP_IN and GF_SWAP_OUT pair;
# test_gfoslib.c drives the module through a stand-in gate with every caller
# order (in and out, each BE or LE) against the module's.
#   1. gfmodgen's refusals: A6 or A7 as an argument, a field past its table;
#   2. the host (x86-64, an LE module): the four copies forced in turn, and
#      the copy with no swap checked to hold no byte-swap instruction;
#   3. ARM64 (an LE module) under qemu-aarch64, when the cross gcc is there,
#      with the same check on its object code (no rev);
#   4. a BE module: PowerPC under qemu-ppc, when powerpc-linux-gnu-gcc is
#      there. Otherwise this pass is reported as skipped, with why.
set -e
cd "$(dirname "$0")"
SDK=../..
T=$(mktemp -d)
trap 'rm -rf "$T"' EXIT
W="-std=gnu11 -O2 -Wall -Wextra -Werror"

# gfmodgen refuses what it must
printf -- '-30 Bad a0,a6\n' > "$T/a6.lvo"
printf -- '-30 Bad d0,a7\n' > "$T/a7.lvo"
printf 'table t struct g struct n 4\n  x 2 u32 in\n' > "$T/past.fields"
for bad in "$T/a6.lvo" "$T/a7.lvo"; do
    if python3 $SDK/tools/gfmodgen.py "$bad" --sig >/dev/null 2>&1; then
        echo "FAIL gfmodgen took $(cat "$bad")"; exit 1
    fi
done
if python3 $SDK/tools/gfmodgen.py test_gfoslib.lvo --sig --fields "$T/past.fields" >/dev/null 2>&1; then
    echo "FAIL gfmodgen took a field past its table"; exit 1
fi
echo "gfmodgen: refuses A6 and A7 as arguments, and a field past its table"

python3 $SDK/tools/gfmodgen.py test_gfoslib.lvo --lib gfoslibtest.library --version 1 --revision 2 \
    --prefix tm_ --out "$T/tstmod" --fields test_gfoslib.fields --include test_gfoslib_lib.h \
    --heavy TstSwizzle --ccr TstAdd --d1 TstDivMod
sig=$(python3 $SDK/tools/gfmodgen.py test_gfoslib.lvo --sig | head -1)
grep -q "$sig" "$T/tstmod.h" || { echo "FAIL gfmodgen: --sig and the header disagree"; exit 1; }

build() {   # cc out [extra]
    for si in 0 1; do for so in 0 1; do
        $1 $W -I$SDK/Include -I"$T" -I. -DGF_SWAP_IN=$si -DGF_SWAP_OUT=$so \
            -c test_gfoslib_body.c -o "$T/body$si$so.o"
    done; done
    $1 $W -I$SDK/Include -I"$T" -I. -o "$2" test_gfoslib.c test_gfoslib_mod.c "$T/tstmod.c" "$T/tstmod_gfsg.c" \
        $SDK/Lib/gfoslib/gfoslib.c "$T/body00.o" "$T/body01.o" "$T/body10.o" "$T/body11.o" $3
}

# the copy with no swap must hold no byte swap; the swap copy must hold some
noswap() {  # objdump pattern cpu
    n00=$($1 -d "$T/body00.o" | grep -c -E "$2" || true)
    n11=$($1 -d "$T/body11.o" | grep -c -E "$2" || true)
    if [ "$n00" -eq 0 ] && [ "$n11" -gt 0 ]; then
        echo "gfoslib: $3: the no-swap copy holds no byte swap; the swap copy holds $n11"
    else
        echo "FAIL gfoslib: $3: byte swaps in the no-swap copy: $n00, in the swap copy: $n11"; exit 1
    fi
}

build "${HOST_CC:-gcc}" "$T/t_gfoslib"
"$T/t_gfoslib"
if command -v objdump >/dev/null && [ "$(uname -m)" = x86_64 ]; then
    noswap objdump '\b(bswap|movbe|rol +\$0x8)' x86-64
fi
if command -v aarch64-linux-gnu-gcc >/dev/null && command -v qemu-aarch64 >/dev/null; then
    build aarch64-linux-gnu-gcc "$T/t_gfoslib_a64" -static
    qemu-aarch64 "$T/t_gfoslib_a64"
    if command -v aarch64-linux-gnu-objdump >/dev/null; then
        noswap aarch64-linux-gnu-objdump '\brev(16|32)?\b' ARM64
    fi
else
    echo "gfoslib: ARM64 pass skipped (no aarch64-linux-gnu-gcc or qemu-aarch64)"
fi
if command -v powerpc-linux-gnu-gcc >/dev/null && command -v qemu-ppc >/dev/null; then
    build powerpc-linux-gnu-gcc "$T/t_gfoslib_ppc" -static
    qemu-ppc "$T/t_gfoslib_ppc"
else
    have=""
    for q in qemu-m68k qemu-ppc; do command -v $q >/dev/null && have="$have $q"; done
    echo "gfoslib: BE-module pass skipped: no powerpc-linux-gnu-gcc (qemu here:${have:- none})"
fi
