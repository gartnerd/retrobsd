cmake_minimum_required(VERSION 3.20)
project(myRetroBSD_native_libgpanel LANGUAGES C)

set(TOPSRC /home/gartnerd/code/myretrobsd)
set(LIBGPDIR ${TOPSRC}/src/libgpanel)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -B${TOPSRC}/lib/ -Wall -Werror")

#get the required 'C' files
#file(GLOB C_FILES ${LIBGPDIR}/*.c)

set(C_FILES ${LIBGPDIR}/open.c  ${LIBGPDIR}/clear.c
	    ${LIBGPDIR}/pixel.c ${LIBGPDIR}/line.c
	    ${LIBGPDIR}/rect.c  ${LIBGPDIR}/fill.c
	    ${LIBGPDIR}/fill_triangle.c 
	    ${LIBGPDIR}/circle.c
	    ${LIBGPDIR}/image.c ${LIBGPDIR}/char.c
	    ${LIBGPDIR}/text.c  ${LIBGPDIR}/text_width.c
	)

message("C_FILES: ${C_FILES}")

set(CMAKE_AR ${retrobsd_BINARY_DIR}/ar)
set(CMAKE_RANLIB ${retrobsd_BINARY_DIR}/ranlib)

add_library(gpanel STATIC ${C_FILES})

