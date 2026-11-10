#!/usr/bin/env python3
"""Make a CatComp-style C header from a catalog description (.cd) file.

    python3 tools/catcomp_h.py prog.cd -o strings.h

The header has, for every string, `#define MSG_X <id>` and `#define MSG_X_STR "..."`.
With CATCOMP_ARRAY defined before it is included, it also defines
`const struct CatCompArrayType CatCompArray[]` ({cca_ID, cca_Str}, in file order),
as AROS's and many Amiga programs' locale.c expect.

.cd syntax handled: ';' comment lines, '#' directives (ignored), a header line
`NAME (id/min/max)` where every field may be empty (an empty id is the last id + 1,
starting at 0), and the string on the following line(s); a line ending in a lone
backslash continues on the next line. C escapes in the string are kept as written.

MIT, Copyright (c) 2026 AmiCradle Team.
"""
import argparse
import re
import sys

HEAD = re.compile(r'^([A-Za-z_][A-Za-z0-9_]*)\s*\(\s*([^/)]*)\s*/\s*([^/)]*)\s*/\s*([^/)]*)\s*\)\s*$')


def parse(text):
    out = []
    lines = text.splitlines()
    i, nxt = 0, 0
    while i < len(lines):
        line = lines[i].rstrip('\r')
        i += 1
        if not line.strip() or line.startswith(';') or line.startswith('#'):
            continue
        m = HEAD.match(line.strip())
        if not m:
            raise SystemExit(f'catcomp_h: line {i}: expected "NAME (id/min/max)", got {line!r}')
        name, ident = m.group(1), m.group(2).strip()
        if ident:
            nxt = int(ident, 0)
        parts = []
        while i < len(lines):
            s = lines[i].rstrip('\r')
            i += 1
            if s.endswith('\\') and not s.endswith('\\\\'):
                parts.append(s[:-1])
                continue
            parts.append(s)
            break
        out.append((name, nxt, ''.join(parts)))
        nxt += 1
    return out


def cstr(s):
    # keep C escapes as written; quote bare double quotes
    r, k = [], 0
    while k < len(s):
        c = s[k]
        if c == '\\' and k + 1 < len(s):
            r.append(s[k:k + 2])
            k += 2
            continue
        r.append('\\"' if c == '"' else c)
        k += 1
    return '"' + ''.join(r) + '"'


def header(entries, guard):
    o = [f'/* Made by catcomp_h.py from a catalog description. Do not edit. */',
         f'#ifndef {guard}', f'#define {guard}', '',
         '#include <exec/types.h>', '']
    for name, ident, s in entries:
        o.append(f'#define {name} {ident}')
        o.append(f'#define {name}_STR {cstr(s)}')
    o += ['', '#ifdef CATCOMP_ARRAY',
          'struct CatCompArrayType { LONG cca_ID; CONST_STRPTR cca_Str; };',
          'static const struct CatCompArrayType CatCompArray[] =', '{']
    for name, _, _ in entries:
        o.append(f'    {{ {name}, (CONST_STRPTR){name}_STR }},')
    o += ['};', '#endif', '', f'#endif /* {guard} */', '']
    return '\n'.join(o)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('cd')
    ap.add_argument('-o', '--output', default='-')
    ap.add_argument('--guard', default='CATCOMP_STRINGS_H')
    a = ap.parse_args()
    with open(a.cd, encoding='latin-1') as f:
        h = header(parse(f.read()), a.guard)
    if a.output == '-':
        sys.stdout.write(h)
    else:
        with open(a.output, 'w', encoding='latin-1') as f:
            f.write(h)


if __name__ == '__main__':
    main()
