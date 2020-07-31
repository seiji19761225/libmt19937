/*
 * mt32: MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt19937ar.h,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */
/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

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
   A PARTICAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
 */

#ifndef __MT19937AR_H__
#define __MT19937AR_H__

#include <libmt19937/mt32.h>

/* macros for backward compatibility -----------------------------------*/
#define init_genrand		mt32_init
#define init_by_array		mt32_init_by_array
#define genrand_int32		mt32_genrand_int32
#define genrand_int31		mt32_genrand_int31
#define genrand_real1		mt32_genrand_real1
#define genrand_real2		mt32_genrand_real2
#define genrand_real3		mt32_genrand_real3
#define genrand_res53		mt32_genrand_res53
/*
#define genrand_exp		mt32_genrand_exp
#define genrand_gamma		mt32_genrand_gamma
#define genrand_geometric	mt32_genrand_geometric
#define genrand_normal		mt32_genrand_normal
#define genrand_poisson		mt32_genrand_poisson
#define load_state_genrand	mt32_load_state
#define load_state_genrand_fp	mt32_load_state_fp
#define save_state_genrand	mt32_save_state
#define save_state_genrand_fp	mt32_save_state_fp
 */

#endif
