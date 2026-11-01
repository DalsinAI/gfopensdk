/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* CallHookA and the BOOPSI method helpers. A hook is entered at h_Entry
 * with the hook in a0, the object in a2 and the message in a1; a method
 * goes to the class's dispatcher hook. These call h_Entry directly, so
 * they need no utility.library. */
#include "alib.h"
#include <stdarg.h>

static inline ULONG call_entry(struct Hook *hook, APTR obj, APTR msg)
{
	register struct Hook *a0 __asm("a0") = hook;
	register APTR a1 __asm("a1") = msg;
	register APTR a2 __asm("a2") = obj;
	register ULONG d0 __asm("d0");
	register ULONG d1 __asm("d1");
	/* push the return address, then h_Entry, and "return" into the hook:
	 * the same on every 68k, with no register to spare */
	__asm__ __volatile__ ("pea 1f\n\tmove.l 8(%/a0),-(%/sp)\n\trts\n1:"
		: "=r" (d0), "=r" (d1), "+r" (a0), "+r" (a1)
		: "r" (a2)
		: "cc", "memory");
	return d0;
}

#define OCLASS_OF(o) (((struct IClass **)(o))[-1])

ULONG CallHookA(struct Hook *hook, Object *obj, APTR msg)
{
	return call_entry(hook, obj, msg);
}

ULONG CallHook(struct Hook *hook, Object *obj, ...)
{
	va_list ap;
	ULONG r;
	va_start(ap, obj);
	r = call_entry(hook, obj, (APTR)ap);
	va_end(ap);
	return r;
}

ULONG DoMethodA(Object *obj, Msg msg)
{
	if (!obj)
		return 0;
	return call_entry(&OCLASS_OF(obj)->cl_Dispatcher, obj, msg);
}

ULONG DoMethod(Object *obj, ULONG methodID, ...)
{
	if (!obj)
		return 0;
	return call_entry(&OCLASS_OF(obj)->cl_Dispatcher, obj, &methodID);
}

ULONG DoSuperMethodA(struct IClass *cl, Object *obj, Msg msg)
{
	if (!cl || !obj)
		return 0;
	return call_entry(&cl->cl_Super->cl_Dispatcher, obj, msg);
}

ULONG DoSuperMethod(struct IClass *cl, Object *obj, ULONG methodID, ...)
{
	if (!cl || !obj)
		return 0;
	return call_entry(&cl->cl_Super->cl_Dispatcher, obj, &methodID);
}

ULONG CoerceMethodA(struct IClass *cl, Object *obj, Msg msg)
{
	if (!cl || !obj)
		return 0;
	return call_entry(&cl->cl_Dispatcher, obj, msg);
}

ULONG CoerceMethod(struct IClass *cl, Object *obj, ULONG methodID, ...)
{
	if (!cl || !obj)
		return 0;
	return call_entry(&cl->cl_Dispatcher, obj, &methodID);
}

ULONG SetSuperAttrs(struct IClass *cl, Object *obj, ULONG tag1, ...)
{
	struct opSet ops;
	ops.MethodID = OM_SET;
	ops.ops_AttrList = (struct TagItem *)&tag1;
	ops.ops_GInfo = NULL;
	return DoSuperMethodA(cl, obj, (Msg)&ops);
}
