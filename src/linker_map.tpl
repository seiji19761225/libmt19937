#=======================================================================
# linker_map.tpl: version script for GNU ld
# (c)2015 Seiji Nishimura
# $Id: linker_map.tpl,v 1.1.1.2 2016/02/16 00:00:00 seiji Exp seiji $
#=======================================================================

__LIBNAME__ {
    global:
        mt32_*;
        mt64_*;
    local:   *;
};
