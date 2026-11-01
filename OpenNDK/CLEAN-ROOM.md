# OpenNDK: what it is written from

OpenNDK is an independent set of headers, function tables and link
libraries for 68k AmigaOS 3.x software. It is the Team's own work, MIT,
Copyright (c) 2026 AmiCradle Team.

## May be used

- **Interface facts:** the names of headers, structures, fields, functions,
  tags and constants; their values, offsets, sizes and types; each call's
  library vector offset and registers. A program needs exactly these to
  build and run, and they are the same in every compatible header set.
- **Behaviour,** from the RKMs, the autodocs and black-box tests on real
  systems, described in our own words.
- **The open libraries' own tables,** such as amigachrome-guest's `.lvo`
  files, which their builds already check against the vendor's.

## Never copied

- Text from the NDK 3.2, the OS 4.1 SDK or any Commodore, Hyperion or
  Cloanto release: header and autodoc comments, descriptions, examples and
  file banners. Comments in OpenNDK are written fresh and kept short.
- Macro and inline bodies written by others. Where a header has always
  carried a macro (`IsListEmpty`, `SetAPen` and the like), its name and
  meaning are interface facts; its body here is ours.
- Code or text from AROS, MorphOS or any other implementation of these
  APIs, beyond what CLEAN-ROOM.md in amigachrome-guest allows.

## Checked, never bundled

The vendor's NDK may be used as a test oracle where someone has it
installed (`check/compare_ndk.sh`): it compiles our layouts and values
against the NDK's headers and lists every difference. Its files are never
committed, copied into OpenNDK or shipped with it.
