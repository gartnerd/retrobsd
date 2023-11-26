cmake_minimum_required(VERSION 3.20.0)
project(retrobsd LANGUAGES C)

#set(TR OFF)
#set_property(C_STANDARD_REQUIRED ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /tmp/elf2aoutbuild)

#collect up the source files
file(GLOB SRC_FILES "*.c")

#Apparently cmake will automatically detect dependencies on
#header files. They don't have to be expicitly specified as
#they are in make
add_executable(fsutil ${SRC_FILES})
set_target_properties(fsutil PROPERTIES C_STANDARD 90)

#use the following for CPP defs
#target_compile_definitions(elf2aout PRIVATE -D)

#The following compiler flag is always required because the 
#target platform is 32bit and assuming compiler is GCC or CLANG
target_compile_options(fsutil PRIVATE -m32)

#Recognized build types: Debug, Release, RelWithDebInfo, MinSizeRel
if("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	if("${TR}")
		message("fsutil - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
		message("fsutil - CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
	endif()
	
	#Debug will cause cmake to automatically add the flag -g
	#It appears that multiple calls concat options and not overwrite prev
	target_compile_options(fsutil PRIVATE -O -Wall)

elseif("${TR}")
	message("fsutil - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

target_link_options(fsutil PRIVATE -m32)
