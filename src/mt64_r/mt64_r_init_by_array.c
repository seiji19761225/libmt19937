/*
 * mt64_r: reentrant version of MT19937-64
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt64_r_init_by_array.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt64_r_internal.h"

/*======================================================================*/
void mt64_r_init_by_array(mt64_context_t *context, uint64_t *init_key, size_t key_length)
#if MT64_R_COK_KERNEL == 1
{				/* initialize by an array.              */
/* init_key is the array for initializing keys
 * key_length is its length
 */
    register uint64_t i = 1, j = 0, k, *state;

    mt64_r_init(context, UINT64_C(19650218));

    state = context->state;

    for (k = (MT64_R_NN > key_length) ? MT64_R_NN : key_length; k > 0; k--) {
	state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 62)) * UINT64_C(3935559000370003845))) + init_key[j] + j;	/* non linear */
	if (++i >= MT64_R_NN) {
	    state[0] = state[MT64_R_NN - 1];
	    i        = 1;
	}
	if (++j >= key_length)
	    j = 0;
    }
    for (k = MT64_R_NN - 1; k > 0; k--) {
	state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 62)) * UINT64_C(2862933555777941757))) - i;			/* non linear */
	if (++i >= MT64_R_NN) {
	    state[0] = state[MT64_R_NN - 1];
	    i        = 1;
	}
    }

    state[0]       = UINT64_C(0x01) << 63;	/* MSB is 1; assuring non-zero initial array. */
    context->left  = 1;
    context->initf = true;

    return;
}
#else				/*......................................*/
{				/* initialize by an array.              */
/* init_key is the array for initializing keys
 * key_length is its length
 */
    register uint32_t i = 1, j = 0, k;
    register uint64_t *mt;

    mt64_r_init(context, UINT64_C(19650218));

    mt = context->mt;

    for (k = (MT64_R_NN > key_length) ? MT64_R_NN : key_length; k > 0; k--) {
	mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 62)) * UINT64_C(3935559000370003845))) + init_key[j] + j;	/* non linear */
	if (++i >= MT64_R_NN) {
	    mt[0] = mt[MT64_R_NN - 1];
	    i     = 1;
	}
	if (++j >= key_length)
	    j = 0;
    }
    for (k = MT64_R_NN - 1; k > 0; k--) {
	mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 62)) * UINT64_C(2862933555777941757))) - i;		/* non linear */
	if (++i >= MT64_R_NN) {
	    mt[0] = mt[MT64_R_NN - 1];
	    i     = 1;
	}
    }

    mt[0] = UINT64_C(0x01) << 63;	/* MSB is 1; assuring non-zero initial array */

    return;
}
#endif
