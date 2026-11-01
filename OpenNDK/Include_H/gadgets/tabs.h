#ifndef GADGETS_TABS_H
#define GADGETS_TABS_H
/*
 * OpenNDK: tabs.gadget, a simple row of tabs from an array.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif
#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef UTILITY_TAGITEM_H
#include <utility/tagitem.h>
#endif

#define TABS_Dummy	(TAG_USER + 0x04000000)

#define TABS_Labels	(TABS_Dummy + 0x0001)	/* struct TabLabel *, ended by a NULL tl_Label */
#define TABS_Current	(TABS_Dummy + 0x0002)	/* the current tab, from 0 */

/* tl_Pens indices */
#define TL_TEXTPEN		0
#define TL_BACKGROUNDPEN	1
#define TL_FILLTEXTPEN		2
#define TL_FILLPEN		3
#define MAX_TL_PENS		4

struct TabLabel
{
	STRPTR		tl_Label;
	WORD		tl_Pens[MAX_TL_PENS];	/* -1: the default */
	struct TagItem	*tl_Attrs;
};

#endif /* GADGETS_TABS_H */
