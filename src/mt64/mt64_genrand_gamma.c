/*
 * mt64: MT19937-64
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt64_genrand_gamma.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt_dist.h"
#include "mt64_internal.h"

/*======================================================================*/
double mt64_genrand_gamma(double a, double b)
{				/* Generate a Gamma-distributed number with shape parameter a and scale parameter b. */
    return _mt_genrand_gamma((double (*) (void *)) mt64_genrand_real3, NULL, a, b);
}
