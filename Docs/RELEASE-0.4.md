The Open SDK 0.4, 18 November 2026: the newest libraries.

Ten libraries are gathered at their main, each with its headers, function
tables and docs (Docs/LIBRARIES.md lists every part and its pin):

- acgame.library 1.3 (acgame 5a43eb9): the game layer, now with sound.
- allegro4.library 1.1 (gfopenallegro 31d0bfc): `<allegro.h>`; games link
  `liballeg.a` from the Allegro 4 release.
- gfopensynth.library 1.0 (gfopensynth 5de9f6d): the MIDI synth.
- transmem.library 1.0 (gfopentransmem 231e4dd).
- lzma.library 1.0 (gfopenlzma 47aeaba).
- bzip2.library 1.0 (gfopenbzip2 d90840c).
- gfopendraw.library 1.0 (gfopendraw e22568e): GFOpenDraw's paint engine.
- gfopeninput.library (gfopeninput c5309c1).
- gfopenusb.library (gfopenusb 4056e1d): headers only, no SFD yet.
- muimaster.library, GFOpenMUI (gfopenmui 922f7ce): `libraries/mui.h`,
  proto/clib/inline and the `zune/` class headers.

`Lib/build.sh` builds `libopensdk.a` with 615 stubs, every SFD but
allegro4's. `tools/gather.py` now makes correct FDs for calls that take
function pointers. `tests/sdk/test_function_tables.py` checks every SFD
against its FD.
