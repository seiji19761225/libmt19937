/*
 * mt32_r: reentrant version of MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_r_save_context.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdlib.h>
#include "mt32_r_internal.h"

/*======================================================================*/
int mt32_r_save_context(mt32_context_t *context, const char *fname)
{				/* write out a context to the restart file.*/
    FILE *fp;
    int status = EXIT_SUCCESS;

    if ((fp = fopen(fname, "wb")) == NULL ||
	mt32_r_save_context_fp(context, fp) == EXIT_FAILURE)
	status = EXIT_FAILURE;

    if (fp != NULL)
	fclose(fp);

    return status;
}
