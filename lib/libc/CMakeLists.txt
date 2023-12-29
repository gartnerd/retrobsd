cmake_minimum_required(VERSION 3.20)
project(myRetroBSD_native_libc LANGUAGES)

set(TOPSRC /home/gartnerd/code/myretrobsd)
set(LIBCDIR ${TOPSRC}/src/libc)
set(OBJECT_OUTPUT_DIR ${CMAKE_BINARY_DIR}/sysobj)

set(CMAKE_ASM_FLAGS ${CMAKE_ASM_FLAGS} -B${TOPSRC}/lib/ -I${LIBCDIR}/mips/sys -DLWHI=lwr -DLWLO=lwl -DSWHI=swr -DSWLO=swl) 
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -Os -B${TOPSRC}/lib/ -Wall -Werror)

set(AGEN_FILES 	${LIBCDIR}/mips/gen/_setjmp.S ${LIBCDIR}/mips/gen/htonl.S ${LIBCDIR}/mips/gen/htons.S)
set(ARNT_FILES ${LIBCDIR}/runtime/sc_case.S)
set(ASYS_FILES ${LIBCDIR}/mips/sys/_exit.S ${LIBCDIR}/mips/sys/_brk.S ${LIBCDIR}/mips/sys/pipe.S ${LIBCDIR}/mips/sys/ptrace.S ${LIBCDIR}/mips/sys/sigaction.S)

file(MAKE_DIRECTORY ${OBJECT_OUTPUT_DIR}/asm)
file(MAKE_DIRECTORY ${OBJECT_OUTPUT_DIR}/c)
file(MAKE_DIRECTORY ${OBJECT_OUTPUT_DIR}/stubs)
file(MAKE_DIRECTORY ${OBJECT_OUTPUT_DIR}/sh)

#file(GLOB_RECURSE ASM_FILES ${LIBCDIR}/mips/**/*.S)

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
list(APPEND C_FILES ${CSYS_FILES} ${CGEN_FILES} ${CSTD_FILES} ${CSLB_FILES} ${CSTR_FILES} ${CNET_FILES} ${CCMP_FILES} ${CRNT_FILES} )

#message("C_FILES: ${C_FILES}")

add_custom_target(assembler_objects)

foreach(ASM_FILE ${ASM_FILES})

	get_filename_component(ASM_NAME ${ASM_FILE} NAME_WE)
	set(OBJ_FILE ${OBJECT_OUTPUT_DIR}/asm/${ASM_NAME}.o)

	add_custom_command(
        	OUTPUT ${OBJ_FILE}
		COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${CMAKE_ASM_FLAGS} -c -o ${OBJ_FILE} ${ASM_FILE} 
        	DEPENDS ${ASM_FILE}
		#COMMENT "Building ${ASM_NAME}.o"
        	VERBATIM
    	)
	
	list(APPEND A_GEN_FILES ${OBJ_FILE}) 
	add_custom_target(${ASM_NAME}_target ALL DEPENDS ${OBJ_FILE})
	add_dependencies(assembler_objects ${ASM_NAME}_target)

	#message(STATUS "ASM_NAME: ${ASM_NAME}")

endforeach()

# Custom target to build object files from C sources
add_custom_target(c_objects)

foreach(C_FILE ${C_FILES})

	get_filename_component(C_NAME ${C_FILE} NAME_WE)
	set(OBJ_FILE ${OBJECT_OUTPUT_DIR}/c/${C_NAME}.o)

    	add_custom_command(
        	OUTPUT ${OBJ_FILE}	
		COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -c -o ${OBJ_FILE} ${C_FILE} 
		DEPENDS ${C_FILE}
		#COMMENT "Building ${C_NAME}.o"
		VERBATIM
    	)

	list(APPEND C_GEN_FILES ${OBJ_FILE}) 
	add_custom_target(${C_NAME}_tgt ALL DEPENDS ${OBJ_FILE})
	add_dependencies(c_objects ${C_NAME}_tgt)

	#message(STATUS "C_NAME: ${C_NAME}")

endforeach()

#reset CMAKE_C_FLAGS variable
set(CMAKE_C_FLAGS )
set(CMAKE_C_FLAGS -mips32r2 -EL -msoft-float -nostdinc -fshort-double -I${TOPSRC}/include)

# Custom target for stub file generation and compilation
foreach(OBJ_FILE ${OBJ_FILES})

	file(GENERATE OUTPUT ${OBJECT_OUTPUT_DIR}/sh/${OBJ_FILE}.sh CONTENT "printf '#include \"SYS.h\"\nSYS(${OBJ_FILE})\n'")

	# Add a custom target to create object file stubs
	add_custom_target(
		${OBJ_FILE} ALL
		DEPENDS ${OBJECT_OUTPUT_DIR}/sh/${OBJ_FILE}.sh
		COMMAND bash ${OBJECT_OUTPUT_DIR}/sh/${OBJ_FILE}.sh | ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${AS} ${CMAKE_ASM_FLAGS} - -c -o ${OBJECT_OUTPUT_DIR}/stubs/${OBJ_FILE}.o 
		VERBATIM
		#WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    	)

	# Add the object file target as a dependency to the libc target
	#add_dependencies(libc ${OBJ_FILE})

	list(APPEND DYN_GEN_FILES ${OBJECT_OUTPUT_DIR}/stubs/${OBJ_FILE}.o) 

	#message("OBJECT_OUTPUT_DIR: ${OBJECT_OUTPUT_DIR}")	

endforeach()

#gather all the generated object files into a single list
list(APPEND ALL_O_FILES ${A_GEN_FILES} ${C_GEN_FILES} ${DYN_GEN_FILES})

#message("ALL_O_FILES: ${ALL_O_FILES}")

add_custom_target(libc ALL DEPENDS assembler_objects c_objects)
#add_dependencies(build_libc assembler_objects c_objects)

# Custom command for creating libc.a
add_custom_command(
    TARGET libc
    POST_BUILD
    #COMMAND ${retrobsd_BINARY_DIR}/ar rc libc.a ${A_GEN_FILES} ${C_GEN_FILES} ${DYN_GEN_FILES}
    COMMAND ${retrobsd_BINARY_DIR}/ar rc libc.a ${A_GEN_FILES}
    COMMAND ${retrobsd_BINARY_DIR}/ar q  libc.a ${C_GEN_FILES}
    COMMAND ${retrobsd_BINARY_DIR}/ar q  libc.a ${DYN_GEN_FILES}
    COMMAND ${retrobsd_BINARY_DIR}/ranlib libc.a
    DEPENDS ${A_GEN_FILES} ${C_GEN_FILES}
    COMMENT "building libc.a"
)

#retrobsd_BINARY_DIR:STATIC
message(STATUS "build_libc dependencies: ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "retrobsd_BINARY_DIR: ${retrobsd_BINARY_DIR}")

# Custom target to build the static library
#add_library(libc STATIC ${A_GEN_FILES} ${C_GEN_FILES} ${DYN_GEN_FILES})


