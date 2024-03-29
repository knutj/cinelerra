/*
 * most other tables are calculated on program start (which is (of course)
 * not ISO-conform) .. 
 * Layer-3 huffman table is in huffman.h
 */

#include "../libzmpeg3.h"

static zaudio_t::imdct_al_table_t alloc_0[] = {
  {4,0},{5,3},{3,-3},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},{9,-255},{10,-511},
  {11,-1023},{12,-2047},{13,-4095},{14,-8191},{15,-16383},{16,-32767},
  {4,0},{5,3},{3,-3},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},{9,-255},{10,-511},
  {11,-1023},{12,-2047},{13,-4095},{14,-8191},{15,-16383},{16,-32767},
  {4,0},{5,3},{3,-3},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},{9,-255},{10,-511},
  {11,-1023},{12,-2047},{13,-4095},{14,-8191},{15,-16383},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767}
};

static zaudio_t::imdct_al_table_t alloc_1[] = {
  {4,0},{5,3},{3,-3},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},{9,-255},{10,-511},
  {11,-1023},{12,-2047},{13,-4095},{14,-8191},{15,-16383},{16,-32767},
  {4,0},{5,3},{3,-3},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},{9,-255},{10,-511},
  {11,-1023},{12,-2047},{13,-4095},{14,-8191},{15,-16383},{16,-32767},
  {4,0},{5,3},{3,-3},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},{9,-255},{10,-511},
  {11,-1023},{12,-2047},{13,-4095},{14,-8191},{15,-16383},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {3,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767},
  {2,0},{5,3},{7,5},{16,-32767}
};

static zaudio_t::imdct_al_table_t alloc_2[] = {
  {4,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},{9,-255},
  {10,-511},{11,-1023},{12,-2047},{13,-4095},{14,-8191},{15,-16383},
  {4,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},{9,-255},
  {10,-511},{11,-1023},{12,-2047},{13,-4095},{14,-8191},{15,-16383},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63}
};

static zaudio_t::imdct_al_table_t alloc_3[] = {
  {4,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},{9,-255},
  {10,-511},{11,-1023},{12,-2047},{13,-4095},{14,-8191},{15,-16383},
  {4,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},{9,-255},
  {10,-511},{11,-1023},{12,-2047},{13,-4095},{14,-8191},{15,-16383},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63}
};

static zaudio_t::imdct_al_table_t alloc_4[] = {
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{14,-8191},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{14,-8191},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{14,-8191},
  {4,0},{5,3},{7,5},{3,-3},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},{8,-127},
  {9,-255},{10,-511},{11,-1023},{12,-2047},{13,-4095},{14,-8191},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {3,0},{5,3},{7,5},{10,9},{4,-7},{5,-15},{6,-31},{7,-63},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9},
  {2,0},{5,3},{7,5},{10,9}
};

int zaudio_decoder_layer_t::
select_table()
{
  static int translate[3][2][16] = {
    {{ 0,2,2,2,2,2,2,0,0,0,1,1,1,1,1,0},
     { 0,2,2,0,0,0,1,1,1,1,1,1,1,1,1,0}},
    {{ 0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0},
     { 0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {{ 0,3,3,3,3,3,3,0,0,0,1,1,1,1,1,0},
     { 0,3,3,0,0,0,1,1,1,1,1,1,1,1,1,0}}
  };
  int table, sblim;
  static imdct_al_table_t *tables[5] = {
    alloc_0, alloc_1, alloc_2, alloc_3, alloc_4
  };
  static int sblims[5] = {27, 30, 8, 12, 30};

  if( lsf )
    table = 4;
  else
    table = translate[sampling_frequency_code][2 - channels][bitrate_index];
  sblim = sblims[table];

  alloc = tables[table];
  II_sblimit = sblim;
  return 0;
}

int zaudio_decoder_layer_t::
step_one(uint8_t *bit_alloc, int *scale)
{
  int stereo = channels - 1;
  int sblimit = II_sblimit;
  int sblimit2 = II_sblimit << stereo;
  imdct_al_table_t *alloc1 = alloc;
  int i, result = 0;
  uint8_t *scfsi_buf = layer2_scfsi_buf;
  uint8_t *scfsi, *bita;
  uint8_t *bita_end = bit_alloc + 64;
  int sc, step;

  bita = bit_alloc;
  if( stereo ) {
    /* Stereo */
    for( i=jsbound; --i>=0 && bita < bita_end-2; alloc1+=(1<<step) ) {
      *bita++ = (char)stream->get_bits(step = alloc1->bits);
      *bita++ = (char)stream->get_bits(step);
    }
    for( i=sblimit-jsbound; --i>=0 && bita < bita_end-2; alloc1+=(1<<step)) {
      bita[0] = (char)stream->get_bits(step = alloc1->bits);
      bita[1] = bita[0];
      bita += 2;
    }
    bita = bit_alloc;
    scfsi = scfsi_buf;
    for( i=sblimit2; --i>=0 ; )
      if( *bita++ )
        *scfsi++ = (char)stream->get_bits(2);
  }
  else {
    /* mono */
    for( i=sblimit; --i>=0 ; alloc1+=(1<<step) )
      *bita++ = (char)stream->get_bits(step = alloc1->bits);
      bita = bit_alloc;
      scfsi = scfsi_buf;
      for( i=sblimit; --i>=0 ; )
        if( *bita++ )
          *scfsi++ = (char)stream->get_bits(2);
  }

  bita = bit_alloc;
  scfsi = scfsi_buf;
  for( i=sblimit2; --i>=0; ) {
    if( *bita++ ) switch(*scfsi++) {
    case 0: 
      *scale++ = stream->get_bits(6);
      *scale++ = stream->get_bits(6);
      *scale++ = stream->get_bits(6);
      break;
    case 1 : 
      *scale++ = sc = stream->get_bits(6);
      *scale++ = sc;
      *scale++ = stream->get_bits(6);
      break;
    case 2: 
      *scale++ = sc = stream->get_bits(6);
      *scale++ = sc;
      *scale++ = sc;
      break;
    default:              /* case 3 */
      *scale++ = stream->get_bits(6);
      *scale++ = sc = stream->get_bits(6);
      *scale++ = sc;
      break;
    }
  }
  return result;
}

int zaudio_decoder_layer_t::
step_two(uint8_t *bit_alloc, float fraction[2][4][SBLIMIT], int *scale, int x1)
{
  int i, j, k, ba, result = 0;
  int sblimit = II_sblimit;
  imdct_al_table_t *alloc2, *alloc1 = alloc;
  uint8_t *bita = bit_alloc;
  int d1, step;

  for( i=0; i<jsbound; ++i, alloc1+=(1<<step) ) {
    step = alloc1->bits;
    for( j=0; j<channels; ++j ) {
      if( (ba=*bita++) != 0 ) {
        k = (alloc2 = alloc1 + ba)->bits;
        if( (d1 = alloc2->d) < 0 ) {
          float cm = muls[k][scale[x1]];
          fraction[j][0][i] = ((float)((int)stream->get_bits(k) + d1)) * cm;
          fraction[j][1][i] = ((float)((int)stream->get_bits(k) + d1)) * cm;
          fraction[j][2][i] = ((float)((int)stream->get_bits(k) + d1)) * cm;
        }
        else {
          static int *table[] = 
            {0, 0, 0, grp_3tab, 0, grp_5tab, 0, 0, 0, grp_9tab};
          uint32_t idx, *tab, m = scale[x1];
          idx = (uint32_t)stream->get_bits(k);
          tab = (uint32_t*)(table[d1] + idx + idx + idx);
          fraction[j][0][i] = muls[*tab++][m];
          fraction[j][1][i] = muls[*tab++][m];
          fraction[j][2][i] = muls[*tab][m];  
        }
        scale += 3;
      }
      else
        fraction[j][0][i] = fraction[j][1][i] = fraction[j][2][i] = 0.0;
    }
  }

  for( i=jsbound; i<sblimit; ++i, alloc1+=(1<<step) ) {
    step = alloc1->bits;
    /* channel 1 and channel 2 bitalloc are the same */
    ++bita;    
    if( (ba=*bita++) != 0 ) {
      k= (alloc2 = alloc1+ba)->bits;
      if( (d1 = alloc2->d) < 0 ) {
        float cm = muls[k][scale[x1 + 3]];
        fraction[1][0][i] = (fraction[0][0][i] = (float)((int)stream->get_bits(k) + d1)) * cm;
        fraction[1][1][i] = (fraction[0][1][i] = (float)((int)stream->get_bits(k) + d1)) * cm;
        fraction[1][2][i] = (fraction[0][2][i] = (float)((int)stream->get_bits(k) + d1)) * cm;
        cm = muls[k][scale[x1]];
        fraction[0][0][i] *= cm; 
        fraction[0][1][i] *= cm; 
        fraction[0][2][i] *= cm;
      }
      else {
        static int *table[] = {0, 0, 0, grp_3tab, 0, grp_5tab, 0, 0, 0, grp_9tab};
        uint8_t idx, *tab, m1, m2;
        m1 = scale[x1]; 
        m2 = scale[x1+3];
        idx = (uint8_t)stream->get_bits(k);
        tab = (uint8_t*)(table[d1] + idx + idx + idx);
        fraction[0][0][i] = muls[*tab][m1]; 
        fraction[1][0][i] = muls[*tab++][m2];
        fraction[0][1][i] = muls[*tab][m1]; 
        fraction[1][1][i] = muls[*tab++][m2];
        fraction[0][2][i] = muls[*tab][m1]; 
        fraction[1][2][i] = muls[*tab][m2];
      }
      scale += 6;
    }
    else {
      fraction[0][0][i] = fraction[0][1][i] = fraction[0][2][i] =
      fraction[1][0][i] = fraction[1][1][i] = fraction[1][2][i] = 0.0;
    }
/* 
   should we use individual scalefac for channel 2 or
   is the current way the right one , where we just copy channel 1 to
   channel 2 ?? 
   The current 'strange' thing is, that we throw away the scalefac
   values for the second channel ...!!
-> changed .. now we use the scalefac values of channel one !! 
*/
  }

  if( sblimit > (int)SBLIMIT ) sblimit = SBLIMIT;
  for( i=sblimit; i < (int)SBLIMIT; ++i )
    for( j=0; j < channels; ++j )
      fraction[j][0][i] = fraction[j][1][i] = fraction[j][2][i] = 0.0;

  return result;
}

int zaudio_decoder_layer_t::
do_layer2(uint8_t *zframe, int zframe_size, float **zoutput, int render)
{
  int i, j, result = 0;
  float fraction[2][4][SBLIMIT]; /* pick_table clears unused subbands */
  uint8_t bit_alloc[64];
  int scale[192];
  int zsingle = single;
  int output_position = 0;
//zmsg("1\n");
  zframe += 4;
  /* Set up bitstream to use buffer */
  stream->use_ptr(zframe);
  if( error_protection )
    stream->get_bits(16);

  select_table();

  jsbound = (mode == md_JOINT_STEREO) ?
    (mode_ext << 2) + 4 : II_sblimit;

  if( channels == 1 || zsingle == 3 )
    zsingle = 0;

  result |= step_one(bit_alloc, scale);

  for( i=0; i < (int)SCALE_BLOCK && !result; ++i ) {
    result |= step_two(bit_alloc, fraction, scale, i >> 2);
    for( j=0; j < 3; ++j ) {
      if( zsingle >= 0 ) {
        /* Monaural */
        if( render )
          synth_stereo(fraction[0][j], 0, zoutput[0], &output_position);
        else
          output_position += 32;
      }
      else {
        /* Stereo */
        int p1 = output_position;
        if( render ) {
//zmsg(" 3\n");
          synth_stereo(fraction[0][j], 0, zoutput[0], &p1);
//zmsg(" 4\n");
          synth_stereo(fraction[1][j], 1, zoutput[1], &output_position);
//zmsg(" 5\n");
        }
        else
          output_position += 32;
      }
    }
  }

  return output_position;
}

