/*
 * wtime.c: wall clock timer
 * (c)2011-2015 Seiji Nishimrua
 * $Id: wtime.c,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
 */

#include "wtime.h"
#include <stddef.h>
#include <sys/time.h>

/*======================================================================*/
double wtime(void)
{				/* wall clock timer                     */
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1)
	return -1.0;		/* negative value means error. */

    return (double) tv.tv_sec  +
	   (double) tv.tv_usec * 1.E-6;
}
