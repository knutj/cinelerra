#!/bin/python

base = {
  "rgb8": {
    "i8": {
      "r": " uint32_t in = *inp, r = ((in>>6)&3)*0x55u, g = ((in>>3)&7)*0x24u, b = (in&7)*0x24u;",
      "w": " uint32_t ot = (r&0xc0u) | ((g>>2)&0x38u) | ((b>>5)&0x07u);\n" +
           " *out++ = ot;",
    },
    "i16": {
      "r": " uint32_t in = *inp, r = ((in>>6)&3)*0x5555u, g = ((in>>3)&7)*0x2492u, b = (in&7)*0x2492u;",
      "w": " uint32_t ot = ((r>>8)&0xc0u) | ((g>>10) & 0x38u) >> 2) | ((b>>13)&0x07u);\n" +
           " *out++ = ot;",
    },
    "fp": {
      "r": " int in = *inp; float r = (in>>6)/3.f, g = ((in>>3)&0x07u)/7.f, b = (in&0x07u)/7.f;",
      "w": " int vr = 3*r+.5f, vg = 7*g+.5f, vb = 7*b+.5f;\n" +
           " *out++ = ((vr<<6)&0xc0u) | ((vg<<3)&0x38u) | (vb&0x7u);",
    },
  },
  "rgb565": {
    "i8": {
      "r": " uint16_t in = *(uint16_t*)inp;\n" +
           " uint32_t r = (in>>8)&0xf8u, g = (in>>3)&0xfcu, b = (in&0x1fu)<<3;",
      "w": " uint16_t ot = ((r<<8) & 0xf800u) | ((g<<3) & 0x07e0u) | ((b>>3) & 0x001fu);\n" +
           " *(uint16_t*)out = ot; out += sizeof(uint16_t);",
    },
    "i16": {
      "r": " uint16_t in = *(uint16_t*)inp;\n" +
           " uint32_t r = in&0xf800u, g = (in<<5)&0xfc00u, b = (in<<11)&0xf800u;",
      "w": " uint32_t ot = (r&0xf800u) | ((g>>5) & 0x07e0u) | ((b>>11) & 0x001fu);\n" +
           " *(uint16_t*)out = ot; out += sizeof(uint16_t);",
    },
    "fp": {
      "r": " uint16_t in = *(uint16_t*)inp;\n" +
           " float r = (in>>11)/31.f, g = ((in>>5)&0x3fu)/63.f, b = (in&0x1fu)/31.f;",
      "w": " uint32_t vr = 31*r+.5f, vg = 63*g+.5f, vb = 31*b+.5f;\n" +
           " out++ = ((vr<<11)&0xf800u) | ((vg<<6)&0x07e0u) | (vb&0x001fu);",
    },
  },
  "rgb888": {
    "i8": {
      "r": " uint32_t r = *inp++, g = *inp++, b = *inp++;",
      "w": " *out++ = r; *out++ = g; *out++ = b;",
    },
    "i16": {
      "r": " uint32_t r = *inp++*0x101u, g = *inp++*0x101u, b = *inp++*0x101u;",
      "w": " *out++ = r>>8; *out++ = g>>8; *out++ = b>>8;",
    },
    "fp": {
      "r": " float r = *inp++/255.f, g=*inp++/255.f, b = *inp++/255.f;",
      "w": " *out++ = 255*r+.5f; *out++ = 255*g+.5f; *out++ = 255*b+.5f;",
    },
  },
  "rgb161616": {
    "i8": {
      "r": " uint32_t r = *inp++>>8, g = *inp++>>8, b = *inp++>>8;",
      "w": " *out++ = r*0x101u; *out++ = g*0x101u; *out++ = b*0x101u;",
    },
    "i16": {
      "r": " uint32_t r = *inp++, g = *inp++, b = *inp++;",
      "w": " *out++ = r; *out++ = g; *out++ = b;",
    },
    "fp": {
      "r": " float r = *inp++/65535.f, g=*inp++/65535.f, b = *inp++/65535.f;",
      "w": " *out++ = 65535.f*r+.5f; *out++ = 65535.f*g+.5f; *out++ = 65535.f*b+.5f;",
    },
  },
  "rgbfloat": {
    "i8": {
      "r": " uint32_t r = *inp++*255+.5f, g = *inp++*255+.5f, b = *inp++*255+.5f;",
      "w": " *out++ = r/255.f; *out++ = g/255.f; *out++ = b/255.f;",
    },
    "i16": {
      "r": " uint32_t r = *inp++*65535.f+.5f, g = *inp++*65535.f+.5f, b = *inp++*65535.f+.5f;",
      "w": " *out++ = r/65535.f; *out++ = g/65535.f; *out++ = b/65535.f;",
    },
    "fp": {
      "r": " float r = *inp++, g=*inp++, b = *inp++;",
      "w": " *out++ = r; *out++ = g; *out++ = b;",
    },
  },

  "bgr565": {
    "i8": {
      "r": " uint16_t in = *(uint16_t*)inp;\n" +
           " uint32_t b = (in>>8)&0xf8u, g = (in>>3)&0xfcu, r = (in&0x1fu)<<3;",
      "w": " uint16_t ot = ((b&0xf8u)<<8) | ((g&0xfcu)<<3) | ((r&0xf8u)>>3);\n" +
           " *(uint16_t*)out = ot; out += sizeof(uint16_t);",
    },
    "i16": {
      "r": " uint16_t in = *(uint16_t*)inp;\n" +
           " uint32_t b = in&0xf800u, g = (in<<5)&0xfc00u, r = (in<<11)&0xf800u;",
      "w": " uint32_t ot = (b&0xf800u) | ((g>>5) & 0x07e0u) << 3) | (r>>11);\n" +
           " *(uint16_t*)out = ot; out += sizeof(uint16_t);",
    },
    "fp": {
      "r": " uint16_t in = *(uint16_t*)inp;\n" +
           " float b = (in>>11)/31.f, g = ((in>>5)&0x3fu)/63.f, r = (in&0x1fu)/31.f;",
      "w": " uint32_t vb = 31*b+.5f, vg = 63*g+.5f, vr = 31*r+.5f;\n" +
           " *out++ = ((vb<<11)&0xf800u) | ((vg<<6)&0x03e0u) | (vr&0x001fu);",
    },
  },
  "bgr888": {
    "i8": {
      "r": " uint32_t b = *inp++, g = *inp++, r = *inp++;",
      "w": " *out++ = b; *out++ = g; *out++ = r;",
    },
    "i16": {
      "r": " uint32_t b = *inp++*0x101u, g = *inp++*0x101u, r = *inp++*0x101u;",
      "w": " *out++ = b>>8; *out++ = g>>8; *out++ = r>>8;",
    },
    "fp": {
      "r": " float b = *inp++/255.f, g=*inp++/255.f, r = *inp++/255.f;",
      "w": " *out++ = 255*b+.5f; *out++ = 255*g+.5f; *out++ = 255*r+.5f;",
    },
  },
  "bgr8888": {
    "i8": {
      "r": " uint32_t b = *inp++, g = *inp++, r = *inp++;",
      "w": " *out++ = b; *out++ = g; *out++ = r; ++out;",
    },
    "i16": {
      "r": " uint32_t b = *inp++*0x101u, g = *inp++*0x101u, r = *inp++*0x101u;",
      "w": " *out++ = b>>8; *out++ = g>>8; *out++ = r>>8; ++out;",
    },
    "fp": {
      "r": " float b = *inp++/255.f, g=*inp++/255.f, r = *inp++/255.f;",
      "w": " *out++ = 255*b+.5f; *out++ = 255*g+.5f; *out++ = 255*r+.5f; ++out;",
    },
  },
  "bgr161616": {
    "i8": {
      "r": " uint32_t b = *inp++>>8, g = *inp++>>8, r = *inp++>>8;",
      "w": " *out++ = b*0x101u; *out++ = g*0x101u; *out++ = r*0x101u;",
    },
    "i16": {
      "r": " uint32_t b = *inp++, g = *inp++, r = *inp++;",
      "w": " *out++ = b; *out++ = g; *out++ = r;",
    },
    "fp": {
      "r": " float b = *inp++/65535.f, g=*inp++/65535.f, r = *inp++/65535.f;",
      "w": " *out++ = 65535.f*b+.5f; *out++ = 65535.f*g+.5f; *out++ = 65535.f*r+.5f;",
    },
  },
  "bgrfloat": {
    "i8": {
      "r": " uint32_t b = *inp++*255+.5f, g = *inp++*255+.5f, r = *inp++*255+.5f;",
      "w": " *out++ = b/255.f; *out++ = g/255.f; *out++ = r/255.f;",
    },
    "i16": {
      "r": " uint32_t b = *inp++*65535.f+.5f, g = *inp++*65535.f+.5f, r = *inp++*65535.f+.5f;",
      "w": " *out++ = b/65535.f; *out++ = g/65535.f; *out++ = r/65535.f;",
    },
    "fp": {
      "r": " float b = *inp++, g=*inp++, r = *inp++;",
      "w": " *out++ = b; *out++ = g; *out++ = r;",
    },
  },

  "yuv888": {
    "i8": {
      "r": " int32_t y = *inp++*0x010101u, u = *inp++, v = *inp++;",
      "w": " *out++ = y; *out++ = u; *out++ = v;",
    },
    "i16": {
      "r": " int32_t y = *inp++*0x010101u, u = *inp++<<8, v = *inp++<<8;",
      "w": " *out++ = y>>8; *out++ = u>>8; *out++ = v>>8;",
    },
  },
  "yuv161616": {
    "i8": {
      "r": " int32_t iy = *inp++, y = (iy<<8) | (iy>>8), u = *inp++>>8, v = *inp++>>8;",
      "w": " *out++ = y<<8; *out++ = u<<8; *out++ = v<<8;",
    },
    "i16": {
      "r": " int32_t iy = *inp++, y = (iy<<8) | (iy>>8), u = *inp++, v = *inp++;",
      "w": " *out++ = y; *out++ = u; *out++ = v;",
    },
  },

  "yuyv8888": {
    "i8": {
      "r": " int32_t iy = inp[(i&1)<<1], y = iy*0x010101u, u = inp[1], v = inp[3];",
      "w": " if( !(j&1) ) { *out++ = y; *out = u; out[2] = v; }\n" +
           " else { *out++ = u; *out++= y; *out++ = v; }",
    },
    "i16": {
      "r": " int32_t iy = inp[(i&1)<<1], y = iy*0x010101u, u = inp[1]<<8, v = inp[3]<<8;",
      "w": " if( !(j&1) ) { *out++ = y>>8; *out = u>>8; out[2] = v>>8; }\n" +
           " else { *out++ = u>>8; *out++= y>>8; *out++ = v>>8; }",
    },
  },

  "yuv10101010": {
    "i8": {
      "r": " int32_t it = (inp[0]<<0) | (inp[1]<<16);\n" +
           " int32_t y = ((it>>22)&0x3ffu)*0x4010u, u = (it>>14)&0xffu, v = (it>>4)&0xffu;",
      "w": " uint32_t ot = (y<<24) | (u<<14) | (v<<4);\n" +
           " *out++ = (ot>>0); *out++ = (ot>>16);",
    },
    "i16": {
      "r": " int32_t it = (inp[0]<<0) | (inp[1]<<16);\n" +
           " int32_t y = ((it>>22)&0x3ffu)*0x4010u, u = (it>>6)&0xffc0u, v = (it<<4)&0xffc0u;",
      "w": " uint32_t ot = ((y&0xffc0u)<<16) | ((u&0xffc0u)<<6) | ((v&0xffc0u)>>4);\n" +
           " *out++ = (ot>>0); *out++ = (ot>>16);",
    },
  },

  "vyu888": {
    "i8": {
      "r": " int32_t v = *inp++, y = *inp++*0x010101u, u = *inp++;",
      "w": " *out++ = v; *out++ = y; *out++ = u;",
    },
    "i16": {
      "r": " int32_t v = *inp++<<8, y = *inp++*0x010101u, u = *inp++<<8;",
      "w": " *out++ = v>>8; *out++ = y>>8; *out++ = u>>8;",
    },
  },

  "uyv888": {
    "i8": {
      "r": " int32_t u = *inp++, y = *inp++*0x010101u, v = *inp++;",
      "w": " *out++ = u; *out++ = y; *out++ = v;",
    },
    "i16": {
      "r": " int32_t u = *inp++<<8, y = *inp++*0x010101u, v = *inp++<<8;",
      "w": " *out++ = u>>8; *out++ = y>>8; *out++ = v>>8;",
    },
  },

  "yuv420p": {
    "i8": {
      "r": " int32_t y = *yip*0x010101u, u = *uip, v = *vip;",
      "w": " yop[j] = y;  uop[j/2] = u;  vop[j/2] = v;",
    },
    "i16": {
      "r": " int32_t y = *yip*0x010101u, u = *uip<<8, v = *vip<<8;",
      "w": " yop[j] = y>>8;  uop[j/2] = u>>8;  vop[j/2] = v>>8;",
    },
  },

  "yuv422p": {
    "i8": {
      "r": " int32_t y = *yip*0x010101u, u = *uip, v = *vip;",
      "w": " yop[j] = y;  uop[j/2] = u;  vop[j/2] = v;",
    },
    "i16": {
      "r": " int32_t y = *yip*0x010101u, u = *uip<<8, v = *vip<<8;",
      "w": " yop[j] = y>>8;  uop[j/2] = u>>8;  vop[j/2] = v>>8;",
    },
  },

  "yuv444p": {
    "i8": {
      "r": " int32_t y = *yip*0x010101u, u = *uip, v = *vip;",
      "w": " yop[j] = y;  uop[j] = u;  vop[j] = v;",
    },
    "i16": {
      "r": " int32_t y = *yip*0x010101u, u = *uip<<8, v = *vip<<8;",
      "w": " yop[j] = y>>8;  uop[j] = u>>8;  vop[j] = v>>8;",
    },
  },

  "yuv411p": {
    "i8": {
      "r": " int32_t y = *yip*0x010101u, u = *uip, v = *vip;",
      "w": " yop[j] = y;  uop[j/4] = u;  vop[j/4] = v;",
    },
    "i16": {
      "r": " int32_t y = *yip*0x010101u, u = *uip<<8, v = *vip<<8;",
      "w": " yop[j] = y>>8;  uop[j/4] = u>>8;  vop[j/4] = v>>8;",
    },
  },

  "yuv410p": {
    "i8": {
      "r": " int32_t y = *yip*0x010101u, u = *uip, v = *vip;",
      "w": " yop[j] = y;  uop[j/4] = u;  vop[j/4] = v;",
    },
    "i16": {
      "r": " int32_t y = *yip*0x010101u, u = *uip<<8, v = *vip<<8;",
      "w": " yop[j] = y>>8;  uop[j/4] = u>>8;  vop[j/4] = v>>8;",
    },
  },
  # alpha component
  "a8": {
    "i8": {
      "r": " z_int a = *inp++;",
      "w": " *out++ = a;",
    },
    "i16": {
      "r": " z_int a = *inp++<<8;",
      "w": " *out++ = a>>8;",
    },
    "fp": {
      "r": " z_float fa = *inp++/255.f;",
      "w": " *out++ = a*255.f+.5f;",
    },
  },
  "a16": {
    "i8": {
      "r": " z_int a = *inp++>>8;",
      "w": " *out++ = a<<8;",
    },
    "i16": {
      "r": " z_int a = *inp++;",
      "w": " *out++ = a;",
    },
    "fp": {
      "r": " z_float fa = *inp++/65535.f;",
      "w": " *out++ = a*65535.f+.5f;",
    },
  },
  "afp": {
    "i8": {
      "r": " z_int a = *inp++*255+.5f;",
      "w": " *out++ = a/255.f;",
    },
    "i16": {
      "r": " z_int a = *inp++*65535.f+.5f;",
      "w": " *out++ = a/65535.f;",
    },
    "fp": {
      "r": " z_float fa = *inp++;",
      "w": " *out++ = fa;",
    },
  },
  # alpha blend rgb/black, yuv/black, rgb/bg_color
  "brgb": {
    "i8": " r = r*a/0xffu; g = g*a/0xffu; b = b*a/0xffu;",
    "i16": " r = r*a/0xffffu; g = g*a/0xffffu; b = b*a/0xffffu;",
    "fp": " r *= fa; g *= fa; b *= fa;",
  },
  "byuv": {
    "i8": " z_int a1 = 0xffu-a;\n" +
          " y = y*a/0xffu; u = (u*a + 0x80u*a1)/0xffu; v = (v*a + 0x80u*a1)/0xffu;",
    "i16": " z_int a1 = 0xffffu-a;\n" +
           " y = y*a/0xffffu; u = (u*a + 0x8000u*a1)/0xffffu; v = (v*a + 0x8000u*a1)/0xffffu;",
  },
  "bbg": {
    "i8": " uint32_t a1 = 0xffu-a;\n" +
        " r = (r*a + bg_r*a1)/0xffu; g = (g*a + bg_g*a1)/0xffu; b = (b*a + bg_b*a1)/0xffu;",
    "i16": "uint32_t a1 = 0xffffu-a;\n" +
        " r = (r*a + bg_r*a1)/0xffffu; g = (g*a + bg_g*a1)/0xffffu; b = (b*a + bg_b*a1)/0xffffu;",
    "fp": " float a1 = 1-fa;\n" +
        " r = (r*fa + bg_r*a1); g = (g*fa + bg_g*a1); b = (b*fa + bg_b*a1);",
  },
}

cmodels = []
layout = {}
dtype = {}
special = {}

def add_cmodel(nm, typ=None, *args):
  global cmodels, layout, dtype
  cmodels += [nm,]
  dtype[nm] = typ
  layout[nm] = args

def specialize(fr_cmdl, to_cmdl, fn):
  global special
  special[(fr_cmdl, to_cmdl)] = fn

add_cmodel("bc_transparency")
add_cmodel("bc_compressed")

add_cmodel("bc_rgb8", "i8", "rgb8")
add_cmodel("bc_rgb565", "i8", "rgb565")
add_cmodel("bc_bgr565", "i8", "bgr565")
add_cmodel("bc_bgr888", "i8", "bgr888")
add_cmodel("bc_bgr8888", "i8", "bgr8888")

add_cmodel("bc_rgb888", "i8", "rgb888")
add_cmodel("bc_rgba8888", "i8", "rgb888", "a8")
add_cmodel("bc_argb8888", "i8", "a8", "rgb888")
add_cmodel("bc_abgr8888", "i8", "a8", "bgr888")
add_cmodel("bc_rgb161616", "i16", "rgb161616")
add_cmodel("bc_rgba16161616", "i16", "rgb161616", "a16")
add_cmodel("bc_yuv888", "i8", "yuv888")
add_cmodel("bc_yuva8888", "i8", "yuv888", "a8")
add_cmodel("bc_yuv161616", "i16", "yuv161616")
add_cmodel("bc_yuva16161616", "i16", "yuv161616", "a16")

add_cmodel("bc_yuv422", "i8", "yuyv8888")
add_cmodel("bc_a8")
add_cmodel("bc_a16")
add_cmodel("bc_a_float")
add_cmodel("bc_yuv101010", "i16", "yuv10101010")
add_cmodel("bc_vyu888", "i8", "vyu888")
add_cmodel("bc_uyva8888", "i8", "uyv888", "a8")
add_cmodel("bc_rgb_float", "fp", "rgbfloat")
add_cmodel("bc_rgba_float", "fp", "rgbfloat", "afp")

add_cmodel("bc_yuv420p", "i8", "yuv420p")
add_cmodel("bc_yuv422p", "i8", "yuv422p")
add_cmodel("bc_yuv444p", "i8", "yuv444p")
add_cmodel("bc_yuv411p", "i8", "yuv411p")
add_cmodel("bc_yuv410p", "i8", "yuv410p")

specialize("bc_rgba8888", "bc_transparency", "XFER_rgba8888_to_transparency")

ctype = {
  "i8": "uint8_t",
  "i16": "uint16_t",
  "fp": "float",
}

adata = {
  "i8": " z_int a=0xff;",
  "i16": " z_int a=0xffff;",
  "fp": " z_float fa=1;",
}

def has_alpha(nm):
  return nm in ["bc_rgba8888", "bc_argb8888", "bc_abgr8888", \
    "bc_rgba16161616", "bc_yuva8888", "bc_yuva16161616", \
    "bc_uyva8888", "bc_rgba_float", ]

def has_bgcolor(fr_cmdl,to_cmdl):
  return fr_cmdl in ["bc_rgba8888"] and \
    to_cmdl in ["bc_rgba888", "bc_bgr565", "bc_rgb565", \
     "bc_bgr888", "bc_rgb888", "bc_bgr8888"]

def is_specialized(fr_cmdl,to_cmdl):
  global special
  return special.get((fr_cmdl, to_cmdl)) is not None

def is_rgb(nm):
  return nm in [ "bc_rgb8", "bc_rgb565", "bc_bgr565", \
    "bc_bgr888", "bc_bgr8888", "bc_rgb888", "bc_rgba8888", \
    "bc_argb8888", "bc_abgr8888", "bc_rgb", "bc_rgb161616", \
    "bc_rgba16161616", "bc_rgb_float", "bc_rgba_float", ]

def is_yuv(nm):
  return nm in [ "bc_yuv888", "bc_yuva8888", "bc_yuv161616", \
    "bc_yuva16161616", "bc_yuv422", "bc_yuv101010", "bc_vyu888", \
    "bc_uyva8888", "bc_yuv420p", "bc_yuv422p", "bc_yuv444p", \
    "bc_yuv411p", "bc_yuv410p"]

def is_planar(nm):
  return nm in [ "bc_yuv420p", "bc_yuv422p", "bc_yuv444p", \
    "bc_yuv411p", "bc_yuv410p"]

def is_float(nm):
  return nm in ["bc_rgb_float", "bc_rgba_float",]

def gen_xfer_proto(pfx, cls, fr_cmdl, to_cmdl):
  global dtype, ctype
  print "%svoid %sxfer_%s_to_%s" % (pfx, cls, fr_cmdl[3:], to_cmdl[3:]),
  ityp = dtype[fr_cmdl];  fr_typ = ctype[ityp];
  otyp = dtype[to_cmdl];  to_typ = ctype[otyp];
  print "(",
  if( is_planar(fr_cmdl) ):
    print "%s *yip, %s *uip, %s *vip, unsigned i," % (fr_typ, fr_typ, fr_typ),
  else:
    print "%s *inp, unsigned i," % (fr_typ),
  if( is_planar(to_cmdl) ):
    print "%s *yop, %s *uop, %s *vop, unsigned j" % (to_typ, to_typ, to_typ),
  else:
    print "%s *&out, unsigned j" % (to_typ),
  print ")",

def gen_xfer_fn(fr_cmdl, to_cmdl):
  global layout, dtype, adata
  ityp = dtype[fr_cmdl];  otyp = dtype[to_cmdl]
  if( ityp is None or otyp is None ): return
  # xfr fn header
  gen_xfer_proto("inline ", "BC_Xfer::", fr_cmdl, to_cmdl);
  # xfr fn body
  print "{"
  # load inp
  if( is_float(to_cmdl) and is_yuv(fr_cmdl) ):
    for ic in layout[fr_cmdl]: print "%s" % (base[ic][ityp]['r']),
    if( ityp == "i8" ):
      print "\n float fy = y/16777215.f, r, g, b; YUV_TO_FLOAT(fy, u, v, r, g, b);",
    elif( ityp == "i16" ):
      print "\n float fy = y/16777215.f, r, g, b; YUV16_TO_RGB_FLOAT(fy, u, v, r, g, b);",
    if( has_alpha(fr_cmdl) or has_alpha(to_cmdl) ):
      if( not has_alpha(fr_cmdl) ):
        print " z_float fa = 1;",
      elif( ityp == "i8" ):
        print " float fa = a/255.f;",
      elif( ityp == "i16" ):
        print " float fa = a/65535.f;",
    fr_cmdl = "bc_rgba_float" if has_alpha(fr_cmdl) else "bc_rgb_float"
  else:
    for ic in layout[fr_cmdl]: print "%s" % (base[ic][otyp]['r']),
    if( has_alpha(to_cmdl) and not has_alpha(fr_cmdl) ):
      print "%s" % (adata[otyp]),
  print ""
  # xfer
  if( is_rgb(fr_cmdl) and is_yuv(to_cmdl) ):
    if( otyp == "i8" ):
      print " int32_t y, u, v;  RGB_TO_YUV(y, u, v, r, g, b);"
    elif( otyp == "i16" ):
      print " int32_t y, u, v;  RGB_TO_YUV16(y, u, v, r, g, b);"
  elif( is_yuv(fr_cmdl) and is_rgb(to_cmdl)):
    if( otyp == "i8" ):
      print " int32_t r, g, b;  YUV_TO_RGB(y, u, v, r, g, b);"
    elif( otyp == "i16" ):
      print " int32_t r, g, b;  YUV_TO_RGB16(y, u, v, r, g, b);"
  elif( is_yuv(fr_cmdl) and is_yuv(to_cmdl) ):
    if( otyp == "i8" ):
      print " y >>= 16;",
    elif( otyp == "i16" ):
      print " y >>= 8;",
  # blend
  if( has_bgcolor(fr_cmdl,to_cmdl) ):
    print "%s" % (base["bbg"][otyp])
  elif( has_alpha(fr_cmdl) and not has_alpha(to_cmdl) ):
    if( is_rgb(to_cmdl) ):
      print "%s" % (base["brgb"][otyp])
    elif( is_yuv(to_cmdl) ):
      print "%s" % (base["byuv"][otyp])
  # store out
  for oc in layout[to_cmdl]:
    print "%s" % (base[oc][otyp]['w']),
  print ""
  print "}"
  print ""

# output code file

print "#include \"xfer.h\""
print ""
print "class BC_Xfer {"
print "public:"
print """  BC_Xfer(unsigned char **output_rows, unsigned char **input_rows,
    unsigned char *out_y_plane, unsigned char *out_u_plane, unsigned char *out_v_plane,
    unsigned char *in_y_plane, unsigned char *in_u_plane, unsigned char *in_v_plane,
    int in_x, int in_y, int in_w, int in_h, int out_x, int out_y, int out_w, int out_h,
    int in_colormodel, int out_colormodel, int bg_color, int in_rowspan, int out_rowspan);"""
print "  ~BC_Xfer();"
print ""
print "  unsigned char **output_rows, **input_rows;"
print "  unsigned char *out_y_plane, *out_u_plane, *out_v_plane;"
print "  unsigned char *in_y_plane, *in_u_plane, *in_v_plane;"
print "  int in_x, in_y; unsigned in_w, in_h;"
print "  int out_x, out_y; unsigned out_w, out_h;"
print "  int in_colormodel, out_colormodel;"
print "  uint32_t bg_color, total_in_w, total_out_w;"
print "  int scale;"
print "  int out_pixelsize, in_pixelsize;"
print "  int *row_table, *column_table;"
print "  uint32_t bg_r, bg_g, bg_b;"
print ""
print "  void xfer();"
print ""
print "  static void init();"
print "  static class Tables { public: Tables() { init(); } } tables;"
print "  static int rtoy_tab[0x100], gtoy_tab[0x100], btoy_tab[0x100];"
print "  static int rtou_tab[0x100], gtou_tab[0x100], btou_tab[0x100];"
print "  static int rtov_tab[0x100], gtov_tab[0x100], btov_tab[0x100];"
print "  static int vtor_tab[0x100], vtog_tab[0x100];"
print "  static int utog_tab[0x100], utob_tab[0x100];"
print "  static float vtor_float_tab[0x100], vtog_float_tab[0x100];"
print "  static float utog_float_tab[0x100], utob_float_tab[0x100];"
print "  static int rtoy_tab16[0x10000], gtoy_tab16[0x10000], btoy_tab16[0x10000];"
print "  static int rtou_tab16[0x10000], gtou_tab16[0x10000], btou_tab16[0x10000];"
print "  static int rtov_tab16[0x10000], gtov_tab16[0x10000], btov_tab16[0x10000];"
print "  static int vtor_tab16[0x10000], vtog_tab16[0x10000];"
print "  static int utog_tab16[0x10000], utob_tab16[0x10000];"
print "  static float v16tor_float_tab[0x10000], v16tog_float_tab[0x10000];"
print "  static float u16tog_float_tab[0x10000], u16tob_float_tab[0x10000];"
print ""

for fr_cmdl in cmodels:
  ityp = dtype[fr_cmdl]
  for to_cmdl in cmodels:
    otyp = dtype[to_cmdl]
    if( is_specialized(fr_cmdl, to_cmdl) ):
      print "  void %s();" % (special[(fr_cmdl, to_cmdl)])
      continue
    if( ityp is None or otyp is None ): continue
    gen_xfer_proto("  ", "", fr_cmdl, to_cmdl);
    print ";"
print "};"
print ""
print ""

for fr_cmdl in cmodels:
  for to_cmdl in cmodels:
    gen_xfer_fn(fr_cmdl, to_cmdl)

# add fix to round in_w/in_h/out_w/out_h down to macro pixel granularity
print ""
print ""
print "void BC_Xfer::xfer()"
print "{"
print "  switch(in_colormodel) {"
for fr_cmdl in cmodels:
  ityp = dtype[fr_cmdl]
  if( ityp is None ):
    if( not fr_cmdl in [it[0] for it in special] ): continue
  print "  case %s:" % (fr_cmdl.upper())
  print "    switch(out_colormodel) {"
  for to_cmdl in cmodels:
    if( is_specialized(fr_cmdl, to_cmdl) ):
      print "    case %s: %s(); break;" % (to_cmdl.upper(), special[(fr_cmdl, to_cmdl)])
      continue
    otyp = dtype[to_cmdl]
    if( ityp is None or otyp is None ): continue
    print "    case %s:" % (to_cmdl.upper()),
    idat = "PLANAR" if is_planar(fr_cmdl) else "FLAT"
    odat = "PLANAR" if is_planar(to_cmdl) else "FLAT"
    print "XFER_%s_to_%s(%s,%s,%s,%s);" \
        % (idat, odat, fr_cmdl[3:], ityp, to_cmdl[3:], otyp),
    print "break;"
  print "    }"
  print "    break;"
print "  }"
print "}"
print ""
print "#include \"xfer.C\""
print ""

