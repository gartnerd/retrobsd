cmake_minimum_required(VERSION 3.20.0)
project(retrobsd LANGUAGES C)

#set(TR OFF)
#set_property(C_STANDARD_REQUIRED ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /tmp/elf2aoutbuild)

#collect up the source files
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB SRC_FILES "${SRC_DIR}/*.c")

#DG - these files are used with different options (see further below) or
#DG - by the makefile Makefile-m4k - dev_nor_flash_4m.c does not appear
#DG - to be used by any target in the original makefile
set(FILES_TO_REMOVE 
	${SRC_DIR}/mips_codetable.c
	${SRC_DIR}/mips16-opc.c
	${SRC_DIR}/mips-opc.c
	${SRC_DIR}/pavo.c
	${SRC_DIR}/m4k.c
	${SRC_DIR}/dev_nor_flash_4m.c
	)

list(REMOVE_ITEM SRC_FILES ${FILES_TO_REMOVE})

#Search for required libs
find_library(pthread pthread REQUIRED)
find_library(elf elf REQUIRED)
find_library(rt rt REQUIRED)

#Apparently cmake will automatically detect dependencies on
#header files. They don't have to be expicitly specified as
#they are in make
add_executable(pic32 ${SRC_FILES})
set_target_properties(pic32 PROPERTIES C_STANDARD 90)

#CPP flags for various boards - good candidate for a list in a gui
target_compile_definitions(pic32 PRIVATE -DSIM_PIC32 -DPIC32MX7 -DMAX32)

#The following compiler flag is always required because the 
#target platform is 32bit and assuming compiler is GCC or CLANG
target_compile_options(pic32 PRIVATE -m32)

#Recognized build types: Debug, Release, RelWithDebInfo, MinSizeRel
if("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	if("${TR}")
		message("pic32 - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
	endif()
	
	#Debug will cause cmake to automatically add the flag -g
	#It appears that multiple calls concat options and not overwrite prev
	target_compile_options(pic32 PRIVATE -O -Wall)

elseif("${TR}")
	message("pic32 - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

target_link_libraries(pic32 PRIVATE pthread elf rt)
target_link_options(pic32 PRIVATE -m32)
