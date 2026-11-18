/* A native job for the CPU cores board: the job's own source, built for
 * the host (x86-64 for cpu.x86_64/1, AArch64 for cpu.arm64/1), not for
 * the Amiga.
 *
 * Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence.
 *
 * The board runs the job as a function in the host's own C calling
 * convention:
 *
 *   uint64_t entry(acn_job *job);    low 32 bits: result, high 32: aux
 *
 * buf[0..2] are the host's copies of the request's buffers 1 to 3 (buffer 0
 * is the code itself); the ones the request marks written are copied back
 * to Amiga memory only when the job returns. x[0..3] are mr_Extra[0..3].
 *
 * The rules:
 *   - Position independent, and on its own: no libc, no system calls (any
 *     system call ends the job, CORES_FAULT with result 31), no globals
 *     that need relocating. Build with -fPIC -ffreestanding -nostdlib and
 *     take the bytes out with objcopy -O binary (Examples/cores-native-job).
 *   - The bytes are big-endian on the Amiga's side and the host's own
 *     order here: a job reading the Amiga's longs swaps them (acn_be32).
 *   - At most 4 MB of code; data buffers 64 MB together, written ones 16 MB.
 *   - Its own sandbox each time: a fresh process, with nothing of earlier
 *     jobs. A crash ends only the job (CORES_FAULT, the signal). */
#ifndef CORES_ACN_JOB_H
#define CORES_ACN_JOB_H

#include <stdint.h>

typedef struct {
    uint8_t *buf[3];                    /* offset 0 */
    uint32_t len[3];                    /* offset 24 */
    uint32_t x[4];                      /* offset 36 */
} acn_job;

#define ACN_RESULT(result, aux) ((uint64_t)(uint32_t)(result) | (uint64_t)(uint32_t)(aux) << 32)

static inline uint32_t acn_be32(const uint8_t *p)
{
    return (uint32_t)p[0] << 24 | (uint32_t)p[1] << 16 | (uint32_t)p[2] << 8 | p[3];
}
static inline void acn_put_be32(uint8_t *p, uint32_t v)
{
    p[0] = (uint8_t)(v >> 24); p[1] = (uint8_t)(v >> 16); p[2] = (uint8_t)(v >> 8); p[3] = (uint8_t)v;
}

#endif
