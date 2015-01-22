/*
 * Copyright (c) 2003 Matteo Frigo
 * Copyright (c) 2003 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sat Jul  5 21:58:04 EDT 2003 */

#include "codelet-rdft.h"

/* Generated by: /homee/stevenj/cvs/fftw3.0.1/genfft/gen_r2hc -compact -variables 4 -n 8 -name r2hcII_8 -dft-II -include r2hcII.h */

/*
 * This function contains 22 FP additions, 10 FP multiplications,
 * (or, 18 additions, 6 multiplications, 4 fused multiply/add),
 * 18 stack variables, and 16 memory accesses
 */
/*
 * Generator Id's : 
 * $Id: algsimp.ml,v 1.7 2003/03/15 20:29:42 stevenj Exp $
 * $Id: fft.ml,v 1.2 2003/03/15 20:29:42 stevenj Exp $
 * $Id: gen_r2hc.ml,v 1.13 2003/04/17 19:25:50 athena Exp $
 */

#include "r2hcII.h"

static void r2hcII_8(const R *I, R *ro, R *io, stride is, stride ros, stride ios, int v, int ivs, int ovs)
{
     DK(KP382683432, +0.382683432365089771728459984030398866761344562);
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     int i;
     for (i = v; i > 0; i = i - 1, I = I + ivs, ro = ro + ovs, io = io + ovs) {
	  E T1, Tj, T4, Ti, T8, Te, Tb, Tf, T2, T3;
	  T1 = I[0];
	  Tj = I[WS(is, 4)];
	  T2 = I[WS(is, 2)];
	  T3 = I[WS(is, 6)];
	  T4 = KP707106781 * (T2 - T3);
	  Ti = KP707106781 * (T2 + T3);
	  {
	       E T6, T7, T9, Ta;
	       T6 = I[WS(is, 1)];
	       T7 = I[WS(is, 5)];
	       T8 = FNMS(KP382683432, T7, KP923879532 * T6);
	       Te = FMA(KP382683432, T6, KP923879532 * T7);
	       T9 = I[WS(is, 3)];
	       Ta = I[WS(is, 7)];
	       Tb = FNMS(KP923879532, Ta, KP382683432 * T9);
	       Tf = FMA(KP923879532, T9, KP382683432 * Ta);
	  }
	  {
	       E T5, Tc, Th, Tk;
	       T5 = T1 + T4;
	       Tc = T8 + Tb;
	       ro[WS(ros, 3)] = T5 - Tc;
	       ro[0] = T5 + Tc;
	       Th = Te + Tf;
	       Tk = Ti + Tj;
	       io[0] = -(Th + Tk);
	       io[WS(ios, 3)] = Tk - Th;
	  }
	  {
	       E Td, Tg, Tl, Tm;
	       Td = T1 - T4;
	       Tg = Te - Tf;
	       ro[WS(ros, 2)] = Td - Tg;
	       ro[WS(ros, 1)] = Td + Tg;
	       Tl = Tb - T8;
	       Tm = Tj - Ti;
	       io[WS(ios, 2)] = Tl - Tm;
	       io[WS(ios, 1)] = Tl + Tm;
	  }
     }
}

static const kr2hc_desc desc = { 8, "r2hcII_8", {18, 6, 4, 0}, &GENUS, 0, 0, 0, 0, 0 };

void X(codelet_r2hcII_8) (planner *p) {
     X(kr2hcII_register) (p, r2hcII_8, &desc);
}
