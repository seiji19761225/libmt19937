/*
 * mt32: MT19937ar
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt32_genrand_poisson.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt_dist.h"
#include "mt32_internal.h"

/*======================================================================*/
double mt32_genrand_poisson(double mu)
{				/* Generate a Poisson-distributed number with mean mu. */
    return _mt_genrand_poisson((double (*) (void *)) mt32_genrand_real3, NULL, mu);
}
