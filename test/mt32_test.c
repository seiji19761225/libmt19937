/*
 * mt32: MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_test.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */
/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
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


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <libmt19937/mt32.h>

/* checkpoint/restart file name */
#define CPR_FILE	"mt32_test.dmp"

/*======================================================================*/
int main(void)
{
    int i;
    uint32_t init[] = {
	UINT32_C(0x123), UINT32_C(0x234),
	UINT32_C(0x345), UINT32_C(0x456)
    };

    mt32_init_by_array(init, sizeof(init) / sizeof(init[0]));

    printf("1000 outputs of mt32_genrand_int32()\n");

    for (i = 0; i < 1000; i++) {
	printf("%10u ", mt32_genrand_int32());
	if (i % 5 == 4)
	    printf("\n");
    }

    if (mt32_save_state(CPR_FILE) == EXIT_FAILURE ||
	mt32_load_state(CPR_FILE) == EXIT_FAILURE) {
	perror(CPR_FILE);
	return EXIT_FAILURE;
    }

    printf("\n1000 outputs of mt32_genrand_real2()\n");

    for (i = 0; i < 1000; i++) {
	printf("%10.8f ", mt32_genrand_real2());
	if (i % 5 == 4)
	    printf("\n");
    }

    return EXIT_SUCCESS;
}
