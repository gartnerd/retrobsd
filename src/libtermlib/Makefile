#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#

#DG - I removed some code that looked like it was intended to
#DG - create profiled images of the listed source files
#DG - It appears to be (possibly) historical cruft
#DG - It's unfortunate that there is a directory and a file named termcap
#DG - termcap.c gets built when the libtermcap.a target is invoked
#DG - the directory "termcap" is triggerred since it's a prereq for "all"
TOPSRC          = $(shell cd ../..; pwd)
include $(TOPSRC)/target.mk

DEFS    = -DNOSCCS
CFLAGS  = -O -DCM_N -DCM_GT -DCM_B -DCM_D $(DEFS) -Wall -Werror
LD      = $(CC)

#DG - tc*.c appear to be files to test terminal func
TSRCS	= tc1.c tc2.c tc3.c

ALLSRCS	= $(wildcard *.c)
SRCS	= $(filter-out $(TSRCS),$(ALLSRCS))

OBJS	= $(patsubst %.c,%.o,$(SRCS))

TAGSFILE= tags

.PHONY: termcap

all:    ../libtermcap.a termcap

termcap:
	$(MAKE) -C $@

../libtermcap.a: $(OBJS)
	$(AR) cr ../libtermcap.a $(OBJS)

install: all
	$(MAKE) -C termcap install

tags:
	cwd=`pwd`; \
	for i in $(SRCS); do \
		ctags -a -f $(TAGSFILE) $$cwd/$$i; \
	done

clean:
	-rm -f *.o 
	-rm -f ../libtermcap.a ../libtermcap_p.a
	-rm -f termcap/termcap
