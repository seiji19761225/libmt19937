/*
 * mt64: MT19937-64
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt64_kernel_org.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdlib.h>
#include "mt64_internal.h"

/* constants       */
#define MT64_NN			312
#define MT64_MM			156
#define MT64_MATRIX_A		UINT64_C(0xB5026F5AA96619E9)	/* constant vector A         */
#define MT64_UM			UINT64_C(0xFFFFFFFF80000000)	/* most  significant 33 bits */
#define MT64_LM			UINT64_C(0x000000007FFFFFFF)	/* least significant 31 bits */
#define MT64_UNINITIALIZED	(MT64_NN+1)			/* not initialized yet       */

/* internal status */
static uint32_t mti = MT64_UNINITIALIZED;
static uint64_t mt[MT64_NN];	/* the state vector */

/*======================================================================*/
void mt64_init(uint64_t s)
{				/* initializes mt[N] with a seed.       */
    register uint32_t mti1;

    mt[0] = s;

    for (mti1 = 0, mti = 1; mti < MT64_NN; mti = (mti1 = mti) + 1)
	mt[mti] = UINT64_C(6364136223846793005) * (mt[mti1] ^ (mt[mti1] >> 62)) + mti;

    return;
}

/*----------------------------------------------------------------------*/
void mt64_init_by_array(uint64_t *init_key, size_t key_length)
{				/* initialize by an array.              */
/* init_key is the array for initializing keys
 * key_length is its length
 */
    register uint32_t i = 1, j = 0, k;

    mt64_init(UINT64_C(19650218));

    for (k = (MT64_NN > key_length) ? MT64_NN : key_length; k > 0; k--) {
	mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 62)) * UINT64_C(3935559000370003845))) + init_key[j] + j;	/* non linear */
	if (++i >= MT64_NN) {
	    mt[0] = mt[MT64_NN - 1];
	    i     = 1;
	}
	if (++j >= key_length)
	    j = 0;
    }
    for (k = MT64_NN - 1; k > 0; k--) {
	mt[i] = (mt[i] ^ ((mt[i - 1] ^ (mt[i - 1] >> 62)) * UINT64_C(2862933555777941757))) - i;		/* non linear */
	if (++i >= MT64_NN) {
	    mt[0] = mt[MT64_NN - 1];
	    i     = 1;
	}
    }

    mt[0] = UINT64_C(0x01) << 63;	/* MSB is 1; assuring non-zero initial array */

    return;
}

/*----------------------------------------------------------------------*/
uint64_t mt64_genrand_int64(void)
{				/* generate a random number in [0:2^64-1].*/
    static   uint64_t mag01[2] = { UINT64_C(0), MT64_MATRIX_A };
    register uint64_t x;
    register uint32_t i;

    if (mti >= MT64_NN) {	/* generate MT64_NN words at one time. */
	if (mti >= MT64_UNINITIALIZED)
	    mt64_init(5489);	/* default initial seed is used.       */
	for (i = 0; i < MT64_NN - MT64_MM; i++) {
	    x     = (mt[i] & MT64_UM) | (mt[i + 1] & MT64_LM);
	    mt[i] =  mt[i  + MT64_MM] ^ (x >> 1) ^ mag01[x & 0x1];
	}
	for (; i < MT64_NN - 1; i++) {
	    x     = (mt[i] & MT64_UM) | (mt[i + 1] & MT64_LM);
	    mt[i] =  mt[i + (MT64_MM - MT64_NN)] ^ (x >> 1) ^ mag01[x & 0x1];
	}
	x               = (mt[MT64_NN - 1] & MT64_UM) | (mt[0] & MT64_LM);
	mt[MT64_NN - 1] =  mt[MT64_MM - 1] ^ (x >> 1) ^ mag01[x & 0x1];
	mti             = 0;
    }

    x  = mt[mti++];
    /* Tempering */
    x ^= (x >> 29) & UINT64_C(0x5555555555555555);
    x ^= (x << 17) & UINT64_C(0x71D67FFFEDA60000);
    x ^= (x << 37) & UINT64_C(0xFFF7EEE000000000);
    x ^= (x >> 43);

    return x;
}

/*----------------------------------------------------------------------*/
int mt64_load_state_fp(FILE *fp)
{				/* load a status from the restart file. */
    if (fread(&mti, sizeof(mti  ), 1      , fp) != 1 ||
	fread( mt , sizeof(mt[0]), MT64_NN, fp) != MT64_NN)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}

/*----------------------------------------------------------------------*/
int mt64_save_state_fp(FILE *fp)
{				/* write out current status to the restart file.*/
    if (fwrite(&mti, sizeof(mti  ), 1      , fp) != 1       ||
	fwrite( mt , sizeof(mt[0]), MT64_NN, fp) != MT64_NN ||
	fflush(fp) != 0)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
