The Open SDK 0.3, 9 November 2026: the boards' libraries.

mitchy.library and akikoplus.library are pinned at their libraries' main
(gfopenservice e94f674, #34; gfosautoconfigboards 8b9ffe0, #4). Their headers
are the review branches' (ca95320, 3f48f80) unchanged, and their autodocs come
with them: `Docs/mitchy.doc` and `Docs/akikoplus.doc`.

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
