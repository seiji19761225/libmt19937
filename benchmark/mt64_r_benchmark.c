/*
 * mt64_r: reentrant version of MT19937-64
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt64_r_benchmark.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <omp.h>
#include <stdio.h>
#include <stdint.h>
#include <libmt19937/mt64_r.h>

#define T_THRESHOLD	60.0

/* prototype */
void mt64_r_test(double *, int *, size_t *);

/*======================================================================*/
int main(int argc, char **argv)
{
    int    n_threads;
    size_t iter  = 1;
    double tm, perf_per_thread;

#pragma omp parallel
    mt64_r_test(&tm, &n_threads, &iter);

    perf_per_thread = (double) iter * 16 / tm * 1.E-6;

    printf("MT64_R Benchmark: %f[MOP/s] = %f[MOP/s/thread] * %d[threads]\n",
						perf_per_thread * n_threads,
						perf_per_thread,  n_threads);

    return 0;
}

/*----------------------------------------------------------------------*/
void mt64_r_test(double *tm, int *n_threads, size_t *iter)
{
    mt64_context_t context = MT64_CONTEXT_INITIALIZER;

#pragma omp single
    *n_threads = omp_get_num_threads();

    mt64_r_init(&context, omp_get_thread_num());

    do {
	register size_t i;
	register uint64_t mt;
	mt64_context_t *cp = &context;

#pragma omp single
	*iter = (*iter << 0x01) | 0x01;
#pragma omp single
	*tm = omp_get_wtime();

	for (i = 0; i < *iter; i++) {	/* generates 16 random numbers per each iteration. */
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	    mt = mt64_r_genrand_int64(cp);
	}

#pragma omp barrier
#pragma omp single
	*tm = omp_get_wtime() - *tm;
    } while (*tm <= T_THRESHOLD);

    return;
}
