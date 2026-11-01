#ifndef UTILITY_TAGITEM_H
#define UTILITY_TAGITEM_H
/*
 * OpenNDK: tag items, the keyword/value pairs most OS calls take.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif

typedef ULONG Tag;

struct TagItem {
	Tag	ti_Tag;		/* what the value means */
	ULONG	ti_Data;	/* the value */
};

/* Control tags understood by every tag list walker */
#define TAG_DONE	(0L)	/* the end of the list */
#define TAG_END		(0L)
#define TAG_IGNORE	(1L)	/* skip this item */
#define TAG_MORE	(2L)	/* continue at the list in ti_Data */
#define TAG_SKIP	(3L)	/* skip this item and ti_Data more */

/* Tags at or above this are a caller's own */
#define TAG_USER	((ULONG)(1UL<<31))

/* FilterTagItems() logic */
#define TAGFILTER_AND	0
#define TAGFILTER_NOT	1

/* MapTags() modes */
#define MAP_REMOVE_NOT_FOUND	0
#define MAP_KEEP_NOT_FOUND	1

#endif /* UTILITY_TAGITEM_H */
