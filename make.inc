#=======================================================================
# make.inc
# $Id: make.inc,v 1.1.1.1 2014/11/18 00:00:00 seiji Exp seiji $
#=======================================================================
.PHONY:
.SUFFIXES:
.SUFFIXES: .c .f .o
SHELL	= /bin/sh
#-----------------------------------------------------------------------
# compiler and compilation flags
CC	= gcc
CFLAGS	= -O3 -fpic -fopenmp
FC	= gfortran
FFLAGS	= -O3 -fpic -fopenmp
#.......................................................................
PFLAGS	=
LIBS	=
#-----------------------------------------------------------------------
# system config.
#<<< C/C++ preprocessor command ........................................
CPP	= cpp -P -nostdinc -traditional -undef
#<<< GNU make command ..................................................
GMAKE	= make
#<<< library archiver ..................................................
AR	= ar crsv
#<<< ranlib command (if needed) ........................................
#RANLIB	= ranlib
#<<< linker/loader .....................................................
LD	= ld
#<<< install command ...................................................
INSTALL	= install -p
M755	= -m755
M644	= -m644
#<<< system directories ................................................
BINDIR	= bin
LIBDIR	= lib
MANDIR	= man
SRCDIR	= src
INCDIR	= include
X11DIR	= /usr/X11R6
#-----------------------------------------------------------------------
# generic rules
.c.o:
	$(CC) $(CFLAGS) $(PFLAGS) -c -o $@ $<
.f.o:
	$(FC) $(FFLAGS) -c -o $@ $<
