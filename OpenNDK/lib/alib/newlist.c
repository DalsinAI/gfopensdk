/* Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE). */
/* NewList: an empty list points its head at its tail and its tail
 * predecessor back at its head. */
#include "alib.h"

VOID NewList(struct List *list)
{
	list->lh_Head = (struct Node *)&list->lh_Tail;
	list->lh_Tail = NULL;
	list->lh_TailPred = (struct Node *)&list->lh_Head;
}
