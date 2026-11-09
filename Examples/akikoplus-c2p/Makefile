# The Open SDK: akikoplus.library's chunky to planar, checked; a Shell command for AmigaOS 3.2.
#   make            build/AkikoC2P
# Needs akikoplus.library 2 when it runs (and mitchy.library for the board; without
# the board it does the work on the 68k); nothing is linked: the calls are inline
# (<proto/akikoplus.h>).
SDK      ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../..)
SPECS    ?= $(abspath $(SDK)/Lib/m68k-soft-m68040.specs)
CC       ?= m68k-amigaos-gcc
# -fno-delete-null-pointer-checks: address 0 is memory on an Amiga; without it GCC
# puts TRAP #7 (Software Failure 80000027) where it proves a pointer null.
CFLAGS   ?= -O2 -fno-delete-null-pointer-checks -Wall -Wextra -Wno-pointer-sign
LDLIBS   ?=

build/AkikoC2P: c2p.c
	@mkdir -p build
	$(CC) -m68040 -specs=$(SPECS) -noixemul $(CFLAGS) $(CFLAGS_EXTRA) -I$(SDK)/Include -o $@ c2p.c $(LDLIBS)

clean:
	rm -rf build
.PHONY: clean
