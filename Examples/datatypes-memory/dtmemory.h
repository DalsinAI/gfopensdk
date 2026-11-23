#ifndef DTMEMORY_H
#define DTMEMORY_H
/*
 * The Open SDK: when a program may hand the datatypes a file's bytes in
 * memory (DTST_MEMORY), and when it must use a file (Docs/datatypes-memory.md).
 * Plain C with no Amiga header, so the rule is tested on the host
 * (tests/host/test_dtmemory.c).
 * MIT, Copyright (c) 2026 AmiCradle Team.
 */

/* datatypes.library 47.100 is the first with a memory source. OS 3.2's own
 * datatypes.library is 47.x below 100: it has none, so do not try it there. */
#define DTMEMORY_VERSION    47
#define DTMEMORY_REVISION   100

/* Nonzero when datatypes.library of this lib_Version and lib_Revision takes
 * DTST_MEMORY. A zero means: write the bytes to a file and open that. A
 * nonzero is not a promise: an older class, or one that streams from a file
 * by name, still fails NewDTObject() (IoErr 212), and then the file is the
 * fallback too. */
static inline int dt_memory_source_ok(unsigned version, unsigned revision)
{
    return version > DTMEMORY_VERSION || (version == DTMEMORY_VERSION && revision >= DTMEMORY_REVISION);
}

#endif /* DTMEMORY_H */
