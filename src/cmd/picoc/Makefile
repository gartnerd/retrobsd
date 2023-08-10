TOPSRC          = $(shell cd ../../..; pwd)
include $(TOPSRC)/target.mk

vpath   %.c platform cstdlib 

CFLAGS          += -g -Os -Werror -mips16
CPPFLAGS	= -DUNIX_HOST -DVER='"1.0"' -DFILENAME_MAX=64 -DL_tmpnam=30 \
                  -DCLOCKS_PER_SEC=80000000 -DPATH_MAX=200 -DNO_FP 

LIBS            = -lm -lc

TARGET          = picoc

EXCLDSRCS	= platform/library_ffox.c platform/library_msvc.c platform/library_srv1.c \
                  platform/library_surveyor.c platform/platform_ffox.c platform/platform_msvc.c \
                  platform/platform_surveyor.c

SRCS		= $(wildcard *.c cstdlib/*.c platform/*.c)
FLTSRCS		= $(filter-out $(EXCLDSRCS),$(SRCS))

OBJS		= $(patsubst %.c,%.o,$(FLTSRCS))

.PHONY:		all install test clean

all:            $(TARGET)

$(TARGET):      $(OBJS)
		$(CC) $(LDFLAGS) -o $(TARGET).elf $(OBJS) $(LIBS)
		$(OBJDUMP) -S $(TARGET).elf > $(TARGET).dis
		$(SIZE) $(TARGET).elf
		$(ELF2AOUT) $(TARGET).elf $@

install:        $(TARGET)
		cp $(TARGET) $(TOPSRC)/bin

test:           all
		(cd tests; make test)

clean:
		rm -f $(TARGET) *.o */*.o *.d */*.d *~ *.elf *.dis

#DG - the following generates depedency rules so that they don't have to be
#DG - listed manually. The code comes from the GNU make manual
%.d:		%.c
		@set -e; rm -f $@; \
		$(CC) -MM $(CPPFLAGS) $< > $@.$$$$; \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
		rm -f $@.$$$$

include $(patsubst %.c,%.d,$(FLTSRCS))
