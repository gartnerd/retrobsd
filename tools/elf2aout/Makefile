## refactoring attempt of makefiles for retrobsd
## flags:	meaning:
## 	-g	creates debugging information in executable - various levels possible
##	-O	level 1 optimization
##	-Wall	enable all compiler warnings
##	-m32	create 32 bit binaries
##
##	use an environment variable to explicitly specify a system wide CC 
##	Ubuntu based systems seem to default to using cc which is a symbolic link to gcc
##

CFLAGS		= -g -O -Wall -m32
LDFLAGS		= -m32
PREFIX		= /usr/local
BINDIR		= $(PREFIX)/bin
OBJS		= elf2aout.o
PROG		= elf2aout

.PHONY:	all install clean

all:		$(PROG)

install:	$(PROG)
		install -s $(PROG) $(BINDIR)
clean:
		rm -f *~ *.o *.lst *.dis $(PROG) $(OBJS)

$(PROG): 	$(OBJS)
		$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

#DG - the following could be omitted. The implicit make rules would cover this.
%.o: 		%.c
		$(CC) $(CFLAGS) -c -o $@ $<

