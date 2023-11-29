cmake_minimum_required(VERSION 3.20.0)
project(retrobsd LANGUAGES C)

#a bin directory can also be specified along with the source dir
add_subdirectory(elf2aout)
add_subdirectory(fsutil)
add_subdirectory(virtualmips)
add_subdirectory(mkrd)
add_subdirectory(kconfig)
add_subdirectory(icache)

#set(TR OFF)
#set_property(C_STANDARD_REQUIRED ON)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY /tmp/elf2aoutbuild)
