! mt64: MT19937-64
! (c)2014-2015 Seiji Nishimura <seiji1976@gmail.com>
! $Id: mt64_test.f,v 1.1.1.2 2015/01/14 00:00:00 seiji Exp seiji $
      PROGRAM MAIN
      USE libmt19937_mt64
      IMPLICIT REAL*8(a-h,o-z)
!
      INTEGER,PARAMETER::N=1000
      REAL(8)::WORK(0:7)
!
      CALL mt64_init(4357_8) !any nonzero 8byte integer can be used as a seed
!
      DO I=0,N-1
         WORK(mod(I,8))=mt64_genrand_real1()
         IF (mod(I,8)==7.or.I==N-1)
     &      WRITE(*,100) WORK(0:mod(I,8))
      END DO
!
      STOP
 100  FORMAT(8(f8.6,' '))
      END
