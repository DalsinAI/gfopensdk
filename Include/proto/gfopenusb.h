/* gfopenusb.library for programs: the prototypes and, with GCC on the 68k,
 * the calls. Define OPENUSB_BASE_NAME to use a base of another name (a
 * local one, in a pure command). MIT, AmiCradle Team. */
#ifndef PROTO_OPENUSB_H
#define PROTO_OPENUSB_H

#include <clib/gfopenusb_protos.h>
#ifndef __NOLIBBASE__
extern struct Library *OpenUSBBase;
#endif
#if defined(__GNUC__) && defined(__mc68000__)
#include <inline/gfopenusb.h>
#endif

#endif
