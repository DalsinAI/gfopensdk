/* Copyright (c) 2026 AmiCradle Team. The Open SDK, MIT licence (LICENSE).
 * SPDX-License-Identifier: MIT
 *
 * Inside the kit: the classic calls go through each interface's own base,
 * opened on first use, so the kit never makes a program open a library it
 * does not use. Include this before any proto/ header.
 */
#ifndef OS4C_INTERNAL_H
#define OS4C_INTERNAL_H

#include <os4compat/os4compat.h>

extern struct Interface os4c_dos_iface;
extern struct Interface os4c_utility_iface;
extern struct Interface os4c_graphics_iface;
extern struct Interface os4c_intuition_iface;

#define DOS_BASE_NAME       OS4C_BASE(os4c_dos_iface)
#define UTILITY_BASE_NAME   OS4C_BASE(os4c_utility_iface)
#define GRAPHICS_BASE_NAME  OS4C_BASE(os4c_graphics_iface)
#define INTUITION_BASE_NAME OS4C_BASE(os4c_intuition_iface)

/* Data.Flags */
#define OS4CF_WEOPENED 1   /* os4c_OpenBase opened it; closed at exit */

#endif
