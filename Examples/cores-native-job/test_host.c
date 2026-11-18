/* Runs the job build for this host's own ISA as the board would (the code
 * placed anywhere, buffers as copies) and checks it against the same sum in
 * C. The other ISA's build is checked for size only.
 *   make check
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence. */
#include <cores/acn_job.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#if defined(__x86_64__)
#define OWN "x86_64"
#define OTHER "arm64"
#elif defined(__aarch64__)
#define OWN "arm64"
#define OTHER "x86_64"
#else
#define OWN NULL
#define OTHER NULL
#endif

static unsigned char *slurp(const char *dir, const char *isa, size_t *n)
{
    char path[512];
    snprintf(path, sizeof path, "%s/job.%s.bin", dir, isa);
    FILE *f = fopen(path, "rb");
    if (!f) return NULL;
    unsigned char *b = malloc(1 << 22);
    *n = fread(b, 1, 1 << 22, f);
    fclose(f);
    return b;
}

int main(int argc, char **argv)
{
    const char *dir = argc > 1 ? argv[1] : "build";
    size_t n = 0;
    int fails = 0;
    if (OTHER) {
        unsigned char *o = slurp(dir, OTHER, &n);
        printf("%s   job.%s.bin: %zu bytes\n", o && n ? "ok  " : "FAIL", OTHER, n);
        fails += !(o && n);
        free(o);
    }
    if (!OWN) { printf("no native ISA here\n"); return fails != 0; }
    unsigned char *code = slurp(dir, OWN, &n);
    if (!code || !n) { printf("FAIL no job.%s.bin\n", OWN); return 1; }
    /* Somewhere the code was never built for, past a page of padding. */
    unsigned char *at = mmap(NULL, 1 << 22, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memcpy(at + 4096 + 64, code, n);
    mprotect(at, 1 << 22, PROT_READ | PROT_EXEC);
    uint64_t (*entry)(acn_job *) = (uint64_t (*)(acn_job *))(at + 4096 + 64);
    for (uint32_t count = 0; count <= 100000; count = count ? count * 10 : 1) {
        uint8_t *in = malloc(count * 4 + 4), *out = calloc(count + 1, 4);
        uint64_t sum = 0;
        int bad = 0;
        for (uint32_t i = 0; i < count; i++) acn_put_be32(in + 4 * i, i * 2654435761u);
        acn_job j = { { in, out, NULL }, { count * 4, count * 4, 0 }, { 0, 0, 0, 0 } };
        uint64_t r = entry(&j);
        for (uint32_t i = 0; i < count; i++) {
            sum += acn_be32(in + 4 * i);
            bad += acn_be32(out + 4 * i) != (uint32_t)sum;
        }
        int ok = r == sum && !bad;
        printf("%s   job.%s.bin, %u longs: $%016llx, totals %s\n", ok ? "ok  " : "FAIL", OWN, count,
               (unsigned long long)r, bad ? "differ" : "agree");
        fails += !ok;
        free(in); free(out);
    }
    printf("%s\n", fails ? "FAILED" : "PASSED");
    return fails != 0;
}
