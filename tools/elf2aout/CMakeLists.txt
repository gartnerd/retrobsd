cmake_minimum_required(VERSION 3.20.0)
project(retrobsd LANGUAGES C)

#set(TR OFF)
#set_property(C_STANDARD_REQUIRED ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /tmp/elf2aoutbuild)

add_executable(elf2aout elf2aout.c)
set_target_properties(elf2aout PROPERTIES C_STANDARD 90)

#target_compile_definitions()
#target_compile_options(elf2aout PRIVATE -m32)

#string(TOUPPER ${CMAKE_BUILD_TYPE} buildtype )
#message("buildtype: ${buildtype}")
#string(COMPARE EQUAL ${buildtype} MINSIZEREL ms) 

#message("ms: ${ms}")
#Doesn't work - if("${string(COMPARE EQUAL string(TOUPPER ${CMAKE_BUILD_TYPE}) MINSIZEREL)}")
#Doesn't work - if("$<STREQUAL:$<UPPER_CASE:${CMAKE_BUILD_TYPE}>,MINSIZEREL>")

#according to chatgpt - the if() command does not support arbitrary expressions or function calls directly
#Note that the build type specified via the CLI has to exactly match the specified type or it fall through
if("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	if("${TR}")
		message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE} - should be Debug")
	endif()
	#Debug will cause cmake to automatically add the flag -g	
	#target_compile_options(elf2aout PRIVATE -O -Wall)

elseif("${CMAKE_BUILD_TYPE}" STREQUAL Release)
	message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE} - should be Release")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL MinSizeRel) 
	message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE} - should be MinSizeRel")
else()
	message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE} - fall through val")
endif()

#target_compile_options(elf2aout PRIVATE -g -O -Wall -m32)
target_link_options(elf2aout PRIVATE -m32)
#target_compile_definitions(elf2aout PRIVATE -g -O0 -Wall -m32)
