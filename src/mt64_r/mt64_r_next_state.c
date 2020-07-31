/*
 * mt64_r: reentrant version of MT19937-64
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt64_r_next_state.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt64_r_internal.h"

#if    MT64_R_COK_KERNEL != 1
#error MT64_R_COK_KERNEL != 1
#endif

/*======================================================================*/
void _mt64_r_next_state(mt64_context_t *context)
{
    register uint32_t  j;
    register uint64_t *p;

    /* if mt64_r_init() has not been called,
     * a default initial seed is used
     */
    if (!context->initf)
	mt64_r_init(context, UINT64_C(5489));

    context->left = MT64_R_NN;
    context->next = p = context->state;

    for (j = MT64_R_NN - MT64_R_MM; j > 0; j--, p++)
	*p = p[MT64_R_MM] ^ TWIST(p[0], p[1]);

    for (j = MT64_R_MM - 1; j > 0; j--, p++)
	*p = p[MT64_R_MM - MT64_R_NN] ^ TWIST(p[0], p[1]);

    *p = p[MT64_R_MM - MT64_R_NN] ^ TWIST(p[0], context->state[0]);

    return;
}
