#ifndef EXEC_ALERTS_H
#define EXEC_ALERTS_H
/*
 * OpenNDK: alert numbers passed to Alert().
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 *
 * An alert number is built from a class bit (bit 31), a subsystem in
 * bits 30-24, a general code in bits 23-16 and a specific code below.
 * A general alert is ORed with an AO_ value naming the missing object.
 */

/* Alert classes: dead ends cannot be recovered from */
#define AT_DeadEnd		0x80000000
#define AT_Recovery		0x00000000

/* General problem codes */
#define AG_NoMemory		0x00010000
#define AG_MakeLib		0x00020000
#define AG_OpenLib		0x00030000
#define AG_OpenDev		0x00040000
#define AG_OpenRes		0x00050000
#define AG_IOError		0x00060000
#define AG_NoSignal		0x00070000
#define AG_BadParm		0x00080000
#define AG_CloseLib		0x00090000
#define AG_CloseDev		0x000A0000
#define AG_ProcCreate		0x000B0000

/* The object that failed to open or was missing */
#define AO_ExecLib		0x8001
#define AO_GraphicsLib		0x8002
#define AO_LayersLib		0x8003
#define AO_Intuition		0x8004
#define AO_MathLib		0x8005
#define AO_DOSLib		0x8007
#define AO_RAMLib		0x8008
#define AO_IconLib		0x8009
#define AO_ExpansionLib		0x800A
#define AO_DiskfontLib		0x800B
#define AO_UtilityLib		0x800C
#define AO_KeyMapLib		0x800D
#define AO_AudioDev		0x8010
#define AO_ConsoleDev		0x8011
#define AO_GamePortDev		0x8012
#define AO_KeyboardDev		0x8013
#define AO_TrackDiskDev		0x8014
#define AO_TimerDev		0x8015
#define AO_CIARsrc		0x8020
#define AO_DiskRsrc		0x8021
#define AO_MiscRsrc		0x8022
#define AO_BootStrap		0x8030
#define AO_Workbench		0x8031
#define AO_DiskCopy		0x8032
#define AO_GadTools		0x8033
#define AO_Unknown		0x8035

/* exec.library */
#define AN_ExecLib		0x01000000
#define AN_ExcptVect		0x01000001
#define AN_BaseChkSum		0x01000002
#define AN_LibChkSum		0x01000003
#define AN_MemCorrupt		0x81000005
#define AN_IntrMem		0x81000006
#define AN_InitAPtr		0x01000007
#define AN_SemCorrupt		0x01000008
#define AN_FreeTwice		0x01000009
#define AN_BogusExcpt		0x8100000A
#define AN_IOUsedTwice		0x0100000B
#define AN_MemoryInsane		0x0100000C
#define AN_IOAfterClose		0x0100000D
#define AN_StackProbe		0x0100000E
#define AN_BadFreeAddr		0x0100000F
#define AN_BadSemaphore		0x01000010
#define AN_AVLNotImpl		0x01000011
#define AN_TreeNotImpl		0x01000012

/* graphics.library */
#define AN_GraphicsLib		0x02000000
#define AN_GfxNoMem		0x82010000
#define AN_GfxNoMemMspc		0x82010001
#define AN_LongFrame		0x82010006
#define AN_ShortFrame		0x82010007
#define AN_TextTmpRas		0x02010009
#define AN_BltBitMap		0x8201000A
#define AN_RegionMemory		0x8201000B
#define AN_MakeVPort		0x82010030
#define AN_GfxNewError		0x0200000C
#define AN_GfxFreeError		0x0200000D
#define AN_GfxNoLCM		0x82011234
#define AN_ObsoleteFont		0x02000401

/* layers.library */
#define AN_LayersLib		0x03000000
#define AN_LayersNoMem		0x83010000

/* intuition.library */
#define AN_Intuition		0x04000000
#define AN_GadgetType		0x84000001
#define AN_BadGadget		0x04000001
#define AN_CreatePort		0x84010002
#define AN_ItemAlloc		0x04010003
#define AN_SubAlloc		0x04010004
#define AN_PlaneAlloc		0x84010005
#define AN_ItemBoxTop		0x84000006
#define AN_OpenScreen		0x84010007
#define AN_OpenScrnRast		0x84010008
#define AN_SysScrnType		0x84000009
#define AN_AddSWGadget		0x8401000A
#define AN_OpenWindow		0x8401000B
#define AN_BadState		0x8400000C
#define AN_BadMessage		0x8400000D
#define AN_WeirdEcho		0x8400000E
#define AN_NoConsole		0x8400000F
#define AN_NoISem		0x04000010
#define AN_ISemOrder		0x04000011
#define AN_DeadIntui		0x04000012

/* The maths libraries */
#define AN_MathLib		0x05000000

/* dos.library */
#define AN_DOSLib		0x07000000
#define AN_StartMem		0x07010001
#define AN_EndTask		0x07000002
#define AN_QPktFail		0x07000003
#define AN_AsyncPkt		0x07000004
#define AN_FreeVec		0x07000005
#define AN_DiskBlkSeq		0x07000006
#define AN_BitMap		0x07000007
#define AN_KeyFree		0x07000008
#define AN_BadChkSum		0x07000009
#define AN_DiskError		0x0700000A
#define AN_KeyRange		0x0700000B
#define AN_BadOverlay		0x0700000C
#define AN_BadInitFunc		0x0700000D
#define AN_FileReclosed		0x0700000E
#define AN_CLIObsolete		0x0700000F

/* ramlib */
#define AN_RAMLib		0x08000000
#define AN_BadSegList		0x08000001

/* icon.library */
#define AN_IconLib		0x09000000

/* expansion.library */
#define AN_ExpansionLib		0x0A000000
#define AN_BadExpansionFree	0x0A000001

/* diskfont.library */
#define AN_DiskfontLib		0x0B000000

/* audio.device */
#define AN_AudioDev		0x10000000

/* console.device */
#define AN_ConsoleDev		0x11000000
#define AN_NoWindow		0x11000001

/* gameport.device */
#define AN_GamePortDev		0x12000000

/* keyboard.device */
#define AN_KeyboardDev		0x13000000

/* trackdisk.device */
#define AN_TrackDiskDev		0x14000000
#define AN_TDCalibSeek		0x14000001
#define AN_TDDelay		0x14000002

/* timer.device */
#define AN_TimerDev		0x15000000
#define AN_TMBadReq		0x15000001
#define AN_TMBadSupply		0x15000002

/* cia.resource */
#define AN_CIARsrc		0x20000000

/* disk.resource */
#define AN_DiskRsrc		0x21000000
#define AN_DRHasDisk		0x21000001
#define AN_DRIntNoAct		0x21000002

/* misc.resource */
#define AN_MiscRsrc		0x22000000

/* The boot code */
#define AN_BootStrap		0x30000000
#define AN_BootError		0x30000001

/* Workbench */
#define AN_Workbench		0x31000000
#define AN_NoFonts		0xB1000001
#define AN_WBBadStartupMsg1	0x31000001
#define AN_WBBadStartupMsg2	0x31000002
#define AN_WBBadIOMsg		0x31000003
#define AN_WBReLayoutToolMenu	0xB1010009

/* DiskCopy */
#define AN_DiskCopy		0x32000000

/* gadtools.library */
#define AN_GadTools		0x33000000

/* utility.library */
#define AN_UtilityLib		0x34000000

/* Anything else */
#define AN_Unknown		0x35000000

/* Processor exceptions, by vector number */
#define ACPU_BusErr		0x80000002
#define ACPU_AddressErr		0x80000003
#define ACPU_InstErr		0x80000004
#define ACPU_DivZero		0x80000005
#define ACPU_CHK		0x80000006
#define ACPU_TRAPV		0x80000007
#define ACPU_PrivErr		0x80000008
#define ACPU_Trace		0x80000009
#define ACPU_LineA		0x8000000A
#define ACPU_LineF		0x8000000B
#define ACPU_Format		0x8000000E
#define ACPU_Spurious		0x80000018
#define ACPU_AutoVec1		0x80000019
#define ACPU_AutoVec2		0x8000001A
#define ACPU_AutoVec3		0x8000001B
#define ACPU_AutoVec4		0x8000001C
#define ACPU_AutoVec5		0x8000001D
#define ACPU_AutoVec6		0x8000001E
#define ACPU_AutoVec7		0x8000001F

#endif /* EXEC_ALERTS_H */
