#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.3 2016/02/16 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include make.inc

.PHONY:
.PHONY: all clean clobber corelib default install install_src src test uninstall
#------------------------------------------------------------------------
default:     src
test:        src
all:         test
src:         corelib
install:     corelib
install_src: corelib

src test corelib:
	$(GMAKE) -C $@

install install_src uninstall:
	$(GMAKE) -C src  $@
	$(GMAKE) -C test $@

clean clobber:
	rm -f *.tgz
	$(GMAKE) -C src  $@
	$(GMAKE) -C test $@
