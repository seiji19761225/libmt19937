/*
 * mt32: MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_genrand_real1.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt32_internal.h"

/*======================================================================*/
double mt32_genrand_real1(void)
{				/* generates a random number in [0:1].  */
    return (double) mt32_genrand_int32() / 4294967295.0;	/* divided by 2^32-1. */
}
