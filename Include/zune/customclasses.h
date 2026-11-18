/* <zune/customclasses.h>: a custom class in one statement, as Zune programs
 * write it. ZUNE_CUSTOMCLASS_n(name, base, supername, supermcc, then n pairs
 * of method and message type) gives:
 *  - struct MUI_CustomClass *name_CLASS, made before main and freed after it;
 *  - a dispatcher that hands each method to name__METHOD(Class *, Object *, type),
 *    defined before the statement, and every other one to the superclass;
 *  - instance data the size of struct name_DATA.
 * Our own header, written from the macro's documented use. Generated for
 * 1 to 15 methods. MIT, Copyright (c) 2026 AmiCradle Team. */
#ifndef ZUNE_CUSTOMCLASSES_H
#define ZUNE_CUSTOMCLASSES_H

#include <libraries/mui.h>
#ifndef GFOPENMUI_HOST
#include <proto/muimaster.h>
#include <clib/alib_protos.h>
#include <aros/symbolsets.h>
#endif

/* the class's making and freeing: before main and after it (ADD2INIT), or by
 * hand on the host, where there are no program sets */
#ifdef GFOPENMUI_HOST
#define ZUNE_CC_SETS_(name)
#else
#define ZUNE_CC_SETS_(name) ADD2INIT(name##_Initialize, 100); ADD2EXIT(name##_Deinitialize, 100);
#endif

#define ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    struct MUI_CustomClass *name##_CLASS; \
    BOOPSI_DISPATCHER_PROTO(IPTR, name##_Dispatcher, cl, obj, msg);

#define ZUNE_CC_TAIL_(name, base, supername, supermcc) \
    default: return DoSuperMethodA(cl, obj, msg); \
    } \
    } \
    BOOPSI_DISPATCHER_END \
    int name##_Initialize(void) \
    { \
        name##_CLASS = MUI_CreateCustomClass((struct Library *)(base), (supername), (supermcc), \
                                             (LONG)sizeof(struct name##_DATA), __extension__ (APTR)name##_Dispatcher); \
        return name##_CLASS != NULL; \
    } \
    void name##_Deinitialize(void) \
    { \
        if (name##_CLASS) MUI_DeleteCustomClass(name##_CLASS); \
        name##_CLASS = NULL; \
    } \
    ZUNE_CC_SETS_(name)

#define ZUNE_CUSTOMCLASS_1(name, base, supername, supermcc, m1, t1) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_2(name, base, supername, supermcc, m1, t1, m2, t2) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_3(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_4(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_5(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_6(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5, m6, t6) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); case m6: return (IPTR)name##__##m6(cl, obj, (t6)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_7(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5, m6, t6, m7, t7) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); case m6: return (IPTR)name##__##m6(cl, obj, (t6)msg); case m7: return (IPTR)name##__##m7(cl, obj, (t7)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_8(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5, m6, t6, m7, t7, m8, t8) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); case m6: return (IPTR)name##__##m6(cl, obj, (t6)msg); case m7: return (IPTR)name##__##m7(cl, obj, (t7)msg); case m8: return (IPTR)name##__##m8(cl, obj, (t8)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_9(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5, m6, t6, m7, t7, m8, t8, m9, t9) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); case m6: return (IPTR)name##__##m6(cl, obj, (t6)msg); case m7: return (IPTR)name##__##m7(cl, obj, (t7)msg); case m8: return (IPTR)name##__##m8(cl, obj, (t8)msg); case m9: return (IPTR)name##__##m9(cl, obj, (t9)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_10(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5, m6, t6, m7, t7, m8, t8, m9, t9, m10, t10) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); case m6: return (IPTR)name##__##m6(cl, obj, (t6)msg); case m7: return (IPTR)name##__##m7(cl, obj, (t7)msg); case m8: return (IPTR)name##__##m8(cl, obj, (t8)msg); case m9: return (IPTR)name##__##m9(cl, obj, (t9)msg); case m10: return (IPTR)name##__##m10(cl, obj, (t10)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_11(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5, m6, t6, m7, t7, m8, t8, m9, t9, m10, t10, m11, t11) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); case m6: return (IPTR)name##__##m6(cl, obj, (t6)msg); case m7: return (IPTR)name##__##m7(cl, obj, (t7)msg); case m8: return (IPTR)name##__##m8(cl, obj, (t8)msg); case m9: return (IPTR)name##__##m9(cl, obj, (t9)msg); case m10: return (IPTR)name##__##m10(cl, obj, (t10)msg); case m11: return (IPTR)name##__##m11(cl, obj, (t11)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_12(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5, m6, t6, m7, t7, m8, t8, m9, t9, m10, t10, m11, t11, m12, t12) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); case m6: return (IPTR)name##__##m6(cl, obj, (t6)msg); case m7: return (IPTR)name##__##m7(cl, obj, (t7)msg); case m8: return (IPTR)name##__##m8(cl, obj, (t8)msg); case m9: return (IPTR)name##__##m9(cl, obj, (t9)msg); case m10: return (IPTR)name##__##m10(cl, obj, (t10)msg); case m11: return (IPTR)name##__##m11(cl, obj, (t11)msg); case m12: return (IPTR)name##__##m12(cl, obj, (t12)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_13(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5, m6, t6, m7, t7, m8, t8, m9, t9, m10, t10, m11, t11, m12, t12, m13, t13) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); case m6: return (IPTR)name##__##m6(cl, obj, (t6)msg); case m7: return (IPTR)name##__##m7(cl, obj, (t7)msg); case m8: return (IPTR)name##__##m8(cl, obj, (t8)msg); case m9: return (IPTR)name##__##m9(cl, obj, (t9)msg); case m10: return (IPTR)name##__##m10(cl, obj, (t10)msg); case m11: return (IPTR)name##__##m11(cl, obj, (t11)msg); case m12: return (IPTR)name##__##m12(cl, obj, (t12)msg); case m13: return (IPTR)name##__##m13(cl, obj, (t13)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_14(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5, m6, t6, m7, t7, m8, t8, m9, t9, m10, t10, m11, t11, m12, t12, m13, t13, m14, t14) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); case m6: return (IPTR)name##__##m6(cl, obj, (t6)msg); case m7: return (IPTR)name##__##m7(cl, obj, (t7)msg); case m8: return (IPTR)name##__##m8(cl, obj, (t8)msg); case m9: return (IPTR)name##__##m9(cl, obj, (t9)msg); case m10: return (IPTR)name##__##m10(cl, obj, (t10)msg); case m11: return (IPTR)name##__##m11(cl, obj, (t11)msg); case m12: return (IPTR)name##__##m12(cl, obj, (t12)msg); case m13: return (IPTR)name##__##m13(cl, obj, (t13)msg); case m14: return (IPTR)name##__##m14(cl, obj, (t14)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#define ZUNE_CUSTOMCLASS_15(name, base, supername, supermcc, m1, t1, m2, t2, m3, t3, m4, t4, m5, t5, m6, t6, m7, t7, m8, t8, m9, t9, m10, t10, m11, t11, m12, t12, m13, t13, m14, t14, m15, t15) \
    ZUNE_CC_HEAD_(name, base, supername, supermcc) \
    BOOPSI_DISPATCHER(IPTR, name##_Dispatcher, cl, obj, msg) \
    { \
    switch (msg->MethodID) { \
    case m1: return (IPTR)name##__##m1(cl, obj, (t1)msg); case m2: return (IPTR)name##__##m2(cl, obj, (t2)msg); case m3: return (IPTR)name##__##m3(cl, obj, (t3)msg); case m4: return (IPTR)name##__##m4(cl, obj, (t4)msg); case m5: return (IPTR)name##__##m5(cl, obj, (t5)msg); case m6: return (IPTR)name##__##m6(cl, obj, (t6)msg); case m7: return (IPTR)name##__##m7(cl, obj, (t7)msg); case m8: return (IPTR)name##__##m8(cl, obj, (t8)msg); case m9: return (IPTR)name##__##m9(cl, obj, (t9)msg); case m10: return (IPTR)name##__##m10(cl, obj, (t10)msg); case m11: return (IPTR)name##__##m11(cl, obj, (t11)msg); case m12: return (IPTR)name##__##m12(cl, obj, (t12)msg); case m13: return (IPTR)name##__##m13(cl, obj, (t13)msg); case m14: return (IPTR)name##__##m14(cl, obj, (t14)msg); case m15: return (IPTR)name##__##m15(cl, obj, (t15)msg); \
    ZUNE_CC_TAIL_(name, base, supername, supermcc)

#endif
