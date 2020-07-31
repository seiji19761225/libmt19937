/*
 * mt32_r: reentrant version of MT19937ar
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt32_r_genrand_geometric.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt_dist.h"
#include "mt32_r_internal.h"

/*======================================================================*/
double mt32_r_genrand_geometric(mt32_context_t *context, double p)
{				/* Generate a standard geometric distributed random number (p is the probability of success). */
    return _mt_genrand_geometric((double (*) (void *)) mt32_r_genrand_real3, (void *) context, p);
}
