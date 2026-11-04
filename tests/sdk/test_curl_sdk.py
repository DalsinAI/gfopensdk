import importlib.util
import json
from pathlib import Path
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
SPEC = importlib.util.spec_from_file_location("curl_sdk", ROOT / "tools/build_curl_sdk.py")
M = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(M)


class CompilerReceiptTests(unittest.TestCase):
    def test_wrong_release_and_incomplete_receipt_are_refused(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            (root / "provenance.json").write_text(json.dumps(dict(release="old", archive_sha256="bad")))
            with self.assertRaisesRegex(ValueError, "open4"):
                M.verify_stove(root)
            (root / "provenance.json").write_text(json.dumps(dict(release="16.2.0-open4", archive_sha256=M.OPEN4, compiler_runtime_sha256={})))
            with self.assertRaisesRegex(ValueError, "incomplete"):
                M.verify_stove(root)

    def test_changed_compiler_input_is_refused(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            (root / "prefix/bin").mkdir(parents=True)
            files = {}
            for n in ["bin/m68k-amigaos-g++"] + [f"lib/{i}" for i in range(100)]:
                p = root / "prefix" / n
                p.parent.mkdir(exist_ok=True)
                p.write_bytes(b"fixture")
                files[n] = M.digest(p)
            (root / "provenance.json").write_text(json.dumps(dict(release="16.2.0-open4", archive_sha256=M.OPEN4, compiler_runtime_sha256=files)))
            M.verify_stove(root)
            (root / "provenance.json").write_text(json.dumps(dict(release="16.2.0-open6", archive_sha256=M.OPEN6, compiler_runtime_sha256=files)))
            M.verify_stove(root)
            (root / "provenance.json").write_text(json.dumps(dict(release="16.2.0-open6", archive_sha256=M.OPEN4, compiler_runtime_sha256=files)))
            with self.assertRaisesRegex(ValueError, "open6"):
                M.verify_stove(root)
            (root / "provenance.json").write_text(json.dumps(dict(release="16.2.0-open6", archive_sha256=M.OPEN6, compiler_runtime_sha256=files)))
            (root / "prefix/bin/m68k-amigaos-g++").write_bytes(b"changed")
            with self.assertRaisesRegex(ValueError, "changed"):
                M.verify_stove(root)
