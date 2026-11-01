#ifndef DOS_DOSEXTENS_H
#define DOS_DOSEXTENS_H
/*
 * OpenNDK: dos.library's inner structures: processes, file handles,
 * packets, the library base and the device list.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_TASKS_H
#include <exec/tasks.h>
#endif
#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif
#ifndef DEVICES_TIMER_H
#include <devices/timer.h>
#endif
#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

/* A dos process: an exec task with dos's state after it. Every
 * process has its own message port for packet replies. */
struct Process {
	struct Task	pr_Task;
	struct MsgPort	pr_MsgPort;
	WORD		pr_Pad;
	BPTR		pr_SegList;		/* array of seglists */
	LONG		pr_StackSize;		/* in bytes */
	APTR		pr_GlobVec;
	LONG		pr_TaskNum;		/* CLI number, 0 if none */
	BPTR		pr_StackBase;
	LONG		pr_Result2;		/* IoErr() */
	BPTR		pr_CurrentDir;
	BPTR		pr_CIS;			/* input stream */
	BPTR		pr_COS;			/* output stream */
	struct MsgPort	*pr_ConsoleTask;		/* console handler's port */
	struct MsgPort	*pr_FileSystemTask;	/* default handler's port */
	BPTR		pr_CLI;			/* struct CommandLineInterface */
	APTR		pr_ReturnAddr;
	APTR		pr_PktWait;		/* replaces WaitPkt() when set */
	APTR		pr_WindowPtr;		/* requester window; -1 for none */
	BPTR		pr_HomeDir;		/* PROGDIR: */
	LONG		pr_Flags;		/* PRF_ */
	VOID		(*pr_ExitCode)(VOID);
	LONG		pr_ExitData;
	STRPTR		pr_Arguments;
	struct MinList	pr_LocalVars;		/* struct LocalVar */
	ULONG		pr_ShellPrivate;
	BPTR		pr_CES;			/* error stream; 0 means pr_COS */
};

/* pr_Flags: what dos frees or closes when the process ends */
#define PRB_FREESEGLIST		0
#define PRF_FREESEGLIST		1
#define PRB_FREECURRDIR		1
#define PRF_FREECURRDIR		2
#define PRB_FREECLI		2
#define PRF_FREECLI		4
#define PRB_CLOSEINPUT		3
#define PRF_CLOSEINPUT		8
#define PRB_CLOSEOUTPUT		4
#define PRF_CLOSEOUTPUT		16
#define PRB_FREEARGS		5
#define PRF_FREEARGS		32

/* The BCPL-era file handle; Open() returns a BPTR to one */
struct FileHandle {
	struct Message	*fh_Link;
	struct MsgPort	*fh_Port;	/* non-zero for interactive streams */
	struct MsgPort	*fh_Type;	/* the handler; 0 for NIL: */
	BPTR		fh_Buf;
	LONG		fh_Pos;
	LONG		fh_End;
	LONG		fh_Funcs;
#define fh_Func1 fh_Funcs
	LONG		fh_Func2;
	LONG		fh_Func3;
	LONG		fh_Args;
#define fh_Arg1 fh_Args
	LONG		fh_Arg2;
};

/* A packet: the request a handler receives */
struct DosPacket {
	struct Message	*dp_Link;	/* the exec message carrying it */
	struct MsgPort	*dp_Port;	/* where to reply */
	LONG		dp_Type;	/* ACTION_ */
	LONG		dp_Res1;
	LONG		dp_Res2;
	LONG		dp_Arg1;
	LONG		dp_Arg2;
	LONG		dp_Arg3;
	LONG		dp_Arg4;
	LONG		dp_Arg5;
	LONG		dp_Arg6;
	LONG		dp_Arg7;
};

/* Older names for some packet fields */
#define dp_Action	dp_Type
#define dp_Status	dp_Res1
#define dp_Status2	dp_Res2
#define dp_BufAddr	dp_Arg1

/* A message and its packet together */
struct StandardPacket {
	struct Message		sp_Msg;
	struct DosPacket	sp_Pkt;
};

/* Packet types */
#define ACTION_NIL		0
#define ACTION_STARTUP		0
#define ACTION_GET_BLOCK	2	/* obsolete */
#define ACTION_SET_MAP		4
#define ACTION_DIE		5
#define ACTION_EVENT		6
#define ACTION_CURRENT_VOLUME	7
#define ACTION_LOCATE_OBJECT	8
#define ACTION_RENAME_DISK	9
#define ACTION_WRITE		'W'
#define ACTION_READ		'R'
#define ACTION_FREE_LOCK	15
#define ACTION_DELETE_OBJECT	16
#define ACTION_RENAME_OBJECT	17
#define ACTION_MORE_CACHE	18
#define ACTION_COPY_DIR		19
#define ACTION_WAIT_CHAR	20
#define ACTION_SET_PROTECT	21
#define ACTION_CREATE_DIR	22
#define ACTION_EXAMINE_OBJECT	23
#define ACTION_EXAMINE_NEXT	24
#define ACTION_DISK_INFO	25
#define ACTION_INFO		26
#define ACTION_FLUSH		27
#define ACTION_SET_COMMENT	28
#define ACTION_PARENT		29
#define ACTION_TIMER		30
#define ACTION_INHIBIT		31
#define ACTION_DISK_TYPE	32
#define ACTION_DISK_CHANGE	33
#define ACTION_SET_DATE		34

#define ACTION_SAME_LOCK	40

#define ACTION_SCREEN_MODE	994

#define ACTION_CHANGE_SIGNAL	995

#define ACTION_READ_RETURN	1001
#define ACTION_WRITE_RETURN	1002
#define ACTION_SEEK		1008
#define ACTION_FINDUPDATE	1004
#define ACTION_FINDINPUT	1005
#define ACTION_FINDOUTPUT	1006
#define ACTION_END		1007

#define ACTION_FORMAT		1020
#define ACTION_MAKE_LINK	1021
#define ACTION_SET_FILE_SIZE	1022
#define ACTION_WRITE_PROTECT	1023
#define ACTION_READ_LINK	1024
#define ACTION_FH_FROM_LOCK	1026
#define ACTION_IS_FILESYSTEM	1027
#define ACTION_CHANGE_MODE	1028
#define ACTION_COPY_DIR_FH	1030
#define ACTION_PARENT_FH	1031
#define ACTION_EXAMINE_ALL	1033
#define ACTION_EXAMINE_FH	1034
#define ACTION_EXAMINE_ALL_END	1035
#define ACTION_SET_OWNER	1036

#define ACTION_LOCK_RECORD	2008
#define ACTION_FREE_RECORD	2009

#define ACTION_ADD_NOTIFY	4097
#define ACTION_REMOVE_NOTIFY	4098

#define ACTION_SERIALIZE_DISK	4200
#define ACTION_GET_DISK_FSSM	4201
#define ACTION_FREE_DISK_FSSM	4202

/* A table of dos error numbers and their messages */
struct ErrorString {
	LONG	*estr_Nums;
	STRPTR	estr_Strings;
};

/* The library base */
struct DosLibrary {
	struct Library		dl_lib;
	struct RootNode		*dl_Root;
	APTR			dl_GV;		/* BCPL global vector */
	LONG			dl_A2;		/* private register values */
	LONG			dl_A5;
	LONG			dl_A6;
	struct ErrorString	*dl_Errors;
	struct timerequest	*dl_TimeReq;	/* private */
	struct Library		*dl_UtilityBase;
	struct Library		*dl_IntuitionBase;
};

/* dos's global state */
struct RootNode {
	BPTR		rn_TaskArray;		/* [count, port 1 .. port count] */
	BPTR		rn_ConsoleSegment;	/* the CLI's seglist */
	struct DateStamp rn_Time;		/* the current time */
	LONG		rn_RestartSeg;
	BPTR		rn_Info;		/* struct DosInfo */
	BPTR		rn_FileHandlerSegment;
	struct MinList	rn_CliList;		/* struct CliProcList */
	struct MsgPort	*rn_BootProc;
	BPTR		rn_ShellSegment;
	LONG		rn_Flags;		/* RNF_ */
};

#define RNB_WILDSTAR	24
#define RNF_WILDSTAR	(1L<<RNB_WILDSTAR)
#define RNB_PRIVATE1	1
#define RNF_PRIVATE1	(1L<<RNB_PRIVATE1)

/* One block of CLI process ports (private) */
struct CliProcList {
	struct MinNode	cpl_Node;
	LONG		cpl_First;	/* the first CLI number held here */
	struct MsgPort	**cpl_Array;	/* [0] is the count */
};

/* The device list and its locks */
struct DosInfo {
	BPTR	di_McName;		/* the resident segment list */
#define di_ResList di_McName
	BPTR	di_DevInfo;		/* the DosList */
	BPTR	di_Devices;
	BPTR	di_Handlers;
	APTR	di_NetHand;
	struct SignalSemaphore di_DevLock;
	struct SignalSemaphore di_EntryLock;
	struct SignalSemaphore di_DeleteLock;
};

/* A resident command or handler (Resident, the shell's list) */
struct Segment {
	BPTR	seg_Next;
	LONG	seg_UC;			/* use count, or CMD_ below */
	BPTR	seg_Seg;
	UBYTE	seg_Name[4];		/* a BSTR, as long as the name */
};

#define CMD_SYSTEM	(-1)
#define CMD_INTERNAL	(-2)
#define CMD_DISABLED	(-999)

/* A CLI's state; pr_CLI points to it */
struct CommandLineInterface {
	LONG	cli_Result2;		/* the last command's IoErr() */
	BSTR	cli_SetName;		/* current directory's name */
	BPTR	cli_CommandDir;		/* the path list */
	LONG	cli_ReturnCode;
	BSTR	cli_CommandName;
	LONG	cli_FailLevel;
	BSTR	cli_Prompt;
	BPTR	cli_StandardInput;
	BPTR	cli_CurrentInput;
	BSTR	cli_CommandFile;	/* the script being run */
	LONG	cli_Interactive;
	LONG	cli_Background;
	BPTR	cli_CurrentOutput;
	LONG	cli_DefaultStack;	/* in longwords */
	BPTR	cli_StandardOutput;
	BPTR	cli_Module;		/* the command's seglist */
};

/* A volume entry in the 1.x style; struct DosList replaces it */
struct DeviceList {
	BPTR		dl_Next;
	LONG		dl_Type;	/* DLT_VOLUME */
	struct MsgPort	*dl_Task;
	BPTR		dl_Lock;
	struct DateStamp dl_VolumeDate;
	BPTR		dl_LockList;
	LONG		dl_DiskType;
	LONG		dl_unused;
	BSTR		dl_Name;
};

/* A generic entry in the 1.x style; struct DosList replaces it */
struct DevInfo {
	BPTR	dvi_Next;
	LONG	dvi_Type;
	APTR	dvi_Task;
	BPTR	dvi_Lock;
	BSTR	dvi_Handler;
	LONG	dvi_StackSize;
	LONG	dvi_Priority;
	LONG	dvi_Startup;
	BPTR	dvi_SegList;
	BPTR	dvi_GlobVec;
	BSTR	dvi_Name;
};

/* One entry of the device list: a device, a volume or an assign */
struct DosList {
	BPTR		dol_Next;
	LONG		dol_Type;	/* DLT_ */
	struct MsgPort	*dol_Task;	/* the handler's port */
	BPTR		dol_Lock;
	union {
		struct {
			BSTR	dol_Handler;	/* handler file to load */
			LONG	dol_StackSize;
			LONG	dol_Priority;
			ULONG	dol_Startup;
			BPTR	dol_SegList;
			BPTR	dol_GlobVec;
		} dol_handler;
		struct {
			struct DateStamp dol_VolumeDate;
			BPTR	dol_LockList;
			LONG	dol_DiskType;
		} dol_volume;
		struct {
			STRPTR	dol_AssignName;	/* late and non-binding assigns */
			struct AssignList *dol_List;	/* further directories */
		} dol_assign;
	} dol_misc;
	BSTR		dol_Name;
};

/* An extra directory of a multi-directory assign */
struct AssignList {
	struct AssignList	*al_Next;
	BPTR			al_Lock;
};

/* dol_Type */
#define DLT_DEVICE	0
#define DLT_DIRECTORY	1	/* an assign */
#define DLT_VOLUME	2
#define DLT_LATE	3
#define DLT_NONBINDING	4
#define DLT_PRIVATE	(-1)

/* What GetDeviceProc() returns */
struct DevProc {
	struct MsgPort	*dvp_Port;
	BPTR		dvp_Lock;
	ULONG		dvp_Flags;
	struct DosList	*dvp_DevNode;	/* private */
};

#define DVPB_UNLOCK	0
#define DVPF_UNLOCK	(1L<<DVPB_UNLOCK)
#define DVPB_ASSIGN	1
#define DVPF_ASSIGN	(1L<<DVPB_ASSIGN)

/* LockDosList() and friends: which lists and what access */
#define LDB_READ	0
#define LDF_READ	(1L<<LDB_READ)
#define LDB_WRITE	1
#define LDF_WRITE	(1L<<LDB_WRITE)
#define LDB_DEVICES	2
#define LDF_DEVICES	(1L<<LDB_DEVICES)
#define LDB_VOLUMES	3
#define LDF_VOLUMES	(1L<<LDB_VOLUMES)
#define LDB_ASSIGNS	4
#define LDF_ASSIGNS	(1L<<LDB_ASSIGNS)
#define LDB_ENTRY	5
#define LDF_ENTRY	(1L<<LDB_ENTRY)
#define LDB_DELETE	6
#define LDF_DELETE	(1L<<LDB_DELETE)

#define LDF_ALL		(LDF_DEVICES|LDF_VOLUMES|LDF_ASSIGNS)

/* A lock as the handler keeps it; Lock() returns a BPTR to one */
struct FileLock {
	BPTR		fl_Link;	/* the handler's chain */
	LONG		fl_Key;
	LONG		fl_Access;	/* SHARED_LOCK or EXCLUSIVE_LOCK */
	struct MsgPort	*fl_Task;	/* the handler's port */
	BPTR		fl_Volume;	/* the volume's DosList entry */
};

/* ErrorReport() types */
#define REPORT_STREAM	0
#define REPORT_TASK	1
#define REPORT_LOCK	2
#define REPORT_VOLUME	3
#define REPORT_INSERT	4

/* Codes ErrorReport() takes beyond the IoErr() ones */
#define ABORT_DISK_ERROR	296
#define ABORT_BUSY		288

/* RunCommand()-style shell start types */
#define RUN_EXECUTE		(-1)
#define RUN_SYSTEM		(-2)
#define RUN_SYSTEM_ASYNCH	(-3)

/* fib_DirEntryType: >= 0 directories, < 0 files */
#define ST_ROOT		1
#define ST_USERDIR	2
#define ST_SOFTLINK	3
#define ST_LINKDIR	4
#define ST_FILE		(-3)
#define ST_LINKFILE	(-4)
#define ST_PIPEFILE	(-5)

/* More names from the 3.2 interface */
#define ACTION_UNDISK_INFO	0x201
#define PRB_CLOSEERROR		6
#define PRF_CLOSEERROR		64

#endif /* DOS_DOSEXTENS_H */
