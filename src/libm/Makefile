TOPSRC		= $(shell cd ../..; pwd)
include $(TOPSRC)/target.mk

CFLAGS          += $(DEFS) -Werror -Wall

#DG - Note: the files assigned to "SRCS" don't appear in this dir
SRCS            = login.c logout.c logwtmp.c

#DG- fabs.c is not part of the original set of files built for the lib
EXCLDOBJS	= fabs.o

ALLOBJS		= $(patsubst %.c,%.o,$(wildcard *.c))
OBJS		= $(filter-out $(EXCLDOBJS),$(ALLOBJS))

.PHONY:		all install clean cleandir depend tags

all:            ../libm.a

../libm.a:	$(OBJS)
		$(AR) cru $@ $(OBJS)
		$(RANLIB) $@

install:	all
#		$(INSTALLDIR) $(DESTDIR)/lib
#		$(INSTALL) ../libm.a $(DESTDIR)/lib/libm.a
#		$(RANLIB) $(DESTDIR)/lib/libm.a

clean:
		rm -f ../libm.a *.o *~ tags

cleandir:       clean
		rm -f .depend

depend:
		mkdep $(CFLAGS) $(SRCS)

tags:
		ctags $(SRCS)
