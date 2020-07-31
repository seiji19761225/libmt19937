/*
 * mt64: MT19937-64
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt64_genrand_int63.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt64_internal.h"

/*======================================================================*/
int64_t mt64_genrand_int63(void)
{				/* generate a random number in [0:2^63-1].*/
    return (int64_t) (mt64_genrand_int64() >> 0x01);
}
