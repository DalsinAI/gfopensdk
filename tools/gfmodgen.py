#!/usr/bin/env python3
# Copyright (c) 2026 AmiCradle Team. MIT licence (LICENSE).
# SPDX-License-Identifier: MIT
"""gfmodgen: a native module's gate entries, field tables and header, and the
68k body's GFSG record, from a library's .lvo and .fields
(amicradle-guest docs/design/Native-Modules-ABI.md, sections 4.2, 8 and 12.4;
gfoslib, GF-126).

  gfmodgen.py LVO --lib z.library --version 53 --revision 15 --prefix zm_ \\
              --out DIR/zmod [--fields FILE] [--include H] [--possize N] \\
              [--heavy A,B] [--d1 C] [--ccr D] [--record DIR/zmod.gfsg]
      writes DIR/zmod.h (the prototypes the module's source defines, the
      tables), DIR/zmod.c (one gate entry a slot, the slot table, the field
      tables, the header), DIR/zmod_gfsg.c (the 68k body's GFSG record, to be
      linked into the 68k build) and, with --record, the record's 64 bytes
  gfmodgen.py LVO --sig [--fields FILE]
      prints the LVO signature (SHA-256) and, with --fields, the layout
      signature: what the 68k body's record and the module's header carry

A .lvo line is "-30 Name d0,a0 # class ...": the LVO, the call, its
registers in the fd's order (never A6, the base, or A7, the stack), then a
comment whose first word may be its core class (pure, locked, anchored).
"private" calls have no registers. The four standard slots (-6 Open, -12
Close, -18 Expunge, -24 reserved) are not in a .lvo; they are the module's
LibOpen, LibClose, LibExpunge and LibNull.

Every entry takes its arguments from the registers the line names and puts
the result in D0. The module defines PREFIX<Name>(struct gf_call *c, uint32_t
...) for each call; a register argument is a uint32_t (a guest address or a
value). A call named in --d1 also takes "uint32_t *out_d1" (the second
result, in D1, which starts as the caller's D1); one in --ccr takes "uint16_t *out_ccr"
(the condition codes X N Z V C in its low five bits, starting as the
caller's). The gate writes D1 and the CCR back only for those slots.

A .fields file describes the structures the 68k shares with the library:

  table NAME GTYPE NTYPE GSIZE       e.g. table z_stream struct zs_g struct zs_n 56
    MEMBER OFFSET KIND FLAGS         e.g.   next_in 0 gptr inout

KIND is u8, u16, u32, u64, gptr, bytes, or an earlier table's NAME, with
[N] for an array; FLAGS is in, out or inout. MEMBER is the member's name in
both GTYPE (the 68k layout) and NTYPE (the native copy). The tables become
gft_NAME, in PREFIXtables; the OFFSETs and GSIZE become static assertions
on GTYPE; the layout signature is worked out here, independently of the C,
and the module's own gf_tables_sig must agree with it.
"""
import argparse
import hashlib
import os
import re
import struct
import sys

CLASSES = ("pure", "locked", "anchored")
LINE = re.compile(r"^\s*(-\d+)\s+(\S+)\s*([a-zA-Z0-9,]*)\s*(?:#\s*(.*))?$")
REG = re.compile(r"^([da])([0-7])$")
KINDS = {"u8": (1, 1), "u16": (2, 2), "u32": (4, 4), "u64": (8, 8), "gptr": (0x14, 4), "bytes": (0x20, 1)}
FLAGS = {"in": 1, "out": 2, "inout": 3}
NEST = 0x40


def parse(path):
    calls = []
    with open(path, encoding="utf-8") as f:
        for n, raw in enumerate(f, 1):
            line = raw.rstrip("\n")
            if not line.strip() or line.lstrip().startswith("#"):
                continue
            m = LINE.match(line)
            if not m:
                sys.exit(f"{path}:{n}: not a .lvo line: {line!r}")
            lvo, name, regs, comment = int(m.group(1)), m.group(2), m.group(3).lower(), m.group(4) or ""
            word = comment.split()[0].rstrip(":,") if comment.split() else ""
            cls = word if word in CLASSES else "-"
            rl = [r for r in regs.split(",") if r]
            for r in rl:
                if not REG.match(r):
                    sys.exit(f"{path}:{n}: not a register: {r}")
                if r in ("a6", "a7"):
                    sys.exit(f"{path}:{n}: {name} takes {r}: A6 is the library base and A7 the stack, "
                             "never an argument")
            if len(set(rl)) != len(rl):
                sys.exit(f"{path}:{n}: {name} names a register twice")
            if name == "private" and rl:
                sys.exit(f"{path}:{n}: a private slot takes no registers")
            calls.append({"lvo": lvo, "name": name, "regs": rl, "cls": cls})
    if not calls:
        sys.exit(f"{path}: no calls")
    want = -30
    for c in calls:
        if c["lvo"] != want:
            sys.exit(f"{path}: {c['name']} is at {c['lvo']}, the table needs {want} there")
        want -= 6
    return calls


def signature(calls):
    norm = "\n".join(f"{c['lvo']} {c['name']} {','.join(c['regs'])} {c['cls']}" for c in calls) + "\n"
    return hashlib.sha256(norm.encode()).hexdigest()


def parse_fields(path):
    tables, cur = [], None
    byname = {}
    with open(path, encoding="utf-8") as f:
        for n, raw in enumerate(f, 1):
            line = raw.split("#", 1)[0].strip()
            if not line:
                continue
            w = line.split()
            if w[0] == "table":
                m = re.match(r"^table\s+(\w+)\s+(struct\s+\w+|\w+)\s+(struct\s+\w+|\w+)\s+(\d+)$", line)
                if not m:
                    sys.exit(f"{path}:{n}: table NAME GTYPE NTYPE GSIZE")
                if m.group(1) in byname:
                    sys.exit(f"{path}:{n}: table {m.group(1)} twice")
                cur = {"name": m.group(1), "gtype": m.group(2), "ntype": m.group(3), "gsize": int(m.group(4)),
                       "fields": []}
                tables.append(cur)
                byname[cur["name"]] = cur
                continue
            if cur is None or len(w) != 4:
                sys.exit(f"{path}:{n}: MEMBER OFFSET KIND FLAGS, inside a table")
            member, off, kind, flags = w[0], int(w[1], 0), w[2], w[3]
            km = re.match(r"^(\w+)(?:\[(\d+)\])?$", kind)
            if not km or flags not in FLAGS:
                sys.exit(f"{path}:{n}: kind {kind!r} or flags {flags!r} not known")
            k, count = km.group(1), int(km.group(2) or 1)
            if count < 1:
                sys.exit(f"{path}:{n}: an array of none")
            if k in KINDS:
                code, size, nest = KINDS[k][0], KINDS[k][1], None
            elif k in byname and byname[k] is not cur:
                code, size, nest = NEST, byname[k]["gsize"], byname[k]
            else:
                sys.exit(f"{path}:{n}: {k} is neither a kind nor an earlier table")
            if off < 0 or off + size * count > cur["gsize"]:
                sys.exit(f"{path}:{n}: {member} runs past {cur['name']}'s {cur['gsize']} bytes")
            if size > 1 and off % 2:
                sys.exit(f"{path}:{n}: {member} at an odd offset: the 68k puts it at an even one")
            cur["fields"].append({"member": member, "off": off, "code": code, "flags": FLAGS[flags],
                                  "count": count, "nest": nest})
    if not tables:
        sys.exit(f"{path}: no tables")
    return tables


def fnv(h, v):
    for i in range(4):
        h ^= (v >> (8 * i)) & 0xff
        h = (h * 0x100000001b3) & 0xffffffffffffffff
    return h


def table_sig(h, t):
    h = fnv(h, t["gsize"])
    h = fnv(h, len(t["fields"]))
    for f in t["fields"]:
        h = fnv(h, f["off"])
        h = fnv(h, f["code"] << 16 | f["flags"])
        h = fnv(h, f["count"])
        if f["nest"]:
            h = table_sig(h, f["nest"])
    return h


def layout_sig(tables):
    h = 0xcbf29ce484222325
    for t in tables or []:
        h = table_sig(h, t)
    return h


def reg_c(r):
    m = REG.match(r)
    return f"c->r.{m.group(1)}[{m.group(2)}]"


def kind_c(code):
    return {1: "GF_K_U8", 2: "GF_K_U16", 4: "GF_K_U32", 8: "GF_K_U64", 0x14: "GF_K_GPTR", 0x20: "GF_K_BYTES"}[code]


def flags_c(v):
    return {1: "GF_F_IN", 2: "GF_F_OUT", 3: "GF_F_INOUT"}[v]


def record(nslots, sig, lsig, possize):
    rec = b"GFSG" + struct.pack(">HH", 1, nslots) + bytes.fromhex(sig) + struct.pack(">QH", lsig, possize)
    return rec + bytes(64 - len(rec))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("lvo")
    ap.add_argument("--sig", action="store_true")
    ap.add_argument("--lib")
    ap.add_argument("--version", type=int)
    ap.add_argument("--revision", type=int)
    ap.add_argument("--prefix", default="lm_")
    ap.add_argument("--out")
    ap.add_argument("--fields")
    ap.add_argument("--include", action="append", default=[], help="a header the .c needs (the tables' types)")
    ap.add_argument("--heavy", default="")
    ap.add_argument("--d1", default="")
    ap.add_argument("--ccr", default="")
    ap.add_argument("--possize", type=int, default=34)
    ap.add_argument("--record")
    a = ap.parse_args()
    calls = parse(a.lvo)
    sig = signature(calls)
    tables = parse_fields(a.fields) if a.fields else []
    lsig = layout_sig(tables)
    nslots = len(calls) + 4
    if a.sig:
        print(sig)
        if a.fields:
            print(f"{lsig:016x}")
        return
    if not (a.lib and a.version is not None and a.revision is not None and a.out):
        ap.error("--lib, --version, --revision and --out are needed to generate")
    if not 34 <= a.possize <= 0xffff:
        ap.error("--possize: a base is at least struct Library's 34 bytes")
    names = {c["name"] for c in calls}
    heavy = {x for x in a.heavy.split(",") if x}
    d1 = {x for x in a.d1.split(",") if x}
    ccr = {x for x in a.ccr.split(",") if x}
    for x in heavy | d1 | ccr:
        if x not in names or x == "private":
            sys.exit(f"--heavy/--d1/--ccr: {x} is not a call in {a.lvo}")
    p = a.prefix
    base = os.path.basename(a.out)
    guard = re.sub(r"\W", "_", base).upper() + "_GFMOD_H"
    src = os.path.basename(a.lvo)
    fsrc = os.path.basename(a.fields) if a.fields else None

    def params(c):
        s = "".join(f", uint32_t {r}" for r in c["regs"])
        if c["name"] in d1:
            s += ", uint32_t *out_d1"
        if c["name"] in ccr:
            s += ", uint16_t *out_ccr"
        return s

    h = [f"/* Generated by gfopensdk tools/gfmodgen.py from {src}" + (f" and {fsrc}" if fsrc else "") +
         ": do not edit. */",
         f"#ifndef {guard}", f"#define {guard}", '#include "gfos/gfoslib.h"',
         "#ifdef __cplusplus", 'extern "C" {', "#endif",
         f"uint32_t {p}LibOpen(struct gf_call *c);",
         f"uint32_t {p}LibClose(struct gf_call *c);",
         f"uint32_t {p}LibExpunge(struct gf_call *c);",
         f"uint32_t {p}Init(struct gf_call *c);",
         f"void {p}Fini(struct gf_call *c);"]
    for c in calls:
        if c["name"] != "private":
            h.append(f"uint32_t {p}{c['name']}(struct gf_call *c{params(c)});   /* {c['lvo']} */")
    for t in tables:
        h.append(f"extern const struct gf_table gft_{t['name']};")
    h.append(f"extern const struct gf_table *const {p}tables[{max(len(tables), 1)}];")
    h += [f"#define {p.upper()}LVO_SIG \"{sig}\"", f"#define {p.upper()}LAYOUT_SIG 0x{lsig:016x}ull",
          f"#define {p.upper()}NSLOTS {nslots}", f"#define {p.upper()}POSSIZE {a.possize}",
          "#ifdef __cplusplus", "}", "#endif", "#endif", ""]

    o = [f"/* Generated by gfopensdk tools/gfmodgen.py from {src}" + (f" and {fsrc}" if fsrc else "") +
         ": do not edit.",
         f" * {a.lib} {a.version}.{a.revision}, {nslots} slots, LVO signature {sig},",
         f" * layout signature {lsig:016x} */",
         f'#include "{base}.h"'] + [f'#include "{x}"' for x in a.include] + [""]
    for t in tables:
        o.append(f"GF_SIZE({t['gtype']}, {t['gsize']});")
        for f in t["fields"]:
            o.append(f"GF_LAYOUT({t['gtype']}, {f['member']}, {f['off']});")
        o.append(f"static const struct gf_field gft_{t['name']}_f[] = {{")
        for f in t["fields"]:
            g, n_, m, fl = t["gtype"], t["ntype"], f["member"], flags_c(f["flags"])
            if f["nest"]:
                if f["count"] != 1:
                    sys.exit(f"{fsrc}: {m}: arrays of structures are not supported yet")
                o.append(f"    GF_FLDS({g}, {n_}, {m}, gft_{f['nest']['name']}, {fl}),")
            elif f["count"] != 1:
                o.append(f"    GF_FLDN({g}, {n_}, {m}, {kind_c(f['code'])}, {fl}, {f['count']}),")
            else:
                o.append(f"    GF_FLD({g}, {n_}, {m}, {kind_c(f['code'])}, {fl}),")
        o.append("};")
        o.append(f"const struct gf_table gft_{t['name']} = GF_TABLE({t['name']}, {t['gtype']}, {t['ntype']}, "
                 f"gft_{t['name']}_f);")
    o.append(f"const struct gf_table *const {p}tables[{max(len(tables), 1)}] = {{ " +
             (", ".join(f"&gft_{t['name']}" for t in tables) if tables else "0") + " };")
    o += ["",
          f"static void gfe_LibOpen(struct gf_call *c) {{ c->r.d[0] = {p}LibOpen(c); }}",
          f"static void gfe_LibClose(struct gf_call *c) {{ c->r.d[0] = {p}LibClose(c); }}",
          f"static void gfe_LibExpunge(struct gf_call *c) {{ c->r.d[0] = {p}LibExpunge(c); }}",
          "static void gfe_LibNull(struct gf_call *c) { c->r.d[0] = 0; }"]
    for i, c in enumerate(calls):
        if c["name"] == "private":
            o.append(f"static void gfe_private_{i}(struct gf_call *c) {{ c->r.d[0] = 0; }}")
            continue
        args = "".join(f", {reg_c(r)}" for r in c["regs"])
        if c["name"] in d1 or c["name"] in ccr:
            body = []
            if c["name"] in d1:
                body.append("uint32_t out_d1 = c->r.d[1];")
                args += ", &out_d1"
            if c["name"] in ccr:
                body.append("uint16_t out_ccr = c->r.sr & 0x1f;")
                args += ", &out_ccr"
            body.append(f"c->r.d[0] = {p}{c['name']}(c{args});")
            if c["name"] in d1:
                body.append("c->r.d[1] = out_d1;")
            if c["name"] in ccr:
                body.append("c->r.sr = (uint16_t)((c->r.sr & ~0x1fu) | (out_ccr & 0x1fu));")
            o.append(f"static void gfe_{c['name']}(struct gf_call *c) {{ " + " ".join(body) + " }")
        else:
            o.append(f"static void gfe_{c['name']}(struct gf_call *c) {{ c->r.d[0] = {p}{c['name']}(c{args}); }}")
    o += ["", "static const struct gf_slot gfm_slots[] = {",
          '    { -6, 0, 0, gfe_LibOpen, "Open" },', '    { -12, 0, 0, gfe_LibClose, "Close" },',
          '    { -18, 0, 0, gfe_LibExpunge, "Expunge" },', '    { -24, 0, 0, gfe_LibNull, "Reserved" },']
    for i, c in enumerate(calls):
        fn = f"gfe_private_{i}" if c["name"] == "private" else f"gfe_{c['name']}"
        mark = "GF_MARK_HEAVY" if c["name"] in heavy else "GF_MARK_LIGHT"
        fl = " | ".join(x for x, s in (("GF_SLOT_D1", d1), ("GF_SLOT_CCR", ccr)) if c["name"] in s) or "0"
        o.append(f'    {{ {c["lvo"]}, {mark}, {fl}, {fn}, "{c["name"]}" }},')
    sigbytes = ", ".join(f"0x{sig[i:i + 2]}" for i in range(0, 64, 2))
    o += ["};", "",
          "/* the header: the loader finds it by its section (.gfmod) or this symbol */",
          '__attribute__((visibility("default"))) GF_SECTION const struct gf_mod gfmod_header = {',
          "    { 'G', 'F', 'M', 'D' }, GF_GATE_ABI, GFOS_CPU, GFOS_NATIVE_ORDER, { 0, 0, 0 },",
          f'    "{a.lib}", {a.version}, {a.revision}, {nslots}, {a.possize},',
          f"    {{ {sigbytes} }},",
          f"    {len(tables)}, {p}tables,",
          f"    gfm_slots, {p}Init, {p}Fini", "};", ""]
    rec = record(nslots, sig, lsig, a.possize)
    g = [f"/* Generated by gfopensdk tools/gfmodgen.py from {src}" + (f" and {fsrc}" if fsrc else "") +
         ": do not edit.",
         f" * {a.lib}'s GFSG record, for its 68k build: 64 bytes in a section of their own that the",
         " * 68k code never reads (Native-Modules-ABI.md 8). The loader compares the module's header with it. */",
         '__attribute__((section(".gfsg"), used)) const unsigned char gfsg_record[64] = {']
    for i in range(0, 64, 16):
        g.append("    " + ", ".join(f"0x{b:02x}" for b in rec[i:i + 16]) + ",")
    g += ["};", ""]
    os.makedirs(os.path.dirname(os.path.abspath(a.out)), exist_ok=True)
    for path, text in ((a.out + ".h", h), (a.out + ".c", o), (a.out + "_gfsg.c", g)):
        with open(path, "w", encoding="utf-8") as f:
            f.write("\n".join(text))
    if a.record:
        with open(a.record, "wb") as f:
            f.write(rec)
    print(f"gfmodgen: {a.lib} {a.version}.{a.revision}: {nslots} slots, {len(heavy)} heavy, {len(tables)} tables, "
          f"LVO sig {sig[:16]}, layout sig {lsig:016x}")


if __name__ == "__main__":
    main()
