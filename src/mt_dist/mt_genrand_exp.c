/*
 * mt_dist: framework of distributed RNG
 * (c)2014-2015 Seiji Nishimura
 * Grabbed from the source code of randmt by Pascal Getreuer
 * $Id: mt_genrand_exp.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include "mt_dist_internal.h"

/*======================================================================*/
double _mt_genrand_exp(double (*genrand) (void *), void *context, double mu)
{				/* Generate an exponentially-distributed number with mean mu (mu>0). */
    return -mu * log(genrand(context));
}
