/*
 * mt64: MT19937-64
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt19937-64.h,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */
/* 
   A C-program for MT19937-64 (2004/9/29 version).
   Coded by Takuji Nishimura and Makoto Matsumoto.

   This is a 64-bit version of Mersenne Twister pseudorandom number
   generator.

   Before using, initialize the state by using init_genrand64(seed)  
   or init_by_array64(init_key, key_length).

   Copyright (C) 1997-2002,2004 Makoto Matsumoto and Takuji Nishimura,
   Copyright (C) 2011 Pascal Getreuer,
   Copyright (C) 2008,2014-2015 Seiji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

   References:
   T. Nishimura, ``Tables of 64-bit Mersenne Twisters''
     ACM Transactions on Modeling and 
     Computer Simulation 10. (2000) 348--357.
   M. Matsumoto and T. Nishimura,
     ``Mersenne Twister: a 623-dimensionally equidistributed
       uniform pseudorandom number generator''
     ACM Transactions on Modeling and 
     Computer Simulation 8. (Jan. 1998) 3--30.

   Any feedback is very welcome.
   http://www.math.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove spaces)
 */

#ifndef __MT19937_64_H__
#define __MT19937_64_H__

#include <libmt19937/mt64.h>

/* macros for backward compatibility -----------------------------------*/
#define init_genrand64		mt64_init
#define init_by_array64		mt64_init_by_array
#define genrand64_int64		mt64_genrand_int64
#define genrand64_int63		mt64_genrand_int63
#define genrand64_real1		mt64_genrand_real1
#define genrand64_real2		mt64_genrand_real2
#define genrand64_real3		mt64_genrand_real3
/*
#define genrand64_exp		mt64_genrand_exp
#define genrand64_gamma		mt64_genrand_gamma
#define genrand64_geometric	mt64_genrand_geometric
#define genrand64_normal	mt64_genrand_normal
#define genrand64_poisson	mt64_genrand_poisson
#define load_state_genrand64	mt64_load_state
#define load_state_genrand64_fp	mt64_load_state_fp
#define save_state_genrand64	mt64_save_state
#define save_state_genrand64_fp	mt64_save_state_fp
 */

#endif
