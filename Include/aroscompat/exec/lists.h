/* The Open SDK's AROS compatibility: <exec/lists.h> with AROS's list
 * macros: NEWLIST, ForeachNode, ForeachNodeSafe, GetHead, GetTail,
 * GetSucc, GetPred (NULL past either end), and IsListEmpty.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#include_next <exec/lists.h>

#ifndef AROSCOMPAT_EXEC_LISTS_H
#define AROSCOMPAT_EXEC_LISTS_H
#define NEWLIST(l) do { struct List *__l = (struct List *)(l); \
        __l->lh_TailPred = (struct Node *)__l; __l->lh_Tail = NULL; \
        __l->lh_Head = (struct Node *)&__l->lh_Tail; } while (0)
#define ForeachNode(l, n) \
    for ((n) = (void *)((struct List *)(l))->lh_Head; ((struct Node *)(n))->ln_Succ; \
         (n) = (void *)((struct Node *)(n))->ln_Succ)
#define ForeachNodeSafe(l, n, n2) \
    for ((n) = (void *)((struct List *)(l))->lh_Head; \
         ((n2) = (void *)((struct Node *)(n))->ln_Succ) != NULL; (n) = (void *)(n2))
#define GetHead(l) (((struct List *)(l))->lh_Head->ln_Succ ? (void *)((struct List *)(l))->lh_Head : NULL)
#define GetTail(l) (((struct List *)(l))->lh_TailPred->ln_Pred ? (void *)((struct List *)(l))->lh_TailPred : NULL)
#define GetSucc(n) (((struct Node *)(n))->ln_Succ->ln_Succ ? (void *)((struct Node *)(n))->ln_Succ : NULL)
#define GetPred(n) (((struct Node *)(n))->ln_Pred->ln_Pred ? (void *)((struct Node *)(n))->ln_Pred : NULL)
#ifndef IsListEmpty
#define IsListEmpty(l) (((struct List *)(l))->lh_TailPred == (struct Node *)(l))
#endif
#endif
