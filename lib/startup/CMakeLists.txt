cmake_minimum_required(VERSION 3.20.0)
project(retrobsd_native LANGUAGES C)

set(TOPSRC /home/gartnerd/code/myretrobsd)
#set_target_properties(crt PROPERTIES C_STANDARD 90)

# Basically all this build has to do is create an object file
# and place it in the parent directory

# main target
add_library(crt0 OBJECT ${TOPSRC}/src/startup-mips/crt0.c)

# Create a custom target to copy the object file after it's built
add_custom_target(CopyObjectFile ALL
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_OBJECTS:crt0> ${CMAKE_CURRENT_SOURCE_DIR}/../crt0.o
	DEPENDS crt0
)

target_compile_options(crt0 PRIVATE -Os -B${TOPSRC}/lib/)
