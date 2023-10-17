# This is the RetroBSD source directory.

## Source Roadmap

    bin         User commands.
    etc         Template files for /etc.
    include     System include files.
    lib         System libraries.
    libexec     System binaries.
    sbin        System administration commands.
    share       Shared resources.
    sys         Kernel sources.
    tools       Build tools and simulators.


## Supported hardware

 * Fubarino SD board.
 * Olimex Duinomite, Duinomite-Mini, Duinomite-Mega and Duinomite-eMega boards.
 * Olimex Pinguino-Micro board with PIC32MX795F512H microcontroller.
 * Maximite and Colour Maximite computers.
 * Majenko SDXL board.
 * 4D Systems Picadillo-35T board.
 * MikroElektronika MultiMedia Board for PIC32MX7.
 * chipKIT Max32 board with SD card shield.
 * chipKIT WF32 board with 2.4" LCD TFT display shield.
 * Sparkfun UBW32 board with SD card slot.
 * Microchip Explorer 16 board, with PIC32 CAN-USB plug-in module and SD & MMC pictail.
 * Microchip PIC32 USB or Ethernet Starter Kit, with I/O Expansion board and SD & MMC pictail.


## Build

To compile everything from sources, you'll need some packages installed, namely:
Berkeley YACC, GNU bison, flex, groff, ELF library and FUSE library.
Under Ubuntu, for example, you can do it by command:

```shell
$ sudo apt-get install bison byacc flex groff-base libelf-dev
```

## - PRELIMINARY (some steps need verification) -

You will need to setup multiarch support when building on 64bit systems because currently RetroBSD requires a 32bit build environment. You can run the following command on Debian based systems to see if any alternate architectures are setup:

```shell
$ dpkg --print-foreign-architectures
```

The output from the command will likely be an empty line unless you have already setup your system for developing with alternate architectures.

Use the following command to make 32bit x86 repos available (I think that is what the command does. See the following references - [Debian Wiki](https://wiki.debian.org/Multiarch/HOWTO), [Ubuntu Doc](https://help.ubuntu.com/community/MultiArch) and [Ubuntu Spec](https://wiki.ubuntu.com/MultiarchSpec). Much of this information was cribbed from : [Linode Help](https://www.linode.com/community/questions/19916/how-do-i-enable-32-bit-support-on-my-64-bit-os))

```shell
$ sudo dpkg --add-architecture i386
$ sudo apt-get update
```

Check if there are newer libraries of the packages you already have installed:

```shell
$ sudo apt-get dist-upgrade
```

Lastly install the requisite compilers and support libraries if not present:

```shell
$ sudo apt-get install build-essential binutils
$ sudo apt-get install binutils-multiarch
$ sudo apt-getinstall multiarch-support
$ sudo apt-get install gcc-multilib g++-multilib
```

Finding the packages that contain the required libraries can be a challenge. The following can help when using Debian systems:

* https://packages.debian.org/index

Using this website indicates that 32bit versions of libelf are found in the following packages

* libelf1
* libelf-dev

The 32bit version of these files can be installed using:

```shell
$sudo apt-get install libelf1:i386
$sudo apt-get install libelf-dev:i386
```

Its likely that you will encounter build errors because of missing tools. The easiest way to rectify this is to search the output from the 'make' command for errors. A tool called 'remake' can help with this.

## End of section

You can change a desired filesystem size and swap area size, as required.
Default is:
```Makefile
FS_MBYTES   = 100
SWAP_MBYTES = 2
```
To compile the kernel and build a filesystem image, run:

```shell
$ make
```

A resulting root filesystem image is in file `sdcard.img`.
A kernel is in file `unix.hex` in your target board subdirectory.


### Filesystem image

You need to put a filesystem image on a SD card.  On Windows, use
Win32DiskImager utility (https://launchpad.net/win32-image-writer/+download).
On Linux, run:

```shell
$ sudo dd if=sdcard.img of=/dev/XYZ
```

Here `XYZ` is a device name of SD card, as recognized by Linux (sdb in my case).


### Install kernel

Kernel image should be written to PIC32 flash memory.  The procedure depends
on a board used.

#### Max32 board:
Use a pic32prog utility (http://code.google.com/p/pic32prog/)
and a USB cable to install a kernel:

```shell
$ pic32prog -d /dev/ttyUSB0 sys/pic32/max32/unix.hex
```

Here you need to change AVRTOOLS path and tty name according to your system.

#### UBW32 board:
Use a pic32prog utility (http://code.google.com/p/pic32prog/)
and a USB cable to install a kernel:

```shell
$ pic32prog sys/pic32/ubw32/unix.hex
```

#### Maximite:
Use the bootload program for Windows, available for download by link:
http://geoffg.net/Downloads/Maximite/Maximite_Update_V2.7B.zip

#### Explorer 16 board:
There is an auxiliary PIC18 chip on the Explorer 16 board, which can be
used as a built-in programmer device.  You will need a PICkit 2 adapter
to install a needed firmware, as described in article:
http://www.paintyourdragon.com/?p=51
(section "Hack #2: Lose the PICkit 2, Save $35").
This should be done only once.

Then, you can use a pic32prog utility (http://code.google.com/p/pic32prog/)
and a USB cable to install a kernel:

``` shell
$ pic32prog sys/pic32/explorer16/unix.hex
```

#### PIC32 Starter Kit:
Use PICkit 2 adapter and software to install a boot loader from
file `sys/pic32/starter-kit/boot.hex`.  This should be done only once.

Then, you can use a pic32prog utility (http://code.google.com/p/pic32prog/)
and a USB cable to install a kernel:

```shell
$ pic32prog sys/pic32/starter-kit/unix.hex
```


## Simulator

You can use a MIPS32 simulator to develop a debug a RetroBSD software,
without a need for hardware board.  By default, a simulator is configured
to imitate a Max32 board.  To build it:

```shell
$ cd tools/virtualmips
$ make
```

Run it:

```shell
$ ./pic32
```

Configuration of simulated board is stored in file `pic32_max32.conf`.
