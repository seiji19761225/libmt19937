/*
 * mt32: MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_genrand_res53.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt32_internal.h"

/*======================================================================*/
double mt32_genrand_res53(void)
{				/* generate a random number in [0:1) with 53-bit resolution.*/
    register uint32_t a, b;

    a = mt32_genrand_int32() >> 0x05,
    b = mt32_genrand_int32() >> 0x06;

    return ((double) a * 67108864.0 + b) / 9007199254740992.0;
}
