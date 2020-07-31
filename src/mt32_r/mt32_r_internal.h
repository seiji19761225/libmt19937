/*
 * mt32_r: reentrant version of MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_r_internal.h,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#ifndef __MT32_R_INTERNAL__
#define __MT32_R_INTERNAL__

#include "mt32_r.h"

/* constants -----------------------------------------------------------*/
#define MT32_R_MM	397
#define MT32_R_MATRIX_A	UINT32_C(0x9908b0df)	/* constant vector A          */
#define MT32_R_UM	UINT32_C(0x80000000)	/* most  significant w-r bits */
#define MT32_R_LM	UINT32_C(0x7fffffff)	/* least significant   r bits */
#define MT32_R_RM	UINT32_C(0xffffffff)	/* for WORDSIZE > 32bit       */

#if MT32_R_COK_KERNEL == 1
/* macro functions -----------------------------------------------------*/
#define MIXBITS(u,v)	(((u)&MT32_R_UM)|((v)&MT32_R_LM))
#define TWIST(u,v)	((MIXBITS(u,v)>>0x01)^(((v)&0x01)?MT32_R_MATRIX_A:0x00))

/* prototype -----------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

void _mt32_r_next_state(mt32_context_t *);

#ifdef __cplusplus
}
#endif

#endif	/* MT32_R_COK_KERNEL == 1 */

#endif
