cmake_minimum_required(VERSION 3.20)
project(myRetroBSD_native_libc LANGUAGES )

#set(CMAKE_C_COMPILER_WORKS 1)

# List all your assembly source files
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

    # Add a custom target for assembling
    add_custom_target(
	${OBJ_FILE} ALL
	#DEPENDS ${OBJECT_OUTPUT_DIR}/${OBJ_FILE}.sh
        COMMAND bash ${OBJECT_OUTPUT_DIR}/${OBJ_FILE}.sh | ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} - -c -o ${OBJECT_OUTPUT_DIR}/${OBJ_FILE}.o 
	VERBATIM
	#WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )


endforeach()

#add_library(libc STATIC ${OBJECT_OUTPUT_DIR}/__sysctl.o ${OBJECT_OUTPUT_DIR}/__sysctl.o)

