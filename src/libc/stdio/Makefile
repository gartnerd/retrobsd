#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
TOPSRC		= $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

CFLAGS		+= $(DEFS) -Os

SRCS		= $(STDSRC) fgetc.c fgets.c fputc.c fputs.c gets.c puts.c \
                  feof.c ferror.c fileno.c

STDSRC		= clrerr.c doscan.c exit.c clnup.c fdopen.c filbuf.c findiop.c \
		  flsbuf.c fopen.c fprintf.c fread.c freopen.c fseek.c \
		  ftell.c fwrite.c getchar.c getw.c printf.c putchar.c putw.c \
		  rew.c scanf.c setbuf.c setbuffer.c setvbuf.c snprintf.c sprintf.c \
		  strout.c ungetc.c vfprintf.c vprintf.c vsprintf.c doprnt.c \
		  remove.c

TAGSFILE	= tags

SRC		= $(wildcard *.c)

#DG - eventhough clnup.c is listed in the source variables above
#DG - it is not included in the obj variables for some reason
OBJS		= $(filter-out clnup.o,$(patsubst %.c,%.o,$(SRC)))

.PHONY:		clean tags depend

#DG - the archiver generates the following error text
#DG - ar: `u' modifier ignored since `D' is the default (see `U')
#DG - this can be fixed by adding the "U" flag
stdio.a:	$(OBJS)
		@echo "building stdio.a"
		@ar cruU stdio.a $(OBJS)

tags:
		cwd=`pwd`; \
		for i in $(SRCS); do \
			ctags -a -f $(TAGSFILE) $$cwd/$$i; \
		done

clean:
		rm -f stdio.a *.o *~ profiled/*.o tags Makefile.bak

depend:
		for i in $(SRCS); do \
		    cc -M $(CFLAGS) $$i | awk ' { if ($$1 != prev) \
			{ if (rec != "") print rec; rec = $$0; prev = $$1; } \
			else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
			else rec = rec " " $$2 } } \
			END { print rec } ' >> makedep; done
		echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
		echo '$$r makedep' >>eddep
		echo 'w' >>eddep
		cp Makefile Makefile.bak
		ed - Makefile < eddep
		rm eddep makedep
		echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
		echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
		echo '# see make depend above' >> Makefile

# DO NOT DELETE THIS LINE -- make depend uses it
