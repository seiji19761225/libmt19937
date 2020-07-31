/*
 * mt32_r: reentrant version of MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_r_save_context_fp.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdlib.h>
#include "mt32_r_internal.h"

/*======================================================================*/
int mt32_r_save_context_fp(mt32_context_t *context, FILE *fp)
#if 0
{				/* write out a context to the restart file.*/
    if (fwrite(context, sizeof(*context), 1, fp) != 1 ||
	fflush(fp) != 0)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
#else				/*......................................*/
#if MT32_R_COK_KERNEL == 1
{				/* write out a context to the restart file.*/
    if (fwrite(&context->left , sizeof(context->left    ), 1        , fp) != 1         ||
	fwrite( context->state, sizeof(context->state[0]), MT32_R_NN, fp) != MT32_R_NN ||
	fflush(fp) != 0)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
#else				/*......................................*/
{				/* write out a context to the restart file.*/
    if (fwrite(&context->mti, sizeof(context->mti  ), 1        , fp) != 1         ||
	fwrite( context->mt , sizeof(context->mt[0]), MT32_R_NN, fp) != MT32_R_NN ||
	fflush(fp) != 0)
	return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
#endif
#endif
