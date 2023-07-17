CFLAGS		= -g -m32 -O -Wall
LDFLAGS		= -m32
PREFIX		= /usr/local
BINDIR		= $(PREFIX)/bin
OBJS		= ice2aout.o
PROG		= ice2aout

.PHONY:		all install clean

all:		$(PROG)

install:	$(PROG)
		install -s $(PROG) $(BINDIR)
clean:
		rm -f *~ *.o *.lst *.dis $(PROG)

$(PROG):	$(OBJS)
		$(CC) $(LDFLAGS) -o $@ $< $(LIBS)
