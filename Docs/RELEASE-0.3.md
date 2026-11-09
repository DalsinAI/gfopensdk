The Open SDK 0.3, 9 November 2026: the boards' libraries.

PRE-RELEASE: mitchy.library and akikoplus.library are pinned at their
libraries' review branches (gfopenservice team5/mitchy-library-20261109
ca95320, gfosautoconfigboards team5/akikoplus-v2-20261109 3f48f80), not
yet merged. Their headers may still change; 0.3 itself is released once
both are merged and repinned to main, with their autodocs.

New: mitchy.library 1.0 (named services on Mitchy, the services card, on
the other ACSV boards, or on a paired Cradle on the LAN, through
gfopenservice.device) and akikoplus.library 2.0 (AkikoPlus, the media
board, on mitchy.library, with the same calls done on the 68k when there
is no board), each with libraries/, clib, proto, inline and pragmas
headers and its SFD/FD. Two examples: `Examples/mitchy-echo` (open a
service by name and call it) and `Examples/akikoplus-c2p` (chunky to
planar, checked against plain C).

Since 0.2: event.library 1.0 and 1.1, regex.library 1.0, openwxtoolkit.library,
arexx/apphost.h (a C program's ARexx port on arexx.class), gfopentls 1.4 /
gfopencrypto 2.3, gfopengpu.library 0.27 (stream v1.10, RemoteFX
Progressive), GFOpenBoost listed.

`Lib/build.sh` builds `libopensdk.a`, a stub for every call in `SFD/`
(448).

What's in it, part by part: `Docs/LIBRARIES.md`. Start with `Docs/PORTING.md`.

MIT, Copyright (c) 2026 AmiCradle Team. Designed, tested and delivered by The AmiCradle Team.
