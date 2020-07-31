#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.3 2016/02/16 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include make.inc

.PHONY:
.PHONY: benchmark clean clobber default install src test uninstall
#------------------------------------------------------------------------
default:        src
benchmark test: src
all: benchmark test

benchmark src test:
	$(GMAKE) -C $@

install uninstall:
	$(GMAKE) -C src  $@
	$(GMAKE) -C test $@
	$(GMAKE) -C benchmark $@

clean clobber:
	rm -f *.tgz
	$(GMAKE) -C src  $@
	$(GMAKE) -C test $@
	$(GMAKE) -C benchmark $@
#------------------------------------------------------------------------
-include addon.mk
