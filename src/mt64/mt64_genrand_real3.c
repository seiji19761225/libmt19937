/*
 * mt64: MT19937-64
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt64_genrand_real3.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt64_internal.h"

/*======================================================================*/
double mt64_genrand_real3(void)
{				/* generates a random number in (0:1).  */
    return ((double) (mt64_genrand_int64() >> 12) + 0.5) / 4503599627370496.0;
}
