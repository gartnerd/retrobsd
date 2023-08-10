TOPSRC		= $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk
#include $(TOPSRC)/cross.mk

CFLAGS		+= -Os -Wall -Werror

OBJS            = scm.o func.o
TESTS           = tests/*.scm

.PHONY:		all clean install tests expected

all:            scm $(MAN)

scm:            $(OBJS)
		$(CC) $(LDFLAGS) -o scm.elf $(OBJS) $(LIBS)
		$(OBJDUMP) -S scm.elf > scm.dis
		$(SIZE) scm.elf
		$(ELF2AOUT) scm.elf $@ && rm scm.elf

clean:
		rm -f *.o scm *.elf *.dis *~ tests/*.out

install:        all
		install scm $(DESTDIR)/bin/

tests:          scm $(TESTS)
		for i in $(TESTS); do \
                        base=`basename $$i .scm`;\
                        ./scm -v $$i > tests/$$base.out;\
                        diff tests/$$base.expected tests/$$base.out; done

expected:       scm $(TESTS)
		for i in $(TESTS); do \
                        base=`basename $$i .scm`;\
                        ./scm -v $$i > tests/$$base.expected; done
