#
# This is the Makefile for 'stdlib'.  New routines ported from 4.4BSD's
# libc/stdlib directory go here but existing libc/gen files are being left
# where they are.
#
TOPSRC		= $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

DEFS		=
CFLAGS		+= $(DEFS) -Os

SRCS		= $(wildcard *.c)

OBJS		= $(patsubst %.c,%.o,$(SRCS))

.PHONY:		all clean depend tags

all:		stdlib.a

#DG - The archive program generates the following error
#DG - ar: `u' modifier ignored since `D' is the default (see `U')
#DG - setting the "U" flag should remove the error
stdlib.a:	$(OBJS)
		@echo "building stdlib"
		@ar cruU stdlib.a $(OBJS)

clean:
		rm -f *.o *~ profiled/*.o tags Makefile.bak stdlib.a stdlib_p.s

depend:		$(SRCS)
		mkdep $(CFLAGS) $(SRCS)

tags:
		cwd=`pwd`; \
		for i in $(SRCS); do \
			ctags -a -f $(TAGSFILE) $$cwd/$$i; \
		done

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
