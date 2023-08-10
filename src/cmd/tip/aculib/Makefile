TOPSRC          = $(shell cd ../../../..; pwd)
include $(TOPSRC)/target.mk

#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	5.3.2	(2.11BSD GTE)	1996/12/1
#
# make file for tip device drivers
#
# Current drivers:
#	BIZCOMP
#	USR COURIER (2400 baud)
#	DEC DF02-AC, DF03-AC
#	DEC DN-11/Able Quadracall
#	HAYES and Hayes emulators
#	PENRIL auto-dialer
#	VENTEL 212+ (w/o echo)
#	VADIC 831 RS232 adaptor
#	VADIC 3451
CFLAGS  += -I.. -Wall -Werror 

SRCS =  $(wildcard *.c)
OBJS =  $(patsubst %.c,%.o,$(SRCS))

.PHONY:	all clean depend lint tags install

all: libacu.a

libacu.a: $(OBJS)
	$(AR) -rc libacu.a $(OBJS)
	$(RANLIB) libacu.a

clean: 
	rm -f $(OBJS) core libacu.a

depend: 
	mkdep $(CFLAGS) $(SRCS)

lint: 
	lint $(CFLAGS) $(SRCS)

tags: 
	ctags $(SRCS)

install:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
