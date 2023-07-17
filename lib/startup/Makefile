#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	crt0	Normal C run time startoff
#
TOPSRC          = $(shell cd ../..; pwd)
include $(TOPSRC)/target.mk

vpath %.c $(TOPSRC)/src/startup-mips

#DG - according to the GNU assembler manual the flag
#DG - combination -W,-x is not valid, or at least it doesn't
#DG - specify a defined action
#DG - 
#DG - The parent Makefile defines a CFLAGS var
#DG - but it appears to get overwritten by the one defined 
#DG - in this file
#CFLAGS          = -Os -B$(TOPSRC)/lib/ -Wa,-x $(DEFS)

CFLAGS          = -Os -B$(TOPSRC)/lib/ $(DEFS)

OBJS		= ../crt0.o

.PHONY:		all clean

all:		$(OBJS)

../crt0.o:	crt0.c
		$(CC) $(DEFS) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS) *~
