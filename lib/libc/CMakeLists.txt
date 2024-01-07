#This recipe will create all the object files for the libraries
#The "ar" program will happily create an archive from all the files
#However, there is a limit on the length of the filename (possibly historical)
#ranlib throws an error when it is given the archive created by "ar" with 
#filenames that are longer than 15 chars

cmake_minimum_required(VERSION 3.20)
project(myRetroBSD_native_libc LANGUAGES C ASM)

set(TOPSRC /home/gartnerd/code/myretrobsd)
set(LIBCDIR ${TOPSRC}/src/libc)
set(OBJECT_OUTPUT_DIR ${CMAKE_BINARY_DIR}/sysobj)

set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -B${TOPSRC}/lib/ -I${LIBCDIR}/mips/sys -DLWHI=lwr -DLWLO=lwl -DSWHI=swr -DSWLO=swl") 

set(CMAKE_AR ${retrobsd_BINARY_DIR}/ar)
set(CMAKE_RANLIB ${retrobsd_BINARY_DIR}/ranlib)

set(AGEN_FILES ${LIBCDIR}/mips/gen/_setjmp.S ${LIBCDIR}/mips/gen/htonl.S ${LIBCDIR}/mips/gen/htons.S)
set(ARNT_FILES ${LIBCDIR}/runtime/sc_case.S)
set(ASYS_FILES ${LIBCDIR}/mips/sys/_exit.S ${LIBCDIR}/mips/sys/_brk.S ${LIBCDIR}/mips/sys/pipe.S ${LIBCDIR}/mips/sys/ptrace.S ${LIBCDIR}/mips/sys/sigaction.S)

file(MAKE_DIRECTORY ${OBJECT_OUTPUT_DIR}/c)

file(GLOB ASTR_FILES ${LIBCDIR}/mips/string/*.S)

list(APPEND ASM_FILES ${ASYS_FILES} ${ASTR_FILES} ${AGEN_FILES} ${ARNT_FILES})

#message(STATUS "ASM_FILES: ${ASM_FILES}")

#object files that are stubs
set(OBJ_FILES	__sysctl accept access adjtime bind chdir 
		chflags chmod chown chroot close connect dup 
		dup2 execve fchdir fchflags fchmod fchown 
		fcntl flock fork fstat fsync ftruncate 
		getdtablesize getgroups getitimer getsockname 
		getpeername getpriority getrlimit getrusage 
		getsockopt gettimeofday ioctl kill killpg link 
		listen lstat mkdir mknod mount open pselect 
		quota read readlink readv reboot recv 
		recvfrom recvmsg rename rmdir select send 
		sendmsg sendto setgroups setitimer setpgrp 
		setpriority setquota setuid seteuid setgid 
		setegid setrlimit setsockopt settimeofday 
		shutdown sigaltstack socket socketpair stat 
		symlink sigprocmask sigstack sigwait statfs 
		fstatfs getfsstat truncate umount unlink 
		utimes wait4 write writev lseek sigsuspend 
		getgid getegid getpgrp getpid getppid getuid 
		geteuid profil sigpending sync ufetch ustore 
		ucall umask vfork vhangup rdglob wrglob
	)

#generate c files from listed OBJ_FILES
foreach(OBJ_FILE ${OBJ_FILES})
        file(GENERATE OUTPUT ${OBJECT_OUTPUT_DIR}/c/${OBJ_FILE}.c CONTENT "#include \"SYS.h\"\nSYS(${OBJ_FILE})\n")
	list(APPEND C_GEN_FILES ${OBJECT_OUTPUT_DIR}/c/${OBJ_FILE}.c)
endforeach()

#get the required 'C' files
file(GLOB CSYS_FILES ${LIBCDIR}/mips/sys/*.c)
file(GLOB CGEN_FILES ${LIBCDIR}/gen/*.c)
file(GLOB CSTD_FILES ${LIBCDIR}/stdio/*.c)
file(GLOB CSLB_FILES ${LIBCDIR}/stdlib/*.c)
file(GLOB CSTR_FILES ${LIBCDIR}/string/*.c)
file(GLOB CNET_FILES ${LIBCDIR}/inet/*.c)
file(GLOB CCMP_FILES ${LIBCDIR}/compat/*.c)
file(GLOB CRNT_FILES ${LIBCDIR}/runtime/*.c)

#get rid of the files that aren't used
list(REMOVE_ITEM CGEN_FILES 	${LIBCDIR}/gen/abs.c ${LIBCDIR}/gen/bcmp-disabled.c
				${LIBCDIR}/gen/bcopy-disabled.c ${LIBCDIR}/gen/bzero-disabled.c
				${LIBCDIR}/gen/fabs.c ${LIBCDIR}/gen/ffs-disabled.c
				${LIBCDIR}/gen/index-disabled.c ${LIBCDIR}/gen/insque.c
				${LIBCDIR}/gen/isinf.c ${LIBCDIR}/gen/isnan.c
				${LIBCDIR}/gen/modf.c ${LIBCDIR}/gen/remque.c
				${LIBCDIR}/gen/rindex-disabled.c ${LIBCDIR}/gen/strcmp-disabled.c
				${LIBCDIR}/gen/strlen-disabled.c ${LIBCDIR}/gen/valloc.c
				)

list(REMOVE_ITEM CSTD_FILES ${LIBCDIR}/stdio/clnup.c)

#It appears that the last add_library() call needs its own source files to work. 
#So just remove a set from C_FILES and add it to the last add_library() call. 
#list(APPEND C_FILES ${CSYS_FILES} ${CGEN_FILES} ${CSTD_FILES} ${CSLB_FILES} ${CSTR_FILES} ${CNET_FILES} ${CCMP_FILES} ${CRNT_FILES} )
list(APPEND C_FILES ${CGEN_FILES} ${CSTD_FILES} ${CSLB_FILES} ${CSTR_FILES} ${CNET_FILES} ${CCMP_FILES} ${CRNT_FILES} )

#message("C_FILES: ${C_FILES}")

add_library(c_gen_objs OBJECT ${C_GEN_FILES})
target_compile_options(c_gen_objs PRIVATE ${AS} -B${TOPSRC}/lib/ -I${LIBCDIR}/mips/sys -DLWHI=lwr -DLWLO=lwl -DSWHI=swr -DSWLO=swl)

add_library(asm_objs OBJECT ${ASM_FILES} )

add_library(c_objs OBJECT ${C_FILES})
target_compile_options(c_objs PRIVATE -Os -B${TOPSRC}/lib/ -Wall -Werror)

add_library(c STATIC $<TARGET_OBJECTS:asm_objs> $<TARGET_OBJECTS:c_objs> $<TARGET_OBJECTS:c_gen_objs> ${CSYS_FILES})
target_compile_options(c PRIVATE -Os -B${TOPSRC}/lib/ -Wall -Werror) 

