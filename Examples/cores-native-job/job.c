/* The native job of Examples/cores-native-job: built for the host, run on
 * a core of the CPU cores board (cpu.x86_64/1 or cpu.arm64/1).
 *
 * Adds up the big-endian longs of buffer 1 and writes each running total
 * into buffer 2 (written). Result: the low 32 bits of the sum; aux: the
 * high 32.
 *
 * One function, with nothing to relocate and no system calls: see
 * <cores/acn_job.h> for the rules.
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence. */
#include <cores/acn_job.h>

__attribute__((section(".text.acn_entry"), used))
uint64_t acn_entry(acn_job *job)
{
    const uint8_t *in = job->buf[0];
    uint8_t *out = job->buf[1];
    uint32_t n = job->len[0] / 4, room = job->len[1] / 4, i;
    uint64_t sum = 0;

    for (i = 0; i < n; i++) {
        sum += acn_be32(in + 4 * i);
        if (i < room)
            acn_put_be32(out + 4 * i, (uint32_t)sum);
    }
    return ACN_RESULT((uint32_t)sum, (uint32_t)(sum >> 32));
}
