!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! libmt19937_mt32_r.f: FORTRAN binding of libmt19937 mt32_r module
! (c)2014-2015 Seiji Nishimura <seiji1976@gmail.com>
! $Id: libmt19937_mt32_r.f.tpl,v 1.1.1.3 2015/01/14 00:00:00 seiji Exp seiji $
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
      MODULE libmt19937_mt32_r
      USE iso_c_binding
      IMPLICIT NONE
      PUBLIC
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! constants
      INTEGER,PARAMETER::MT32_R_NN=624
#ifndef USE_COK_KERNEL
      INTEGER,PARAMETER::MT32_R_UNINITIALIZED=MT32_R_NN+1
#endif
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! data type
      TYPE,BIND(C)::mt32_context
#ifdef  USE_COK_KERNEL
      LOGICAL(C_BOOL)::initf
      TYPE(C_PTR)::next
      INTEGER(C_INT32_T)::left,state(MT32_R_NN)
#else
      INTEGER(C_INT32_T)::mti,mt(MT32_R_NN)
#endif
      END TYPE
!
      TYPE(mt32_context),PARAMETER::                                    &
     &     mt32_context_initializer=                                    &
#ifdef  USE_COK_KERNEL
     &                    mt32_context(.FALSE.,C_NULL_PTR,1,MT32_R_NN*0)
#else
     &                    mt32_context(MT32_R_UNINITIALIZED,MT32_R_NN*0)
#endif
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! C API interfaces
      INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_r_init
      SUBROUTINE mt32_r_init(context,s)                          BIND(C)
      IMPORT::mt32_context,C_INT32_T
      TYPE(mt32_context),INTENT(IN)::context
      INTEGER(C_INT32_T),VALUE,INTENT(IN)::s
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_r_init_by_array
      SUBROUTINE mt32_r_init_by_array(context,s,n)               BIND(C)
      IMPORT::mt32_context,C_INT32_T,C_SIZE_T
      TYPE(mt32_context),INTENT(IN)::context
      INTEGER(C_INT32_T),INTENT(IN)::s(*)
      INTEGER(C_SIZE_T),VALUE,INTENT(IN)::n
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_r_genrand_int32
      FUNCTION mt32_r_genrand_int32(context)                     BIND(C)
      IMPORT::mt32_context,C_INT32_T
      INTEGER(C_INT32_T)::mt32_r_genrand_int32
      TYPE(mt32_context),INTENT(IN)::context
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_r_genrand_int31
      FUNCTION mt32_r_genrand_int31(context)                     BIND(C)
      IMPORT::mt32_context,C_INT32_T
      INTEGER(C_INT32_T)::mt32_r_genrand_int31
      TYPE(mt32_context),INTENT(IN)::context
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_r_genrand_real1
      FUNCTION mt32_r_genrand_real1(context)                     BIND(C)
      IMPORT::mt32_context,C_DOUBLE
      REAL(C_DOUBLE)::mt32_r_genrand_real1
      TYPE(mt32_context),INTENT(IN)::context
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_r_genrand_real2
      FUNCTION mt32_r_genrand_real2(context)                     BIND(C)
      IMPORT::mt32_context,C_DOUBLE
      REAL(C_DOUBLE)::mt32_r_genrand_real2
      TYPE(mt32_context),INTENT(IN)::context
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_r_genrand_real3
      FUNCTION mt32_r_genrand_real3(context)                     BIND(C)
      IMPORT::mt32_context,C_DOUBLE
      REAL(C_DOUBLE)::mt32_r_genrand_real3
      TYPE(mt32_context),INTENT(IN)::context
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_r_genrand_res53
      FUNCTION mt32_r_genrand_res53(context)                     BIND(C)
      IMPORT::mt32_context,C_DOUBLE
      REAL(C_DOUBLE)::mt32_r_genrand_res53
      TYPE(mt32_context),INTENT(IN)::context
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_exp
      FUNCTION mt32_genrand_exp(context,mu)                      BIND(C)
      IMPORT::mt32_context,C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_exp
      TYPE(mt32_context),INTENT(IN)::context
      REAL(C_DOUBLE),VALUE,INTENT(IN)::mu
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_gamma
      FUNCTION mt32_genrand_gamma(context,a,b)                   BIND(C)
      IMPORT::mt32_context,C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_gamma
      TYPE(mt32_context),INTENT(IN)::context
      REAL(C_DOUBLE),VALUE,INTENT(IN)::a,b
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_geometric
      FUNCTION mt32_genrand_geometric(context,p)                 BIND(C)
      IMPORT::mt32_context,C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_geometric
      TYPE(mt32_context),INTENT(IN)::context
      REAL(C_DOUBLE),VALUE,INTENT(IN)::p
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_normal
      FUNCTION mt32_genrand_normal(context)                      BIND(C)
      IMPORT::mt32_context,C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_normal
      TYPE(mt32_context),INTENT(IN)::context
      END FUNCTION
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_genrand_poisson
      FUNCTION mt32_genrand_poisson(context,mu)                  BIND(C)
      IMPORT::mt32_context,C_DOUBLE
      REAL(C_DOUBLE)::mt32_genrand_poisson
      TYPE(mt32_context),INTENT(IN)::context
      REAL(C_DOUBLE),VALUE,INTENT(IN)::mu
      END FUNCTION
      END INTERFACE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
!  wrapper procedures
      CONTAINS
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_r_save_context
      SUBROUTINE mt32_r_save_context(context,fname,istat)
      USE iso_fortran_env,ONLY:ERROR_UNIT
      TYPE(mt32_context),INTENT(IN)::context
      CHARACTER(LEN=*),INTENT(IN)::fname
      INTEGER,OPTIONAL,INTENT(OUT)::istat
      INTEGER::ierr
      INTERFACE
      FUNCTION c_mt32_r_save_context(context,fname)                     &
     &                                BIND(C,NAME='mt32_r_save_context')
      IMPORT::mt32_context,C_INT,C_CHAR
      INTEGER(C_INT)::c_mt32_r_save_context
      TYPE(mt32_context),INTENT(IN)::context
      CHARACTER(C_CHAR),INTENT(IN)::fname(*)
      END FUNCTION
      END INTERFACE
      ierr=c_mt32_r_save_context(context,TRIM(fname)//C_NULL_CHAR)
      IF (PRESENT(istat)) THEN
         istat=ierr
      ELSE IF (ierr/=0) THEN
         WRITE(ERROR_UNIT,100) 'mt32_r_save_context',TRIM(fname)
      END IF
      RETURN
 100  FORMAT('I/O error happened in ',A,' call for ',A,'.')
      END SUBROUTINE
!---+&---1----+----2----+----3----+----4----+----5----+----6----+----7--
! mt32_r_load_context
      SUBROUTINE mt32_r_load_context(context,fname,istat)
      USE iso_fortran_env,ONLY:ERROR_UNIT
      TYPE(mt32_context),INTENT(OUT)::context
      CHARACTER(LEN=*),INTENT(IN)::fname
      INTEGER,OPTIONAL,INTENT(OUT)::istat
      INTEGER::ierr
      INTERFACE
      FUNCTION c_mt32_r_load_context(context,fname)                     &
     &                                BIND(C,NAME='mt32_r_load_context')
      IMPORT::mt32_context,C_INT,C_CHAR
      INTEGER(C_INT)::c_mt32_r_load_context
      TYPE(mt32_context),INTENT(OUT)::context
      CHARACTER(C_CHAR),INTENT(IN)::fname(*)
      END FUNCTION
      END INTERFACE
      ierr=c_mt32_r_load_context(context,TRIM(fname)//C_NULL_CHAR)
      IF (PRESENT(istat)) THEN
         istat=ierr
      ELSE IF (ierr/=0) THEN
         WRITE(ERROR_UNIT,100) 'mt32_r_load_context',TRIM(fname)
      END IF
      RETURN
 100  FORMAT('I/O error happened in ',A,' call for ',A,'.')
      END SUBROUTINE
      END MODULE
