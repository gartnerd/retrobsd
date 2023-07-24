TOPSRC          = $(shell cd ../..; pwd)
include $(TOPSRC)/target.mk

CFLAGS          += -O -Wall -Werror

CSRCS		= $(wildcard *.c)

OBJS		= $(patsubst %.c,%.o,$(CSRCS))

.PHONY:		all install clean

all:    	../libwiznet.a

../libwiznet.a: $(OBJS)
		$(AR) cru $@ $(OBJS)
		$(RANLIB) $@

install: 	all

clean:
		rm -f *.o a.out core test errs ../libwiznet*.a
