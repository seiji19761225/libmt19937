/*
 * mt32: MT19937ar
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt32_benchmark.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdio.h>
#include <stdint.h>
#include <libmt19937/mt32.h>

#include "wtime.h"

#define T_THRESHOLD	60.0

/* prototype */
void mt32_test(double *, size_t *);

/*======================================================================*/
int main(int argc, char **argv)
{
    size_t iter = 1;
    double tm, perf;

    mt32_test(&tm, &iter);

    perf = (double) iter * 16 / tm * 1.E-6;

    printf("MT32 Benchmark: %f[MOP/s]\n", perf);

    return 0;
}

/*----------------------------------------------------------------------*/
void mt32_test(double *tm, size_t *iter)
{
    mt32_init(0x1234);

    do {
	register size_t i;
	register uint32_t mt;

	*iter = (*iter << 0x01) | 0x01;
	*tm = wtime();

	for (i = 0; i < *iter; i++) {	/* generates 16 random numbers per each iteration. */
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	    mt = mt32_genrand_int32();
	}

	*tm = wtime() - *tm;
    } while (*tm <= T_THRESHOLD);

    return;
}
