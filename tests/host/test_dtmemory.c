/* Host test: Examples/datatypes-memory/dtmemory.h, the rule for when the
 * datatypes take a memory source (Docs/datatypes-memory.md).
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#include <stdio.h>
#include "dtmemory.h"

static int failed;
#define CHECK(c, what) do { if (!(c)) { printf("FAIL %s\n", what); failed++; } } while (0)

int main(void)
{
    CHECK(dt_memory_source_ok(47, 100), "47.100 takes memory");
    CHECK(dt_memory_source_ok(47, 101), "47.101 takes memory");
    CHECK(dt_memory_source_ok(48, 0), "48.0 takes memory");
    CHECK(dt_memory_source_ok(53, 1), "53.1 takes memory");
    CHECK(!dt_memory_source_ok(47, 99), "47.99 uses a file");
    CHECK(!dt_memory_source_ok(47, 15), "OS 3.2's 47.15 uses a file");
    CHECK(!dt_memory_source_ok(47, 0), "47.0 uses a file");
    CHECK(!dt_memory_source_ok(45, 200), "45.200 uses a file: the revision alone does not count");
    CHECK(!dt_memory_source_ok(39, 0), "39.0 uses a file");
    CHECK(DTMEMORY_VERSION == 47 && DTMEMORY_REVISION == 100, "the numbers the note gives");
    if (!failed) printf("dtmemory: 10 passed\n");
    return failed != 0;
}
