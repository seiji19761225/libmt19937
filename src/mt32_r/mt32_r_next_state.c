/*
 * mt32_r: reentrant version of MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_r_next_state.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "mt32_r_internal.h"

#if    MT32_R_COK_KERNEL != 1
#error MT32_R_COK_KERNEL != 1
#endif

/*======================================================================*/
void _mt32_r_next_state(mt32_context_t *context)
{
    register uint32_t j, *p;

    /* if mt32_r_init() has not been called,
     * a default initial seed is used
     */
    if (!context->initf)
	mt32_r_init(context, UINT32_C(5489));

    context->left = MT32_R_NN;
    context->next = p = context->state;

    for (j = MT32_R_NN - MT32_R_MM; j > 0; j--, p++)
	*p = p[MT32_R_MM] ^ TWIST(p[0], p[1]);

    for (j = MT32_R_MM - 1; j > 0; j--, p++)
	*p = p[MT32_R_MM - MT32_R_NN] ^ TWIST(p[0], p[1]);

    *p = p[MT32_R_MM - MT32_R_NN] ^ TWIST(p[0], context->state[0]);

    return;
}
