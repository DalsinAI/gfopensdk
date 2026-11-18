/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * DUMB's loading calls, as Allegro 4 games use them for module music
 * (with aldumb.h). Our own code, not DUMB's: a DUH only names the file, and
 * gfopenmusic.library reads and plays it (MOD, S3M, XM, IT through
 * gfopenmodule.datatype) when a player starts. Game-side, in liballeg.a.
 */
#ifndef A4_DUMB_H
#define A4_DUMB_H

#ifdef __cplusplus
extern "C" {
#endif

#define DUMB_MAJOR_VERSION    0
#define DUMB_MINOR_VERSION    9
#define DUMB_REVISION_VERSION 3
#define DUMB_VERSION_STR      "0.9.3"
#define DUMB_NAME             "DUMB v" DUMB_VERSION_STR

typedef struct DUH DUH;

void dumb_register_stdfiles(void);
void dumb_exit(void);

/* every loader gives a DUH for an existing file, NULL when it is missing */
DUH *dumb_load_mod(const char *filename);
DUH *dumb_load_mod_quick(const char *filename);
DUH *dumb_load_s3m(const char *filename);
DUH *dumb_load_s3m_quick(const char *filename);
DUH *dumb_load_xm(const char *filename);
DUH *dumb_load_xm_quick(const char *filename);
DUH *dumb_load_it(const char *filename);
DUH *dumb_load_it_quick(const char *filename);
void unload_duh(DUH *duh);
long duh_get_length(DUH *duh);      /* 0: not known until it plays */

extern int dumb_resampling_quality; /* kept */
extern int dumb_it_max_to_mix;      /* kept */

#ifdef __cplusplus
}
#endif

#endif
