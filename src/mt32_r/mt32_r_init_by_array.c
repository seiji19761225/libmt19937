/*
 * mt32_r: reentrant version of MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_r_init_by_array.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt32_r_internal.h"

/*======================================================================*/
void mt32_r_init_by_array(mt32_context_t *context, uint32_t *init_key, size_t key_length)
#if MT32_R_COK_KERNEL == 1
{				/* initialize by an array.              */
/* init_key is the array for initializing keys
 * key_length is its length
 * slight change for C++, 2004/2/26
 */
    register uint32_t i = 1, j = 0, k, *state;

    mt32_r_init(context, UINT32_C(19650218));

    state = context->state;

    for (k = (MT32_R_NN > key_length) ? MT32_R_NN : key_length; k > 0; k--) {
	state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * UINT32_C(1664525))) + init_key[j] + j;	/* non linear */
#if UINT32_MAX > MT32_R_RM
	state[i] &= MT32_R_RM;	/* for WORDSIZE > 32bit */
#endif
	if (++i >= MT32_R_NN) {
	    state[0] = state[MT32_R_NN - 1];
	    i        = 1;
	}
	if (++j >= key_length)
	    j = 0;
    }
    for (k = MT32_R_NN - 1; k > 0; k--) {
	state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * UINT32_C(1566083941))) - i;			/* non linear */
#if UINT32_MAX > MT32_R_RM
	state[i] &= MT32_R_RM;	/* for WORDSIZE > 32bit */
#endif
	if (++i >= MT32_R_NN) {
	    state[0] = state[MT32_R_NN - 1];
	    i        = 1;
	}
    }

    state[0]       = UINT32_C(0x01) << 31;	/* MSB is 1; assuring non-zero initial array. */
    context->left  = 1;
    context->initf = true;

    return;
}
#else				/*......................................*/
{				/* initialize by an array.              */
/* init_key is the array for initializing keys
 * key_length is its length
 * slight change for C++, 2004/2/26
 */
    register uint32_t i = 1, j = 0, k, *mt;

    mt32_r_init(context, UINT32_C(19650218));

    mt = context->mt;

    for (k = (MT32_R_NN > key_length) ? MT32_R_NN : key_length; k > 0; k--) {
	mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * UINT32_C(1664525))) + init_key[j] + j;	/* non linear */
#if UINT32_MAX > MT32_R_RM
	mt[i] &= MT32_R_RM;	/* for WORDSIZE > 32bit */
#endif
	if (++i >= MT32_R_NN) {
	    mt[0] = mt[MT32_R_NN - 1];
	    i     = 1;
	}
	if (++j >= key_length)
	    j = 0;
    }
    for (k = MT32_R_NN - 1; k > 0; k--) {
	mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * UINT32_C(1566083941))) - i;			/* non linear */
#if UINT32_MAX > MT32_R_RM
	mt[i] &= MT32_R_RM;	/* for WORDSIZE > 32bit */
#endif
	if (++i >= MT32_R_NN) {
	    mt[0] = mt[MT32_R_NN - 1];
	    i     = 1;
	}
    }

    mt[0] = UINT32_C(0x01) << 31;	/* MSB is 1; assuring non-zero initial array. */

    return;
}
#endif
