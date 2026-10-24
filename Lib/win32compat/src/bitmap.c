/* Copyright (c) 2026 AmigaChrome Team. MIT licence. */
#include <win32compat/bitmap.h>
#include <limits.h>
#include <string.h>

static uint64_t pitch(const OW32_Bitmap *b)
{ return b->stride < 0 ? (uint64_t)(-(int64_t)b->stride) : (uint64_t)b->stride; }
OW32_Status OW32_BitmapValidate(const OW32_Bitmap *b)
{
    uint64_t row_bytes, span;
    if (!b || !b->storage || !b->bytes || !b->width || !b->height) return OW32_INVALID;
    if (b->format != OW32_INDEX8 && b->format != OW32_BGRX32) return OW32_UNSUPPORTED;
    if (b->bytes > UINTPTR_MAX - (uintptr_t)b->storage) return OW32_RANGE;
    row_bytes = (uint64_t)b->width * (unsigned)b->format;
    if (b->row0 > b->bytes || row_bytes > b->bytes - b->row0) return OW32_RANGE;
    if (b->height > 1 && pitch(b) < row_bytes) return OW32_RANGE;
    span = (uint64_t)(b->height - 1) * pitch(b);
    if (b->stride < 0) {
        if (span > b->row0) return OW32_RANGE;
    } else if (span > b->bytes - b->row0 - row_bytes) return OW32_RANGE;
    return OW32_OK;
}
OW32_Status OW32_BitmapInit(OW32_Bitmap *out, void *storage, size_t bytes,
    size_t row0, uint32_t width, uint32_t height, int32_t stride, OW32_Format format)
{
    OW32_Bitmap b;
    OW32_Status result;
    if (!out) return OW32_INVALID;
    b.storage = storage; b.bytes = bytes; b.row0 = row0; b.width = width;
    b.height = height; b.stride = stride; b.format = format;
    result = OW32_BitmapValidate(&b);
    if (result == OW32_OK) *out = b;
    return result;
}
static uint32_t le32(const unsigned char *p)
{ return (uint32_t)p[0] | (uint32_t)p[1]<<8 | (uint32_t)p[2]<<16 | (uint32_t)p[3]<<24; }
static unsigned le16(const unsigned char *p)
{ return (unsigned)p[0] | (unsigned)p[1]<<8; }
OW32_Status OW32_BitmapFromDIB(OW32_Bitmap *out, void *pixels, size_t bytes,
    const void *header, size_t header_bytes)
{
    const unsigned char *h = header;
    uint32_t w, raw_height, count;
    int64_t height;
    uint64_t stride, required;
    OW32_Format format;
    if (!out || !h || header_bytes < 40) return OW32_INVALID;
    if (le32(h) < 40 || le32(h) > header_bytes) return OW32_RANGE;
    w = le32(h+4); raw_height = le32(h+8);
    height = raw_height <= INT32_MAX ? (int64_t)raw_height : (int64_t)raw_height - INT64_C(4294967296);
    if (!w || w > INT32_MAX || !height || height == INT32_MIN || le16(h+12) != 1) return OW32_INVALID;
    if (le32(h+16) != 0) return OW32_UNSUPPORTED;
    if (le16(h+14) == 8) format = OW32_INDEX8;
    else if (le16(h+14) == 32) format = OW32_BGRX32;
    else return OW32_UNSUPPORTED;
    count = (uint32_t)(height < 0 ? -height : height);
    stride = (((uint64_t)w * (unsigned)format + 3) / 4) * 4;
    required = stride * count;
    if (stride > INT32_MAX || required > bytes) return OW32_RANGE;
    return OW32_BitmapInit(out, pixels, bytes, height > 0 ? (size_t)(stride*(count-1)) : 0,
        w, count, height > 0 ? -(int32_t)stride : (int32_t)stride, format);
}
static size_t row_offset(const OW32_Bitmap *b, uint32_t y)
{
    size_t delta = (size_t)((uint64_t)y * pitch(b));
    return b->stride < 0 ? b->row0 - delta : b->row0 + delta;
}
OW32_Status OW32_BitmapRowOffset(const OW32_Bitmap *b, uint32_t row, size_t *offset)
{
    OW32_Status r = OW32_BitmapValidate(b);
    if (r != OW32_OK) return r;
    if (!offset) return OW32_INVALID;
    if (row >= b->height) return OW32_RANGE;
    *offset = row_offset(b,row); return OW32_OK;
}
static int64_t max64(int64_t a,int64_t b) { return a>b?a:b; }
static int64_t min64(int64_t a,int64_t b) { return a<b?a:b; }
static OW32_Status clip(const OW32_Bitmap *d,int32_t dx,int32_t dy,const OW32_Bitmap *s,
    int32_t sx,int32_t sy,uint32_t w,uint32_t h,OW32_CopyArea *a)
{
    int64_t left=0,top=0,right=w,bottom=h;
    left=max64(left,-(int64_t)sx); left=max64(left,-(int64_t)dx);
    top=max64(top,-(int64_t)sy); top=max64(top,-(int64_t)dy);
    right=min64(right,(int64_t)s->width-sx); right=min64(right,(int64_t)d->width-dx);
    bottom=min64(bottom,(int64_t)s->height-sy); bottom=min64(bottom,(int64_t)d->height-dy);
    if (right<=left || bottom<=top) { memset(a,0,sizeof *a); return OW32_EMPTY; }
    a->sx=(uint32_t)((int64_t)sx+left); a->sy=(uint32_t)((int64_t)sy+top);
    a->dx=(uint32_t)((int64_t)dx+left); a->dy=(uint32_t)((int64_t)dy+top);
    a->width=(uint32_t)(right-left); a->height=(uint32_t)(bottom-top); return OW32_OK;
}
static int same_layout(const OW32_Bitmap *a,const OW32_Bitmap *b)
{
    return a->storage==b->storage && a->bytes==b->bytes && a->row0==b->row0 &&
        a->width==b->width && a->height==b->height && a->stride==b->stride && a->format==b->format;
}
OW32_Status OW32_BitmapCopy(OW32_Bitmap *dst,int32_t dx,int32_t dy,const OW32_Bitmap *src,
    int32_t sx,int32_t sy,uint32_t width,uint32_t height,OW32_CopyArea *copied)
{
    OW32_Status r; OW32_CopyArea a; uint32_t i; int self;
    uintptr_t dp,sp;
    if ((r=OW32_BitmapValidate(dst))!=OW32_OK || (r=OW32_BitmapValidate(src))!=OW32_OK) return r;
    if (dst->format!=src->format) return OW32_UNSUPPORTED;
    r=clip(dst,dx,dy,src,sx,sy,width,height,&a);
    if (r!=OW32_OK) { if(copied)*copied=a; return r; }
    dp=(uintptr_t)dst->storage; sp=(uintptr_t)src->storage; self=same_layout(dst,src);
    if (!self && dp<sp+src->bytes && sp<dp+dst->bytes) return OW32_ALIAS;
    for(i=0;i<a.height;i++) {
        uint32_t j=self && a.dy>a.sy ? a.height-1-i : i;
        size_t to=row_offset(dst,a.dy+j)+(size_t)a.dx*(unsigned)dst->format;
        size_t from=row_offset(src,a.sy+j)+(size_t)a.sx*(unsigned)src->format;
        memmove(dst->storage+to,src->storage+from,(size_t)a.width*(unsigned)dst->format);
    }
    if(copied)*copied=a;
    return OW32_OK;
}
OW32_Status OW32_BitmapFill(OW32_Bitmap *dst,int32_t x,int32_t y,
    uint32_t width,uint32_t height,uint32_t value)
{
    OW32_Status r=OW32_BitmapValidate(dst); OW32_CopyArea a; uint32_t i,j;
    if(r!=OW32_OK)return r;
    if(dst->format==OW32_INDEX8 && value>255)return OW32_RANGE;
    r=clip(dst,x,y,dst,x,y,width,height,&a); if(r!=OW32_OK)return r;
    for(i=0;i<a.height;i++) {
        unsigned char *p=dst->storage+row_offset(dst,a.dy+i)+(size_t)a.dx*(unsigned)dst->format;
        if(dst->format==OW32_INDEX8)memset(p,(int)value,a.width);
        else for(j=0;j<a.width;j++,p+=4) {p[0]=(unsigned char)value;p[1]=(unsigned char)(value>>8);p[2]=(unsigned char)(value>>16);p[3]=0;}
    }
    return OW32_OK;
}
