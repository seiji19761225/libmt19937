/*
 * mt32_r: reentrant version of MT19937ar
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt32_r_genrand_exp.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt_dist.h"
#include "mt32_r_internal.h"

/*======================================================================*/
double mt32_r_genrand_exp(mt32_context_t *context, double mu)
{				/* Generate an exponentially-distributed number with mean mu (mu>0). */
    return _mt_genrand_exp((double (*) (void *)) mt32_r_genrand_real3, (void *) context, mu);
}
