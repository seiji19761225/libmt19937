/*
 * mt32: MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_genrand_int31.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt32_internal.h"

/*======================================================================*/
int32_t mt32_genrand_int31(void)
{				/* generate a random number in [0:2^31-1].*/
    return (int32_t) (mt32_genrand_int32() >> 0x01);
}
