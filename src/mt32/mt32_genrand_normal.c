/*
 * mt32: MT19937ar
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt32_genrand_normal.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt_dist.h"
#include "mt32_internal.h"

/*======================================================================*/
double mt32_genrand_normal(void)
{				/* Generate a standard normal distributed random number. */
    return _mt_genrand_normal((double (*) (void *)) mt32_genrand_real3, NULL);
}
