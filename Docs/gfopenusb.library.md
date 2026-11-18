
# GFOpenUSB

USB for AmigaOS 3.2.x that keeps every card and program that works today and
gives them a way forward. Plug in a USB card or adapter, run GFOpenUp, and
keyboards, mice, game pads, memory sticks, printers, network and serial
adapters, sound and MIDI work, with no stack to choose and nothing to read.

Dale, 4 October 2026: "GFOpenUSB, which has to provide compatibility to the
legacy while offering a way forward, supporting the myriad of those USB
adaptor things".

Status, 17 October 2026: **our own clean-room stack** (Dale, 16 October,
22:33), in the 1M GFOpenKick ROM. `DESIGN.md` section 8 is the design now.
Built: the core and the hub class (`gfopenusb.library`), `ListUSB`, and the
ROM's starter (`gfopenusb.boot`); run on Cradle with acusb.device (W54). Mass
storage (U2, `gfopenusbstorage.class` with `usbdisk.device`) and HID (U3,
`gfopenusbhid.class`: keyboards and mice into input.device, pads into
gfopeninput.library), on the class contract in `include/libraries/gfopenusb.h`
(W58, `DESIGN.md` 8.10).

`gfopenusbhid.class` 1.1 (4 November 2026): a mouse's wheel both ways. The
vertical wheel is NewMouse's `$7A`/`$7B` as before, and the horizontal one
(the consumer page's AC Pan) is `$7C` left and `$7D` right, each pressed and
let go, sent to input.device with `IND_ADDEVENT`. The Team's input.device
50.5 (gfopeninput) makes each a full NewMouse step and keeps its wheel
switch. It is in the ROM's usb group, so it comes with the next GFOpenKick
ROM.

| Folder | What |
| --- | --- |
| `core/` | The stack with no Amiga headers: enumeration, the hub class, transfers, the device list; mass storage's bulk-only transport, SCSI commands and partition tables (`ousb_msc.c`); HID's report parser, raw key table and events (`ousb_hid.c`) |
| `library/` | `gfopenusb.library`: the core on a UHCMD host controller driver (`usbhw.h`) |
| `include/` | `libraries/gfopenusb.h`, `clib/`, `inline/`, `proto/gfopenusb.h`: for classes and programs |
| `commands/` | `ListUSB`: what is plugged in |
| `classes/` | `storage/gfopenusbstorage.class` (and `usbdisk.device`), `hid/gfopenusbhid.class` |
| `boot/` | `gfopenusb.boot`: the ROM's starter, only with acusb.device's board |
| `tests/` | The core, mass storage (a model disk) and HID (a model keyboard, mouse and pad) against a model bus (`run.sh`; host and qemu-m68k), and `amiga/USBProbe`, `amiga/USBDiskTest` for a running system |

Build: `sh build-amiga.sh` with an os32 stove (`STOVE=`, `NDK=` to choose
the NDK); `sh tests/run.sh` for the tests. In the ROM: amicradle-guest's
`tools/openkickrom/trial-1m/build.sh` with `USB=` this checkout.

## Licence

MIT, Copyright (c) 2026 AmiCradle Team (`LICENSE`). No code of Poseidon,
AROS, ANAIIS or Sirion is in it: it is written from the USB 2.0
specification and the published host controller interface.

If you use or build on this work, we ask (we do not require) that you credit
the AmiCradle Team, for example "based on GFOpenUSB by the AmiCradle
Team".
