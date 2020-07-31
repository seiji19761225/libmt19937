/*
 * mt32_r: reentrant version of MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_r_genrand_res53.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt32_r_internal.h"

/*======================================================================*/
double mt32_r_genrand_res53(mt32_context_t *context)
#ifdef USE_INLINED_GENERATOR
#if MT32_R_COK_KERNEL == 1
{				/* generate a random number in [0:1) with 53-bit resolution.*/
    register uint32_t a, b;

    if (--context->left == 0)	/* update the state vector */
	_mt32_r_next_state(context);

    a  = *context->next++;

    /* Tempering */
    a  ^= (a >> 11);
    a  ^= (a <<  7) & UINT32_C(0x9d2c5680);
    a  ^= (a << 15) & UINT32_C(0xefc60000);
    a  ^= (a >> 18);
    a >>= 0x05;

    if (--context->left == 0)	/* update the state vector */
	_mt32_r_next_state(context);

    b  = *context->next++;

    /* Tempering */
    b  ^= (b >> 11);
    b  ^= (b <<  7) & UINT32_C(0x9d2c5680);
    b  ^= (b << 15) & UINT32_C(0xefc60000);
    b  ^= (b >> 18);
    b >>= 0x06;

    return ((double) a * 67108864.0 + b) / 9007199254740992.0;
}
#else				/*......................................*/
{				/* generate a random number in [0:1) with 53-bit resolution.*/
    static   uint32_t mag01[2] = { UINT32_C(0), MT32_R_MATRIX_A };	/* mag01[i] = i * MATRIX_A */
    register uint32_t a, b, kk, mti, *mt;

    mti = context->mti;
    mt  = context->mt ;

    if (mti >= MT32_R_NN) {	/* generate MT32_R_NN words at one time. */
	if (mti >= MT32_R_UNINITIALIZED)
	    mt32_r_init(context, 5489);	/* default initial seed is used. */
	for (kk = 0; kk < MT32_R_NN - MT32_R_MM; kk++) {
	    a      = (mt[kk] & MT32_R_UM) | (mt[kk + 1] & MT32_R_LM);
	    mt[kk] =  mt[kk  + MT32_R_MM] ^ (a >> 1) ^ mag01[a & 0x1];
	}
	for (; kk < MT32_R_NN - 1; kk++) {
	    a      = (mt[kk] & MT32_R_UM) | (mt[kk + 1] & MT32_R_LM);
	    mt[kk] =  mt[kk + (MT32_R_MM - MT32_R_NN)] ^ (a >> 1) ^ mag01[a & 0x1];
	}
	a                 = (mt[MT32_R_NN - 1] & MT32_R_UM) | (mt[0] & MT32_R_LM);
	mt[MT32_R_NN - 1] =  mt[MT32_R_MM - 1] ^ (a >> 1) ^ mag01[a & 0x1];
	mti               = 0;
    }

    a   = mt[mti++];
    /* Tempering */
    a  ^= (a >> 11);
    a  ^= (a <<  7) & UINT32_C(0x9d2c5680);
    a  ^= (a << 15) & UINT32_C(0xefc60000);
    a  ^= (a >> 18);
    a >>= 0x05;

    if (mti == MT32_R_NN) {	/* generate MT32_R_NN words at one time. */
	for (kk = 0; kk < MT32_R_NN - MT32_R_MM; kk++) {
	    b      = (mt[kk] & MT32_R_UM) | (mt[kk + 1] & MT32_R_LM);
	    mt[kk] =  mt[kk  + MT32_R_MM] ^ (b >> 1) ^ mag01[b & 0x1];
	}
	for (; kk < MT32_R_NN - 1; kk++) {
	    b      = (mt[kk] & MT32_R_UM) | (mt[kk + 1] & MT32_R_LM);
	    mt[kk] =  mt[kk + (MT32_R_MM - MT32_R_NN)] ^ (b >> 1) ^ mag01[b & 0x1];
	}
	b                 = (mt[MT32_R_NN - 1] & MT32_R_UM) | (mt[0] & MT32_R_LM);
	mt[MT32_R_NN - 1] =  mt[MT32_R_MM - 1] ^ (b >> 1) ^ mag01[b & 0x1];
	mti               = 0;
    }

    b   = mt[mti++];
    /* Tempering */
    b  ^= (b >> 11);
    b  ^= (b <<  7) & UINT32_C(0x9d2c5680);
    b  ^= (b << 15) & UINT32_C(0xefc60000);
    b  ^= (b >> 18);
    b >>= 0x06;

    context->mti = mti;

    return ((double) a * 67108864.0 + b) / 9007199254740992.0;
}
#endif
#else				/*......................................*/
{				/* generate a random number in [0:1) with 53-bit resolution.*/
    register uint32_t a, b;

    a = mt32_r_genrand_int32(context) >> 0x05,
    b = mt32_r_genrand_int32(context) >> 0x06;

    return ((double) a * 67108864.0 + b) / 9007199254740992.0;
}
#endif
