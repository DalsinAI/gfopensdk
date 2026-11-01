#!/usr/bin/env python3
# Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
# SPDX-License-Identifier: MIT
"""Gather the SDK's headers and function tables from each library's repository.

    tools/gather.py            fetch each part at its pinned commit and copy its files
    tools/gather.py --check    the same, but only say whether the copies here match
    tools/gather.py --offline-check  verify recorded source hashes without repository access

The full online check needs access to every source repository, including the
private guest repository. Cloud checks use the recorded file hashes; maintainers
must run the full online check when advancing a source pin.

manifest.json names each part's repository, commit and files. The FD files
are made from the SFD files, so there is one source for each function table.
"""
import hashlib, json, os, subprocess, sys, tempfile, shutil

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def fetch(repo, commit, cache):
    d = os.path.join(cache, repo.replace("/", "_"))
    if not os.path.isdir(os.path.join(d, ".git")):
        subprocess.run(["git", "init", "-q", d], check=True)
        subprocess.run(["git", "-C", d, "remote", "add", "origin", f"https://github.com/{repo}"], check=True)
    subprocess.run(["git", "-C", d, "fetch", "-q", "--depth", "1", "origin", commit], check=True)
    subprocess.run(["git", "-C", d, "checkout", "-q", "--force", commit], check=True)
    return d


def sfd_to_fd(sfd):
    """An FD file from an SFD file: ##base, ##bias, ##public and one line a function."""
    out, base = [], None
    for line in sfd.splitlines():
        s = line.strip()
        if s.split()[:1] == ["==base"]:
            base = s.split()[1]
            out.append(f"##base {base}")
        elif s.startswith("==bias"):
            out.append(f"##bias {s.split()[1]}")
        elif s in ("==public", "==private"):
            out.append("##" + s[2:])
        elif s == "==end":
            out.append("##end")
        elif s and not s.startswith(("==", "*")):
            # "ULONG Name(ULONG a, ULONG b)(d0,d1)" -> "Name(a,b)(d0,d1)"
            head, regs = s.rsplit(")(", 1)
            ret_name, args = head.split("(", 1)
            name = ret_name.split()[-1].lstrip("*")
            names = [a.strip().split()[-1].lstrip("*") for a in args.split(",") if a.strip()]
            out.append(f"{name}({','.join(names)})({regs}")
    return "\n".join(out) + "\n"


def output_paths(part):
    paths = set(part["files"].values())
    for path in list(paths):
        if path.endswith(".sfd") and not path.startswith("OpenNDK/"):
            paths.add("FD/" + os.path.basename(path)[:-4] + ".fd")
    return paths


def made_fd(part, sfd_to):
    """The FD path gather.py makes from an SFD, or None when the part copies
    its own FD (a library whose SFD has ==varargs and spaced register lists,
    which ndkgen.py reads and sfd_to_fd doesn't)."""
    if not sfd_to.endswith(".sfd") or sfd_to.startswith("OpenNDK/"):
        return None
    fd = "FD/" + os.path.basename(sfd_to)[:-4] + ".fd"
    return None if fd in part["files"].values() else fd


def offline_check(manifest, root):
    for part in manifest["parts"]:
        expected = part.get("sha256", {})
        if set(expected) != output_paths(part):
            raise ValueError("incomplete source-file receipt: " + part["name"])
        for path, sha in expected.items():
            with open(os.path.join(root, path), "rb") as f:
                actual = hashlib.file_digest(f, "sha256").hexdigest()
            if actual != sha:
                raise ValueError("gathered file changed: " + path)
    print("all gathered file hashes match the recorded pinned-source receipts")
    return 0


def main():
    check = "--check" in sys.argv
    manifest = json.load(open(os.path.join(ROOT, "manifest.json")))
    if "--offline-check" in sys.argv:
        return offline_check(manifest, ROOT)
    cache = os.environ.get("OPENSDK_CACHE") or os.path.join(tempfile.gettempdir(), "opensdk-cache")
    os.makedirs(cache, exist_ok=True)
    stale = []
    for part in manifest["parts"]:
        src = fetch(part["repo"], part["commit"], cache)
        for frm, to in part["files"].items():
            data = open(os.path.join(src, frm), "rb").read()
            outs = [(to, data)]
            # OpenNDK's own tools/ndkgen.py makes its FD and the rest
            fd_path = made_fd(part, to)
            if fd_path:
                fd = sfd_to_fd(data.decode("latin-1")).encode("latin-1")
                outs.append((fd_path, fd))
            for path, body in outs:
                if part.get("sha256") and hashlib.sha256(body).hexdigest() != part["sha256"].get(path):
                    raise ValueError("pinned source disagrees with receipt: " + path)
                dst = os.path.join(ROOT, path)
                have = open(dst, "rb").read() if os.path.exists(dst) else None
                if have != body:
                    stale.append(path)
                    if not check:
                        os.makedirs(os.path.dirname(dst), exist_ok=True)
                        open(dst, "wb").write(body)
        print(f"{part['name']}: {part['repo']} {part['commit'][:7]}")
    if check and stale:
        print("out of date: " + ", ".join(stale))
        return 1
    print("up to date" if check else f"{len(stale)} file(s) written")
    return 0


if __name__ == "__main__":
    sys.exit(main())
