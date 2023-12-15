cmake_minimum_required(VERSION 3.20)

#Setting the LANGUAGES flag to C causes cmake to 
#try and compile its own test file with what appear
#to be the compiler flags set in this file. Leaving
#the value empty bypasses this test - necessary in this case
project(myRetroBSD_native_libc LANGUAGES)

set(TOPSRC /home/gartnerd/code/myretrobsd)
set(LIBCDIR ${TOPSRC}/src/libc)

#get assembler files
file(GLOB ASYS_FILES ${LIBCDIR}/mips/sys/*.S)
file(GLOB ASTR_FILES ${LIBCDIR}/mips/string/*.S)

set(AGEN_FILES 	${LIBCDIR}/mips/gen/_setjmp.S ${LIBCDIR}/mips/gen/htonl.S ${LIBCDIR}/mips/gen/htons.S)
set(ARNT_FILES ${LIBCDIR}/runtime/sc_case.S)

list(APPEND ASM_FILES ${ASYS_FILES} ${ASTR_FILES} ${AGEN_FILES} ${ARNT_FILES})

message("ASM_FILES: ${ASM_FILES}")

# Custom target to build object files from assembly sources
add_custom_target(assembler_objects)

foreach(ASM_FILE ${ASM_FILES})
	get_filename_component(ASM_NAME ${ASM_FILE} NAME_WE)
    	add_custom_command(
        	TARGET assembler_objects
		COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -c ${ASM_FILE} -o ${OBJECT_OUTPUT_DIR}/${ASM_NAME}.o
		DEPENDS ${ASM_FILES}
		COMMENT "Building ${ASM_NAME}.o"
    )
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
list(REMOVE_ITEM ${CGEN_FILES} 	${LIBCDIR}/gen/abs.c ${LIBCDIR}/gen/bcmp-disabled.c
				${LIBCDIR}/gen/bcopy-disabled.c ${LIBCDIR}/gen/bzero-disabled.c
				${LIBCDIR}/gen/fabs.c ${LIBCDIR}/gen/ffs-disabled.c
				${LIBCDIR}/gen/index-disabled.c ${LIBCDIR}/gen/insque.c
				${LIBCDIR}/gen/isinf.c ${LIBCDIR}/gen/isnan.c
				${LIBCDIR}/gen/modf.c ${LIBCDIR}/gen/remque.c
				${LIBCDIR}/gen/rindex-disabled.c ${LIBCDIR}/gen/strcmp-disabled.c
				${LIBCDIR}/gen/strlen-disabled.c ${LIBCDIR}/gen/valloc.c
				)

list(REMOVE_ITEM ${CSTD_FILES}  ${LIBCDIR}/stdio/clnup.c)
list(APPEND C_FILES ${CSYS_FILES} ${CGEN_FILES} ${CSTD_FILES} ${CSLB_FILES} ${CSTR_FILES} ${CNET_FILES} ${CCMP_FILES} ${CRNT_FILES} )

message("C_FILES: ${C_FILES}")

# Custom target to build object files from C sources
add_custom_target(c_objects)

foreach(C_FILE ${C_FILES})
	get_filename_component(C_NAME ${C_FILE} NAME_WE)
    	add_custom_command(
        	TARGET c_objects
		COMMAND ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} -c ${C_FILE} -o ${OBJECT_OUTPUT_DIR}/${C_NAME}.o
		DEPENDS ${C_FILE}
        	COMMENT "Building ${C_NAME}.o"
    	)
endforeach()


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

# Set the output directory for object files
set(OBJECT_OUTPUT_DIR ${CMAKE_BINARY_DIR}/objs)

# Create the object file directory
file(MAKE_DIRECTORY ${OBJECT_OUTPUT_DIR})

# Create a loop to generate object files for each assembly source file
foreach(OBJ_FILE ${OBJ_FILES})

	file(GENERATE OUTPUT ${OBJECT_OUTPUT_DIR}/${OBJ_FILE}.sh CONTENT "printf '#include \"SYS.h\"\nSYS(${OBJ_FILE})\n'")

	# Add a custom target to create object file stubs
	add_custom_target(
		${OBJ_FILE} ALL
		DEPENDS ${OBJECT_OUTPUT_DIR}/${OBJ_FILE}.sh
        	COMMAND bash ${OBJECT_OUTPUT_DIR}/${OBJ_FILE}.sh | ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} - -c -o ${OBJECT_OUTPUT_DIR}/${OBJ_FILE}.o 
		VERBATIM
		#WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    	)

	# Add the object file target as a dependency to the libc target
	#add_dependencies(libc ${OBJ_FILE})

	list(APPEND DYN_GEN_FILES ${OBJECT_OUTPUT_DIR}/${OBJ_FILE}.o) 

	#message("OBJECT_OUTPUT_DIR: ${OBJECT_OUTPUT_DIR}")	

endforeach()

#set variable for created object files
#file(GLOB O_FILES ${OBJECT_OUTPUT_DIR}/*.o)

message("Object files: ${DYN_GEN_FILES}")

# Custom target to build the static library
add_custom_target(libc STATIC DEPENDS assembler_objects c_objects ${DYN_GEN_FILES})
add_dependencies(libc assembler_objects c_objects)

# Print information about the generated object files
add_custom_command(
    TARGET libc
    COMMAND ${CMAKE_COMMAND} -E echo "Object files: ${OBJECT_OUTPUT_DIR}/*.o"
)

