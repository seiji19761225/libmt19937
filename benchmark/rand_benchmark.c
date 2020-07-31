/*
 * rand_benchmark.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: rand_benchmark.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdio.h>
#include <stdlib.h>

#include "wtime.h"

#define T_THRESHOLD	60.0

/* prototype */
void rand_test(double *, size_t *);

/*======================================================================*/
int main(int argc, char **argv)
{
    size_t iter = 1;
    double tm, perf;

    rand_test(&tm, &iter);

    perf = (double) iter * 16 / tm * 1.E-6;

    printf("RAND Benchmark: %f[MOP/s]\n", perf);

    return 0;
}

/*----------------------------------------------------------------------*/
void rand_test(double *tm, size_t *iter)
{
    srand(0x1234);

    do {
	register size_t i;
	register int rnd;

	*iter = (*iter << 0x01) | 0x01;
	*tm = wtime();

	for (i = 0; i < *iter; i++) {	/* generates 16 random numbers per each iteration. */
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	    rnd = rand();
	}

	*tm = wtime() - *tm;
    } while (*tm <= T_THRESHOLD);

    return;
}
