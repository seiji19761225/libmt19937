/*
 * mt32_r: reentrant version of MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_r_genrand_int32.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt32_r_internal.h"

/*======================================================================*/
uint32_t mt32_r_genrand_int32(mt32_context_t *context)
#if MT32_R_COK_KERNEL == 1
{				/* generate a random number in [0:2^32-1].*/
    register uint32_t y;

    if (--context->left == 0)	/* update the state vector */
	_mt32_r_next_state(context);

    y  = *context->next++;

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y <<  7) & UINT32_C(0x9d2c5680);
    y ^= (y << 15) & UINT32_C(0xefc60000);
    y ^= (y >> 18);

    return y;
}
#else				/*......................................*/
{				/* generate a random number in [0:2^32-1].*/
    static   uint32_t mag01[2] = { UINT32_C(0), MT32_R_MATRIX_A };	/* mag01[i] = i * MATRIX_A */
    register uint32_t y, kk, mti, *mt;

    mti = context->mti;
    mt  = context->mt ;

    if (mti >= MT32_R_NN) {	/* generate MT32_R_NN words at one time. */
	if (mti >= MT32_R_UNINITIALIZED)
	    mt32_r_init(context, 5489);	/* default initial seed is used. */
	for (kk = 0; kk < MT32_R_NN - MT32_R_MM; kk++) {
	    y      = (mt[kk] & MT32_R_UM) | (mt[kk + 1] & MT32_R_LM);
	    mt[kk] =  mt[kk  + MT32_R_MM] ^ (y >> 1) ^ mag01[y & 0x1];
	}
	for (; kk < MT32_R_NN - 1; kk++) {
	    y      = (mt[kk] & MT32_R_UM) | (mt[kk + 1] & MT32_R_LM);
	    mt[kk] =  mt[kk + (MT32_R_MM - MT32_R_NN)] ^ (y >> 1) ^ mag01[y & 0x1];
	}
	y                 = (mt[MT32_R_NN - 1] & MT32_R_UM) | (mt[0] & MT32_R_LM);
	mt[MT32_R_NN - 1] =  mt[MT32_R_MM - 1] ^ (y >> 1) ^ mag01[y & 0x1];
	mti               = 0;
    }

    y  = mt[mti++];
    /* Tempering */
    y ^= (y >> 11);
    y ^= (y <<  7) & UINT32_C(0x9d2c5680);
    y ^= (y << 15) & UINT32_C(0xefc60000);
    y ^= (y >> 18);

    context->mti = mti;

    return y;
}
#endif
