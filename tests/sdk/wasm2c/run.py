#!/usr/bin/env python3
from pathlib import Path
import argparse,importlib.util,subprocess,tempfile,shutil,os,contextlib,json,hashlib
root=Path(__file__).resolve().parents[3]
p=argparse.ArgumentParser();p.add_argument('--wabt',type=Path,default=root/'tests/sdk/wasm2c/upstream-1.0.41');p.add_argument('--cc',default='cc');p.add_argument('--runner',default='');p.add_argument('--flags',default='');p.add_argument('--build',type=Path);p.add_argument('--compile-only',action='store_true');a=p.parse_args()
spec=importlib.util.spec_from_file_location('patch',root/'tools/patch_wasm2c_memory.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
import shlex
if (a.wabt/'SOURCE.json').exists():
 receipt=json.loads((a.wabt/'SOURCE.json').read_text())
 for name,sha in receipt['sha256'].items():assert hashlib.sha256((a.wabt/name).read_bytes()).hexdigest()==sha,name
if a.build:
 a.build.mkdir(parents=True,exist_ok=True)
 if any(a.build.iterdir()):p.error('build directory must be empty')
with (contextlib.nullcontext(str(a.build.resolve())) if a.build else tempfile.TemporaryDirectory()) as temp:
 d=Path(temp);shutil.copy2(a.wabt/'include/wasm-rt.h',d/'wasm-rt.h')
 for source in (a.wabt/'share/wabt/wasm2c').iterdir():
  if source.is_file() and source.suffix in ['.c','.h','.inc']:shutil.copy2(source,d/source.name)
 m.apply(d)
 try:m.apply(d);raise AssertionError('second application accepted')
 except ValueError:pass
 flags=['-std=c99','-O1','-DWABT_BIG_ENDIAN=0','-DWASM_RT_USE_MMAP=0','-DWASM_RT_MEMCHECK_BOUNDS_CHECK=1','-I'+str(d),*shlex.split(a.flags)]
 subprocess.run([a.cc,*flags,'-Drealloc=ow_test_realloc','-Dcalloc=ow_test_calloc','-Dabort=ow_test_abort','-c',str(d/'wasm-rt-mem-impl.c'),'-o',str(d/'runtime.o')],check=True)
 subprocess.run([a.cc,*flags,str(root/'tests/sdk/wasm2c/memory_test.c'),str(d/'runtime.o'),'-o',str(d/'test')],check=True)
 if a.compile_only:
  print('Compiled test:',d/'test');raise SystemExit(0)
 subprocess.run([*shlex.split(a.runner),str(d/'test')],check=True)
 r=subprocess.run([*shlex.split(a.runner),str(d/'test'),'--fail-init']);assert r.returncode==75,r.returncode
 print('Allocation failure rejected before returning an invalid instance')
