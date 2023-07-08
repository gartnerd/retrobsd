SUBDIR		= elf2aout fsutil virtualmips mkrd kconfig icache

.PHONY:		all install

all install:	$(SUBDIR)
		-for i in $(SUBDIR); do $(MAKE) -C $$i $(MFLAGS) BINDIR=$(BINDIR) $@; done

clean:
		rm -f *~
		-for i in $(SUBDIR); do $(MAKE) -C $$i $(MFLAGS) clean; done
