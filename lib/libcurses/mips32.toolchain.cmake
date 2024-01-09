# mips32.toolchain.cmake
# https://sourcery.mentor.com/GNUToolchain/release2641

set(TOPSRC /home/gartnerd/code/myretrobsd)

# Set the compiler
set(CMAKE_C_COMPILER /usr/local/mips-2013.11/bin/mips-sde-elf-gcc)
set(CMAKE_CXX_COMPILER /usr/local/mips-2013.11/bin/mips-sde-elf-g++)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR mips32)

# Specify the cross-compiler prefix
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Specify the root directory of the cross-compiler
set(CMAKE_FIND_ROOT_PATH /usr/local/mips-2013.11/bin)

set(CMAKE_C_FLAGS "-mips32r2 -EL -msoft-float -nostdinc -fshort-double -I${TOPSRC}/include")

