#ifndef GADGETS_STRING_H
#define GADGETS_STRING_H
/*
 * OpenNDK: string.gadget, ReAction's text field (strgclass's STRINGA_ tags apply).
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif
#ifndef INTUITION_SGHOOKS_H
#include <intuition/sghooks.h>
#endif

/* Tags of ReAction's own, beside intuition/gadgetclass.h's STRINGA_ */
#define STRINGA_MinVisible	(REACTION_Dummy + 0x0055000)	/* characters always shown */
#define STRINGA_HookType	(REACTION_Dummy + 0x0055001)	/* SHK_ below */
#define STRINGA_GetBlockPos	(REACTION_Dummy + 0x0055010)	/* (get) the marked block */
#define STRINGA_Mark		(REACTION_Dummy + 0x0055011)	/* mark a block */
#define STRINGA_AllowMarking	(REACTION_Dummy + 0x0055012)	/* BOOL */

/* Built-in edit hooks */
#define SHK_CUSTOM	0
#define SHK_PASSWORD	1
#define SHK_IPADDRESS	2
#define SHK_FLOAT	3
#define SHK_HEXIDECIMAL	4
#define SHK_TELEPHONE	5
#define SHK_POSTALCODE	6
#define SHK_AMOUNT	7
#define SHK_UPPERCASE	8
#define SHK_HOTKEY	9

/* More names from the 3.2 interface */
#define SHK_HEXADECIMAL		4
#define STRINGA_ASLTags		0x85055013UL
#define STRINGA_DisablePopup	0x85055015UL
#define STRINGA_InterimUpdates	0x85055013UL
#define STRINGA_MarkActive	0x85055014UL
#define STRINGA_MaxVal		0x85055017UL
#define STRINGA_MinVal		0x85055016UL
#define STRINGA_RelVerifySpecial	0x8505500AUL

#endif /* GADGETS_STRING_H */
