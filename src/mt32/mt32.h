/*
 * mt32: MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32.h,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
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

#ifndef __MT32_H__
#define __MT32_H__

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

/* prototypes ----------------------------------------------------------*/

#ifndef __MT32_INTERNAL__
#define   MT32_API
#else
#define   MT32_API	extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

MT32_API void     mt32_init             (uint32_t);
MT32_API void     mt32_init_by_array    (uint32_t *, size_t);
MT32_API uint32_t mt32_genrand_int32    (void);
/* These real versions are due to Isaku Wada, 2002/01/09 added ---------*/
MT32_API int32_t  mt32_genrand_int31    (void);
MT32_API double   mt32_genrand_real1    (void);
MT32_API double   mt32_genrand_real2    (void);
MT32_API double   mt32_genrand_real3    (void);
MT32_API double   mt32_genrand_res53    (void);
/* These distributed functions are written by Pascal Getreuer ----------*/
MT32_API double   mt32_genrand_exp      (double);
MT32_API double   mt32_genrand_gamma    (double, double);
MT32_API double   mt32_genrand_geometric(double);
MT32_API double   mt32_genrand_normal   (void);
MT32_API double   mt32_genrand_poisson  (double);
/* These checkpoint/restart are written by Seiji Nishimura -------------*/
MT32_API int      mt32_save_state       (const char *);
MT32_API int      mt32_load_state       (const char *);
MT32_API int      mt32_save_state_fp    (FILE *);
MT32_API int      mt32_load_state_fp    (FILE *);

#ifdef __cplusplus
}
#endif

#undef    MT32_API
#endif
