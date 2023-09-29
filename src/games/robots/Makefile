#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	@(#)Makefile	5.2 (Berkeley) 5/15/86
#
TOPSRC          = $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk
#include $(TOPSRC)/cross.mk
#CFLAGS  	= -O -DCROSS -g -DFANCY

CFLAGS  	+= -Werror -Wall
CPPFLAGS	+= -DMAX_PER_UID=5 

OBJS            = extern.o init_field.o main.o make_level.o move.o \
		  move_robs.o play_level.o query.o rnd_pos.o score.o \
		  flush_in.o
MAN             = robots.0
LIBS            = -lcurses -ltermcap -lc

.PHONY:		all clean install

all:            robots $(MAN)

robots:         $(OBJS)
		$(CC) $(LDFLAGS) -o $@.elf $(OBJS) $(LIBS)
		$(OBJDUMP) -S $@.elf > $@.dis
		$(SIZE) $@.elf
		$(ELF2AOUT) $@.elf $@ && rm $@.elf

$(OBJS):	robots.h

$(MAN):         robots.6
		nroff -man $< > $@

clean:
		rm -f *.o core robots *.0 *.dis

install:        all
		install robots $(DESTDIR)/games/
		install -m 644 $(MAN) $(DESTDIR)/share/man/cat6/
		install -c -m 644 /dev/null $(DESTDIR)/games/lib/robots_roll
