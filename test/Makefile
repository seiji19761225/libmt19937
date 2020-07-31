#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.4 2014/11/28 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include ../make.inc

.PHONY: default clean clobber install uninstall verify

D_TESTS	= \
mt32_dist_test  \
mt64_dist_test
V_TESTS	= \
mt19937ar_test   mt32_test  mt32_r_test  \
mt19937-64_test  mt64_test  mt64_r_test
TESTS	= $(D_TESTS) $(V_TESTS)
#-----------------------------------------------------------------------
#defaults
CONFIG	= ../src/config.mk
PREFIX	= $(shell grep ^PREFIX  $(CONFIG) | tail -1 | awk '{printf $$3;}')
LIBNAME	= $(shell grep ^LIBNAME $(CONFIG) | tail -1 | awk '{printf $$3;}')
#
FILES	= $(shell find . -type f | grep -v -e Makefile -e RCS | sort)
SRCPATH	= $(PREFIX)/$(SRCDIR)/lib$(LIBNAME)/test
#.......................................................................
CPREFIX	= ../src
CFLAGS	+= -I$(CPREFIX)/$(INCDIR)
LIBS	+= -L$(CPREFIX)/$(LIBDIR) -l$(LIBNAME) -lm
#-----------------------------------------------------------------------
default: all
all:     $(TESTS)
#	@ls -l $^

verify:  $(V_TESTS)
	@echo -e "    ***** VERIFICATION *****"; \
	for test in $^; do \
	    ./$$test | diff reference_outputs/$${test}.out - > /dev/null 2>&1; \
	    if [ $$? == 0 ]; then \
		printf "%-16s: --- PASSED ---\n" $$test; \
	    else \
		printf "%-16s: >>> FAILED <<<\n" $$test; \
	    fi \
	done

$(TESTS):
	$(CC) $(CFLAGS) $(PFLAGS) -o $@ $^ $(LIBS)

install:
	mkdir -p  $(SRCPATH)
	tar -cf - $(FILES) | tar -C $(SRCPATH) -xf -

uninstall:
	rm -rf $(SRCPATH)

clean clobber:
	rm -f $(strip $(TESTS)) *.o *~ core*
	rm -f *.dmp
#-----------------------------------------------------------------------
# dependencies
# distribution tests
mt32_dist_test:  mt32_dist_test.c
mt64_dist_test:  mt64_dist_test.c
# verification tests
mt19937ar_test:  mt19937ar_test.c
mt32_test:       mt32_test.c
mt32_r_test:     mt32_r_test.c
mt19937-64_test: mt19937-64_test.c
mt64_test:       mt64_test.c
mt64_r_test:     mt64_r_test.c
