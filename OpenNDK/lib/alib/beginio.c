/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* BeginIO: the device's own BeginIO vector (-30), called directly, as
 * SendIO would but without clearing io_Flags. */
#include "alib.h"

VOID BeginIO(struct IORequest *ioReq)
{
	register struct IORequest *a1 __asm("a1") = ioReq;
	register struct Device *a6 __asm("a6") = ioReq->io_Device;
	register ULONG d0 __asm("d0"), d1 __asm("d1"), a0 __asm("a0");
	__asm__ __volatile__ ("jsr -30(%/a6)"
		: "=r" (d0), "=r" (d1), "=r" (a0), "+r" (a1)
		: "r" (a6)
		: "cc", "memory");
}
