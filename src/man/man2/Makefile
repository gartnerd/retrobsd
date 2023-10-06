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
#	@(#)Makefile	2.11 (2.11BSD) 2000/3/4
#
TOPSRC = $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

MDIR=	/share/man/cat2

SRCS=	$(wildcard *.2)
OBJS=	$(patsubst %.2,%.0,$(SRCS))

.SUFFIXES: .2 .0

.2.0:
	$(MANROFF) $*.2 > $*.0

.PHONY:	all clean install

all: _make_01

_make_01: $(OBJS)

clean:
	rm -f $(OBJS)

P=$(DESTDIR)$(MDIR)

install: _make_01
	cp $(OBJS) $(P)
	ln -f $(P)/dup.0 $(P)/dup2.0
	ln -f $(P)/brk.0 $(P)/sbrk.0
	ln -f $(P)/stat.0 $(P)/fstat.0
	ln -f $(P)/stat.0 $(P)/lstat.0
	ln -f $(P)/read.0 $(P)/readv.0
	ln -f $(P)/recv.0 $(P)/recvfrom.0
	ln -f $(P)/recv.0 $(P)/recvmsg.0
	ln -f $(P)/send.0 $(P)/sendmsg.0
	ln -f $(P)/send.0 $(P)/sendto.0
	ln -f $(P)/statfs.0 $(P)/fstatfs.0
	ln -f $(P)/wait.0 $(P)/wait3.0
	ln -f $(P)/wait.0 $(P)/wait4.0
	ln -f $(P)/wait.0 $(P)/waitpid.0
	ln -f $(P)/chmod.0 $(P)/fchdir.0
	ln -f $(P)/chflags.0 $(P)/fchflags.0
	ln -f $(P)/chmod.0 $(P)/fchmod.0
	ln -f $(P)/chown.0 $(P)/fchown.0
	ln -f $(P)/mount.0 $(P)/umount.0
	ln -f $(P)/select.0 $(P)/pselect.0
	ln -f $(P)/write.0 $(P)/writev.0
	ln -f $(P)/getpid.0 $(P)/getppid.0
	ln -f $(P)/truncate.0 $(P)/ftruncate.0
	ln -f $(P)/gethostid.0 $(P)/sethostid.0
	ln -f $(P)/getitimer.0 $(P)/setitimer.0
	ln -f $(P)/getrlimit.0 $(P)/setrlimit.0
	ln -f $(P)/getsockopt.0 $(P)/setsockopt.0
	ln -f $(P)/gethostname.0 $(P)/sethostname.0
	ln -f $(P)/getpriority.0 $(P)/setpriority.0
	ln -f $(P)/gettimeofday.0 $(P)/settimeofday.0
	ln -f $(P)/getlogin.0 $(P)/setlogin.0
	ln -f $(P)/getuid.0 $(P)/geteuid.0
	ln -f $(P)/getgid.0 $(P)/getegid.0
	ln -f $(P)/setuid.0 $(P)/setgid.0
	ln -f $(P)/setuid.0 $(P)/seteuid.0
	ln -f $(P)/setuid.0 $(P)/setegid.0
