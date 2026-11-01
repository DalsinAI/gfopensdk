#ifndef INTUITION_CGHOOKS_H
#define INTUITION_CGHOOKS_H
/*
 * OpenNDK: what a custom (BOOPSI) gadget is told about where it lives.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef INTUITION_INTUITION_H
#include <intuition/intuition.h>
#endif

/* Passed to a gadget's methods; read it, never write it */
struct GadgetInfo
{
    struct Screen *gi_Screen;
    struct Window *gi_Window;		/* NULL in a screen gadget */
    struct Requester *gi_Requester;	/* NULL unless in a requester */

    /* Use ObtainGIRPort() rather than these two */
    struct RastPort *gi_RastPort;
    struct Layer *gi_Layer;

    /* The box the gadget's relative position counts from */
    struct IBox gi_Domain;

    struct
    {
	UBYTE DetailPen;
	UBYTE BlockPen;
    } gi_Pens;

    struct DrawInfo *gi_DrInfo;

    ULONG gi_Reserved[6];
};

/* A proportional gadget's container and knob */
struct PGX
{
    struct IBox pgx_Container;
    struct IBox pgx_NewKnob;
};

/* An old-style custom gadget keeps its hook in MutualExclude */
#define CUSTOM_HOOK(gadget)	((struct Hook *)(gadget)->MutualExclude)

#endif /* INTUITION_CGHOOKS_H */
