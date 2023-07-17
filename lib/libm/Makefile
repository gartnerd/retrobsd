TOPSRC          = $(shell cd ../..; pwd)

include $(TOPSRC)/target.mk

vpath %.c $(TOPSRC)/src/libm

CFLAGS          = -Os -B$(TOPSRC)/lib/ $(DEFS) -Wall -Werror

SRCS		= $(notdir $(wildcard $(TOPSRC)/src/libm/*.c))
EXCLD_SRCS	= fabs.c
FILT_SRCS	= $(filter-out $(EXCLD_SRCS),$(SRCS))

OBJS		= $(patsubst %.c,%.o,$(FILT_SRCS))

.PHONY:		all clean

all:            ../libm.a

../libm.a: 	../ar ../ranlib $(OBJS)
		../ar rc $@ $(OBJS)
		../ranlib $@

clean:
		rm -f *~ *.o a.out *.a
