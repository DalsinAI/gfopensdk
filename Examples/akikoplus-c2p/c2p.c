/* akikoplus.library from the Open SDK: chunky to planar (AP_C2P).
 *
 * Makes a 320 x 200 chunky picture of 8-bit pens (diagonal bands), turns it
 * into 8 bitplanes with AP_C2P, and checks every byte against a plain C
 * conversion done here. AkikoPlus does it on the board when one is fitted
 * and the job is big enough (AP_SetThreshold); otherwise the library does it
 * on the 68k: the same bytes either way. AP_Query(APQ_LASTRAN) says which.
 *
 *   AkikoC2P [MODE=AUTO|68K|BOARD] [DEPTH=<1-8>]
 *
 * The planes are in one block, plane after plane (ap_PlaneStride), each
 * row 40 bytes (ap_RowStride): the layout of a BitMap allocated with
 * AllocBitMap(320, 200, depth, 0, NULL) when it isn't interleaved, so
 * bm->Planes[0] and bm->BytesPerRow give the two strides of a real screen.
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence: your own
 * program built from it is yours to licence as you like. */
#include <exec/types.h>
#include <exec/memory.h>
#include <exec/libraries.h>
#include <dos/dos.h>
#include <libraries/akikoplus.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/akikoplus.h>

static const char version[] __attribute__((used)) = "$VER: AkikoC2P 1.0 (9.11.2026)";

struct Library *AkikoPlusBase;

#define W 320
#define H 200
#define ROW (W / 8)

/* Pixel x of a row is bit 7 - (x & 7) of byte x / 8, in every plane. */
static void c2p_reference(const UBYTE *chunky, UBYTE *planes, UWORD depth)
{
    ULONG x, y, p;
    for (p = 0; p < depth; p++)
        for (y = 0; y < H; y++)
            for (x = 0; x < W; x += 8) {
                UBYTE b = 0;
                ULONG k;
                for (k = 0; k < 8; k++)
                    b = (UBYTE)((b << 1) | ((chunky[y * W + x + k] >> p) & 1));
                planes[p * ROW * H + y * ROW + x / 8] = b;
            }
}

static ULONG mode_of(const char *s)
{
    if (!s)
        return APMODE_AUTO;
    if ((s[0] | 0x20) == 'b')
        return APMODE_BOARD;
    if (s[0] == '6')
        return APMODE_68K;
    return APMODE_AUTO;
}

int main(void)
{
    LONG args[2] = { 0, 0 };
    struct RDArgs *rd;
    UBYTE *chunky = NULL, *planes = NULL, *check = NULL;
    struct APC2P c2p;
    ULONG status, x, y, bad = 0, size;
    LONG err, ran;
    UWORD depth = 8;
    int rc = RETURN_FAIL;

    rd = ReadArgs((CONST_STRPTR)"MODE/K,DEPTH/K/N", args, NULL);
    if (!rd) {
        PrintFault(IoErr(), (CONST_STRPTR)"AkikoC2P");
        return RETURN_FAIL;
    }
    if (args[1] && *(LONG *)args[1] >= 1 && *(LONG *)args[1] <= 8)
        depth = (UWORD)*(LONG *)args[1];
    size = (ULONG)ROW * H * depth;

    AkikoPlusBase = OpenLibrary((CONST_STRPTR)AKIKOPLUS_NAME, AKIKOPLUS_VERSION);
    if (!AkikoPlusBase) {
        Printf((CONST_STRPTR)"no %s %ld\n", (LONG)AKIKOPLUS_NAME, (LONG)AKIKOPLUS_VERSION);
        goto out;
    }
    status = AP_Status();
    Printf((CONST_STRPTR)"akikoplus.library %ld.%ld: %s\n", (LONG)AkikoPlusBase->lib_Version,
           (LONG)AkikoPlusBase->lib_Revision,
           (LONG)((status & APSF_BOARD) ? "the board's services are open" : "no board: the 68k does the work"));
    AP_SetMode(mode_of((const char *)args[0]));

    chunky = AllocVec(W * H, MEMF_ANY);
    planes = AllocVec(size, MEMF_ANY | MEMF_CLEAR);
    check = AllocVec(size, MEMF_ANY | MEMF_CLEAR);
    if (!chunky || !planes || !check) {
        Printf((CONST_STRPTR)"no memory\n");
        goto out;
    }
    for (y = 0; y < H; y++)
        for (x = 0; x < W; x++)
            chunky[y * W + x] = (UBYTE)((x + y) >> 1);

    c2p.ap_Chunky = chunky;
    c2p.ap_Planes = planes;
    c2p.ap_ChunkyLen = W * H;
    c2p.ap_PlanesLen = size;
    c2p.ap_Width = W;
    c2p.ap_Height = H;
    c2p.ap_Depth = depth;
    c2p.ap_Pad = 0;
    c2p.ap_ChunkyPitch = W;
    c2p.ap_RowStride = ROW;
    c2p.ap_PlaneStride = (ULONG)ROW * H;
    err = AP_C2P(&c2p);
    ran = AP_Query(APQ_LASTRAN);
    if (err < 0) {
        Printf((CONST_STRPTR)"AP_C2P: error %ld\n", err);
        goto out;
    }

    c2p_reference(chunky, check, depth);
    for (x = 0; x < size; x++)
        if (planes[x] != check[x])
            bad++;
    Printf((CONST_STRPTR)"%ld x %ld, %ld planes, on %s: %s (%lu bytes differ)\n", (LONG)W, (LONG)H,
           (LONG)depth, (LONG)(ran == 1 ? "the board" : ran == 0 ? "the 68k" : "?"),
           (LONG)(bad ? "WRONG" : "right"), bad);
    rc = bad ? RETURN_ERROR : RETURN_OK;
out:
    if (check)
        FreeVec(check);
    if (planes)
        FreeVec(planes);
    if (chunky)
        FreeVec(chunky);
    if (AkikoPlusBase)
        CloseLibrary(AkikoPlusBase);
    FreeArgs(rd);
    return rc;
}
