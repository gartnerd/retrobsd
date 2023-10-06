#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.
#
# Redistribution and use in source and binary forms are permitted
# provided that the above copyright notice and this paragraph are
# duplicated in all such forms and that any documentation,
# advertising materials, and other materials related to such
# distribution and use acknowledge that the software was developed
# by the University of California, Berkeley.  The name of the
# University may not be used to endorse or promote products derived
# from this software without specific prior written permission.
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
#
#	@(#)Makefile	5.4.7 (2.11BSD) 1997/1/10
#
TOPSRC = $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

MDIR=	/share/man/cat8
SRCS=	$(wildcard *.8)
OBJS=	$(patsubst %.8,%.0,$(SRCS))

.PHONY:	   all clean install
.SUFFIXES: .8 .0

.8.0:
	$(MANROFF) $*.8 > $*.0

all: _make_01

_make_01: $(OBJS)

clean:
	rm -f $(OBJS)

install: _make_01
	cp $(OBJS) $(DESTDIR)$(MDIR)
	ln -f $(DESTDIR)$(MDIR)/uucico.0 $(DESTDIR)$(MDIR)/uucpd.0
