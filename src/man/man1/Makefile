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
#	@(#)Makefile	1.9 (2.11BSD) 1998/1/24
#
TOPSRC = $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

MDIR=	/share/man/cat1

#DG - There may be some reason (historical?) why the sources and objects were
#DG - split into two groups. I've consolidated them into one group
SRCS=	$(wildcard *.1)
OBJS=	$(patsubst %.1,%.0,$(SRCS))

.SUFFIXES: .1 .0

.1.0:
	$(MANROFF) $*.1 > $*.0

.PHONY:	all clean

all: _make_01

_make_01: $(OBJS)

eqn.0:
	eqn eqn.1 | $(MANROFF) > $@

clean:
	rm -f $(OBJS)

install: _make_01
	cp $(OBJS) $(DESTDIR)$(MDIR)
	ln -f $(DESTDIR)/$(MDIR)/sh.0 $(DESTDIR)$(MDIR)/case.0
	ln -f $(DESTDIR)/$(MDIR)/eqn.0 $(DESTDIR)$(MDIR)/checkeq.0
	ln -f $(DESTDIR)$(MDIR)/tip.0 $(DESTDIR)$(MDIR)/cu.0
	ln -f $(DESTDIR)$(MDIR)/diff.0 $(DESTDIR)$(MDIR)/diffh.0
	ln -f $(DESTDIR)$(MDIR)/ex.0 $(DESTDIR)$(MDIR)/edit.0
	ln -f $(DESTDIR)$(MDIR)/grep.0 $(DESTDIR)$(MDIR)/egrep.0
	ln -f $(DESTDIR)$(MDIR)/diction.0 $(DESTDIR)$(MDIR)/explain.0
	ln -f $(DESTDIR)$(MDIR)/grep.0 $(DESTDIR)$(MDIR)/fgrep.0
	ln -f $(DESTDIR)$(MDIR)/sh.0 $(DESTDIR)$(MDIR)/for.0
	ln -f $(DESTDIR)$(MDIR)/sh.0 $(DESTDIR)$(MDIR)/if.0
	ln -f $(DESTDIR)$(MDIR)/lookbib.0 $(DESTDIR)$(MDIR)/indxbib.0
	ln -f $(DESTDIR)$(MDIR)/eqn.0 $(DESTDIR)$(MDIR)/neqn.0
	ln -f $(DESTDIR)$(MDIR)/nice.0 $(DESTDIR)$(MDIR)/nohup.0
	ln -f $(DESTDIR)$(MDIR)/more.0 $(DESTDIR)$(MDIR)/page.0
	ln -f $(DESTDIR)$(MDIR)/spell.0 $(DESTDIR)$(MDIR)/spellin.0
	ln -f $(DESTDIR)$(MDIR)/spell.0 $(DESTDIR)$(MDIR)/spellout.0
	ln -f $(DESTDIR)$(MDIR)/compress.0 $(DESTDIR)$(MDIR)/uncompress.0
	ln -f $(DESTDIR)$(MDIR)/expand.0 $(DESTDIR)$(MDIR)/unexpand.0
	ln -f $(DESTDIR)$(MDIR)/uuencode.0 $(DESTDIR)$(MDIR)/uudecode.0
	ln -f $(DESTDIR)$(MDIR)/sh.0 $(DESTDIR)$(MDIR)/while.0
	ln -f $(DESTDIR)$(MDIR)/compress.0 $(DESTDIR)$(MDIR)/zcat.0
