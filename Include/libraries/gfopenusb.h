/* libraries/gfopenusb.h: GFOpenUSB's core, gfopenusb.library (DESIGN.md, the
 * revision of 17 October 2026). The device list, the devices' and
 * interfaces' fields, the error codes and the class contract that U2 (mass
 * storage) and U3 (HID) plug into.
 *
 * Fixed-width types only, so the same structures serve the stack's portable
 * core (core/ousb_core.c, tested on the host) and Amiga programs. Fields
 * are read-only for everyone but the core; read them between
 * OUSB_LockList() and OUSB_UnlockList(), or from a class's own device
 * between its Attach and its Detach.
 *
 * Our own header, written from the USB 2.0 specification (chapter 9 and the
 * hub class, chapter 11). MIT, AmiCradle Team. */
#ifndef LIBRARIES_OPENUSB_H
#define LIBRARIES_OPENUSB_H

#include <stdint.h>

#define OPENUSB_NAME     "gfopenusb.library"
#define OPENUSB_VERSION  1

#define OUSB_MAXIFACES   8      /* interfaces kept per device (alternate setting 0) */
#define OUSB_MAXEPS      8      /* endpoints kept per interface */
#define OUSB_MAXPORTS    15     /* ports a hub may have here */
#define OUSB_NAMELEN     32     /* product and maker strings, Latin-1, NUL included */
#define OUSB_CDESC_MAX   1024   /* the most of a configuration descriptor kept */
#define OUSB_MAXBUSES    4      /* host controllers at once */

/* Errors. 1 to 13 are the host controller's own codes (the classic UHCMD
 * interface's UHIOERR numbers), passed on as they come. */
#define OUSB_OK           0
#define OUSB_OFFLINE      1     /* the bus is not operational */
#define OUSB_NAK          2
#define OUSB_HOSTERROR    3
#define OUSB_STALL        4     /* the endpoint is halted: OUSB_ClearHalt() */
#define OUSB_PKTTOOLARGE  5
#define OUSB_TIMEOUT      6     /* no answer: on Cradle, no device at that address */
#define OUSB_OVERFLOW     7
#define OUSB_CRCERROR     8
#define OUSB_RUNTPACKET   9
#define OUSB_NAKTIMEOUT   10    /* NAKed until the transfer's timeout */
#define OUSB_BADPARAMS    11
#define OUSB_NOMEM        12
#define OUSB_BABBLE       13
#define OUSB_GONE         64    /* the device was unplugged */
#define OUSB_BADDESC      65    /* a descriptor that does not parse */
#define OUSB_NOADDRESS    66    /* all 127 addresses in use */
#define OUSB_NOHARDWARE   67    /* the host controller driver did not open */
#define OUSB_ABORTED      68    /* OUSB_AbortTransfer() */

/* speeds */
#define OUSB_FULL  0
#define OUSB_LOW   1
#define OUSB_HIGH  2

/* endpoint types (bmAttributes & 3) */
#define OUSB_CONTROL 0
#define OUSB_ISO     1
#define OUSB_BULK    2
#define OUSB_INT     3

/* a device's flags */
#define OUSB_DF_HUB        0x01  /* the hub class drives it (built into the core) */
#define OUSB_DF_ROOT       0x02  /* the root hub */
#define OUSB_DF_CONFIGURED 0x04  /* SET_CONFIGURATION done */
#define OUSB_DF_GONE       0x08  /* unplugged: being removed */

struct OUSBEndpoint {
    uint8_t  address;            /* bEndpointAddress: number, $80 for IN */
    uint8_t  attributes;         /* bmAttributes: the type in bits 0-1 */
    uint8_t  interval;           /* bInterval as the descriptor says */
    uint8_t  pad;
    uint16_t maxpkt;             /* wMaxPacketSize */
    uint16_t pad2;
};

struct OUSBInterface {
    uint8_t  number, alt;        /* bInterfaceNumber, bAlternateSetting (0) */
    uint8_t  iclass, isubclass, iprotocol;
    uint8_t  neps;               /* endpoints kept in eps[] */
    uint16_t desc_off;           /* its interface descriptor's offset in the device's cdesc */
    uint16_t desc_len;           /* from there to the next interface descriptor: class
                                    descriptors (HID's, for one) are in this range */
    uint16_t pad;
    struct OUSBEndpoint eps[OUSB_MAXEPS];
    void    *binding;            /* the class's handle from its Attach, or NULL */
    void    *bound;              /* the class library that has it, or NULL */
};

struct OUSBDevice {
    struct OUSBDevice *next;     /* the next device found (all buses: OUSB_NextDevice) */
    struct OUSBDevice *parent;   /* its hub; NULL for a root hub */
    uint8_t  bus, addr, port, speed;      /* port: on its hub, 1 up; 0 for a root hub */
    uint8_t  depth, flags, nifaces, cfgvalue;
    uint16_t vid, pid, bcd_device, bcd_usb;
    uint8_t  dclass, dsubclass, dprotocol, maxpkt0;
    uint8_t  nports;             /* a hub's ports */
    uint8_t  tt_addr, tt_port;   /* a low or full speed device behind a high speed hub:
                                    the hub whose transaction translator splits for it */
    uint8_t  pad;
    char     product[OUSB_NAMELEN];
    char     maker[OUSB_NAMELEN];
    uint8_t  ddesc[18];          /* the device descriptor */
    uint16_t cdesc_len;
    uint8_t *cdesc;              /* the whole configuration descriptor (OUSB_CDESC_MAX at most) */
    struct OUSBInterface ifaces[OUSB_MAXIFACES];
    /* the core's own from here: may change */
    struct OUSBDevice *child[OUSB_MAXPORTS + 1];
    uint16_t pwrgood_ms;         /* a hub's power-on to power-good time */
    uint8_t  status_ep, status_len;       /* a hub's status-change endpoint and its report's length */
    void    *glue;               /* the Amiga side's (the hub's status request) */
};

/* The class contract (U2, U3 and later classes).
 *
 * A class is a library, opened by the core with OpenLibrary() under the name
 * the interface's class code gives (OUSB_HIDCLASS_NAME, OUSB_STORAGECLASS_NAME:
 * on a disk SYS:Classes/USB/, which is part of LIBS:; in the ROM
 * ROM:Classes/USB/). Past the four standard vectors it has two functions:
 *
 *   -30  APTR Attach(struct OUSBDevice *dev a0, struct OUSBInterface *ifc a1)
 *        Called by the bus's process when a configured device has an
 *        interface with that class code and no driver. Return a handle to
 *        take the interface, or NULL to leave it. Return quickly: do slow
 *        work (mounting, reading reports) in a task of the class's own.
 *   -36  void Detach(APTR handle a0)
 *        Called when the device goes (unplugged, or its hub went). The
 *        device's transfers fail with OUSB_GONE or OUSB_TIMEOUT from now on.
 *        Stop using the device and close its pipes before returning: the
 *        core frees the device right after.
 *
 * The core keeps the library open while it holds an interface. Transfers go
 * through gfopenusb.library's Control, OpenPipe and Transfer calls. */
#define OUSB_CLASS_HID      3
#define OUSB_CLASS_STORAGE  8
#define OUSB_CLASS_HUB      9
#define OUSB_HIDCLASS_NAME     "USB/gfopenusbhid.class"      /* U3 */
#define OUSB_STORAGECLASS_NAME "USB/gfopenusbstorage.class"  /* U2 */
/* Cradle's folder sticks (amicradle DRIVE_HOTPLUG.md): vendor $DA15, interface
 * $FF/$AC/$01, a bulk pair carrying ACStorage requests. A host folder, or a USB
 * stick the host mounted (its FAT, exFAT or NTFS), mounted as USB0: to USB9:
 * with L:ACFS by gfopenusbacfs.class (classes/acfs). */
#define OUSB_CLASS_VENDOR      0xFF
#define OUSB_CRADLE_VID        0xDA15
#define OUSB_ACFS_SUBCLASS     0xAC
#define OUSB_ACFS_PROTOCOL     0x01
#define OUSB_ACFSCLASS_NAME    "USB/gfopenusbacfs.class"

/* setup packets: bmRequestType bits */
#define OUSB_RT_IN        0x80
#define OUSB_RT_CLASS     0x20
#define OUSB_RT_VENDOR    0x40
#define OUSB_RT_DEVICE    0x00
#define OUSB_RT_INTERFACE 0x01
#define OUSB_RT_ENDPOINT  0x02
#define OUSB_RT_OTHER     0x03

#endif
