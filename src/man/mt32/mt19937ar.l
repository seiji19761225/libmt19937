.\" $Id: mt19937ar.l,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
.TH MT19937ar l

.SH NAME
.B MT19937ar
\- a Mersenne Twister pseudorandom number generator

.SH SYNTAX
#include <libmt19937/mt19937ar.h>

.SH DESCRIPTION
This is a Mersenne Twister pseudorandom number generator with period 2^19937-1 with improved initialization scheme, by Takuji Nishimura and Makoto Matsumoto. 

.SH INITIALIZATION
The initialization scheme for the previous versions of MT (e.g. 1999/10/28 version or earlier) has a tiny problem, that the most significant bits of the seed is not well reflected to the state vector of MT.

This version (2002/1/26) has two initialization schemes:
.B init_genrand(\fIseed\fP)
and
.B init_by_array(\fIinit_key\fP, \fIkey_length\fP).

.B init_genrand(\fIseed\fP)
initializes the state vector by using one unsigned 32-bit integer "\fIseed\fP", which may be zero.

.B init_by_array(\fIinit_key\fP, \fIkey_length\fP)
initializes the state vector by using an array \fIinit_key\fP[] of unsigned 32-bit integers of length \fIkey_length\fP.
If \fIkey_length\fP is smaller than 624, then each array of 32-bit integers gives distinct initial state vector.
This is useful if you want a larger seed space than 32-bit word.

.SH GENERATION
After initialization, the following type of pseudorandom numbers are available.

.B genrand_int32()
\- generates unsigned 32-bit integers.
.br
.B genrand_int31()
\- generates unsigned 31-bit integers.
.br
.B genrand_real1()
\- generates uniform real in [0:1] (32-bit resolution).
.br
.B genrand_real2()
\- generates uniform real in [0:1) (32-bit resolution).
.br
.B genrand_real3()
\- generates uniform real in (0:1) (32-bit resolution).
.br
.B genrand_res53()
\- generates uniform real in [0:1) with 53-bit resolution.

.SH CRIPTROGRAPHY
This generator is not cryptoraphically secure.
You need to use a one-way (or hash) function to obtain a secure random sequence.

.SH CORRESPONDENCE
See:
.br
URL  http://www.math.keio.ac.jp/matumoto/emt.html
.br
E-mail   matumoto@math.keio.ac.jp, nisimura@sci.kj.yamagata-u.ac.jp

.SH REFERENCE
M. Matsumoto and T. Nishimura,
"Mersenne Twister: A 623-Dimensionally Equidistributed Uniform Pseudo-Random Number Generator",
ACM Transactions on Modeling and Computer Simulation,
Vol. 8, No. 1, January 1998, pp 3--30.

.SH COPYRIGHT
(c)1997-2002 Makoto Matsumoto and Takuji Nishimura, All rights reserved.
.br
(c)2008,2014-2015 Seiji Nishimura, All rights reserved.
