#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
# makefile
# $Id: Makefile,v 1.1.1.6 2016/02/16 00:00:00 seiji Exp seiji $
#=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
include ../make.inc
include ./config.mk

.PHONY: clean clobber default install uninstall
#------------------------------------------------------------------------
# modules
#........................................................................
# mt32    module (32bit)
MT32_DIR	= mt32
MT32_SRC	= \
mt32_genrand_exp.c    mt32_genrand_gamma.c   mt32_genrand_geometric.c  \
mt32_genrand_int31.c  mt32_genrand_normal.c  mt32_genrand_poisson.c    \
mt32_genrand_real1.c  mt32_genrand_real2.c   mt32_genrand_real3.c      \
mt32_genrand_res53.c  mt32_load_state.c      mt32_save_state.c
ifeq ($(COK),yes)
MT32_SRC	+= mt32_kernel_cok.c
else
MT32_SRC	+= mt32_kernel_org.c
endif
MT32_HDR	= $(MT32_DIR)/mt32.h $(MT32_DIR)/mt19937ar.h
#........................................................................
# mt32_r  module (32bit reentrant)
MT32R_DIR	= mt32_r
MT32R_SRC	= \
mt32_r_genrand_exp.c      mt32_r_genrand_gamma.c  mt32_r_genrand_geometric.c  \
mt32_r_genrand_int31.c    mt32_r_genrand_int32.c  mt32_r_genrand_normal.c     \
mt32_r_genrand_poisson.c  mt32_r_genrand_real1.c  mt32_r_genrand_real2.c      \
mt32_r_genrand_real3.c    mt32_r_genrand_res53.c  mt32_r_init.c               \
mt32_r_init_by_array.c    mt32_r_load_context.c   mt32_r_load_context_fp.c    \
mt32_r_save_context.c     mt32_r_save_context_fp.c
ifeq ($(COK),yes)
MT32R_SRC	+= mt32_r_next_state.c
endif
MT32R_HDR	= mt32_r.h
#........................................................................
# mt64    module (64bit)
MT64_DIR	= mt64
MT64_SRC	= \
mt64_genrand_exp.c    mt64_genrand_gamma.c   mt64_genrand_geometric.c  \
mt64_genrand_int63.c  mt64_genrand_normal.c  mt64_genrand_poisson.c    \
mt64_genrand_real1.c  mt64_genrand_real2.c   mt64_genrand_real3.c      \
mt64_load_state.c     mt64_save_state.c
ifeq ($(COK),yes)
MT64_SRC	+= mt64_kernel_cok.c
else
MT64_SRC	+= mt64_kernel_org.c
endif
MT64_HDR	= $(MT64_DIR)/mt64.h $(MT64_DIR)/mt19937-64.h
#........................................................................
# mt64_r  module (64bit reentrant)
MT64R_DIR	= mt64_r
MT64R_SRC	= \
mt64_r_genrand_exp.c      mt64_r_genrand_gamma.c    mt64_r_genrand_geometric.c  \
mt64_r_genrand_int63.c    mt64_r_genrand_int64.c    mt64_r_genrand_normal.c     \
mt64_r_genrand_poisson.c  mt64_r_genrand_real1.c    mt64_r_genrand_real2.c      \
mt64_r_genrand_real3.c    mt64_r_init.c             mt64_r_init_by_array.c      \
mt64_r_load_context.c     mt64_r_load_context_fp.c  mt64_r_save_context.c       \
mt64_r_save_context_fp.c
ifeq ($(COK),yes)
MT64R_SRC	+= mt64_r_next_state.c
endif
MT64R_HDR	= mt64_r.h
#........................................................................
# mt_dist module (framework of distributed RNG)
MTDIST_DIR	= mt_dist
MTDIST_SRC	= \
mt_genrand_exp.c     mt_genrand_gamma.c    mt_genrand_geometric.c  \
mt_genrand_normal.c  mt_genrand_poisson.c
#........................................................................
DIRS	= $(MT32_DIR) $(MT32R_DIR) $(MT64_DIR) $(MT64R_DIR) $(MTDIST_DIR)
SRCS	= $(MT32_SRC) $(MT32R_SRC) $(MT64_SRC) $(MT64R_SRC) $(MTDIST_SRC)
HEADERS	= $(MT32_HDR) $(MT32R_HDR) $(MT64_HDR) $(MT64R_HDR)
#------------------------------------------------------------------------
# auto-config.
VERSION	= 1.1.1
LIB_A	= lib$(LIBNAME).a
LIB_S	= lib$(LIBNAME).so.1.1.1
SONAME	= lib$(LIBNAME).so.1
LD_MAP	= lib$(LIBNAME).map
#
LIBPATH	= $(PREFIX)/$(LIBDIR)
INCPATH	= $(PREFIX)/$(INCDIR)/lib$(LIBNAME)
#........................................................................
TARGET	= $(LIB_A)

CFLAGS	+= -I. -I./include -I./mt_dist

ifeq ($(BUILD),product)
PFLAGS	+= -DNDEBUG
else
ifeq ($(BUILD),debug)
PFLAGS	+= -DDEBUG
endif
endif

ifeq ($(COK),yes)
COK_KERNEL	= 1
else
COK_KERNEL	= 0
endif

ifeq ($(INLINE),yes)
PFLAGS	+= -DUSE_INLINED_GENERATOR
endif

ifneq ($(SHARED),no)
MAJOR	= $(shell echo $(SHARED) | awk 'BEGIN{FS="."}; {print $$1}')
MINOR	= $(shell echo $(SHARED) | awk 'BEGIN{FS="."}; {print $$2}')
ifneq ($(MAJOR),)
ifneq ($(MINOR),)
VERSION	= $(SHARED)
SONAME	= lib$(LIBNAME).so.$(MAJOR)
LIB_S	= lib$(LIBNAME).so.$(VERSION)
endif
endif
TARGET	+= $(LIB_S)
endif

LIBS	+= -lm
#........................................................................
OBJS	= $(strip $(subst .c,.o,$(SRCS)))
#........................................................................
VPATH	= $(DIRS)
#------------------------------------------------------------------------
default:  $(TARGET)
	@ls -l $^

$(LIB_A): $(OBJS)
	$(AR) $@ $^
ifneq  ($(RANLIB),)
	$(RANLIB) $@
endif

$(LIB_S): $(OBJS) $(LD_MAP)
	$(CC) -shared -o $@ -Wl,-soname,$(SONAME) -Wl,--version-script,$(LD_MAP) $(OBJS) $(LIBS)
#........................................................................
install:  $(TARGET) $(HEADERS)
	mkdir -p   $(LIBPATH) $(INCPATH)
	$(INSTALL) $(M644) $(HEADERS) $(INCPATH)
	$(INSTALL) $(M644) $(LIB_A)   $(LIBPATH)
ifneq  ($(SHARED),no)
	$(INSTALL) $(M755) $(LIB_S)   $(LIBPATH)
	cd $(LIBPATH); rm -f $(SONAME)       ; ln -s $(LIB_S) $(SONAME)
	cd $(LIBPATH); rm -f lib$(LIBNAME).so; ln -s $(LIB_S) lib$(LIBNAME).so
endif
	$(GMAKE) -C man $@

uninstall:
	rm -f  $(LIBPATH)/lib$(LIBNAME)*
	rm -rf $(INCPATH)
	$(GMAKE) -C man $@

clean:
	rm -f $(TARGET) $(LD_MAP) *.o *.h *~ core*
clobber: clean uninstall
#........................................................................
# auto-generation
mt32_r.h mt64_r.h:
	sed -e "s/__COK_KERNEL__/$(COK_KERNEL)/g"          < $< > $@
$(LD_MAP): linker_map.tpl
	sed -e "s/__LIBNAME__/lib$(LIBNAME)_v$(VERSION)/g" < $< > $@
#........................................................................
# dependencies
#........................................................................
$(OBJS): ../make.inc config.mk
#........................................................................
mt32_r.h: mt32_r.h.tpl
mt64_r.h: mt64_r.h.tpl
#........................................................................
#mt32     module
$(subst .c,.o,$(MT32_SRC)):   mt32.h
# mt32_r  module
$(subst .c,.o,$(MT32R_SRC)):  mt32_r.h
#mt64     module
$(subst .c,.o,$(MT64_SRC)):   mt64.h
# mt64_r  module
$(subst .c,.o,$(MT64R_SRC)):  mt64_r.h
# mt_dist module
$(subst .c,.o,$(MTDIST_SRC)): mt_dist.h
#........................................................................
