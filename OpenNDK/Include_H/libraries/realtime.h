#ifndef LIBRARIES_REALTIME_H
#define LIBRARIES_REALTIME_H
/*
 * OpenNDK: realtime.library's conductors, players, tags and base.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif
#ifndef EXEC_LISTS_H
#include <exec/lists.h>
#endif
#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef UTILITY_HOOKS_H
#include <utility/hooks.h>
#endif

/* The clock's rate, in ticks a second */
#define TICK_FREQ	1200

/* A group of players sharing one clock */
struct Conductor {
	struct Node	cdt_Link;
	UWORD		cdt_Reserved0;
	struct MinList	cdt_Players;		/* struct Player */
	ULONG		cdt_ClockTime;		/* the clock now */
	ULONG		cdt_StartTime;		/* the clock at the last start */
	ULONG		cdt_ExternalTime;	/* time from an external sync */
	ULONG		cdt_MaxExternalTime;
	ULONG		cdt_Metronome;
	UWORD		cdt_Reserved1;
	UWORD		cdt_Flags;		/* CONDUCTF_ */
	UBYTE		cdt_State;		/* CONDSTATE_ */
};

/* cdt_Flags */
#define CONDUCTB_EXTERNAL	0
#define CONDUCTB_GOTTICK	1
#define CONDUCTB_METROSET	2
#define CONDUCTB_PRIVATE	3

#define CONDUCTF_EXTERNAL	(1<<CONDUCTB_EXTERNAL)
#define CONDUCTF_GOTTICK	(1<<CONDUCTB_GOTTICK)
#define CONDUCTF_METROSET	(1<<CONDUCTB_METROSET)
#define CONDUCTF_PRIVATE	(1<<CONDUCTB_PRIVATE)

/* cdt_State, and SetConductorState()'s state */
#define CONDSTATE_STOPPED	0
#define CONDSTATE_PAUSED	1
#define CONDSTATE_LOCATE	2
#define CONDSTATE_RUNNING	3

/* SetConductorState() only: not states the conductor stays in */
#define CONDSTATE_METRIC	-1
#define CONDSTATE_SHUTTLE	-2
#define CONDSTATE_LOCATE_SET	-3

/* One client of a conductor */
struct Player {
	struct Node	pl_Link;
	BYTE		pl_Reserved0;
	BYTE		pl_Reserved1;
	struct Hook	*pl_Hook;		/* called with pmTime/pmState */
	struct Conductor *pl_Source;
	struct Task	*pl_Task;		/* signalled at the alarm */
	LONG		pl_MetricTime;
	LONG		pl_AlarmTime;
	APTR		pl_UserData;
	UWORD		pl_PlayerID;
	UWORD		pl_Flags;		/* PLAYERF_ */
};

/* pl_Flags */
#define PLAYERB_READY		0
#define PLAYERB_ALARMSET	1
#define PLAYERB_QUIET		2
#define PLAYERB_CONDUCTED	3
#define PLAYERB_EXTSYNC		4

#define PLAYERF_READY		(1<<PLAYERB_READY)
#define PLAYERF_ALARMSET	(1<<PLAYERB_ALARMSET)
#define PLAYERF_QUIET		(1<<PLAYERB_QUIET)
#define PLAYERF_CONDUCTED	(1<<PLAYERB_CONDUCTED)
#define PLAYERF_EXTSYNC		(1<<PLAYERB_EXTSYNC)

/* Tags for CreatePlayerA(), SetPlayerAttrsA() and GetPlayerAttrsA() */
#define PLAYER_Base		(TAG_USER+64)
#define PLAYER_Hook		(PLAYER_Base+1)
#define PLAYER_Name		(PLAYER_Base+2)
#define PLAYER_Priority		(PLAYER_Base+3)
#define PLAYER_Conductor	(PLAYER_Base+4)
#define PLAYER_Ready		(PLAYER_Base+5)
#define PLAYER_AlarmTime	(PLAYER_Base+12)
#define PLAYER_Alarm		(PLAYER_Base+13)
#define PLAYER_AlarmSigTask	(PLAYER_Base+6)
#define PLAYER_AlarmSigBit	(PLAYER_Base+8)
#define PLAYER_Conducted	(PLAYER_Base+7)
#define PLAYER_Quiet		(PLAYER_Base+9)
#define PLAYER_UserData		(PLAYER_Base+10)
#define PLAYER_ID		(PLAYER_Base+11)
#define PLAYER_ExtSync		(PLAYER_Base+14)
#define PLAYER_ErrorCode	(PLAYER_Base+15)

/* What a player's hook is told */
#define PM_TICK		0
#define PM_STATE	1
#define PM_POSITION	2
#define PM_SHUTTLE	3

struct pmTime {
	ULONG	pmt_Method;	/* PM_TICK, PM_POSITION or PM_SHUTTLE */
	ULONG	pmt_Time;
};

struct pmState {
	ULONG	pms_Method;	/* PM_STATE */
	ULONG	pms_OldState;
};

/* LockRealTime()'s lock types */
#define RT_CONDUCTORS	0

/* Error codes */
#define RTE_NOMEMORY	801
#define RTE_NOCONDUCTOR	802
#define RTE_NOTIMER	803
#define RTE_PLAYING	804

/* The library's base; rtb_Time may be read directly */
struct RealTimeBase {
	struct Library	rtb_LibNode;
	UBYTE		rtb_Reserved0[2];
	ULONG		rtb_Time;
	ULONG		rtb_TimeFrac;
	UWORD		rtb_Reserved1;
	WORD		rtb_TickErr;
};

/* The range of rtb_TickErr, in microseconds */
#define RealTime_TickErr_Min	-705
#define RealTime_TickErr_Max	705

#endif /* LIBRARIES_REALTIME_H */
