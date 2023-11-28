cmake_minimum_required(VERSION 3.20.0)
project(retrobsd LANGUAGES C)

# collect up the source files
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

# commands to generated a parser via "byacc"
# typically done with an "include_pkg" function
# but none available for byacc
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/config.c 
			  ${CMAKE_CURRENT_SOURCE_DIR}/y.tab.h
		   COMMAND byacc -d ${CMAKE_CURRENT_SOURCE_DIR}/config.y
		   COMMAND mv -f ${CMAKE_CURRENT_BINARY_DIR}/y.tab.c 
		   		 ${CMAKE_CURRENT_SOURCE_DIR}/config.c
		   COMMAND mv -f ${CMAKE_CURRENT_BINARY_DIR}/y.tab.h
		   		 ${CMAKE_CURRENT_SOURCE_DIR}/y.tab.h
		   VERBATIM
		   )

# command to generate lexer
add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lang.c 
       		   COMMAND lex -t ${CMAKE_CURRENT_SOURCE_DIR}/lang.l >
		   	   	  ${CMAKE_CURRENT_SOURCE_DIR}/lang.c
		   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lang.l
		   VERBATIM
	   	   )	   

# main target
add_executable(kconfig  ${CMAKE_CURRENT_SOURCE_DIR}/config.c 
			${CMAKE_CURRENT_SOURCE_DIR}/lang.c
			${SRC_FILES} 
			)

# Add a custom command to remove the files generated
# by byacc and lex - this is emulates "makes" actions
add_custom_command(TARGET kconfig POST_BUILD
		   COMMAND ${CMAKE_COMMAND} -E remove 
				${CMAKE_CURRENT_SOURCE_DIR}/config.c
				${CMAKE_CURRENT_SOURCE_DIR}/lang.c
				${CMAKE_CURRENT_SOURCE_DIR}/y.tab.h
    		   COMMENT "\tdeleting config.c, lang.c and y.tab.h"
		   )

# custom command to generate man file
add_custom_command(TARGET kconfig POST_BUILD
       		   COMMAND groff -man ${CMAKE_CURRENT_SOURCE_DIR}/kconfig.8
		   		    > kconfig.0
		   COMMENT "\tbuilding man page"
		   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/kconfig.8
		   VERBATIM
	   	   )	   

# Create a custom target 
# Using to remove byacc and lex generated files and to
# create the man page for kconfig
add_custom_target(rm_gen_files DEPENDS kconfig)
add_custom_target(man_files DEPENDS kconfig)

# Make sure the custom command is executed after the build
add_dependencies(rm_gen_files kconfig)
add_dependencies(man_files kconfig)

set_target_properties(kconfig PROPERTIES C_STANDARD 90)

# The following compiler flag is always required because the 
# target platform is 32bit and assuming compiler is GCC or CLANG
target_compile_options(kconfig PRIVATE -m32)

# Recognized build types: Debug, Release, RelWithDebInfo, MinSizeRel
if("${CMAKE_BUILD_TYPE}" STREQUAL Debug)
	if("${TR}")
		message("kconfig - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
	endif()
	
	#Debug will cause cmake to automatically add the flag -g
	#It appears that multiple calls concat options and not overwrite prev
	target_compile_options(kconfig PRIVATE -O -Wall -Werror)

elseif("${TR}")
	message("kconfig - CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

target_link_options(kconfig PRIVATE -m32)
