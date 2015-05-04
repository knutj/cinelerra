#include "bccmodels.h"
#include "clip.h"
#include <stdint.h>

#define ZTYP(ty) typedef ty z_##ty __attribute__ ((__unused__))
ZTYP(int);
ZTYP(float);

// All variables are unsigned
// y -> 24 bits u, v, -> 8 bits r, g, b -> 8 bits
#define YUV_TO_RGB(y, u, v, r, g, b) \
{ \
	(r) = ((y + vtor_tab[v]) >> 16); \
	(g) = ((y + utog_tab[u] + vtog_tab[v]) >> 16); \
	(b) = ((y + utob_tab[u]) >> 16); \
	CLAMP(r, 0, 0xff); CLAMP(g, 0, 0xff); CLAMP(b, 0, 0xff); \
}

// y -> 0 - 1 float
// u, v, -> 8 bits
// r, g, b -> float
#define YUV_TO_FLOAT(y, u, v, r, g, b) \
{ \
	(r) = y + vtor_float_tab[v]; \
	(g) = y + utog_float_tab[u] + vtog_float_tab[v]; \
	(b) = y + utob_float_tab[u]; \
}

// y -> 0 - 1 float
// u, v, -> 16 bits
// r, g, b -> float
#define YUV16_TO_RGB_FLOAT(y, u, v, r, g, b) \
{ \
	(r) = y + v16tor_float_tab[v]; \
	(g) = y + u16tog_float_tab[u] + v16tog_float_tab[v]; \
	(b) = y + u16tob_float_tab[u]; \
}

// y -> 24 bits   u, v-> 16 bits
#define YUV_TO_RGB16(y, u, v, r, g, b) \
{ \
	(r) = ((y + vtor_tab16[v]) >> 8); \
	(g) = ((y + utog_tab16[u] + vtog_tab16[v]) >> 8); \
	(b) = ((y + utob_tab16[u]) >> 8); \
	CLAMP(r, 0, 0xffff); CLAMP(g, 0, 0xffff); CLAMP(b, 0, 0xffff); \
}




#define RGB_TO_YUV(y, u, v, r, g, b) \
{ \
	y = ((rtoy_tab[r] + gtoy_tab[g] + btoy_tab[b]) >> 16); \
	u = ((rtou_tab[r] + gtou_tab[g] + btou_tab[b]) >> 16); \
	v = ((rtov_tab[r] + gtov_tab[g] + btov_tab[b]) >> 16); \
	CLAMP(y, 0, 0xff); CLAMP(u, 0, 0xff); CLAMP(v, 0, 0xff); \
}

// r, g, b -> 16 bits
#define RGB_TO_YUV16(y, u, v, r, g, b) \
{ \
	y = ((rtoy_tab16[r] + gtoy_tab16[g] + btoy_tab16[b]) >> 8); \
	u = ((rtou_tab16[r] + gtou_tab16[g] + btou_tab16[b]) >> 8); \
	v = ((rtov_tab16[r] + gtov_tab16[g] + btov_tab16[b]) >> 8); \
	CLAMP(y, 0, 0xffff); CLAMP(u, 0, 0xffff); CLAMP(v, 0, 0xffff); \
}

typedef union { uint8_t *i8; uint16_t *i16; float *fp; } iop_t;

#define xfer_flat_row_out \
    iop_t out; out.i8 = output_rows[i + out_y] + out_x * out_pixelsize; \

#define xfer_flat_row_in \
    iop_t inp_row; inp_row.i8 = input_rows[row_table[i]]; \

#define xfer_flat_col_in \
    iop_t inp; inp.i8 = inp_row.i8 + column_table[j]; \


// yuv420p  2x2
#define xfer_yuv420p_out \
    iop_t yop; yop.i8 = out_y_plane + i * total_out_w + out_x; \
    iop_t uop; uop.i8 = out_u_plane + i / 2 * total_out_w / 2 + out_x / 2; \
    iop_t vop; vop.i8 = out_v_plane + i / 2 * total_out_w / 2 + out_x / 2; \

#define xfer_yuv420p_row_in \
    iop_t yip_row; yip_row.i8 = in_y_plane + row_table[i] * total_in_w; \
    iop_t uip_row; uip_row.i8 = in_u_plane + row_table[i] / 2 * total_in_w / 2; \
    iop_t vip_row; vip_row.i8 = in_v_plane + row_table[i] / 2 * total_in_w / 2; \

#define xfer_yuv420p_col_in \
    iop_t yip; yip.i8 = yip_row.i8 + column_table[j]; \
    iop_t uip; uip.i8 = uip_row.i8 + column_table[j] / 2; \
    iop_t vip; vip.i8 = vip_row.i8 + column_table[j] / 2; \

// yuv422p  2x1
#define xfer_yuv422p_out \
    iop_t yop; yop.i8 = out_y_plane + i * total_out_w + out_x; \
    iop_t uop; uop.i8 = out_u_plane + i * total_out_w / 2 + out_x / 2; \
    iop_t vop; vop.i8 = out_v_plane + i * total_out_w / 2 + out_x / 2; \

#define xfer_yuv422p_row_in \
    iop_t yip_row; yip_row.i8 = in_y_plane + row_table[i] * total_in_w; \
    iop_t uip_row; uip_row.i8 = in_u_plane + row_table[i] * total_in_w / 2; \
    iop_t vip_row; vip_row.i8 = in_v_plane + row_table[i] * total_in_w / 2; \

#define xfer_yuv422p_col_in \
    iop_t yip; yip.i8 = yip_row.i8 + column_table[j]; \
    iop_t uip; uip.i8 = uip_row.i8 + column_table[j] / 2; \
    iop_t vip; vip.i8 = vip_row.i8 + column_table[j] / 2; \

// yuv444p  1x1
#define xfer_yuv444p_out \
    iop_t yop; yop.i8 = out_y_plane + i * total_out_w + out_x; \
    iop_t uop; uop.i8 = out_u_plane + i * total_out_w + out_x; \
    iop_t vop; vop.i8 = out_v_plane + i * total_out_w + out_x; \

#define xfer_yuv444p_row_in \
    iop_t yip_row; yip_row.i8 = in_y_plane + row_table[i] * total_in_w; \
    iop_t uip_row; uip_row.i8 = in_u_plane + row_table[i] * total_in_w; \
    iop_t vip_row; vip_row.i8 = in_v_plane + row_table[i] * total_in_w; \

#define xfer_yuv444p_col_in \
    iop_t yip; yip.i8 = yip_row.i8 + column_table[j]; \
    iop_t uip; uip.i8 = uip_row.i8 + column_table[j]; \
    iop_t vip; vip.i8 = vip_row.i8 + column_table[j]; \

// yuv411p  4x1
#define xfer_yuv411p_out \
    iop_t yop; yop.i8 = out_y_plane + i * total_out_w + out_x; \
    iop_t uop; uop.i8 = out_u_plane + i * total_out_w / 4 + out_x / 4; \
    iop_t vop; vop.i8 = out_v_plane + i * total_out_w / 4 + out_x / 4; \

#define xfer_yuv411p_row_in \
    iop_t yip_row; yip_row.i8 = in_y_plane + row_table[i] * total_in_w; \
    iop_t uip_row; uip_row.i8 = in_u_plane + row_table[i] * total_in_w / 4; \
    iop_t vip_row; vip_row.i8 = in_v_plane + row_table[i] * total_in_w / 4; \

#define xfer_yuv411p_col_in \
    iop_t yip; yip.i8 = yip_row.i8 + column_table[j]; \
    iop_t uip; uip.i8 = uip_row.i8 + column_table[j] / 4; \
    iop_t vip; vip.i8 = vip_row.i8 + column_table[j] / 4; \

// yuv410p  4x4
#define xfer_yuv410p_out \
    iop_t yop; yop.i8 = out_y_plane + i * total_out_w + out_x; \
    iop_t uop; uop.i8 = out_u_plane + (i / 4 * total_out_w / 4) + out_x / 4; \
    iop_t vop; vop.i8 = out_v_plane + (i / 4 * total_out_w / 4) + out_x / 4; \

#define xfer_yuv410p_row_in \
    iop_t yip_row; yip_row.i8 = in_y_plane + row_table[i] * total_in_w; \
    iop_t uip_row; uip_row.i8 = in_u_plane + row_table[i] / 4 * total_in_w / 4; \
    iop_t vip_row; vip_row.i8 = in_v_plane + row_table[i] / 4 * total_in_w / 4; \

#define xfer_yuv410p_col_in \
    iop_t yip; yip.i8 = yip_row.i8 + column_table[j]; \
    iop_t uip; uip.i8 = uip_row.i8 + column_table[j] / 4; \
    iop_t vip; vip.i8 = vip_row.i8 + column_table[j] / 4; \

#define XFER_FLAT_to_FLAT(icm,p,ocm,q) \
  for( unsigned i=0; i<out_h; ++i ) { \
    xfer_flat_row_in  xfer_flat_row_out \
    for( unsigned j=0; j<out_w; ++j ) { xfer_flat_col_in \
      xfer_##icm##_to_##ocm(inp.p, i, out.q, j); \
    } \
  } 
 
#define XFER_FLAT_to_PLANAR(icm,p,ocm,q) \
  for( unsigned i=0; i<out_h; ++i ) { \
    xfer_flat_row_in  xfer_##ocm##_out \
    for( unsigned j=0; j<out_w; ++j ) { xfer_flat_col_in \
      xfer_##icm##_to_##ocm(inp.p, i, yop.q, uop.q, vop.q, j); \
    } \
  } 
 
#define XFER_PLANAR_to_FLAT(icm,p,ocm,q) \
  for( unsigned i=0; i<out_h; ++i ) { \
    xfer_flat_row_out xfer_##icm##_row_in \
    for( unsigned j=0; j<out_w; ++j ) { xfer_##icm##_col_in \
      xfer_##icm##_to_##ocm(yip.p, uip.p, vip.p, i, out.q, j); \
    } \
  } 
 
#define XFER_PLANAR_to_PLANAR(icm,p,ocm,q) \
  for( unsigned i=0; i<out_h; ++i ) { \
    xfer_##ocm##_out xfer_##icm##_row_in \
    for( unsigned j=0; j<out_w; ++j ) { xfer_##icm##_col_in \
      xfer_##icm##_to_##ocm(yip.p, uip.p, vip.p, i, yop.q, uop.q, vop.q, j); \
    } \
  } 

