/*
 * mt64_r: reentrant version of MT19937-64
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt64_r_init.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt64_r_internal.h"

/*======================================================================*/
void mt64_r_init(mt64_context_t *context, unsigned long s)
#if MT64_R_COK_KERNEL	== 1
{				/* initializes mt[N] with a seed.       */
    register uint64_t j, jm1, *state;

    state    = context->state;
    state[0] = s;

    for (jm1 = 0, j = 1; j < MT64_R_NN; j = (jm1 = j) + 1)
	state[j] = (UINT64_C(6364136223846793005) * (state[jm1] ^ (state[jm1] >> 62)) + j);

    context->left  = 1;
    context->initf = true;

    return;
}
#else				/*......................................*/
{				/* initializes mt[N] with a seed.       */
    register uint32_t mti, mti1;
    register uint64_t *mt;

    mt    = context->mt;
    mt[0] = s;

    for (mti = 1; mti < MT64_R_NN; mti++) {
	mti1    = mti - 1;
	mt[mti] = UINT64_C(6364136223846793005) * (mt[mti1] ^ (mt[mti1] >> 62)) + mti;
    }

    context->mti = MT64_R_NN;

    return;
}
#endif
