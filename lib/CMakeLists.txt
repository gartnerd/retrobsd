cmake_minimum_required(VERSION 3.20.0)
project(retrobsd LANGUAGES C)

# I hope this is a temporary hack
set(TOPSRC "/home/gartnerd/code/myretrobsd")

# Have to create soft links to some header files
# to emulate what happens in the original makefile
#add_custom_target(add_headers 
#	COMMAND create_symlink a.out.h "${TOPSRC}/include/a.out.h" )
#
#		  COMMAND create_symlink  ar.h     ../../include/ar.h 
#		  COMMAND create_symlink  nlist.h  ../../include/nlist.h
#		  COMMAND create_symlink  ranlib.h ../../include/ranlib.h
#		  COMMENT "creating header file symbolic links"
#		  )
		
# create archiver
# set source files
file(GLOB AR_SRC "${TOPSRC}/src/cmd/ar/*.c")

include_directories(BEFORE	"${TOPSRC}/include" 
				"${TOPSRC}/src/cmd/ar" 
				"${TOPSRC}/src/cmd/as"
		    )

add_executable(ar ${AR_SRC})

#add_dependencies(ar add_headers)
#message("AR_SRC: ${AR_SRC}")

target_compile_options(ar PRIVATE -m32 -Os -fno-builtin -Wall -DCROSS -I. )
target_compile_options(ar PRIVATE	-idirafter ${TOPSRC}/include 
                   			-idirafter ${TOPSRC}/src/cmd/ar
                   			-idirafter ${TOPSRC}/src/cmd/as
					)

# Recognized build types: Debug, Release, RelWithDebInfo, MinSizeRel
if("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
        if("${TR}")
                message("ar - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
        endif()

        #Debug will cause cmake to automatically add the flag -g
        #It appears that multiple calls concat options and not overwrite prev
        target_compile_options(ar PRIVATE -Os -fno-builtin -Wall 
			       	-DCROSS -I. 
				)

elseif("${TR}")
        message("kconfig - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

target_link_options(ar PRIVATE -g -m32)

include(ExternalProject)

ExternalProject_Add(
    retrobsd_native
    PREFIX ${CMAKE_BINARY_DIR}/startup-build
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/startup
    CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/startup/mips32.toolchain.cmake
    INSTALL_COMMAND ""  # Disable
)
