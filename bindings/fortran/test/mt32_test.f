! mt32: MT19937ar
! (c)2014-2015 Seiji Nishimura <seiji1976@gmail.com>
! $Id: mt32_test.f,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
      PROGRAM MAIN
      USE libmt19937_mt32
      IMPLICIT REAL*8(a-h,o-z)
!
      INTEGER,PARAMETER::N=1000
      REAL(8)::WORK(0:7)
!
      CALL mt32_init(4357_4) !any nonzero 4byte integer can be used as a seed
!
      DO I=0,N-1
         WORK(mod(I,8))=mt32_genrand_real1()
         IF (mod(I,8)==7.or.I==N-1)
     &      WRITE(*,100) WORK(0:mod(I,8))
      END DO
!
      STOP
 100  FORMAT(8(f8.6,' '))
      END
