# The Open SDK: include this in a Makefile that builds OS 4 source for OS 3.2.
#   SDK := path/to/gfopensdk
#   include $(SDK)/Lib/os4compat/os4compat.mk
#   $(CC) $(OS4COMPAT_CFLAGS) ... $(OS4COMPAT_LIBS)
# The generated proto/ and interfaces/ headers come first on the include
# path, so <proto/dos.h> gives the program IDOS as OS 4 does.
OS4COMPAT_DIR    := $(SDK)/Lib/os4compat/build
OS4COMPAT_CFLAGS := -I$(OS4COMPAT_DIR)/include -I$(SDK)/Include
# -specs: the soft-float 68040 link (libnix's soft libm020, not libm881).
OS4COMPAT_LIBS   := -specs=$(abspath $(SDK)/Lib/m68k-soft-m68040.specs) -L$(OS4COMPAT_DIR) -los4compat -lamiga
