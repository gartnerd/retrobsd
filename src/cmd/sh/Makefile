TOPSRC		= $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

vpath %.h .

SRCS		= $(wildcard *.c)
EXCLDSRCS	= profile.c trace.c
FLTSRCS		= $(filter-out $(EXCLDSRCS),$(SRCS))

OBJS		= $(patsubst %.c,%.o,$(FLTSRCS))

.PHONY:		all install clean

all:		sh

sh:		$(OBJS)
		$(CC) $(LDFLAGS) -o sh.elf $(OBJS) $(LIBS)
		$(OBJDUMP) -S sh.elf > sh.dis
		$(SIZE) sh.elf
		$(ELF2AOUT) sh.elf $@ && rm sh.elf

install:	all
		install sh $(DESTDIR)/bin/

clean:
		rm -f sh *.o *.d *~ *.elf *.dis

#DG - the following generates depedency rules so that they don't have to be
#DG - listed manually. The code comes from the GNU make manual
#DG - system header file get listed as dependencies even when using the "-MM" flag
%.d:		%.c
		@set -e; rm -f $@; \
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

include $(patsubst %.c,%.d,$(FLTSRCS))
