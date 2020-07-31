.\" $Id: mt32_r.l,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
.TH MT32_R l

.SH NAME
.B MT32_R
\- a 32-bit reentrant Mersenne Twister pseudorandom number generator

.SH SYNTAX
#include <libmt19937/mt32_r.h>

.SH DESCRIPTION
This is a 32-bit reentrant Mersenne Twister pseudorandom number generator with period 2^19937-1 with improved initialization scheme, by Takuji Nishimura and Makoto Matsumoto. 

.SH CONTEXT
All mt32_r functions require pointer of a
.B mt32_context_t
data as the first argument.
Each
.B mt32_context_t
data type has a state vector of MT19937ar inside.

.SH INITIALIZATION
Before calling pseudorandom number generation functions, all
.B mt32_context_t
data must be initialized.
This version has two initialization schemes:
.B mt32_r_init(\fIcontext\fP, \fIseed\fP)
and
.B mt32_r_init_by_array(\fIcontext\fP, \fIinit_key\fP, \fIkey_length\fP).

.B mt32_r_init(\fIcontext\fP, \fIseed\fP)
initializes the state vector by using one uint32_t "\fIseed\fP", which may be zero.

.B mt32_r_init_by_array(\fIcontext\fP, \fIinit_key\fP, \fIkey_length\fP)
initializes the state vector by using an array \fIinit_key\fP[] of uint32_t of length \fIkey_length\fP.
If \fIkey_length\fP is smaller than 624, then each member of uint32_t gives distinct initial state vector.
This is useful if you want a larger seed space than a 32-bit word.

.SH GENERATION
After initialization, the following type of pseudorandom numbers are available.

.B mt32_r_genrand_int32(\fIcontext\fP)
\- generates unsigned 32-bit integers.
.br
.B mt32_r_genrand_int31(\fIcontext\fP)
\- generates unsigned 31-bit integers.
.br
.B mt32_r_genrand_real1(\fIcontext\fP)
\- generates uniform real in [0:1] (32-bit resolution).
.br
.B mt32_r_genrand_real2(\fIcontext\fP)
\- generates uniform real in [0:1) (32-bit resolution).
.br
.B mt32_r_genrand_real3(\fIcontext\fP)
\- generates uniform real in (0:1) (32-bit resolution).
.br
.B mt32_r_genrand_res53(\fIcontext\fP)
\- generates uniform real in [0:1) with 53-bit resolution.

The following type of distributed pseudorandom numbers are also available.

.B mt32_r_genrand_normal(\fIcontext\fP)
\- generates a standard normal distributed random number.
.br
.B mt32_r_genrand_exp(\fIcontext\fP, \fImu\fP)
\- generates an exponentially-distributed number with mean \fImu\fP.
.br
.B mt32_r_genrand_gamma(\fIcontext\fP, \fIa\fP, \fIb\fP)
\- generates a Gamma-distributed number with shape parameter \fIa\fP and scale parameter \fIb\fP.
.br
.B mt32_r_genrand_geometric(\fIcontext\fP, \fIp\fP)
\- generates a geometrically-distributed number where \fIp\fP is the probability of success.
.br
.B mt32_r_genrand_poisson(\fIcontext\fP, \fImu\fP)
\- generates a Poisson-distributed number with mean \fImu\fP.

.SH LOAD/SAVE
Following functions are provided to load/save context of the pseudorandom number generator.

.B mt32_r_load_context(\fIcontext\fP, \fIfname\fP)
\- loads context from a binary file. \fIfname\fP is the file name.
.br
.B mt32_r_load_context_fp(\fIcontext\fP, \fIfp\fP)
\- loads context from a binary file. \fIfp\fP is the file pointer.
.br
.B mt32_r_save_context(\fIcontext\fP, \fIfname\fP)
\- writes out current context to a binary file. \fIfname\fP is the file name.
.br
.B mt32_r_save_context_fp(\fIcontext\fP, \fIfp\fP)
\- writes out current context to a binary file. \fIfp\fP is the file pointer.

.B NOTE:
these functions return status value:
.B EXIT_SUCCESS
or
.B EXIT_FAILURE.

.SH SEE ALSO
.BR mt32 (l),
.BR mt19937ar (l)

.SH COPYRIGHT
(c)1997-2002 Makoto Matsumoto and Takuji Nishimura, All rights reserved.
.br
(c)2011 Pascal Getreuer, All rights reserved.
.br
(c)2008,2014-2015 Seiji Nishimura, All rights reserved.
