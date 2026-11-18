/* Copyright (c) 2026 AmiCradle Team. MIT licence (see allegro4/LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * DUMB's Allegro layer: a player for a DUH. Playing goes to
 * gfopenmusic.library (ahi.device); without it a player still runs, silent.
 * The music plays on its own, so al_poll_duh only reports. Game-side, in liballeg.a.
 */
#ifndef A4_ALDUMB_H
#define A4_ALDUMB_H

#include <allegro.h>
#include "dumb.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AL_DUH_PLAYER AL_DUH_PLAYER;

/* n_channels, bufsize and freq are kept for the game; the music library mixes */
AL_DUH_PLAYER *al_start_duh(DUH *duh, int n_channels, long pos, float volume, long bufsize, int freq);
void al_stop_duh(AL_DUH_PLAYER *dp);
void al_pause_duh(AL_DUH_PLAYER *dp);
void al_resume_duh(AL_DUH_PLAYER *dp);
void al_duh_set_priority(AL_DUH_PLAYER *dp, int priority);
void al_duh_set_volume(AL_DUH_PLAYER *dp, float volume);
float al_duh_get_volume(AL_DUH_PLAYER *dp);
int al_poll_duh(AL_DUH_PLAYER *dp);           /* nonzero once the music has stopped */
long al_duh_get_position(AL_DUH_PLAYER *dp);  /* 65536 a second */

/* datafile objects: kept, a datafile's music is not read */
void dumb_register_dat_mod(long type);
void dumb_register_dat_s3m(long type);
void dumb_register_dat_xm(long type);
void dumb_register_dat_it(long type);

#ifdef __cplusplus
}
#endif

#endif
