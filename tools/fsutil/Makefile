CFLAGS		= -g -O -Wall -m32
LDFLAGS		= -m32
DESTDIR		= /usr/local
BINDIR		= $(DESTDIR)/bin
OBJS		= $(patsubst %.c,%.o,$(wildcard *.c)) 
PROG		= fsutil

.PHONY:		all install clean

# Enable mount option.
#ENABLE_FUSE    = 1

# Fuse - userspace file system. See man 8 fuse for details
# FUSE_PATH may get defined in another Makefile
# currently pkg-config fuse --whatever doesn't work on my system
ifneq ($(ENABLE_FUSE),)
    CFLAGS       += -DENABLE_FUSE
    MOUNT_CFLAGS = -DFUSE_USE_VERSION=26
    MOUNT_CFLAGS += $(shell PKG_CONFIG_PATH=$(FUSE_PATH) pkg-config fuse --cflags)
    LIBS         += $(shell PKG_CONFIG_PATH=$(FUSE_PATH) pkg-config fuse --libs)
endif

all:		$(PROG)

install:	$(PROG)
		install -s $(PROG) $(BINDIR)
clean:
		rm -rf *~ *.o *.lst *.dis $(PROG)

$(PROG):	$(OBJS)
		$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

root.bin:       $(PROG)
		./$(PROG) -n16384 -s2048 $@
		./$(PROG) -v $@
		./$(PROG) -c $@

swap.bin:
		dd bs=1k count=2048 < /dev/zero > $@

mount.o:	CFLAGS += $(MOUNT_CFLAGS)
mount.o: 	mount.c bsdfs.h
		$(CC) $(CFLAGS) -c -o $@ $<

block.o: 	block.c bsdfs.h
check.o: 	check.c bsdfs.h
create.o: 	create.c bsdfs.h
file.o: 	file.c bsdfs.h
fsutil.o: 	fsutil.c bsdfs.h manifest.h
inode.o: 	inode.c bsdfs.h
manifest.o: 	manifest.c bsdfs.h manifest.h
superblock.o: 	superblock.c bsdfs.h
