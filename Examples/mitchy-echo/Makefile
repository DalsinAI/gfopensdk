# The Open SDK: mitchy.library, a service opened by name and called; a Shell command for AmigaOS 3.2.
#   make            build/MitchyEcho
# Needs mitchy.library (and gfopenservice.device) when it runs; nothing is linked:
# the calls are inline (<proto/mitchy.h>). Or link libopensdk.a's stubs instead:
#   make CFLAGS_EXTRA=-D_NO_INLINE LDLIBS="-L$(SDK)/Lib/build/<prefix> -lopensdk"
SDK      ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../..)
SPECS    ?= $(abspath $(SDK)/Lib/m68k-soft-m68040.specs)
CC       ?= m68k-amigaos-gcc
# -fno-delete-null-pointer-checks: address 0 is memory on an Amiga; without it GCC
# puts TRAP #7 (Software Failure 80000027) where it proves a pointer null.
CFLAGS   ?= -O2 -fno-delete-null-pointer-checks -Wall -Wextra -Wno-pointer-sign
LDLIBS   ?=

build/MitchyEcho: echo.c
	@mkdir -p build
	$(CC) -m68040 -specs=$(SPECS) -noixemul $(CFLAGS) $(CFLAGS_EXTRA) -I$(SDK)/Include -o $@ echo.c $(LDLIBS)

clean:
	rm -rf build
.PHONY: clean
