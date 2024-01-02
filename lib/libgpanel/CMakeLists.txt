cmake_minimum_required(VERSION 3.20)
project(myRetroBSD_native_libgpanel LANGUAGES C)

set(TOPSRC /home/gartnerd/code/myretrobsd)
set(LIBGPDIR ${TOPSRC}/src/libgpanel)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os -B${TOPSRC}/lib/ -Wall -Werror")

#get the required 'C' files
#file(GLOB C_FILES ${LIBGPDIR}/*.c)

#the file fill_tangle.c is a copy of fill_triangle. I think for some historical
#reasons the length of the filename was limited to 15 chars. If greater than that then
#the "ar" program changes the header information in the created archive. This however
#causes "ranlib" to choke. Simple fix is to rename the file to something shorter.
#The original file name is fine with GNU make because it uses a standard ".o" extension instead of 
#cmake's ".c.o" extension when creating the object file. These two extra chars cause it to exceed
#the filename length limit

set(C_FILES ${LIBGPDIR}/open.c  ${LIBGPDIR}/clear.c
	    ${LIBGPDIR}/pixel.c ${LIBGPDIR}/line.c
	    ${LIBGPDIR}/rect.c  ${LIBGPDIR}/fill.c
	    ${LIBGPDIR}/fill_tangle.c #run up against a name length limit in the "ar" program
	    ${LIBGPDIR}/circle.c
	    ${LIBGPDIR}/image.c ${LIBGPDIR}/char.c
	    ${LIBGPDIR}/text.c  ${LIBGPDIR}/text_width.c
	)

#message("C_FILES: ${C_FILES}")

set(CMAKE_AR ${retrobsd_BINARY_DIR}/ar)
set(CMAKE_RANLIB ${retrobsd_BINARY_DIR}/ranlib)

add_library(gpanel STATIC ${C_FILES})

