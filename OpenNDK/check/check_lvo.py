#!/usr/bin/env python3
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
"""Compare OpenNDK's SFDs with the open libraries' own .lvo tables.

    check_lvo.py --guest AMICRADLE-GUEST [--gfx GFOPENGFX] [--datatypes GFOPENDATATYPES] [SFD...]

Each open library keeps a .lvo table (LVO, call, registers) that its build
checks against the vendor's function table, so a match here means the SFD's
names, slots and registers are the ones programs already link against.
Private slots are compared by position only. Calls an open library adds
past the end of the NDK's table are ours (GFOpen additions, declared in the
Open SDK's own headers, never in OpenNDK) and are listed, not counted.
Exit 1 on any difference.
"""
import argparse
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "tools"))
import ndkgen  # noqa: E402

# SFD stem -> .lvo path, relative to the guest checkout ("gfx:" = gfopengfx,
# "dt:" = gfopendatatypes)
LVO = {
    "exec": "libraries/openexec/exec.lvo",
    "dos": "libraries/opendos/dos.lvo",
    "utility": "libraries/openutility/utility.lvo",
    "intuition": "libraries/openintuition/intuition.lvo",
    "gadtools": "libraries/opengadtools/gadtools/gadtools.lvo",
    "asl": "libraries/openasl/asl.lvo",
    "amigaguide": "libraries/openamigaguide/amigaguide.lvo",
    "bullet": "libraries/openbullet/bullet.lvo",
    "commodities": "libraries/opencommodities/commodities.lvo",
    "datatypes": "dt:libraries/opendatatypes/datatypes.lvo",
    "diskfont": "libraries/opendiskfont/diskfont.lvo",
    "expansion": "libraries/openexpansion/expansion.lvo",
    "iffparse": "libraries/openiffparse/iffparse.lvo",
    "keymap": "libraries/openkeymap/keymap.lvo",
    "locale": "libraries/openlocale/locale.lvo",
    "lowlevel": "libraries/openlowlevel/lowlevel.lvo",
    "mathffp": "libraries/openmathffp/mathffp.lvo",
    "mathtrans": "libraries/openmathffp/mathtrans.lvo",
    "mathieeedoubbas": "libraries/openmathieee/mathieeedoubbas.lvo",
    "mathieeedoubtrans": "libraries/openmathieee/mathieeedoubtrans.lvo",
    "mathieeesingbas": "libraries/openmathieee/mathieeesingbas.lvo",
    "mathieeesingtrans": "libraries/openmathieee/mathieeesingtrans.lvo",
    "nonvolatile": "libraries/opennonvolatile/nonvolatile.lvo",
    "realtime": "libraries/openrealtime/realtime.lvo",
    "rexxsyslib": "libraries/openrexxsyslib/rexxsyslib.lvo",
    "console": "devices/openconsole.device/console.lvo",
    "timer": "devices/opentimer.device/timer.lvo",
    "ramdrive": "devices/openramdrive.device/ramdrive.lvo",
    "battclock": "resources/openbattclock.resource/battclock.lvo",
    "battmem": "resources/openbattmem.resource/battmem.lvo",
    "cardres": "resources/opencard.resource/card.lvo",
    "cia": "resources/opencia.resource/cia.lvo",
    "disk": "resources/opendisk.resource/disk.lvo",
    "misc": "resources/openmisc.resource/misc.lvo",
    "potgo": "resources/openpotgo.resource/potgo.lvo",
    "graphics": "gfx:library/graphics/graphics.lvo",
    "layers": "gfx:library/layers/layers.lvo",
}

# Our own calls in the vendor's private or past-the-end slots, and the Open
# SDK header that declares them
OURS = {
    "exec": "Include/exec/gfopenexec_atomic.h (AtomicCAS and friends; check GFOpenExec first)",
    "graphics": "Include/proto/gfxdispatch.h, Include/graphics/gfxdispatch.h",
    "layers": "Include/graphics/gfopenlayers.h",
    "dos": "none: ODShellRun is shell.library's own, not for programs",
}


def reaction_lvo(roots, stem):
    for root, pat in ((roots[0], "libraries/openreaction/%s/%s.lvo"),
                      (roots[0], "libraries/opendatatypes/classes/datatypes/%s/%s.lvo"),
                      (roots[1], "libraries/opendatatypes/classes/datatypes/%s/%s.lvo")):
        p = os.path.join(root, pat % (stem, stem)) if root else None
        if p and os.path.exists(p):
            return p
    return None


def read_lvo(path):
    out = {}
    for raw in open(path):
        toks = [t for t in raw.split("#")[0].split() if not t.startswith(">")]
        if toks:
            out[-int(toks[0])] = (toks[1], toks[2].lower() if len(toks) > 2 else "")
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--guest", required=True)
    ap.add_argument("--gfx")
    ap.add_argument("--datatypes")
    ap.add_argument("sfd", nargs="*")
    o = ap.parse_args()
    sfds = o.sfd or sorted(glob.glob(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "SFD", "*.sfd")))
    bad = checked = 0
    for path in sfds:
        lib = ndkgen.Lib(path)
        rel = LVO.get(lib.stem)
        if rel and rel.startswith("gfx:"):
            lvo = os.path.join(o.gfx, rel[4:]) if o.gfx else None
        elif rel and rel.startswith("dt:"):
            lvo = os.path.join(o.datatypes, rel[3:]) if o.datatypes else None
            if not (lvo and os.path.exists(lvo)):
                lvo = os.path.join(o.guest, rel[3:])
        elif rel:
            lvo = os.path.join(o.guest, rel)
        else:
            lvo = reaction_lvo((o.guest, o.datatypes), lib.stem)
        if not lvo or not os.path.exists(lvo):
            print("%s: no .lvo to compare with" % lib.sfdname)
            continue
        ours = {f.bias: (("private" if f.private else f.name), ",".join(f.regs)) for f in lib.slots()}
        theirs = read_lvo(lvo)
        checked += 1
        for b in sorted(set(ours) | set(theirs)):
            a, t = ours.get(b), theirs.get(b)
            if t is None and a and a[0] == "private":
                continue
            if t is None and b > max(theirs):
                # a call past the end of the open library's table: one it
                # doesn't have yet, not a disagreement
                print("%s -%d: %s not in the open library yet" % (lib.sfdname, b, a[0]))
                continue
            if a is None and b > max(ours):
                print("%s -%d: %s is ours, past the NDK's table (SDK: %s)"
                      % (lib.sfdname, b, t[0], OURS.get(lib.stem, "not declared yet")))
                continue
            if a is None or t is None:
                print("%s -%d: SFD %s, .lvo %s" % (lib.sfdname, b, a, t))
                bad += 1
            elif a[0] == "private" or t[0] == "private":
                if a[0] != t[0]:
                    note = " (ours; SDK: %s)" % OURS[lib.stem] if lib.stem in OURS and a[0] == "private" else ""
                    print("%s -%d: SFD %s, .lvo %s (private in one)%s" % (lib.sfdname, b, a, t, note))
            elif a != t:
                print("%s -%d: SFD %s(%s), .lvo %s(%s)" % (lib.sfdname, b, a[0], a[1], t[0], t[1]))
                bad += 1
    print("%d SFDs compared with .lvo tables, %d differences" % (checked, bad))
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
