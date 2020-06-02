               ARM Microcontroller Firmware Development Framework

   Here are some frameworks for developing firmware for a number of [1]ARM
   (Advanced RISC Machine) architecture single chip microcontrollers.

   I am interested in alternatives to the traditional GCC development
   environment, so you will find here some experiments with [2]Astrobe
   Oberon, [3]Free Pascal, [4]GNAT Ada, [5]ARM Mbed OS, and [6]Mikropascal
   for ARM microcontrollers. I am convinced that the true value of a
   microcontroller development environment lies in the richness of its
   software component libraries more than any other factor. For this
   reason, my own work has mostly switched to ARM Mbed OS and Mikropascal,
   both of which include very extensive component libraries.

News

     * 13 March 2017 -- Moved the original GCC framework into the gcc/
       subdirectory. Removed some obsolete cruft (EFM32, mbed Classic,
       etc.). Started adding support for developing with [7]Free Pascal
       Embedded for ARM microcontrollers.
     * 17 March 2017 -- Updated binutils to 2.28, gcc to 6.3.0, newlib to
       2.5.0, and gdb to 7.12.1. Imported [8]LEGO Power Functions Infrared
       Remote Control Protocol implementation.
     * 20 March 2017 -- Cleaned up and reordered ARM.mk. Modified ARM.mk
       to append CFLAGS, CXXFLAGS, and LDFLAGS to RMAKEFLAGS so ensure
       that they are propagated to subordinate make jobs. Added
       lightweight_strncasecmp() to conio.c.
     * 19 September 2017 -- Upgraded binutils to 2.29, gcc to 7.2.0, and
       gdb to 8.0.1.
     * 9 April 2019 -- The framework here for using [9]ARM Mbed OS has
       been greatly improved and streamlined. Compiling the OS takes quite
       a while, so it is now built as a library once for each target board
       and saved in ~/.mbedos. This speeds up building and rebuilding
       applications.
     * 2 June 2020 -- Upgraded Mbed OS to 5.15.3. Also made some minor
       tweaks to the Mbed OS framework.

Git Repository

   The source code is available at: [10]http://git.munts.com/arm-mcu

   Use the following command to clone it:

   git clone http://git.munts.com/arm-mcu.git
   _______________________________________________________________________

   Questions or comments to Philip Munts [11]phil@munts.net

   I am available for custom system development (hardware and software) of
   products using these ARM microcontrollers.

References

   1. http://www.arm.com/
   2. http://www.astrobe.com/
   3. http://wiki.freepascal.org/Embedded
   4. https://docs.adacore.com/gnat_ugx-docs/html/gnat_ugx/gnat_ugx/arm-elf_topics_and_tutorial.html
   5. https://os.mbed.com/
   6. https://www.mikroe.com/mikropascal-arm
   7. http://wiki.freepascal.org/TARGET_Embedded
   8. https://www.lego.com/en-us/powerfunctions/articles/8884-control-5fcb2efbb4e74f0c926948df71445765
   9. https://www.mbed.com/en/platform/mbed-os
  10. http://git.munts.com/arm-mcu
  11. mailto:phil@munts.net
