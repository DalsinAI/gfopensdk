# The Open SDK: a native job on the CPU cores board; a Shell command for AmigaOS 3.2.
#   make            build/CoresNativeJob, build/job.x86_64.bin and build/job.arm64.bin
#   make check      runs both job builds' code on this host where it can (test_host.c)
# Copy CoresNativeJob and the two .bin files to the same drawer on the Amiga.
# The jobs need a host C compiler for each ISA: gcc on an x86-64 PC, and
# aarch64-linux-gnu-gcc (or gcc on a Pi). Missing one skips that .bin.
SDK      ?= $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../..)
SPECS    ?= $(abspath $(SDK)/Lib/m68k-soft-m68040.specs)
CC       ?= m68k-amigaos-gcc
CFLAGS   ?= -O2 -fno-delete-null-pointer-checks -Wall -Wextra -Wno-pointer-sign
X86_CC   ?= x86_64-linux-gnu-gcc
ARM_CC   ?= aarch64-linux-gnu-gcc
JOBFLAGS  = -O2 -fPIC -ffreestanding -nostdlib -fno-stack-protector -fno-asynchronous-unwind-tables \
            -fno-exceptions -I$(SDK)/Include
OBJCOPY_X86 ?= x86_64-linux-gnu-objcopy
OBJCOPY_ARM ?= aarch64-linux-gnu-objcopy

all: build/CoresNativeJob build/job.x86_64.bin build/job.arm64.bin

build/CoresNativeJob: native.c
	@mkdir -p build
	$(CC) -m68040 -specs=$(SPECS) -noixemul $(CFLAGS) -I$(SDK)/Include -o $@ native.c

# Only the entry's section: one function, starting at offset 0.
build/job.x86_64.bin: job.c
	@mkdir -p build
	$(X86_CC) $(JOBFLAGS) -fcf-protection=none -c -o build/job.x86_64.o job.c
	$(OBJCOPY_X86) -O binary --only-section=.text.acn_entry build/job.x86_64.o $@

build/job.arm64.bin: job.c
	@mkdir -p build
	$(ARM_CC) $(JOBFLAGS) -mbranch-protection=none -c -o build/job.arm64.o job.c
	$(OBJCOPY_ARM) -O binary --only-section=.text.acn_entry build/job.arm64.o $@

check: build/job.x86_64.bin build/job.arm64.bin
	cc -O2 -I$(SDK)/Include -o build/test_host test_host.c
	./build/test_host build

clean:
	rm -rf build
.PHONY: all check clean
