/* The CPU cores board's native jobs, from the Open SDK.
 *
 * Loads a job built for the host (job.c, built as job.x86_64.bin and
 * job.arm64.bin) and runs it on a core of the board through mitchy.library:
 * cpu.arm64/1 on a Pi 5, cpu.x86_64/1 on a PC. The job adds up COUNT longs
 * and writes the running totals; the program checks every one of them
 * against the same sum done here on the 68k.
 *
 * With no board, or a host that does not offer native jobs (the host's
 * AC_NATIVE=1), it does the work on the 68k alone: a real program always
 * has that way too.
 *
 *   CoresNativeJob [COUNT=<longs>] [DIR=<where the .bin files are>]
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence: your own
 * program built from it is yours to licence as you like. */
#include <exec/types.h>
#include <exec/memory.h>
#include <exec/libraries.h>
#include <dos/dos.h>
#include <libraries/mitchy.h>
#include <hardware/coresboard.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/mitchy.h>
#include <string.h>

static const char version[] __attribute__((used)) = "$VER: CoresNativeJob 1.0 (18.11.2026)";

struct Library *MitchyBase;

/* The job's bytes, from DIR/job.<isa>.bin. */
static UBYTE *load_job(CONST_STRPTR dir, CONST_STRPTR isa, ULONG *len)
{
    char path[256];
    BPTR fh;
    LONG size;
    UBYTE *code = NULL;
    struct FileInfoBlock *fib;

    path[0] = 0;
    if (dir)
        strncpy(path, (const char *)dir, sizeof path - 32);
    path[sizeof path - 32] = 0;
    AddPart((STRPTR)path, (CONST_STRPTR)"job.", sizeof path);
    strcat(path, (const char *)isa);
    strcat(path, ".bin");
    fh = Open((CONST_STRPTR)path, MODE_OLDFILE);
    if (!fh) {
        Printf((CONST_STRPTR)"no %s\n", (LONG)path);
        return NULL;
    }
    fib = AllocDosObject(DOS_FIB, NULL);
    if (fib && ExamineFH(fh, fib) && (size = fib->fib_Size) > 0) {
        code = AllocVec((ULONG)size, MEMF_ANY);
        if (code && Read(fh, code, size) != size) {
            FreeVec(code);
            code = NULL;
        }
        *len = (ULONG)size;
    }
    if (fib)
        FreeDosObject(DOS_FIB, fib);
    Close(fh);
    return code;
}

int main(void)
{
    LONG args[2] = { 0, 0 };
    struct RDArgs *rd;
    ULONG count = 100000, i, codelen = 0;
    ULONG *in = NULL, *out = NULL, sumhi = 0, sumlo = 0;
    UBYTE *code = NULL;
    struct MitchyService *service = NULL;
    struct MitchyRequest *req = NULL;
    const char *name = NULL, *isa = NULL;
    LONG error = 0, status;
    int rc = RETURN_FAIL;

    rd = ReadArgs((CONST_STRPTR)"COUNT/N,DIR", args, NULL);
    if (!rd) {
        PrintFault(IoErr(), (CONST_STRPTR)"CoresNativeJob");
        return RETURN_FAIL;
    }
    if (args[0] && *(LONG *)args[0] > 0)
        count = (ULONG)*(LONG *)args[0];
    in = AllocVec(count * 4, MEMF_ANY);
    out = AllocVec(count * 4, MEMF_ANY | MEMF_CLEAR);
    if (!in || !out) {
        Printf((CONST_STRPTR)"no memory for %lu longs\n", count);
        goto out;
    }
    for (i = 0; i < count; i++)
        in[i] = i * 2654435761UL;               /* anything that carries */

    /* The 68k's own answer: the fallback, and the check. */
    for (i = 0; i < count; i++) {
        ULONG lo = sumlo + in[i];
        sumhi += lo < sumlo;
        sumlo = lo;
    }

    MitchyBase = OpenLibrary((CONST_STRPTR)MITCHYNAME, MITCHYVERSION);
    if (MitchyBase) {
        /* An ARM64 host first (a Pi 5), then an x86-64 one. */
        name = "cpu.arm64/1"; isa = "arm64";
        service = MitchyOpen((CONST_STRPTR)name, 0, &error);
        if (!service) {
            name = "cpu.x86_64/1"; isa = "x86_64";
            service = MitchyOpen((CONST_STRPTR)name, 0, &error);
        }
    }
    if (!service) {
        Printf((CONST_STRPTR)"no native cores here: the 68k did it, sum $%08lx%08lx\n", sumhi, sumlo);
        rc = RETURN_OK;
        goto out;
    }
    code = load_job((CONST_STRPTR)args[1], (CONST_STRPTR)isa, &codelen);
    req = code ? MitchyAllocRequest(service, NULL) : NULL;
    if (!req)
        goto out;

    req->mr_Op = CORES_OP_RUN;
    req->mr_Flags = CORESF_WRITTEN(2) | CORESF_TIMEOUT(5000);
    req->mr_Arg = 0;                            /* the entry: the first byte of the code */
    req->mr_Buf[0].mb_Data = code;              /* buffer 0: the code */
    req->mr_Buf[0].mb_Length = codelen;
    req->mr_Buf[1].mb_Data = in;                /* the job's buf[0] */
    req->mr_Buf[1].mb_Length = count * 4;
    req->mr_Buf[2].mb_Data = out;               /* its buf[1], written */
    req->mr_Buf[2].mb_Length = count * 4;
    status = MitchyDoRequest(req);
    if (status != MITCHY_OK) {
        Printf((CONST_STRPTR)"%s: status %ld (result %lu)\n", (LONG)name, status, req->mr_Result);
        rc = RETURN_ERROR;
        goto out;
    }
    {
        ULONG lo = 0, bad = 0;
        for (i = 0; i < count; i++) {
            lo += in[i];
            if (out[i] != lo)
                bad++;
        }
        Printf((CONST_STRPTR)"%s: sum $%08lx%08lx, the 68k's $%08lx%08lx; %lu of %lu totals differ\n", (LONG)name,
               req->mr_Aux, req->mr_Result, sumhi, sumlo, bad, count);
        rc = req->mr_Result == sumlo && req->mr_Aux == sumhi && !bad ? RETURN_OK : RETURN_ERROR;
    }

out:
    if (req)
        MitchyFreeRequest(req);
    if (service)
        MitchyClose(service);
    if (MitchyBase)
        CloseLibrary(MitchyBase);
    if (code)
        FreeVec(code);
    if (in)
        FreeVec(in);
    if (out)
        FreeVec(out);
    FreeArgs(rd);
    return rc;
}
