/* The Open SDK's AROS compatibility: amiga.lib calls AROS adds.
 *  - StrDup: a copy of a string in AllocVec memory (FreeVec frees it), NULL for NULL or no memory.
 *  - DoSuperNewTags: OM_NEW to the superclass with the tags that follow.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#include <exec/types.h>
#include <exec/memory.h>
#include <intuition/classes.h>
#include <intuition/classusr.h>
#include <utility/tagitem.h>
#include <proto/exec.h>
#include <clib/alib_protos.h>
#include <string.h>
#include <proto/alib.h>

STRPTR StrDup(CONST_STRPTR str)
{
    ULONG n;
    STRPTR copy;
    if (!str) return NULL;
    n = strlen((const char *)str) + 1;
    copy = (STRPTR)AllocVec(n, MEMF_ANY);
    if (copy) CopyMem((APTR)str, copy, n);
    return copy;
}

IPTR DoSuperNewTags(struct IClass *cl, Object *obj, APTR gadgetinfo, Tag tag1, ...)
{
    /* on the 68k the tags that follow are on the stack in order: a tag list */
    struct opSet msg;
    msg.MethodID = OM_NEW;
    msg.ops_AttrList = (struct TagItem *)&tag1;
    msg.ops_GInfo = (struct GadgetInfo *)gadgetinfo;
    return DoSuperMethodA(cl, obj, (Msg)&msg);
}
