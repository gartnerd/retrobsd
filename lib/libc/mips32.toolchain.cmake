# mips32.toolchain.cmake
# https://sourcery.mentor.com/GNUToolchain/release2641

set(TOPSRC /home/gartnerd/code/myretrobsd)

# Set the compiler
set(CMAKE_C_COMPILER /usr/local/mips-2013.11/bin/mips-sde-elf-gcc)
set(CMAKE_CXX_COMPILER /usr/local/mips-2013.11/bin/mips-sde-elf-g++)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR mips32)

# Specify the cross-compiler prefix
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Specify the root directory of the cross-compiler
set(CMAKE_FIND_ROOT_PATH /usr/local/mips-2013.11/bin)

# Specify compiler flags - Debug, Release, RelMinSize, etc
set(CMAKE_C_FLAGS -mips32r2 -EL -msoft-float -nostdinc -fshort-double -Os -I${TOPSRC}/include -x assembler-with-cpp -c -B${TOPSRC}/lib/)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} -I${TOPSRC}/src/libc/mips/sys -I/usr/local/mips-2013.11/mips-sde-elf/include/sys -DLWHI=lwr -DLWLO=lwl -DSWHI=swr -DSWLO=swl) 

# Specify linker flags - EXE,STATIC,SHARED & MODULE
set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -Wl,--oformat=elf32-tradlittlemips -N -nostartfiles -fno-dwarf2-cfi-asm -T${TOPSRC}/src/elf32-mips.ld ${TOPSRC}/src/crt0.o -L${TOPSRC}/src
")

# Additional settings as needed
