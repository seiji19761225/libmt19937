/*
 * mt_dist: framework of distributed RNG
 * (c)2014-2015 Seiji Nishimura
 * Grabbed from the source code of randmt by Pascal Getreuer
 * $Id: mt_genrand_normal.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include "mt_dist_internal.h"

/*======================================================================*/
double _mt_genrand_normal(double (*genrand) (void *), void *context)
#if 0
{				/* Generate a standard normal distributed random number. */
    return sqrt(-2.0 *    log(genrand(context))) *
	   cos ( 2.0 * M_PI * genrand(context));
}
#else				/*......................................*/
{				/* Generate a standard normal distributed random number. */
    return sqrt(-2.0 *    log(genrand(context))) *
	   sin ( 2.0 * M_PI * genrand(context));
}
#endif
