#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
TOPSRC		= $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

SRCS		= $(wildcard *.c)

OBJS		= $(patsubst %.c,%.o,$(SRCS))

CFLAGS		+= $(DEFS) -Os

.PHONY:		tags clean depend

#DG - The archive generates the following error:
#DG - ar: `u' modifier ignored since `D' is the default (see `U')
#DG - according to the man page to override this default behaviour
#DG - we can specify "U" and this should bring things back to what they were
inet.a: 	$(OBJS)
		@echo "building inet.a"
		@ar cruU inet.a $(OBJS)

tags:
		cwd=`pwd`; \
		for i in $(SRCS); do \
			ctags -a -f $(TAGSFILE) $$cwd/$$i; \
		done

clean:
		rm -f *.a *~ *.o profiled/*.o errs a.out core tags Makefile.bak

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
