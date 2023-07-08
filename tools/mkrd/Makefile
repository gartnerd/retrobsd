OBJS    = mkrd.o
BIN     = mkrd
CFLAGS  = -m32 -Wall -Werror -O 
LDFLAGS = -m32

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $< $(LIBS)

#DG - adding header file prerequisite
mkrd.o:	mkrd.c rdisk.h

clean:
	@rm -f $(BIN) $(OBJS)
