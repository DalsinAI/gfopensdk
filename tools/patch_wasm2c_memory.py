#!/usr/bin/env python3
"""Apply the pinned WABT 1.0.41 non-mmap allocation-capacity patch."""
from pathlib import Path
import argparse
import hashlib
import json

PINS = {'wasm-rt.h':'0757a097bf55ccc904f34249bbc63f18c9f6415f78bc39b87208f776d63d3a61',
        'wasm-rt-mem-impl-helper.inc':'1d0f57627e92fe581ef1dd5da37fd38122b39580065ab9d661874e2c9d431d41'}
def digest(b): return hashlib.sha256(b).hexdigest()
def replace(s, old, new, count=1):
    if s.count(old)!=count: raise ValueError('Unexpected pinned WABT template: '+old[:80])
    return s.replace(old,new)
def apply(root):
    original={name:(root/name).read_bytes() for name in PINS}
    for name,sha in PINS.items():
        if digest(original[name])!=sha: raise ValueError('Unexpected upstream source: '+name+'; apply before other compatibility patches')
    h=original['wasm-rt.h'].decode()
    h=replace(h,'  bool is64;','  bool is64;\n  /** Open SDK: physical non-mmap allocation; size remains the logical bound. */\n  uint64_t allocation_capacity;',2)
    s=original['wasm-rt-mem-impl-helper.inc'].decode()
    guard='''/* Open SDK profile: forward-addressed wasm32, ordinary 64 KiB pages.
 * Retain upstream notices. All generated/host objects must be rebuilt because
 * the memory structure gains allocation_capacity. Shared memories unsupported. */
#if WASM_RT_USE_MMAP || WABT_BIG_ENDIAN
#error "Open SDK capacity profile requires non-mmap forward memory"
#endif
'''
    s=replace(s,'  uint64_t byte_length = initial_pages * page_size;',guard+'''#ifdef WASM_RT_MEM_OPS_SHARED
  abort(); /* Moving shared memory is not a supported profile. */
#endif
  if (is64 || page_size != WASM_DEFAULT_PAGE_SIZE || max_pages > 65536 ||
      initial_pages > max_pages || initial_pages > SIZE_MAX / page_size) abort();
  uint64_t byte_length = initial_pages * page_size;''')
    s=replace(s,'  memory->data = (MEMORY_CELL_TYPE)calloc(byte_length, 1);\n  memory->data_end = memory->data + byte_length;', '''  memory->data = (MEMORY_CELL_TYPE)calloc((size_t)byte_length, 1);
  if (byte_length && !memory->data) abort();
  memory->allocation_capacity = byte_length;
  memory->data_end = memory->data ? memory->data + byte_length : memory->data;''')
    old='''  uint8_t* new_data = realloc((void*)memory->data, new_size);
  if (new_data == NULL) {
    return -1;
  }'''
    new='''  if (new_size > SIZE_MAX) return -1;
  uint64_t capacity = memory->allocation_capacity;
  uint8_t* new_data = (uint8_t*)memory->data;
  if (new_size > capacity) {
    uint64_t limit = memory->max_pages * memory->page_size;
    if (limit > SIZE_MAX) limit = SIZE_MAX;
    if (!capacity) capacity = memory->page_size;
    while (capacity < new_size) {
      capacity = capacity > limit / 2 ? limit : capacity * 2;
    }
    new_data = realloc((void*)memory->data, (size_t)capacity);
    /* Spare capacity is optional: preserve exact-growth availability. */
    if (!new_data && capacity != new_size) {
      capacity = new_size;
      new_data = realloc((void*)memory->data, (size_t)capacity);
    }
    if (!new_data) return -1;
  }'''
    s=replace(s,old,new)
    s=replace(s,'  memory->data = (MEMORY_CELL_TYPE)new_data;\n  memory->data_end = memory->data + new_size;', '''  memory->data = (MEMORY_CELL_TYPE)new_data;
  memory->allocation_capacity = capacity;
  memory->data_end = memory->data + new_size;''')
    s=replace(s,'  uint64_t old_pages = memory->pages;','  uint64_t old_pages = memory->pages;\n  if (!delta) return old_pages;')
    s=replace(s,'  free((void*)memory->data);','''  free((void*)memory->data);
  memory->data = NULL;
  memory->data_end = NULL;
  memory->allocation_capacity = 0;
  memory->pages = memory->size = 0;''')
    outputs={'wasm-rt.h':h.encode(),'wasm-rt-mem-impl-helper.inc':s.encode()}
    for name,data in outputs.items():(root/name).write_bytes(data)
    receipt={'upstream':'WebAssembly/wabt','version':'1.0.41','profile':'non-mmap forward wasm32, 64KiB pages, no shared memory','patch':'Open SDK allocation-capacity v1','input_sha256':PINS,'output_sha256':{n:digest(b) for n,b in outputs.items()}}
    (root/'openamiga-memory-receipt.json').write_text(json.dumps(receipt,indent=2)+'\n')
    return receipt

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--runtime',type=Path,required=True);a=p.parse_args()
    try:apply(a.runtime.resolve())
    except (OSError,ValueError) as e:p.error(str(e))
    print('Applied pinned WABT 1.0.41 allocation-capacity profile')
if __name__=='__main__':main()
