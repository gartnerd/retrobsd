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
#	@(#)Makefile	5.4.3 (2.11BSD) 1997/5/31
#
TOPSRC = $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

MDIR=	$(DESTDIR)/share/man/cat4

SRCS= 	$(wildcard *.4)
OBJS=	$(patsubst %.4,%.0,$(SRCS))

.SUFFIXES: .4 .0

.4.0:
	$(MANROFF) $*.4 > $*.0

.PHONY:	all clean install

all: $(OBJS)

clean: 
	rm -f $(OBJS)

install: all
	cp $(OBJS) $(MDIR)
	ln -f $(MDIR)/xp.0 $(MDIR)/dvhp.0
	ln -f $(MDIR)/xp.0 $(MDIR)/hp.0
	ln -f $(MDIR)/xp.0 $(MDIR)/rm.0
	ln -f $(MDIR)/xp.0 $(MDIR)/rp.0
	ln -f $(MDIR)/mem.0 $(MDIR)/kmem.0
	ln -f $(MDIR)/fd.0 $(MDIR)/stdin.0
	ln -f $(MDIR)/fd.0 $(MDIR)/stderr.0
	ln -f $(MDIR)/fd.0 $(MDIR)/stdout.0
