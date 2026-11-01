/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* HookEntry: put in h_Entry when h_SubEntry is a C function taking
 * (hook, object, message) on the stack. */
#if defined(__ELF__)
#define SYM(x) x
#define R(x) %x
#else
#define SYM(x) _##x
#define R(x) x
#endif
	.text
	.even
	.globl	SYM(HookEntry)
SYM(HookEntry):
	move.l	R(a1),-(R(sp))
	move.l	R(a2),-(R(sp))
	move.l	R(a0),-(R(sp))
	move.l	12(R(a0)),R(a0)
	jsr	(R(a0))
	lea	12(R(sp)),R(sp)
	rts
