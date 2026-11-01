#ifndef UTILITY_PACK_H
#define UTILITY_PACK_H
/*
 * OpenNDK: pack tables for PackStructureTags() and UnpackStructureTags().
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 *
 * A table entry is a ULONG: bits 0-12 the field's byte offset, 13-15 a
 * bit number, 16-25 the tag's offset from the table's tag base, 26 set
 * when the tag only reports existence, 27-28 the field size, 29 and 30
 * restrict the entry to packing or unpacking, 31 marks a signed field.
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

#define PSTB_SIGNED	31
#define PSTB_UNPACK	30
#define PSTB_PACK	29
#define PSTB_EXISTS	26

#define PSTF_SIGNED	(1L<<PSTB_SIGNED)
#define PSTF_UNPACK	(1L<<PSTB_UNPACK)
#define PSTF_PACK	(1L<<PSTB_PACK)
#define PSTF_EXISTS	(1L<<PSTB_EXISTS)

/* Direction */
#define PKCTRL_PACKUNPACK	0x00000000
#define PKCTRL_PACKONLY		0x40000000
#define PKCTRL_UNPACKONLY	0x20000000

/* Field type */
#define PKCTRL_BYTE		0x80000000
#define PKCTRL_WORD		0x88000000
#define PKCTRL_LONG		0x90000000

#define PKCTRL_UBYTE		0x00000000
#define PKCTRL_UWORD		0x08000000
#define PKCTRL_ULONG		0x10000000

#define PKCTRL_BIT		0x18000000
#define PKCTRL_FLIPBIT		0x98000000

/* Bit number (0-31) of the single bit set in a flag value. */
#define PK_BITNUM1(f) \
	((f) == 0x01 ? 0 : (f) == 0x02 ? 1 : (f) == 0x04 ? 2 : (f) == 0x08 ? 3 : \
	 (f) == 0x10 ? 4 : (f) == 0x20 ? 5 : (f) == 0x40 ? 6 : 7)
#define PK_BITNUM2(f) \
	((f) < 0x100 ? PK_BITNUM1(f) : 8 + PK_BITNUM1((f) >> 8))
#define PK_BITNUM(f) \
	((f) < 0x10000 ? PK_BITNUM2(f) : 16 + PK_BITNUM2((f) >> 16))

/* Byte inside a big-endian word or long that holds the flag's bit. */
#define PK_WORDOFFSET(f)	((f) < 0x100 ? 1 : 0)
#define PK_LONGOFFSET(f) \
	((f) < 0x100 ? 3 : (f) < 0x10000 ? 2 : (f) < 0x1000000 ? 1 : 0)

/* Byte offset of a field. */
#define PK_CALCOFFSET(type, field)	((ULONG)(&((struct type *)0)->field))

/* Table building */
#define PACK_STARTTABLE(tagbase)	(tagbase)
#define PACK_NEWOFFSET(tagbase)		(-1L), (tagbase)
#define PACK_ENDTABLE			0

#define PACK_ENTRY(tagbase, tag, type, field, control) \
	((control) | (((tag) - (tagbase)) << 16L) | PK_CALCOFFSET(type, field))

#define PACK_BYTEBIT(tagbase, tag, type, field, control, flags) \
	((control) | (((tag) - (tagbase)) << 16L) | \
	 PK_CALCOFFSET(type, field) | (PK_BITNUM(flags) << 13L))

#define PACK_WORDBIT(tagbase, tag, type, field, control, flags) \
	((control) | (((tag) - (tagbase)) << 16L) | \
	 (PK_CALCOFFSET(type, field) + PK_WORDOFFSET(flags)) | \
	 ((PK_BITNUM(flags) & 7) << 13L))

#define PACK_LONGBIT(tagbase, tag, type, field, control, flags) \
	((control) | (((tag) - (tagbase)) << 16L) | \
	 (PK_CALCOFFSET(type, field) + PK_LONGOFFSET(flags)) | \
	 ((PK_BITNUM(flags) & 7) << 13L))

#endif /* UTILITY_PACK_H */
