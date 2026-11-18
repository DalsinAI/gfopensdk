/* proto/muimaster.h: muimaster.library's calls (GFOpenMUI), through
 * MUIMasterBase; libmuimaster.a opens it for a program that has none.
 * MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef PROTO_MUIMASTER_H
#define PROTO_MUIMASTER_H
#include <exec/types.h>
#include <exec/libraries.h>
#include <libraries/mui.h>
extern struct Library *MUIMasterBase;
#include <clib/muimaster_protos.h>
#include <inline/muimaster.h>
#endif
