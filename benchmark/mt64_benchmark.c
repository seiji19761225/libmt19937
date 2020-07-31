/*
 * mt64: MT19937-64
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt64_benchmark.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdio.h>
#include <stdint.h>
#include <libmt19937/mt64.h>

#include "wtime.h"

#define T_THRESHOLD	60.0

/* prototype */
void mt64_test(double *, size_t *);

/*======================================================================*/
int main(int argc, char **argv)
{
    size_t iter = 1;
    double tm, perf;

    mt64_test(&tm, &iter);

    perf = (double) iter * 16 / tm * 1.E-6;

    printf("MT64 Benchmark: %f[MOP/s]\n", perf);

    return 0;
}

/*----------------------------------------------------------------------*/
void mt64_test(double *tm, size_t *iter)
{
    mt64_init(0x1234);

    do {
	register size_t i;
	register uint64_t mt;

	*iter = (*iter << 0x01) | 0x01;
	*tm = wtime();

	for (i = 0; i < *iter; i++) {	/* generates 16 random numbers per each iteration. */
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	    mt = mt64_genrand_int64();
	}

	*tm = wtime() - *tm;
    } while (*tm <= T_THRESHOLD);

    return;
}
