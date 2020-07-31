#=======================================================================
# makefile
# $Id: Makefile,v 1.1.1.4 2016/02/16 00:00:00 seiji Exp seiji $
#=======================================================================
include ../make.inc

.PHONY: default clean clobber install install_src uninstall

PFLAGS	=
LIBS	=
#-----------------------------------------------------------------------
# modules
#.......................................................................
# mt32   module (32bit)
MT32_SRC	= libmt19937_mt32.f
#.......................................................................
# mt32_r module (32bit reentrant)
MT32R_SRC	= libmt19937_mt32_r.f
#.......................................................................
# mt64   module (64bit)
MT64_SRC	= libmt19937_mt64.f
#.......................................................................
# mt64_r module (64bit reentrant)
MT64R_SRC	= libmt19937_mt64_r.f
#.......................................................................
SRCS	= $(MT32_SRC) $(MT32R_SRC) $(MT64_SRC) $(MT64R_SRC)
#-----------------------------------------------------------------------
# auto-config.
include ./config.mk
#......................................................................
# FORTRAN binding library installation path
FPREFIX	= $(PREFIX)
FLIBDIR	= $(LIBDIR)
FSRCDIR	= $(SRCDIR)
FINCDIR	= $(INCDIR)
#
LIBPATH	= $(FPREFIX)/$(FLIBDIR)
SRCPATH	= $(FPREFIX)/$(FSRCDIR)/lib$(LIBNAME)/fortran
INCPATH	= $(FPREFIX)/$(FINCDIR)/lib$(LIBNAME)/fortran
#......................................................................
#LIBS	+= -L$(PREFIX)/$(LIBDIR) -l$(LIBNAME)
LIB_A	= lib$(LIBNAME)_fortran.a
LIB_S	= lib$(LIBNAME)_fortran.so.1.1.1
SONAME	= lib$(LIBNAME)_fortran.so.1
#......................................................................
TARGET	= $(LIB_A)

ifeq ($(COK),yes)
PFLAGS	+= -DUSE_COK_KERNEL
endif

ifneq ($(SHARED),no)
MAJOR	= $(shell echo $(SHARED) | awk 'BEGIN{FS="."}; {print $$1}')
MINOR	= $(shell echo $(SHARED) | awk 'BEGIN{FS="."}; {print $$2}')
ifneq ($(MAJOR),)
ifneq ($(MINOR),)
SONAME	= lib$(LIBNAME)_fortran.so.$(MAJOR)
LIB_S	= lib$(LIBNAME)_fortran.so.$(SHARED)
endif
endif
TARGET	+= $(LIB_S)
endif
#.......................................................................
OBJS	= $(strip $(subst .f,.o  ,$(SRCS)))
MODS	= $(strip $(subst .f,.mod,$(SRCS)))
#-----------------------------------------------------------------------
default: $(TARGET)
	@ls -l $^
	@ls -l $(MODS)

$(LIB_A): $(SRCS) $(OBJS)
	$(AR) $@ $^
ifneq  ($(RANLIB),)
	$(RANLIB) $@
endif

$(LIB_S): $(LIB_A)
	$(FC) -shared -o $@ -Wl,-soname,$(SONAME) $(OBJS) $(LIBS)

$(SRCS):
	$(CPP) $(PFLAGS) < $< | sed -e '/^ *$$/d' > $@
#.......................................................................
install: $(TARGET) $(MODS)
	mkdir -p   $(LIBPATH) $(INCPATH)
	$(INSTALL) $(M644) $(MODS)  $(INCPATH)
	$(INSTALL) $(M644) $(LIB_A) $(LIBPATH)
ifneq  ($(SHARED),no)
	$(INSTALL) $(M755) $(LIB_S) $(LIBPATH)
	cd $(LIBPATH); rm -f $(SONAME)               ; ln -s $(LIB_S) $(SONAME)
	cd $(LIBPATH); rm -f lib$(LIBNAME)_fortran.so; ln -s $(LIB_S) lib$(LIBNAME)_fortran.so
endif
#	$(GMAKE) -C man $@

install_src: $(SRCS)
	mkdir -p   $(SRCPATH)
	$(INSTALL) $(M644) $(SRCS) $(SRCPATH)
#	$(GMAKE) -C man install

uninstall:
	rm -f $(LIBPATH)/lib$(LIBNAME)_fortran*
	rm -f $(INCPATH)/libmt19937*.mod
	rm -f $(SRCPATH)/libmt19937*.f
#	$(GMAKE) -C man $@

clean:
	rm -f $(TARGET) *.o *.mod *~ core*
	for file in *; do \
	    if [ -e $${file}.tpl ]; then \
	        rm -f $${file}; \
	    fi; \
	done
clobber: clean uninstall
#.......................................................................
# dependencies
#.......................................................................
$(OBJS): ./config.mk ../make.inc
libmt19937_mt32.f:   libmt19937_mt32.f.tpl
libmt19937_mt32_r.f: libmt19937_mt32_r.f.tpl
libmt19937_mt64.f:   libmt19937_mt64.f.tpl
libmt19937_mt64_r.f: libmt19937_mt64_r.f.tpl
