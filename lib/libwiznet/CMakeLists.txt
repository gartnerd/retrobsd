cmake_minimum_required(VERSION 3.20)
project(myRetroBSD_native_libwiznet LANGUAGES C)

set(TOPSRC /home/gartnerd/code/myretrobsd)
set(LIBWIZNETDIR ${TOPSRC}/src/libwiznet)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -B${TOPSRC}/lib/ -Wall -Werror")

#get the required 'C' files
file(GLOB C_FILES ${LIBWIZNETDIR}/*.c)

#message("C_FILES: ${C_FILES}")

set(CMAKE_AR ${retrobsd_BINARY_DIR}/ar)
set(CMAKE_RANLIB ${retrobsd_BINARY_DIR}/ranlib)

add_library(wiznet STATIC ${C_FILES})

