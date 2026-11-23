/*
 * The Open SDK: a picture opened from memory through the datatypes
 * (DTST_MEMORY), with the fallback to a file in T:. A Shell command:
 *
 *     DTMemInfo PICTURE
 *
 * reads PICTURE into memory, as a browser holds a download, and prints its
 * size in pixels and which way it was opened. The rule and whose bytes they
 * are: Docs/datatypes-memory.md.
 * MIT, Copyright (c) 2026 AmiCradle Team.
 */
#include <exec/types.h>
#include <exec/memory.h>
#include <exec/libraries.h>
#include <dos/dos.h>
#include <intuition/classusr.h>
#include <graphics/gfx.h>
#include <datatypes/datatypes.h>
#include <datatypes/datatypesclass.h>
#include <datatypes/pictureclass.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/datatypes.h>

#include "dtmemory.h"

/* OS 3.2's NDK has no numbers for these; the Open SDK's headers do */
#ifndef DTST_MEMORY
#define DTST_MEMORY 5
#endif
#ifndef DTA_SourceAddress
#define DTA_SourceAddress (DTA_Dummy + 39)
#define DTA_SourceSize    (DTA_Dummy + 40)
#endif

struct Library *DataTypesBase;

/* the whole file in memory, or NULL with the reason in IoErr() */
static UBYTE *read_file(CONST_STRPTR name, ULONG *size)
{
    UBYTE *bytes = NULL;
    BPTR fh = Open(name, MODE_OLDFILE);
    if (fh) {
        LONG len;
        Seek(fh, 0, OFFSET_END);
        len = Seek(fh, 0, OFFSET_BEGINNING);
        if (len > 0 && (bytes = AllocVec((ULONG)len, MEMF_ANY)) != NULL) {
            if (Read(fh, bytes, len) != len) {
                FreeVec(bytes);
                bytes = NULL;
            } else
                *size = (ULONG)len;
        } else if (len <= 0)
            SetIoErr(ERROR_OBJECT_WRONG_TYPE);
        Close(fh);
    }
    return bytes;
}

/* a picture object on the bytes: from memory where datatypes.library has the
 * source and the class takes it, otherwise through a file in T:. *temp is
 * set when the file was made; the caller deletes it after DisposeDTObject(). */
static Object *picture_from_bytes(UBYTE *bytes, ULONG size, CONST_STRPTR temp_name, BOOL *temp)
{
    Object *o = NULL;
    *temp = FALSE;
    if (dt_memory_source_ok(DataTypesBase->lib_Version, DataTypesBase->lib_Revision))
        o = NewDTObject(NULL,
                        DTA_SourceType, DTST_MEMORY,
                        DTA_SourceAddress, (ULONG)bytes,
                        DTA_SourceSize, size,
                        DTA_GroupID, GID_PICTURE,
                        PDTA_DestMode, PMODE_V43,
                        TAG_DONE);
    if (!o) {   /* no memory source, an older class, or a class that streams from a file */
        BPTR fh = Open(temp_name, MODE_NEWFILE);
        if (fh) {
            BOOL written = Write(fh, bytes, (LONG)size) == (LONG)size;
            Close(fh);
            *temp = TRUE;
            if (written)
                o = NewDTObject((APTR)temp_name,
                                DTA_SourceType, DTST_FILE,
                                DTA_GroupID, GID_PICTURE,
                                PDTA_DestMode, PMODE_V43,
                                TAG_DONE);
        }
    }
    return o;
}

int main(int argc, char **argv)
{
    static const char temp_name[] = "T:DTMemInfo.tmp";
    UBYTE *bytes;
    ULONG size = 0;
    int rc = RETURN_FAIL;
    if (argc != 2) {
        PutStr((CONST_STRPTR)"Usage: DTMemInfo PICTURE\n");
        return RETURN_WARN;
    }
    if (!(DataTypesBase = OpenLibrary((CONST_STRPTR)"datatypes.library", 39))) {
        PutStr((CONST_STRPTR)"DTMemInfo: no datatypes.library\n");
        return RETURN_FAIL;
    }
    if ((bytes = read_file((CONST_STRPTR)argv[1], &size)) != NULL) {
        BOOL temp;
        Object *o = picture_from_bytes(bytes, size, (CONST_STRPTR)temp_name, &temp);
        if (o) {
            struct BitMapHeader *bmh = NULL;
            LONG args[3];
            GetDTAttrs(o, PDTA_BitMapHeader, (ULONG)&bmh, TAG_DONE);
            args[0] = bmh ? bmh->bmh_Width : 0;
            args[1] = bmh ? bmh->bmh_Height : 0;
            args[2] = (LONG)(temp ? "through a file in T:" : "from memory");
            VPrintf((CONST_STRPTR)"%ld x %ld, opened %s\n", args);
            DisposeDTObject(o);     /* the bytes stay unchanged until here */
            rc = RETURN_OK;
        } else
            PrintFault(IoErr(), (CONST_STRPTR)"DTMemInfo");
        if (temp)
            DeleteFile((CONST_STRPTR)temp_name);    /* only the file this program made */
        FreeVec(bytes);
    } else
        PrintFault(IoErr(), (CONST_STRPTR)"DTMemInfo");
    CloseLibrary(DataTypesBase);
    return rc;
}
