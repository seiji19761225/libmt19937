! mt32_r: reentrant version of MT19937ar
! (c)2014-2015 Seiji Nishimura <seiji1976@gmail.com>
! $Id: mt32_r_test.f,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
      PROGRAM MAIN
      USE libmt19937_mt32_r
      IMPLICIT REAL*8(a-h,o-z)
!
      INTEGER,PARAMETER::N=1000
      REAL(8)::WORK(0:7)
      TYPE(mt32_context)::context=MT32_CONTEXT_INITIALIZER
!
      CALL mt32_r_init(context,4357_4) !any nonzero 4byte integer can be used as a seed
!
      DO I=0,N-1
         WORK(mod(I,8))=mt32_r_genrand_real1(context)
         IF (mod(I,8)==7.or.I==N-1)
     &      WRITE(*,100) WORK(0:mod(I,8))
      END DO
!
      STOP
 100  FORMAT(8(f8.6,' '))
      END
