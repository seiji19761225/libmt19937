/*
 * mt64_r: reentrant version of MT19937-64
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt64_r_internal.h,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#ifndef __MT64_R_INTERNAL__
#define __MT64_R_INTERNAL__

#include "mt64_r.h"

/* constants -----------------------------------------------------------*/
#define MT64_R_MM	156
#define MT64_R_MATRIX_A	UINT64_C(0xB5026F5AA96619E9)	/* constant vector A         */
#define MT64_R_UM	UINT64_C(0xFFFFFFFF80000000)	/* most  significant 33 bits */
#define MT64_R_LM	UINT64_C(0x000000007FFFFFFF)	/* least significant 31 bits */

#if MT64_R_COK_KERNEL == 1
/* macro functions -----------------------------------------------------*/
#define MIXBITS(u,v)	(((u)&MT64_R_UM)|((v)&MT64_R_LM))
#define TWIST(u,v)	((MIXBITS(u,v)>>0x01)^(((v)&0x01)?MT64_R_MATRIX_A:0x00))

/* prototype -----------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

void _mt64_r_next_state(mt64_context_t *);

#ifdef __cplusplus
}
#endif

#endif	/* MT64_R_COK_KERNEL == 1 */

#endif
