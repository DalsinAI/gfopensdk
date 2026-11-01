#!/usr/bin/env python3
# Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
# SPDX-License-Identifier: MIT
"""Make OS 4 style interfaces for AmigaOS 3.2 libraries from their SFD files.

    tools/os4ifgen.py OUTDIR file_lib.sfd [more_lib.sfd ...]

For each SFD file (exec_lib.sfd, dos_lib.sfd, ...) it writes:

    OUTDIR/include/interfaces/<name>.h  struct <Name>IFace, one member a function
    OUTDIR/include/proto/<name>.h       the base, the interface and, with
                                        __USE_INLINE__, OS 4's bare-name macros
    OUTDIR/src/<name>_iface.c           the members: small functions that make
                                        the classic call through the NDK's inlines
    OUTDIR/src/<name>_ivar.c            the I<Name> pointer, alone so a program
                                        that defines its own pointer still links
    OUTDIR/src/os4c_registry.c          the table GetInterface() looks names up in

The NDK's SFD files are the user's (as the NDK is); this tool only reads them,
so nothing from the NDK is shipped with the SDK. Calls OS 4 has and OS 3.2 has
not (AllocSysObject, ExamineDir, Strlcpy, ...) are added from EXTRAS below and
implemented in Lib/os4compat/src.
"""
import os, re, sys

# Interface names as OS 4 spells them, by the SFD file's prefix.
NAMES = {
    "exec": "Exec", "dos": "DOS", "graphics": "Graphics", "intuition": "Intuition",
    "utility": "Utility", "gadtools": "GadTools", "asl": "Asl", "icon": "Icon",
    "wb": "Workbench", "commodities": "Commodities", "layers": "Layers",
    "locale": "Locale", "keymap": "Keymap", "datatypes": "DataTypes",
    "diskfont": "Diskfont", "iffparse": "IFFParse", "rexxsyslib": "RexxSys",
    "expansion": "Expansion", "timer": "Timer", "input": "Input",
    "console": "Console", "lowlevel": "LowLevel", "nonvolatile": "NonVolatile",
    "amigaguide": "AmigaGuide", "bullet": "Bullet", "translator": "Translator",
    "battclock": "BattClock", "battmem": "BattMem", "cybergraphics": "CyberGFX",
    "bsdsocket": "Socket", "openrtg": "OpenRTG", "listbrowser": "ListBrowser",
    "chooser": "Chooser", "clicktab": "ClickTab", "layout": "Layout",
    "window": "Window", "requester": "Requester", "texteditor": "TextEditor",
    "speedbar": "SpeedBar", "label": "Label", "bitmap": "BitMap",
}

# OS 4 calls with no OS 3.2 equal: (member declaration, implementation).
# A member whose name is also in the SFD replaces the generated one.
EXTRAS = {
    "exec": [
        ("struct Library *(*OpenLibrary)(CONST_STRPTR name, ULONG version)", "os4c_OpenLibrary"),
        ("APTR (*AllocVec)(ULONG size, ULONG flags)", "os4c_AllocVec"),
        ("APTR (*AllocMem)(ULONG size, ULONG flags)", "os4c_AllocMem"),
        ("struct Interface *(*GetInterface)(struct Library *library, CONST_STRPTR name, ULONG version, struct TagItem *tags)", "os4c_GetInterface"),
        ("VOID (*DropInterface)(struct Interface *iface)", "os4c_DropInterface"),
        ("APTR (*AllocSysObject)(ULONG type, struct TagItem *tags)", "os4c_AllocSysObject"),
        ("APTR (*AllocSysObjectTags)(ULONG type, ...)", "os4c_AllocSysObjectTags"),
        ("VOID (*FreeSysObject)(ULONG type, APTR object)", "os4c_FreeSysObject"),
        # ASOPOOL_Protected pools take a lock in these
        ("APTR (*AllocPooled)(APTR poolHeader, ULONG memSize)", "os4c_AllocPooled"),
        ("VOID (*FreePooled)(APTR poolHeader, APTR memory, ULONG memSize)", "os4c_FreePooled"),
        ("APTR (*AllocVecPooled)(APTR poolHeader, ULONG memSize)", "os4c_AllocVecPooled"),
        ("VOID (*FreeVecPooled)(APTR poolHeader, APTR memory)", "os4c_FreeVecPooled"),
        ("VOID (*DeletePool)(APTR poolHeader)", "os4c_DeletePool"),
        ("APTR (*AllocVecTagList)(ULONG size, struct TagItem *tags)", "os4c_AllocVecTagList"),
        ("APTR (*AllocVecTags)(ULONG size, ...)", "os4c_AllocVecTags"),
        ("VOID (*DebugPrintF)(CONST_STRPTR format, ...)", "os4c_DebugPrintF"),
        ("VOID (*NewList)(struct List *list)", "os4c_NewList"),
        ("VOID (*NewMinList)(struct MinList *list)", "os4c_NewMinList"),
        ("struct Node *(*GetHead)(struct List *list)", "os4c_GetHead"),
        ("struct Node *(*GetTail)(struct List *list)", "os4c_GetTail"),
        ("struct Node *(*GetSucc)(struct Node *node)", "os4c_GetSucc"),
        ("struct Node *(*GetPred)(struct Node *node)", "os4c_GetPred"),
        ("VOID (*MutexObtain)(APTR mutex)", "os4c_MutexObtain"),
        ("BOOL (*MutexAttempt)(APTR mutex)", "os4c_MutexAttempt"),
        ("VOID (*MutexRelease)(APTR mutex)", "os4c_MutexRelease"),
    ],
    "dos": [
        ("BPTR (*FOpen)(CONST_STRPTR name, LONG mode, LONG bufsize)", "os4c_FOpen"),
        ("LONG (*FClose)(BPTR file)", "os4c_FClose"),
        ("LONG (*ChangeFilePosition)(BPTR file, int64 position, LONG mode)", "os4c_ChangeFilePosition"),
        ("int64 (*GetFilePosition)(BPTR file)", "os4c_GetFilePosition"),
        ("int64 (*GetFileSize)(BPTR file)", "os4c_GetFileSize"),
        ("struct ExamineData *(*ExamineObject)(struct TagItem *tags)", "os4c_ExamineObject"),
        ("struct ExamineData *(*ExamineObjectTags)(Tag tag1, ...)", "os4c_ExamineObjectTags"),
        ("APTR (*ObtainDirContext)(struct TagItem *tags)", "os4c_ObtainDirContext"),
        ("APTR (*ObtainDirContextTags)(Tag tag1, ...)", "os4c_ObtainDirContextTags"),
        ("struct ExamineData *(*ExamineDir)(APTR context)", "os4c_ExamineDir"),
        ("VOID (*ReleaseDirContext)(APTR context)", "os4c_ReleaseDirContext"),
        ("VOID (*FreeDosObject)(ULONG type, APTR object)", "os4c_FreeDosObject"),
    ],
    "utility": [
        ("ULONG (*Strlcpy)(STRPTR dst, CONST_STRPTR src, ULONG size)", "os4c_Strlcpy"),
        ("ULONG (*Strlcat)(STRPTR dst, CONST_STRPTR src, ULONG size)", "os4c_Strlcat"),
        ("LONG (*SNPrintf)(STRPTR buffer, ULONG size, CONST_STRPTR format, ...)", "os4c_SNPrintf"),
        ("LONG (*VSNPrintf)(STRPTR buffer, ULONG size, CONST_STRPTR format, va_list args)", "os4c_VSNPrintf"),
        ("STRPTR (*ASPrintf)(CONST_STRPTR format, ...)", "os4c_ASPrintf"),
        ("STRPTR (*VASPrintf)(CONST_STRPTR format, va_list args)", "os4c_VASPrintf"),
    ],
    "graphics": [
        ("struct BitMap *(*AllocBitMapTagList)(ULONG width, ULONG height, ULONG depth, struct TagItem *tags)", "os4c_AllocBitMapTagList"),
        ("struct BitMap *(*AllocBitMapTags)(ULONG width, ULONG height, ULONG depth, ...)", "os4c_AllocBitMapTags"),
        ("LONG (*BltBitMapTagList)(struct TagItem *tags)", "os4c_BltBitMapTagList"),
        ("LONG (*BltBitMapTags)(Tag tag1, ...)", "os4c_BltBitMapTags"),
        ("ULONG (*CompositeTagList)(ULONG op, struct BitMap *src, struct BitMap *dst, struct TagItem *tags)", "os4c_CompositeTagList"),
        ("ULONG (*CompositeTags)(ULONG op, struct BitMap *src, struct BitMap *dst, ...)", "os4c_CompositeTags"),
    ],
    "intuition": [
        ("ULONG (*IDoMethodA)(Object *obj, Msg msg)", "os4c_IDoMethodA"),
        ("ULONG (*IDoMethod)(Object *obj, ULONG methodID, ...)", "os4c_IDoMethod"),
        ("ULONG (*IDoSuperMethodA)(struct IClass *cl, Object *obj, Msg msg)", "os4c_IDoSuperMethodA"),
        ("ULONG (*IDoSuperMethod)(struct IClass *cl, Object *obj, ULONG methodID, ...)", "os4c_IDoSuperMethod"),
        ("ULONG (*ICoerceMethodA)(struct IClass *cl, Object *obj, Msg msg)", "os4c_ICoerceMethodA"),
    ],
}

PROTO_RE = re.compile(r"^(.*?)\b(\w+)\s*\((.*)\)\s*\(([^)]*)\)\s*$")
MEMBER_RE = re.compile(r"^(.*?)\(\*(\w+)\)\((.*)\)$")


def split_params(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip())
            cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    if out in (["void"], ["VOID"]):
        return []
    return out


def param_name(p):
    m = re.search(r"\(\s*\*\s*(\w+)\s*\)", p)
    if m:
        return m.group(1)
    return re.findall(r"\w+", p)[-1]


def param_type(p):
    """The parameter's type with its name taken out, for casts."""
    name = param_name(p)
    if re.search(r"\(\s*\*\s*%s\s*\)" % name, p):
        return re.sub(r"\(\s*\*\s*%s\s*\)" % name, "(*)", p).strip()
    return re.sub(r"\b%s\s*$" % name, "", p).strip()


def parse_sfd(path):
    lib = {"funcs": [], "includes": [], "base": None, "basetype": None, "libname": None}
    public, pending = True, None
    last = None
    held = ""
    for raw in open(path, encoding="latin-1"):
        line = raw.strip()
        if not line or line.startswith("*"):
            continue
        # a prototype can run over several lines (exec's SetFunction): join
        # them until the parentheses balance and the register list is there
        if held:
            line, held = held + " " + line, ""
        if not line.startswith("==") and (line.count("(") != line.count(")") or not line.endswith(")")):
            held = line
            continue
        if line.startswith("=="):
            key, _, val = line[2:].partition(" ")
            val = val.strip()
            if key == "base":
                lib["base"] = val.lstrip("_")
            elif key == "basetype":
                lib["basetype"] = val
            elif key == "libname":
                lib["libname"] = val
            elif key == "include":
                lib["includes"].append(val)
            elif key == "public":
                public = True
            elif key == "private":
                public = False
            elif key in ("varargs", "alias"):
                pending = key
            elif key == "end":
                break
            continue
        m = PROTO_RE.match(line)
        if not m:
            continue
        ret, name, params = m.group(1).strip(), m.group(2), split_params(m.group(3))
        kind, pending = pending, None
        if not public:
            continue
        f = {"ret": ret, "name": name, "params": params, "kind": kind or "normal", "base": None}
        if kind in ("varargs", "alias"):
            if last is None:
                continue
            f["base"] = last
        else:
            last = f
        lib["funcs"].append(f)
    return lib


def is_void(ret):
    return ret.replace(" ", "") in ("VOID", "void")


def wrapper(prefix, f):
    """A member's function: the classic call through the NDK's inline macro."""
    w = "os4c_%s_%s" % (prefix, f["name"])
    ret, rv = f["ret"], "" if is_void(f["ret"]) else "return "
    if f["kind"] == "normal":
        args = ", ".join(param_name(p) for p in f["params"])
        decl = ", ".join(f["params"]) or "void"
        return w, "static %s %s(%s)\n{\n\t%s%s(%s);\n}\n" % (ret, w, decl, rv, f["name"], args)
    base = f["base"]
    named = [p for p in f["params"] if p != "..."]
    if f["kind"] == "alias":
        if len(named) != len(base["params"]):
            return None, None
        args = ", ".join(param_name(p) for p in named)
        decl = ", ".join(named) or "void"
        return w, "static %s %s(%s)\n{\n\t%s%s(%s);\n}\n" % (ret, w, decl, rv, base["name"], args)
    # varargs: the stack holds the variable arguments in a row, as amiga.lib's stubs assume
    k, n = len(named), len(base["params"])
    decl = ", ".join(named + ["..."])
    cast = param_type(base["params"][-1]) if n else "APTR"
    if k == n and k > 0:
        args = [param_name(p) for p in named[:-1]] + ["(%s)&%s" % (cast, param_name(named[-1]))]
        return w, "static %s %s(%s)\n{\n\t%s%s(%s);\n}\n" % (ret, w, decl, rv, base["name"], ", ".join(args))
    if k == n - 1 and k > 0:
        args = [param_name(p) for p in named] + ["(%s)ap" % cast]
        body = "\tva_list ap;\n"
        if not is_void(ret):
            body += "\t%s r;\n" % ret
        body += "\tva_start(ap, %s);\n" % param_name(named[-1])
        body += "\t%s%s(%s);\n" % ("" if is_void(ret) else "r = ", base["name"], ", ".join(args))
        body += "\tva_end(ap);\n"
        if not is_void(ret):
            body += "\treturn r;\n"
        return w, "static %s %s(%s)\n{\n%s}\n" % (ret, w, decl, body)
    return None, None


def member(ret, name, params):
    return "\t%s (*%s)(%s);\n" % (ret, name, ", ".join(params) or "void")


def generate(out, sfd):
    prefix = re.sub(r"(_lib)?\.sfd$", "", os.path.basename(sfd))
    nice = NAMES.get(prefix, prefix[:1].upper() + prefix[1:])
    iface, ivar = nice + "IFace", "I" + nice
    lib = parse_sfd(sfd)
    if not lib["base"] or not lib["libname"]:
        sys.exit("%s: no ==base or ==libname" % sfd)
    guard = prefix.upper()
    extras = EXTRAS.get(prefix, [])
    replaced = {MEMBER_RE.match(d).group(2) for d, _ in extras}
    funcs = [f for f in lib["funcs"] if f["name"] not in replaced]
    # names can repeat (an alias of a varargs name); keep the first
    seen, uniq = set(), []
    for f in funcs:
        if f["name"] not in seen:
            seen.add(f["name"])
            uniq.append(f)
    funcs = uniq
    incs = "".join("#include %s\n" % i for i in lib["includes"])

    members, bodies, inits = [], [], []
    for f in funcs:
        w, body = wrapper(prefix, f)
        if not w:
            continue
        params = [p for p in f["params"]]
        if f["kind"] == "varargs" and "..." not in params:
            params = params + ["..."]
        members.append(member(f["ret"], f["name"], params))
        bodies.append(body)
        inits.append("\t.%s = %s,\n" % (f["name"], w))
    for decl, impl in extras:
        m = MEMBER_RE.match(decl)
        members.append("\t%s (*%s)(%s);\n" % (m.group(1).strip(), m.group(2), m.group(3)))
        inits.append("\t.%s = %s,\n" % (m.group(2), impl))

    os.makedirs(os.path.join(out, "include", "interfaces"), exist_ok=True)
    os.makedirs(os.path.join(out, "include", "proto"), exist_ok=True)
    os.makedirs(os.path.join(out, "src"), exist_ok=True)
    head = "/* Made by the Open SDK's tools/os4ifgen.py from %s. Do not edit. */\n" % os.path.basename(sfd)

    with open(os.path.join(out, "include", "interfaces", prefix + ".h"), "w") as h:
        h.write(head)
        h.write("#ifndef OS4C_INTERFACES_%s_H\n#define OS4C_INTERFACES_%s_H\n" % (guard, guard))
        h.write("#include <os4compat/os4compat.h>\n" + incs)
        h.write("\nstruct %s\n{\n\tstruct InterfaceData Data;\n" % iface)
        h.write("\tULONG (*Obtain)(void);\n\tULONG (*Release)(void);\n")
        h.write("\tVOID (*Expunge)(void);\n\tstruct Interface *(*Clone)(void);\n")
        h.write("".join(members))
        h.write("};\n\n#endif\n")

    with open(os.path.join(out, "include", "proto", prefix + ".h"), "w") as h:
        h.write(head)
        h.write("#ifndef _PROTO_%s_H\n#define _PROTO_%s_H\n" % (guard, guard))
        h.write("#include <os4compat/os4compat.h>\n" + incs)
        h.write("#include <clib/%s_protos.h>\n" % prefix)
        h.write("#include <interfaces/%s.h>\n" % prefix)
        h.write("extern %s%s;\n" % (lib["basetype"] if lib["basetype"].endswith("*") else lib["basetype"] + " ", lib["base"]))
        h.write("extern struct %s *%s;\n" % (iface, ivar))
        h.write("#ifdef __USE_INLINE__\n")
        for f in funcs:
            h.write("#undef %s\n#define %s(...) %s->%s(__VA_ARGS__)\n" % (f["name"], f["name"], ivar, f["name"]))
        for decl, _ in extras:
            n = MEMBER_RE.match(decl).group(2)
            h.write("#undef %s\n#define %s(...) %s->%s(__VA_ARGS__)\n" % (n, n, ivar, n))
        h.write("#endif\n#endif\n")

    with open(os.path.join(out, "src", prefix + "_iface.c"), "w") as c:
        c.write(head)
        c.write("#include <stdarg.h>\n")
        c.write('#include "../include/interfaces/%s.h"\n' % prefix)
        c.write("extern struct %s os4c_%s_iface;\n" % (iface, prefix))
        if prefix != "exec":
            # the members call through the interface's own base, opened on first use,
            # so linking an interface never makes the startup code open its library
            c.write("#define %s_BASE_NAME OS4C_BASE(os4c_%s_iface)\n" % (guard, prefix))
        c.write("#include <proto/%s.h>\n\n" % prefix)
        c.write("".join(bodies))
        c.write("\nstruct %s os4c_%s_iface = {\n" % (iface, prefix))
        c.write('\t.Data = { .LibName = "%s", .Version = 1 },\n' % lib["libname"])
        c.write("\t.Obtain = os4c_IfaceObtain,\n\t.Release = os4c_IfaceRelease,\n")
        c.write("\t.Expunge = os4c_IfaceExpunge,\n\t.Clone = os4c_IfaceClone,\n")
        c.write("".join(inits))
        c.write("};\n")

    with open(os.path.join(out, "src", prefix + "_ivar.c"), "w") as c:
        c.write(head)
        c.write('#include "../include/interfaces/%s.h"\n' % prefix)
        c.write("extern struct %s os4c_%s_iface;\n" % (iface, prefix))
        c.write("struct %s *%s = &os4c_%s_iface;\n" % (iface, ivar, prefix))

    return {"prefix": prefix, "libname": lib["libname"], "iface": iface, "base": lib["base"],
            "basetype": lib["basetype"], "count": len(members)}


def registry(out, libs):
    with open(os.path.join(out, "src", "os4c_registry.c"), "w") as c:
        c.write("/* Made by the Open SDK's tools/os4ifgen.py. Do not edit. */\n")
        c.write("#include <os4compat/os4compat.h>\n\n")
        for l in libs:
            c.write("extern struct Interface os4c_%s_iface;\n" % l["prefix"])
        c.write("\nstruct Interface *const os4c_registry[] = {\n")
        for l in libs:
            c.write("\t&os4c_%s_iface,\n" % l["prefix"])
        c.write("\t0\n};\n")


def main():
    if len(sys.argv) < 3:
        sys.exit(__doc__)
    out, libs = sys.argv[1], []
    for sfd in sys.argv[2:]:
        libs.append(generate(out, sfd))
    registry(out, libs)
    for l in libs:
        print("%-24s %-20s %4d members" % (l["libname"], l["iface"], l["count"]))


if __name__ == "__main__":
    main()
