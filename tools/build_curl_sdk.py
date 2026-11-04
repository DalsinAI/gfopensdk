#!/usr/bin/env python3
# Copyright (c) 2026 AmiCradle Team. MIT licence (LICENSE).
"""Build the pinned OpenAmigaCurl in isolation and create a target SDK overlay.

Offline: source repositories and upstream tarballs must already be present.
No live stove, ROM, installed SDK or source checkout is modified.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import tarfile
import tempfile

ROOT = Path(__file__).resolve().parents[1]
CURL = "5776d8375c5d87b7b6c8d5187c3a061567f6bd54"
TLS = "919dd04ff675bee42a5bf0c26393043fd4c78d77"
OPEN4 = "495319a2ffd803278f8827cad70074029c7aa9ecbe05d037e8646ba43ab94ab2"   # the open4 release tarball (the autoinc-move fix, GCC PR 123853)
OPEN6 = "65f284476ec20cdf7851475d91d2c18d77fa6f2a0eb0f844b6ca23dbfa57eaa7"   # the open6 release tarball (GFOpenAmigaGCC; open4's fixes and later)
RELEASES = {"16.2.0-open4": OPEN4, "16.2.0-open6": OPEN6}


def digest(path):
    with path.open("rb") as f:
        return hashlib.file_digest(f, "sha256").hexdigest()


def verify_stove(stove):
    receipt = json.loads((stove / "provenance.json").read_text())
    if RELEASES.get(receipt["release"]) != receipt["archive_sha256"]:
        raise ValueError("use a verified GCC 16.2.0-open4 or open6 stove")
    files = receipt["compiler_runtime_sha256"]
    if len(files) < 100 or "bin/m68k-amigaos-g++" not in files:
        raise ValueError("incomplete compiler receipt")
    prefix = (stove / "prefix").resolve()
    for name, expected in files.items():
        p = (prefix / name).resolve()
        if not p.is_relative_to(prefix) or digest(p) != expected:
            raise ValueError("compiler/runtime changed: " + name)
    return receipt


def export(source, pin, dest):
    subprocess.run(["git", "-C", str(source), "cat-file", "-e", pin + "^{commit}"], check=True)
    dest.mkdir(parents=True)
    with tempfile.TemporaryFile() as archive:
        subprocess.run(["git", "-C", str(source), "archive", pin], stdout=archive, check=True)
        archive.seek(0)
        with tarfile.open(fileobj=archive) as tf:
            tf.extractall(dest, filter="data")


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for name in ("stove", "curl-source", "tls-source", "tarballs", "dependencies", "out"):
        ap.add_argument("--" + name, type=Path, required=True)
    ap.add_argument("--jobs", type=int, default=2)
    args = ap.parse_args()
    if args.out.exists() or args.out.is_symlink() or args.jobs < 1:
        ap.error("use a new output directory and positive jobs")
    stove, out = args.stove.resolve(), args.out.resolve()
    receipt = verify_stove(stove)
    deps = args.dependencies.resolve()
    required = ["lib/libz.a", "include/zlib.h", "include/zconf.h"]
    inputs = {name: digest(deps / name) for name in required}
    # Validate pins before creating any output.
    for source, pin in ((args.curl_source, CURL), (args.tls_source, TLS)):
        subprocess.run(["git", "-C", str(source), "cat-file", "-e", pin + "^{commit}"], check=True)
    out.mkdir(parents=True)
    curl, tls, sdk = out / "sources/curl", out / "sources/tls", out / "sdk"
    export(args.curl_source, CURL, curl)
    export(args.tls_source, TLS, tls)
    # Complete native header sets go first, never a mix of vendor and OpenNDK.
    shutil.copytree(ROOT / "OpenNDK/Include_H", sdk / "include")
    shutil.copytree(ROOT / "Include", sdk / "include", dirs_exist_ok=True)
    shutil.copytree(tls / "include", sdk / "include", dirs_exist_ok=True)
    (sdk / "lib").mkdir()
    for name in required:
        shutil.copy2(deps / name, sdk / name)
    cpu = f"-m68040 -m68881 -mcrt=nix20 -pthread -isystem {sdk / 'include'}"
    env = dict(os.environ, OS32_GCC16=str(stove), OS32_CPU_FLAGS=cpu,
               OPENTLS_INCLUDE=str(tls / "include"), DEPS_PREFIX=str(sdk),
               PREFIX=str(sdk), TARBALLS=str(args.tarballs.resolve()), JOBS=str(args.jobs))
    # GCC ignores -I for a directory also listed as -idirafter. That would
    # let the compiler's old NDK win and mix incompatible HOOKFUNC types.
    env.pop("NDK_INCLUDE", None)
    with (out / "build.log").open("w") as log:
        subprocess.run(["sh", str(curl / "build.sh")], env=env, stdout=log,
                       stderr=subprocess.STDOUT, check=True)
    notices = sdk / "share/licenses"
    notices.mkdir(parents=True)
    for name in ("LICENSE", "THIRD_PARTY_NOTICES.md", "SOURCES"):
        shutil.copy2(curl / name, notices / ("openamigacurl-" + name))
    shutil.copytree(curl / "upstream", notices / "curl-upstream")
    shutil.copy2(ROOT / "LICENSE", notices / "open-sdk-LICENSE")
    shutil.copy2(ROOT / "OpenNDK/LICENSE", notices / "OpenNDK-LICENSE")
    shutil.copy2(tls / "LICENSE", notices / "OpenTLS-LICENSE")
    pkg = sdk / "lib/pkgconfig"
    pkg.mkdir()
    (pkg / "libcurl.pc").write_text(
        "prefix=${pcfiledir}/../..\nlibdir=${prefix}/lib\nincludedir=${prefix}/include\n"
        "Name: libcurl\nDescription: OpenAmigaCurl HTTP/HTTPS, OpenTLS and nghttp2\n"
        "Version: 8.22.0\nLibs: -L${libdir} -lcurl\n"
        "Libs.private: -lnghttp2 -lz -lpthread -latomic\n"
        "Cflags: -I${includedir} -DCURL_STATICLIB\n")
    config = sdk / "lib/cmake/CURL"
    config.mkdir(parents=True)
    (config / "CURLConfig.cmake").write_text(
        'get_filename_component(_CURL_PREFIX "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)\n'
        'set(CURL_FOUND TRUE)\nset(CURL_VERSION 8.22.0)\nset(CURL_VERSION_STRING 8.22.0)\n'
        'set(CURL_INCLUDE_DIRS "${_CURL_PREFIX}/include")\n'
        'set(CURL_LIBRARIES CURL::libcurl)\n'
        'if(NOT TARGET CURL::libcurl)\n'
        '  add_library(CURL::libcurl STATIC IMPORTED)\n'
        '  set_target_properties(CURL::libcurl PROPERTIES\n'
        '    IMPORTED_LOCATION "${_CURL_PREFIX}/lib/libcurl.a"\n'
        '    INTERFACE_INCLUDE_DIRECTORIES "${_CURL_PREFIX}/include"\n'
        '    INTERFACE_COMPILE_DEFINITIONS CURL_STATICLIB\n'
        '    INTERFACE_LINK_LIBRARIES "${_CURL_PREFIX}/lib/libnghttp2.a;${_CURL_PREFIX}/lib/libz.a;pthread;atomic")\n'
        'endif()\n')
    # The upstream build links curltest, exercising the full static closure.
    report = dict(curl_commit=CURL, tls_commit=TLS, cpu_flags=cpu,
                  compiler_release=receipt["release"], compiler_archive_sha256=OPEN4,
                  dependency_inputs=inputs, scope="68040/FPU compile and link only; no network/runtime qualification")
    report["files"] = {str(p.relative_to(sdk)): digest(p) for p in sorted(sdk.rglob("*")) if p.is_file()}
    (out / "receipt.json").write_text(json.dumps(report, indent=2) + "\n")
    print(sdk)


if __name__ == "__main__":
    main()
