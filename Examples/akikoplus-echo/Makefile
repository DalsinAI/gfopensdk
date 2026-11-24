# The Open SDK: akikoplus.library 3's services: echo/1 called and read ahead; a Shell command for AmigaOS 3.2.
#   make            build/AkikoEcho
# Needs akikoplus.library 3 and mitchy.library when it runs, and a board or a paired
# Cradle offering the service; nothing is linked: the calls are inline
# (<proto/akikoplus.h>).
SDK      ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../..)
SPECS    ?= $(abspath $(SDK)/Lib/m68k-soft-m68040.specs)
CC       ?= m68k-amigaos-gcc
# -fno-delete-null-pointer-checks: address 0 is memory on an Amiga; without it GCC
# puts TRAP #7 (Software Failure 80000027) where it proves a pointer null.
CFLAGS   ?= -O2 -fno-delete-null-pointer-checks -Wall -Wextra -Wno-pointer-sign
LDLIBS   ?=

build/AkikoEcho: echo.c
	@mkdir -p build
	$(CC) -m68040 -specs=$(SPECS) -noixemul $(CFLAGS) $(CFLAGS_EXTRA) -I$(SDK)/Include -o $@ echo.c $(LDLIBS)

clean:
	rm -rf build
.PHONY: clean
