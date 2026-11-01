#ifndef EXEC_INITIALIZERS_H
#define EXEC_INITIALIZERS_H
/*
 * OpenNDK: macros that build the tables InitStruct() reads.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

/* Address of a field in a structure placed at address zero. */
#define OFFSET(structName, structEntry) \
	(&(((struct structName *)0)->structEntry))

/* Each command word: bits 15-14 the action, 13-12 the size, then a 16-bit offset. */
#define INITBYTE(offset, value) \
	0xe000, (UWORD)(offset), (UWORD)((value) << 8)
#define INITWORD(offset, value) \
	0xd000, (UWORD)(offset), (UWORD)(value)
#define INITLONG(offset, value) \
	0xc000, (UWORD)(offset), \
	(UWORD)(((ULONG)(value)) >> 16), (UWORD)(((ULONG)(value)) & 0xffff)
#define INITSTRUCT(size, offset, value, count) \
	(UWORD)(0xc000 | ((size) << 12) | ((count) << 8) | \
		((UWORD)(((ULONG)(offset)) >> 16))), \
	(UWORD)(((ULONG)(offset)) & 0xffff)

#endif /* EXEC_INITIALIZERS_H */
