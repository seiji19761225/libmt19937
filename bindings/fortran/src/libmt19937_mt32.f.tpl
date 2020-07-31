!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! libmt19937_mt32.f: FORTRAN binding of libmt19937 mt32 module
! (c)2014-2015 Seiji Nishimura <seiji1976@gmail.com>
! $Id: libmt19937_mt32.f.tpl,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
      MODULE libmt19937_mt32
      USE iso_c_binding
      IMPLICIT NONE
      PUBLIC
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! C API interfaces
      INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_init
      SUBROUTINE mt32_init(s)                                    BIND(C)
      IMPORT::C_INT32_T
      INTEGER(C_INT32_T),VALUE,INTENT(IN)::s
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_init_by_array
      SUBROUTINE mt32_init_by_array(s,n)                         BIND(C)
      IMPORT::C_INT32_T,C_SIZE_T
      INTEGER(C_INT32_T),INTENT(IN)::s(*)
      INTEGER(C_SIZE_T),VALUE,INTENT(IN)::n
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_int32
      FUNCTION mt32_genrand_int32()                              BIND(C)
      IMPORT::C_INT32_T
      INTEGER(C_INT32_T)::mt32_genrand_int32
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_int31
      FUNCTION mt32_genrand_int31()                              BIND(C)
      IMPORT::C_INT32_T
      INTEGER(C_INT32_T)::mt32_genrand_int31
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_real1
      FUNCTION mt32_genrand_real1()                              BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_real1
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_real2
      FUNCTION mt32_genrand_real2()                              BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_real2
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_real3
      FUNCTION mt32_genrand_real3()                              BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_real3
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_res53
      FUNCTION mt32_genrand_res53()                              BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_res53
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_exp
      FUNCTION mt32_genrand_exp(mu)                              BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_exp
      REAL(C_DOUBLE),VALUE,INTENT(IN)::mu
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_gamma
      FUNCTION mt32_genrand_gamma(a,b)                           BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_gamma
      REAL(C_DOUBLE),VALUE,INTENT(IN)::a,b
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_geometric
      FUNCTION mt32_genrand_geometric(p)                         BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_geometric
      REAL(C_DOUBLE),VALUE,INTENT(IN)::p
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_normal
      FUNCTION mt32_genrand_normal()                             BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_normal
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_poisson
      FUNCTION mt32_genrand_poisson(mu)                          BIND(C)
      IMPORT::C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_poisson
      REAL(C_DOUBLE),VALUE,INTENT(IN)::mu
      END FUNCTION
      END INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
!  wrapper procedures
      CONTAINS
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_save_state
      SUBROUTINE mt32_save_state(fname,istat)
      USE iso_fortran_env,ONLY:ERROR_UNIT
      CHARACTER(LEN=*),INTENT(IN)::fname
      INTEGER,OPTIONAL,INTENT(OUT)::istat
      INTEGER::ierr
      INTERFACE
      FUNCTION c_mt32_save_state(fname)   BIND(C,NAME='mt32_save_state')
      IMPORT::C_INT,C_CHAR
      INTEGER(C_INT)::c_mt32_save_state
      CHARACTER(C_CHAR),INTENT(IN)::fname(*)
      END FUNCTION
      END INTERFACE
      ierr=c_mt32_save_state(TRIM(fname)//C_NULL_CHAR)
      IF (PRESENT(istat)) THEN
         istat=ierr
      ELSE IF (ierr/=0) THEN
         WRITE(ERROR_UNIT,100) 'mt32_save_state',TRIM(fname)
      END IF
      RETURN
 100  FORMAT('I/O error happened in ',A,' call for ',A,'.')
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_load_state
      SUBROUTINE mt32_load_state(fname,istat)
      USE iso_fortran_env,ONLY:ERROR_UNIT
      CHARACTER(LEN=*),INTENT(IN)::fname
      INTEGER,OPTIONAL,INTENT(OUT)::istat
      INTEGER::ierr
      INTERFACE
      FUNCTION c_mt32_load_state(fname)   BIND(C,NAME='mt32_load_state')
      IMPORT::C_INT,C_CHAR
      INTEGER(C_INT)::c_mt32_load_state
      CHARACTER(C_CHAR),INTENT(IN)::fname(*)
      END FUNCTION
      END INTERFACE
      ierr=c_mt32_load_state(TRIM(fname)//C_NULL_CHAR)
      IF (PRESENT(istat)) THEN
         istat=ierr
      ELSE IF (ierr/=0) THEN
         WRITE(ERROR_UNIT,100) 'mt32_load_state',TRIM(fname)
      END IF
      RETURN
 100  FORMAT('I/O error happened in ',A,' call for ',A,'.')
      END SUBROUTINE
      END MODULE
