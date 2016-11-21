               ARM Microcontroller Firmware Development Framework

   Here is a framework for developing firmware for a number of [1]ARM
   (Advanced RISC Machine) architecture single chip microcontrollers.

   Each MCU directory includes startup code, linker script, [2]newlib
   syscall bindings, and [3]OpenOCD scripts for debugging and flashing.

News

     * 21 January 2016 -- Upgraded binutils to 2.25.1, gcc to 5.3.0,
       newlib to 2.3.0, and gdb to 0.7.1.
     * 6 April 2016 -- New toolchain release 2016.097: Upgraded binutils
       to 2.26, newlib to 2.4.0 and gdb to 7.11.
     * 22 June 2016 -- Added I2C master and SPI master support for STM32F1
       devices. Added STM32F1 peripheral pin remapping services, allowing
       all board dependent code to be removed from driver modules i2c.,
       serial.c, and spi.c.
     * 23 June 2016 -- Added support for non-blocking I/O (O_NONBLOCK).
       Changed device_read_raw() to block by default, waiting for at least
       one byte of data.
     * 25 July 2016 -- Added byte stream framing library and demo program.
     * 2 November 2016 -- Modified device_read_raw() to return EAGAIN in
       errno if there is no data available on a stream with O_NONBLOCK
       set. Imported liblinx and libstream from [4]libsimpleio.
     * 8 November 2016 -- Upgraded binutils to 2.27. Upgraded gcc to
       5.4.0. Upgraded newlib to 2.4.0.20160923. Upgraded gdb to 7.12.
       Imported the [5]ut hash hash table library. Added [6]LabView LINX
       Remote I/O demo server, written in C++. It may need to be compiled
       with -O3 or -Os optimzation to fit in devices with 128K flash.
     * 18 November 2016 -- Downgraded gcc to 4.9.4 because of some issues
       with GCC 5.
     * 21 November 2016 -- Upgraded gcc to 6.2.0.

Git Repository

   The source code is available at: [7]http://git.munts.com

   Use the following command to clone it:

   git clone http://git.munts.com/arm-mcu.git

Copyright:

   Original works herein are copyrighted as follows:

Copyright (C)2013-2016, Philip Munts, President, Munts AM Corp.

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

   Questions or comments to Philip Munts [8]phil@munts.net

   I am available for custom system development (hardware and software) of
   products using these ARM microcontrollers.

References

   1. http://www.arm.com/
   2. http://sourceware.org/newlib
   3. http://openocd.sourceforge.net/
   4. http://git.munts.com/libsimpleio
   5. http://troydhanson.github.io/uthash/index.html
   6. https://www.labviewmakerhub.com/doku.php?id=learn:libraries:linx:spec:start
   7. http://git.munts.com/
   8. mailto:phil@munts.net
