#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
TOPSRC		= $(shell cd ..; pwd)
include $(TOPSRC)/target.mk

# Programs that live in subdirectories, and have makefiles of their own.
#
SUBDIR		= startup-$(MACHINE) libc libm libutil libtermlib libcurses \
                  libvmf libwiznet libreadline libgpanel share cmd games man

#DG - we need to do something special to mimic the original way this 
#DG - makefile worked when called from its' parent with the install target
#Get the goal specified on the command line.
ifeq ($(filter install,$(MAKECMDGOALS)),install)
    TARGET := all install
endif

.PHONY:		all clean install $(SUBDIR)

all:		$(SUBDIR)

install:	elf32-mips.ld $(SUBDIR)

$(SUBDIR):	
		$(MAKE) -C $@ DESTDIR=$(DESTDIR) $(TARGET)

clean:
		rm -f a.out core *.s *.o *.a *~
		-for i in $(SUBDIR); do $(MAKE) -C $$i clean; done
