TOPSRC		= $(shell cd ../..; pwd)

include $(TOPSRC)/target.mk

LIBCDIR          = $(TOPSRC)/src/libc

vpath %.S $(LIBCDIR)/mips/sys $(LIBCDIR)/mips/string $(LIBCDIR)/mips/gen \
          $(LIBCDIR)/runtime

vpath %.c $(LIBCDIR)/mips/sys $(LIBCDIR)/gen $(LIBCDIR)/stdio \
          $(LIBCDIR)/stdlib $(LIBCDIR)/string $(LIBCDIR)/inet \
          $(LIBCDIR)/compat $(LIBCDIR)/runtime

CFLAGS		= -Os -B$(TOPSRC)/lib/ $(DEFS) -Wall -Werror
ASFLAGS		= -B$(TOPSRC)/lib/ $(DEFS) -I$(LIBCDIR)/mips/sys

# modules which can not use SYSCALL and must be assembled from sources.  The
# rest of the system calls are generated with printf(1) and do not have
# source files associated with them.

# libc/mips/sys
SYSOBJS		= __sysctl.o accept.o access.o adjtime.o bind.o chdir.o \
		  chflags.o chmod.o chown.o chroot.o close.o connect.o dup.o \
		  dup2.o execve.o fchdir.o fchflags.o fchmod.o fchown.o \
		  fcntl.o flock.o fork.o fstat.o fsync.o ftruncate.o \
		  getdtablesize.o getgroups.o getitimer.o getsockname.o \
		  getpeername.o getpriority.o getrlimit.o getrusage.o \
                  getsockopt.o gettimeofday.o ioctl.o kill.o killpg.o link.o \
                  listen.o lstat.o mkdir.o mknod.o mount.o open.o pselect.o \
                  quota.o read.o readlink.o readv.o reboot.o recv.o \
                  recvfrom.o recvmsg.o rename.o rmdir.o select.o send.o \
                  sendmsg.o sendto.o setgroups.o setitimer.o setpgrp.o \
                  setpriority.o setquota.o setuid.o seteuid.o setgid.o \
                  setegid.o setrlimit.o setsockopt.o settimeofday.o \
                  shutdown.o sigaltstack.o socket.o socketpair.o stat.o \
                  symlink.o sigprocmask.o sigstack.o sigwait.o statfs.o \
                  fstatfs.o getfsstat.o truncate.o umount.o unlink.o \
                  utimes.o wait4.o write.o writev.o lseek.o sigsuspend.o \
		  getgid.o getegid.o getpgrp.o getpid.o getppid.o getuid.o \
                  geteuid.o profil.o sigpending.o sync.o ufetch.o ustore.o \
                  ucall.o umask.o vfork.o vhangup.o rdglob.o wrglob.o

OBJS		= $(SYSOBJS) sbrk.o execl.o execle.o execv.o \
		  _exit.o _brk.o pipe.o ptrace.o sigaction.o

# libc/mips/string
ASFLAGS         += -DLWHI=lwr -DLWLO=lwl -DSWHI=swr -DSWLO=swl

MIPS_STRING_ASR   = $(wildcard $(LIBCDIR)/mips/string/*.S)
MIPS_STRING_OBJS  = $(notdir $(patsubst %.S,%.o,$(MIPS_STRING_ASR)))

OBJS		+= $(MIPS_STRING_OBJS)

# libc/mips/gen
MIPS_GEN_OBJS	= _setjmp.o htonl.o htons.o

OBJS		+= $(MIPS_GEN_OBJS)

# libc/gen
GEN_EXCLD_SRCS	= abs.c bcmp-disabled.c bcopy-disabled.c bzero-disabled.c fabs.c ffs-disabled.c \
		  index-disabled.c insque.c isinf.c isnan.c modf.c remque.c rindex-disabled.c \
		  strcmp-disabled.c strlen-disabled.c valloc.c

GEN_SRCS = $(notdir $(wildcard $(LIBCDIR)/gen/*.c))
GEN_FILT_SRCS = $(filter-out $(GEN_EXCLD_SRCS),$(GEN_SRCS))

GEN_OBJS = $(patsubst %.c,%.o,$(GEN_FILT_SRCS))

OBJS	+= $(GEN_OBJS)

# libc/stdio
STDIO_EXCLD_SRCS = clnup.c

STDIO_SRCS = $(notdir $(wildcard $(LIBCDIR)/stdio/*.c))
STDIO_FILT_SRCS = $(filter-out $(STDIO_EXCLD_SRCS),$(STDIO_SRCS))

STDIO_OBJS = $(patsubst %.c,%.o,$(STDIO_FILT_SRCS))

OBJS	+= $(STDIO_OBJS)

# libc/stdlib
STDLIB_SRCS = $(notdir $(wildcard $(LIBCDIR)/stdlib/*.c))
STDLIB_OBJS = $(patsubst %.c,%.o,$(STDLIB_SRCS))

OBJS	+= $(STDLIB_OBJS)

# libc/string
STR_SRCS = $(notdir $(wildcard $(LIBCDIR)/string/*.c))
STR_OBJS = $(patsubst %.c,%.o,$(STR_SRCS))

OBJS 	+= $(STR_OBJS)

# libc/inet
INET_SRCS = $(notdir $(wildcard $(LIBCDIR)/inet/*.c))
INET_OBJS = $(patsubst %.c,%.o,$(INET_SRCS))

OBJS 	+= $(INET_OBJS)

# libc/compat
COMPAT_SRCS = $(notdir $(wildcard $(LIBCDIR)/compat/*.c))
COMPAT_OBJS = $(patsubst %.c,%.o,$(COMPAT_SRCS))

OBJS	+= $(COMPAT_OBJS)

# libc/runtime
#one assmbler file - sc_case.S
RUNTIME_SRCS = $(notdir $(wildcard $(LIBCDIR)/runtime/*.c))
RUNTIME_OBJS = $(patsubst %.c,%.o,$(RUNTIME_SRCS)) sc_case.o

OBJS	+= $(RUNTIME_OBJS)

.PHONY:		all clean

all:            ../libc.a

../libc.a:      ../ar ../ranlib $(OBJS)
		../ar rc $@ $(OBJS)
		../ranlib $@

$(SYSOBJS):	$(LIBCDIR)/mips/sys/SYS.h
		@echo creating $*.o
		@printf '#include "SYS.h"\nSYS($*)\n' | $(AS) $(ASFLAGS) - -c -o $*.o

clean:
		rm -f *~ *.o a.out *.a
