# The Open SDK: a window in HTML and CSS (OpenLayout UI) for AmigaOS 3.2.
#   make            build/HelloUI.os32
# OLUI is OpenLayout's repository (DalsinAI/gfopenlayout) with
# ./build-ui-amiga.sh run in it, which makes build-amiga/ui/libolui.a.
# Soft float (-m68040, no -m68881): one binary for 68040s with or without
# an FPU. SPECS keeps its link on libnix's soft maths.
NAME     ?= HelloUI
SRC      ?= hello.c
SDK      ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../..)
SPECS    ?= $(abspath $(SDK)/Lib/m68k-soft-m68040.specs)
OLUI     ?= $(HOME)/gfopenlayout
CC_OS32  ?= m68k-amigaos-gcc
# -fno-delete-null-pointer-checks: address 0 is memory on an Amiga; without it GCC
# puts TRAP #7 (Software Failure 80000027) where it proves a pointer null.
CFLAGS   ?= -O2 -fno-delete-null-pointer-checks -Wall -Wextra -Wno-pointer-sign

all: os32
os32: build/$(NAME).os32

build/$(NAME).os32: $(SRC)
	@mkdir -p build
	$(CC_OS32) -m68040 -specs=$(SPECS) -noixemul $(CFLAGS) -I$(SDK)/Include -I$(OLUI)/include \
	  -o $@ $(SRC) $(OLUI)/build-amiga/ui/libolui.a

clean:
	rm -rf build
.PHONY: all os32 clean
