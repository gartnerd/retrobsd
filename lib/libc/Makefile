TOPSRC		= $(shell cd ../..; pwd)

include $(TOPSRC)/target.mk

LIBCDIR          = $(TOPSRC)/src/libc

vpath %.S $(LIBCDIR)/mips/sys $(LIBCDIR)/mips/string $(LIBCDIR)/mips/gen \
          $(LIBCDIR)/runtime

vpath %.c $(LIBCDIR)/mips/sys $(LIBCDIR)/gen $(LIBCDIR)/stdio \
          $(LIBCDIR)/stdlib $(LIBCDIR)/string $(LIBCDIR)/inet \
          $(LIBCDIR)/compat $(LIBCDIR)/runtime

CFLAGS		= -Os -B$(TOPSRC)/lib/ $(DEFS) -Wa,-x -Wall -Werror
ASFLAGS		+= -B$(TOPSRC)/lib/ $(DEFS) -Wa,-x -I$(LIBCDIR)/mips/sys

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

#TODO - check if including extra files with the wildcard
#match. May have to filter the results of some of the matches
#see the filter files in myretrobsd/tmp

# libc/mips/string
ASFLAGS         += -DLWHI=lwr -DLWLO=lwl -DSWHI=swr -DSWLO=swl
#OBJS            += bcopy.o bzero.o ffs.o memcpy.o memmove.o memset.o \
                   strlen.o bcmp.o index.o rindex.o strcmp.o

MIPS_STRING_ASR = $(wildcard $(LIBCDIR)/mips/string/*.S)
#MIPS_STRING_CSR = $(wildcard $(LIBCDIR)/mips/string/*.c)
#MIPS_STRING_SRCS = $(MIPS_STR_ASR) $(MIPS_STRING_CSR)
MIPS_STRING_OBJS  = $(patsubst %.S,%.o,$(MIPS_STRING_ASR))
#MIPS_STRING_OBJS += $(patsubst %.c,%.o,$(MIPS_STRING_CSR))


# libc/mips/gen
MIPS_GEN_OBJS            = _setjmp.o htonl.o htons.o

# libc/gen
#OBJS            += abort.o alarm.o atof.o atoi.o atol.o calloc.o closedir.o crypt.o \
                   ctime.o ctype_.o daemon.o devname.o ecvt.o err.o \
                   execvp.o fakcu.o frexp.o fstab.o gcvt.o getenv.o getgrent.o \
                   getgrgid.o getgrnam.o getlogin.o \
                   getgrouplist.o gethostname.o getpagesize.o \
                   getpass.o getpwent.o getloadavg.o getmntinfo.o \
                   getttyent.o getttynam.o getusershell.o getwd.o \
                   initgroups.o isatty.o isinff.o isnanf.o ldexp.o malloc.o mktemp.o \
                   modff.o ndbm.o nlist.o knlist.o opendir.o perror.o popen.o \
                   psignal.o qsort.o random.o readdir.o regex.o scandir.o \
                   seekdir.o setmode.o sethostname.o setenv.o siglist.o \
                   signal.o siginterrupt.o sigsetops.o \
                   sleep.o strcasecmp.o strftime.o swab.o sysctl.o syslog.o system.o \
                   strcat.o strncat.o strcpy.o strncpy.o strncmp.o \
                   telldir.o time.o timezone.o ttyname.o ttyslot.o ualarm.o usleep.o \
                   strdup.o uname.o wait.o wait3.o waitpid.o

LIBC_GEN_CSR = $(wildcard $(LIBCDIR)/gen/*.c)
LIBC_GEN_OBJS = $(patsubst %.c,%.o,$(LIBC_GEN_CSR))
G_EXCLUDED_SRCS = abs.c bcmp-disabled.c bcopy-disabled.c bzero-disabled.c fabs.c \
	   ffs-disabled.c index-disabled.c insque.c isinf.c isnan.c modf.c \
	   remque.c rindex-disabled.c strcmp-disabled.c strlen-disabled.c \
	   valloc.c

# libc/stdio
#OBJS            += fgetc.o fgets.o fputc.o fputs.o gets.o puts.o \
                   clrerr.o doscan.o exit.o fdopen.o filbuf.o findiop.o \
                   flsbuf.o fopen.o fprintf.o fread.o freopen.o fseek.o \
                   ftell.o fwrite.o getchar.o getw.o printf.o putchar.o putw.o \
                   rew.o scanf.o setbuf.o setbuffer.o setvbuf.o snprintf.o sprintf.o \
                   strout.o ungetc.o vfprintf.o vprintf.o vsprintf.o doprnt.o \
                   remove.o feof.o ferror.o fileno.o

LIBC_STDIO_CSR = $(wildcard $(LIBCDIR)/stdio/*.c)
LIBC_STDIO_OBJS = $(patsubst %.c,%.o,$(LIBC_STDIO_CSR))
EXECLUDE = clnup.c

# libc/stdlib
#OBJS            += getopt.o getsubopt.o strtol.o strtoul.o strtod.o

LIBC_STDLIB_CSR = $(wildcard $(LIBCDIR)/stdlib/*.c)
LIBC_STDLIB_OBJS = $(patsubst %.c,%o,$(LIBC_STDLIB_CSR))

# libc/string
#OBJS            += strcspn.o strpbrk.o strerror.o strsep.o strspn.o \
                   strstr.o strtok.o strtok_r.o

LIBC_STR_CSR = $(wildcard $(LIBCDIR)/string/*.c)
LIBC_STR_OBJS = $(patsubst %.c,%.o,$(LIBC_STR_CSR))

# libc/inet
#OBJS            += inet_addr.o inet_network.o inet_netof.o \
                   inet_ntoa.o inet_lnaof.o inet_maddr.o

LIBC_INET_CSR = $(wildcard $(LIBCDIR)/inet/*.c)
LIBC_INET_OBJS = $(patsubst %.c,%.o,$(LIBCDIR))

# libc/compat
#OBJS            += creat.o ftime.o gethostid.o memccpy.o memchr.o \
                   memcmp.o memcpy.o memset.o nice.o pause.o rand.o \
                   sethostid.o setregid.o setreuid.o setrgid.o setruid.o \
                   sigcompat.o strchr.o strrchr.o times.o tmpnam.o \
                   utime.o

LIBC_COMPAT_CSR = $(wildcard $(LIBCDIR)/compat/*.c)
LIBC_COMPAT_OBJS = $(patsubst %.c,%.o,$(LIBC_COMPAT_CSR))


# libc/runtime
#OBJS            += addsf3.o comparesf2.o divsf3.o fixsfsi.o floatsisf.o \
                   mulsf3.o negsf2.o subsf3.o sc_case.o fixunssfsi.o \
                   floatunsisf.o

#one assmbler file - sc_case.S
LIBC_RUNTIME_CSR = $(wildcard $(LIBCDIR)/runtime/*.c)
LIBC_RUNTIME_OBJS = $(patsubst %.c,%.o,$(LIBC_RUNTIME_CSR)) sc_case.o



all:            ../libc.a

../libc.a:      ../ar ../ranlib $(OBJS)
		../ar rc $@ $(OBJS)
		../ranlib $@

$(SYSOBJS):	$(LIBCDIR)/mips/sys/SYS.h
		@echo creating $*.o
		@printf '#include "SYS.h"\nSYS($*)\n' | $(AS) $(ASFLAGS) - -c -o $*.o

clean:
		(rm -f *~ *.o a.out *.a
