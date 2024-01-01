cmake_minimum_required(VERSION 3.20)
project(myRetroBSD_native_libtermlib LANGUAGES C)

set(TOPSRC /home/gartnerd/code/myretrobsd)
set(LIBTERMDIR ${TOPSRC}/src/libtermlib)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -B${TOPSRC}/lib/ -Wall -Werror")

#get the required 'C' files
set(C_FILES ${LIBTERMDIR}/termcap.c ${LIBTERMDIR}/tgoto.c
	    ${LIBTERMDIR}/tputs.c ${LIBTERMDIR}/tcattr.c 
	    )

#message("C_FILES: ${C_FILES}")

set(CMAKE_AR ${retrobsd_BINARY_DIR}/ar)
set(CMAKE_RANLIB ${retrobsd_BINARY_DIR}/ranlib)

add_library(termlib STATIC ${C_FILES})

