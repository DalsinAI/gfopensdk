/* Copyright (c) 2026 AmigaChrome Team. MIT licence. */
#include <win32compat/bitmap.h>
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHECK(x) do {if(!(x)){fprintf(stderr,"FAIL line %d: %s\n",__LINE__,#x);exit(1);}}while(0)
static void put32(unsigned char*p,uint32_t v){unsigned i;for(i=0;i<4;i++)p[i]=(unsigned char)(v>>(8*i));}
static void dib(unsigned char*h,uint32_t w,uint32_t height,unsigned bpp)
{memset(h,0,40);put32(h,40);put32(h+4,w);put32(h+8,height);h[12]=1;h[14]=(unsigned char)bpp;}
static size_t at(const OW32_Bitmap*b,uint32_t x,uint32_t y)
{/* Independent test layout: each case deliberately uses four padding bytes. */
 size_t row=b->stride<0?b->height-1-y:y;
 return 16+row*((size_t)b->width*(unsigned)b->format+4)+(size_t)x*(unsigned)b->format;
}
static uint32_t rng=0x25ac090;
static uint32_t random32(void){rng^=rng<<13;rng^=rng>>17;rng^=rng<<5;return rng;}
static void validation(void)
{
 unsigned char raw[160],hdr[41]; OW32_Bitmap b,old;size_t offset=77;
 memset(&b,0,sizeof b);CHECK(OW32_BitmapValidate(&b)==OW32_INVALID);
 CHECK(OW32_BitmapInit(&b,raw,sizeof raw,0,4,3,16,OW32_BGRX32)==OW32_OK);old=b;
 CHECK(OW32_BitmapInit(&b,raw,sizeof raw,0,4,3,15,OW32_BGRX32)==OW32_RANGE);CHECK(!memcmp(&b,&old,sizeof b));
 CHECK(OW32_BitmapInit(&b,raw,47,0,4,3,16,OW32_BGRX32)==OW32_RANGE);
 CHECK(OW32_BitmapInit(&b,raw,sizeof raw,0,4,3,-16,OW32_BGRX32)==OW32_RANGE);
 CHECK(OW32_BitmapInit(&b,raw,sizeof raw,32,4,3,-16,OW32_BGRX32)==OW32_OK);
 CHECK(OW32_BitmapRowOffset(&b,0,&offset)==OW32_OK&&offset==32);
 CHECK(OW32_BitmapRowOffset(&b,2,&offset)==OW32_OK&&offset==0);
 CHECK(OW32_BitmapRowOffset(&b,3,&offset)==OW32_RANGE&&offset==0);
 CHECK(OW32_BitmapInit(&b,raw,sizeof raw,0,UINT32_MAX,UINT32_MAX,INT32_MIN,OW32_BGRX32)==OW32_RANGE);
 CHECK(OW32_BitmapInit(&b,raw,sizeof raw,SIZE_MAX,4,3,16,OW32_BGRX32)==OW32_RANGE);
 CHECK(OW32_BitmapInit(&b,raw,sizeof raw,0,1,1,0,(OW32_Format)3)==OW32_UNSUPPORTED);
 dib(hdr+1,4,3,32);CHECK(OW32_BitmapFromDIB(&b,raw,48,hdr+1,40)==OW32_OK&&b.row0==32&&b.stride==-16);
 dib(hdr+1,4,0xfffffffdU,32);CHECK(OW32_BitmapFromDIB(&b,raw,48,hdr+1,40)==OW32_OK&&b.row0==0&&b.stride==16);
 CHECK(OW32_BitmapFromDIB(&b,raw,47,hdr+1,40)==OW32_RANGE);
 CHECK(OW32_BitmapFromDIB(&b,raw,48,hdr+1,39)==OW32_INVALID);
 dib(hdr,4,0x80000000U,32);CHECK(OW32_BitmapFromDIB(&b,raw,sizeof raw,hdr,40)==OW32_INVALID);
 dib(hdr,0xffffffffU,3,32);CHECK(OW32_BitmapFromDIB(&b,raw,sizeof raw,hdr,40)==OW32_INVALID);
 dib(hdr,4,3,24);CHECK(OW32_BitmapFromDIB(&b,raw,sizeof raw,hdr,40)==OW32_UNSUPPORTED);
 dib(hdr,4,3,32);put32(hdr+16,1);CHECK(OW32_BitmapFromDIB(&b,raw,sizeof raw,hdr,40)==OW32_UNSUPPORTED);
 dib(hdr,4,3,32);put32(hdr,124);CHECK(OW32_BitmapFromDIB(&b,raw,sizeof raw,hdr,40)==OW32_RANGE);
}
static void scroll_surface(void)
{
 /* 2048x1024 backing store with a 640x480 visible destination. Viewport
  * dimensions must never replace backing-store width, height or pitch. */
 const size_t sn=2048UL*1024*4,dn=640UL*480*4;
 unsigned char *s=malloc(sn+32),*d=malloc(dn+32),hdr[40];OW32_Bitmap src,dst;OW32_CopyArea area;size_t i;
 CHECK(s&&d);memset(s,0xa7,sn+32);memset(d,0x5a,dn+32);
 dib(hdr,2048,1024,32);CHECK(OW32_BitmapFromDIB(&src,s+16,sn,hdr,40)==OW32_OK);
 CHECK(src.width==2048&&src.height==1024&&src.stride==-8192);
 CHECK(OW32_BitmapInit(&dst,d+16,dn,0,640,480,2560,OW32_BGRX32)==OW32_OK);
 CHECK(OW32_BitmapFill(&src,1300,300,640,480,0x00cfcfcf)==OW32_OK);
 CHECK(OW32_BitmapCopy(&dst,0,0,&src,1300,300,640,480,&area)==OW32_OK&&area.width==640&&area.height==480);
 for(i=0;i<dn;i++)CHECK(d[16+i]==(i%4==3?0:0xcf));
 for(i=0;i<16;i++){CHECK(s[i]==0xa7&&s[sn+16+i]==0xa7);CHECK(d[i]==0x5a&&d[dn+16+i]==0x5a);}
 /* Keep the allocation fixed and lie about its dimensions: reject it. */
 src.height=2048;memset(d+16,0x5a,dn);CHECK(OW32_BitmapCopy(&dst,0,0,&src,0,0,640,480,NULL)==OW32_RANGE);
 for(i=0;i<dn+32;i++)CHECK(d[i]==0x5a);
 dib(hdr,0x00080000U,1024,32);CHECK(OW32_BitmapFromDIB(&src,s+16,sn,hdr,40)==OW32_RANGE);
 free(s);free(d);
}
static void random_copy(void)
{
 unsigned char a[1024],b[1024],expected[1024],snapshot[1024];unsigned test;
 for(test=0;test<2000;test++) {
  OW32_Bitmap src,dst;OW32_CopyArea area;OW32_Status result;
  unsigned fmt=(test&1)?4:1,w=7,h=6,pitch=w*fmt+4,i,x,y,k;int self=(test%3)==0;
  int32_t sx=(int32_t)(random32()%25)-12,sy=(int32_t)(random32()%21)-10;
  int32_t dx=(int32_t)(random32()%25)-12,dy=(int32_t)(random32()%21)-10;
  uint32_t rw=random32()%20,rh=random32()%18;int any=0;
  for(i=0;i<sizeof a;i++){a[i]=(unsigned char)random32();b[i]=(unsigned char)random32();}
  CHECK(OW32_BitmapInit(&src,a,sizeof a,16+((test&2)?(h-1)*pitch:0),w,h,(test&2)?-(int32_t)pitch:(int32_t)pitch,(OW32_Format)fmt)==OW32_OK);
  if(self)dst=src;
  else CHECK(OW32_BitmapInit(&dst,b,sizeof b,16+((test&4)?(h-1)*pitch:0),w,h,(test&4)?-(int32_t)pitch:(int32_t)pitch,(OW32_Format)fmt)==OW32_OK);
  memcpy(expected,dst.storage,sizeof expected);memcpy(snapshot,src.storage,sizeof snapshot);
  for(y=0;y<h;y++)for(x=0;x<w;x++) {
   int64_t rx=(int64_t)x-dx,ry=(int64_t)y-dy,xx=(int64_t)sx+rx,yy=(int64_t)sy+ry;
   if(rx<0||ry<0||rx>=rw||ry>=rh||xx<0||yy<0||xx>=w||yy>=h)continue;
   any=1;for(k=0;k<fmt;k++)expected[at(&dst,x,y)+k]=snapshot[at(&src,(uint32_t)xx,(uint32_t)yy)+k];
  }
  result=OW32_BitmapCopy(&dst,dx,dy,&src,sx,sy,rw,rh,&area);
  CHECK(result==(any?OW32_OK:OW32_EMPTY));CHECK(!memcmp(expected,dst.storage,sizeof expected));
 }
}
static void index_padding(void)
{
 unsigned char bytes[24],h[40];OW32_Bitmap b;unsigned i;memset(bytes,0x77,sizeof bytes);
 dib(h,3,2,8);CHECK(OW32_BitmapFromDIB(&b,bytes+4,8,h,40)==OW32_OK&&b.stride==-4);
 CHECK(OW32_BitmapFill(&b,0,0,3,2,0x19)==OW32_OK);
 for(i=0;i<sizeof bytes;i++)CHECK(bytes[i]==((i>=4&&i<12&&(i-4)%4<3)?0x19:0x77));
}
static void edge_cases(void)
{
 unsigned char data[256],before[256];OW32_Bitmap a,b;size_t i;
 memset(data,0x71,sizeof data);memcpy(before,data,sizeof data);
 CHECK(OW32_BitmapInit(&a,data,sizeof data,0,8,8,32,OW32_BGRX32)==OW32_OK);
 CHECK(OW32_BitmapCopy(&a,INT32_MIN,INT32_MIN,&a,INT32_MAX,INT32_MAX,UINT32_MAX,UINT32_MAX,NULL)==OW32_EMPTY);
 CHECK(!memcmp(before,data,sizeof data));
 CHECK(OW32_BitmapFill(&a,INT32_MAX,0,UINT32_MAX,1,0)==OW32_EMPTY);
 CHECK(OW32_BitmapInit(&b,data+4,sizeof data-4,0,7,7,32,OW32_BGRX32)==OW32_OK);
 CHECK(OW32_BitmapCopy(&b,0,0,&a,0,0,2,2,NULL)==OW32_ALIAS);CHECK(!memcmp(before,data,sizeof data));
 CHECK(OW32_BitmapInit(&b,data,sizeof data,0,8,8,8,OW32_INDEX8)==OW32_OK);
 CHECK(OW32_BitmapFill(&b,0,0,8,8,256)==OW32_RANGE);CHECK(!memcmp(before,data,sizeof data));
 CHECK(OW32_BitmapCopy(&a,0,0,&b,0,0,1,1,NULL)==OW32_UNSUPPORTED);
 CHECK(OW32_BitmapFill(&a,-1,-1,3,3,0x00112233)==OW32_OK);
 for(i=0;i<sizeof data;i++){unsigned row=(unsigned)i/32,col=(unsigned)i%32;
  unsigned char v=before[i];if(row<2&&col<8){unsigned k=col%4;v=k==0?0x33:k==1?0x22:k==2?0x11:0;}CHECK(data[i]==v);}
}
int main(void)
{validation();scroll_surface();random_copy();index_padding();edge_cases();puts("win32compat bitmap: PASS (DIB endian/stride, oversized surface, 2000 reference copies, guards and invalid metadata)");return 0;}
