/* libgfopensynth.a: gfopensynth.library's calls for C programs and ports
 * (link -lgfopensynth): the library opens at the first call and closes when
 * the program ends. gs_open returns NULL, with IoErr() set, when the
 * library or the synth can't be opened. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef GFOPENSYNTH_H
#define GFOPENSYNTH_H

#include <libraries/gfopensynth.h>

#ifdef __cplusplus
extern "C" {
#endif

int gs_available(void);                         /* the library opened */
struct GSSynth *gs_open(const struct TagItem *tags);
void gs_close(struct GSSynth *synth);
void gs_short(struct GSSynth *synth, unsigned long msg);   /* GS_MSG(status, d1, d2) */
void gs_sysex(struct GSSynth *synth, const unsigned char *data, unsigned long len);
int gs_play_file(struct GSSynth *synth, const char *name, const struct TagItem *tags);
void gs_stop_file(struct GSSynth *synth);
void gs_set_volume(struct GSSynth *synth, unsigned long volume);   /* 0 to GS_VOLUME_FULL */
void gs_reset(struct GSSynth *synth);
unsigned long gs_get(struct GSSynth *synth, unsigned long attr);
unsigned long gs_render(struct GSSynth *synth, short *buffer, unsigned long frames);
/* a MIDI file held in memory (copied: the caller's bytes need not stay) */
int gs_play_mem(struct GSSynth *synth, const unsigned char *data, unsigned long len, const struct TagItem *tags);
void gs_pause_file(struct GSSynth *synth, int pause);
void gs_seek_file(struct GSSynth *synth, unsigned long beat);
/* raw MIDI bytes, as written to a MIDI port (running status and SysEx) */
void gs_write(struct GSSynth *synth, const unsigned char *data, unsigned long len);
unsigned long gs_mem_length(const unsigned char *data, unsigned long len);   /* milliseconds, 0: not a MIDI file */

#ifdef __cplusplus
}
#endif

#endif
