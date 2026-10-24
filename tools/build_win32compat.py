#!/usr/bin/env python3
"""Build an isolated checked-bitmap SDK overlay using the verified Open3 stove."""
from pathlib import Path
import argparse
import json
import shutil
import subprocess
from build_curl_sdk import verify_stove, digest, OPEN3

ROOT = Path(__file__).resolve().parents[1]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--stove', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    args = parser.parse_args()
    stove, out = args.stove.resolve(), args.out.resolve()
    verify_stove(stove)
    for protected in [ROOT, stove]:
        if out == protected or out in protected.parents or protected in out.parents:
            parser.error('output must be separate from source and compiler directories')
    if out.exists() and any(out.iterdir()):
        parser.error('output must be empty; objects are always rebuilt')
    out.mkdir(parents=True, exist_ok=True)
    sdk = out/'sdk'
    for name in ['Include/win32compat', 'Lib', 'Lib/win32compat/src', 'Docs']:
        (sdk/name).mkdir(parents=True, exist_ok=True)
    sources = [ROOT/'Lib/win32compat/src/bitmap.c', ROOT/'Include/win32compat/bitmap.h',
               ROOT/'tests/sdk/win32compat/bitmap_test.c', ROOT/'Docs/WIN32COMPAT.md']
    cc = stove/'prefix/bin/m68k-amigaos-gcc'
    flags = ['-std=c99', '-O2', '-m68040', '-m68881', '-mcrt=nix20', '-Wall',
             '-Wextra', '-Werror', '-fno-common', '-fno-strict-aliasing', '-I'+str(ROOT/'Include')]
    obj = out/'bitmap.o'
    subprocess.run([str(cc), *flags, '-c', str(sources[0]), '-o', str(obj)], check=True)
    archive = sdk/'Lib/libwin32compat.a'
    subprocess.run([str(stove/'prefix/bin/m68k-amigaos-ar'), 'rcs', str(archive), str(obj)], check=True)
    subprocess.run([str(cc), *flags, str(sources[2]), str(archive), '-o', str(out/'bitmap-test')], check=True)
    for source, relative in [(sources[0], 'Lib/win32compat/src/bitmap.c'),
                             (sources[1], 'Include/win32compat/bitmap.h'),
                             (sources[3], 'Docs/WIN32COMPAT.md'),
                             (ROOT/'LICENSE', 'Lib/win32compat/LICENSE')]:
        shutil.copy2(source, sdk/relative)
    receipt = dict(component='win32compat-bitmap', version='0.1',
                   compiler=subprocess.check_output([str(cc), '--version'], text=True).splitlines()[0],
                   compiler_archive_sha256=OPEN3, flags=flags,
                   source_sha256={str(p.relative_to(ROOT)): digest(p) for p in sources},
                   artifact_sha256={str(p.relative_to(out)): digest(p) for p in sorted(out.rglob('*')) if p.is_file()},
                   runtime_status='unrun; building and linking do not qualify execution')
    (out/'receipt.json').write_text(json.dumps(receipt, indent=2)+'\n')
    print('Built isolated overlay:', sdk)

if __name__ == '__main__':
    main()
