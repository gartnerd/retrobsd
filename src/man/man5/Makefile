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
#	@(#)Makefile	5.4.3 (2.11BSD GTE) 1996/3/20
#
TOPSRC = $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

MDIR=	/share/man/cat5
SRCS=	$(wildcard *.5)
OBJS=	$(patsubst %.5,%.0,$(SRCS))

.SUFFIXES: .5 .0

.5.0:
	$(MANROFF) $*.5 > $*.0

.PHONY:	all clean install

all: _make_01

_make_01: $(OBJS)

clean: 
	rm -f $(OBJS)

install: _make_01
	cp $(OBJS) $(DESTDIR)$(MDIR)
	ln -f $(DESTDIR)$(MDIR)/fs.0 $(DESTDIR)$(MDIR)/inode.0
	ln -f $(DESTDIR)$(MDIR)/dump.0 $(DESTDIR)$(MDIR)/dumpdates.0
	ln -f $(DESTDIR)$(MDIR)/utmp.0 $(DESTDIR)$(MDIR)/wtmp.0
