.\" $Id: mt32.l,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
.TH MT32 l

.SH NAME
.B MT32
\- a 32-bit Mersenne Twister pseudorandom number generator

.SH SYNTAX
#include <libmt19937/mt32.h>

.SH DESCRIPTION
This is a 32-bit Mersenne Twister pseudorandom number generator with period 2^19937-1 with improved initialization scheme, by Takuji Nishimura and Makoto Matsumoto. 

.SH INITIALIZATION
This version has two initialization schemes:
.B mt32_init(\fIseed\fP)
and
.B mt32_init_by_array(\fIinit_key\fP, \fIkey_length\fP).

.B mt32_init(\fIseed\fP)
initializes the state vector by using one uint32_t "\fIseed\fP", which may be zero.

.B mt32_init_by_array(\fIinit_key\fP, \fIkey_length\fP)
initializes the state vector by using an array \fIinit_key\fP[] of uint32_t of length \fIkey_length\fP.
If \fIkey_length\fP is smaller than 624, then each member of uint32_t gives distinct initial state vector.
This is useful if you want a larger seed space than a 32-bit word.

.SH GENERATION
After initialization, the following type of uniform pseudorandom numbers are available.

.B mt32_genrand_int32()
\- generates unsigned 32-bit integers.
.br
.B mt32_genrand_int31()
\- generates unsigned 31-bit integers.
.br
.B mt32_genrand_real1()
\- generates uniform real in [0:1] (32-bit resolution).
.br
.B mt32_genrand_real2()
\- generates uniform real in [0:1) (32-bit resolution).
.br
.B mt32_genrand_real3()
\- generates uniform real in (0:1) (32-bit resolution).
.br
.B mt32_genrand_res53()
\- generates uniform real in [0:1) with 53-bit resolution.

The following type of distributed pseudorandom numbers are also available.

.B mt32_genrand_normal()
\- generates a standard normal distributed random number.
.br
.B mt32_genrand_exp(\fImu\fP)
\- generates an exponentially-distributed number with mean \fImu\fP.
.br
.B mt32_genrand_gamma(\fIa\fP, \fIb\fP)
\- generates a Gamma-distributed number with shape parameter \fIa\fP and scale parameter \fIb\fP.
.br
.B mt32_genrand_geometric(\fIp\fP)
\- generates a geometrically-distributed number where \fIp\fP is the probability of success.
.br
.B mt32_genrand_poisson(\fImu\fP)
\- generates a Poisson-distributed number with mean \fImu\fP.

.SH LOAD/SAVE
Following functions are provided to load/save status of the pseudorandom number generator.

.B mt32_load_state(\fIfname\fP)
\- loads status from a binary file. \fIfname\fP is the file name.
.br
.B mt32_load_state_fp(\fIfp\fP)
\- loads status from a binary file. \fIfp\fP is the file pointer.
.br
.B mt32_save_state(\fIfname\fP)
\- writes out current status to a binary file. \fIfname\fP is the file name.
.br
.B mt32_save_state_fp(\fIfp\fP)
\- writes out current status to a binary file. \fIfp\fP is the file pointer.

.B NOTE:
these functions return status value:
.B EXIT_SUCCESS
or
.B EXIT_FAILURE.

.SH SEE ALSO
.BR mt19937ar (l)

.SH COPYRIGHT
(c)1997-2002 Makoto Matsumoto and Takuji Nishimura, All rights reserved.
.br
(c)2011 Pascal Getreuer, All rights reserved.
.br
(c)2008,2014-2015 Seiji Nishimura, All rights reserved.
