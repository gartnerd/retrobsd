#DG - not all subdirectories under "tools" are spec'd/used

SUBDIRS		= elf2aout fsutil virtualmips mkrd kconfig icache

.PHONY:		all install clean $(SUBDIRS)

all install:	$(SUBDIRS)

$(SUBDIRS):
		$(MAKE) -C $@ $(MFLAGS) BINDIR=$(BINDIR)

clean:
		rm -f *~
		-for i in $(SUBDIRS); do $(MAKE) -C $$i $(MFLAGS) clean; done
