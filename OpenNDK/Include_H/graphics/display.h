#ifndef GRAPHICS_DISPLAY_H
#define GRAPHICS_DISPLAY_H
/*
 * OpenNDK: old bit masks for the display control registers.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

/* BPLCON0 */
#define MODE_640	0x8000
#define PLNCNTMSK	0x7	/* plane count, 0 to 6 */
#define PLNCNTSHFT	12
#define PF2PRI		0x40	/* in BPLCON2 */
#define COLORON		0x0200	/* composite colour */
#define DBLPF		0x400
#define HOLDNMODIFY	0x800
#define INTERLACE	4

/* BPLCON1 */
#define PFA_FINE_SCROLL		0xF
#define PFB_FINE_SCROLL_SHIFT	4
#define PF_FINE_SCROLL_MASK	0xF

/* DIWSTRT and DIWSTOP */
#define DIW_HORIZ_POS		0x7F
#define DIW_VRTCL_POS		0x1FF
#define DIW_VRTCL_POS_SHIFT	7

/* DDFSTRT and DDFSTOP */
#define DFTCH_MASK	0xFF

/* VPOSR long-frame bit */
#define VPOSRLOF	0x8000

#endif /* GRAPHICS_DISPLAY_H */
