/* gfopenusb.library's calls for GCC on the 68k (clib/gfopenusb_protos.h).
 * The base is OPENUSB_BASE_NAME (default OpenUSBBase), global or local.
 * Each macro takes its arguments into temporaries before it loads the
 * registers, so an argument may itself be a library call. Our own header,
 * NDK-independent. MIT, AmiCradle Team. */
#ifndef INLINE_OPENUSB_H
#define INLINE_OPENUSB_H

#ifndef OPENUSB_BASE_NAME
#define OPENUSB_BASE_NAME OpenUSBBase
#endif

#define __OUSB_B  register struct Library *_b __asm("a6") = (struct Library *)(__ob)
#define __OUSB_X  "d1", "cc", "memory"

#define OUSB_AddHardware(name, unit) ({ CONST_STRPTR __n = (name); ULONG __u = (unit); void *__ob = (OPENUSB_BASE_NAME); \
    __OUSB_B; register LONG _r __asm("d0") = (LONG)__u; register CONST_STRPTR _a0 __asm("a0") = __n; \
    __asm__ __volatile__ ("jsr -30(%%a6)" : "+r"(_r), "+r"(_a0) : "r"(_b) : "a1", __OUSB_X); _r; })

#define OUSB_LockList() ({ void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    __asm__ __volatile__ ("jsr -36(%%a6)" : : "r"(_b) : "d0", "a0", "a1", __OUSB_X); })

#define OUSB_UnlockList() ({ void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    __asm__ __volatile__ ("jsr -42(%%a6)" : : "r"(_b) : "d0", "a0", "a1", __OUSB_X); })

#define OUSB_NextDevice(prev) ({ struct OUSBDevice *__p = (prev); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register struct OUSBDevice *_r __asm("d0"); register struct OUSBDevice *_a0 __asm("a0") = __p; \
    __asm__ __volatile__ ("jsr -48(%%a6)" : "=r"(_r), "+r"(_a0) : "r"(_b) : "a1", __OUSB_X); _r; })

#define OUSB_Generation() ({ void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; register ULONG _r __asm("d0"); \
    __asm__ __volatile__ ("jsr -54(%%a6)" : "=r"(_r) : "r"(_b) : "a0", "a1", __OUSB_X); _r; })

#define OUSB_HardwareName(bus, unit) ({ ULONG __bu = (bus); ULONG *__un = (unit); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register STRPTR _r __asm("d0") = (STRPTR)__bu; register ULONG *_a0 __asm("a0") = __un; \
    __asm__ __volatile__ ("jsr -60(%%a6)" : "+r"(_r), "+r"(_a0) : "r"(_b) : "a1", __OUSB_X); _r; })

#define OUSB_Control(dev, setup, data, len, timeout, actual) ({ struct OUSBDevice *__d = (dev); const UBYTE *__s = (setup); \
    APTR __da = (data); ULONG __l = (len), __t = (timeout); ULONG *__ac = (actual); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register LONG _r __asm("d0") = (LONG)__l; register ULONG _d1 __asm("d1") = __t; \
    register struct OUSBDevice *_a0 __asm("a0") = __d; register const UBYTE *_a1 __asm("a1") = __s; \
    register APTR _a2 __asm("a2") = __da; register ULONG *_a3 __asm("a3") = __ac; \
    __asm__ __volatile__ ("jsr -66(%%a6)" : "+r"(_r), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_b), "r"(_a2), "r"(_a3) : "cc", "memory"); _r; })

#define OUSB_OpenPipe(dev, ep) ({ struct OUSBDevice *__d = (dev); ULONG __e = (ep); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register struct OUSBPipe *_r __asm("d0") = (struct OUSBPipe *)__e; register struct OUSBDevice *_a0 __asm("a0") = __d; \
    __asm__ __volatile__ ("jsr -72(%%a6)" : "+r"(_r), "+r"(_a0) : "r"(_b) : "a1", __OUSB_X); _r; })

#define OUSB_ClosePipe(pipe) ({ struct OUSBPipe *__p = (pipe); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register struct OUSBPipe *_a0 __asm("a0") = __p; \
    __asm__ __volatile__ ("jsr -78(%%a6)" : "+r"(_a0) : "r"(_b) : "d0", "a1", __OUSB_X); })

#define OUSB_Transfer(pipe, data, len, timeout, actual) ({ struct OUSBPipe *__p = (pipe); APTR __da = (data); \
    ULONG __l = (len), __t = (timeout); ULONG *__ac = (actual); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register LONG _r __asm("d0") = (LONG)__l; register ULONG _d1 __asm("d1") = __t; \
    register struct OUSBPipe *_a0 __asm("a0") = __p; register APTR _a1 __asm("a1") = __da; register ULONG *_a2 __asm("a2") = __ac; \
    __asm__ __volatile__ ("jsr -84(%%a6)" : "+r"(_r), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_b), "r"(_a2) : "cc", "memory"); _r; })

#define OUSB_SendTransfer(pipe, data, len, timeout) ({ struct OUSBPipe *__p = (pipe); APTR __da = (data); \
    ULONG __l = (len), __t = (timeout); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register LONG _r __asm("d0") = (LONG)__l; register ULONG _d1 __asm("d1") = __t; \
    register struct OUSBPipe *_a0 __asm("a0") = __p; register APTR _a1 __asm("a1") = __da; \
    __asm__ __volatile__ ("jsr -90(%%a6)" : "+r"(_r), "+r"(_d1), "+r"(_a0), "+r"(_a1) : "r"(_b) : "cc", "memory"); _r; })

#define OUSB_WaitTransfer(pipe, actual) ({ struct OUSBPipe *__p = (pipe); ULONG *__ac = (actual); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register LONG _r __asm("d0"); register struct OUSBPipe *_a0 __asm("a0") = __p; register ULONG *_a1 __asm("a1") = __ac; \
    __asm__ __volatile__ ("jsr -96(%%a6)" : "=r"(_r), "+r"(_a0), "+r"(_a1) : "r"(_b) : __OUSB_X); _r; })

#define OUSB_CheckTransfer(pipe) ({ struct OUSBPipe *__p = (pipe); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register LONG _r __asm("d0"); register struct OUSBPipe *_a0 __asm("a0") = __p; \
    __asm__ __volatile__ ("jsr -102(%%a6)" : "=r"(_r), "+r"(_a0) : "r"(_b) : "a1", __OUSB_X); _r; })

#define OUSB_AbortTransfer(pipe) ({ struct OUSBPipe *__p = (pipe); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register struct OUSBPipe *_a0 __asm("a0") = __p; \
    __asm__ __volatile__ ("jsr -108(%%a6)" : "+r"(_a0) : "r"(_b) : "d0", "a1", __OUSB_X); })

#define OUSB_PipeSignal(pipe) ({ struct OUSBPipe *__p = (pipe); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register ULONG _r __asm("d0"); register struct OUSBPipe *_a0 __asm("a0") = __p; \
    __asm__ __volatile__ ("jsr -114(%%a6)" : "=r"(_r), "+r"(_a0) : "r"(_b) : "a1", __OUSB_X); _r; })

#define OUSB_ClearHalt(pipe) ({ struct OUSBPipe *__p = (pipe); void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register LONG _r __asm("d0"); register struct OUSBPipe *_a0 __asm("a0") = __p; \
    __asm__ __volatile__ ("jsr -120(%%a6)" : "=r"(_r), "+r"(_a0) : "r"(_b) : "a1", __OUSB_X); _r; })

#define OUSB_ReadLog(index, what, args) ({ ULONG __i = (index); CONST_STRPTR *__w = (what); ULONG *__ar = (args); \
    void *__ob = (OPENUSB_BASE_NAME); __OUSB_B; \
    register LONG _r __asm("d0") = (LONG)__i; register CONST_STRPTR *_a0 __asm("a0") = __w; register ULONG *_a1 __asm("a1") = __ar; \
    __asm__ __volatile__ ("jsr -126(%%a6)" : "+r"(_r), "+r"(_a0), "+r"(_a1) : "r"(_b) : __OUSB_X); _r; })

#endif
