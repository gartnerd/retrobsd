cmake_minimum_required(VERSION 3.20.0)
project(retrobsd LANGUAGES C)

#set_property(C_STANDARD_REQUIRED ON)

add_executable(ice2aout ice2aout.c)
set_target_properties(ice2aout PROPERTIES C_STANDARD 90)

#The following compiler flag is always required because the 
#target platform is 32bit and assuming compiler is GCC or CLANG
target_compile_options(ice2aout PRIVATE -m32)

#Apparently the if() command does not support arbitrary expressions or function calls directly
#Note that the build type specified via the CLI has to exactly match the specified type or it fall through
#Recognized build types: Debug, Release, RelWithDebInfo, MinSizeRel
if("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	if("${TR}")
		message("ice2aout - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
	endif()
	
	#Debug will cause cmake to automatically add the flag -g
	#It appears that multiple calls concat options and not overwrite prev
	target_compile_options(ice2aout PRIVATE -O -Wall)

elseif("${TR}")
	message("ice2aout - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

target_link_options(ice2aout PRIVATE -m32)
