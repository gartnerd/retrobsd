#DG - According to the GNU make manual MFLAGS is an older version
#DG - of MAKEFLAGS (with some minor behaviour changes). 
#DG - Its not really depricated but kept for compatibility with 
#DG - older make files
#
#DG - removed the depend target - don't think it's being used

TOPSRC          = $(shell cd ..; pwd)
SUBDIRS		= startup libc libm libcurses libtermlib libwiznet libreadline libgpanel
PROGS		= ar as aout ld nm ranlib size strip

# DG - idirafter indicates location to search for header files
CFLAGS          =  -m32 -Os -std=gnu89 -fno-builtin -g -Wall -DCROSS -I. \
                   -idirafter $(TOPSRC)/include \
                   -idirafter $(TOPSRC)/src/cmd/ar \
                   -idirafter $(TOPSRC)/src/cmd/as

LDFLAGS         = -g -m32

AR_OBJS         = ar.o append.o archive.o contents.o delete.o extract.o \
                  misc.o move.o print.o replace.o strmode.o

AOUT_OBJS       = aout.o mips-dis.o

RANLIB_OBJS     = ranlib.o archive.o

HEADERS         = a.out.h ar.h nlist.h ranlib.h

vpath %.c $(TOPSRC)/src/cmd/aout $(TOPSRC)/src/cmd/ar $(TOPSRC)/src/cmd/as \
    $(TOPSRC)/src/cmd/ld $(TOPSRC)/src/cmd/nm $(TOPSRC)/src/cmd/ranlib \
    $(TOPSRC)/src/cmd

.PHONY: all install clean $(SUBDIRS)

all install: $(HEADERS) $(PROGS) $(SUBDIRS)

#DG - see GNU make manual section 4.5 PHONY targets on 
#DG - suggestion for recursive make suggestions - haven't tried with install target
$(SUBDIRS):
		$(MAKE) -C $@ $(MFLAGS) DESTDIR=$(DESTDIR)

clean:
		rm -f *~ *.o *.a *.h $(PROGS) retroImage gccdump.s
		for i in $(SUBDIRS); do $(MAKE) -C $$i $(MFLAGS) clean; done

ar:             $(AR_OBJS)
		$(CC) $(LDFLAGS) -o $@ $(AR_OBJS) $(LIBS)

as:             as.o
		$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

aout:           $(AOUT_OBJS)
		$(CC) $(LDFLAGS) -o $@ $(AOUT_OBJS) $(LIBS)

ld:             ld.o
		$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

nm:             nm.o
		$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

ranlib:         $(RANLIB_OBJS)
		$(CC) $(LDFLAGS) -o $@ $(RANLIB_OBJS) $(LIBS)

size:           size.o
		$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

strip:          strip.o
		$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

$(HEADERS):
		-ln -s -f ../include/a.out.h .
		-ln -s -f ../include/ar.h .
		-ln -s -f ../include/nlist.h .
		-ln -s -f ../include/ranlib.h .
