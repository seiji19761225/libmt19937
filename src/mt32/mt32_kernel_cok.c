/*
 * mt32: MT19937ar (with Shawn Cokus's optimization and Matthe Bellew's simplification)
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_kernel_cok.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdlib.h>
#include <stdbool.h>
#include "mt32_internal.h"

/* constants       */
#define MT32_NN			624
#define MT32_MM			397
#define MT32_MATRIX_A		UINT32_C(0x9908b0df)	/* constant vector A          */
#define MT32_UM			UINT32_C(0x80000000)	/* most  significant w-r bits */
#define MT32_LM			UINT32_C(0x7fffffff)	/* least significant   r bits */
#define MT32_RM			UINT32_C(0xffffffff)	/* for WORDSIZE > 32bit       */

/* macro functions */
#define MIXBITS(u,v)		(((u)&MT32_UM)|((v)&MT32_LM))
#define TWIST(u,v)		((MIXBITS(u,v)>>0x01)^(((v)&0x01)?MT32_MATRIX_A:0x00))

/* internal status */
static uint32_t state[MT32_NN];	/* the state vector */
static uint32_t *next = NULL, left = 1;
static bool     initf = false;

/* prototype       */
static void _mt32_next_state(void);

/*======================================================================*/
void mt32_init(uint32_t s)
{				/* initializes state[N] with a seed.    */
    register uint32_t j, jm1;

    state[0]  = s;
#if UINT32_MAX > MT32_RM
    state[0] &= MT32_RM;	/* for WORDSIZE > 32bit */
#endif

    for (jm1 = 0, j = 1; j < MT32_NN; j = (jm1 = j) + 1) {
	state[j] = (UINT32_C(1812433253) * (state[jm1] ^ (state[jm1] >> 30)) + j);
/*  See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
 *  In the previous versions, MSBs of the seed affect
 *  only MSBs of the array state[].
 *  2002/01/09 modified by Makoto Matsumoto
 */
#if UINT32_MAX > MT32_RM
	state[j] &= MT32_RM;	/* for WORDSIZE > 32bit */
#endif
    }

    left  = 1;
    initf = true;

    return;
}

/*----------------------------------------------------------------------*/
void mt32_init_by_array(uint32_t *init_key, size_t key_length)
{				/* initialize by an array.              */
/* init_key is the array for initializing keys
 * key_length is its length
 * slight change for C++, 2004/2/26
 */
    register uint32_t i = 1, j = 0, k;

    mt32_init(UINT32_C(19650218));

    for (k = (MT32_NN > key_length) ? MT32_NN : key_length; k > 0; k--) {
	state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * UINT32_C(1664525))) + init_key[j] + j;	/* non linear */
#if UINT32_MAX > MT32_RM
	state[i] &= MT32_RM;	/* for WORDSIZE > 32bit */
#endif
	if (++i >= MT32_NN) {
	    state[0] = state[MT32_NN - 1];
	    i        = 1;
	}
	if (++j >= key_length)
	    j = 0;
    }
    for (k = MT32_NN - 1; k > 0; k--) {
	state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * UINT32_C(1566083941))) - i;			/* non linear */
#if UINT32_MAX > MT32_RM
	state[i] &= MT32_RM;	/* for WORDSIZE > 32bit */
#endif
	if (++i >= MT32_NN) {
	    state[0] = state[MT32_NN - 1];
	    i        = 1;
	}
    }

    state[0] = UINT32_C(0x01) << 31;	/* MSB is 1; assuring non-zero initial array. */
    left     = 1;
    initf    = true;

    return;
}

/*----------------------------------------------------------------------*/
uint32_t mt32_genrand_int32(void)
{				/* generate a random number in [0:2^32-1].*/
    register uint32_t y;

    if (--left == 0)	/* update the state vector */
	_mt32_next_state();

    y  = *next++;

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y <<  7) & UINT32_C(0x9d2c5680);
    y ^= (y << 15) & UINT32_C(0xefc60000);
    y ^= (y >> 18);

    return y;
}

/*----------------------------------------------------------------------*/
int mt32_load_state_fp(FILE *fp)
{				/* load a status from the restart file. */
    if (fread(&left, sizeof(left    ), 1      , fp) != 1 ||
	fread(state, sizeof(state[0]), MT32_NN, fp) != MT32_NN)
	return EXIT_FAILURE;

    next  = state + MT32_NN - left + 1;
    initf = true;

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
int mt32_save_state_fp(FILE *fp)
{				/* write out current status to the restart file.*/
    if (fwrite(&left, sizeof(left    ), 1      , fp) != 1       ||
	fwrite(state, sizeof(state[0]), MT32_NN, fp) != MT32_NN ||
	fflush(fp) != 0)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
static void _mt32_next_state(void)
{
    register uint32_t j, *p = state;

    /* if mt32_init() has not been called,
     * a default initial seed is used
     */
    if (!initf)
	mt32_init(UINT32_C(5489));

    left = MT32_NN;
    next = p;	/* == state */

    for (j = MT32_NN - MT32_MM; j > 0; j--, p++)
	*p = p[MT32_MM] ^ TWIST(p[0], p[1]);

    for (j = MT32_MM - 1; j > 0; j--, p++)
	*p = p[MT32_MM - MT32_NN] ^ TWIST(p[0], p[1]);

    *p = p[MT32_MM - MT32_NN] ^ TWIST(p[0], state[0]);

    return;
}
