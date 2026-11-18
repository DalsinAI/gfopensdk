/* Made by hand from MUI's published muimaster_lib.fd (offsets and registers).
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef CLIB_MUIMASTER_PROTOS_H
#define CLIB_MUIMASTER_PROTOS_H
#include <libraries/mui.h>

Object * MUI_NewObjectA(CONST_STRPTR classname, struct TagItem *tags);
VOID MUI_DisposeObject(Object *obj);
LONG MUI_RequestA(APTR app, APTR win, ULONG flags, CONST_STRPTR title, CONST_STRPTR gadgets, CONST_STRPTR format, APTR params);
APTR MUI_AllocAslRequest(ULONG type, struct TagItem *tags);
BOOL MUI_AslRequest(APTR req, struct TagItem *tags);
VOID MUI_FreeAslRequest(APTR req);
LONG MUI_Error(VOID);
LONG MUI_SetError(LONG num);
struct IClass * MUI_GetClass(CONST_STRPTR classname);
VOID MUI_FreeClass(struct IClass *cl);
VOID MUI_RequestIDCMP(Object *obj, ULONG flags);
VOID MUI_RejectIDCMP(Object *obj, ULONG flags);
VOID MUI_Redraw(Object *obj, ULONG flags);
struct MUI_CustomClass * MUI_CreateCustomClass(struct Library *base, CONST_STRPTR supername, struct MUI_CustomClass *supermcc, LONG datasize, APTR dispatcher);
BOOL MUI_DeleteCustomClass(struct MUI_CustomClass *mcc);
Object * MUI_MakeObjectA(LONG type, IPTR *params);
BOOL MUI_Layout(Object *obj, LONG left, LONG top, LONG width, LONG height, ULONG flags);

/* the varargs forms (libmuimaster.a) */
Object *MUI_NewObject(CONST_STRPTR classname, ...);
Object *MUI_MakeObject(LONG type, ...);
LONG MUI_Request(APTR app, APTR win, ULONG flags, CONST_STRPTR title, CONST_STRPTR gadgets, CONST_STRPTR format, ...);
APTR MUI_AllocAslRequestTags(ULONG type, ...);
BOOL MUI_AslRequestTags(APTR req, ...);

#endif
