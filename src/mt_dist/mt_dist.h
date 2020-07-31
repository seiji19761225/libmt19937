/*
 * mt_dist: framework of distributed RNG
 * (c)2014-2015 Seiji Nishimura
 * $Id: mt_dist.h,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#ifndef __MT_DIST_H__
#define __MT_DIST_H__

/* prototypes ----------------------------------------------------------*/

#ifndef __MT_DIST_INTERNAL__
#define   MT_DIST_API
#else
#define   MT_DIST_API	extern
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* These distributed functions are written by Pascal Getreuer ----------*/
MT_DIST_API double _mt_genrand_exp      (double (*) (void *), void *, double);
MT_DIST_API double _mt_genrand_gamma    (double (*) (void *), void *, double, double);
MT_DIST_API double _mt_genrand_geometric(double (*) (void *), void *, double);
MT_DIST_API double _mt_genrand_normal   (double (*) (void *), void *);
MT_DIST_API double _mt_genrand_poisson  (double (*) (void *), void *, double);

#ifdef __cplusplus
}
#endif

#undef    MT_DIST_API
#endif
