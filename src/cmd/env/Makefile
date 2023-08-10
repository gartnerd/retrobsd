TOPSRC		= $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk
#include $(TOPSRC)/cross.mk

OBJS            = env.o

CFLAGS		+= -Werror -Wall 

CPPFLAGS        += -DGCC_COMPAT \
                   -DVERSSTR=\"1.0\" \
                   -DSTDINC=\"/include\" \
                   -DLIBDIR=\"/lib\" \
                   -DLIBEXECDIR=\"/libexec\"
                   -DCRT0FILE=\"/lib/crt0.o\" \
                   -DCRT0FILE_PROFILE=\"/lib/gcrt0.o\"

.PHONY:		all clean install

all:            env

env:            $(OBJS)
		$(CC) $(LDFLAGS) -o env.elf $(OBJS) $(LIBS)
		$(OBJDUMP) -S env.elf > env.dis
		$(SIZE) env.elf
		$(ELF2AOUT) env.elf $@ && rm env.elf

clean:
		rm -f *.o *.0 *.elf env *.elf *.dis tags *~

install:        all
		install env $(DESTDIR)/bin/
