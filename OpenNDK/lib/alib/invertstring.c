/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* InvertString: the chain of raw key input events that types a string with
 * a keymap (NULL is the default one), for commodities to feed AddIEvents.
 * Plain characters go through keymap.library's MapANSI (a character behind a
 * dead key gets the dead key as its ie_Prev1Down code). "<description>" is
 * one event from a commodities input description (ParseIX), such as
 * "<alt f1>". "\n" and "\r" are the Return key, "\t" the Tab key, and "\\"
 * or "\<" a plain backslash or "<". Free the chain with FreeIEvents. */
#include "alib.h"
#include <devices/inputevent.h>
#include <libraries/commodities.h>
#include <proto/commodities.h>
#include <proto/keymap.h>

static struct InputEvent *new_event(struct InputEvent ***tail)
{
	struct InputEvent *ie = AllocMem(sizeof(*ie), MEMF_PUBLIC | MEMF_CLEAR);
	if (ie) {
		ie->ie_Class = IECLASS_RAWKEY;
		**tail = ie;
		*tail = &ie->ie_NextEvent;
	}
	return ie;
}

struct InputEvent *InvertString(CONST_STRPTR str, CONST struct KeyMap *km)
{
	struct InputEvent *head = NULL, **tail = &head, *ie;
	if (!str)
		return NULL;
	while (*str) {
		UBYTE c = *str++;
		if (c == '<') {
			char desc[128];
			ULONG n = 0;
			IX ix;
			while (*str && *str != '>') {
				if (n < sizeof(desc) - 1)
					desc[n++] = *str;
				str++;
			}
			if (*str == '>')
				str++;
			desc[n] = 0;
			if (ParseIX((CONST_STRPTR)desc, &ix) != 0)
				goto fail;
			if (!(ie = new_event(&tail)))
				goto fail;
			ie->ie_Class = ix.ix_Class;
			ie->ie_Code = ix.ix_Code;
			ie->ie_Qualifier = ix.ix_Qualifier;
			continue;
		}
		if (c == '\\' && *str) {
			UBYTE e = *str++;
			if (e == 'n' || e == 'r' || e == 't') {
				if (!(ie = new_event(&tail)))
					goto fail;
				ie->ie_Code = e == 't' ? 0x42 : 0x44;
				continue;
			}
			c = e;
		}
		{
			UBYTE keys[4];
			LONG got = MapANSI((CONST_STRPTR)&c, 1, (STRPTR)keys, 2, (struct KeyMap *)km);
			if (got < 1)
				goto fail;
			if (!(ie = new_event(&tail)))
				goto fail;
			if (got >= 2) {
				ie->ie_Prev1DownCode = keys[0];
				ie->ie_Prev1DownQual = keys[1];
				ie->ie_Code = keys[2];
				ie->ie_Qualifier = keys[3];
			} else {
				ie->ie_Code = keys[0];
				ie->ie_Qualifier = keys[1];
			}
		}
	}
	return head;
fail:
	FreeIEvents(head);
	return NULL;
}
