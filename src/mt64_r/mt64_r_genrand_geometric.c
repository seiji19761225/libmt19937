/*
 * mt64_r: reentrant version of MT19937-64
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt64_r_genrand_geometric.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt_dist.h"
#include "mt64_r_internal.h"

/*======================================================================*/
double mt64_r_genrand_geometric(mt64_context_t *context, double p)
{				/* Generate a standard geometric distributed random number (p is the probability of success). */
    return _mt_genrand_geometric((double (*) (void *)) mt64_r_genrand_real3, (void *) context, p);
}
