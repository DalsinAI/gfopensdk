# Copyright (c) 2026 AmigaChrome Team. MIT licence.
SDK := ../..
CC = m68k-amigaos-gcc
AR = m68k-amigaos-ar
CPU ?= -m68040 -m68881
CFLAGS ?= -std=c99 -O2 -Wall -Wextra -Werror -fno-common -fno-strict-aliasing
BUILD ?= build
all: $(BUILD)/libwin32compat.a
$(BUILD)/bitmap.o: src/bitmap.c $(SDK)/Include/win32compat/bitmap.h
	mkdir -p $(BUILD)
	$(CC) $(CPU) $(CPPFLAGS) $(CFLAGS) -I$(SDK)/Include -c $< -o $@
$(BUILD)/libwin32compat.a: $(BUILD)/bitmap.o
	$(AR) rcs $@ $<
clean:
	rm -rf $(BUILD)
.PHONY: all clean
