# The Open SDK: OpenGPU's vector drawing, a Shell command for AmigaOS 3.2.
#   make            build/OpenGPUVector
# Needs opengpu.library (OpenUp installs it) when it runs; nothing is linked:
# the calls are inline (<proto/opengpu.h>), the stream words written here.
SDK      ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../..)
SPECS    ?= $(abspath $(SDK)/Lib/m68k-soft-m68040.specs)
CC       ?= m68k-amigaos-gcc
# -fno-delete-null-pointer-checks: address 0 is memory on an Amiga; without it GCC
# puts TRAP #7 (Software Failure 80000027) where it proves a pointer null.
CFLAGS   ?= -O2 -fno-delete-null-pointer-checks -Wall -Wextra -Wno-pointer-sign

build/OpenGPUVector: vector.c
	@mkdir -p build
	$(CC) -m68040 -specs=$(SPECS) -noixemul $(CFLAGS) -I$(SDK)/Include -o $@ vector.c

clean:
	rm -rf build
.PHONY: clean
