# Building for the Open platform

The Open platform is AmigaOS 3.2.x with the Open libraries. The same sources
build for AROS 68k, as two separate binaries from one source, with no
`#ifdef` maze.

## Start from a template

| Template | What you get |
| --- | --- |
| `Templates/shell-command` | A Shell command with ReadArgs, Ctrl-C and a version string |
| `Templates/gadtools-app` | A font-sensitive GadTools window with a menu, keys and a status line, following the Open apps' rules |
| `Templates/olui-app` | A window described in HTML and CSS, in the user's theme, with its events in C (OpenLayout UI: [OPENLAYOUT-UI.md](OPENLAYOUT-UI.md)). OS 3.2 only |

Copy the drawer, rename the program, then run `make`. That gives you
`build/<Name>.os32` and `build/<Name>.aros`. ACKitchen sets `CC_OS32` and
`CC_AROS` to its stoves. Elsewhere, put `m68k-amigaos-gcc` (bebbo's, with
NDK 3.2) and `m68k-aros-gcc` on your PATH.

## The platform's rules

- **Set FPCR to 0 when doubles matter.** OS 3.2.3's ROM `mathieeesingbas`
  sets single precision in each task that opens it, so a program that needs
  double precision sets FPCR itself.
- **Give a big program its own stack** with `StackSwap`, because libnix
  ignores `__stack`.
- **Build libraries with `-fno-common`**, so library bases aren't merged.
- **Never put one library call inside another's arguments** with the NDK's
  inline calls, as in `GetTagData(TAG, (ULONG)FindTask(NULL), tags)`. Each
  inline call loads its library base into a6, so the inner call leaves the
  wrong base there and the outer call jumps into the wrong library. Work
  out the inner value into a local first. Calls through OS 4 interfaces
  (os4compat) are safe either way.
- **Never require an accelerator.** Every Open library works on a real
  68040 with no Cradle. OpenGPU always has its CPU back end, and a feature
  that needs the services card says so in words.
- **Use published interfaces only:** OS 4's RTG calls by name, the standard
  bsdsocket numbers, MUI's function table through Zune and AROS's GLA calls.

## What's in this SDK (0.1)

| Part | Headers | Function table |
| --- | --- | --- |
| gfopenrtg.library 0.10 | `gfopenrtg/gfopenrtg.h`, `gfopenrtg/modes.h`, `proto/`, `inline/` | `SFD/gfopenrtg_lib.sfd`, `FD/gfopenrtg_lib.fd` |
| opensocket.library | `acnetwork.h`, `proto/acnetwork.h`, `opensocket/acnet_socket_tags.h` | in the proto header |
| bsdsocket.library | in OpenNDK: `proto/bsdsocket.h`, `sys/socket.h`, `netinet/in.h`, `netdb.h`, `arpa/inet.h` and the rest | `OpenNDK/SFD/bsdsocket_lib.sfd` |
| accontrol.device | `accontrol/accontrol.h` | device commands |
| oapspool.device | `openprint/oap_device.h` | device commands |
| os4compat 0.1 | `os4compat/os4compat.h`, made `interfaces/` and `proto/` | `Lib/os4compat`, made from the NDK's SFD files |

## Porting from OS 4

`Docs/PORTING-OS4.md`: the os4compat kit gives OS 3.2's libraries OS 4's
interfaces (`IExec->AllocVec()`) and adds the OS 4 calls OS 3.2 lacks, so
most OS 4 source builds for 68k unchanged.

`manifest.json` lists the commit each part comes from, and
`tools/gather.py --check` says whether the copies here still match.
