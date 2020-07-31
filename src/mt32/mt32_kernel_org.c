/*
 * mt32: MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_kernel_org.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdlib.h>
#include "mt32_internal.h"

/* constants       */
#define MT32_NN			624
#define MT32_MM			397
#define MT32_MATRIX_A		UINT32_C(0x9908b0df)	/* constant vector A          */
#define MT32_UM			UINT32_C(0x80000000)	/* most  significant w-r bits */
#define MT32_LM			UINT32_C(0x7fffffff)	/* least significant   r bits */
#define MT32_RM			UINT32_C(0xffffffff)	/* for WORDSIZE > 32bit       */
#define MT32_UNINITIALIZED	(MT32_NN+1)		/* not initialized yet        */

/* internal status */
static uint32_t mt[MT32_NN],	/* the state vector */
		mti = MT32_UNINITIALIZED;

/*======================================================================*/
void mt32_init(uint32_t s)
{				/* initializes mt[N] with a seed.       */
    register uint32_t mti1;

    mt[0]  = s;
#if UINT32_MAX > MT32_RM
    mt[0] &= MT32_RM;	/* for WORDSIZE > 32bit */
#endif

    for (mti1 = 0, mti = 1; mti < MT32_NN; mti = (mti1 = mti) + 1) {
	mt[mti] = UINT32_C(1812433253) * (mt[mti1] ^ (mt[mti1] >> 30)) + mti;
/*  See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
 *  In the previous versions, MSBs of the seed affect
 *  only MSBs of the array mt[].
 *  2002/01/09 modified by Makoto Matsumoto
 */
#if UINT32_MAX > MT32_RM
	mt[mti] &= MT32_RM;	/* for WORDSIZE > 32bit */
#endif
    }

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
	mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * UINT32_C(1664525))) + init_key[j] + j;	/* non linear */
#if UINT32_MAX > MT32_RM
	mt[i] &= MT32_RM;	/* for WORDSIZE > 32bit */
#endif
	if (++i >= MT32_NN) {
	    mt[0] = mt[MT32_NN - 1];
	    i     = 1;
	}
	if (++j >= key_length)
	    j = 0;
    }
    for (k = MT32_NN - 1; k > 0; k--) {
	mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 30)) * UINT32_C(1566083941))) - i;			/* non linear */
#if UINT32_MAX > MT32_RM
	mt[i] &= MT32_RM;	/* for WORDSIZE > 32bit */
#endif
	if (++i >= MT32_NN) {
	    mt[0] = mt[MT32_NN - 1];
	    i     = 1;
	}
    }

    mt[0] = UINT32_C(0x01) << 31;	/* MSB is 1; assuring non-zero initial array. */

    return;
}

/*----------------------------------------------------------------------*/
uint32_t mt32_genrand_int32(void)
{				/* generate a random number in [0:2^32-1].*/
    static   uint32_t mag01[2] = { UINT32_C(0), MT32_MATRIX_A };	/* mag01[i] = i * MATRIX_A */
    register uint32_t y, kk;

    if (mti >= MT32_NN) {	/* generate MT32_NN words at one time. */
	if (mti >= MT32_UNINITIALIZED)
	    mt32_init(5489);	/* default initial seed is used.       */
	for (kk = 0; kk < MT32_NN - MT32_MM; kk++) {
	    y      = (mt[kk] & MT32_UM) | (mt[kk + 1] & MT32_LM);
	    mt[kk] =  mt[kk  + MT32_MM] ^ (y >> 1) ^ mag01[y & 0x1];
	}
	for (; kk < MT32_NN - 1; kk++) {
	    y      = (mt[kk] & MT32_UM) | (mt[kk + 1] & MT32_LM);
	    mt[kk] =  mt[kk + (MT32_MM - MT32_NN)] ^ (y >> 1) ^ mag01[y & 0x1];
	}
	y                 = (mt[MT32_NN - 1] & MT32_UM) | (mt[0] & MT32_LM);
	mt[MT32_NN - 1]   =  mt[MT32_MM - 1] ^ (y >> 1) ^ mag01[y & 0x1];
	mti               = 0;
    }

    y  = mt[mti++];
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
    if (fread(&mti, sizeof(mti  ), 1      , fp) != 1 ||
	fread( mt , sizeof(mt[0]), MT32_NN, fp) != MT32_NN)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
int mt32_save_state_fp(FILE *fp)
{				/* write out current status to the restart file.*/
    if (fwrite(&mti, sizeof(mti  ), 1      , fp) != 1       ||
	fwrite( mt , sizeof(mt[0]), MT32_NN, fp) != MT32_NN ||
	fflush(fp) != 0)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
