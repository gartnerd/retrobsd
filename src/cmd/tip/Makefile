TOPSRC          = $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	5.4.1	(2.11BSD)	1996/12/1
#
# make file for intermachine communications package
#
# Files are:
#	/etc/remote		remote host description file
#	/etc/phones		phone number file, owned by $(OWNER) and
#				  mode 6??
#	$(ADM)/aculog		ACU accounting file, owned by $(OWNER) and
#				  mode 6?? (if ACULOG defined)
# Presently supports:
#	BIZCOMP
#	DEC DF02-AC, DF03-AC
#	DEC DN-11/Able Quadracall
#	HAYES and Hayes emulators
#	PENRIL autodialer
#	USR COURIER (2400 baud)
#	VENTEL 212+
#	VADIC 831 RS232 adaptor
#	VADIC 3451
# (drivers are located in aculib.a)
#
# Configuration defines:
#	DF02, DF03, DN11	ACU's supported
#	  BIZ1031, BIZ1022, VENTEL, V831, V3451, HAYES, COURIER, PENRIL
#	ACULOG			turn on tip logging of ACU use
#	PRISTINE		no phone #'s put in ACU log file
#	CONNECT			worthless command
#	DEFBR			default baud rate to make connection at
#	DEFFS			default frame size for FTP buffering of
#				writes on local side
#	BUFSIZ			buffer sizing from stdio, must be fed
#				explicitly to remcap.c if not 1024
ADM     	= var/log
OWNER   	= uucp
GROUP   	= daemon
CONFIG  	= -DHAYES
LIBS    	+= -lacu -L./aculib
CFLAGS		+= -Wall -Werror
CPPFLAGS	+= -DDEFBR=1200 -DDEFFS=BUFSIZ -DACULOG -DPRISTINE 

SRCS		= $(wildcard *.c)
OBJS		= $(patsubst %.c,%.o,$(SRCS))

.PHONY:		all aculib clean depend install lint tags

all: 		aculib tip

tip:    	$(OBJS)
		$(CC) $(LDFLAGS) -o tip.elf $(OBJS) $(LIBS)
		$(OBJDUMP) -S tip.elf > tip.dis
		$(SIZE) tip.elf
		$(ELF2AOUT) tip.elf $@

# acutab is configuration dependent, and so depends on the makefile
acutab.o: 	Makefile
acutab.o: 	acutab.c
		$(CC) -c $(CPPFLAGS) $(CFLAGS) $(CONFIG) acutab.c

# remote.o depends on the makefile because of DEFBR and DEFFS
# log.o depends on the makefile because of ACULOG
log.o remote.o: Makefile

aculib: 
		$(MAKE) $(MFLAGS) -C aculib

clean: 
		rm -f $(OBJS) core tip tip.elf tip.dis
		$(MAKE) $(MFLAGS) -C aculib clean

depend: 
		mkdep $(CFLAGS) $(SRCS)
		cd aculib; $(MAKE) $(MFLAGS) depend

install: 	aculib tip
		cd aculib; $(MAKE) $(MFLAGS) install
		cp tip $(DESTDIR)/bin/tip
		rm -f $(DESTDIR)/bin/cu
		touch $(DESTDIR)/$(ADM)/aculog
		chmod 600 $(DESTDIR)/$(ADM)/aculog
		-mkdir -p $(DESTDIR)/var/lock
		@echo "create /etc/remote and /etc/phones"
		cp remote-file $(DESTDIR)/etc/remote
		cp phones-file $(DESTDIR)/etc/phones

lint:
		lint $(CFLAGS) $(SRCS)

tags:
		ctags $(SRCS)

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
