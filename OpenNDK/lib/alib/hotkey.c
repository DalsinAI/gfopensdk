/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* HotKey and FreeIEvents: a commodities filter that sends to a port and
 * swallows the event; and freeing a chain of input events. */
#include "alib.h"
#include <libraries/commodities.h>
#include <proto/commodities.h>

CxObj *HotKey(CONST_STRPTR description, struct MsgPort *port, LONG id)
{
	CxObj *filter = CxFilter(description);
	if (!filter)
		return NULL;
	AttachCxObj(filter, CxSender(port, id));
	AttachCxObj(filter, CxTranslate(NULL));
	if (CxObjError(filter)) {
		DeleteCxObjAll(filter);
		return NULL;
	}
	return filter;
}

VOID FreeIEvents(struct InputEvent *events)
{
	while (events) {
		struct InputEvent *next = events->ie_NextEvent;
		FreeMem(events, sizeof(*events));
		events = next;
	}
}
