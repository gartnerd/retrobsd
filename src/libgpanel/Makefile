TOPSRC          = $(shell cd ../..; pwd)
include $(TOPSRC)/target.mk

CFLAGS          += -O -Wall -Werror
MAN             = gpanel.0
MANSRC          = gpanel.3

CSRCS		= $(wildcard *.c)

OBJS		= $(patsubst %.c,%.o,$(CSRCS))

.PHONY:		all install clean

all:    	../libgpanel.a $(MAN)

../libgpanel.a: $(OBJS)
		@$(AR) cru $@ $(OBJS)
		$(RANLIB) $@

$(MAN):         $(MANSRC)
		$(MANROFF) $< > $@

install: 	all
		cp $(MAN) $(DESTDIR)/share/man/cat3/

clean:
		rm -f *.o a.out core test errs ../libgpanel*.a $(MAN)
