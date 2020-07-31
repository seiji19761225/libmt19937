/*
 * mt32: MT19937ar
 * (c)2008,2014-2015 Seiji Nishimura <seiji1976@gmail.com>
 * $Id: mt32_save_state.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include <stdlib.h>
#include "mt32_internal.h"

/*======================================================================*/
int mt32_load_state(const char *fname)
{				/* load a state from the restart file. */
    FILE *fp;
    int status = EXIT_SUCCESS;

    if ((fp = fopen(fname, "rb")) == NULL ||
	mt32_load_state_fp(fp)    == EXIT_FAILURE)
	status = EXIT_FAILURE;

    if (fp != NULL)
	fclose(fp);

    return status;
}
