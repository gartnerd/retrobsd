CC		?= gcc
CFLAGS		= -g -m32 -O -Wall -Werror
LDFLAGS		= -m32
YACC            = byacc -d
PREFIX		= /usr/local
BINDIR		= $(PREFIX)/bin
OBJS            = config.o main.o lang.o mkioconf.o mkmakefile.o mkswapconf.o
PROG		= kconfig

.PHONY:		all clean install

all:		$(PROG) $(PROG).0

install:	$(PROG)
		install -s $(PROG) $(BINDIR)

$(PROG).0:      $(PROG).8
		nroff -man $< > $@

clean:
		rm -rf *~ *.o *.lst *.dis $(PROG) $(PROG).0 y.tab.[ch] lang.c config.c

$(PROG):	$(OBJS)
		$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

main.o: 	main.c y.tab.h config.h
mkioconf.o: 	mkioconf.c y.tab.h config.h
mkmakefile.o: 	mkmakefile.c y.tab.h config.h
mkswapconf.o: 	mkswapconf.c config.h

#DG - mkheaders does not appear to be used
#mkheaders.o: mkheaders.c config.h y.tab.h

