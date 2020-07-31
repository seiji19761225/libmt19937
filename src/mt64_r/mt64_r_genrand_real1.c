/*
 * mt64_r: reentrant version of MT19937-64
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt64_r_genrand_real1.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt64_r_internal.h"

/*======================================================================*/
double mt64_r_genrand_real1(mt64_context_t *context)
#ifdef USE_INLINED_GENERATOR
#if MT64_R_COK_KERNEL == 1
{				/* generates a random number in [0:1].  */
    register uint64_t y;

    if (--context->left == 0)	/* update the state vector */
	_mt64_r_next_state(context);

    y  = *context->next++;

    /* Tempering */
    y ^= (y >> 29) & UINT64_C(0x5555555555555555);
    y ^= (y << 17) & UINT64_C(0x71D67FFFEDA60000);
    y ^= (y << 37) & UINT64_C(0xFFF7EEE000000000);
    y ^= (y >> 43);

    return (double) (y >> 11) / 9007199254740991.0;
}
#else				/*......................................*/
{				/* generates a random number in [0:1].  */
    static   uint64_t mag01[2] = { UINT64_C(0), MT64_R_MATRIX_A };
    register uint64_t *mt, x;
    register uint32_t mti, i;

    mti = context->mti;
    mt  = context->mt ;

    if (mti >= MT64_R_NN) {	/* generate MT64_R_NN words at one time. */
	if (mti >= MT64_R_UNINITIALIZED)
	    mt64_r_init(context, 5489);	/* default initial seed is used. */
	for (i = 0; i < MT64_R_NN - MT64_R_MM; i++) {
	    x     = (mt[i] & MT64_R_UM) | (mt[i + 1] & MT64_R_LM);
	    mt[i] =  mt[i  + MT64_R_MM] ^ (x >> 1) ^ mag01[x & 0x1];
	}
	for (; i < MT64_R_NN - 1; i++) {
	    x     = (mt[i] & MT64_R_UM) | (mt[i + 1] & MT64_R_LM);
	    mt[i] =  mt[i + (MT64_R_MM - MT64_R_NN)] ^ (x >> 1) ^ mag01[x & 0x1];
	}
	x                 = (mt[MT64_R_NN - 1] & MT64_R_UM) | (mt[0] & MT64_R_LM);
	mt[MT64_R_NN - 1] =  mt[MT64_R_MM - 1] ^ (x >> 1) ^ mag01[x & 0x1];
	mti               = 0;
    }

    x  = mt[mti++];
    /* Tempering */
    x ^= (x >> 29) & UINT64_C(0x5555555555555555);
    x ^= (x << 17) & UINT64_C(0x71D67FFFEDA60000);
    x ^= (x << 37) & UINT64_C(0xFFF7EEE000000000);
    x ^= (x >> 43);

    context->mti = mti;

    return (double) (x >> 11) / 9007199254740991.0;
}
#endif
#else				/*......................................*/
{				/* generates a random number in [0:1].  */
    return (double) (mt64_r_genrand_int64(context) >> 11) / 9007199254740991.0;
}
#endif
