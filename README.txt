               ARM Microcontroller Firmware Development Framework

   Here are some frameworks for developing firmware for a number of [1]ARM
   (Advanced RISC Machine) architecture single chip microcontrollers.

   I am interested in alternatives to the traditional GCC development
   environment, so you will find here some experiments with [2]Astrobe
   Oberon, [3]Free Pascal, [4]GNAT Ada, [5]Mbed OS 5, and [6]Mikropascal
   for ARM microcontrollers. I am convinced that the true value of a
   microcontroller development environment lies in the richness of its
   software component libraries more than any other factor. For this
   reason, my own work has mostly switched to Mbed OS 5 and Mikropascal,
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

Git Repository

   The source code is available at: [9]http://git.munts.com

   Use the following command to clone it:

   git clone http://git.munts.com/arm-mcu.git

Copyright:

   Original works herein are copyrighted as follows:

Copyright (C)2013-2018, Philip Munts, President, Munts AM Corp.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

   Redistributed works herein are copyrighted and/or licensed by their
   respective authors.
   ___________________________________________________________________

   Questions or comments to Philip Munts [10]phil@munts.net

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
   9. http://git.munts.com/
  10. mailto:phil@munts.net
