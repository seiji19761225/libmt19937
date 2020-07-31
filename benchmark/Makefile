#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.2 2014/11/28 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include ../make.inc

.PHONY: default clean clobber install uninstall

BINS	= \
mt32_benchmark  mt32_r_benchmark  \
mt64_benchmark  mt64_r_benchmark  \
rand_benchmark  rand_r_benchmark
OBJS	= wtime.o
#-----------------------------------------------------------------------
#defaults
CONFIG	= ../src/config.mk
PREFIX	= $(shell grep ^PREFIX  $(CONFIG) | tail -1 | awk '{printf $$3;}')
LIBNAME	= $(shell grep ^LIBNAME $(CONFIG) | tail -1 | awk '{printf $$3;}')
#
FILES	= $(shell find . -type f | grep -v -e Makefile -e RCS | sort)
SRCPATH	= $(PREFIX)/$(SRCDIR)/lib$(LIBNAME)/benchmark
#.......................................................................
CPREFIX	= ../src
CFLAGS	+= -I$(CPREFIX)/$(INCDIR)
LIBS	+= -L$(CPREFIX)/$(LIBDIR) -l$(LIBNAME)
#-----------------------------------------------------------------------
default: $(BINS)
#	@ls -l $^

$(BINS):
	$(CC) $(CFLAGS) $(PFLAGS) -o $@ $^ $(LIBS)

install:
	mkdir -p  $(SRCPATH)
	tar -cf - $(FILES) | tar -C $(SRCPATH) -xf -

uninstall:
	rm -rf $(SRCPATH)

clean clobber:
	rm -f $(strip $(BINS)) *.o *~ core*
#-----------------------------------------------------------------------
# dependencies
wtime.o: wtime.h
#.......................................................................
mt32_benchmark:   mt32_benchmark.c   $(OBJS)
mt32_r_benchmark: mt32_r_benchmark.c
mt64_benchmark:   mt64_benchmark.c   $(OBJS)
mt64_r_benchmark: mt64_r_benchmark.c
rand_benchmark:   rand_benchmark.c   $(OBJS)
rand_r_benchmark: rand_r_benchmark.c
