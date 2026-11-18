# GFOpenSynth design

MT-32 and General MIDI for Amiga programs. Studied from mt32-pi (a Pi that
stands in for an MT-32 or a SoundFont synth on a real MIDI port); none of its
code, Munt's or FluidSynth's is used. Ours, so it ports to other platforms.

## Shape

```
 Amiga program --CAMD--> DEVS:Midi/akikoplus --+
 Amiga program --gfopensynth.library-----------+--> AkikoPlus MIDI port (bytes)
                                                         |
                                  host space:  gfopensynth engine (src/)
                                               SoundFont / MT-32 ROMs from cards/
                                                         |
                                                   host audio out
```

- **The port.** AkikoPlus gets a MIDI port: a serial-style byte stream (out
  and in FIFOs, status), as a real MIDI interface is. Only MIDI bytes cross
  it; no PCM comes back, as with a real box.
- **The synth.** In host space, the device plugged into the port: the bytes
  go through `gs_synth_port` (parser + synth) and the synth renders to the
  host's audio, as a real synth's own audio out.
- **No board.** gfopensynth.library runs the same engine on the 68k
  (General MIDI from a SoundFont) and sends it to ahi.device, or hands the
  samples to a program that mixes its own (allegro4.library, ACGame).
- **ROMs and SoundFonts** live in host space under the card's folder, never
  in the guest, a repository, a release or a build. On the 68k rung the
  SoundFont comes from `DEVS:SoundFonts/` (or `ENV:GFOpenSynth/SoundFont`).

## Engines

1. **General MIDI from a SoundFont** (this draft): SF2 2.04 zones, the
   volume envelope (delay, attack, hold, decay, sustain, release, key
   scaling), pan, initial attenuation (0.4 of the specification's unit, as
   SoundFonts made on EMU's hardware expect), velocity, CC 7/10/11/64,
   RPN 0 bend range, all notes/sound off, reset controllers, exclusive
   classes, loops (none, always, until released), voice stealing (quietest
   released, else oldest). Not yet: the filter, the modulation envelope and
   LFOs, reverb and chorus, SF2 modulators.
2. **MT-32 through GM** (this draft): `GS_MODE_MT32_GM` listens on MIDI
   channels 2-10 as an MT-32 does from power on and maps its 128 programs to
   the nearest GM ones. MT-32 SysEx is counted and ignored.
3. **MT-32 (LA synthesis) from the ROMs**: ours, a later stage. The ROM
   handling it needs is here: `gs_rom.c` knows every MT-32, CM-32L and
   CM-32LN control ROM and both PCM ROMs by SHA-1, joins `_a`/`_b` (even and
   odd bytes) and `_l`/`_h` (halves) and the CM-32L PCM (MT-32 PCM followed
   by `cm32l_pcm_h`), and picks a complete set, newest control ROM first.

## Numbers

Everything is integer: Q16 pitch increments from a 2^(c/1200) table, Q15
gains from a 10^(-cB/200) table, the SF2 concave curve and constant-power pan
as tables (`tools/gen_tables.py` writes `src/gs_tables.c`; the host tests
check it is current). Envelopes and gains step every 32 frames
(`GS_BLOCK`); samples are linearly interpolated. 64-bit sums only at note
on, bend and tempo changes.

## The library

`include/sfd/gfopensynth_lib.sfd` lists the calls. `GSOpenSynthA` takes
`GSA_Output` (auto: the port if its device opens, else the 68k to AHI;
`ENV:GFOpenSynth/Output`), `GSA_Engine` (GM or MT-32), and for the 68k
`GSA_SoundFont`, `GSA_Rate`, `GSA_Voices`, `GSA_Unit`. On the port the
engine and the volume go as SysEx (`F0 7D 'G' 'S' 01 mode F7`, and the
universal master volume), so the host's synth is set the same way a real
box is; a MIDI file is timed in the library's player process with
timer.device and sent as bytes. On the 68k the player process keeps two
linked AHI buffers of 100 ms going. `GSRenderS16` is for programs that mix
their own (allegro4.library).

For a program that holds its music in memory (allegro4.library: a game's
MIDI objects come out of its datafile): `GSPlayMemA` plays a MIDI file from
memory (copied), `GSPauseFile` holds it and lets it go on, `GSSeekFile`
moves it to a beat (tempo, programs and controllers kept on the way, notes
left out), `GSWriteBytes` takes raw MIDI bytes as a port does, and
`GSMemLength` is a file's length without playing it. `GSA_Position`
(milliseconds) and `GSA_Beat` say where the file is.

## Where the sound goes

- **On the port** the synth is a box in the machine: its sound joins
  Paula's (and the AHI board's) at the machine's own output. It does not
  pass through ahi.device, as a real MT-32's would not.
- **`GSOUT_AHI`**: the 68k engine writes to ahi.device (unit `GSA_Unit`).
- **`GSOUT_CALLER`**: the program mixes the synth into its own sound.
  allegro4.library does this when there is no port, so its music goes out
  with its samples through acgame.library: AHI, with Paula as the fallback.

## Next

1. (done in this draft) gfopensynth.library.
2. AkikoPlus MIDI port: guest device and the host side, in
   gfosautoconfigboards (`cards/akikoplus`) and the runtime, with this
   engine built for the host.
3. CAMD driver for the port.
4. (done: gfopenallegro) allegro4.library's MIDI through it.
5. The LA engine.

Labs wait until after the Pi 5 update and Dale's go. Tests with real ROMs run
only on our own machines.

MIT, Copyright (c) 2026 AmiCradle Team.
