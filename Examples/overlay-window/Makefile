# The Open SDK: gfopenoverlay.library, an overlay in a window; a Shell command for AmigaOS 3.2.
#   make            build/OverlayWindow
# Needs gfopenoverlay.library 1 in LIBS: and layers.library 47.111 or later when it runs.
SDK      ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../..)
CC       ?= m68k-amigaos-gcc
CFLAGS   ?= -O2 -fno-delete-null-pointer-checks -Wall -Wextra -Wno-pointer-sign

build/OverlayWindow: overlay.c
	@mkdir -p build
	$(CC) -m68020 -noixemul $(CFLAGS) $(CFLAGS_EXTRA) -I$(SDK)/Include -o $@ overlay.c

clean:
	rm -rf build
