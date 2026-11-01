#!/usr/bin/env python3
# Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
"""Measure a header set's structures and constants, and compare two sets.

    layouts.py dump INCLUDE_DIR OUT.json      (CC, READELF from the environment)
    layouts.py measure INCLUDE_DIR PROBE.json OUT.json   (CC from the environment)
    layouts.py compare OURS.json THEIRS.json  [--report FILE [--detail THEIRS_DWARF.json]]

dump compiles every header under INCLUDE_DIR (leaving out proto/, inline/,
pragmas/ and clib/) with an ELF m68k GCC and -g, reads each structure's
size and each field's offset and size back from the debug information, and
evaluates every constant the headers #define. Nothing is run, so any m68k
ELF GCC will do: Ubuntu's m68k-linux-gnu-gcc, or the aros68k stove's.

compare lists every structure, field and constant whose size, offset or
value differs, and what one set has that the other lacks. It exits 1 when
anything both sets have differs.

Used by compare_ndk.sh to check OpenNDK against a vendor NDK installed on
the same machine; the vendor's files are only read, never copied.
"""
import json
import os
import re
import subprocess
import sys
import tempfile

SKIP_DIRS = ("proto", "inline", "pragmas", "pragma", "clib", "ppcinline", "ppcpragmas", "lvo")
CC = os.environ.get("CC", "m68k-linux-gnu-gcc")
READELF = os.environ.get("READELF", "readelf")


def headers(root):
    out = []
    for d, dirs, files in os.walk(root):
        rel = os.path.relpath(d, root)
        if rel.split(os.sep)[0] in SKIP_DIRS:
            continue
        for f in files:
            if f.endswith(".h"):
                out.append(os.path.normpath(os.path.join(rel, f)).replace(os.sep, "/"))
    return sorted(out)


def cflags(root):
    inc = subprocess.run([CC, "-print-file-name=include"], capture_output=True, text=True).stdout.strip()
    shim = os.path.join(os.path.dirname(os.path.abspath(__file__)), "shim")
    return ["-nostdinc", "-ffreestanding", "-isystem", inc, "-idirafter", shim, "-I", root, "-w",
            "-fomit-frame-pointer"] \
        + os.environ.get("LAYOUT_CFLAGS", "").split()


def usable(root, hs, tmp, errors=None):
    """The headers that compile on their own (a vendor set may have some
    that don't); each is tried alone. The first error of each that doesn't
    goes into errors."""
    ok = []
    src = os.path.join(tmp, "one.c")
    for h in hs:
        open(src, "w").write("#include <%s>\n" % h)
        r = subprocess.run([CC] + cflags(root) + ["-fsyntax-only", "-fno-diagnostics-show-caret", src],
                           capture_output=True, text=True)
        if r.returncode == 0:
            ok.append(h)
        elif errors is not None:
            first = next((l for l in r.stderr.splitlines() if "error" in l), r.stderr.strip()[:200])
            errors[h] = first.replace(root + "/", "")
    return ok


def together(root, hs, tmp):
    """Drop headers until the rest compile in one unit."""
    src = os.path.join(tmp, "all.c")
    hs = list(hs)
    while True:
        open(src, "w").write("".join("#include <%s>\n" % h for h in hs))
        r = subprocess.run([CC] + cflags(root) + ["-fsyntax-only", src], capture_output=True, text=True)
        if r.returncode == 0:
            return hs
        bad = set(re.findall(r"In file included from [^:]*all\.c:(\d+)", r.stderr))
        bad |= set(re.findall(r"all\.c:(\d+):", r.stderr))
        if not bad:
            raise SystemExit("cannot compile the headers together:\n" + r.stderr[:3000])
        drop = sorted(int(b) for b in bad)[-1] - 1
        print("  left out of the unit: %s" % hs[drop], file=sys.stderr)
        del hs[drop]


# ------------------------------------------------------------------ DWARF

def parse_dies(text):
    dies, stack = {}, []
    cur = None
    for line in text.splitlines():
        m = re.match(r"\s*<(\d+)><([0-9a-f]+)>: Abbrev Number: (\d+)(?: \((\w+)\))?", line)
        if m:
            depth, off, tag = int(m.group(1)), int(m.group(2), 16), m.group(4)
            if tag is None:                      # end of a list of children
                continue
            cur = {"tag": tag, "attrs": {}, "children": [], "off": off}
            dies[off] = cur
            del stack[depth:]
            if stack:
                stack[-1]["children"].append(off)
            stack.append(cur)
            continue
        m = re.match(r"\s*<[0-9a-f]+>\s+(DW_AT_\w+)\s*:\s*(.*)$", line)
        if m and cur is not None:
            name, val = m.group(1), m.group(2).strip()
            if name == "DW_AT_name":
                val = val.split(": ")[-1] if val.startswith("(") else val
            cur["attrs"][name] = val
    return dies


def ref(val):
    m = re.search(r"<0x([0-9a-f]+)>", val or "")
    return int(m.group(1), 16) if m else None


def num(val):
    m = re.match(r"(-?\d+|0x[0-9a-f]+)", (val or "").strip())
    return int(m.group(1), 0) if m else None


def type_size(dies, off, seen=0):
    d = dies.get(off)
    if d is None or seen > 20:
        return None
    a = d["attrs"]
    if "DW_AT_byte_size" in a:
        return num(a["DW_AT_byte_size"])
    if d["tag"] == "DW_TAG_pointer_type":
        return 4
    if d["tag"] == "DW_TAG_array_type":
        n = type_size(dies, ref(a.get("DW_AT_type")), seen + 1)
        for c in d["children"]:
            ca = dies[c]["attrs"]
            if "DW_AT_count" in ca:
                cnt = num(ca["DW_AT_count"])
            elif "DW_AT_upper_bound" in ca:
                cnt = num(ca["DW_AT_upper_bound"]) + 1
            else:
                cnt = 0
            n = (n or 0) * cnt
        return n
    if "DW_AT_type" in a:
        return type_size(dies, ref(a["DW_AT_type"]), seen + 1)
    return None


def members(dies, d, prefix=""):
    out = []
    for c in d["children"]:
        m = dies[c]
        if m["tag"] != "DW_TAG_member":
            continue
        a = m["attrs"]
        off = num(a.get("DW_AT_data_member_location", "0")) or 0
        t = ref(a.get("DW_AT_type"))
        name = a.get("DW_AT_name")
        if name is None:                         # an anonymous struct or union
            inner = dies.get(t)
            if inner:
                for n, o, s in members(dies, inner, prefix):
                    out.append((n, o + off, s))
            continue
        out.append((prefix + name, off, type_size(dies, t)))
    return out


def structs(obj):
    text = subprocess.run([READELF, "--debug-dump=info", obj], capture_output=True, text=True).stdout
    dies = parse_dies(text)
    out = {}
    for d in dies.values():
        if d["tag"] not in ("DW_TAG_structure_type", "DW_TAG_union_type"):
            continue
        a = d["attrs"]
        if "DW_AT_name" not in a or "DW_AT_declaration" in a:
            continue
        key = ("union " if d["tag"] == "DW_TAG_union_type" else "struct ") + a["DW_AT_name"]
        out[key] = {"size": num(a.get("DW_AT_byte_size")),
                    "members": [[n, o, s] for n, o, s in members(dies, d)]}
    return out


# --------------------------------------------------------------- constants

def evaluate(root, src, exprs, tmp):
    """The value of each constant expression in exprs (key -> C text) with
    src included, read back from the compiler's assembler output, so any
    m68k GCC will do and nothing is run. Expressions that don't compile
    are left out."""
    keys = sorted(exprs)
    ev = os.path.join(tmp, "ev.c")
    asm = os.path.join(tmp, "ev.s")
    while True:
        body = ["#include \"%s\"" % src, "void __openndk_values(void) {"]
        for k in keys:
            body.append("__asm__ volatile (\"#OPENNDK %s %%0\" :: \"i\" ((long)(%s)));" % (k, exprs[k]))
        body.append("}")
        open(ev, "w").write("\n".join(body) + "\n")
        r = subprocess.run([CC] + cflags(root) + ["-O0", "-S", ev, "-o", asm], capture_output=True, text=True)
        if r.returncode == 0:
            break
        bad = {int(x) - 3 for x in re.findall(r"ev\.c:(\d+):\d+:", r.stderr)}
        if not bad:
            raise SystemExit("cannot evaluate the constants:\n" + r.stderr[:3000])
        keys = [k for i, k in enumerate(keys) if i not in bad]
    out = {}
    for line in open(asm):
        m = re.search(r"#OPENNDK (\S+) #?(-?\d+)", line)
        if m:
            out[m.group(1)] = int(m.group(2)) & 0xFFFFFFFF
    return out


def macros(root, src, tmp):
    empty = os.path.join(tmp, "empty.c")
    open(empty, "w").write("")
    def defs(path):
        r = subprocess.run([CC] + cflags(root) + ["-E", "-dM", path], capture_output=True, text=True)
        out = {}
        for line in r.stdout.splitlines():
            m = re.match(r"#define (\w+) (.+)$", line)
            if m:
                out[m.group(1)] = m.group(2)
        return out
    base = defs(empty)
    names = [n for n, v in defs(src).items()
             if n not in base and '"' not in v and not re.search(r"\b(sizeof|offsetof)\b", v)
             and not n.endswith("_H") and not n.endswith("_I")]
    return evaluate(root, src, {n: n for n in names}, tmp)


def struct_names(src_text):
    return set(re.findall(r"\b(struct|union)\s+(\w+)\s*\{", src_text))


def where(root, src, tmp):
    """The header each #define and each structure comes from, by the
    preprocessor's line markers."""
    r = subprocess.run([CC] + cflags(root) + ["-E", "-dD", src], capture_output=True, text=True).stdout
    cur, consts, structs_ = None, {}, {}
    pre = root.rstrip("/") + "/"
    for line in r.splitlines():
        m = re.match(r'# \d+ "([^"]+)"', line)
        if m:
            cur = m.group(1)[len(pre):] if m.group(1).startswith(pre) else None
            continue
        if cur is None:
            continue
        m = re.match(r"#define (\w+)", line)
        if m:
            consts.setdefault(m.group(1), cur)
            continue
        for kw, n in re.findall(r"\b(struct|union)\s+(\w+)\s*\{", line):
            structs_.setdefault("%s %s" % (kw, n), cur)
    return consts, structs_


def unit(root, tmp):
    errors = {}
    hs = together(root, usable(root, headers(root), tmp, errors), tmp)
    src = os.path.join(tmp, "all.c")
    open(src, "w").write("".join("#include <%s>\n" % h for h in hs))
    return hs, src, errors


def dump(root, dest):
    """Structures from the debug information (needs an ELF GCC)."""
    root = os.path.abspath(root)
    with tempfile.TemporaryDirectory() as tmp:
        hs, src, errors = unit(root, tmp)
        obj = os.path.join(tmp, "all.o")
        subprocess.run([CC] + cflags(root) + ["-g", "-gdwarf-4", "-fno-eliminate-unused-debug-types",
                                              "-c", src, "-o", obj], check=True)
        data = {"headers": hs, "errors": errors, "structs": structs(obj), "constants": macros(root, src, tmp)}
        data["const_headers"], data["struct_headers"] = where(root, src, tmp)
    save(data, dest)


def measure(root, probe_path, dest):
    """Structures by sizeof and offsetof, for every structure and field
    named in a dump (probe), with any m68k GCC: the vendor NDK is measured
    this way with the compiler it was written for. Structures the probe
    doesn't name are listed with their size only."""
    root = os.path.abspath(root)
    probe = json.load(open(probe_path))
    with tempfile.TemporaryDirectory() as tmp:
        hs, src, errors = unit(root, tmp)
        pre = subprocess.run([CC] + cflags(root) + ["-E", src], capture_output=True, text=True).stdout
        exprs = {}
        names = {k for k in probe["structs"]} | {"%s %s" % kw for kw in struct_names(pre)}
        for k in names:
            exprs["S:%s" % k.replace(" ", ":")] = "sizeof(%s)" % k
            for n, _, _ in probe["structs"].get(k, {}).get("members", []):
                if re.match(r"^\w+$", n):
                    exprs["O:%s:%s" % (k.replace(" ", ":"), n)] = "__builtin_offsetof(%s, %s)" % (k, n)
                    exprs["Z:%s:%s" % (k.replace(" ", ":"), n)] = "sizeof(((%s *)0)->%s)" % (k, n)
        vals = evaluate(root, src, exprs, tmp)
        st = {}
        for key, v in vals.items():
            if key.startswith("S:"):
                st.setdefault(key[2:].replace(":", " "), {"size": None, "members": []})["size"] = v
        for k in st:
            kk = k.replace(" ", ":")
            for n, _, _ in probe["structs"].get(k, {}).get("members", []):
                if "O:%s:%s" % (kk, n) in vals:
                    st[k]["members"].append([n, vals["O:%s:%s" % (kk, n)], vals.get("Z:%s:%s" % (kk, n))])
        data = {"headers": hs, "errors": errors, "structs": st, "constants": macros(root, src, tmp)}
        data["const_headers"], data["struct_headers"] = where(root, src, tmp)
    save(data, dest)


def save(data, dest):
    json.dump(data, open(dest, "w"), indent=0, sort_keys=True)
    print("%s: %d headers (%d not compiling alone), %d structures, %d constants" % (
        dest, len(data["headers"]), len(data["errors"]), len(data["structs"]), len(data["constants"])))


def compare(ours_path, theirs_path, report=None, detail_path=None):
    ours, theirs = json.load(open(ours_path)), json.load(open(theirs_path))
    detail = json.load(open(detail_path))["structs"] if detail_path and os.path.exists(detail_path) else {}
    differing = set()
    lines, bad = [], 0
    def say(s):
        lines.append(s)
    say("# OpenNDK against the vendor NDK\n")
    say("## Differences in what both have\n")
    for k in sorted(set(ours["structs"]) & set(theirs["structs"])):
        a, b = ours["structs"][k], theirs["structs"][k]
        if a["size"] != b["size"]:
            say("- %s: size %s, NDK %s" % (k, a["size"], b["size"])); bad += 1; differing.add(k)
        am = {m[0]: m for m in a["members"]}
        bm = {m[0]: m for m in b["members"]}
        for n in sorted(set(am) & set(bm), key=lambda n: bm[n][1]):
            if am[n][1:] != bm[n][1:]:
                differing.add(k)
                say("- %s.%s: offset %s size %s, NDK offset %s size %s" % (k, n, am[n][1], am[n][2], bm[n][1], bm[n][2])); bad += 1
        for n in sorted(set(bm) - set(am), key=lambda n: bm[n][1]):
            say("- %s.%s: missing (NDK offset %s)" % (k, n, bm[n][1])); bad += 1; differing.add(k)
        for n in sorted(set(am) - set(bm), key=lambda n: am[n][1]):
            say("- %s.%s: not in the NDK (offset %s)" % (k, n, am[n][1])); bad += 1; differing.add(k)
    for k in sorted(set(ours["constants"]) & set(theirs["constants"])):
        if ours["constants"][k] != theirs["constants"][k]:
            say("- %s = 0x%x, NDK 0x%x" % (k, ours["constants"][k], theirs["constants"][k])); bad += 1
    say("\n## Missing from OpenNDK\n")
    say("Headers: " + (", ".join(sorted(set(theirs["headers"]) - set(ours["headers"]))) or "none"))
    miss = sorted(set(theirs["structs"]) - set(ours["structs"]))
    say("\nStructures (%d): %s" % (len(miss), ", ".join("%s (%s bytes)" % (k, theirs["structs"][k]["size"]) for k in miss) or "none"))
    missc = sorted(set(theirs["constants"]) - set(ours["constants"]))
    say("\nConstants (%d), by the NDK header that has them:" % len(missc))
    byh = {}
    for k in missc:
        byh.setdefault(theirs.get("const_headers", {}).get(k, "?"), []).append(k)
    for h in sorted(byh):
        say("- %s: %s" % (h, ", ".join("%s=0x%x" % (k, theirs["constants"][k]) for k in byh[h])))
    if detail:
        say("\n## The NDK's layout of each structure that differs or is missing\n")
        sh = theirs.get("struct_headers", {})
        for k in sorted(differing | set(miss)):
            d = detail.get(k)
            if not d:
                say("- %s (%s): no layout read" % (k, sh.get(k, "?")))
                continue
            say("- %s (%s), %s bytes: %s" % (k, sh.get(k, "?"), d["size"],
                ", ".join("%s@%s/%s" % (n, o, z) for n, o, z in d["members"])))
    extra = sorted(set(ours["constants"]) - set(theirs["constants"]))
    say("\n## In OpenNDK only\n\nConstants (%d): %s" % (len(extra), ", ".join(extra) if len(extra) <= 400 else "(too many to list)"))
    for side, d in (("OpenNDK", ours), ("NDK", theirs)):
        errs = d.get("errors", {})
        say("\n## %s headers that don't compile alone (%d)\n" % (side, len(errs)))
        for h in sorted(errs)[:60]:
            say("- %s: %s" % (h, errs[h]))
    shared = len(set(ours["structs"]) & set(theirs["structs"])), len(set(ours["constants"]) & set(theirs["constants"]))
    say("\n%d structures and %d constants compared, %d differences." % (shared[0], shared[1], bad))
    text = "\n".join(lines) + "\n"
    if report:
        open(report, "w").write(text)
    print(text if not report else lines[-1])
    return bad


def main():
    if len(sys.argv) >= 4 and sys.argv[1] == "dump":
        dump(sys.argv[2], sys.argv[3])
    elif len(sys.argv) >= 5 and sys.argv[1] == "measure":
        measure(sys.argv[2], sys.argv[3], sys.argv[4])
    elif len(sys.argv) >= 4 and sys.argv[1] == "compare":
        rep = sys.argv[5] if len(sys.argv) > 5 and sys.argv[4] == "--report" else None
        det = sys.argv[7] if len(sys.argv) > 7 and sys.argv[6] == "--detail" else None
        sys.exit(1 if compare(sys.argv[2], sys.argv[3], rep, det) else 0)
    else:
        print(__doc__)
        sys.exit(2)


if __name__ == "__main__":
    main()
