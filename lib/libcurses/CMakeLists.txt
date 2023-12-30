cmake_minimum_required(VERSION 3.20)
project(myRetroBSD_native_libcurses LANGUAGES C)

set(TOPSRC /home/gartnerd/code/myretrobsd)
set(LIBCURSESDIR ${TOPSRC}/src/libcurses)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -B${TOPSRC}/lib/ -Wall -Werror")

#get the required 'C' files
file(GLOB C_FILES ${LIBCURSESDIR}/*.c)

#get rid of the files that aren't used
list(REMOVE_ITEM C_FILES ${LIBCURSESDIR}/test.c)

#message("C_FILES: ${C_FILES}")

set(CMAKE_AR ${retrobsd_BINARY_DIR}/ar)
set(CMAKE_RANLIB ${retrobsd_BINARY_DIR}/ranlib)

add_library(curses STATIC ${C_FILES})

