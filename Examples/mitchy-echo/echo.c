/* mitchy.library from the Open SDK: open a service by name and call it.
 *
 * Lists the services this machine can reach (a Mitchy card, another ACSV
 * board, or a paired Cradle on the LAN), opens one by name and version
 * (echo/1 unless you give another), says where it runs, then sends it a
 * buffer and checks what comes back. echo/1 copies buffer 0 into buffer 1
 * (operation 1) and answers the bytes it wrote, so the answer must equal
 * the question.
 *
 *   MitchyEcho [NAME=<service>] [TEXT=<text>]
 *
 * With no board and no paired Cradle, MitchyOpen fails and says why
 * (MitchyStatusText): a real program then does the work itself on the 68k.
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence: your own
 * program built from it is yours to licence as you like. */
#include <exec/types.h>
#include <exec/libraries.h>
#include <dos/dos.h>
#include <libraries/mitchy.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/mitchy.h>

static const char version[] __attribute__((used)) = "$VER: MitchyEcho 1.0 (9.11.2026)";

struct Library *MitchyBase;

#define ECHO_OP 1                   /* echo/1: buffer 0 into buffer 1 */

static ULONG length(const char *s)
{
    ULONG n = 0;
    while (s[n])
        n++;
    return n;
}

static BOOL same(const char *a, const char *b, ULONG n)
{
    while (n--)
        if (*a++ != *b++)
            return FALSE;
    return TRUE;
}

int main(void)
{
    LONG args[2] = { 0, 0 };
    struct RDArgs *rd;
    const char *name, *text;
    static char list[512], answer[256];
    struct MitchyService *service;
    struct MitchyRequest *req;
    CONST_STRPTR why;
    LONG error = 0, status, n, i;
    ULONG len;
    const char *where;
    int rc = RETURN_FAIL;

    rd = ReadArgs((CONST_STRPTR)"NAME,TEXT", args, NULL);
    if (!rd) {
        PrintFault(IoErr(), (CONST_STRPTR)"MitchyEcho");
        return RETURN_FAIL;
    }
    name = args[0] ? (const char *)args[0] : "echo/1";
    text = args[1] ? (const char *)args[1] : "Hello from the 68k";
    len = length(text);
    if (len > sizeof answer - 1)
        len = sizeof answer - 1;

    MitchyBase = OpenLibrary((CONST_STRPTR)MITCHYNAME, MITCHYVERSION);
    if (!MitchyBase) {
        Printf((CONST_STRPTR)"no %s %ld\n", (LONG)MITCHYNAME, (LONG)MITCHYVERSION);
        FreeArgs(rd);
        return RETURN_FAIL;
    }

    /* Every service on offer, a NUL after each name. */
    n = MitchyList((STRPTR)list, sizeof list);
    Printf((CONST_STRPTR)"services:");
    for (i = 0; i < n && i < (LONG)sizeof list && list[i]; i += (LONG)length(list + i) + 1)
        Printf((CONST_STRPTR)" %s", (LONG)(list + i));
    Printf((CONST_STRPTR)"\n");

    service = MitchyOpen((CONST_STRPTR)name, 0, &error);
    if (!service) {
        /* one library call at a time: never nest one inside another's arguments */
        why = MitchyStatusText(error);
        Printf((CONST_STRPTR)"%s: %s (%ld)\n", (LONG)name, (LONG)why, error);
        rc = RETURN_WARN;
        goto out;
    }
    status = MitchyWhere(service);
    where = status == MITCHY_WHERE_BOARD ? "a board in this machine"
          : status == MITCHY_WHERE_LAN ? "a paired Cradle on the LAN" : "?";
    Printf((CONST_STRPTR)"%s: open, on %s\n", (LONG)name, (LONG)where);

    req = MitchyAllocRequest(service, NULL);    /* no port: wait on its signal */
    if (!req) {
        Printf((CONST_STRPTR)"no request\n");
        goto close;
    }
    req->mr_Op = ECHO_OP;
    req->mr_Flags = MBF_BUF1;                   /* the service writes buffer 1 */
    req->mr_Buf[0].mb_Data = (APTR)text;
    req->mr_Buf[0].mb_Length = len;
    req->mr_Buf[1].mb_Data = answer;
    req->mr_Buf[1].mb_Length = sizeof answer - 1;
    status = MitchyDoRequest(req);
    if (status == MITCHY_OK) {
        BOOL ok = req->mr_Result == len && same(text, answer, len);
        answer[req->mr_Result < sizeof answer ? req->mr_Result : sizeof answer - 1] = 0;
        Printf((CONST_STRPTR)"sent \"%s\", got \"%s\" (%lu bytes): %s\n", (LONG)text, (LONG)answer,
               req->mr_Result, (LONG)(ok ? "the same" : "DIFFERENT"));
        rc = ok ? RETURN_OK : RETURN_ERROR;
    } else {
        why = MitchyStatusText(status);
        Printf((CONST_STRPTR)"%s: %s (%ld)\n", (LONG)name, (LONG)why, status);
        rc = RETURN_ERROR;
    }
    MitchyFreeRequest(req);
close:
    MitchyClose(service);
out:
    CloseLibrary(MitchyBase);
    FreeArgs(rd);
    return rc;
}
