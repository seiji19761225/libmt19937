/*
 * mt_dist: framework of distributed RNG
 * (c)2014-2015 Seiji Nishimura
 * Grabbed from the source code of randmt by Pascal Getreuer
 * $Id: mt_genrand_gamma.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include "mt_dist_internal.h"

/*======================================================================*/
double _mt_genrand_gamma(double (*genrand) (void *), void *context, double a, double b)
{				/* Generate a Gamma-distributed number with shape parameter a and scale parameter b. */
    double gamma = 0.0;

    if (a >= 1.0) {
	double c, d, u, v, x;
	d = a - 1.0 / 3.0;
	c = 1.0 / sqrt(9.0 * d);
	do {
	    do {
		x = _mt_genrand_normal(genrand, context);
		v = 1.0 + c * x;
	    } while (v <= 0.0);
	    v = v * v * v;
	    u = genrand(context);
	    x = x * x;
	} while (u >= 1.0 - 0.0331 * x * x &&
		 log(u) >= x / 2.0 + d * (1.0 - v + log(v)));
	gamma = b * d * v;
    } else if (a > 0.0) {
	gamma = _mt_genrand_gamma(genrand, context , 1.0 + a, b) *
			      pow(genrand (context), 1.0 / a);
    }

    return gamma;
}
