/*
 * mt64_r: reentrant version of MT19937-64
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt64_r.h.tpl,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
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

#ifndef __MT64_R_H__
#define __MT64_R_H__

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

/* constant ------------------------------------------------------------*/
#define MT64_R_COK_KERNEL	__COK_KERNEL__
#define MT64_R_NN		312

/* MT19937ar context data type -----------------------------------------*/
typedef struct {
#if MT64_R_COK_KERNEL == 1
    bool initf;
    uint32_t left;
    uint64_t *next, state[MT64_R_NN];	/* the state vector */
#else
    uint32_t mti;
    uint64_t mt[MT64_R_NN];		/* the state vector */
#endif
} mt64_context_t;

#if MT64_R_COK_KERNEL == 1
#define MT64_CONTEXT_INITIALIZER	((mt64_context_t) {.initf=false,.left=1})
#else
#define MT64_R_UNINITIALIZED		(MT64_R_NN+1)
#define MT64_CONTEXT_INITIALIZER	((mt64_context_t) {.mti=MT64_R_UNINITIALIZED})
#endif

/* prototypes ----------------------------------------------------------*/

#ifndef __MT64_R_INTERNAL__
#define   MT64_R_API
#else
#define   MT64_R_API	extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

MT64_R_API void     mt64_r_init             (mt64_context_t *, uint64_t);
MT64_R_API void     mt64_r_init_by_array    (mt64_context_t *, uint64_t *, size_t);
MT64_R_API uint64_t mt64_r_genrand_int64    (mt64_context_t *);
MT64_R_API int64_t  mt64_r_genrand_int63    (mt64_context_t *);
MT64_R_API double   mt64_r_genrand_real1    (mt64_context_t *);
MT64_R_API double   mt64_r_genrand_real2    (mt64_context_t *);
MT64_R_API double   mt64_r_genrand_real3    (mt64_context_t *);
/* These distributed functions are written by Pascal Getreuer ----------*/
MT64_R_API double   mt64_r_genrand_exp      (mt64_context_t *, double);
MT64_R_API double   mt64_r_genrand_gamma    (mt64_context_t *, double, double);
MT64_R_API double   mt64_r_genrand_geometric(mt64_context_t *, double);
MT64_R_API double   mt64_r_genrand_normal   (mt64_context_t *);
MT64_R_API double   mt64_r_genrand_poisson  (mt64_context_t *, double);
/* These checkpoint/restart are written by Seiji Nishimura -------------*/
MT64_R_API int      mt64_r_save_context     (mt64_context_t *, const char *);
MT64_R_API int      mt64_r_load_context     (mt64_context_t *, const char *);
MT64_R_API int      mt64_r_save_context_fp  (mt64_context_t *, FILE *);
MT64_R_API int      mt64_r_load_context_fp  (mt64_context_t *, FILE *);

#ifdef __cplusplus
}
#endif

#undef    MT64_R_API
#endif
