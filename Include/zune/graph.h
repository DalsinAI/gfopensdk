/* Graph.mcc: values read from sources (a hook each) every period, drawn
 * as lines over time against a grid. Published names and numbers (AROS's
 * Graph.mcc), our own text. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_GRAPH_H
#define ZUNE_GRAPH_H

#ifndef LIBRARIES_MUI_H
#include <libraries/mui.h>
#endif
#ifndef MUIB_RSVD
#define MUIB_RSVD (MUIB_MUI | 0x10400000UL)
#endif
#ifndef MUIB_AROS
#define MUIB_AROS (MUIB_RSVD | 0x00070000UL)
#endif

#ifndef STACKED
#define STACKED
#endif

#define MUIC_Graph "Graph.mcc"
#define MUIB_Graph (MUIB_AROS | 0x00000000UL)

#define MUIA_Graph_InfoText       (MUIB_Graph | 0x00000001UL)   /* ISG CONST_STRPTR */
#define MUIA_Graph_EntryCount     (MUIB_Graph | 0x00000002UL)   /* ..G IPTR: samples kept */
#define MUIA_Graph_Aggregate      (MUIB_Graph | 0x00000003UL)   /* ISG BOOL: sources stacked */
#define MUIA_Graph_PeriodCeiling  (MUIB_Graph | 0x00000010UL)   /* ISG IPTR, ms shown */
#define MUIA_Graph_PeriodStep     (MUIB_Graph | 0x00000011UL)   /* ISG IPTR, ms between upright lines */
#define MUIA_Graph_PeriodInterval (MUIB_Graph | 0x00000012UL)   /* ISG IPTR, ms between samples */
#define MUIA_Graph_ValueCeiling   (MUIB_Graph | 0x00000020UL)   /* ISG IPTR: the top */
#define MUIA_Graph_ValueStep      (MUIB_Graph | 0x00000021UL)   /* ISG IPTR, between level lines */
#define MUIA_Graph_ManualRefresh  (MUIB_Graph | 0x000000FEUL)   /* ISG BOOL: no timer, MUIM_Graph_Timer by hand */
#define MUIA_Graph_PeriodicTick   (MUIB_Graph | 0x000000FFUL)   /* ..G BOOL: set on each sample (notify) */

#define MUIM_Graph_GetSourceHandle (MUIB_Graph | 0x00000001UL)
#define MUIM_Graph_SetSourceAttrib (MUIB_Graph | 0x00000002UL)
#define MUIM_Graph_Reset           (MUIB_Graph | 0x0000000FUL)
#define MUIM_Graph_Timer           (MUIB_Graph | 0x000000FFUL)

struct MUIP_Graph_GetSourceHandle { STACKED IPTR MethodID; STACKED IPTR SourceNo; };
struct MUIP_Graph_SetSourceAttrib { STACKED IPTR MethodID; STACKED APTR SourceHandle; STACKED IPTR Attrib; STACKED IPTR AttribVal; };

/* a source's attributes. ReadHook is called with the sample's IPTR as its
 * object and the source's number as its message, and stores the value */
#define MUIV_Graph_Source_ReadHook   0x00000001UL   /* struct Hook * */
#define MUIV_Graph_Source_PenSrc     0x00000002UL   /* ULONG[3]: 32-bit red, green, blue of the line */
#define MUIV_Graph_Source_Pen        0x00000003UL   /* LONG: the line's pen */
#define MUIV_Graph_Source_FillPenSrc 0x00000004UL   /* ULONG[3]: of the area under it */
#define MUIV_Graph_Source_FillPen    0x00000005UL   /* LONG: the area's pen */

#define GraphObject MUIOBJMACRO_START(MUIC_Graph)

#endif
