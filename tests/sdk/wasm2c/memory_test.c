/* Copyright (c) 2026 AmigaChrome Team. MIT licence. */
#include "wasm-rt.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static unsigned calls,fail_reserve,fail_all,fail_initial;
static size_t exact_size;
void *ow_test_realloc(void *p,size_t n){calls++;if(fail_all||(fail_reserve&&n!=exact_size))return NULL;return realloc(p,n);}
void *ow_test_calloc(size_t n,size_t size){if(fail_initial)return NULL;return calloc(n,size);}
void ow_test_abort(void){exit(75);}
#define CHECK(x) do{if(!(x)){fprintf(stderr,"memory FAIL line %d: %s\n",__LINE__,#x);exit(1);}}while(0)
int main(int argc,char**argv){wasm_rt_memory_t m;unsigned before;uint8_t *old;(void)argv;
 if(argc>1){fail_initial=1;wasm_rt_allocate_memory(&m,1,8,0,65536);return 1;}
 wasm_rt_allocate_memory(&m,1,8,0,65536);CHECK(m.size==65536&&m.allocation_capacity==65536);
 memset(m.data,0x19,65536);before=calls;CHECK(wasm_rt_grow_memory(&m,0)==1&&calls==before);
 CHECK(wasm_rt_grow_memory(&m,1)==1&&m.pages==2);CHECK(m.data[0]==0x19&&m.data[65535]==0x19&&m.data[65536]==0);
 CHECK(wasm_rt_grow_memory(&m,1)==2&&m.pages==3);CHECK(m.allocation_capacity==4*65536&&m.size==3*65536&&m.data_end==m.data+m.size);
 memset(m.data+m.size,0xcf,65536);old=m.data;before=calls;
 CHECK(wasm_rt_grow_memory(&m,1)==3&&m.data==old&&calls==before);CHECK(m.data[3*65536]==0&&m.data[4*65536-1]==0);
 fail_all=1;CHECK(wasm_rt_grow_memory(&m,1)==UINT64_MAX&&m.pages==4&&m.size==4*65536&&m.data==old&&m.allocation_capacity==4*65536);CHECK(m.data[0]==0x19);fail_all=0;
 before=calls;CHECK(wasm_rt_grow_memory(&m,5)==UINT64_MAX&&calls==before&&m.pages==4);
 wasm_rt_free_memory(&m);CHECK(!m.data&&!m.data_end&&!m.allocation_capacity&&!m.size);
 wasm_rt_allocate_memory(&m,1,8,0,65536);fail_reserve=1;exact_size=3*65536;
 CHECK(wasm_rt_grow_memory(&m,2)==1&&m.size==exact_size&&m.allocation_capacity==exact_size);fail_reserve=0;wasm_rt_free_memory(&m);
 wasm_rt_allocate_memory(&m,0,8,0,65536);CHECK(wasm_rt_grow_memory(&m,0)==0);CHECK(wasm_rt_grow_memory(&m,1)==0&&m.size==65536);wasm_rt_free_memory(&m);
 puts("wasm2c capacity: PASS (logical bounds, zeroing, no-op growth, preservation, failures, fallback, teardown)");return 0;}
