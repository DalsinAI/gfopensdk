#ifndef EXEC_EXECBASE_H
#define EXEC_EXECBASE_H
/*
 * OpenNDK: exec.library's base, the system's central structure.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_INTERRUPTS_H
#include <exec/interrupts.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef EXEC_TASKS_H
#include <exec/tasks.h>
#endif

struct ExecBase {
	struct Library LibNode;

	UWORD	SoftVer;	/* kickstart release */
	WORD	LowMemChkSum;
	ULONG	ChkBase;	/* complement of the base's address */
	APTR	ColdCapture;	/* reset hooks */
	APTR	CoolCapture;
	APTR	WarmCapture;
	APTR	SysStkUpper;	/* supervisor stack */
	APTR	SysStkLower;
	ULONG	MaxLocMem;	/* top of chip memory */
	APTR	DebugEntry;
	APTR	DebugData;
	APTR	AlertData;
	APTR	MaxExtMem;	/* top of slow memory, or 0 */

	UWORD	ChkSum;		/* sum of the words above */

	struct IntVector IntVects[16];

	struct Task *ThisTask;	/* the running task */
	ULONG	IdleCount;
	ULONG	DispCount;
	UWORD	Quantum;	/* time slice */
	UWORD	Elapsed;
	UWORD	SysFlags;	/* private */
	BYTE	IDNestCnt;
	BYTE	TDNestCnt;

	UWORD	AttnFlags;	/* CPU and FPU present (AFF_) */
	UWORD	AttnResched;	/* private */
	APTR	ResModules;	/* resident module array */
	APTR	TaskTrapCode;
	APTR	TaskExceptCode;
	APTR	TaskExitCode;
	ULONG	TaskSigAlloc;
	UWORD	TaskTrapAlloc;

	/* System lists */
	struct List MemList;
	struct List ResourceList;
	struct List DeviceList;
	struct List IntrList;
	struct List LibList;
	struct List PortList;
	struct List TaskReady;
	struct List TaskWait;

	struct SoftIntList SoftInts[5];

	LONG	LastAlert[4];

	UBYTE	VBlankFrequency;
	UBYTE	PowerSupplyFrequency;

	struct List SemaphoreList;

	/* Kickstart resident and memory hooks */
	APTR	KickMemPtr;
	APTR	KickTagPtr;
	APTR	KickCheckSum;

	/* V36 and later */
	UWORD	ex_Pad0;
	ULONG	ex_LaunchPoint;	/* private */
	APTR	ex_RamLibPrivate;
	ULONG	ex_EClockFrequency;	/* E clock ticks per second */
	ULONG	ex_CacheControl;	/* private */
	ULONG	ex_TaskID;
	ULONG	ex_Reserved1[5];
	APTR	ex_MMULock;	/* private */
	ULONG	ex_Reserved2[3];

	/* V39 and later */
	struct MinList ex_MemHandlers;
	APTR	ex_MemHandler;	/* private */
};

/* AttnFlags: the processor and maths unit fitted */
#define AFB_68010	0
#define AFB_68020	1
#define AFB_68030	2
#define AFB_68040	3
#define AFB_68881	4
#define AFB_68882	5
#define AFB_FPU40	6
#define AFB_68060	7
#define AFB_PRIVATE	15

#define AFF_68010	(1L<<0)
#define AFF_68020	(1L<<1)
#define AFF_68030	(1L<<2)
#define AFF_68040	(1L<<3)
#define AFF_68881	(1L<<4)
#define AFF_68882	(1L<<5)
#define AFF_FPU40	(1L<<6)
#define AFF_68060	(1L<<7)
#define AFF_PRIVATE	(1L<<15)

/* Cache bits for CacheControl() and CacheClearE() */
#define CACRB_EnableI		0
#define CACRB_FreezeI		1
#define CACRB_ClearI		3
#define CACRB_IBE		4
#define CACRB_EnableD		8
#define CACRB_FreezeD		9
#define CACRB_ClearD		11
#define CACRB_DBE		12
#define CACRB_WriteAllocate	13
#define CACRB_EnableE		30
#define CACRB_CopyBack		31

#define CACRF_EnableI		(1L<<0)
#define CACRF_FreezeI		(1L<<1)
#define CACRF_ClearI		(1L<<3)
#define CACRF_IBE		(1L<<4)
#define CACRF_EnableD		(1L<<8)
#define CACRF_FreezeD		(1L<<9)
#define CACRF_ClearD		(1L<<11)
#define CACRF_DBE		(1L<<12)
#define CACRF_WriteAllocate	(1L<<13)
#define CACRF_EnableE		(1L<<30)
#define CACRF_CopyBack		(1UL<<31)

/* Flags for CachePreDMA() and CachePostDMA() */
#define DMA_Continue		(1L<<1)
#define DMA_NoModify		(1L<<2)
#define DMA_ReadFromRAM		(1L<<3)

/* More names from the 3.2 interface */
#define AFB_FPGA		10
#define AFF_FPGA		0x400

#endif /* EXEC_EXECBASE_H */
