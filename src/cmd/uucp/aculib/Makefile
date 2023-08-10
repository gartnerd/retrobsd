#	Makefile	4.4	86/02/12

TOPSRC          = $(shell cd ../../../..; pwd)
include $(TOPSRC)/target.mk

DEBUG           =
CFLAGS          = -Os -Werror $(DEBUG)

SRCS		= $(wildcard *.c)

OBJS		= $(patsubst %.c,%.o,$(SRCS))

libacu.a: 	$(OBJS)
		$(AR) cr libacu.a $(OBJS)
		-$(RANLIB) libacu.a

$(OBJS):        ../uucp.h ../condevs.h

install:        libacu.a

clean:
		rm -f *.o core errs  libacu.a
