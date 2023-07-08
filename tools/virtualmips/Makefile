#
# Build VirtualMIPS simulator.
#

#DG - most of the ideas for reworking this file comes from
#DG - https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/

PROG		:= pic32
SRCS		:= $(wildcard *.c)

#DG - these files are used with different options (see further below) or
#DG - by the makefile Makefile-m4k
EXCLUDED_SRCS	:= mips_codetable.c mips16-opc.c mips-opc.c pavo.c m4k.c

#DG - the following file doesn't appear to be used for anything
EXCLUDED_SRCS	+= dev_nor_flash_4m.c

FILTERED_SRCS 	:= $(filter-out $(EXCLUDED_SRCS),$(SRCS))
OBJS		:= $(patsubst %.c,%.o,$(FILTERED_SRCS))

CC          	?= gcc
LDFLAGS 	:= -m32
DEPDIR		:= .deps
DEPFLAGS	= -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d
LIBS		:= -lpthread
LIBS		+= $(shell pkg-config libelf --libs)

ifneq ($(wildcard /usr/lib/librt.a),)
LIBS		+= -lrt                             # Linux
endif
ifneq ($(wildcard /usr/lib/i386-linux-gnu/librt.a),)
LIBS		+= -lrt                             # Linux
endif

#DG - common compiler and preproccessor flags for target boards
#DG - possible optimization
#DG - CFLAGS	+= -O3 -fomit-frame-pointer
CFLAGS		:= -g -m32 -O -Wall 
CFLAGS      	+= $(shell pkg-config libelf --cflags)

CPPFLAGS	:= -DSIM_PIC32 -DPIC32MX7

# Select target board:
# chipKIT Max32
CPPFLAGS	+= -DMAX32

# Maximite
#CPPFLAGS		+= -DMAXIMITE

# Microchip Explorer 16
#CPPFLAGS		+= -DEXPLORER16

# UBW32 with UART console
#CPPFLAGS		+= -DUBW32

# Ingenic JZ4740.
#CFLAGS		+= -DSIM_PAVO -D_USE_FDD_
#PROG		= pavo
#OBJS		= pavo.o jz4740.o jz4740_dev_cpm.o jz4740_dev_dma.o \
#              jz4740_dev_emc.o jz4740_dev_gpio.o jz4740_dev_int.o \
#              jz4740_dev_rtc.o jz4740_dev_ts.o \
#              jz4740_dev_uart.o jz4740_dev_wdt_tcu.o

# Implement LCD.
#CFLAGS		+= -DSIM_LCD
#LIBS		+= -lSDL
#OBJS		+= jz4740_dev_lcd.o vp_sdl.o

# Use JIT compiler.
#CFLAGS		+= -D_USE_JIT_
#OBJS		+= mips_jit.o x86_trans.o

all:		$(DEPDIR) $(PROG)

$(PROG):	$(OBJS)
		$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

#DG - remove implicit rules for creating object files - will use our own
#DG - the empty recipe for this target is supposed to accomplish this
%.o:		%.c

#DG - create a specific rule to replace the rule
#DG - "| $(DEPDIR) - is an order only rule - no timestamps, it just has to exist
%.o:		%.c $(DEPDIR)/%.d | $(DEPDIR)
		$(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c $(OUTPUT_OPTION) $<

clean:
		rm -rf *.o *~ *_log.txt $(DEPDIR) pavo pic32 m4k

$(DEPDIR):
		@mkdir -p $@

#DG - the following is some magic for dependencies
DEPFILES 	:= $(patsubst %.c,$(DEPDIR)/%.d,$(FILTERED_SRCS))

#DG - this is a file target. Make tries to match the list of files represented
#DG - by the target once it is expanded. It will try to recreate any that don't exist
#DG - I'm not sure how exactly it does this - possibly by recompiling the corresponding
#DG - object file
$(DEPFILES):

#DG - this causes make to incorporate the generated dependency information
#DG - into the build process
#DG - this should come after the initial build target or trouble will ensue... apparently
#DG - keeping it at the end of the file should be fine for most cases
include $(wildcard $(DEPFILES))

