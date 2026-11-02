# Restart: The Open SDK

_Written 6 October 2026 at about 23:55 UTC, while all work is paused on @SacredTrees's word (23:28 UTC). Read this first when work resumes; the newest capsule and the live PR list win if they disagree._

## What this repo is

The Open SDK: one kit to build and port to and from AmigaOS 3.2: headers, function tables, link libraries, autodocs, examples and ACKitchen templates for every Open library, plus os4compat for OS 4 source.

## Where it stands

Phase 1 (#1) and the os4compat kit (#2, HelloOS4 14/14 on a scratch instance) are merged. Docs/PORTING.md holds the 68k rule: never nest one inline library call in another's arguments.

## Merged lately

- #2 (73d1da9, 2026-10-06): os4compat 0.1: build AmigaOS 4 source for OS 3.2
- #3 (c2cc80e, 2026-10-06): Credit who made The Open SDK: CONTRIBUTORS.md
- #1 (923797c, 2026-10-06): Open SDK phase 1: today's headers, two templates, and the gather tool

## Open pull requests

- None.

## Next step

1. The one-SDK layout (one manual, ACKitchen pointing at it, every Open readme linking back), offered but not started.
2. First real OS 4 port test with the shim.

## Waiting on @SacredTrees

- Nothing blocking. Third-party imports from the Aminet review need "yes with review".

## Who owns it

Aminet/OS4 thread (done); Open apps queue.

## Capsules

Restart capsules for this repo's workstreams, in amicradle's `capjumps/` shelf:

- [`20261006_AmigaChrome_Aminet_OS4_Compat_Restart_Capsule.zip`](https://github.com/DalsinAI/amicradle/tree/main/capjumps)
- [`20261006_AmigaChrome_OpenApps_Queue_Restart_Capsule.zip`](https://github.com/DalsinAI/amicradle/tree/main/capjumps)

Team rules that still hold: commits as SacredTrees with no co-author lines; third-party code only on "yes with review" (licence checked, commit and sha256 pinned, fetched at build, never committed); deploys with deploy_dev.py only, on a typed line.
