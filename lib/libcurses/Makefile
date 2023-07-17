TOPSRC		= $(shell cd ../..; pwd)

include $(TOPSRC)/target.mk

vpath %.c $(TOPSRC)/src/libcurses

CFLAGS		= -Os -B$(TOPSRC)/lib/ $(DEFS) -Wall -Werror

EXCLD_SRCS	= test.c

SRCS		= $(notdir $(wildcard $(TOPSRC)/src/libcurses/*.c))
FILT_SRCS	= $(filter-out $(EXCLD_SRCS),$(SRCS))

OBJS		= $(patsubst %.c,%.o,$(FILT_SRCS))

.PHONY:		all clean

all:            ../libcurses.a

../libcurses.a: ../ar ../ranlib $(OBJS)
		../ar rc $@ $(OBJS)
		../ranlib $@

clean:
		rm -f *~ *.o a.out *.a
