cmake_minimum_required(VERSION 3.20)
project(myRetroBSD_native_libm LANGUAGES C)

set(TOPSRC /home/gartnerd/code/myretrobsd)
set(LIBMDIR ${TOPSRC}/src/libm)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -B${TOPSRC}/lib/ -Wall -Werror")

#get the required 'C' files
file(GLOB C_FILES ${LIBMDIR}/*.c)

#get rid of the files that aren't used
list(REMOVE_ITEM C_FILES ${LIBMDIR}/fabs.c)

#message("C_FILES: ${C_FILES}")

set(CMAKE_AR ${retrobsd_BINARY_DIR}/ar)
set(CMAKE_RANLIB ${retrobsd_BINARY_DIR}/ranlib)

add_library(m STATIC ${C_FILES})

