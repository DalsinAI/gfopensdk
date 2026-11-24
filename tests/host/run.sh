#!/bin/sh
# Host tests for os4compat: the generator and the plain-C calls, with the
# host's gcc and stand-in NDK headers (mock/). The 68k build is Lib/os4compat.
# Then gfoslib (Include/gfos/gfoslib.h, GF-126): test_gfoslib.sh.
set -e
cd "$(dirname "$0")"
SDK=../..
T=$(mktemp -d)
python3 $SDK/tools/os4ifgen.py "$T" test_lib.sfd
W="-Wall -Wextra -Werror -Wno-unused-parameter -Wno-pointer-sign -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast"
# the members are built against the NDK's proto (here mock/), the program against the overrides
gcc $W -Imock -I$SDK/Include -c -o "$T/test_iface.o" "$T/src/test_iface.c"
gcc $W -Imock -I$SDK/Include -c -o "$T/test_ivar.o" "$T/src/test_ivar.c"
gcc $W -Imock -I$SDK/Include -c -o "$T/reg.o" "$T/src/os4c_registry.c"
gcc $W -I"$T/include" -Imock -I$SDK/Include -o "$T/t_iface" test_iface.c "$T"/*.o
gcc $W -I"$T/include" -Imock -I$SDK/Include -fsyntax-only test_inline.c
gcc $W -Imock -I$SDK/Include -o "$T/t_fmt" test_fmt.c $SDK/Lib/os4compat/src/utility_fmt.c
# the rule for a datatypes memory source (Examples/datatypes-memory), plain C
gcc $W -I$SDK/Examples/datatypes-memory -o "$T/t_dtmemory" test_dtmemory.c
"$T/t_dtmemory"
"$T/t_iface"
"$T/t_fmt"
rm -rf "$T"
# gfoslib: the module generator, the four byte-order copies, every caller order
sh ./test_gfoslib.sh
echo "host tests passed"
