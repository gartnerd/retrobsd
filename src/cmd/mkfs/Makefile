#
# Public Domain.  1996/11/16 - Steven Schultz
#
TOPSRC		= $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk
#include $(TOPSRC)/cross.mk

CFLAGS		+= -Wall -Werror

SRCS		= mkfs.c
OBJS		= mkfs.o
MAN		= mkfs.0
MANSRC		= mkfs.8

.PHONY:		all clean depend install lint tags

all:		mkfs mkfs.0

mkfs:		$(OBJS)
		$(CC) $(LDFLAGS) -o mkfs.elf $(OBJS) $(LIBS)
		$(OBJDUMP) -S mkfs.elf > mkfs.dis
		$(SIZE) mkfs.elf
		$(ELF2AOUT) mkfs.elf $@ && rm mkfs.elf

$(MAN):		$(MANSRC)
		$(MANROFF) $(MANSRC) > $(MAN)

clean:
		rm -f *.o *.elf *.dis *~ $(MAN) mkfs tags

depend:		$(SRCS)
		mkdep $(CFLAGS) $(SRCS)

install:	all
		cp $(MAN) $(DESTDIR)/share/man/cat8/
		install mkfs $(DESTDIR)/sbin/mkfs

lint:		$(SRCS)
		lint -hax $(SRCS)

tags:		$(SRCS)
		ctags $(SRCS)

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.
