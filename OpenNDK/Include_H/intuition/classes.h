#ifndef INTUITION_CLASSES_H
#define INTUITION_CLASSES_H
/*
 * OpenNDK: BOOPSI classes and objects as Intuition keeps them.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef INTUITION_CLASSUSR_H
#include <intuition/classusr.h>
#endif

/* A class. Only the class's own code looks inside. */
typedef struct IClass
{
    struct Hook cl_Dispatcher;
    ULONG cl_Reserved;			/* must be 0 */
    struct IClass *cl_Super;
    ClassID cl_ID;

    UWORD cl_InstOffset;		/* this class's data in an object */
    UWORD cl_InstSize;

    ULONG cl_UserData;			/* the class's own */
    ULONG cl_SubclassCount;
    ULONG cl_ObjectCount;
    ULONG cl_Flags;
} Class;

/* cl_Flags */
#define CLF_INLIST	0x00000001	/* AddClass() has made it public */

/* The address of class cl's data in object o */
#define INST_DATA(cl, o)	((VOID *)(((UBYTE *)(o)) + (cl)->cl_InstOffset))

/* Bytes an object of class cl takes, its header included */
#define SIZEOF_INSTANCE(cl) \
    ((cl)->cl_InstOffset + (cl)->cl_InstSize + sizeof(struct _Object))

/* The header in front of every object; an Object * points just past it */
struct _Object
{
    struct MinNode o_Node;
    struct IClass *o_Class;
};

#define _OBJ(o)		((struct _Object *)(o))
#define BASEOBJECT(_obj) ((Object *)(_OBJ(_obj) + 1))
#define _OBJECT(o)	(_OBJ(o) - 1)
#define OCLASS(o)	((_OBJECT(o))->o_Class)

/* The base of a class held in its own library */
struct ClassLibrary
{
    struct Library cl_Lib;
    UWORD cl_Pad;
    Class *cl_Class;
};

#endif /* INTUITION_CLASSES_H */
