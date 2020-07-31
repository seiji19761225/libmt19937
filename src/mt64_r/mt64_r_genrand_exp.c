/*
 * mt64_r: reentrant version of MT19937-64
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt64_r_genrand_exp.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt_dist.h"
#include "mt64_r_internal.h"

/*======================================================================*/
double mt64_r_genrand_exp(mt64_context_t *context, double mu)
{				/* Generate an exponentially-distributed number with mean mu (mu>0). */
    return _mt_genrand_exp((double (*) (void *)) mt64_r_genrand_real3, (void *) context, mu);
}
