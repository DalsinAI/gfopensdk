#ifndef INTUITION_CLASSUSR_H
#define INTUITION_CLASSUSR_H
/*
 * OpenNDK: BOOPSI as a program sees it: objects, the built-in class
 * names and rootclass's methods.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif

/* An object is only ever handled by pointer */
typedef ULONG Object;

/* A class's public name */
typedef UBYTE *ClassID;

/* Every method's message starts with its method ID */
typedef struct
{
    ULONG MethodID;
} *Msg;

/* The classes built into Intuition */
#define ROOTCLASS	"rootclass"
#define IMAGECLASS	"imageclass"
#define FRAMEICLASS	"frameiclass"
#define SYSICLASS	"sysiclass"
#define FILLRECTCLASS	"fillrectclass"
#define GADGETCLASS	"gadgetclass"
#define PROPGCLASS	"propgclass"
#define STRGCLASS	"strgclass"
#define BUTTONGCLASS	"buttongclass"
#define FRBUTTONCLASS	"frbuttonclass"
#define GROUPGCLASS	"groupgclass"
#define ICCLASS		"icclass"
#define MODELCLASS	"modelclass"
#define ITEXTICLASS	"itexticlass"
#define POINTERCLASS	"pointerclass"	/* V39 */

/* rootclass's methods */
#define OM_Dummy	(0x100)
#define OM_NEW		(0x101)
#define OM_DISPOSE	(0x102)
#define OM_SET		(0x103)
#define OM_GET		(0x104)
#define OM_ADDTAIL	(0x105)
#define OM_REMOVE	(0x106)
#define OM_NOTIFY	(0x107)
#define OM_UPDATE	(0x108)
#define OM_ADDMEMBER	(0x109)
#define OM_REMMEMBER	(0x10A)

/* OM_NEW and OM_SET */
struct opSet
{
    ULONG MethodID;
    struct TagItem *ops_AttrList;
    struct GadgetInfo *ops_GInfo;	/* NULL for OM_NEW */
};

/* OM_NOTIFY and OM_UPDATE */
struct opUpdate
{
    ULONG MethodID;
    struct TagItem *opu_AttrList;
    struct GadgetInfo *opu_GInfo;
    ULONG opu_Flags;
};

/* opu_Flags */
#define OPUF_INTERIM	(1 << 0)	/* more updates follow */

/* OM_GET */
struct opGet
{
    ULONG MethodID;
    ULONG opg_AttrID;
    ULONG *opg_Storage;
};

/* OM_ADDTAIL */
struct opAddTail
{
    ULONG MethodID;
    struct List *opat_List;
};

/* OM_ADDMEMBER and OM_REMMEMBER */
struct opMember
{
    ULONG MethodID;
    Object *opam_Object;
};
#define opAddMember opMember

#endif /* INTUITION_CLASSUSR_H */
