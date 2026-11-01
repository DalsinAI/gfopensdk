#ifndef GADGETS_GETFILE_H
#define GADGETS_GETFILE_H
/*
 * OpenNDK: getfile.gadget, a file name field with a file requester behind it.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef REACTION_REACTION_H
#include <reaction/reaction.h>
#endif
#ifndef INTUITION_GADGETCLASS_H
#include <intuition/gadgetclass.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif

#define GETFILE_Dummy		(REACTION_Dummy + 0x60000)

#define GETFILE_TitleText	(GETFILE_Dummy + 1)	/* the requester's title */
#define GETFILE_LeftEdge	(GETFILE_Dummy + 2)	/* the requester's box */
#define GETFILE_TopEdge		(GETFILE_Dummy + 3)
#define GETFILE_Width		(GETFILE_Dummy + 4)
#define GETFILE_Height		(GETFILE_Dummy + 5)
#define GETFILE_FullFile	(GETFILE_Dummy + 8)	/* STRPTR: drawer and file together */
#define GETFILE_File		(GETFILE_Dummy + 6)
#define GETFILE_Drawer		(GETFILE_Dummy + 7)
#define GETFILE_Pattern		(GETFILE_Dummy + 10)
#define GETFILE_DoSaveMode	(GETFILE_Dummy + 11)
#define GETFILE_DoMultiSelect	(GETFILE_Dummy + 12)
#define GETFILE_DoPatterns	(GETFILE_Dummy + 13)
#define GETFILE_DrawersOnly	(GETFILE_Dummy + 14)
#define GETFILE_FilterFunc	(GETFILE_Dummy + 15)
#define GETFILE_RejectIcons	(GETFILE_Dummy + 16)
#define GETFILE_RejectPattern	(GETFILE_Dummy + 17)
#define GETFILE_AcceptPattern	(GETFILE_Dummy + 18)
#define GETFILE_FilterDrawers	(GETFILE_Dummy + 19)
#define GETFILE_Filelist	(GETFILE_Dummy + 20)	/* (get) struct List *: a multi-select's files */
#define GETFILE_LBNodeStructs	(GETFILE_Dummy + 21)	/* BOOL: that list as listbrowser nodes */
#define GETFILE_ReadOnly	(GETFILE_Dummy + 22)
#define GETFILE_FullFileExpand	(GETFILE_Dummy + 9)

/* Methods */
#define GFILE_REQUEST	0x620001	/* open the requester */
#define GFILE_FREELIST	0x620002	/* free a GETFILE_Filelist */

struct gfRequest
{
	ULONG		MethodID;	/* GFILE_REQUEST */
	struct Window	*gfr_Window;	/* the window it opens over */
};

/* GFILE_REQUEST's message */
struct gfileRequest
{
    ULONG MethodID;
    struct Window *gfile_Window;
};

/* GFILE_FREELIST's message */
struct gfileFreelist
{
    ULONG MethodID;
    struct List *gfile_Filelist;
};

/* More names from the 3.2 interface */
#define GETFILE_AllowEmptyFileSelection	(GETFILE_Dummy + 24)
#define GETFILE_FilePartOnly	(GETFILE_Dummy + 23)
#define GETFILE_FilterHook	(GETFILE_Dummy + 25)
#define GETFILE_InitialShowVolumes	(GETFILE_Dummy + 26)

/* the requester through the gadget, and freeing its list of files */
#define gfRequestFile(obj, win)	DoMethod((obj), GFILE_REQUEST, (win))
#define gfRequestDir(obj, win)	DoMethod((obj), GFILE_REQUEST, (win))
#define gfFreeFilelist(obj, list)	DoMethod((obj), GFILE_FREELIST, (list))

#endif /* GADGETS_GETFILE_H */
