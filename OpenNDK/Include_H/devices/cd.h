#ifndef DEVICES_CD_H
#define DEVICES_CD_H
/*
 * OpenNDK: the CD device commands (cd.device and compatibles), status
 * bits and table-of-contents structures.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif

/* Commands */
#define CD_RESET		1
#define CD_READ			2
#define CD_WRITE		3
#define CD_UPDATE		4
#define CD_CLEAR		5
#define CD_STOP			6
#define CD_START		7
#define CD_FLUSH		8
#define CD_MOTOR		9
#define CD_SEEK			10
#define CD_FORMAT		11
#define CD_REMOVE		12
#define CD_CHANGENUM		13
#define CD_CHANGESTATE		14
#define CD_PROTSTATUS		15

#define CD_GETDRIVETYPE		18
#define CD_GETNUMTRACKS		19
#define CD_ADDCHANGEINT		20
#define CD_REMCHANGEINT		21
#define CD_GETGEOMETRY		22
#define CD_EJECT		23

#define CD_INFO			32
#define CD_CONFIG		33
#define CD_TOCMSF		34
#define CD_TOCLSN		35

#define CD_READXL		36

#define CD_PLAYTRACK		37
#define CD_PLAYMSF		38
#define CD_PLAYLSN		39
#define CD_PAUSE		40
#define CD_SEARCH		41

#define CD_QCODEMSF		42
#define CD_QCODELSN		43
#define CD_ATTENUATE		44

#define CD_ADDFRAMEINT		45
#define CD_REMFRAMEINT		46

/* io_Error */
#define CDERR_OPENFAIL		(-1)
#define CDERR_ABORTED		(-2)
#define CDERR_NOCMD		(-3)
#define CDERR_BADLENGTH		(-4)
#define CDERR_BADADDRESS	(-5)
#define CDERR_UNITBUSY		(-6)
#define CDERR_SELFTEST		(-7)

#define CDERR_NotSpecified	20
#define CDERR_NoSecHdr		21
#define CDERR_BadSecPreamble	22
#define CDERR_BadSecID		23
#define CDERR_BadHdrSum		24
#define CDERR_BadSecSum		25
#define CDERR_TooFewSecs	26
#define CDERR_BadSecHdr		27
#define CDERR_WriteProt		28
#define CDERR_NoDisk		29
#define CDERR_SeekError		30
#define CDERR_NoMem		31
#define CDERR_BadUnitNum	32
#define CDERR_BadDriveType	33
#define CDERR_DriveInUse	34
#define CDERR_PostReset		35
#define CDERR_BadDataType	36
#define CDERR_InvalidState	37

#define CDERR_Phase		42
#define CDERR_NoBoard		50

/* CD_CONFIG tags */
#define TAGCD_PLAYSPEED		0x0001
#define TAGCD_READSPEED		0x0002
#define TAGCD_READXLSPEED	0x0003
#define TAGCD_SECTORSIZE	0x0004
#define TAGCD_XLECC		0x0005
#define TAGCD_EJECTRESET	0x0006

/* What CD_INFO fills */
struct CDInfo {
	UWORD	PlaySpeed;	/* audio play speed */
	UWORD	ReadSpeed;	/* data read speed */
	UWORD	ReadXLSpeed;	/* CD_READXL speed */
	UWORD	SectorSize;	/* 2048 or 2328 */
	UWORD	XLECC;		/* CD_READXL corrects errors */
	UWORD	EjectReset;	/* eject resets the machine */
	UWORD	Reserved1[4];
	UWORD	MaxSpeed;	/* fastest read speed */
	UWORD	AudioPrecision;	/* attenuation steps */
	UWORD	Status;		/* CDSTSF_ */
	UWORD	Reserved2[4];
};

/* CDInfo.Status */
#define CDSTSB_CLOSED		0
#define CDSTSB_DISK		1
#define CDSTSB_SPIN		2
#define CDSTSB_TOC		3
#define CDSTSB_CDROM		4
#define CDSTSB_PLAYING		5
#define CDSTSB_PAUSED		6
#define CDSTSB_SEARCH		7
#define CDSTSB_DIRECTION	8

#define CDSTSF_CLOSED		0x0001
#define CDSTSF_DISK		0x0002
#define CDSTSF_SPIN		0x0004
#define CDSTSF_TOC		0x0008
#define CDSTSF_CDROM		0x0010
#define CDSTSF_PLAYING		0x0020
#define CDSTSF_PAUSED		0x0040
#define CDSTSF_SEARCH		0x0080
#define CDSTSF_DIRECTION	0x0100

/* CD_SEARCH modes */
#define CDMODE_NORMAL	0
#define CDMODE_FFWD	1
#define CDMODE_FREV	2

/* A position as minutes, seconds and frames */
struct RMSF {
	UBYTE	Reserved;	/* 0 */
	UBYTE	Minute;
	UBYTE	Second;
	UBYTE	Frame;
};

/* A position either way: MSF or logical sector number */
union LSNMSF {
	struct RMSF	MSF;
	ULONG		LSN;
};

/* One transfer of a CD_READXL list */
struct CDXL {
	struct MinNode	Node;
	char		*Buffer;	/* word aligned */
	LONG		Length;		/* even */
	LONG		Actual;
	APTR		IntData;	/* for IntCode, in A1 */
	VOID		(*IntCode)(VOID);	/* called when done, or NULL */
};

/* Entry 0 of a table of contents */
struct TOCSummary {
	UBYTE		FirstTrack;
	UBYTE		LastTrack;
	union LSNMSF	LeadOut;	/* the end of the disc */
};

/* Entries 1 on */
struct TOCEntry {
	UBYTE		CtlAdr;
	UBYTE		Track;
	union LSNMSF	Position;
};

union CDTOC {
	struct TOCSummary	Summary;
	struct TOCEntry		Entry;
};

/* What CD_QCODEMSF and CD_QCODELSN return */
struct QCode {
	UBYTE		CtlAdr;
	UBYTE		Track;
	UBYTE		Index;
	UBYTE		Zero;
	union LSNMSF	TrackPosition;
	union LSNMSF	DiskPosition;
};

/* CtlAdr: control nibble */
#define CTLADR_CTLMASK	0xF0

#define CTL_CTLMASK	0xD0
#define CTL_2AUD	0x00	/* two-channel audio */
#define CTL_2AUDEMPH	0x10	/* with pre-emphasis */
#define CTL_4AUD	0x80	/* four-channel audio */
#define CTL_4AUDEMPH	0x90
#define CTL_DATA	0x40	/* a data track */

#define CTL_COPYMASK	0x20
#define CTL_COPY	0x20	/* copying permitted */

/* CtlAdr: address nibble */
#define CTLADR_ADRMASK	0x0F

#define ADR_POSITION	0x01
#define ADR_UPC		0x02
#define ADR_ISRC	0x03
#define ADR_HYBRID	0x05

#endif /* DEVICES_CD_H */
