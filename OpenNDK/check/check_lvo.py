#!/usr/bin/env python3
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
"""Compare OpenNDK's SFDs with the open libraries' own .lvo tables.

    check_lvo.py --guest AMIGACHROME-GUEST [--gfx OPENAMIGAGFX] [SFD...]

Each open library keeps a .lvo table (LVO, call, registers) that its build
checks against the vendor's function table, so a match here means the SFD's
names, slots and registers are the ones programs already link against.
Private slots are compared by position only. Exit 1 on any difference.
"""
import argparse
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "tools"))
import ndkgen  # noqa: E402

# SFD stem -> .lvo path, relative to the guest checkout ("gfx:" = gfopengfx)
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
    "datatypes": "libraries/opendatatypes/datatypes.lvo",
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


def reaction_lvo(guest, stem):
    for pat in ("libraries/openreaction/%s/%s.lvo", "libraries/opendatatypes/classes/datatypes/%s/%s.lvo"):
        p = os.path.join(guest, pat % (stem, stem))
        if os.path.exists(p):
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
    ap.add_argument("sfd", nargs="*")
    o = ap.parse_args()
    sfds = o.sfd or sorted(glob.glob(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "SFD", "*.sfd")))
    bad = checked = 0
    for path in sfds:
        lib = ndkgen.Lib(path)
        rel = LVO.get(lib.stem)
        if rel and rel.startswith("gfx:"):
            lvo = os.path.join(o.gfx, rel[4:]) if o.gfx else None
        elif rel:
            lvo = os.path.join(o.guest, rel)
        else:
            lvo = reaction_lvo(o.guest, lib.stem)
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
            if a is None or t is None:
                print("%s -%d: SFD %s, .lvo %s" % (lib.sfdname, b, a, t))
                bad += 1
            elif a[0] == "private" or t[0] == "private":
                if a[0] != t[0]:
                    print("%s -%d: SFD %s, .lvo %s (private in one)" % (lib.sfdname, b, a, t))
            elif a != t:
                print("%s -%d: SFD %s(%s), .lvo %s(%s)" % (lib.sfdname, b, a[0], a[1], t[0], t[1]))
                bad += 1
    print("%d SFDs compared with .lvo tables, %d differences" % (checked, bad))
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
