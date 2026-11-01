#ifndef DATATYPES_PICTURECLASS_H
#define DATATYPES_PICTURECLASS_H
/*
 * OpenNDK: picture.datatype's attributes, methods and IFF ILBM chunks.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif
#ifndef DATATYPES_DATATYPESCLASS_H
#include <datatypes/datatypesclass.h>
#endif
#ifndef LIBRARIES_IFFPARSE_H
#include <libraries/iffparse.h>
#endif
#ifndef GRAPHICS_GFX_H
#include <graphics/gfx.h>
#endif

#define PICTUREDTCLASS	"picture.datatype"

/* Attributes */
#define PDTA_ModeID		(DTA_Dummy + 200)	/* the display mode */
#define PDTA_BitMapHeader	(DTA_Dummy + 201)	/* struct BitMapHeader * */
#define PDTA_BitMap		(DTA_Dummy + 202)	/* the source bitmap */
#define PDTA_ColorRegisters	(DTA_Dummy + 203)	/* struct ColorRegister * */
#define PDTA_CRegs		(DTA_Dummy + 204)	/* ULONG * of 32-bit colours */
#define PDTA_GRegs		(DTA_Dummy + 205)	/* the same, remapped */
#define PDTA_ColorTable		(DTA_Dummy + 206)	/* the pens, source to screen */
#define PDTA_ColorTable2	(DTA_Dummy + 207)
#define PDTA_Allocated		(DTA_Dummy + 208)
#define PDTA_NumColors		(DTA_Dummy + 209)
#define PDTA_NumAlloc		(DTA_Dummy + 210)	/* pens allocated */
#define PDTA_Remap		(DTA_Dummy + 211)	/* remap to the screen */
#define PDTA_Screen		(DTA_Dummy + 212)	/* the screen to remap for */
#define PDTA_FreeSourceBitMap	(DTA_Dummy + 213)
#define PDTA_Grab		(DTA_Dummy + 214)	/* Point * hot spot */
#define PDTA_DestBitMap		(DTA_Dummy + 215)	/* the remapped bitmap */
#define PDTA_ClassBitMap	(DTA_Dummy + 216)
#define PDTA_NumSparse		(DTA_Dummy + 217)	/* entries in PDTA_SparseTable */
#define PDTA_SparseTable	(DTA_Dummy + 218)	/* UBYTE * of the pens to use */
#define PDTA_WhichPicture	(DTA_Dummy + 219)	/* which picture of several */
#define PDTA_GetNumPictures	(DTA_Dummy + 220)
#define PDTA_MaxDitherPens	(DTA_Dummy + 221)
#define PDTA_DitherQuality	(DTA_Dummy + 222)
#define PDTA_AllocatedPens	(DTA_Dummy + 223)
#define PDTA_ScaleQuality	(DTA_Dummy + 224)
#define PDTA_SourceMode		(DTA_Dummy + 250)	/* PMODE_ */
#define PDTA_DestMode		(DTA_Dummy + 251)
#define PDTA_UseFriendBitMap	(DTA_Dummy + 255)
#define PDTA_MaskPlane		(DTA_Dummy + 258)

/* PDTA_SourceMode and PDTA_DestMode */
#define PMODE_V42	0	/* planar, as version 42 classes */
#define PMODE_V43	1	/* chunky and true colour too */

/* Methods */
#define PDTM_Dummy		(DTM_Dummy + 0x60)
#define PDTM_WRITEPIXELARRAY	(PDTM_Dummy + 0)
#define PDTM_READPIXELARRAY	(PDTM_Dummy + 1)
#define PDTM_SCALE		(PDTM_Dummy + 2)

/* PDTM_WRITEPIXELARRAY and PDTM_READPIXELARRAY */
struct pdtBlitPixelArray {
	ULONG	MethodID;
	APTR	pbpa_PixelData;
	ULONG	pbpa_PixelFormat;	/* PBPAFMT_ */
	ULONG	pbpa_PixelArrayMod;	/* bytes a row */
	ULONG	pbpa_Left;
	ULONG	pbpa_Top;
	ULONG	pbpa_Width;
	ULONG	pbpa_Height;
};

/* pbpa_PixelFormat */
#define PBPAFMT_RGB	0
#define PBPAFMT_RGBA	1
#define PBPAFMT_ARGB	2
#define PBPAFMT_LUT8	3
#define PBPAFMT_GREY8	4

/* PDTM_SCALE */
struct pdtScale {
	ULONG	MethodID;
	ULONG	ps_NewWidth;
	ULONG	ps_NewHeight;
	ULONG	ps_Flags;
};

/* ps_Flags */
#define PScale_KeepAspect	0x10

/* An ILBM's BMHD chunk */
struct BitMapHeader {
	UWORD	bmh_Width;
	UWORD	bmh_Height;
	WORD	bmh_Left;
	WORD	bmh_Top;
	UBYTE	bmh_Depth;
	UBYTE	bmh_Masking;		/* msk */
	UBYTE	bmh_Compression;	/* cmp */
	UBYTE	bmh_Pad;		/* BMHDF_ */
	UWORD	bmh_Transparent;	/* the transparent colour */
	UBYTE	bmh_XAspect;
	UBYTE	bmh_YAspect;
	WORD	bmh_PageWidth;
	WORD	bmh_PageHeight;
};

/* bmh_Masking */
#define mskNone			0
#define mskHasMask		1
#define mskHasTransparentColor	2
#define mskLasso		3
#define mskHasAlpha		4

/* bmh_Compression */
#define cmpNone		0
#define cmpByteRun1	1
#define cmpByteRun2	2

/* bmh_Pad */
#define BMHDB_CMAPOK	7	/* the colour map has 8 significant bits */
#define BMHDF_CMAPOK	(1<<BMHDB_CMAPOK)

/* One CMAP entry */
struct ColorRegister {
	UBYTE	red;
	UBYTE	green;
	UBYTE	blue;
};

/* ILBM chunks */
#define ID_ILBM	MAKE_ID('I','L','B','M')
#define ID_BMHD	MAKE_ID('B','M','H','D')
#define ID_CMAP	MAKE_ID('C','M','A','P')
#define ID_CRNG	MAKE_ID('C','R','N','G')
#define ID_GRAB	MAKE_ID('G','R','A','B')
#define ID_SPRT	MAKE_ID('S','P','R','T')
#define ID_DEST	MAKE_ID('D','E','S','T')
#define ID_CAMG	MAKE_ID('C','A','M','G')
#ifndef ID_BODY
#define ID_BODY	MAKE_ID('B','O','D','Y')
#endif

/* PDTM_OBTAINPIXELARRAY's message */
struct pdtObtainPixelArray
{
    ULONG MethodID;
    APTR popa_PixelArray;		/* filled in */
    ULONG popa_Flags;
};

/* More names from the 3.2 interface */
#define PDTANUMPICTURES_Unknown	0
#define PDTA_AlphaChannel	0x80001100UL
#define PDTA_ForeignPlaceholder1	0x80001103UL
#define PDTA_ObtainPixelBuffer	0x80001104UL
#define PDTA_SubClassRendersAll	0x80001105UL
#define PDTM_OBTAINPIXELARRAY	0x667
#define POBAB_WRITEGREY8	0
#define POPAF_WRITEGREY8	1

#endif /* DATATYPES_PICTURECLASS_H */
