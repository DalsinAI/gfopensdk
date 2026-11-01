#!/usr/bin/env python3
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
"""Compare OpenNDK's SFDs with a vendor NDK's: the same calls at the same
offsets, the same registers, and the same prototypes once spacing, CONST
and argument names are set aside.

    compare_sfd.py NDK_SFD_DIR [--report FILE]

Exit 1 on any difference. The vendor's files are only read.
"""
import glob
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "tools"))
import ndkgen  # noqa: E402


def norm_type(t):
    t = re.sub(r"\b(CONST|const)\b", "", t)
    t = t.replace("CONST_STRPTR", "STRPTR").replace("CONST_APTR", "APTR")
    t = re.sub(r"\s+", "", t)
    return "APTR" if t in ("VOID*", "void*") else t


def sig(f):
    return (norm_type(f.ret), tuple(norm_type(a.type) for a in f.args), f.dots)


def proto(f):
    """A call as name, types and registers only: what a program's binary
    depends on, with none of the vendor's wording."""
    args = [norm_type(a.type) for a in f.args] + (["..."] if f.dots else [])
    return "%s %s(%s) (%s)%s" % (norm_type(f.ret), f.name, ", ".join(args), ",".join(f.regs),
                                 " private" if f.private else "")


def main():
    ndk = sys.argv[1]
    report = sys.argv[3] if len(sys.argv) > 3 and sys.argv[2] == "--report" else None
    here = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "SFD")
    out, bad, typediff = [], 0, 0
    theirs = {os.path.basename(p): p for p in glob.glob(os.path.join(ndk, "*.sfd"))}
    ours = {os.path.basename(p): p for p in glob.glob(os.path.join(here, "*.sfd"))}
    for name in sorted(set(ours) & set(theirs)):
        try:
            a, b = ndkgen.Lib(ours[name], need_base=False), ndkgen.Lib(theirs[name], need_base=False)
        except ValueError as e:
            out.append("- %s: cannot read: %s" % (name, e)); bad += 1
            continue
        if a.base != b.base and b.base:
            out.append("- %s: base %s, NDK %s" % (name, a.base, b.base)); bad += 1
        sa = {f.bias: f for f in a.slots()}
        sb = {f.bias: f for f in b.slots()}
        for bias in sorted(set(sa) | set(sb)):
            fa, fb = sa.get(bias), sb.get(bias)
            if fa is None and fb.private or fb is None and fa.private:
                continue                        # a private slot one side leaves unnamed
            if fa is None or fb is None:
                out.append("- %s -%d: %s, NDK %s" % (name, bias, fa and proto(fa), fb and proto(fb))); bad += 1
                continue
            if fa.private and fb.private:
                continue
            if fa.name != fb.name or fa.regs != fb.regs or fa.private != fb.private:
                out.append("- %s -%d: %s, NDK %s" % (name, bias, proto(fa), proto(fb)))
                bad += 1
            elif sig(fa) != sig(fb):
                out.append("- %s -%d: types %s, NDK %s" % (name, bias, proto(fa), proto(fb))); typediff += 1
        va = {f.name for f in a.funcs if f.varargs_of or f.alias_of}
        vb = {f.name for f in b.funcs if (f.varargs_of or f.alias_of) and not f.private}
        for n in sorted(vb - va):
            f = next(f for f in b.funcs if f.name == n)
            out.append("- %s: varargs or alias missing: %s" % (name, proto(f))); bad += 1
        for n in sorted(va - vb):
            out.append("- %s: varargs or alias %s not in the NDK" % (name, n))
    miss = sorted(set(theirs) - set(ours))
    out.append("\nSFDs missing from OpenNDK (%d): %s" % (len(miss), ", ".join(miss) or "none"))
    for name in miss:
        try:
            b = ndkgen.Lib(theirs[name], need_base=False)
        except ValueError as e:
            out.append("- %s: cannot read: %s" % (name, e))
            continue
        out.append("\n%s: base %s, type %s" % (name, b.base, b.basetype))
        for f in b.funcs:
            kind = "varargs " if f.varargs_of else "alias " if f.alias_of else ""
            out.append("- -%d %s%s" % (f.bias, kind, proto(f)))
    out.append("%d SFDs compared: %d differences in names, offsets or registers, %d in types."
               % (len(set(ours) & set(theirs)), bad, typediff))
    text = "\n".join(out) + "\n"
    if report:
        open(report, "w").write(text)
        print(out[-1])
    else:
        print(text)
    sys.exit(1 if bad else 0)


if __name__ == "__main__":
    main()
