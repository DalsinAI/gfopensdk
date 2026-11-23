# Opening a datatype object from memory (DTST_MEMORY)

A program that already holds a file's bytes (a browser's download, an
archive member, a resource) can hand them to the datatypes where they are.
Nothing is written to `T:`.

## What changed

datatypes.library 47.100 already took `DTST_MEMORY` and recognised the type
from the bytes, but the classes in this pack refused the source with IoErr
212 (`ERROR_OBJECT_WRONG_TYPE`): their shared reader, `dt_read_source()`
(`Datatypes/common/dtlib.c`), only took a file. It now copies a memory
source (GF-70). The rule is in `Datatypes/common/dtsource.h`.

## The call

```c
#include <datatypes/datatypes.h>
#include <datatypes/datatypesclass.h>

#ifndef DTST_MEMORY                 /* OS 3.2's NDK has no numbers for V44 */
#define DTST_MEMORY 5
#endif
#ifndef DTA_SourceAddress
#define DTA_SourceAddress (DTA_Dummy + 39)
#define DTA_SourceSize    (DTA_Dummy + 40)
#endif

Object *o = NewDTObject(NULL,
    DTA_SourceType,    DTST_MEMORY,
    DTA_SourceAddress, (ULONG)bytes,
    DTA_SourceSize,    size,
    DTA_GroupID,       GID_PICTURE,     /* optional, as for a file */
    PDTA_DestMode,     PMODE_V43,
    TAG_DONE);
```

The name argument is NULL. Everything after `NewDTObject()` is the same as
for a file: `GetDTAttrs()`, `DTM_PROCLAYOUT`, `PDTM_READPIXELARRAY`,
`DisposeDTObject()`.

The Open SDK's own headers (OpenNDK `datatypes/datatypesclass.h`) define
`DTST_MEMORY`, `DTA_SourceAddress` and `DTA_SourceSize`; the `#ifndef` lines
are only needed when building against OS 3.2's NDK.

## Which classes

| Classes | From memory |
| --- | --- |
| gfopenpng | yes, checked in a lab on datatypes.library 47.100 |
| gfopengif (stills and animations), webp, gfopentga, gfopenpicture | yes, the same reader; not yet run in a lab |
| gfopensound, gfopenmodule, gfopenmidi, gfopendoc | read through the same reader; not yet run in a lab |
| IFF types (ilbm, 8svx, anim) | datatypes.library opens an IFF handle on the memory itself |
| webm, cdxl, pcm, smacker, gfopenvideo's large films | no: they stream from a file by name |

It needs both parts: datatypes.library 47.100 or later, and classes built
from this change or later (the pack after 0.2-rc1). The class versions did
not change, so do not test a class's version: ask, and fall back.

## How to detect it, and the fallback

1. `DataTypesBase->lib_Version > 47`, or `== 47` with `lib_Revision >= 100`:
   try memory. OS 3.2's datatypes.library (47.x below 100) has no memory
   source: do not try, use a file.
2. If `NewDTObject()` returns NULL, write the bytes to a file in `T:` and
   open that, as before. An older class under the new library answers
   IoErr 212; so does a class that streams from a file.
3. Delete the temporary file only when you made one.

## Example

`Examples/datatypes-memory` is a Shell command that does all of this:
`DTMemInfo PICTURE` reads the file into memory, opens it from memory where
it can and through a file in `T:` where it cannot, and says which. The rule
of step 1 is `dt_memory_source_ok()` in its `dtmemory.h`, tested on the host
(`tests/host/test_dtmemory.c`). The same words are beside `DTST_MEMORY` in
OpenNDK's `datatypes/datatypesclass.h`.

## Whose bytes

- The classes in this pack copy the bytes while the object is made
  (`OM_NEW`). After `NewDTObject()` returns, the object does not read your
  buffer again, and an animated GIF keeps its own copy for as long as it
  lives.
- That is these classes' behaviour, not a promise of the source type. An
  IFF type reads through a handle on your memory, and another vendor's
  class may read later. The safe rule: keep the buffer unchanged until
  `DisposeDTObject()`.
- The datatypes never free or write to your buffer.
- Memory: there are two copies of the file while the object is made (yours
  and the class's), as there were with the file in `T:` on a RAM disk.

## Speed

Lab, open ROM, three decodes of a 465 KB PNG (640x480): 63 ms from memory,
781 ms through a file in `T:`.

## For the browser (gfopenbrowser)

1. Merge order does not matter: without the new classes the browser's
   memory attempt fails and it uses the file.
2. gfopenbrowser pull request 3 adds WebKit patch 0127 (`newPicture()` in
   `DatatypesDecode.c`): memory first on 47.100 and later, the file
   otherwise, for stills and animated GIFs.
3. The next RC engine build (RC5) applies patches 0125, 0126 and 0127, and
   the machine it runs on needs this pack's classes.
4. Lab check owed on that engine: a page with PNG, GIF and WebP pictures
   and an animated GIF shows with no `T:OpenBrowser-*.img` written on the
   open ROM machine; the same page still shows on OS 3.2 through the file.
