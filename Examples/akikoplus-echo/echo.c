/* akikoplus.library 3 from the Open SDK: a named service through AkikoPlus.
 *
 * Opens a service by name and version (echo/1 unless you give another) with
 * AP_OpenService: on the AkikoPlus board when it is fitted, else on Mitchy or
 * a paired Cradle on the LAN. Says where it runs, then calls it twice: once
 * waited for (AP_CallService) and once as a read-ahead (AP_SendService on a
 * port of its own, then AP_WaitService), checking each answer. echo/1 copies
 * buffer 0 into buffer 1 (operation 1) and answers the bytes it wrote. This
 * is how the GFOpen datatypes reach media.decode/1.
 *
 *   AkikoEcho [NAME=<service>] [TEXT=<text>]
 *
 * Without akikoplus.library 3, or with no board and no paired Cradle, it says
 * why: a real program then takes its next way in or does the work on the 68k.
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence: your own
 * program built from it is yours to licence as you like. */
#include <exec/types.h>
#include <exec/libraries.h>
#include <exec/ports.h>
#include <dos/dos.h>
#include <libraries/akikoplus.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/akikoplus.h>

static const char version[] __attribute__((used)) = "$VER: AkikoEcho 1.0 (24.11.2026)";

struct Library *AkikoPlusBase;

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

static void fill(struct APServiceCall *c, const char *text, ULONG len, char *answer)
{
    int i;
    c->asc_Op = ECHO_OP;
    c->asc_Pad = 0;
    c->asc_Flags = APSF_WRITTEN(1);
    c->asc_Arg = 0;
    for (i = 0; i < 4; i++) {
        c->asc_Buf[i].ab_Data = NULL;
        c->asc_Buf[i].ab_Length = 0;
        c->asc_Extra[i] = 0;
    }
    c->asc_Buf[0].ab_Data = (APTR)text;
    c->asc_Buf[0].ab_Length = len;
    c->asc_Buf[1].ab_Data = answer;
    c->asc_Buf[1].ab_Length = len;
}

int main(void)
{
    LONG args[2] = { 0, 0 };
    struct RDArgs *rd;
    const char *name, *text;
    static char answer[256];
    struct APServiceCall call;
    struct MsgPort *port;
    APTR service, req;
    ULONG ra[2], len;
    LONG error = 0, status, where, i;
    int rc = RETURN_FAIL;

    rd = ReadArgs((CONST_STRPTR)"NAME,TEXT", args, NULL);
    if (!rd) {
        PrintFault(IoErr(), (CONST_STRPTR)"AkikoEcho");
        return RETURN_FAIL;
    }
    name = args[0] ? (const char *)args[0] : "echo/1";
    text = args[1] ? (const char *)args[1] : "Hello from the 68k";
    len = length(text);
    if (len > sizeof answer - 1)
        len = sizeof answer - 1;

    AkikoPlusBase = OpenLibrary((CONST_STRPTR)AKIKOPLUS_NAME, AKIKOPLUS_SERVICES_VERSION);
    if (!AkikoPlusBase) {
        Printf((CONST_STRPTR)"no %s %ld\n", (LONG)AKIKOPLUS_NAME, (LONG)AKIKOPLUS_SERVICES_VERSION);
        FreeArgs(rd);
        return RETURN_FAIL;
    }
    service = AP_OpenService((CONST_STRPTR)name, 0, &error);
    if (!service) {
        Printf((CONST_STRPTR)"%s: not opened (%ld%s)\n", (LONG)name, error,
               (LONG)(error == APSERR_NOMITCHY ? ", no mitchy.library" : error == APSERR_NOTFITTED ? ", no board or Cradle" : ""));
        goto out;
    }
    where = AP_ServiceWhere(service);
    Printf((CONST_STRPTR)"%s runs %s\n", (LONG)name,
           (LONG)(where == AP_WHERE_BOARD ? "on a board in this machine" : where == AP_WHERE_LAN ? "on a paired Cradle" : "nowhere"));

    /* Once, waited for. */
    for (i = 0; i < (LONG)len; i++)
        answer[i] = 0;
    fill(&call, text, len, answer);
    status = AP_CallService(service, &call, ra);
    if (status != APS_OK || ra[0] != len || !same(text, answer, len)) {
        Printf((CONST_STRPTR)"AP_CallService: status %ld, %ld bytes back\n", status, (LONG)ra[0]);
        goto close;
    }
    Printf((CONST_STRPTR)"AP_CallService: %ld bytes back, the same\n", (LONG)ra[0]);

    /* Again as a read-ahead: sent, then taken. */
    for (i = 0; i < (LONG)len; i++)
        answer[i] = 0;
    if (!(port = CreateMsgPort())) {
        Printf((CONST_STRPTR)"no port\n");
        goto close;
    }
    if (!(req = AP_SendService(service, &call, port))) {
        Printf((CONST_STRPTR)"AP_SendService: not sent\n");
        DeleteMsgPort(port);
        goto close;
    }
    status = AP_WaitService(req, ra);
    DeleteMsgPort(port);
    if (status != APS_OK || ra[0] != len || !same(text, answer, len)) {
        Printf((CONST_STRPTR)"AP_SendService + AP_WaitService: status %ld, %ld bytes back\n", status, (LONG)ra[0]);
        goto close;
    }
    Printf((CONST_STRPTR)"AP_SendService + AP_WaitService: %ld bytes back, the same\n", (LONG)ra[0]);
    rc = RETURN_OK;
close:
    AP_CloseService(service);
out:
    CloseLibrary(AkikoPlusBase);
    FreeArgs(rd);
    return rc;
}
