# What the Open SDK holds

The Open SDK 0.2, 5 November 2026. Each part's headers, function tables
and docs are copied by `tools/gather.py` from its own repository at the
commit `manifest.json` pins; change them there, then move the pin here.

## Libraries, devices and classes

| Part | Version, source | Include | SFD/FD | Docs |
| --- | --- | --- | --- | --- |
| gfopenrtg.library | 0.25, main 5af78d8, `gfopenrtg` | `proto/gfopenrtg.h` | gfopenrtg_lib.fd, gfopenrtg_lib.sfd | – |
| gfopengpu.library | 0.27, main 5af78d8, `gfopenrtg` | `proto/gfopengpu.h` | gfopengpu_lib.fd, gfopengpu_lib.sfd | [AutoDocs-GFOpenGPU.md](AutoDocs-GFOpenGPU.md) |
| gfopenfont.library | 1.7, main dc4878f, `gfopenfont` | `proto/gfopenfont.h` | gfopenfont_lib.fd, gfopenfont_lib.sfd | [gfopenfont.doc](gfopenfont.doc) |
| opensocket.library | main e7a6066, `gfopensocket` | `proto/acnetwork.h` | – | – |
| bsdsocket.library | main e7a6066, `gfopensocket` | OpenNDK `Include_H` (`proto/bsdsocket.h`) | bsdsocket_lib.sfd | – |
| accontrol.device | main e22fda4, `amicradle-guest` | `accontrol/accontrol.h` | – | – |
| oapspool.device | main 6e3b292, `gfopenprint` | `openprint/oap_device.h` | – | – |
| gfopentls.library / gfopencrypto.library | 1.3 / 2.1, main aa6f6a5, `gfopentls` | `proto/gfopencrypto.h`, `proto/gfopentls.h` | gfopentls_lib.fd | [AutoDocs-GFOpenTLS.md](AutoDocs-GFOpenTLS.md) |
| gfopenlayout.library | 11.0, main 6ecdfa1, `gfopenlayout` | `proto/gfopenlayout.h` | gfopenlayout_lib.fd, gfopenlayout_lib.sfd | [GFCSS.md](GFCSS.md), [GFOpenLayout-UI.md](GFOpenLayout-UI.md) |
| javascript.library | 1.0, main f3f41ce, `gfopenbrowser` | `proto/javascript.h` | javascript_lib.fd, javascript_lib.sfd | [javascript.library.md](javascript.library.md) |
| json.library | 1.0, main f3f41ce, `gfopenbrowser` | `proto/json.h` | json_lib.fd, json_lib.sfd | [json.library.md](json.library.md) |
| unicode.library | 1.0, main f3f41ce, `gfopenbrowser` | `proto/unicode.h` | unicode_lib.fd, unicode_lib.sfd | [unicode.library.md](unicode.library.md) |
| weblayout.library | 1.0, main f3f41ce, `gfopenbrowser` | `proto/weblayout.h` | weblayout_lib.fd, weblayout_lib.sfd | [weblayout.library.md](weblayout.library.md) |
| webbrowser.library | 1.0, main f3f41ce, `gfopenbrowser` | `proto/webbrowser.h` | – | [webbrowser.library.md](webbrowser.library.md) |
| gfopenmedia.library | 1.0, main 214ac79, `gfopenmedia` | `proto/gfopenmedia.h` | gfopenmedia_lib.fd, gfopenmedia_lib.sfd | [gfopenmedia.doc](gfopenmedia.doc) |
| gfopenmulticore.library | main b3f33b0, `gfopenmulticore` | `proto/gfopenmulticore.h` | gfopenmulticore_lib.fd, gfopenmulticore_lib.sfd | [gfopenmulticore.doc](gfopenmulticore.doc) |
| gfopenntlm.library | 1.1, main 4bb461a, `gfopenntlm` | `proto/gfopenntlm.h` | gfopenntlm_lib.fd, gfopenntlm_lib.sfd | [gfopenntlm.doc](gfopenntlm.doc) |
| pixman.library | 2.1, main f3b30ef, `gfopenpixman` | `proto/pixman.h` | pixman_lib.fd, pixman_lib.sfd | [pixman.library.md](pixman.library.md) |
| elf.library | 2.0, main a6f9c20, `gfopenelflibrary` | `elf/openelf_public.h` | – | [elf.library.md](elf.library.md), [elf.lvo](elf.lvo) |
| gfopenservice.device | main 90dedba, `gfopenservice` | `devices/gfopenservice.h` | – | – |
| GFOpenDatatypes classes | gfopengif.datatype 47.3, main 169b7f8, `gfopendatatypes` | `datatypes/gfopenimage.h`, `datatypes/streamclass.h` | – | – |
| GFOpenGfx graphics and layers additions | main 9565e57, `gfopengfx` | `proto/gfxdispatch.h`, `graphics/gfopenlayers.h` | – | – |
| GFOpenExec atomic calls | main e22fda4, `amicradle-guest` | `exec/gfopenexec_atomic.h` | – | – |

Programs include the `proto/` header, which gives GCC inline calls. Every
SFD is also built into stubs: see **Link library** below.

Notes:

- **elf.library** keeps its calls in `openelf_public.h` and `elf.lvo`
  (LVO, call, registers); it has no SFD yet, so no proto/inline header and
  no stubs. Call it through the LVOs listed in the header.
- **webbrowser.library** has proto, clib and inline headers but no SFD, so
  no FD and no stubs.
- **GFOpenExec atomic calls** live in exec.library's private slots on
  OS 3.2's own exec: check that exec is GFOpenExec first, as the header
  says. **GFOpenGfx** adds calls past the end of graphics.library's and
  layers.library's tables. OpenNDK stays the vendor NDK's interface; these
  calls are declared only here (`OpenNDK/check/check_lvo.py` lists them as
  ours).
- **GFOpenDatatypes**: the classes' own headers. gfopengif.datatype 47.3
  (animated GIFs in MultiView) needs no header change; programs use it
  through datatypes.library.

## Link library

`Lib/build.sh` builds `Lib/build/<compiler>/libopensdk.a`: one stub for
every public call in `SFD/`, made by OpenNDK's `tools/ndkgen.py` the same way
as OpenNDK's `libamiga.a`. Link with `-lopensdk` (after `-L` to that folder)
when you don't use the inline headers.

    sh Lib/build.sh                              # the os32-gcc16 stove
    PREFIX=m68k-linux-gnu- sh Lib/build.sh       # an ELF m68k GCC (CI)

Every SFD in `SFD/` is in it.

## Built from source, not kept here

These are static link libraries built from a pinned upstream source that
is fetched at build time, so the SDK points at them instead of copying:

| Part | Repository | Build | Gives |
| --- | --- | --- | --- |
| PortAudio with an AHI host API (for now; see below) | `DalsinAI/gfopenportaudio-` | `STOVE=... OUT=out ./build-amiga.sh` | `out/sdk/lib/libportaudio.a`, `out/sdk/include/portaudio.h`, `portaudio-2.0.pc` |
| GFOpenWX Toolkit (wxWidgets 3.2 on GFOpenLayout) | `DalsinAI/gfopenwxtoolkit` | `./build-amiga.sh` (see its README) | wxWidgets' static libraries and `wx/openlayout/` headers |
| curl and nghttp2 | `DalsinAI/gfopencurl` | `tools/build_curl_sdk.py` (see `Docs/SDK-AUDIT-20261024.md`) | an SDK overlay with `libcurl.a` |

PortAudio is becoming portaudio.library, a clean-room build of our own
tuned for the Amiga. When it lands, its headers and SFD are gathered here
like the other libraries' and the static build above goes.

## Soft float and the FPU

`Lib/m68k-soft-m68040.specs` links the soft-float maths for 68040 programs.
The runtime FPU check (fpuauto, amicradle-guest `common/fpuauto`), which
uses the FPU when the machine has one, is being put into the stoves' own
gcc specs; the SDK's specs file follows once that is merged.
