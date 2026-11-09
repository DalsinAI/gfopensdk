/* physfs.library from the Open SDK: one tree of files from a drawer or an
 * archive.
 *
 * Mounts FROM (a drawer, or a zip, 7z, WAD, GRP, HOG, PAK... file) and
 * lists every file in it with its size; or, with FILE, writes that one
 * file to the Shell. Deflated zip members are inflated by LIBS:z.library.
 *
 *   PhysFSList FROM=<drawer or archive> [FILE=<name inside it>]
 *
 * The program is built with -lphysfs_auto, which opens physfs.library 1
 * before main() and closes it after: there is no OpenLibrary() here, and
 * the PhysicsFS calls are PhysicsFS's own (<physfs.h>). The enumerate
 * callback needs nothing special; a program built -fbaserel would mark it
 * __saveds.
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence: your own
 * program built from it is yours to licence as you like. */
#include <stdio.h>
#include <exec/types.h>
#include <dos/dos.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <physfs.h>

static const char version[] __attribute__((used)) = "$VER: PhysFSList 1.0 (9.11.2026)";

static ULONG files, bytes;

static void say_error(const char *what)
{
    Printf((CONST_STRPTR) "PhysFSList: %s: %s\n", (LONG) what,
           (LONG) PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
}

/* Called by PHYSFS_enumerate for each name in a drawer of the tree. */
static PHYSFS_EnumerateCallbackResult list_one(void *data, const char *dir, const char *name)
{
    char path[512];
    PHYSFS_Stat st;
    (void) data;
    if (dir[0])
        snprintf(path, sizeof path, "%s/%s", dir, name);
    else
        snprintf(path, sizeof path, "%s", name);
    if (!PHYSFS_stat(path, &st))
        return PHYSFS_ENUM_ERROR;
    if (st.filetype == PHYSFS_FILETYPE_DIRECTORY)
        return PHYSFS_enumerate(path, list_one, NULL) ? PHYSFS_ENUM_OK : PHYSFS_ENUM_ERROR;
    Printf((CONST_STRPTR) "%10lu %s\n", (ULONG) st.filesize, (LONG) path);
    files++;
    bytes += (ULONG) st.filesize;
    return CheckSignal(SIGBREAKF_CTRL_C) ? PHYSFS_ENUM_STOP : PHYSFS_ENUM_OK;
}

static int write_out(const char *name)
{
    char buf[4096];
    PHYSFS_sint64 got;
    PHYSFS_File *f = PHYSFS_openRead(name);
    if (!f)
    {
        say_error(name);
        return RETURN_ERROR;
    }
    while ((got = PHYSFS_readBytes(f, buf, sizeof buf)) > 0)
        Write(Output(), buf, (LONG) got);
    PHYSFS_close(f);
    return got < 0 ? RETURN_ERROR : RETURN_OK;
}

int main(int argc, char **argv)
{
    LONG args[2] = { 0, 0 };
    struct RDArgs *rd;
    int rc = RETURN_OK;
    (void) argc;

    rd = ReadArgs((CONST_STRPTR) "FROM/A,FILE", args, NULL);
    if (!rd)
    {
        PrintFault(IoErr(), (CONST_STRPTR) "PhysFSList");
        return RETURN_FAIL;
    }
    if (!PHYSFS_init(argv[0]))
    {
        say_error("PHYSFS_init");
        FreeArgs(rd);
        return RETURN_FAIL;
    }
    if (!PHYSFS_mount((const char *) args[0], NULL, 0))
    {
        say_error((const char *) args[0]);
        rc = RETURN_ERROR;
    }
    else if (args[1])
        rc = write_out((const char *) args[1]);
    else if (!PHYSFS_enumerate("", list_one, NULL))
    {
        say_error("listing");
        rc = RETURN_ERROR;
    }
    else
        Printf((CONST_STRPTR) "%lu files, %lu bytes\n", files, bytes);
    PHYSFS_deinit();
    FreeArgs(rd);
    return rc;
}
