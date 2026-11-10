/* aroscompat-hello: an AROS-style Shell command built for AmigaOS 3.x with
 * the Open SDK's AROS compatibility (Docs/PORTING-AROS.md). It uses the
 * AROS forms a ported program meets: AROS_SH2 with SHArg, a hook made with
 * AROS_UFH3 and called with its registers (AROS_UFC3), library calls by
 * their offsets (AROS_LC2, AROS_LC1NR), ForeachNode, the byte-order macros, IPTR
 * and ADD2INIT/ADD2EXIT with static functions.
 *   AROSHello [NAME] [TIMES=n]
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#include <exec/types.h>
#include <exec/lists.h>
#include <exec/memory.h>
#include <utility/hooks.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <aros/shcommands.h>
#include <aros/asmcall.h>
#include <aros/libcall.h>
#include <aros/macros.h>
#include <aros/debug.h>
#include <aros/symbolsets.h>

/* ADD2INIT/ADD2EXIT with static functions, as AROS programs use them */
static LONG set_ran;
static BOOL set_init(void) { set_ran = 1; return TRUE; }
static void set_exit(void) { PutStr("sets exit\n"); }
ADD2INIT(set_init, 90);
ADD2EXIT(set_exit, 90);

AROS_UFH3(IPTR, count_hook,
          AROS_UFHA(struct Hook *, hook, A0),
          AROS_UFHA(APTR, object, A2),
          AROS_UFHA(APTR, message, A1))
{
    AROS_USERFUNC_INIT
    (void)object;
    (void)message;
    hook->h_Data = (APTR)((IPTR)hook->h_Data + 1);
    return (IPTR)hook->h_Data;
    AROS_USERFUNC_EXIT
}

AROS_SH2(AROSHello, 1.0,
AROS_SHA(STRPTR, ,NAME, ,"Amiga"),
AROS_SHA(LONG *, ,TIMES,/K/N,NULL))
{
    AROS_SHCOMMAND_INIT
    struct Hook hook;
    struct List list;
    struct Node nodes[3], *n;
    LONG times = SHArg(TIMES) ? *SHArg(TIMES) : 1, i, seen = 0;
    ULONG be = AROS_LONG2BE(0x11223344), le = AROS_LONG2LE(0x11223344);
    APTR mem;

    hook.h_Entry = (HOOKFUNC)(void *)count_hook;
    hook.h_Data = (APTR)0;
    for (i = 0; i < times; i++) {
        Printf("Hello, %s\n", (IPTR)SHArg(NAME));
        AROS_UFC3(IPTR, hook.h_Entry, AROS_UFCA(struct Hook *, &hook, A0),
                  AROS_UFCA(APTR, NULL, A2), AROS_UFCA(APTR, NULL, A1));
    }
    NEWLIST(&list);
    for (i = 0; i < 3; i++) AddTail(&list, &nodes[i]);
    ForeachNode(&list, n) seen++;
    /* exec's AllocVec (offset 114) and FreeVec (115) called by their offsets */
    mem = AROS_LC2(APTR, AllocVec, AROS_LCA(ULONG, 64, D0), AROS_LCA(ULONG, MEMF_CLEAR, D1),
                   struct ExecBase *, SysBase, 114, Exec);
    AROS_LC1NR(void, FreeVec, AROS_LCA(APTR, mem, A1), struct ExecBase *, SysBase, 115, Exec);
    Printf("hook %ld, list %ld, LONG2BE %08lx, LONG2LE %08lx, memory %s\n",
           (IPTR)hook.h_Data, seen, be, le, (IPTR)(mem ? "ok" : "none"));
    Printf("sets init %ld\n", set_ran);
    D(bug("not printed: DEBUG is 0\n"));
    return (IPTR)hook.h_Data == (IPTR)times && seen == 3 && mem ? RETURN_OK : RETURN_FAIL;
    AROS_SHCOMMAND_EXIT
}
