cmake_minimum_required(VERSION 3.20.0)
project(retrobsd LANGUAGES C)

# I hope this is a temporary hack
set(TOPSRC "/home/gartnerd/code/myretrobsd")

# DG - Initial adding a hack to emulate original
# Have to create soft links to some header files
# to emulate what happens in the original makefile
add_custom_target(add_headers 
	COMMAND ${CMAKE_COMMAND} -E create_symlink ${TOPSRC}/include/a.out.h	${CMAKE_CURRENT_SOURCE_DIR}/a.out.h 
	COMMAND ${CMAKE_COMMAND} -E create_symlink ${TOPSRC}/include/ar.h	${CMAKE_CURRENT_SOURCE_DIR}/ar.h      
	COMMAND ${CMAKE_COMMAND} -E create_symlink ${TOPSRC}/include/nlist.h	${CMAKE_CURRENT_SOURCE_DIR}/nlist.h  
	COMMAND ${CMAKE_COMMAND} -E create_symlink ${TOPSRC}/include/ranlib.h	${CMAKE_CURRENT_SOURCE_DIR}/ranlib.h 
	COMMENT "creating header file symbolic links"
	)
		
# create archiver
# set source files
file(GLOB AR_SRC "${TOPSRC}/src/cmd/ar/*.c")
add_executable(ar ${AR_SRC})
add_dependencies(ar add_headers)
target_compile_options(ar PRIVATE -m32 -Os -fno-builtin -Wall -DCROSS -I${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options(ar PRIVATE -idirafter ${TOPSRC}/include )

file(GLOB AS_SRC "${TOPSRC}/src/cmd/as/*.c")
add_executable(as ${AS_SRC})
set_target_properties(as PROPERTIES C_STANDARD 90)
target_compile_options(as PRIVATE -m32 -Os -fno-builtin -Wall -DCROSS -I${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options(as PRIVATE -idirafter ${TOPSRC}/include )

file(GLOB AOUT_SRC "${TOPSRC}/src/cmd/aout/aout.c" "${TOPSRC}/src/cmd/aout/mips-dis.c")
add_executable(aout ${AOUT_SRC})
set_target_properties(aout PROPERTIES C_STANDARD 90)
target_compile_options(aout PRIVATE -m32 -Os -fno-builtin -Wall -DCROSS -I${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options(aout PRIVATE -idirafter ${TOPSRC}/include)

add_executable(ld ${TOPSRC}/src/cmd/ld/ld.c)
set_target_properties(ld PROPERTIES C_STANDARD 90)
target_compile_options(ld PRIVATE -m32 -Os -fno-builtin -Wall -DCROSS -I${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options(ld PRIVATE -idirafter ${TOPSRC}/include)

add_executable(nm ${TOPSRC}/src/cmd/nm/nm.c)
set_target_properties(nm PROPERTIES C_STANDARD 90)
target_compile_options(nm PRIVATE -m32 -Os -fno-builtin -Wall -DCROSS -I${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options(nm PRIVATE -idirafter ${TOPSRC}/include)

add_executable(ranlib ${TOPSRC}/src/cmd/ranlib/ranlib.c ${TOPSRC}/src/cmd/ar/archive.c)
set_target_properties(ranlib PROPERTIES C_STANDARD 90)
target_compile_options(ranlib PRIVATE -m32 -Os -fno-builtin -Wall -DCROSS -I${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options(ranlib PRIVATE -idirafter ${TOPSRC}/include)

add_executable(size ${TOPSRC}/src/cmd/size.c )
set_target_properties(size PROPERTIES C_STANDARD 90)
target_compile_options(size PRIVATE -m32 -Os -fno-builtin -Wall -DCROSS -I${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options(size PRIVATE -idirafter ${TOPSRC}/include)

add_executable(strip ${TOPSRC}/src/cmd/strip.c )
set_target_properties(strip PROPERTIES C_STANDARD 90)
target_compile_options(strip PRIVATE -m32 -Os -fno-builtin -Wall -DCROSS -I${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options(strip PRIVATE -idirafter ${TOPSRC}/include)


#-idirafter ${TOPSRC}/src/cmd/ar
#-idirafter ${TOPSRC}/src/cmd/as

# Recognized build types: Debug, Release, RelWithDebInfo, MinSizeRel
if("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
        if("${TR}")
                message("lib dir - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
        endif()

elseif("${TR}")
        message("lib dir - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

target_link_options(ar 	   PRIVATE -g -m32)
target_link_options(as	   PRIVATE -g -m32)
target_link_options(aout   PRIVATE -g -m32)
target_link_options(ld 	   PRIVATE -g -m32)
target_link_options(nm 	   PRIVATE -g -m32)
target_link_options(ranlib PRIVATE -g -m32)
target_link_options(size   PRIVATE -g -m32)
target_link_options(strip  PRIVATE -g -m32)

include(ExternalProject)

ExternalProject_Add(
    retrobsd_native
    PREFIX ${CMAKE_BINARY_DIR}/startup-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/startup
    CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/startup/mips32.toolchain.cmake
    INSTALL_COMMAND ""  # Disable
)

# Extract the build directory name from CMAKE_BINARY_DIR
#get_filename_component(BUILD_DIR_NAME ${CMAKE_BINARY_DIR} NAME)

ExternalProject_Add(
    retrobsd_native_libc
    PREFIX ${CMAKE_BINARY_DIR}/libc-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libc
    CMAKE_ARGS 
    		-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/libc/mips32.toolchain.cmake
		-Dretrobsd_BINARY_DIR=${retrobsd_BINARY_DIR}  # Pass the build directory name as a variable
    INSTALL_COMMAND ""  # Disable
)

ExternalProject_Add(
    retrobsd_native_libm
    PREFIX ${CMAKE_BINARY_DIR}/libm-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libm
    CMAKE_ARGS 
    		-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/libm/mips32.toolchain.cmake
		-Dretrobsd_BINARY_DIR=${retrobsd_BINARY_DIR}  # Pass the build directory name as a variable
    INSTALL_COMMAND ""  # Disable
)

ExternalProject_Add(
    retrobsd_native_libcurses
    PREFIX ${CMAKE_BINARY_DIR}/libcurses-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libcurses
    CMAKE_ARGS 
    		-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/libcurses/mips32.toolchain.cmake
		-Dretrobsd_BINARY_DIR=${retrobsd_BINARY_DIR}  # Pass the build directory name as a variable
    INSTALL_COMMAND ""  # Disable
)

ExternalProject_Add(
    retrobsd_native_libtermlib
    PREFIX ${CMAKE_BINARY_DIR}/libtermlib-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libtermlib
    CMAKE_ARGS 
    		-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/libtermlib/mips32.toolchain.cmake
		-Dretrobsd_BINARY_DIR=${retrobsd_BINARY_DIR}  # Pass the build directory name as a variable
    INSTALL_COMMAND ""  # Disable
)

ExternalProject_Add(
    retrobsd_native_libwiznet
    PREFIX ${CMAKE_BINARY_DIR}/libwiznet-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libwiznet
    CMAKE_ARGS 
    		-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/libwiznet/mips32.toolchain.cmake
		-Dretrobsd_BINARY_DIR=${retrobsd_BINARY_DIR}  # Pass the build directory name as a variable
    INSTALL_COMMAND ""  # Disable
)

ExternalProject_Add(
    retrobsd_native_libreadline
    PREFIX ${CMAKE_BINARY_DIR}/libreadline-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libreadline
    CMAKE_ARGS 
    		-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/libreadline/mips32.toolchain.cmake
		-Dretrobsd_BINARY_DIR=${retrobsd_BINARY_DIR}  # Pass the build directory name as a variable
    INSTALL_COMMAND ""  # Disable
)

ExternalProject_Add(
    retrobsd_native_libgpanel
    PREFIX ${CMAKE_BINARY_DIR}/libgpanel-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libgpanel
    CMAKE_ARGS 
    		-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/libgpanel/mips32.toolchain.cmake
		-Dretrobsd_BINARY_DIR=${retrobsd_BINARY_DIR}  # Pass the build directory name as a variable
    INSTALL_COMMAND ""  # Disable
)

