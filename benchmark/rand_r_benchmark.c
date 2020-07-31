/*
 * rand_r_benchmark.c
 * (c)2014-2015 Seiji Nishimura
 * $Id: rand_r_benchmark.c,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define T_THRESHOLD	60.0

/* prototype */
void rand_r_test(double *, int *, size_t *);

/*======================================================================*/
int main(int argc, char **argv)
{
    int    n_threads;
    size_t iter  = 1;
    double tm, perf_per_thread;

#pragma omp parallel
    rand_r_test(&tm, &n_threads, &iter);

    perf_per_thread = (double) iter * 16 / tm * 1.E-6;

    printf("RAND_R Benchmark: %f[MOP/s] = %f[MOP/s/thread] * %d[threads]\n",
						perf_per_thread * n_threads,
						perf_per_thread,  n_threads);

    return 0;
}

/*----------------------------------------------------------------------*/
void rand_r_test(double *tm, int *n_threads, size_t *iter)
{
    unsigned int seed;

    seed = omp_get_thread_num();

#pragma omp single
    *n_threads = omp_get_num_threads();

    do {
	register size_t i;
	register int rnd;
	unsigned int *sp = &seed;

#pragma omp single
	*iter = (*iter << 0x01) | 0x01;
#pragma omp single
	*tm = omp_get_wtime();

	for (i = 0; i < *iter; i++) {	/* generates 16 random numbers per each iteration. */
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	    rnd = rand_r(sp);
	}

#pragma omp barrier
#pragma omp single
	*tm = omp_get_wtime() - *tm;
    } while (*tm <= T_THRESHOLD);

    return;
}
