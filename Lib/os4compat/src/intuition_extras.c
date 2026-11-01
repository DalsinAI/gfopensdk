/* Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * BOOPSI method calls, which OS 4 has in intuition.library and OS 3.2 has
 * only in amiga.lib: each is a call of a class's dispatcher hook.
 */
#include "os4c_internal.h"
#include <proto/utility.h>

ULONG os4c_IDoMethodA(Object *obj, Msg msg)
{
	return obj ? CallHookPkt(&OCLASS(obj)->cl_Dispatcher, obj, msg) : 0;
}

ULONG os4c_IDoMethod(Object *obj, ULONG methodID, ...)
{
	return os4c_IDoMethodA(obj, (Msg)&methodID);
}

ULONG os4c_IDoSuperMethodA(struct IClass *cl, Object *obj, Msg msg)
{
	return cl && obj ? CallHookPkt(&cl->cl_Super->cl_Dispatcher, obj, msg) : 0;
}

ULONG os4c_IDoSuperMethod(struct IClass *cl, Object *obj, ULONG methodID, ...)
{
	return os4c_IDoSuperMethodA(cl, obj, (Msg)&methodID);
}

ULONG os4c_ICoerceMethodA(struct IClass *cl, Object *obj, Msg msg)
{
	return cl && obj ? CallHookPkt(&cl->cl_Dispatcher, obj, msg) : 0;
}
