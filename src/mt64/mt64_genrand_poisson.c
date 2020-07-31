/*
 * mt64: MT19937-64
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt64_genrand_poisson.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt_dist.h"
#include "mt64_internal.h"

/*======================================================================*/
double mt64_genrand_poisson(double mu)
{				/* Generate a Poisson-distributed number with mean mu. */
    return _mt_genrand_poisson((double (*) (void *)) mt64_genrand_real3, NULL, mu);
}
