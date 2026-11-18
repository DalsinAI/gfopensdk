# GFOpenMUI

`muimaster.library` 19.x for AmigaOS 3.2.3 and GFOS: MUI's programming
interface, written clean-room by the AmiCradle Team over GFOpenLayout's UI
(olui). A MUI program opens `muimaster.library` and gets windows laid out,
drawn and themed by GFOpenLayout, the same way GFOpenGTK and gfopenwx
programs do. It runs on a 68040 or 68060 (soft float), like the rest of
the Team's libraries.

Design: amicradle-teams `designs/MUIMASTER-DESIGN-20261110.md` (v2,
validated by Team 5 on 10 November 2026). In short:

- muimaster keeps MUI's objects, tags, methods and notification, and holds
  no geometry: a window's tree becomes olui markup when it opens, and state
  changes go through `olui_set_*`.
- What olui lacks for MUI (grid, same-size groups, pages, access keys,
  splitters, owned elements with input) is added to GFOpenLayout
  (library 18), where GFOpenGTK and gfopenwx gain from it too.
- Custom classes (MUI's and BOOPSI's) draw in owned elements.
- After that, BOOPSI, GadTools and ReAction programs converge on the same
  layout through olbridge.

Order of work: GFOpenLayout's grid, same-size and owned-element PRs, then
this library's core with Calculator as the first program, then the rest.

## The core (step 2)

`muimaster/` holds the core classes: Notify (notification with
`MUIV_TriggerValue`, `MUIV_NotTriggerValue`, `MUIA_NoNotify`), Area,
Group (rows, columns, `MUIA_Group_Columns` grids, `SameWidth`,
`SameHeight`, `SameSize`, spacing), Rectangle, Text (labels, and buttons
with `MUIA_InputMode`), Window and Application (`NewInput`, `ReturnID`),
and the calls `MUI_NewObjectA`, `MUI_MakeObjectA`, `MUI_DisposeObject`,
`MUI_CreateCustomClass` and their friends. `include/libraries/mui.h` is
the programs' header, written from MUI's published interface (names and
ID values).

On the host the core runs over a small BOOPSI (`host/`) and a window-less
backend; the tests build a Calculator-shaped program with MUI's macros,
open it, press its buttons through olui and check the boxes and the
notifications:

    make -C muimaster GFOPENLAYOUT=/path/to/gfopenlayout test

`GFOPENLAYOUT` must have library 18 (grid and same-size: gfopenlayout
PRs #46 and #47). The Amiga backend and `muimaster.library` itself come
next, with Calculator on GFOS and OS 3.2.3.

## The Zune preview

Until 10 November 2026 this repository held a port of AROS's Zune
(`zunemaster.library` with a `muimaster.library` face, shipped in GFOpenUp
as a preview). It is on the **`reference/zune`** branch, unchanged
(main at 0c945fe), with its APL 1.1 licence, for reference and for the
GFOpenUp builds that still take it. Nothing of it is copied into main:
GFOpenMUI is clean-room.

## Licence

MIT, Copyright (c) 2026 AmiCradle Team (`LICENSE`). `CONTRIBUTORS.md`
says who made it.
