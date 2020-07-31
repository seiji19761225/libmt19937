#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.3 2016/02/16 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include ../../make.inc

.PHONY: default clean clobber install uninstall
#-----------------------------------------------------------------------
# modules
#........................................................................
# mt32   module
MT32_DIR	= mt32
MT32_MAN	= \
genrand_int31.l       genrand_int32.l           genrand_real1.l         \
genrand_real2.l       genrand_real3.l           genrand_res53.l         \
init_by_array.l       init_genrand.l            mt19937.l               \
mt19937ar.l           mt32.l                    mt32_genrand_exp.l      \
mt32_genrand_gamma.l  mt32_genrand_geometric.l  mt32_genrand_int31.l    \
mt32_genrand_int32.l  mt32_genrand_normal.l     mt32_genrand_poisson.l  \
mt32_genrand_real1.l  mt32_genrand_real2.l      mt32_genrand_real3.l    \
mt32_genrand_res53.l  mt32_init.l               mt32_init_by_array.l    \
mt32_load_state.l     mt32_load_state_fp.l      mt32_save_state.l       \
mt32_save_state_fp.l
#........................................................................
# mt32_r module
MT32R_DIR	= mt32_r
MT32R_MAN	= \
mt32_context_t.l          mt32_r.l                    mt32_r_genrand_exp.l      \
mt32_r_genrand_gamma.l    mt32_r_genrand_geometric.l  mt32_r_genrand_int31.l    \
mt32_r_genrand_int32.l    mt32_r_genrand_normal.l     mt32_r_genrand_poisson.l  \
mt32_r_genrand_real1.l    mt32_r_genrand_real2.l      mt32_r_genrand_real3.l    \
mt32_r_genrand_res53.l    mt32_r_init.l               mt32_r_init_by_array.l    \
mt32_r_load_context.l     mt32_r_load_context_fp.l    mt32_r_save_context.l     \
mt32_r_save_context_fp.l
#........................................................................
# mt64   module
MT64_DIR	= mt64
MT64_MAN	= \
genrand64_int63.l       genrand64_int64.l     genrand64_real1.l         \
genrand64_real2.l       genrand64_real3.l     init_by_array64.l         \
init_genrand64.l        mt19937-64.l          mt64.l                    \
mt64_genrand_exp.l      mt64_genrand_gamma.l  mt64_genrand_geometric.l  \
mt64_genrand_int63.l    mt64_genrand_int64.l  mt64_genrand_normal.l     \
mt64_genrand_poisson.l  mt64_genrand_real1.l  mt64_genrand_real2.l      \
mt64_genrand_real3.l    mt64_init.l           mt64_init_by_array.l      \
mt64_load_state.l       mt64_load_state_fp.l  mt64_save_state.l         \
mt64_save_state_fp.l
#........................................................................
# mt64_r module
MT64R_DIR	= mt64_r
MT64R_MAN	= \
mt64_context_t.l          mt64_r.l                    mt64_r_genrand_exp.l      \
mt64_r_genrand_gamma.l    mt64_r_genrand_geometric.l  mt64_r_genrand_int63.l    \
mt64_r_genrand_int64.l    mt64_r_genrand_normal.l     mt64_r_genrand_poisson.l  \
mt64_r_genrand_real1.l    mt64_r_genrand_real2.l      mt64_r_genrand_real3.l    \
mt64_r_init.l             mt64_r_init_by_array.l      mt64_r_load_context.l     \
mt64_r_load_context_fp.l  mt64_r_save_context.l       mt64_r_save_context_fp.l
#........................................................................
DIRS	= $(MT32_DIR) $(MT32R_DIR) $(MT64_DIR) $(MT64R_DIR)
MANS	= $(MT32_MAN) $(MT32R_MAN) $(MT64_MAN) $(MT64R_MAN)
#-----------------------------------------------------------------------
#defaults
PREFIX	= $(shell grep ^PREFIX ../config.mk | tail -1 | awk '{printf $$3;}')
#.......................................................................
# destination directory
DESTDIR	= $(PREFIX)/$(MANDIR)
#-----------------------------------------------------------------------
default:

install:
	mkdir -p $(DESTDIR)/manl
	cd $(MT32_DIR) ; $(INSTALL) $(M644) $(strip $(MT32_MAN))  $(DESTDIR)/manl
	cd $(MT32R_DIR); $(INSTALL) $(M644) $(strip $(MT32R_MAN)) $(DESTDIR)/manl
	cd $(MT64_DIR) ; $(INSTALL) $(M644) $(strip $(MT64_MAN))  $(DESTDIR)/manl
	cd $(MT64R_DIR); $(INSTALL) $(M644) $(strip $(MT64R_MAN)) $(DESTDIR)/manl

uninstall:
	if [ -d $(DESTDIR)/manl ]; then cd $(DESTDIR)/manl; rm -f $(strip $(MANS)); fi

update_db:
	if [ -x "`which mandb      2> /dev/null`" ]; then mandb      -q   $(DESTDIR); fi
	if [ -x "`which makewhatis 2> /dev/null`" ]; then makewhatis -s l $(DESTDIR); fi
