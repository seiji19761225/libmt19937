/*
 * mt64: MT19937-64
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt64_genrand_geometric.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt_dist.h"
#include "mt64_internal.h"

/*======================================================================*/
double mt64_genrand_geometric(double p)
{				/* Generate a standard geometric distributed random number (p is the probability of success). */
    return _mt_genrand_geometric((double (*) (void *)) mt64_genrand_real3, NULL, p);
}
