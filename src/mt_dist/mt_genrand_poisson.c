/*
 * mt_dist: framework of distributed RNG
 * (c)2014-2015 Seiji Nishimura
 * Grabbed from the source code of randmt by Pascal Getreuer
 * $Id: mt_genrand_poisson.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <math.h>
#include "mt_dist_internal.h"

#ifndef M_LOGSQRT2PI
#define M_LOGSQRT2PI    0.9189385332046727417803297	/* == log(sqrt(2.0*M_PI)) */
#endif

/* prototype */
static double _mt_logfactorial(double);

/*======================================================================*/
double _mt_genrand_poisson(double (*genrand) (void *), void *context, double mu)
{				/* Generate a Poisson-distributed number with mean mu. */
    double k, b, a, U, V, us, vr, invalpha, logmu;

    if (mu < 10.0) {		/* Use simple direct algorthm for small mu */
	vr = exp(-mu);
	k  = -1.0;
	V  =  1.0;
	do {
	    k += 1.0;
	    V *= genrand(context);
	} while (V > vr);
    } else {			/* Use the "PTRS" algorithm of Hormann     */
	b        =  0.931  + 2.53    * sqrt(mu);
	a        = -0.059  + 0.02483 * b;
	vr       =  0.9277 - 3.6224  / (b - 2.0);
	invalpha =  1.1239 + 1.1328  / (b - 3.4);
	logmu    = log(mu);
	do {
	    U  = genrand(context) - 0.5;
	    V  = genrand(context);
	    us = 0.5 - fabs(U);
	    k  = floor((2.0 * a / us + b) * U + mu + 0.43);
	} while ((us < 0.07 || V > vr               ) &&
		 (k  < 0.0  || (us < 0.013 && V > us) ||
		 log(V * invalpha / (a / (us * us) + b)) > -mu + k * logmu - _mt_logfactorial(k)));
    }

    return k;
}

/*----------------------------------------------------------------------*/
static double _mt_logfactorial(double n)
{				/* Compute the natural logarithm of the factorial   */
    int i;
    double x, xsq, res, corr, logfactorial;
    static const double Table[] = {	/* Look-up table for log(n!) for n=2,...,11 */
	0.69314718055994530942, 1.7917594692280550008,
	3.1780538303479456197 , 4.7874917427820459943,
	6.5792512120101009951 , 8.5251613610654143002,
	10.604602902745250228 , 12.801827480081469611,
	15.104412573075515295 , 17.502307845873885839
    },                  C    [] = {	/* Asymptotic approximation coefficients    */
	-1.910444077728e-03         , 8.4171387781295e-04           ,
	-5.952379913043012e-04      , 7.93650793500350248e-04       ,
	-2.777777777777681622553e-03, 8.333333333333333331554247e-02,
	 5.7083835261e-03
    };

    if (n > 11.0) {		/* Asymptotic approximation, based on the public domain */
				/* NETLIB (Fortran) code by W.J. Cody and L. Stoltz     */
	x = 1.0 + floor(n + 0.5);
	if (x <= 2.25e76) {
	    res = C[6];
	    xsq = x * x;
	    for (i = 0; i < 6; i++)
		res = res / xsq + C[i];
	} else {
	    res = 0.0;
	}
	corr         = log(x);
	logfactorial = res / x + M_LOGSQRT2PI - corr / 2.0 + x * (corr - 1.0);
    } else {			/* Use look-up table */
	i            = (int) floor(n + 0.5);
	logfactorial = (i >= 2) ? Table[i - 2] : 0.0;
    }

    return logfactorial;
}
