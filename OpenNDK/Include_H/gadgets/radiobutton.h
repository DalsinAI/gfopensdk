#ifndef GADGETS_RADIOBUTTON_H
#define GADGETS_RADIOBUTTON_H
/*
 * OpenNDK: radiobutton.gadget, one choice from a column of buttons.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif

#define RADIOBUTTON_Dummy	(REACTION_Dummy + 0x14000)

#define RADIOBUTTON_Labels	(RADIOBUTTON_Dummy + 0x0001)	/* struct List * of AllocRadioButtonNode()s */
#define RADIOBUTTON_Strings	(RADIOBUTTON_Dummy + 0x0002)	/* STRPTR *: labels without nodes */
#define RADIOBUTTON_Spacing	(RADIOBUTTON_Dummy + 0x0003)
#define RADIOBUTTON_Selected	(RADIOBUTTON_Dummy + 0x0004)	/* the chosen button, from 0 */
#define RADIOBUTTON_LabelPlace	(RADIOBUTTON_Dummy + 0x0005)

/* A radio button node's attributes */
#define RBNA_Dummy	(TAG_USER + 0x020000)

#define RBNA_UserData	(RBNA_Dummy + 0x0001)
#define RBNA_Label	(RBNA_Dummy + 0x0002)	/* STRPTR */

/* More names from the 3.2 interface */
#define RADIOBUTTON_LabelArray	(RADIOBUTTON_Dummy + 6)
#define RBNA_Disabled		(RBNA_Dummy + 4)
#define RBNA_HintInfo		(RBNA_Dummy + 3)
#define RBNA_Labels		(RBNA_Dummy + 2)

#endif /* GADGETS_RADIOBUTTON_H */
