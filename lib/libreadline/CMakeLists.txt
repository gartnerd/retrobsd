cmake_minimum_required(VERSION 3.20)
project(myRetroBSD_native_libreadline LANGUAGES C)

set(TOPSRC /home/gartnerd/code/myretrobsd)
set(LIBRDLDIR ${TOPSRC}/src/libreadline)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -B${TOPSRC}/lib/ -Wall -Werror")

#get the required 'C' file
set(C_FILE ${LIBRDLDIR}/readline.c )

#message("C_FILE: ${C_FILE}")

set(CMAKE_AR ${retrobsd_BINARY_DIR}/ar)
set(CMAKE_RANLIB ${retrobsd_BINARY_DIR}/ranlib)

add_library(readline STATIC ${C_FILE})
target_include_directories(readline PRIVATE ${LIBRDLDIR})
