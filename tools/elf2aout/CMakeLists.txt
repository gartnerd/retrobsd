cmake_minimum_required(VERSION 3.20.0)
project(retrobsd LANGUAGES C)

#set(TR OFF)
#set_property(C_STANDARD_REQUIRED ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /tmp/elf2aoutbuild)

add_executable(elf2aout elf2aout.c)
set_target_properties(elf2aout PROPERTIES C_STANDARD 90)

#use the following for CPP defs
#target_compile_definitions(elf2aout PRIVATE -D)

#The following compiler flag is always required because the 
#target platform is 32bit and assuming compiler is GCC or CLANG
target_compile_options(elf2aout PRIVATE -m32)

#Apparently the if() command does not support arbitrary expressions or function calls directly
#Note that the build type specified via the CLI has to exactly match the specified type or it fall through
#Recognized build types: Debug, Release, RelWithDebInfo, MinSizeRel
if("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	if("${TR}")
		message("elf2aout - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
	endif()
	
	#Debug will cause cmake to automatically add the flag -g
	#It appears that multiple calls concat options and not overwrite prev
	target_compile_options(elf2aout PRIVATE -O -Wall)

elseif("${TR}")
	message("elf2aout - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

target_link_options(elf2aout PRIVATE -m32)
