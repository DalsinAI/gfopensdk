/* Made by hand from MUI's published muimaster_lib.fd (offsets and registers).
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef INLINE_MUIMASTER_H
#define INLINE_MUIMASTER_H
#ifndef __INLINE_MACROS_H
#include <inline/macros.h>
#endif
#ifndef MUIMASTER_BASE_NAME
#define MUIMASTER_BASE_NAME MUIMasterBase
#endif

#define MUI_NewObjectA(classname,tags) LP2(0x1e, Object *, MUI_NewObjectA, CONST_STRPTR, classname, a0, struct TagItem *, tags, a1, , MUIMASTER_BASE_NAME)
#define MUI_DisposeObject(obj) LP1NR(0x24, MUI_DisposeObject, Object *, obj, a0, , MUIMASTER_BASE_NAME)
#define MUI_RequestA(app,win,flags,title,gadgets,format,params) LP7(0x2a, LONG, MUI_RequestA, APTR, app, d0, APTR, win, d1, ULONG, flags, d2, CONST_STRPTR, title, a0, CONST_STRPTR, gadgets, a1, CONST_STRPTR, format, a2, APTR, params, a3, , MUIMASTER_BASE_NAME)
#define MUI_AllocAslRequest(type,tags) LP2(0x30, APTR, MUI_AllocAslRequest, ULONG, type, d0, struct TagItem *, tags, a0, , MUIMASTER_BASE_NAME)
#define MUI_AslRequest(req,tags) LP2(0x36, BOOL, MUI_AslRequest, APTR, req, a0, struct TagItem *, tags, a1, , MUIMASTER_BASE_NAME)
#define MUI_FreeAslRequest(req) LP1NR(0x3c, MUI_FreeAslRequest, APTR, req, a0, , MUIMASTER_BASE_NAME)
#define MUI_Error() LP0(0x42, LONG, MUI_Error, , MUIMASTER_BASE_NAME)
#define MUI_SetError(num) LP1(0x48, LONG, MUI_SetError, LONG, num, d0, , MUIMASTER_BASE_NAME)
#define MUI_GetClass(classname) LP1(0x4e, struct IClass *, MUI_GetClass, CONST_STRPTR, classname, a0, , MUIMASTER_BASE_NAME)
#define MUI_FreeClass(cl) LP1NR(0x54, MUI_FreeClass, struct IClass *, cl, a0, , MUIMASTER_BASE_NAME)
#define MUI_RequestIDCMP(obj,flags) LP2NR(0x5a, MUI_RequestIDCMP, Object *, obj, a0, ULONG, flags, d0, , MUIMASTER_BASE_NAME)
#define MUI_RejectIDCMP(obj,flags) LP2NR(0x60, MUI_RejectIDCMP, Object *, obj, a0, ULONG, flags, d0, , MUIMASTER_BASE_NAME)
#define MUI_Redraw(obj,flags) LP2NR(0x66, MUI_Redraw, Object *, obj, a0, ULONG, flags, d0, , MUIMASTER_BASE_NAME)
#define MUI_CreateCustomClass(base,supername,supermcc,datasize,dispatcher) LP5(0x6c, struct MUI_CustomClass *, MUI_CreateCustomClass, struct Library *, base, a0, CONST_STRPTR, supername, a1, struct MUI_CustomClass *, supermcc, a2, LONG, datasize, d0, APTR, dispatcher, a3, , MUIMASTER_BASE_NAME)
#define MUI_DeleteCustomClass(mcc) LP1(0x72, BOOL, MUI_DeleteCustomClass, struct MUI_CustomClass *, mcc, a0, , MUIMASTER_BASE_NAME)
#define MUI_MakeObjectA(type,params) LP2(0x78, Object *, MUI_MakeObjectA, LONG, type, d0, IPTR *, params, a0, , MUIMASTER_BASE_NAME)
#define MUI_Layout(obj,left,top,width,height,flags) LP6(0x7e, BOOL, MUI_Layout, Object *, obj, a0, LONG, left, d0, LONG, top, d1, LONG, width, d2, LONG, height, d3, ULONG, flags, d4, , MUIMASTER_BASE_NAME)

#endif
