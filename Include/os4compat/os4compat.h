/* Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * os4compat: build AmigaOS 4 source for AmigaOS 3.2 (m68k), unchanged where
 * we can. OS 4 calls every library through an interface (IExec->AllocVec());
 * this kit gives each OS 3.2 library an interface whose members make the
 * classic call, and adds the OS 4 calls OS 3.2 lacks. Docs/PORTING-OS4.md
 * says how to use it and what it covers.
 *
 * Written from OS 4's public documentation. Names follow OS 4 so source
 * compiles unchanged; the values are ours, since everything is rebuilt.
 */
#ifndef OS4COMPAT_OS4COMPAT_H
#define OS4COMPAT_OS4COMPAT_H

#include <stdarg.h>
#include <exec/types.h>
#include <exec/nodes.h>
#include <exec/lists.h>
#include <exec/ports.h>
#include <exec/io.h>
#include <exec/semaphores.h>
#include <exec/interrupts.h>
#include <exec/memory.h>
#include <utility/tagitem.h>
#include <utility/hooks.h>
#include <dos/dos.h>
#include <dos/dosextens.h>
#include <graphics/gfx.h>
#include <intuition/classes.h>
#include <intuition/classusr.h>

#define OS4COMPAT_VERSION  0
#define OS4COMPAT_REVISION 1

/* ---- OS 4's types ---------------------------------------------------- */
#ifndef OS4C_NO_TYPES
typedef unsigned char      uint8;
typedef signed char        int8;
typedef unsigned short     uint16;
typedef signed short       int16;
typedef unsigned long      uint32;
typedef signed long        int32;
typedef unsigned long long uint64;
typedef signed long long   int64;
typedef float              float32;
typedef double             float64;
#endif
#ifndef APICALL
#define APICALL
#endif
#ifndef VARARGS68K
#define VARARGS68K
#endif
#ifndef __USE_BASETYPE__
#define __USE_BASETYPE__
#endif

/* ---- Interfaces ------------------------------------------------------ */
struct InterfaceData
{
	struct Node    Link;
	struct Library *LibBase;     /* the library this interface calls */
	ULONG          RefCount;
	ULONG          Version;
	ULONG          Flags;
	CONST_STRPTR   LibName;      /* opened on first use when LibBase is 0 */
	APTR           EnvironmentVector;
};

struct Interface
{
	struct InterfaceData Data;
	ULONG (*Obtain)(void);
	ULONG (*Release)(void);
	VOID (*Expunge)(void);
	struct Interface *(*Clone)(void);
};

/* the base a member calls through; opens the library on first use */
#define OS4C_BASE(iface) \
	((iface).Data.LibBase ? (APTR)(iface).Data.LibBase \
	                      : (APTR)os4c_OpenBase((struct Interface *)&(iface)))
struct Library *os4c_OpenBase(struct Interface *iface);

ULONG os4c_IfaceObtain(void);
ULONG os4c_IfaceRelease(void);
VOID os4c_IfaceExpunge(void);
struct Interface *os4c_IfaceClone(void);

/* ---- exec: memory ---------------------------------------------------- */
/* OS 4's memory kinds. OS 3.2 has one kind of memory, so they mean MEMF_ANY. */
#define MEMF_PRIVATE    (1UL << 11)
#define MEMF_SHARED     (1UL << 12)
#define MEMF_EXECUTABLE (1UL << 13)
#define MEMF_OS4ONLY    (MEMF_PRIVATE | MEMF_SHARED | MEMF_EXECUTABLE)

#define AVT_Dummy          (TAG_USER + 0x4f340000)
#define AVT_Type           (AVT_Dummy + 1)  /* MEMF_PRIVATE, MEMF_SHARED, ... */
#define AVT_ClearWithValue (AVT_Dummy + 2)  /* fill with this byte */
#define AVT_Alignment      (AVT_Dummy + 3)  /* power of two, up to 4096 */
#define AVT_Lock           (AVT_Dummy + 4)  /* ignored: no virtual memory */
#define AVT_Contiguous     (AVT_Dummy + 5)  /* ignored */
#define AVT_Wait           (AVT_Dummy + 6)  /* ignored */

/* ---- exec: system objects -------------------------------------------- */
#define ASOT_IOREQUEST 0
#define ASOT_HOOK      1
#define ASOT_INTERRUPT 2
#define ASOT_LIST      3
#define ASOT_DMAENTRY  4   /* not supported: returns 0 */
#define ASOT_NODE      5
#define ASOT_PORT      6
#define ASOT_SEMAPHORE 8
#define ASOT_TAGLIST   9
#define ASOT_MEMPOOL   10
#define ASOT_ITEMPOOL  11  /* not supported: returns 0 */
#define ASOT_RMAP      12  /* not supported: returns 0 */
#define ASOT_MUTEX     13
#define ASOT_EXTMEM    14  /* not supported here: use openextmem.library */
#define ASOT_MESSAGE   15

#define ASO_Dummy          (TAG_USER + 0x4f341000)
#define ASO_NoTrack        (ASO_Dummy + 1)   /* ignored */
#define ASO_MemoryOvr      (ASO_Dummy + 2)   /* MEMF_ flags for the object */

#define ASOIOR_Size        (ASO_Dummy + 10)  /* size of the IORequest */
#define ASOIOR_ReplyPort   (ASO_Dummy + 11)
#define ASOIOR_Duplicate   (ASO_Dummy + 12)  /* copy this IORequest */

#define ASOHOOK_Size       (ASO_Dummy + 20)
#define ASOHOOK_Entry      (ASO_Dummy + 21)
#define ASOHOOK_Subentry   (ASO_Dummy + 22)
#define ASOHOOK_Data       (ASO_Dummy + 23)

#define ASOINTR_Size       (ASO_Dummy + 30)
#define ASOINTR_Code       (ASO_Dummy + 31)
#define ASOINTR_Data       (ASO_Dummy + 32)

#define ASOLIST_Size       (ASO_Dummy + 40)
#define ASOLIST_Type       (ASO_Dummy + 41)
#define ASOLIST_Min        (ASO_Dummy + 42)  /* TRUE: a MinList */

#define ASONODE_Size       (ASO_Dummy + 50)
#define ASONODE_Min        (ASO_Dummy + 51)
#define ASONODE_Type       (ASO_Dummy + 52)
#define ASONODE_Pri        (ASO_Dummy + 53)
#define ASONODE_Name       (ASO_Dummy + 54)

#define ASOPORT_Size       (ASO_Dummy + 60)
#define ASOPORT_AllocSig   (ASO_Dummy + 61)  /* default TRUE */
#define ASOPORT_Action     (ASO_Dummy + 62)  /* PA_SIGNAL, PA_SOFTINT, PA_IGNORE */
#define ASOPORT_Pri        (ASO_Dummy + 63)
#define ASOPORT_Name       (ASO_Dummy + 64)
#define ASOPORT_Signal     (ASO_Dummy + 65)  /* use this signal number */
#define ASOPORT_Target     (ASO_Dummy + 66)  /* task to signal */
#define ASOPORT_Public     (ASO_Dummy + 67)  /* AddPort() it */
#define ASOPORT_CopyName   (ASO_Dummy + 68)

#define ASOSEM_Size        (ASO_Dummy + 70)
#define ASOSEM_Name        (ASO_Dummy + 71)
#define ASOSEM_Pri         (ASO_Dummy + 72)
#define ASOSEM_Public      (ASO_Dummy + 73)  /* AddSemaphore() it */
#define ASOSEM_CopyName    (ASO_Dummy + 74)

#define ASOTAGS_Size       (ASO_Dummy + 80)  /* number of tags */
#define ASOTAGS_NumEntries ASOTAGS_Size

#define ASOPOOL_MFlags     (ASO_Dummy + 90)
#define ASOPOOL_Puddle     (ASO_Dummy + 91)
#define ASOPOOL_Threshold  (ASO_Dummy + 92)
#define ASOPOOL_Protected  (ASO_Dummy + 93)  /* guard with a semaphore */
#define ASOPOOL_Name       (ASO_Dummy + 94)  /* ignored */

#define ASOMUTEX_Recursive (ASO_Dummy + 100) /* always recursive here */

#define ASOMSG_Size        (ASO_Dummy + 110)
#define ASOMSG_ReplyPort   (ASO_Dummy + 111)
#define ASOMSG_Length      (ASO_Dummy + 112)
#define ASOMSG_Name        (ASO_Dummy + 113)

/* ---- dos: 64-bit files and examining --------------------------------- */
#define DOS_EXAMINEDATA   0x4f340001UL  /* FreeDosObject() type */

#define EX_Dummy          (TAG_USER + 0x4f342000)
#define EX_StringNameInput (EX_Dummy + 1)
#define EX_StringName     EX_StringNameInput
#define EX_LockInput      (EX_Dummy + 2)
#define EX_FileLockInput  EX_LockInput
#define EX_FileHandleInput (EX_Dummy + 3)
#define EX_DataFields     (EX_Dummy + 4)  /* EXF_ mask; we always fill all */
#define EX_MatchString    (EX_Dummy + 5)  /* AmigaDOS pattern for ExamineDir() */
#define EX_MatchFunc      (EX_Dummy + 6)  /* struct Hook *, object = ExamineData */
#define EX_DoCurrentDir   (EX_Dummy + 7)  /* ignored */
#define EX_ResetContext   (EX_Dummy + 8)  /* ignored */

#define EXF_TYPE       (1UL << 0)
#define EXF_SIZE       (1UL << 1)
#define EXF_DATE       (1UL << 2)
#define EXF_PROTECTION (1UL << 3)
#define EXF_NAME       (1UL << 4)
#define EXF_COMMENT    (1UL << 5)
#define EXF_LINK       (1UL << 6)
#define EXF_OWNER      (1UL << 7)
#define EXF_OBJECTID   (1UL << 8)
#define EXF_ALL        0xffffffffUL

/* Type: the fib_DirEntryType values */
#define FSO_TYPE_MASK      0xff
#define FSO_TYPE_SOFTLINK  ST_SOFTLINK
#define FSO_TYPE_FILE      ST_FILE
#define FSO_TYPE_DIRECTORY ST_USERDIR

struct ExamineData
{
	struct MinNode   EXDnode;
	ULONG            EXDinfo;
	ULONG            FSPrivate;
	ULONG            Reserved0;
	APTR             Reserved2;
	ULONG            StructSize;
	ULONG            RefCount;
	uint64           ObjectID;      /* fib_DiskKey */
	LONG             Type;          /* ST_FILE, ST_USERDIR, ST_SOFTLINK, ... */
	int64            FileSize;      /* -1 for drawers */
	struct DateStamp Date;
	ULONG            RawProtection; /* as stored: RWED bits are 0 for allowed */
	ULONG            Protection;    /* as OS 4 gives it: RWED bits are 1 for allowed */
	ULONG            OwnerUID;
	ULONG            OwnerGID;
	STRPTR           Name;
	STRPTR           RawLink;
	STRPTR           Link;
	STRPTR           Comment;
	/* the strings live here */
	UBYTE            NameBuffer[108];
	UBYTE            CommentBuffer[80];
	UBYTE            LinkBuffer[256];
};

#define EXD_IS_FILE(d)      ((d)->Type < 0 && (d)->Type != ST_SOFTLINK && (d)->Type != ST_LINKFILE)
#define EXD_IS_DIRECTORY(d) ((d)->Type > 0 && (d)->Type != ST_SOFTLINK && (d)->Type != ST_LINKDIR)
#define EXD_IS_LINK(d)      ((d)->Type == ST_SOFTLINK || (d)->Type == ST_LINKFILE || (d)->Type == ST_LINKDIR)
#define EXD_IS_SOFTLINK(d)  ((d)->Type == ST_SOFTLINK)
#define EXD_IS_PIPE(d)      ((d)->Type == ST_PIPEFILE)
#define EXD_IS_SOCKET(d)    (0)

/* OS 4's Protection bits are set for "allowed", the opposite of FIBF_ */
#define EXDF_NO_READ    (1UL << 3)
#define EXDF_NO_WRITE   (1UL << 2)
#define EXDF_NO_EXECUTE (1UL << 1)
#define EXDF_NO_DELETE  (1UL << 0)

/* ---- graphics -------------------------------------------------------- */
/* NDK 3.2's graphics/gfx.h already has these, with the values P96 and OS 4
 * use; keep its values so code built with and without os4compat agrees */
#ifndef BMATags_Friend
#define BMATags_Friend      (TAG_USER + 0)
#define BMATags_Depth       (TAG_USER + 1)
#define BMATags_RGBFormat   (TAG_USER + 2)
#define BMATags_Clear       (TAG_USER + 3)
#define BMATags_Displayable (TAG_USER + 4)
#define BMATags_Private1    (TAG_USER + 5)
#define BMATags_NoMemory    (TAG_USER + 6)
#define BMATags_NoSprite    (TAG_USER + 7)
#define BMATags_UserPrivate (TAG_USER + 17)
#endif
#ifndef BMATags_PixelFormat
#define BMATags_PixelFormat BMATags_RGBFormat
#endif
#ifndef BMATags_Interleaved
#define BMATags_Interleaved (TAG_USER + 0x4f343004)  /* ours: the NDK has none */
#endif

#define BLITA_Dummy     (TAG_USER + 0x4f344000)
#define BLITA_SrcX      (BLITA_Dummy + 1)
#define BLITA_SrcY      (BLITA_Dummy + 2)
#define BLITA_DestX     (BLITA_Dummy + 3)
#define BLITA_DestY     (BLITA_Dummy + 4)
#define BLITA_Width     (BLITA_Dummy + 5)
#define BLITA_Height    (BLITA_Dummy + 6)
#define BLITA_Source    (BLITA_Dummy + 7)
#define BLITA_Dest      (BLITA_Dummy + 8)
#define BLITA_Minterm   (BLITA_Dummy + 9)
#define BLITA_Mask      (BLITA_Dummy + 10)
#define BLITA_SrcType   (BLITA_Dummy + 11)
#define BLITA_DestType  (BLITA_Dummy + 12)
#define BLITA_UseSrcAlpha (BLITA_Dummy + 13) /* not supported: FALSE */

#define BLITT_BITMAP    0
#define BLITT_RASTPORT  1
#define BLITT_TEMPLATE  2   /* not supported */
#define BLITT_ALPHATEMPLATE 3 /* not supported */
#define BLITT_CHUNKY    4   /* not supported */
#define BLITT_RGB24     5   /* not supported */
#define BLITT_ARGB32    6   /* not supported */

#define COMPOSITE_Clear    0
#define COMPOSITE_Src      1
#define COMPOSITE_Dest     2
#define COMPOSITE_Src_Over_Dest 3
#define COMPOSITE_Dest_Over_Src 4
#define COMPOSITE_Plus     12

#define COMPTAG_Dummy      (TAG_USER + 0x4f345000)
#define COMPTAG_SrcX       (COMPTAG_Dummy + 1)
#define COMPTAG_SrcY       (COMPTAG_Dummy + 2)
#define COMPTAG_SrcWidth   (COMPTAG_Dummy + 3)
#define COMPTAG_SrcHeight  (COMPTAG_Dummy + 4)
#define COMPTAG_OffsetX    (COMPTAG_Dummy + 5)
#define COMPTAG_OffsetY    (COMPTAG_Dummy + 6)
#define COMPTAG_DestX      (COMPTAG_Dummy + 7)
#define COMPTAG_DestY      (COMPTAG_Dummy + 8)
#define COMPTAG_DestWidth  (COMPTAG_Dummy + 9)
#define COMPTAG_DestHeight (COMPTAG_Dummy + 10)
#define COMPTAG_ScaleX     (COMPTAG_Dummy + 11) /* 16.16 fixed point */
#define COMPTAG_ScaleY     (COMPTAG_Dummy + 12)
#define COMPTAG_SrcAlpha   (COMPTAG_Dummy + 13) /* 16.16, 1.0 = opaque */
#define COMPTAG_DestAlpha  (COMPTAG_Dummy + 14)
#define COMPTAG_Flags      (COMPTAG_Dummy + 15)
#define COMPTAG_SrcAlphaMask (COMPTAG_Dummy + 16)
#define COMPTAG_DestAlphaMask (COMPTAG_Dummy + 17)

#define COMPFLAG_SrcFilter      (1UL << 0)
#define COMPFLAG_IgnoreDestAlpha (1UL << 1)
#define COMPFLAG_HardwareOnly   (1UL << 2)
#define COMPFLAG_SrcAlphaOverride (1UL << 3)

#define COMPERR_Success          0
#define COMPERR_Incompatible     1
#define COMPERR_Value            2
#define COMPERR_SoftwareFallback 3
#define COMPERR_OutOfMemory      4
#define COMPERR_Generic          5
#define COMPERR_UnknownOperator  6
#define COMPERR_MissingInput     7

/* ---- the calls the kit adds ------------------------------------------ */
struct IClass;
struct BitMap;
struct RastPort;

struct Library *os4c_OpenLibrary(CONST_STRPTR name, ULONG version);
APTR os4c_AllocVec(ULONG size, ULONG flags);
APTR os4c_AllocMem(ULONG size, ULONG flags);
struct Interface *os4c_GetInterface(struct Library *library, CONST_STRPTR name, ULONG version, struct TagItem *tags);
VOID os4c_DropInterface(struct Interface *iface);
APTR os4c_AllocSysObject(ULONG type, struct TagItem *tags);
APTR os4c_AllocSysObjectTags(ULONG type, ...);
VOID os4c_FreeSysObject(ULONG type, APTR object);
APTR os4c_AllocPooled(APTR pool, ULONG size);
VOID os4c_FreePooled(APTR pool, APTR memory, ULONG size);
APTR os4c_AllocVecPooled(APTR pool, ULONG size);
VOID os4c_FreeVecPooled(APTR pool, APTR memory);
VOID os4c_DeletePool(APTR pool);
APTR os4c_AllocVecTagList(ULONG size, struct TagItem *tags);
APTR os4c_AllocVecTags(ULONG size, ...);
VOID os4c_DebugPrintF(CONST_STRPTR format, ...);
VOID os4c_NewList(struct List *list);
VOID os4c_NewMinList(struct MinList *list);
struct Node *os4c_GetHead(struct List *list);
struct Node *os4c_GetTail(struct List *list);
struct Node *os4c_GetSucc(struct Node *node);
struct Node *os4c_GetPred(struct Node *node);
VOID os4c_MutexObtain(APTR mutex);
BOOL os4c_MutexAttempt(APTR mutex);
VOID os4c_MutexRelease(APTR mutex);

BPTR os4c_FOpen(CONST_STRPTR name, LONG mode, LONG bufsize);
LONG os4c_FClose(BPTR file);
LONG os4c_ChangeFilePosition(BPTR file, int64 position, LONG mode);
int64 os4c_GetFilePosition(BPTR file);
int64 os4c_GetFileSize(BPTR file);
struct ExamineData *os4c_ExamineObject(struct TagItem *tags);
struct ExamineData *os4c_ExamineObjectTags(Tag tag1, ...);
APTR os4c_ObtainDirContext(struct TagItem *tags);
APTR os4c_ObtainDirContextTags(Tag tag1, ...);
struct ExamineData *os4c_ExamineDir(APTR context);
VOID os4c_ReleaseDirContext(APTR context);
VOID os4c_FreeDosObject(ULONG type, APTR object);

ULONG os4c_Strlcpy(STRPTR dst, CONST_STRPTR src, ULONG size);
ULONG os4c_Strlcat(STRPTR dst, CONST_STRPTR src, ULONG size);
LONG os4c_SNPrintf(STRPTR buffer, ULONG size, CONST_STRPTR format, ...);
LONG os4c_VSNPrintf(STRPTR buffer, ULONG size, CONST_STRPTR format, va_list args);
STRPTR os4c_ASPrintf(CONST_STRPTR format, ...);
STRPTR os4c_VASPrintf(CONST_STRPTR format, va_list args);

struct BitMap *os4c_AllocBitMapTagList(ULONG width, ULONG height, ULONG depth, struct TagItem *tags);
struct BitMap *os4c_AllocBitMapTags(ULONG width, ULONG height, ULONG depth, ...);
LONG os4c_BltBitMapTagList(struct TagItem *tags);
LONG os4c_BltBitMapTags(Tag tag1, ...);
ULONG os4c_CompositeTagList(ULONG op, struct BitMap *src, struct BitMap *dst, struct TagItem *tags);
ULONG os4c_CompositeTags(ULONG op, struct BitMap *src, struct BitMap *dst, ...);

ULONG os4c_IDoMethodA(Object *obj, Msg msg);
ULONG os4c_IDoMethod(Object *obj, ULONG methodID, ...);
ULONG os4c_IDoSuperMethodA(struct IClass *cl, Object *obj, Msg msg);
ULONG os4c_IDoSuperMethod(struct IClass *cl, Object *obj, ULONG methodID, ...);
ULONG os4c_ICoerceMethodA(struct IClass *cl, Object *obj, Msg msg);

/* the interfaces built for this program; GetInterface() looks in here */
extern struct Interface *const os4c_registry[];

#endif
