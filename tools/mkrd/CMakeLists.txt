cmake_minimum_required(VERSION 3.20.0)
project(retrobsd LANGUAGES C)

#set(TR OFF)
#set_property(C_STANDARD_REQUIRED ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /tmp/elf2aoutbuild)

add_executable(mkrd mkrd.c )
set_target_properties(mkrd PROPERTIES C_STANDARD 90)

#The following compiler flag is always required because the 
#target platform is 32bit and assuming compiler is GCC or CLANG
target_compile_options(mkrd PRIVATE -m32)

#Recognized build types: Debug, Release, RelWithDebInfo, MinSizeRel
if("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	if("${TR}")
		message("mkrd - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
		message("mkrd - CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
	endif()
	
	#Debug will cause cmake to automatically add the flag -g
	#It appears that multiple calls concat options and not overwrite prev
	target_compile_options(mkrd PRIVATE -O -Wall -Werror)

elseif("${TR}")
	message("mkrd - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

target_link_options(mkrd PRIVATE -m32)
