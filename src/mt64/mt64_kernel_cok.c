/*
 * mt64: MT19937-64 (with Shawn Cokus's optimization and Matthe Bellew's simplification)
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt64_kernel_cok.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdlib.h>
#include <stdbool.h>
#include "mt64_internal.h"

/* constants       */
#define MT64_NN			312
#define MT64_MM			156
#define MT64_MATRIX_A		UINT64_C(0xB5026F5AA96619E9)	/* constant vector A         */
#define MT64_UM			UINT64_C(0xFFFFFFFF80000000)	/* most  significant 33 bits */
#define MT64_LM			UINT64_C(0x000000007FFFFFFF)	/* least significant 31 bits */

/* macro functions */
#define MIXBITS(u,v)		(((u)&MT64_UM)|((v)&MT64_LM))
#define TWIST(u,v)		((MIXBITS(u,v)>>0x01)^(((v)&0x01)?MT64_MATRIX_A:0x00))

/* internal status */
static uint64_t *next = NULL, state[MT64_NN];	/* the state vector */
static uint32_t left  = 1;
static bool initf = false;

/* prototype       */
static void _mt64_next_state(void);

/*======================================================================*/
void mt64_init(uint64_t s)
{				/* initializes mt[N] with a seed.       */
    register uint64_t j, jm1;

    state[0]  = s;

    for (jm1 = 0, j = 1; j < MT64_NN; j = (jm1 = j) + 1)
	state[j] = (UINT64_C(6364136223846793005) * (state[jm1] ^ (state[jm1] >> 62)) + j);

    left  = 1;
    initf = true;

    return;
}

/*----------------------------------------------------------------------*/
void mt64_init_by_array(uint64_t *init_key, size_t key_length)
{				/* initialize by an array.              */
/* init_key is the array for initializing keys
 * key_length is its length
 */
    register uint64_t i = 1, j = 0, k;

    mt64_init(UINT64_C(19650218));

    for (k = (MT64_NN > key_length) ? MT64_NN : key_length; k > 0; k--) {
	state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 62)) * UINT64_C(3935559000370003845))) + init_key[j] + j;	/* non linear */
	if (++i >= MT64_NN) {
	    state[0] = state[MT64_NN - 1];
	    i        = 1;
	}
	if (++j >= key_length)
	    j = 0;
    }
    for (k = MT64_NN - 1; k > 0; k--) {
	state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 62)) * UINT64_C(2862933555777941757))) - i;			/* non linear */
	if (++i >= MT64_NN) {
	    state[0] = state[MT64_NN - 1];
	    i        = 1;
	}
    }

    state[0] = UINT64_C(0x01) << 63;	/* MSB is 1; assuring non-zero initial array. */
    left     = 1;
    initf    = true;

    return;
}

/*----------------------------------------------------------------------*/
uint64_t mt64_genrand_int64(void)
{				/* generate a random number in [0:2^64-1].*/
    register uint64_t y;

    if (--left == 0)	/* update the state vector */
	_mt64_next_state();

    y  = *next++;

    /* Tempering */
    y ^= (y >> 29) & UINT64_C(0x5555555555555555);
    y ^= (y << 17) & UINT64_C(0x71D67FFFEDA60000);
    y ^= (y << 37) & UINT64_C(0xFFF7EEE000000000);
    y ^= (y >> 43);

    return y;
}

/*----------------------------------------------------------------------*/
int mt64_load_state_fp(FILE *fp)
{				/* load a status from the restart file. */
    if (fread(&left, sizeof(left    ), 1      , fp) != 1 ||
	fread(state, sizeof(state[0]), MT64_NN, fp) != MT64_NN)
	return EXIT_FAILURE;

    next  = state + MT64_NN - left + 1;
    initf = true;

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
int mt64_save_state_fp(FILE *fp)
{				/* write out current status to the restart file.*/
    if (fwrite(&left, sizeof(left    ), 1      , fp) != 1       ||
	fwrite(state, sizeof(state[0]), MT64_NN, fp) != MT64_NN ||
	fflush(fp) != 0)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
static void _mt64_next_state(void)
{
    register uint64_t j, *p = state;

    /* if mt64_init() has not been called,
     * a default initial seed is used
     */
    if (!initf)
	mt64_init(UINT64_C(5489));

    left = MT64_NN;
    next = p;	/* == state */

    for (j = MT64_NN - MT64_MM; j > 0; j--, p++)
	*p = p[MT64_MM] ^ TWIST(p[0], p[1]);

    for (j = MT64_MM - 1; j > 0; j--, p++)
	*p = p[MT64_MM - MT64_NN] ^ TWIST(p[0], p[1]);

    *p = p[MT64_MM - MT64_NN] ^ TWIST(p[0], state[0]);

    return;
}
