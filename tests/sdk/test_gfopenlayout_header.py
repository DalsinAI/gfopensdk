#!/usr/bin/env python3
"""The SDK's <libraries/gfopenlayout.h> declares every type gfopenlayout_lib.sfd's calls take.

Lib/build.sh makes clib/gfopenlayout_protos.h and its stubs from SFD/gfopenlayout_lib.sfd,
whose only header is <libraries/gfopenlayout.h>. A call whose types that header (and what it
includes) doesn't declare can't be compiled there: library 25's OLDraw_ calls take oldraw types
from gfopenlayout_draw.h.
"""
from __future__ import annotations

import re
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
INCLUDE = ROOT / "Include"
SFD = ROOT / "SFD" / "gfopenlayout_lib.sfd"
OURS = re.compile(r"\b(ol[a-z]*_[A-Za-z0-9_]+|oldraw|ol_[a-z]+)\b")


def reachable(name: str, seen: set[Path]) -> set[Path]:
    path = INCLUDE / name
    if not path.is_file() or path in seen:
        return seen
    seen.add(path)
    for inc in re.findall(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]', path.read_text(), re.M):
        reachable(inc, seen)
    return seen


def declared_types(headers: set[Path]) -> set[str]:
    names: set[str] = set()
    for h in headers:
        text = re.sub(r"/\*.*?\*/", "", h.read_text(), flags=re.S)
        names.update(re.findall(r"\btypedef\b[^;{]*?\b(\w+)\s*;", text))
        names.update(re.findall(r"\}\s*(\w+)\s*;", text))
        names.update(re.findall(r"\btypedef\b[^;]*?\(\s*\*\s*(\w+)\s*\)", text))
    return names


def sfd_types() -> dict[str, str]:
    used: dict[str, str] = {}
    for line in SFD.read_text().splitlines():
        m = re.match(r"^([^=*#].*?)\b([A-Z]\w*)\((.*)\)\([^)]*\)\s*$", line)
        if not m:
            continue
        ret, call, args = m.groups()
        for part in [ret] + args.split(","):
            words = re.sub(r"\bstruct\s+\w+", "", part)
            words = re.sub(r"\w+\s*$", "", words) if part is not ret else words
            for t in OURS.findall(words):
                used.setdefault(t, call)
    return used


class LibraryHeader(unittest.TestCase):
    def test_every_sfd_type_is_declared_by_the_public_header(self):
        types = declared_types(reachable("libraries/gfopenlayout.h", set()))
        missing = {t: call for t, call in sfd_types().items() if t not in types}
        self.assertEqual(missing, {}, "types the SFD's calls take that <libraries/gfopenlayout.h> doesn't declare")

    def test_the_drawing_calls_are_checked(self):
        self.assertIn("oldraw_rect", sfd_types())


if __name__ == "__main__":
    unittest.main()
