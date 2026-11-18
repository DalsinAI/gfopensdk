# Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
# SPDX-License-Identifier: MIT
"""Every library's SFD/ and FD/ give the same calls at the same offsets, and
the libraries gathered into the SDK on 18 November 2026 are all there:
manifest part, proto header, function table, docs and a line in
Docs/LIBRARIES.md."""
import json
import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


def sfd_calls(text):
    """(bias, [(name, regs)]) from an SFD, with or without spaces before the
    register list; ==varargs/==alias lines name another entry, not a slot."""
    bias, calls, skip_next = None, [], False
    for line in text.splitlines():
        s = line.strip()
        if s.startswith("==bias"):
            bias = int(s.split()[1])
        elif s in ("==varargs", "==alias"):
            skip_next = True
        elif s.startswith("==reserve"):
            calls.extend([(None, None)] * int(s.split()[1]))
        elif s and not s.startswith(("==", "*")):
            if skip_next:
                skip_next = False
                continue
            head, regs = re.match(r"^(.*\))\s*\(([^)]*)\)\s*$", s).groups()
            name = head.split("(", 1)[0].split()[-1].lstrip("*")
            calls.append((name, regs.replace(" ", "").replace("/", ",").lower()))
    while calls and calls[-1] == (None, None):  # reserved slots at the end
        calls.pop()
    return bias, calls


def fd_calls(text):
    bias, calls = None, []
    for line in text.splitlines():
        s = line.strip()
        if s.startswith("##bias"):
            new = int(s.split()[1])
            if bias is not None:
                # a gap in the table: one empty slot each 6 bytes
                calls.extend([(None, None)] * ((new - bias - 6 * len(calls)) // 6))
            else:
                bias = new
        elif s and not s.startswith(("##", "*")):
            m = re.match(r"^(\w+)\(([^)]*)\)\(([^)]*)\)$", s.replace(" ", ""))
            calls.append((m.group(1), m.group(3).replace("/", ",").lower()))
    return bias, calls


NEW = {
    # part name: (proto header, SFD, docs file or None)
    "acgame.library": ("proto/acgame.h", "acgame_lib.sfd", "acgame.library.md"),
    "allegro4.library": ("allegro.h", "allegro4_lib.sfd", "allegro4.library.md"),
    "gfopensynth.library": ("proto/gfopensynth.h", "gfopensynth_lib.sfd", "gfopensynth.library.md"),
    "transmem.library": ("proto/transmem.h", "transmem_lib.sfd", "transmem.library.md"),
    "lzma.library": ("proto/lzma.h", "lzma_lib.sfd", "lzma.library.md"),
    "bzip2.library": ("proto/bzip2.h", "bzip2_lib.sfd", "bzip2.library.md"),
    "gfopendraw.library": ("proto/gfopendraw.h", "gfopendraw_lib.sfd", "gfopendraw.library.md"),
    "gfopeninput.library": ("proto/gfopeninput.h", "gfopeninput_lib.sfd", "gfopeninput.library.md"),
    # no SFD in their repositories yet: headers and docs only
    "gfopenusb.library": ("proto/gfopenusb.h", None, "gfopenusb.library.md"),
    "muimaster.library (GFOpenMUI)": ("proto/muimaster.h", None, "gfopenmui.md"),
}


class FunctionTableTests(unittest.TestCase):
    def test_parsers_on_a_fixture(self):
        sfd = ("==bias 30\n==public\nLONG A(LONG x) (d0)\nVOID B(APTR p, LONG n)(a0,d0)\n"
               "==varargs\nVOID BTags(APTR p, ...)(a0,a1)\n==reserve 1\nLONG C()()\n==end\n")
        fd = "##bias 30\n##public\nA(x)(d0)\nB(p,n)(a0,d0)\n##bias 48\nC()()\n##end\n"
        self.assertEqual(sfd_calls(sfd), fd_calls(fd))
        self.assertEqual(sfd_calls(sfd)[1][1], ("B", "a0,d0"))

    def test_gather_names_function_pointer_arguments(self):
        import importlib.util
        spec = importlib.util.spec_from_file_location("gather", ROOT / "tools/gather.py")
        g = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(g)
        sfd = ("==base _XBase\n==bias 30\n==public\n"
               "void T(MAP * table, const RGB * pal, void(*blend)(const PALETTE pal, int x, RGB *rgb), "
               "void (*cb)(int pos))(a0,a1,a2,a3)\nLONG U(LONG a, APTR * b)(d0,a0)\n==end\n")
        self.assertEqual(g.sfd_to_fd(sfd), "##base _XBase\n##bias 30\n##public\n"
                         "T(table,pal,blend,cb)(a0,a1,a2,a3)\nU(a,b)(d0,a0)\n##end\n")

    def test_every_sfd_matches_its_fd(self):
        sfds = sorted((ROOT / "SFD").glob("*.sfd"))
        self.assertTrue(sfds)
        for sfd in sfds:
            fd = ROOT / "FD" / (sfd.stem + ".fd")
            with self.subTest(sfd=sfd.name):
                self.assertTrue(fd.exists(), "no FD for " + sfd.name)
                want = sfd_calls(sfd.read_text(encoding="latin-1"))
                have = fd_calls(fd.read_text(encoding="latin-1"))
                self.assertEqual(want[0], have[0], "bias")
                self.assertEqual([c for c in want[1] if c[0]], [c for c in have[1] if c[0]])
                self.assertEqual(want[1], have[1], "offsets")

    def test_new_libraries_are_gathered_whole(self):
        manifest = json.loads((ROOT / "manifest.json").read_text())
        parts = {p["name"]: p for p in manifest["parts"]}
        index = (ROOT / "Docs/LIBRARIES.md").read_text()
        headers = (ROOT / "tests/sdk/headers.c").read_text()
        for name, (proto, sfd, doc) in NEW.items():
            with self.subTest(part=name):
                self.assertIn(name, parts)
                self.assertRegex(parts[name]["commit"], r"^[0-9a-f]{40}$")
                outs = set(parts[name]["files"].values())
                self.assertIn("Include/" + proto, outs)
                if sfd:
                    self.assertIn("SFD/" + sfd, outs)
                    self.assertTrue((ROOT / "FD" / sfd.replace(".sfd", ".fd")).exists())
                if doc:
                    self.assertIn("Docs/" + doc, outs)
                    self.assertIn(f"]({doc})", index)
                self.assertIn(f"| {name} |", index)
                if name != "allegro4.library":
                    self.assertIn(f"#include <{proto}>", headers)

    def test_acgame_lvos(self):
        # acgame.library's LVOs that ports and allegro4.library call by number
        _, calls = sfd_calls((ROOT / "SFD/acgame_lib.sfd").read_text())
        lvo = {n: -(30 + 6 * i) for i, (n, _) in enumerate(calls) if n}
        self.assertEqual(lvo["ACG_OpenAllegro"], -144)
        self.assertEqual(lvo["ACG_AudioOpen"], -150)
        self.assertEqual(lvo["ACG_VoicePosition"], -186)

    def test_allegro4_stays_out_of_libopensdk(self):
        # its calls need <allegro.h> and the C library; games link liballeg.a
        build = (ROOT / "Lib/build.sh").read_text()
        self.assertRegex(build, r'SKIP=\$\{SKIP-"[^"]*allegro4_lib\.sfd[^"]*"\}')


if __name__ == "__main__":
    unittest.main()
