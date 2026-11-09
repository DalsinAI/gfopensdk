# The Open SDK: physfs.library, a drawer or an archive listed or read; a Shell command for AmigaOS 3.2.
#   make            build/PhysFSList
# Needs physfs.library 1 in LIBS: when it runs (and LIBS:z.library for
# deflated zip members). -lphysfs_auto opens the library before main();
# Lib/build.sh builds libphysfs_auto.a (Lib/build/m68k-amigaos/ with the
# os32-gcc16 stove).
SDK      ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../..)
SPECS    ?= $(abspath $(SDK)/Lib/m68k-soft-m68040.specs)
CC       ?= m68k-amigaos-gcc
SDKLIB   ?= $(SDK)/Lib/build/m68k-amigaos
# -fno-delete-null-pointer-checks: address 0 is memory on an Amiga; without it GCC
# puts TRAP #7 (Software Failure 80000027) where it proves a pointer null.
CFLAGS   ?= -O2 -fno-delete-null-pointer-checks -Wall -Wextra -Wno-pointer-sign
LDLIBS   ?= -L$(SDKLIB) -lphysfs_auto

build/PhysFSList: list.c
	@mkdir -p build
	$(CC) -m68040 -specs=$(SPECS) -noixemul $(CFLAGS) $(CFLAGS_EXTRA) -I$(SDK)/Include -o $@ list.c $(LDLIBS)

clean:
	rm -rf build
.PHONY: clean
