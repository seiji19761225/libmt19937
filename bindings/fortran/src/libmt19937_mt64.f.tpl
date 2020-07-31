!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! libmt19937_mt64.f: FORTRAN binding of libmt19937 mt64 module
! (c)2014-2015 Seiji Nishimura <seiji1976@gmail.com>
! $Id: libmt19937_mt64.f.tpl,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
      MODULE libmt19937_mt64
      USE iso_c_binding
      IMPLICIT NONE
      PUBLIC
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! C API interfaces
      INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_init
      SUBROUTINE mt64_init(s)                                    BIND(C)
      IMPORT::C_INT64_T
      INTEGER(C_INT64_T),VALUE,INTENT(IN)::s
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_init_by_array
      SUBROUTINE mt64_init_by_array(s,n)                         BIND(C)
      IMPORT::C_INT64_T,C_SIZE_T
      INTEGER(C_INT64_T),INTENT(IN)::s(*)
      INTEGER(C_SIZE_T),VALUE,INTENT(IN)::n
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_genrand_int64
      FUNCTION mt64_genrand_int64()                              BIND(C)
      IMPORT::C_INT64_T
      INTEGER(C_INT64_T)::mt64_genrand_int64
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_genrand_int63
      FUNCTION mt64_genrand_int63()                              BIND(C)
      IMPORT::C_INT64_T
      INTEGER(C_INT64_T)::mt64_genrand_int63
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_genrand_real1
      FUNCTION mt64_genrand_real1()                              BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt64_genrand_real1
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_genrand_real2
      FUNCTION mt64_genrand_real2()                              BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt64_genrand_real2
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_genrand_real3
      FUNCTION mt64_genrand_real3()                              BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt64_genrand_real3
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_genrand_exp
      FUNCTION mt64_genrand_exp(mu)                              BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt64_genrand_exp
      REAL(C_DOUBLE),VALUE,INTENT(IN)::mu
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_genrand_gamma
      FUNCTION mt64_genrand_gamma(a,b)                           BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt64_genrand_gamma
      REAL(C_DOUBLE),VALUE,INTENT(IN)::a,b
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_genrand_geometric
      FUNCTION mt64_genrand_geometric(p)                         BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt64_genrand_geometric
      REAL(C_DOUBLE),VALUE,INTENT(IN)::p
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_genrand_normal
      FUNCTION mt64_genrand_normal()                             BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt64_genrand_normal
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_genrand_poisson
      FUNCTION mt64_genrand_poisson(mu)                          BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt64_genrand_poisson
      REAL(C_DOUBLE),VALUE,INTENT(IN)::mu
      END FUNCTION
      END INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
!  wrapper procedures
      CONTAINS
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_save_state
      SUBROUTINE mt64_save_state(fname,istat)
      USE iso_fortran_env,ONLY:ERROR_UNIT
      CHARACTER(LEN=*),INTENT(IN)::fname
      INTEGER,OPTIONAL,INTENT(OUT)::istat
      INTEGER::ierr
      INTERFACE
      FUNCTION c_mt64_save_state(fname)   BIND(C,NAME='mt64_save_state')
      IMPORT::C_INT,C_CHAR
      INTEGER(C_INT)::c_mt64_save_state
      CHARACTER(C_CHAR),INTENT(IN)::fname(*)
      END FUNCTION
      END INTERFACE
      ierr=c_mt64_save_state(TRIM(fname)//C_NULL_CHAR)
      IF (PRESENT(istat)) THEN
         istat=ierr
      ELSE IF(ierr/=0) THEN
         WRITE(ERROR_UNIT,100) 'mt64_save_state',TRIM(fname)
      END IF
      RETURN
 100  FORMAT('I/O error happened in ',A,' call for ',A,'.')
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt64_load_state
      SUBROUTINE mt64_load_state(fname,istat)
      USE iso_fortran_env,ONLY:ERROR_UNIT
      CHARACTER(LEN=*),INTENT(IN)::fname
      INTEGER,OPTIONAL,INTENT(OUT)::istat
      INTEGER::ierr
      INTERFACE
      FUNCTION c_mt64_load_state(fname)   BIND(C,NAME='mt64_load_state')
      IMPORT::C_INT,C_CHAR
      INTEGER(C_INT)::c_mt64_load_state
      CHARACTER(C_CHAR),INTENT(IN)::fname(*)
      END FUNCTION
      END INTERFACE
      ierr=c_mt64_load_state(TRIM(fname)//C_NULL_CHAR)
      IF (PRESENT(istat)) THEN
         istat=ierr
      ELSE IF(ierr/=0) THEN
         WRITE(ERROR_UNIT,100) 'mt64_load_state',TRIM(fname)
      END IF
      RETURN
 100  FORMAT('I/O error happened in ',A,' call for ',A,'.')
      END SUBROUTINE
      END MODULE
