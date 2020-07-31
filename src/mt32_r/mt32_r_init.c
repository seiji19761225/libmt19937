/*
 * mt32_r: reentrant version of MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_r_init.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt32_r_internal.h"

/*======================================================================*/
void mt32_r_init(mt32_context_t *context, uint32_t s)
#if MT32_R_COK_KERNEL == 1
{				/* initializes state[N] with a seed.    */
    register uint32_t j, jm1, *state;

    state     = context->state;
    state[0]  = s;
#if UINT32_MAX > MT32_R_RM
    state[0] &= MT32_R_RM;	/* for WORDSIZE > 32bit */
#endif

    for (jm1 = 0, j = 1; j < MT32_R_NN; j = (jm1 = j) + 1) {
	state[j] = (UINT32_C(1812433253) * (state[jm1] ^ (state[jm1] >> 30)) + j);
/*  See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
 *  In the previous versions, MSBs of the seed affect
 *  only MSBs of the array state[].
 *  2002/01/09 modified by Makoto Matsumoto
 */
#if UINT32_MAX > MT32_R_RM
	state[j] &= MT32_R_RM;	/* for WORDSIZE > 32bit */
#endif
    }

    context->left  = 1;
    context->initf = true;

    return;
}
#else				/*......................................*/
{				/* initializes mt[N] with a seed.       */
    register uint32_t mti, mti1, *mt;

    mt    = context->mt;
    mt[0] = s;

#if UINT32_MAX > MT32_R_RM
    mt[0] &= MT32_R_RM;	/* for WORDSIZE > 32bit */
#endif

    for (mti = 1; mti < MT32_R_NN; mti++) {
	mti1     = mti - 1;
	mt[mti]  = UINT32_C(1812433253) * (mt[mti1] ^ (mt[mti1] >> 30)) + mti;
/*  See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
 *  In the previous versions, MSBs of the seed affect
 *  only MSBs of the array mt[].
 *  2002/01/09 modified by Makoto Matsumoto
 */
#if UINT32_MAX > MT32_R_RM
	mt[mti] &= MT32_R_RM;	/* for WORDSIZE > 32bit */
#endif
    }

    context->mti = MT32_R_NN;

    return;
}
#endif
