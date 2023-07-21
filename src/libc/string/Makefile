#
# This is the Makefile for the 'string' functions.  New routines ported from
# 4.4BSD's libc/string directory go here but existing libc/gen files are
# being left where they are.
#
TOPSRC		= $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

DEFS		=
CFLAGS		+= $(DEFS) -Os

SRCS		= $(wildcard *.c)
OBJS		= $(patsubst %.c,%.o,$(SRCS))

.PHONY:		all clean depend tags

all:		string.a

#DG - the archiver generates the following error message:
#DG - ar: `u' modifier ignored since `D' is the default (see `U')
#DG - setting the "U" flag should address this issue
string.a:	$(OBJS)
		@echo "building normal string.a"
		@ar cruU string.a $(OBJS)

clean:
		rm -f *.o *~ profiled/*.o tags Makefile.bak string.a string_p.a

#DG - there is no program named "mkdep" on my particular linux
#DG - installation - 5.15.0-76-generic. There is "mkdepend"
depend:		$(SRCS)
		mkdep $(CFLAGS) $(SRCS)

tags:
		cwd=`pwd`; \
		for i in $(SRCS); do \
			ctags -a -f $(TAGSFILE) $$cwd/$$i; \
		done

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
