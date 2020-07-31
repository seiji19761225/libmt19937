/*
 * mt_dist: framework of distributed RNG
 * (c)2014-2015 Seiji Nishimura
 * Grabbed from the source code of randmt by Pascal Getreuer
 * $Id: mt_genrand_geometric.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include "mt_dist_internal.h"

/*======================================================================*/
double _mt_genrand_geometric(double (*genrand) (void *), void *context, double p)
{				/* Generate a standard geometric distributed random number (p is the probability of success). */
    return floor(log(genrand(context)) / log(1.0 - p)) + 1.0;
}
