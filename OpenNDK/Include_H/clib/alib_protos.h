#ifndef CLIB_ALIB_PROTOS_H
#define CLIB_ALIB_PROTOS_H
/*
 * OpenNDK: the calls libamiga.a provides beside the library stubs.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 * Written by hand (the other clib/ headers are generated). The code is
 * in OpenNDK/lib/alib.
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_IO_H
#include <exec/io.h>
#endif
#ifndef EXEC_TASKS_H
#include <exec/tasks.h>
#endif
#ifndef DEVICES_TIMER_H
#include <devices/timer.h>
#endif
#ifndef DEVICES_INPUTEVENT_H
#include <devices/inputevent.h>
#endif
#ifndef DEVICES_KEYMAP_H
#include <devices/keymap.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef INTUITION_CLASSES_H
#include <intuition/classes.h>
#endif
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif
#ifndef LIBRARIES_COMMODITIES_H
#include <libraries/commodities.h>
#endif
#ifndef GRAPHICS_GRAPHINT_H
#include <graphics/graphint.h>
#endif
#ifndef REXX_STORAGE_H
#include <rexx/storage.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* exec helpers */
VOID BeginIO(struct IORequest *ioReq);
struct IORequest *CreateExtIO(CONST struct MsgPort *port, LONG ioSize);
VOID DeleteExtIO(struct IORequest *ioReq);
struct IOStdReq *CreateStdIO(CONST struct MsgPort *port);
VOID DeleteStdIO(struct IOStdReq *ioReq);
struct MsgPort *CreatePort(CONST_STRPTR name, LONG pri);
VOID DeletePort(struct MsgPort *ioReq);
struct Task *CreateTask(CONST_STRPTR name, LONG pri, CONST_APTR initPC, ULONG stackSize);
VOID DeleteTask(struct Task *task);
VOID NewList(struct List *list);

/* Memory pools that also work before exec V39 */
APTR LibCreatePool(ULONG memFlags, ULONG puddleSize, ULONG threshSize);
VOID LibDeletePool(APTR poolHeader);
APTR LibAllocPooled(APTR poolHeader, ULONG memSize);
VOID LibFreePooled(APTR poolHeader, APTR memory, ULONG memSize);

/* Random numbers */
ULONG FastRand(ULONG seed);
UWORD RangeRand(ULONG maxValue);

/* Hooks and BOOPSI */
ULONG HookEntry(struct Hook *hookPtr, Object *obj, APTR message);
ULONG CallHookA(struct Hook *hookPtr, Object *obj, APTR message);
ULONG CallHook(struct Hook *hookPtr, Object *obj, ...);
ULONG DoMethodA(Object *obj, Msg message);
ULONG DoMethod(Object *obj, ULONG methodID, ...);
ULONG DoSuperMethodA(struct IClass *cl, Object *obj, Msg message);
ULONG DoSuperMethod(struct IClass *cl, Object *obj, ULONG methodID, ...);
ULONG CoerceMethodA(struct IClass *cl, Object *obj, Msg message);
ULONG CoerceMethod(struct IClass *cl, Object *obj, ULONG methodID, ...);
ULONG SetSuperAttrs(struct IClass *cl, Object *obj, ULONG tag1, ...);

/* Timer */
LONG TimeDelay(LONG unit, ULONG seconds, ULONG micros);
LONG DoTimer(TimeVal_Type *tv, LONG unit, LONG command);

/* Tool types for programs started from the Shell or Workbench */
STRPTR *ArgArrayInit(LONG argc, CONST_STRPTR *argv);
VOID ArgArrayDone(VOID);
STRPTR ArgString(CONST_STRPTR *tt, CONST_STRPTR entry, CONST_STRPTR defaultString);
LONG ArgInt(CONST_STRPTR *tt, CONST_STRPTR entry, LONG defaultVal);

/* Commodities */
CxObj *HotKey(CONST_STRPTR description, struct MsgPort *port, LONG id);
VOID FreeIEvents(struct InputEvent *events);
struct KeyMap;
struct InputEvent *InvertString(CONST_STRPTR str, CONST struct KeyMap *km);

/* ARexx: a host's way to the variables of the program whose command it
 * holds, through rexxsyslib.library 45's GetRexxVarFromMsg and
 * SetRexxVarFromMsg. Each answers 0, or an ERR10_ code from
 * <rexx/errors.h>: 3 no memory, 9 too long, 10 not a message from an
 * ARexx program, 14 no rexxsyslib.library 45. GetRexxVar's value (at most
 * 255 characters) is a copy in libamiga.a's own memory, good until the
 * program's next GetRexxVar; don't write to it. */
BOOL CheckRexxMsg(CONST struct RexxMsg *rexxmsg);
LONG GetRexxVar(struct RexxMsg *rexxmsg, CONST_STRPTR name, STRPTR *result);
LONG SetRexxVar(struct RexxMsg *rexxmsg, CONST_STRPTR name, CONST_STRPTR value, LONG length);

#ifdef __cplusplus
}
#endif

#endif /* CLIB_ALIB_PROTOS_H */
