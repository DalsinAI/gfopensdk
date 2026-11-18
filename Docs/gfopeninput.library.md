# GFOpenInput

One standard way for Amiga programs to use game controllers, as part of the
GFOpen family for AmigaOS 3.2. `gfopeninput.library` lists every controller,
says when one comes or goes, and reports each in one standard layout (the
one SDL 2's GameController API uses: A, B, X, Y, the shoulders, triggers,
two sticks and the d-pad), with the raw buttons and axes beside it, rumble
where the pad has it, and one mapping database.

- **Every source:** the Amiga's joystick ports and CD32 pads, USB pads through
  Poseidon, pads on AmiCradle's x86 or ARM64 cores (mapped there), and the
  A1200's own ports under a PiStorm.
- **Older games keep working:** any modern pad can drive an Amiga port as a
  joystick or a CD32 pad, so games that use `lowlevel.library`,
  `gameport.device` or the chips themselves see one. On AmiCradle the
  cores do this already. On a real Amiga, the `ReadJoyPort` patch for USB
  pads is opt-in, switched on in GFOpenPrefs; nothing is patched by default.
- **Mappings built in** for the common families (Xbox, PlayStation, Switch,
  8BitDo and CD32-style pads), in SDL's GameControllerDB format, with the
  user's own lines on top.
- **SDL 2** in GFOpenGPU is built on it, so `SDL_GameController` works with no
  setup.
- **GFOpenPrefs** gets a Gamepads page to test pads, map them and choose which
  pad drives which port.

The design is [`Design-GFOpenInput.md`](Design-GFOpenInput.md).

## Current status, 8 October 2026

**0.1, in review.** `gfopeninput.library` 1.2 works on AmiCradle. The rest of 0.1 is in progress with other helpers. The design is 0.2: section 1.1 has the user's decisions, and section 11 the defaults decided for 0.1.

| Part | State |
| --- | --- |
| `include/libraries/gfopeninput.h`, the SFD, `clib`, `proto` and `inline` headers | **Frozen for 0.1** (8 October 2026): they change only by adding |
| `library/openinput_lib.c` | **The core, 1.2:** <ul><li>listing, with IDs never reused</li><li>hot-plug, state and mapping messages to a program's port</li><li>the standard layout, raw state and dead zones</li><li>`OIT_Exclusive`, which pauses a pad's legacy feed</li><li>button names per family</li><li>the legacy-port calls</li></ul> |
| `library/mapping.c` | SDL's GameControllerDB text format (`platform:AmigaOS 3`); built-in lines for Xbox, PlayStation, Switch, 8BitDo and CD32-style pads, under the user's lines from `ENV:GFOpenInput/mappings.txt` |
| `library/src_amicradle.c` | **Pads on AmiCradle's cores:** read from the services card's pad window with no round trip; exclusive use, rumble and ports go back through the window. It needs amicradle's pad window (its pull request) |
| `library/src_amigaport.c` | **The Amiga ports, and the opt-in `ReadJoyPort` patch** (below): joysticks and CD32 pads in either game port; the patch, off by default, lets games that use `lowlevel.library` see any GFOpenInput pad as a CD32 pad or a joystick |
| `library/source.h` | The interface a source is written to, frozen like the header (one member added at the end since: `os_Refresh`) |
| `tools/lltest.c`, `tools/llchain.c` (`LLTest`, `LLChain`) | Test tools for the ports and the patch (below) |
| `tools/oilist.c` (`OIList`) | **Lists controllers and the ports.** `STATE`, `WATCH` (hot-plug), `LIVE` (every change), `EXCLUSIVE`, `RUMBLE`, `SETPORT=` and `MODE=`, and `SECONDS=` |
| SDL 2 on GFOpenInput, the GFOpenPrefs Gamepads page | In progress with other helpers |

**Tested:**
- `gfopeninput.library` and `OIList` build with the os32 stove (GCC 6.5) and the os32-gcc16 stove.
- On a scratch OS 3.2.3 instance, with amicradle's pad window and a synthetic pad on the cores (`AC_TEST_PAD=1`), these worked:
  - listing, hot-plug (new IDs each time) and live state with full analogue sticks and triggers;
  - exclusive use, which paused port 1's feed;
  - rumble reaching the bridge;
  - setting a port from the Amiga.
- No real pad was attached.

## The Amiga ports, and the ReadJoyPort patch (`library/src_amigaport.c`)

- **The ports:** a joystick or a CD32 pad in either game port, read through
  `lowlevel.library`'s `ReadJoyPort`, in the standard layout: a CD32 pad's
  red, blue, green and yellow are A, B, X and Y, Reverse and Forward the
  shoulders, Play is Start; a joystick's fire is A and its second button B.
  The joystick port is always listed; the mouse port when a CD32 pad is
  read in it, or as a joystick when `ENV:GFOpenInput/MousePort` is
  `joystick` (`lowlevel.library` reads a mouse there as a stick too). A port a pad feeds is listed as the pad, not the port.
- **The patch, opt-in only:** nothing is patched until
  `ENV:GFOpenInput/LowLevelPatch` is `1` (GFOpenPrefs' Gamepads page sets it).
  Then `ReadJoyPort` answers for the chosen port with a pad, any GFOpenInput
  pad, as a CD32 pad or a joystick (`ENV:GFOpenInput/ports.prefs`:
  `port 1 cd32 any`, or a pad's GUID in place of `any`; that is also the
  default), and passes every other port through. A pad opened with
  `OIT_Exclusive` is paused: its port reads its own hardware again.
  Switching it off takes the patch out within a second, unless another
  program has patched `ReadJoyPort` on top since; then it stays in,
  passing every call through, until that one has gone. While it is in, the
  library keeps itself open, so it is never expunged under the patch.
- **Test tools:** `LLTest` reads a port through `ReadJoyPort` as an older
  game does, and says where the function is (so a patch going in or out
  shows); `LLChain` puts a pass-through patch of its own on top, to test
  the removal rule.

## The Team's input.device (`device/`)

The input library, input.device 50 (amicradle
`docs/design/Design-Open-Input-Library.md`). It is not gfopeninput.library:
it is the system's input device, with OS 3.2's face, and it lives here
because it runs on every tier (a real Amiga, the PiStorm, the appliance,
AmiCradle) and shares the acceleration design with GFOpenInput.

| Part | What it does |
| --- | --- |
| `device/input_dev.c` | **The device:** the commands (`IND_ADDHANDLER`, `IND_REMHANDLER`, `IND_WRITEEVENT`, `IND_ADDEVENT`, `IND_SETTHRESH`, `IND_SETPERIOD`, `IND_SETMPORT`, `IND_SETMTYPE`, `IND_SETMTRIG`) and `PeekQualifier()`; the input task at priority 20, which reads keyboard.device and gameport.device, sends timer events ten times a second and passes every event down the handlers in priority order |
| `device/keys.c` | The qualifiers, the last two keys pressed (for dead keys) and which keys repeat. Key repeat has one voice: this device repeats at Input prefs' delay and rate (`IND_SETTHRESH`, `IND_SETPERIOD` from IPrefs), marked `IEQUALIFIER_REPEAT` |
| `device/pointer.c` | **AmiCradle's absolute pointer:** the host pointer's place from the services card's pointer window (`$8C00`) becomes `IECLASS_NEWPOINTERPOS` (`IESUBCLASS_PIXEL`) against the screen under it. The device writes `'INPT'` in the window's OWNER word, so the runtime stops steering with mouse counts. The counters' movement that follows a new place is dropped; movement with no new place behind it (a relative mouse, the host pointer captured) goes on as on any Amiga |
| `device/accel.c` | **Relative acceleration:** the curve of `Design-Pointer-Acceleration.md` (velocity over a 24 ms window, exact below the precision speed, smooth up to the maximum, a turn resets, no count lost), only for relative mice, never on AmiCradle's absolute pointer |
| `device/teamprefs.c` | The Team's chunk in input.prefs, `OIAC` (twenty bytes: `teamprefs.h`), read when IPrefs applies Input prefs, and (50.5) once at the first command a process sends. No chunk: acceleration off, the wheel and the middle button on. Its flags word: the wheel off, the middle button off, a wheel adapter on the joystick port and its counts a step |
| The wheel (50.5) | Each step goes down the handlers as the NewMouse standard has it: `IECLASS_NEWMOUSE` and `IECLASS_RAWKEY` `NM_WHEEL_UP`/`DOWN`/`LEFT`/`RIGHT` (`$7A`-`$7D`), pressed and let go, with the qualifiers held. From AmiCradle's pointer window (ring KIND 4, the host's wheel), from a driver's `IND_ADDEVENT` of the raw key (gfopenusb's HID class; a `NEWMOUSE` event beside it is dropped, as this device sends its own), and from a wheel adapter on the joystick port (the WheelBusMouse and PS2M way: JOY1DAT's vertical counter is the wheel, its horizontal one a second wheel; off unless switched on, as a joystick there would scroll). The middle button (a pressed wheel) is `IECODE_MBUTTON` with `IEQUALIFIER_MIDBUTTON` from gameport.device's POTGO reading or the ring, as before; switched off, it sends nothing. What a step scrolls in a program that doesn't know the wheel is GFOpenWindows' (gfopenprefs `Windows/`) |
| `tools/inputprobe.c` (`InputProbe`) | `INFO`: which input.device runs; `WATCH secs`: every event on the chain, at priority 100 |
| `tools/chipscreen.c`, `tools/joyread.c` (`ChipScreen`, `JoyRead`) | Test tools: a chipset screen in front (hires, lores, interlaced); JOY0DAT read as a game that takes over the machine reads it |
| `tools/inputcmds.c` (`InputCmds`) | Lab checks, run the same way on OS 3.2's input.device and the Team's: `TRIG`, `TYPE` and `PORT` (`IND_SETMTRIG`, `IND_SETMTYPE`, `IND_SETMPORT` against gameport.device's units), `ABORT` (AbortIO on a queued command), `TAKE secs` (a program takes the mouse port and gives it back), `QUICK` (which commands are done at once), `SHOW`, `ALL`. Prints PASS or FAIL lines |
| `tools/cxprobe.c`, `tools/deltaprobe.c`, `tools/handlerregs.c` (`CxProbe`, `DeltaProbe`, `HandlerRegs`) | A commodity with a hotkey that answers Exchange; what a window with `IDCMP_DELTAMOVE` and a handler above Intuition see of the mouse; how handlers are called (registers, Forbid, Disable) |

**Loading it** in place of the ROM's, for now (the firmware's ROM module
path comes later): put `LoadModule DEVS:input.device` (wherever it was
copied) in `S:Pre-LoadModule-Startup`. Its version (50) is above the ROM's
(47) with the ROM's priority (40) and flags, so the next start uses it;
`InputProbe INFO` says which one runs. Take the line out and cold start to
have the ROM's back. With Team 2's open keyboard and gameport modules
(amicradle-guest #99) the same line loads all three:
`LoadModule DEVS:input.device DEVS:keyboard.module DEVS:gameport.module`.

**Tested** (13 October 2026, a lab copied from Instance-32, OS 3.2):
the host tests (`tests/host/run.sh`, 43 checks of `test_device.c`); the
desktop, a click on a prefs editor's Save, keys with shift and their
repeat (600 ms and 50 ms by default, 300 ms and 100 ms after Input prefs
said so); the absolute pointer on a PAL hires, lores and interlaced chipset
screen and on a 1920 x 1080 RTG screen, exact at rest; JOY0DAT still moving
for programs that read it; and, on a runtime without the pointer window,
relative mice with acceleration off and on. The numbers are in the design.
50.2 (13 October 2026, lab `inputpasses-a`, copied from Instance-32, on
the deployed runtime): `InputCmds ALL QUICK` passes on OS 3.2's own
keyboard.device and gameport.device and on Team 2's open ones, as on the
ROM's input.device; `TAKE`, Exchange and commodity hotkeys, relative and
absolute movement (`DeltaProbe`), and Ken's Labyrinth from start to its
first floor.

## Building

    library/build.sh [OUT_DIR]          # default build/
    device/build.sh [OUT_DIR]           # input.device and the test tools
    STOVE=~/AmiCradle/stoves/os32-gcc16 library/build.sh build-gcc16

It makes `gfopeninput.library` (bare: no startup code or C library),
`OIList`, `LLTest` and `LLChain`. Copy the library to `LIBS:` and run `OIList`.

## Licence and credit

GFOpenInput is free software under the MIT licence (`LICENSE`,
Copyright (c) 2026 AmiCradle Team): anyone may use it, change it, fork it and
ship it, commercially too. The licence's one condition keeps the credit: the
copyright notice and the licence text stay with every copy and fork. The Team
also asks, as a courtesy rather than a condition, that a fork or a port say
it is based on GFOpenInput by the AmiCradle Team.

GFOpenInput was created by the AmiCradle Team, for AmiCradle.
