/*
 * mt32: MT19937ar
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt32_dist_test.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */
/*
 * 
 * # TEST PROGRAM
 * 
 * The test program applies the Kolmogorov-Smirnov and chi-squared tests to 
 * verify that the pseudorandom samplers produce the intended distributions. 
 * Note that the output of this program is different on each run.
 * 
 * Typical output is shown below:
 * 
 * For each random number generator, we sample N=1000000
 * values and compare the sample distribution to the theoretical
 * density function with the Kolmogorov-Smirnov test.
 * 
 *     Sampler                      D
 *     mt32_genrand_real3()         0.001095
 *     mt32_genrand_normal()        0.001077
 *     mt32_genrand_exp(1)          0.000811
 *     mt32_genrand_gamma(0.2,1)    0.000516
 *     mt32_genrand_gamma(  1,1)    0.000906
 *     mt32_genrand_gamma(  2,1)    0.001051
 *     mt32_genrand_gamma( 20,1)    0.001079
 * 
 * Supposing the distributions are correct, the D values should be
 * small with high probability:
 *     D < 0.001358 with probability 0.95
 *     D < 0.001627 with probability 0.99
 *     D < 0.001949 with probability 0.999
 * 
 * We apply the chi-squared test to verify the distributions of the
 * geometric and Poisson generators (the Kolmogorov-Smirnov test
 * applies only to continuous distributions).
 * 
 *     Sampler                      p-value
 *     mt32_genrand_geometric(0.1)  0.883482
 *     mt32_genrand_geometric(0.5)  0.527853
 *     mt32_genrand_geometric(0.9)  0.651309
 *     mt32_genrand_poisson(0.2)    0.700759
 *     mt32_genrand_poisson(  1)    0.551421
 *     mt32_genrand_poisson(  2)    0.619268
 *     mt32_genrand_poisson( 20)    0.656092
 *     mt32_genrand_poisson(200)    0.422257
 * 
 * Supposing the distributions are correct, the p-values should be
 * above zero with high probability:
 *     p-value > 0.05 with probability 0.95
 *     p-value > 0.01 with probability 0.99
 *     p-value > 0.001 with probability 0.999
 * 
 */
/* Random distribution test, Pascal Getreuer 2011
 *
 * Copyright (C) 2011, Pascal Getreuer <getreuer@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1. Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *
 *   3. The names of its contributors may not be used to endorse or promote
 *      products derived from this software without specific prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <libmt19937/mt32.h>

#ifndef M_LN10
/** \brief Natural logarithm of 10 */
#define M_LN10      2.30258509299404568401799145468436421
#endif
#ifndef M_SQRT2
/** \brief The constant \f$ \sqrt{2} \f$ */
#define M_SQRT2     1.41421356237309504880168872420969808
#endif
#ifndef M_1_SQRTPI
/** \brief The constant \f$ 1/\pi \f$ */
#define M_1_SQRTPI  0.564189583547756286948
#endif
#ifndef M_LOGSQRT2PI
/** @brief The constant log(sqrt(2 pi)) */
#define M_LOGSQRT2PI    0.9189385332046727417803297
#endif

#if defined(__GNUC__) && !defined(ATTRIBUTE_UNUSED)
/* Macro for the unused attribue GNU extension */
#define ATTRIBUTE_UNUSED __attribute__((unused))
#endif
#ifndef ATTRIBUTE_UNUSED
#define ATTRIBUTE_UNUSED
#endif

double erfc(double x);
double lgamma(double x);
double gammap(double a, double x);

static double real3cdf(double x, ATTRIBUTE_UNUSED const double *params)
    { return (x <= 0) ? 0 : ((1 <= x) ? 1 : x); }

static double normalcdf(double x, ATTRIBUTE_UNUSED const double *params)
    { return 0.5*erfc(-x/M_SQRT2); }
static double expcdf(double x, const double *params)
    { return 1 - exp(-x/params[0]); }
static double gammacdf(double x, const double *params)
    { return gammap(params[0], x/params[1]); }
static double poissoncdf(double x, const double *params)
    { return (x < 0) ? 0 : (1 - gammap(floor(x + 1), params[0])); }
static double geometriccdf(double x, const double *params)
    { return (x < 1) ? 0 : (1 - pow(1 - params[0], floor(x))); }
static int cmp_double(const void *a, const void *b)
    { return (*((double *)a) > *((double *)b))
        - (*((double *)a) < *((double *)b)); }

static double ks_test(double *x, unsigned long numsamples,
    double (*cdf)(double, const double *), const double *params);
static double ks_critical(long numsamples, double alpha);
static double chi2_test(double *x, long numsamples, long minbin, long maxbin,
    double (*cdf)(double, const double *), const double *params);


int main(void)
{    
    const long numsamples = 1000000;
    double *x, mu, p, param[2];
    long n;
    
    
    if(!(x = (double *)malloc(sizeof(double)*numsamples)))
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }   
        
    mt32_init((int) time(NULL));
    
    printf("Pseudorandom distribution test, Pascal Getreuer 2011\n\n");
    printf("For each random number sampler, we sample N=%ld\n"
	   "values and compare the sample distribution to the theoretical\n"
	   "density function with the Kolmogorov-Smirnov test.\n\n"
	   "    Sampler                      D\n", numsamples);
    
    /*** Test real3orm random number generator ***/
    printf("    mt32_genrand_real3()         ");
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_real3();    
    printf("%.6f\n", ks_test(x, numsamples, real3cdf, NULL));
    
    /*** Test normal random number generator ***/
    printf("    mt32_genrand_normal()        ");    
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_normal();    
    printf("%.6f\n", ks_test(x, numsamples, normalcdf, NULL));
    
    /*** Test exponential random number generator ***/
    printf("    mt32_genrand_exp(%g)          ", mu = 1);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_exp(mu);
    printf("%.6f\n", ks_test(x, numsamples, expcdf, &mu));
    
    /*** Test Gamma random number generator ***/
    printf("    mt32_genrand_gamma(%3g,%g)    ", param[0] = 0.2, param[1] = 1);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_gamma(param[0], param[1]);
    printf("%.6f\n", ks_test(x, numsamples, gammacdf, param));
    
    printf("    mt32_genrand_gamma(%3g,%g)    ", param[0] = 1, param[1] = 1);    
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_gamma(param[0], param[1]);
    printf("%.6f\n", ks_test(x, numsamples, gammacdf, param));
    
    printf("    mt32_genrand_gamma(%3g,%g)    ", param[0] = 2, param[1] = 1);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_gamma(param[0], param[1]);
    printf("%.6f\n", ks_test(x, numsamples, gammacdf, param));
    
    printf("    mt32_genrand_gamma(%3g,%g)    ", param[0] = 20, param[1] = 1);  
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_gamma(param[0], param[1]);
    printf("%.6f\n", ks_test(x, numsamples, gammacdf, param));
    
    printf("\nSupposing the distributions are correct, the D values should be\n"
        "small with high probability:\n");
    printf("    D < %.6f with probability 0.95\n", 
        ks_critical(numsamples, 0.95));
    printf("    D < %.6f with probability 0.99\n", 
        ks_critical(numsamples, 0.99));
    printf("    D < %.6f with probability 0.999\n\n", 
        ks_critical(numsamples, 0.999));
    
    
    printf("We apply the chi-squared test to verify the distributions of the\n"
	   "geometric and Poisson generators (the Kolmogorov-Smirnov test\n"
	   "applies only to continuous distributions).\n\n"
	   "    Sampler                      p-value\n");
    /*** Test geometric random number generator ***/
    printf("    mt32_genrand_geometric(%3g)  ", p = 0.1);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_geometric(p);
    printf("%.6f\n", chi2_test(x, numsamples, 1, 46, geometriccdf, &p));
    printf("    mt32_genrand_geometric(%3g)  ", p = 0.5);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_geometric(p);
    printf("%.6f\n", chi2_test(x, numsamples, 1, 17, geometriccdf, &p));
    printf("    mt32_genrand_geometric(%3g)  ", p = 0.9);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_geometric(p);
    printf("%.6f\n", chi2_test(x, numsamples, 1, 5, geometriccdf, &p));

    /*** Test Poisson random number generator ***/
    printf("    mt32_genrand_poisson(%3g)    ", mu = 0.2);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_poisson(mu);
    printf("%.6f\n", chi2_test(x, numsamples, 0, 4, poissoncdf, &mu));
    
    printf("    mt32_genrand_poisson(%3g)    ", mu = 1);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_poisson(mu);
    printf("%.6f\n", chi2_test(x, numsamples, 0, 8, poissoncdf, &mu));
    
    printf("    mt32_genrand_poisson(%3g)    ", mu = 2);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_poisson(mu);
    printf("%.6f\n", chi2_test(x, numsamples, 0, 10, poissoncdf, &mu));
    
    printf("    mt32_genrand_poisson(%3g)    ", mu = 20);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_poisson(mu);
    printf("%.6f\n", chi2_test(x, numsamples, 4, 42, poissoncdf, &mu));

    printf("    mt32_genrand_poisson(%3g)    ", mu = 200);
    for(n = 0; n < numsamples; n++)
        x[n] = mt32_genrand_poisson(mu);
    printf("%.6f\n", chi2_test(x, numsamples, 146, 259, poissoncdf, &mu));

    printf("\nSupposing the distributions are correct, the p-values should be\n"
	   "above zero with high probability:\n");
    printf("    p-value > 0.05 with probability 0.95\n"
	   "    p-value > 0.01 with probability 0.99\n"
	   "    p-value > 0.001 with probability 0.999\n\n");
    free(x);
    return 0;
}


static double ks_test(double *x, unsigned long numsamples,
    double (*cdf)(double, const double *), const double *params)
{
    double xleft, xright, cdfvalue = 1e300, diff, ks_statistic;
    unsigned long n;

    qsort(x, numsamples, sizeof(double), cmp_double);

    for(n = 0, xright = ks_statistic = 0; n < numsamples; n++)
    {
        xleft = xright;
        xright = ((double)n + 1.0) / numsamples;
        cdfvalue = cdf(x[n], params);

        if((diff = fabs(xleft - cdfvalue)) > ks_statistic)
            ks_statistic = diff;
        if((diff = fabs(xright - cdfvalue)) > ks_statistic)
            ks_statistic = diff;
    }

    return ks_statistic;
}

/* Asymptotic approximation of Kolmogorov-Smirnov critical values
       Miller, "Table of Percentage Points of Kolmogorov Statistics," 1956 */
static double ks_critical(long numsamples, double alpha)
{
    double temp, cv;

    alpha = 0.5*(1 - alpha);
    temp = -log(alpha)/M_LN10;
    cv = sqrt(-0.5*log(alpha)/numsamples) - 0.16693/numsamples
        - (0.09037*sqrt(temp)*temp - 0.01515*temp - 0.08467*alpha - 0.11143)
        /(sqrt(numsamples)*numsamples);
    return (cv <= 1 - alpha) ? cv : (1 - alpha);
}


static double chi2_test(double *x, long numsamples, long minbin, long maxbin,
    double (*cdf)(double, const double *), const double *params)
{
    double chi2stat = 0, expected, diff;
    long *observed;
    long n, k, numbins = maxbin - minbin + 1;

    if(!(observed = (long *)calloc(numbins, sizeof(long))))
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 0;
    }

    for(n = 0; n < numsamples; n++)
    {
        k = (long)floor(x[n] + 0.5);

        if(k <= minbin)
            observed[0]++;
        else if(k >= maxbin)
            observed[numbins - 1]++;
        else
            observed[k - minbin]++;
    }

    for(n = minbin; n <= maxbin; n++)
    {        
        if(n == minbin)
            expected = numsamples*cdf(n, params);
        else if(n == maxbin)
            expected = numsamples*(1 - cdf(n - 1, params));
        else
            expected = numsamples*(cdf(n, params) - cdf(n - 1, params));
        
        if(expected < 10)
            printf("Warning: expected=%g in bin %ld is less than 10\n", 
                expected, n);
        else
        {
            diff = observed[n - minbin] - expected;
            chi2stat += diff * diff / expected;
        }
    }
    
    free(observed);
    return (1 - gammap(0.5*(numbins - 1), chi2stat/2));
}


/* Special math functions **************************************************/

#ifndef EPS
/** @brief Smallest double precision machine number such that 1 + EPS > 1 */
#define EPS             2.22e-16
#endif

#ifndef INFINITY
static double __makeinfinity() {
  double zero = 0;
  return 1/zero;
}
/** @brief Positive infinity */
#define INFINITY __makeinfinity()
#endif

/** @brief Largest value for which loggamma produces a finite value */
#define XBIG            2.55e305
/** @brief Approximate value of loggamma(XBIG)^(1/4) */
#define QRTXBIG         2.25e76


static double erfc_rpoly(const double *P, const double *Q, int N, double x);

/**
 * \brief Complement error function 
 *
 * Based on the public domain NETLIB (Fortran) code by W. J. Cody
 * Applied Mathematics Division
 * Argonne National Laboratory
 * Argonne, IL 60439
 * 
 * From the original documentation:
 * The main computation evaluates near-minimax approximations from "Rational
 * Chebyshev approximations for the error function" by W. J. Cody, Math. 
 * Comp., 1969, PP. 631-638.  This transportable program uses rational 
 * functions that theoretically approximate erf(x) and erfc(x) to at least 18
 * significant decimal digits.  The accuracy achieved depends on the 
 * arithmetic system, the compiler, the intrinsic functions, and proper
 * selection of the machine-dependent constants.
 */
double erfc(double x)
{
    static const double P1[5] = { 3.16112374387056560e0, 
        1.13864154151050156e2, 3.77485237685302021e2, 
        3.20937758913846947e3, 1.85777706184603153e-1 };
    static const double Q1[4] = { 2.36012909523441209e1, 
        2.44024637934444173e2, 1.28261652607737228e3, 
        2.84423683343917062e3 };
    static const double P2[9] = { 5.64188496988670089e-1,
        8.88314979438837594e0, 6.61191906371416295e1,
        2.98635138197400131e2, 8.81952221241769090e2,
        1.71204761263407058e3, 2.05107837782607147e3,
        1.23033935479799725e3, 2.15311535474403846e-8 };
    static const double Q2[8] = { 1.57449261107098347e1,
        1.17693950891312499e2, 5.37181101862009858e2,
        1.62138957456669019e3, 3.29079923573345963e3,
        4.36261909014324716e3, 3.43936767414372164e3,
        1.23033935480374942e3 };
    static const double P3[6] = { 3.05326634961232344e-1,
        3.60344899949804439e-1, 1.25781726111229246e-1,
        1.60837851487422766e-2, 6.58749161529837803e-4,
        1.63153871373020978e-2 };
    static const double Q3[5] = { 2.56852019228982242e0,
        1.87295284992346047e0, 5.27905102951428412e-1,
        6.05183413124413191e-2, 2.33520497626869185e-3 };
    double y, result;
    
    y = fabs(x);
    
    if(y <= 0.46875)
        return 1 - x * erfc_rpoly(P1, Q1, 3, (y > 1.11e-16) ? y*y : 0);
    else if(y <= 4)
        result = exp(-y*y) * erfc_rpoly(P2, Q2, 7, y);
    else if(y >= 26.543)
        result = 0;
    else
        result = exp(-y*y) * ( (M_1_SQRTPI 
            - y*y * erfc_rpoly(P3, Q3, 4, 1.0/(y*y))) / y );
    
    return (x < 0) ? (2 - result) : result;
}

/* Evaluate rational polynomial
 * P[N+1] x^N+1 + P[0] x^N + ... + P[N-1] x + P[N]
 *        x^N+1 + Q[0] x^N + ... + Q[N-1] x + Q[N]
 */
static double erfc_rpoly(const double *P, const double *Q, int N, double x)
{
    double xnum = P[N + 1]*x, xden = x;
    int n;
    
    for(n = 0; n < N; n++)
    {
        xnum = (xnum + P[n]) * x;
        xden = (xden + Q[n]) * x;
    }
    
    return (xnum + P[N]) / (xden + Q[N]);
}


static double lgamma_rpoly(const double *P, const double *Q,  double x);
static double lgamma_asymp(double x);

/**
 * \brief The natural logarithm of the gamma function
 *
 * Based on the public domain NETLIB (Fortran) code by W. J. Cody and L. Stoltz
 * Applied Mathematics Division
 * Argonne National Laboratory
 * Argonne, IL 60439
 * 
 * From the original documentation:
 * This routine calculates the LOG(GAMMA) function for a positive real argument
 * X.  Computation is based on an algorithm outlined in references 1 and 2.  
 * The program uses rational functions that theoretically approximate 
 * LOG(GAMMA) to at least 18 significant decimal digits.  The approximation for
 * X > 12 is from reference 3, while approximations for X < 12.0 are similar to
 * those in reference 1, but are unpublished.  The accuracy achieved depends on
 * the arithmetic system, the compiler, the intrinsic functions, and proper 
 * selection of the machine-dependent constants.
 * 
 * Error returns:
 * The program returns the value XINF for X .LE. 0.0 or when overflow would occur.
 * The computation is believed to be free of underflow and overflow.
 * 
 * References:
 * 1. W. J. Cody and K. E. Hillstrom, "Chebyshev Approximations for the Natural 
 *    Logarithm of the Gamma Function," Math. Comp. 21, 1967, pp. 198-203.
 * 2. K. E. Hillstrom, ANL/AMD Program ANLC366S, DGAMMA/DLGAMA, May, 1969.
 * 3. Hart, Et. Al., Computer Approximations, Wiley and sons, New York, 1968.
 */
double lgamma(double x)
{
    /* Numerator and denominator coefficients for rational minimax
       approximation over (0.5,1.5).                               */
    static const double P1[8] = {
        4.945235359296727046734888e0, 2.018112620856775083915565e2,
        2.290838373831346393026739e3, 1.131967205903380828685045e4,
        2.855724635671635335736389e4, 3.848496228443793359990269e4,
        2.637748787624195437963534e4, 7.225813979700288197698961e3};
    static const double Q1[8] = {
        6.748212550303777196073036e1, 1.113332393857199323513008e3,
        7.738757056935398733233834e3, 2.763987074403340708898585e4,
        5.499310206226157329794414e4, 6.161122180066002127833352e4,
        3.635127591501940507276287e4, 8.785536302431013170870835e3};
    /* Numerator and denominator coefficients for rational minimax
       approximation over (1.5,4.0).                               */
    static const double P2[8] = {
        4.974607845568932035012064e0, 5.424138599891070494101986e2,
        1.550693864978364947665077e4, 1.847932904445632425417223e5,
        1.088204769468828767498470e6, 3.338152967987029735917223e6,
        5.106661678927352456275255e6, 3.074109054850539556250927e6};
    static const double Q2[8] = {
        1.830328399370592604055942e2, 7.765049321445005871323047e3,
        1.331903827966074194402448e5, 1.136705821321969608938755e6,
        5.267964117437946917577538e6, 1.346701454311101692290052e7,
        1.782736530353274213975932e7, 9.533095591844353613395747e6};
    /* Numerator and denominator coefficients for rational minimax
       approximation over (4.0,12.0).                              */
    static const double P4[8] = {
        1.474502166059939948905062e4, 2.426813369486704502836312e6,
        1.214755574045093227939592e8, 2.663432449630976949898078e9,
        2.940378956634553899906876e10, 1.702665737765398868392998e11,
        4.926125793377430887588120e11, 5.606251856223951465078242e11};
    static const double Q4[8] = {
        -2.690530175870899333379843e3, -6.393885654300092398984238e5,
        -4.135599930241388052042842e7, -1.120872109616147941376570e9,
        -1.488613728678813811542398e10, -1.016803586272438228077304e11,
        -3.417476345507377132798597e11, -4.463158187419713286462081e11};    
    double y, corr;
    
    if(x < 0 || XBIG < x)
        return INFINITY;
    else if(x < EPS)
        return -log(x);
    else if(x <= 1.5)
    {
        if(x < 0.6796875)
        {
            corr = -log(x);
            y = x;
        }
        else
        {
            corr = 0;
            y = x - 1;
        }
        
        if(x <= 0.5 || x >= 0.6796875)
            return corr + (y * (-5.772156649015328605195174e-1 
                + y * lgamma_rpoly(P1, Q1, y)));
        else
        {
            x -= 1;
            return corr + (x * (4.227843350984671393993777e-1 
                + x * lgamma_rpoly(P2, Q2, x)));
        }
    }
    else if(x <= 4)
    {
        x -= 2;
        return x * (4.227843350984671393993777e-1 
            + x * lgamma_rpoly(P2, Q2, x));
    }
    else if(x <= 12)
    {
        x -= 4;
        return 1.791759469228055000094023e0 
            - x * lgamma_rpoly(P4, Q4, x);
    }
    else
        return lgamma_asymp(x);
}

/* Evaluate rational polynomial 
 (P[0] x^7 + P[1] x^6 + P[2] x^5 + P[3] x^4 + P[4] x^3 
 + P[5] x^2 + P[6] x + P[7]) /
 (x^8 + Q[0] x^7 + Q[1] x^6 + Q[2] x^5 + Q[3] x^4 + Q[4] x^3 
 + Q[5] x^2 + Q[6] x + Q[7])
 */
static double lgamma_rpoly(const double *P, const double *Q,  double x)
{
    double xnum = P[0], xden = x + Q[0];
    int i;
    
    for(i = 1; i < 8; i++)
    {
        xnum = xnum*x + P[i];
        xden = xden*x + Q[i];
    }
    
    return xnum/xden;
}

/* Asymptotic approximation of loggamma over (12, INF) */
static double lgamma_asymp(double x)
{
    /* Approximation coefficients */
    static const double C[8] = { -1.910444077728e-03, 
        8.4171387781295e-04, -5.952379913043012e-04, 
        7.93650793500350248e-04, -2.777777777777681622553e-03, 
        8.333333333333333331554247e-02, 5.7083835261e-03};
    double xsq, res, corr;
    int i;
    
    res = 0;
        
    if(x <= QRTXBIG)
    {
        res = C[6];
        xsq = x*x;
        
        for(i = 0; i < 6; i++)
            res = res/xsq + C[i];
    }
    
    corr = log(x);
    return res/x + M_LOGSQRT2PI - corr/2 + x*(corr - 1);
}


/* This routine evaluates the regularized gamma function
 *  P(a,x) = gamma(a,x)/Gamma(a),
 * where gamma(a,x) is the lower incomplete Gamma function.
 */
double gammap(double a, double x)
{
    if(a < 0 || x < 0)
        return 0;
    else if(x < 1 || x < a + 1)
    {   /* Series expansion:
         *            x^a e^-x          x        x^2
         *  P(a,x) = ---------- ( 1 + ----- + ---------- + ... )
         *           Gamma(1+a)       (a+1)   (a+1)(a+2)
         */
        double xden = a, sum = 1, term = 1;
        
        do
        {
            sum += (term *= x/(xden += 1));
        }while(term > sum*1e-15);
        
        return exp(a*log(x) - x - lgamma(1.0 + a)) * sum;
    }
    else
    {   /* Continued fraction expansion using modified Lentz's algorithm */
        double prod, C = x + 1 - a, D = 0, xnum, xden, delta = 0;
        int i;
        
        for(i = 1, prod = xden = C; i < 100 && fabs(delta - 1) > 2.22e-16; i++)
        {
            xnum = i*(a - i);
            xden += 2;
            D = xden + xnum*D;
            C = xden + xnum/C;
            
            if(fabs(D) < 1e-60)
                D = 1e-60;
            if(fabs(C) < 1e-60)
                C = 1e-60;
            
            prod *= (delta = C*(D = 1/D));
        }
        
        return 1 - exp(a*log(x) - x - lgamma(a)) / prod;
    }
}

