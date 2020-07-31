#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.1 2014/11/18 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include ../make.inc

.PHONY: default clean clobber verification

BINS	= \
mt32_test  mt32_r_test  \
mt64_test  mt64_r_test
#-----------------------------------------------------------------------
#defaults
CONFIG	= ../src/config.mk
PREFIX	= $(shell grep ^PREFIX  $(CONFIG) | tail -1 | awk '{printf $$3;}')
LIBNAME	= $(shell grep ^LIBNAME $(CONFIG) | tail -1 | awk '{printf $$3;}')
#
FILES	= $(shell find . -type f | grep -v -e Makefile -e RCS | sort)
SRCPATH	= $(PREFIX)/$(SRCDIR)/lib$(LIBNAME)/fortran/test
#.......................................................................
CPREFIX	= ../../../src
FPREFIX	= ../src
FFLAGS	+= -I$(FPREFIX)/$(INCDIR)/lib$(LIBNAME)
LIBS	+= -L$(FPREFIX)/$(LIBDIR) -l$(LIBNAME)_fortran -L$(CPREFIX)/$(LIBDIR) -l$(LIBNAME)
#-----------------------------------------------------------------------
default: verification

verification: $(BINS)
#	@ls -l $^
	@echo -e "    ***** VERIFICATION *****"; \
	for bin in $^; do \
	    ./$$bin | diff reference_outputs/$${bin}.out - > /dev/null 2>&1; \
	    if [ $$? == 0 ]; then \
		printf "%-16s: --- PASSED ---\n" $$bin; \
	    else \
		printf "%-16s: >>> FAILED <<<\n" $$bin; \
	    fi \
	done

$(BINS): $(FPREFIX)/$(LIBDIR)/lib$(LIBNAME)_fortran.a \
	 $(CPREFIX)/$(LIBDIR)/lib$(LIBNAME).a
	$(FC) $(FFLAGS) -o $@ $@.f $(LIBS)

install install_src:
	mkdir -p  $(SRCPATH)
	tar -cf - $(FILES) | tar -C $(SRCPATH) -xf -

uninstall:
	rm -rf $(SRCPATH)

clean clobber:
	rm -f $(strip $(BINS)) *.o *~ core*
	rm -f *.dmp
#-----------------------------------------------------------------------
# dependencies
mt32_test:   mt32_test.f
mt32_r_test: mt32_r_test.f
mt64_test:   mt64_test.f
mt64_r_test: mt64_r_test.f
